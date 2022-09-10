#include "EnemyPink.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"

EnemyPink::EnemyPink(Player* getPlayer) :player(getPlayer) {
	SetUp(EnemyAra::Type::pink, Direction::down, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //�����������A�ڂ�����EnemyAra���Q��
}

void EnemyPink::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[����p

	if (angle == Direction::up)
	{
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle) - 3); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
	}
	if (angle == Direction::left)
	{
		TargetSet(player->ClculatTileX(angle) - 3, player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
	}
	if (angle == Direction::down)
	{
		TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle) + 3); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
	}
	if (angle == Direction::right)
	{
		TargetSet(player->ClculatTileX(angle) + 3, player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
	}

}
void EnemyPink::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 3, WARP_AREA_Y - 4); } //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyPink::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��