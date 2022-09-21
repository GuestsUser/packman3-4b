#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"
#include "Worldval.h"
#include <deque>

EnemyRed::EnemyRed(Player* getPlayer, std::deque<EnemyAra*>* getList):player(getPlayer), enemyList(getList), foodCountTotal(WorldVal::Get<int>("foodCountTotal")), foodMax(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")->size() - 1) { //最大数の-1はフルーツターゲットの分
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 3), 11 * TILE ); //初期化処理、詳しくはEnemyAraを参照
}

void EnemyRed::SetAttackModeTarget() {  //追いかけモードの時ターゲット指定
	Direction angle = player->GetDirection(); //プレイヤー動作角
	TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //目標マスにプレイヤー位置を指定
}
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 25, WARP_AREA_Y - 4); } //縄張りモード時のターゲット指定
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 14); } //巣の中の位置指定

int EnemyRed::Spurt() {
	for (int i = 0; i < enemyList->size(); ++i) {
		EnemyAra::State state = (*enemyList)[i]->GetState();
		if (state == EnemyAra::State::cringe || state == EnemyAra::State::damage) { return -1; } //cringe、damageの敵がいる場合スパートは利用しない
	}
	int residue = foodMax - (*foodCountTotal); //エサの残り個数

	if (residue <= 10) { return 17; }
	if (residue <= 20) { return 16; }
	return -1; //何れかの条件にも引っかからなかった場合使わない
}