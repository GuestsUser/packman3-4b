#include "DxLib.h"
#include "EnemyOrange.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include <math.h>

EnemyOrange::EnemyOrange(Player* getPlayer) :player(getPlayer) {	//初期化処理
	SetUp(EnemyAra::Type::orange, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1));
}

void EnemyOrange::SetAttackModeTarget() {  //追いかけモードの時ターゲット指定
	Direction angle = player->GetDirection(); //プレイヤー動作方向

	int centerX = player->ClculatTileX(angle) * TILE;
	int centerY = player->ClculatTileY(angle) * TILE;
	int orangeX = ClculatTileX() * TILE;
	int orangeY = ClculatTileY() * TILE;
	int radius = 65;


	if (sqrt(pow((centerX - orangeX),2) + pow((centerY - orangeY),2)) <= radius) {
		TargetSet(WARP_AREA_X + 1, WARP_AREA_Y + 31);
	}
	else {
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //目標マスにプレイヤー位置を指定
	}
}

void EnemyOrange::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 1, WARP_AREA_Y + 31); }	 //縄張りモード時のターゲット指定
void EnemyOrange::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //巣の中の位置指定