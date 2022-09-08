#include "EnemyOrange.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"

EnemyOrange::EnemyOrange(Player* getPlayer) :player(getPlayer) {	//����������
	SetUp(EnemyAra::Type::orange, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1));
}

void EnemyOrange::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[�������
	TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
}

void EnemyOrange::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 1, WARP_AREA_Y); }	 //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyOrange::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��