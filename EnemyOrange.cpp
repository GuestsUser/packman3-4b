#include "DxLib.h"
#include "EnemyOrange.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include <math.h>

EnemyOrange::EnemyOrange(Player* getPlayer) :player(getPlayer) {	//����������
	SetUp(EnemyAra::Type::orange, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1));
}

void EnemyOrange::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[�������

	int centerX = player->ClculatTileX(angle) * TILE;
	int centerY = player->ClculatTileY(angle) * TILE;
	int orangeX = ClculatTileX() * TILE;
	int orangeY = ClculatTileY() * TILE;
	int radius = 65;


	if (sqrt(pow((centerX - orangeX),2) + pow((centerY - orangeY),2)) <= radius) {
		TargetSet(WARP_AREA_X + 1, WARP_AREA_Y + 31);
	}
	else {
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
	}
}

void EnemyOrange::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 1, WARP_AREA_Y + 31); }	 //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyOrange::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��