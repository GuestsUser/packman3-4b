#include "Sound.h"
#include "Worldval.h"
#include "PowerModeProcess.h"
#include "DxLib.h"

Sound::Sound(PowerModeProcess* set, Player* pacman, std::deque<EnemyAra*>* getEnemy) : powerMode(set),player(pacman), enemy(getEnemy)
{
	count1 = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	count5 = 0;

	enemyMoveSE = *WorldVal::Get<int>("enemyMoveSE");
	squrtSE1 = *WorldVal::Get<int>("squrtSE1");
	squrtSE2 = *WorldVal::Get<int>("squrtSE2");
	squrtSE3 = *WorldVal::Get<int>("squrtSE3");
	squrtSE4 = *WorldVal::Get<int>("squrtSE4");

	cringeSE = *WorldVal::Get<int>("cringeSE");
	damageSE = *WorldVal::Get<int>("damageSE");

	foodcount = WorldVal::Get<int>("foodCountTotal");

	isUpdate = false;
	flg = false;
	flg = false;
}

void Sound::Update()
{
	if (isUpdate)
	{
		if (powerMode->GetState() == PowerModeProcess::State::free)
		{
			if (*foodcount >= 0 && *foodcount <= 115) {
				if (count1 == 0)
				{
					PlaySoundMem(enemyMoveSE, DX_PLAYTYPE_LOOP);
					count1 = 1;
				}
			}
		}

		if (*foodcount == 244) {
			//�N���A������A��\���̂��鉹���ׂĎ~�߂�
			StopSound();
			StopSoundMem(cringeSE);
			StopSoundMem(damageSE);
			return;
		}

		for (int i = 0; i < enemy->size(); ++i) {
			EnemyAra::State enemyState = (*enemy)[i]->GetState();
			//if (enemyState == EnemyAra::State::neutral || enemyState == EnemyAra::State::wait) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //�ʏ�A�ҋ@��Ԃ̓G�ɂ̂݃C�W�P��Ԃ�t�^����
			if (enemyState == EnemyAra::State::damage) {
				ChangeSound2();
				return;
			}
		}
		StopSoundMem(damageSE);
		flg2 = false;

		if (powerMode->GetState() == PowerModeProcess::State::run) { ChangeSound(); return; } //�p���[�G�T�L�����Ȃ�Ȃ�ς���

		//for (int i = 0; i < enemy->size(); ++i) {
		//	EnemyAra::State enemyState = (*enemy)[i]->GetState();
		//	//if (enemyState == EnemyAra::State::neutral || enemyState == EnemyAra::State::wait) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //�ʏ�A�ҋ@��Ԃ̓G�ɂ̂݃C�W�P��Ԃ�t�^����
		//	if (enemyState == EnemyAra::State::cringe) {
		//		ChangeSound();
		//		return;
		//	}
		//}
		StopSoundMem(cringeSE);
		flg = false;

		spurtSound();
	}
}

void Sound::spurtSound()
{
	if (isUpdate)
	{
		foodcount = WorldVal::Get<int>("foodCountTotal");

		if (*foodcount >= 116 && *foodcount <= 179)//116
		{
			if (count2 == 0 && !flg)
			{
				StopSoundMem(enemyMoveSE);
				count2 = 1;
			}
			if (count2 == 1)
			{
				PlaySoundMem(squrtSE1, DX_PLAYTYPE_LOOP);
				count2 = 2;
			}
		}
		else if (*foodcount >= 180 && *foodcount <= 211)//180
		{
			if (count3 == 0 && !flg)
			{
				StopSoundMem(squrtSE1);
				count3 = 1;
			}
			if (count3 == 1)
			{
				PlaySoundMem(squrtSE2, DX_PLAYTYPE_LOOP);
				count3 = 2;
			}
		}
		else if (*foodcount >= 212 && *foodcount <= 227)//212
		{
			if (count4 == 0 && !flg)
			{
				StopSoundMem(squrtSE2);
				count4 = 1;
			}
			if (count4 == 1)
			{
				PlaySoundMem(squrtSE3, DX_PLAYTYPE_LOOP);
				count4 = 2;
			}
		}
		else if (*foodcount >= 228 && *foodcount <= 243)//228
		{
			if (count5 == 0 && !flg)
			{
				StopSoundMem(squrtSE3);
				count5 = 1;
			}
			if (count5 == 1)
			{
				PlaySoundMem(squrtSE3, DX_PLAYTYPE_LOOP);
				count5 = 2;
			}
		}
	}
}

//�G����������ԂɂȂ�����ʏ펞�̉����~����
//�G�������ԂɂȂ����炢������Ԏ��̉����~����
void Sound::ChangeSound() {
	if (flg == false) {
		PlaySoundMem(cringeSE, DX_PLAYTYPE_LOOP);
		flg = true;
	}

	StopSound();

	count1 = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	count5 = 0;
}

void Sound::ChangeSound2() {
	if (flg2 == false && !PowerModeProcess::GetIsPause()) {
		PlaySoundMem(damageSE, DX_PLAYTYPE_LOOP);
		StopSoundMem(cringeSE);
		flg2 = true;
		flg = false;
	}

	StopSound();

	count1 = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	count5 = 0;
}


void Sound::StopSound() {
	StopSoundMem(enemyMoveSE);
	StopSoundMem(squrtSE1);
	StopSoundMem(squrtSE2);
	StopSoundMem(squrtSE3);
	StopSoundMem(squrtSE4);
}

void Sound::SoundSe() {
	StopSoundMem(cringeSE);
	StopSoundMem(damageSE);
	PlaySoundMem(damageSE, DX_PLAYTYPE_LOOP);
}