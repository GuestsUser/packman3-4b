#pragma once
#include "EnemyAra.h"

class Player;

class EnemyPink :public EnemyAra
{
private:
	Player* player;
public:
	EnemyPink(Player* getPlayer);
	void SetAttackModeTarget(); //追いかけモード中の狙いマス決定関数、オーバーライドして使う
	void SetStandbyModeTarget(); //上記の縄張りモード版
	void SetWaitModeTarget(); //巣の中の待機位置決定関数
};

