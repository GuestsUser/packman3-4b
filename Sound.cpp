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

		if (powerMode->GetState() == PowerModeProcess::State::run) { ChangeSound(); return; } //パワーエサ有効中なら曲を変える

		//for (int i = 0; i < enemy->size(); ++i) {
		//	EnemyAra::State enemyState = (*enemy)[i]->GetState();
		//	//if (enemyState == EnemyAra::State::neutral || enemyState == EnemyAra::State::wait) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //通常、待機状態の敵にのみイジケ状態を付与する
		//	if (enemyState == EnemyAra::State::cringe) {
		//		ChangeSound();
		//		return;
		//	}
		//}
		StopSoundMem(cringeSE);
		flg = false;
	}
}

void Sound::spurtSound()
{
	if (isUpdate)
	{
		foodcount = WorldVal::Get<int>("foodCountTotal");

		if (*foodcount >= 116 && *foodcount <= 179)//116
		{
			if (count2 == 0)
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
			if (count3 == 0)
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
			if (count4 == 0)
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
			if (count5 == 0)
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
		else if (*foodcount == 244) {
			StopSoundMem(squrtSE3);
		}
	}
}

//敵がいじけ状態になったら通常時の音を停止する
//敵がやられ状態になったらいじけ状態時の音を停止する
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

void Sound::StopSound() {
	StopSoundMem(enemyMoveSE);
	StopSoundMem(squrtSE1);
	StopSoundMem(squrtSE2);
	StopSoundMem(squrtSE3);
	StopSoundMem(squrtSE4);
}