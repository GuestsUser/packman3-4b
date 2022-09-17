#pragma once
#include "PowerModeProcess.h"
#include "Player.h"
#include "EnemyAra.h"

class Sound
{
public:
	Sound();

	PowerModeProcess powerMode; //パワーエサ取得時処理とかやるやつ
	Player player;
	std::deque<EnemyAra*> enemy;

	int count1;
	int count2;
	int count3;
	int count4;
	int count5;

	int enemyMoveSE;
	int spurtSE1;
	int spurtSE2;
	int spurtSE3;
	int spurtSE4;

	int* foodcount;

	bool isUpdate;

	void Update();
	void spurtSound();

	void SetSEUpdate(bool set) { isUpdate = set; }
	bool GetSEUpdate() { return isUpdate; }

private:
};