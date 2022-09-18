#pragma once
#include "PowerModeProcess.h"
#include "Player.h"
#include "EnemyAra.h"
#include <deque>

class Sound 
{
public:
	Sound(PowerModeProcess* set, Player* pacman, std::deque<EnemyAra*>* getEnemy);

	PowerModeProcess* powerMode;
	Player* player;
	std::deque<EnemyAra*>* enemy;

	int count1;
	int count2;
	int count3;
	int count4;
	int count5;

	int enemyMoveSE;
	int squrtSE1;
	int squrtSE2;
	int squrtSE3;
	int squrtSE4;

	int cringeSE;
	int damageSE;
	bool flg;

	int* foodcount;

	bool isUpdate;

	void Update();
	void spurtSound();
	void ChangeSound();	//
	void StopSound();	//�G�̃X�p�[�g�����~�߂鎞�����o�����߂̊֐�
	void SoundSe();		//�G����������Ԃ�������ԂɂȂ����������o�����߂̊֐�

	void SetSEUpdate(bool set) { isUpdate = set; }
	bool GetSEUpdate() { return isUpdate; }

private:
};