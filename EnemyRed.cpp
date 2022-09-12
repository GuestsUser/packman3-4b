#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"

EnemyRed::EnemyRed(Player* getPlayer, std::deque<EnemyAra*>* getList):player(getPlayer), enemyList(getList) {
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + 3); //�����������A�ڂ�����EnemyAra���Q��
}

void EnemyRed::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[����p
	TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
}
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 24, WARP_AREA_Y - 4); } //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��

void EnemyRed::Spurt() {

}