#pragma once
#include "EnemyAra.h"

class Player;


class Enemyblue : public EnemyAra {
private:
	Player* player;
	//EnemyRed* enemyred;
public:
	Enemyblue(Player* getPlayer); //追いかけ作成のためにシーンなどから値を引っ張ってくる必要がある場合コンストラクタの引数に自由に変数を追加していい、自由に追加する為の継承でもある

	void SetAttackModeTarget(); //追いかけモード中の狙いマス決定関数、オーバーライドして使う
	void SetStandbyModeTarget(); //上記の縄張りモード版
	void SetWaitModeTarget(); //巣の中の待機位置決定関数
};