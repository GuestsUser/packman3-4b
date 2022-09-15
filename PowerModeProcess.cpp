#include "PowerModeProcess.h"
#include "EnemyAra.h"
#include "Player.h"
#include "Worldval.h"
#include "ConstVal.h"

PowerModeProcess::State PowerModeProcess::state = PowerModeProcess::State::free; //���̒�`
int PowerModeProcess::time = 0;

PowerModeProcess::PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy) :player(setPlayer),enemy(setEnemy) { //�쐬�������s��Ԃɏ�����
	time = 0;
	state = State::free;
}

void PowerModeProcess::Update() {
	switch (state) {
	case PowerModeProcess::State::start:
		if (time <= 0) { //�p���[���[�h���������Ă����ꍇ�G���]�����s���Ȃ�if��
			for (int i = 0; i < enemy->size(); ++i) { (*enemy)[i]->SetReversOrder(true); } //�G���]����
		}
		time = ClculatIniTime(); //�V�������s���ԓ���
		if (time <= 0) { return; } //�V�������Ԃ�0�Ȃ甽�]�����ďI���

		player->SetState(Player::State::power); //�v���C���[�̏�Ԃ��p���[�G�T�L����ԂɕύX
		for (int i = 0; i < enemy->size(); ++i) { 
			EnemyAra::State enemyState = (*enemy)[i]->GetState();
			if (enemyState == EnemyAra::State::neutral || enemyState == EnemyAra::State::wait) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //�ʏ�A�ҋ@��Ԃ̓G�ɂ̂݃C�W�P��Ԃ�t�^����
		}
		state = State::run; //���s���ɕύX

		break;
	case PowerModeProcess::State::run:
		--time;
		if (time <= 0) {
			player->SetState(Player::State::neutral); //�v���C���[�̏�Ԃ�ʏ��ԂɕύX
			for (int i = 0; i < enemy->size(); ++i) {
				EnemyAra::State enemyState = (*enemy)[i]->GetState();
				if (enemyState == EnemyAra::State::cringe) { (*enemy)[i]->SetState(EnemyAra::State::neutral); } //�ҋ@��ԉ������@�ɂ���Ă̓o�O�𐶂މ\������
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
