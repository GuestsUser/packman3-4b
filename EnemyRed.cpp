#include "EnemyRed.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"
#include "Worldval.h"
#include <deque>

EnemyRed::EnemyRed(Player* getPlayer, std::deque<EnemyAra*>* getList):player(getPlayer), enemyList(getList), foodCountTotal(WorldVal::Get<int>("foodCountTotal")), foodMax(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")->size() - 1) { //�ő吔��-1�̓t���[�c�^�[�Q�b�g�̕�
	SetUp(EnemyAra::Type::red, Direction::left, 13 * TILE + (TILE - 3), 11 * TILE ); //�����������A�ڂ�����EnemyAra���Q��
}

void EnemyRed::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[����p
	TargetSet(player->ClculatTileX(angle), player->ClculatTileY(angle)); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
}
void EnemyRed::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 25, WARP_AREA_Y - 4); } //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void EnemyRed::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 14); } //���̒��̈ʒu�w��

int EnemyRed::Spurt() {
	for (int i = 0; i < enemyList->size(); ++i) {
		EnemyAra::State state = (*enemyList)[i]->GetState();
		if (state == EnemyAra::State::cringe || state == EnemyAra::State::damage) { return -1; } //cringe�Adamage�̓G������ꍇ�X�p�[�g�͗��p���Ȃ�
	}
	int residue = foodMax - (*foodCountTotal); //�G�T�̎c���

	if (residue <= 10) { return 17; }
	if (residue <= 20) { return 16; }
	return -1; //���ꂩ�̏����ɂ�����������Ȃ������ꍇ�g��Ȃ�
}