#pragma once
#include "EnemyAra.h"

class Player;

class EnemyPink :public EnemyAra
{
private:
	Player* player;
public:
	EnemyPink(Player* getPlayer);
	void SetAttackModeTarget(); //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
	void SetStandbyModeTarget(); //��L�̓꒣�胂�[�h��
	void SetWaitModeTarget(); //���̒��̑ҋ@�ʒu����֐�
};

