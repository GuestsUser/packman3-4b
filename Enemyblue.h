#pragma once
#include "EnemyAra.h"

class Player;

class Enemyblue : public EnemyAra {
private:
	Player* player;
	EnemyAra* enemyred;
public:
	Enemyblue(Player* getPlayer,EnemyAra* getEnemyred); //�ǂ������쐬�̂��߂ɃV�[���Ȃǂ���l�����������Ă���K�v������ꍇ�R���X�g���N�^�̈����Ɏ��R�ɕϐ���ǉ����Ă����A���R�ɒǉ�����ׂ̌p���ł�����

	void SetAttackModeTarget(); //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
	void SetStandbyModeTarget(); //��L�̓꒣�胂�[�h��
	void SetWaitModeTarget(); //���̒��̑ҋ@�ʒu����֐�
};