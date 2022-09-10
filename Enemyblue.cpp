#include "Enemyblue.h"
#include "EnemyAra.h"
#include "Grid.h"
#include "ConstVal.h"
#include "Player.h"
#include "Grid.h"
#include "EnemyRed.h"

Enemyblue::Enemyblue(Player* getPlayer,EnemyAra* getEnemyRed) :player(getPlayer),enemyred(getEnemyRed) {
	SetUp(EnemyAra::Type::blue, Direction::left, 13 * TILE + (TILE - 1), 11 * TILE + (TILE - 1)); //�����������A�ڂ�����EnemyAra���Q��
}

void Enemyblue::SetAttackModeTarget() {  //�ǂ��������[�h�̎��^�[�Q�b�g�w��
	Direction angle = player->GetDirection(); //�v���C���[����p

	int x = abs(player->ClculatTileX(angle) - enemyred->ClculatTileX());
	int y = abs(player->ClculatTileY(angle) - enemyred->ClculatTileY());

	if (player->ClculatTileX(angle) >= enemyred->ClculatTileX()) {//�p�b�N�}�����G���X���W���傫����
		if (player->ClculatTileY(angle) >= enemyred->ClculatTileY()) {//�p�b�N�}�����G���Y���W���傫����
			TargetSet(player->ClculatTileX(angle) + x, player->ClculatTileY(angle) + y); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
		}
		else {
			TargetSet(player->ClculatTileX(angle) + x, player->ClculatTileY(angle) - y);
		}
	}
	if (player->ClculatTileX(angle) <= enemyred->ClculatTileX()) {//�p�b�N�}�����G���x���W����������
		if (player->ClculatTileY(angle) >= enemyred->ClculatTileY()) {//�p�b�N�}�����G���y���W���傫����
			TargetSet(player->ClculatTileX(angle) - x, player->ClculatTileY(angle) + y); //�ڕW�}�X�Ƀv���C���[�ʒu���w��
		}
		else {
			TargetSet(player->ClculatTileX(angle) - x, player->ClculatTileY(angle) - y);
		}
	}
}
void Enemyblue::SetStandbyModeTarget() { TargetSet(WARP_AREA_X + 26, WARP_AREA_Y+31); } //�꒣�胂�[�h���̃^�[�Q�b�g�w��
void Enemyblue::SetWaitModeTarget() { TargetSet(WARP_AREA_X + 13, WARP_AREA_Y + 11); } //���̒��̈ʒu�w��