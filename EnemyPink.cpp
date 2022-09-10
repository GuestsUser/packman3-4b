#include "EnemyPink.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"

EnemyPink::EnemyPink(Player* getPlayer) :player(getPlayer) {
	SetUp(EnemyAra::Type::pink, Direction::down, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //初期化処理、詳しくはEnemyAraを参照
}

void EnemyPink::SetAttackModeTarget() {  //追いかけモードの時ターゲット指定
	Direction angle = player->GetDirection(); //プレイヤー動作角

	if (angle == Direction::up)
	{
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle) - 3); //目標マスにプレイヤー位置を指定
	}
	if (angle == Direction::left)
	{
		TargetSet(player->ClculatTileX(angle) - 3, player->ClculatTileY(angle)); //目標マスにプレイヤー位置を指定
	}
	if (angle == Direction::down)
	{
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle) + 3); //目標マスにプレイヤー位置を指定
	}
	if (angle == Direction::right)
	{
		TargetSet(player->ClculatTileX(angle) + 3, player->ClculatTileY(angle)); //目標マスにプレイヤー位置を指定
	}

}
void EnemyPink::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 3, WARP_AREA_Y - 4); } //縄張りモード時のターゲット指定
void EnemyPink::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //巣の中の位置指定