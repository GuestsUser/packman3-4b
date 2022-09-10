#include "Enemyblue.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"
#include "EnemyRed.h"

Enemyblue::Enemyblue(Player* getPlayer,EnemyAra* getEnemyRed) :player(getPlayer),enemyred(getEnemyRed) {
	SetUp(EnemyAra::Type::blue, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //初期化処理、詳しくはEnemyAraを参照
}

void Enemyblue::SetAttackModeTarget() {  //追いかけモードの時ターゲット指定
	Direction angle = player->GetDirection(); //プレイヤー動作角

	int x = abs(player->ClculatTileX(angle) - enemyred->ClculatTileX());
	int y = abs(player->ClculatTileY(angle) - enemyred->ClculatTileY());

	if (player->ClculatTileX(angle) >= enemyred->ClculatTileX()) {//パックマンが敵よりX座標が大きい時
		if (player->ClculatTileY(angle) >= enemyred->ClculatTileY()) {//パックマンが敵よりY座標が大きい時
			TargetSet(player->ClculatTileX(angle) + x, player->ClculatTileY(angle) + y); //目標マスにプレイヤー位置を指定
		}
		else {
			TargetSet(player->ClculatTileX(angle) + x, player->ClculatTileY(angle) - y);
		}
	}
	if (player->ClculatTileX(angle) <= enemyred->ClculatTileX()) {//パックマンが敵よりx座標が小さい時
		if (player->ClculatTileY(angle) >= enemyred->ClculatTileY()) {//パックマンが敵よりy座標が大きい時
			TargetSet(player->ClculatTileX(angle) - x, player->ClculatTileY(angle) + y); //目標マスにプレイヤー位置を指定
		}
		else {
			TargetSet(player->ClculatTileX(angle) - x, player->ClculatTileY(angle) - y);
		}
	}
}
void Enemyblue::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 26, WARP_AREA_Y+31); } //縄張りモード時のターゲット指定
void Enemyblue::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //巣の中の位置指定