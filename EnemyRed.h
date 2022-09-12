#pragma once
#include "EnemyAra.h"
#include <deque>
class Player;

class EnemyRed : public EnemyAra {
private:
	Player* player;
	std::deque<EnemyAra*>* enemyList; //�Q�[���V�[���������Ă���G���X�g

	int foodMax; //�G�T�ő吔
	int* foodCountTotal; //�G�T��H�ׂ����v��
public:
	EnemyRed(Player* getPlayer, std::deque<EnemyAra*>* getList); //�ǂ������쐬�̂��߂ɃV�[���Ȃǂ���l�����������Ă���K�v������ꍇ�R���X�g���N�^�̈����Ɏ��R�ɕϐ���ǉ����Ă����A���R�ɒǉ�����ׂ̌p���ł�����

	void SetAttackModeTarget(); //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
	void SetStandbyModeTarget(); //��L�̓꒣�胂�[�h��
	void SetWaitModeTarget(); //���̒��̑ҋ@�ʒu����֐�

	int Spurt();
};