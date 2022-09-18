#include "DxLib.h"
#include "PowerModeProcess.h"
#include "EnemyAra.h"
#include "Player.h"
#include "Worldval.h"
#include "ConstVal.h"
#include <math.h>

PowerModeProcess::State PowerModeProcess::state = PowerModeProcess::State::free; //���̒�`
int PowerModeProcess::time = 0;
int PowerModeProcess::rawDrawTime = 120; //���̒l
int PowerModeProcess::drawTime = rawDrawTime;

PowerModeProcess::PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy) :player(setPlayer), enemy(setEnemy), combo(0), target(nullptr), eatSE3(*WorldVal::Get<int>("eatSE3")) { //�쐬�������s��Ԃɏ�����
	time = 0;
	drawTime = 0;
	state = State::free;
}

void PowerModeProcess::Update() {
	switch (state) {
	case PowerModeProcess::State::start:
		if (time <= 0) { //�p���[���[�h���������Ă����ꍇ�G���]�����s���Ȃ�if��
			for (int i = 0; i < enemy->size(); ++i) { (*enemy)[i]->SetReversOrder(true); } //�G���]����
		}
		combo = 0; //�R���{�̏�����
		time = ClculatIniTime(); //�V�������s���ԓ���
		if (time <= 0) { return; } //�V�������Ԃ�0�Ȃ甽�]�����ďI���

		player->SetState(Player::State::power); //�v���C���[�̏�Ԃ��p���[�G�T�L����ԂɕύX
		for (int i = 0; i < enemy->size(); ++i) { 
			EnemyAra::State enemyState = (*enemy)[i]->GetState();
			if (enemyState != EnemyAra::State::damage) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //�����ԈȊO�Ȃ�C�W�P��Ԃ�t�^����
		}
		state = State::run; //���s���ɕύX

		break;
	case PowerModeProcess::State::run:
		if (drawTime > 0) { break; } //�X�R�A�\�����͎��s��~
		--time; //�J�E���g�_�E��
		
		if (time <= 0) {
			player->SetState(Player::State::neutral); //�v���C���[�̏�Ԃ�ʏ��ԂɕύX
			for (int i = 0; i < enemy->size(); ++i) {
				EnemyAra::State enemyState = (*enemy)[i]->GetState();
				if (enemyState != EnemyAra::State::damage) { (*enemy)[i]->SetState(EnemyAra::State::neutral); } //�����ԈȊO�̓G�͒ʏ�ɂ���
			}
			state = State::free; //���s�󋵂������ԂɕύX
		}
		break;
	case PowerModeProcess::State::end:
		break;
	case PowerModeProcess::State::free:
		break;
	}
}

void PowerModeProcess::Draw() {
	if (drawTime > 0) { //�`�ʎ��Ԃ�0���ߎ��̂ݎ��s
		if (drawTime == 1) { //���ŏI���̏ꍇ�I��������ʂ�
			//�G�l�~�[�A�v���C���[�̏����A�\���̍ĊJ
			for (int i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(true);
				(*enemy)[i]->SetRunDraw(true);
			}
			player->SetRunUpdate(true);
			player->SetRunDraw(true);
			drawTime = 0;
			return;
		}
		SetFontSize(18);
		DrawFormatString(target->GetDrawX(), target->GetDrawY(), GetColor(0, 255, 255), "%d", ClculatScore()); //�X�R�A�\��
		--drawTime;
	}
}

void PowerModeProcess::Hit(EnemyAra* set) {
	target = set; //�X�R�A�\���̃^�[�Q�b�g���w��
	drawTime = rawDrawTime; //�c��\�����Ԃ̏�����
	for (int i = 0; i < enemy->size(); ++i) {
		if ((*enemy)[i]->GetState() == EnemyAra::State::damage) { continue; } //�����Ԃ̓G�͎~�߂Ȃ�
		(*enemy)[i]->SetRunUpdate(false); //�����̔���s
		(*enemy)[i]->SetRunDraw(false); //��\����
	}
	player->SetRunUpdate(false); //�����̔���s
	player->SetRunDraw(false); //��\����
	target->SetState(EnemyAra::State::damage); //�^�[�Q�b�g�G�������Ԃɐݒ�
	++combo; //�R���{�l�����Z
	*WorldVal::Get<int>("score") += ClculatScore(); //�X�R�A���Z

	//������se�炵������
	PlaySoundMem(eatSE3,DX_PLAYTYPE_BACK);

}

int PowerModeProcess::ClculatIniTime() {
	switch (*WorldVal::Get<int>("nowStage")) { //���݃X�e�[�W���ɍ��킹�ĕԂ����Ԃ�ς���
	case 0:
		return 6 * FPS; 

	case 1: case 5: case 9:
		return 5 * FPS;

	case 2:
		return 4 * FPS;

	case 3: case 13:
		return 3 * FPS;

	case 4: case 6: case 7: case 10:
		return 2 * FPS;

	case 8: case 11: case 12: case 14: case 15: case 17:
		return 1 * FPS;

	default: return 0;
	}
}

int PowerModeProcess::ClculatScore() { return 100 * pow(2, combo); }