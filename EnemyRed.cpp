#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"

EnemyRed::EnemyRed() {
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //初期化処理、詳しくはEnemyAraを参照
}

void EnemyRed::SetAttackModeTarget() { TargetSet(WARP_AREA_X + 26, WARP_AREA_Y + 30); } //追いかけモードの時ターゲット指定、動作は仮の物
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 1, WARP_AREA_Y); } //縄張りモード時のターゲット指定
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //巣の中の位置指定