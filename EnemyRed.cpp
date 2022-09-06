#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"

EnemyRed::EnemyRed() {
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //�����������A�ڂ�����EnemyAra���Q��
}

void EnemyRed::SetAttackModeTarget() { TargetSet(WARP_AREA_X + 26, WARP_AREA_Y + 30); } //�ǂ��������[�h�̎��^�[�Q�b�g�w��A����͉��̕�
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 1, WARP_AREA_Y); } //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��