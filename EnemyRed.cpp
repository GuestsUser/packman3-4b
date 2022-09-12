#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"

EnemyRed::EnemyRed(Player* getPlayer, std::deque<EnemyAra*>* getList):player(getPlayer), enemyList(getList) {
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + 3); //初期化処理、詳しくはEnemyAraを参照
}

void EnemyRed::SetAttackModeTarget() {  //追いかけモードの時ターゲット指定
	Direction angle = player->GetDirection(); //プレイヤー動作角
	TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //目標マスにプレイヤー位置を指定
}
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 24, WARP_AREA_Y - 4); } //縄張りモード時のターゲット指定
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //巣の中の位置指定

void EnemyRed::Spurt() {

}