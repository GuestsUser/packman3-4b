#include "GlovalLoading.h"
#include "Worldval.h"

void GlovalLoading() { //�F�X�ȑS�̌����ϐ��̏���
	WorldVal::Set("foodCountTotal", new int(0)); //���̃V�[���ł̐H�ׂ��G�T��
	WorldVal::Set("fruitsDisplay", new int(0)); //���̃V�[���ł̕\����������
	WorldVal::Set("Life", new int(3)); //���̃V�[���ł̐H�ׂ��G�T��
	WorldVal::Set("start", new int(0)); //���̃V�[���ł̐H�ׂ��G�T��
	WorldVal::Set("nowStage", new int(0)); //���݂̃X�e�[�W���A0�X�^�[�g
	WorldVal::Set("dieCount", new int(0)); //���̃X�e�[�W�ł��ꂽ��
	WorldVal::Set("activeFoodCount", new int(0)); //���̃��C�t�ŃG�T��H�ׂ�����
	WorldVal::Set("enemyActive", new int(0)); //Game.cpp�Ŏg�p���Ă���G�̎�ޔ���p

}