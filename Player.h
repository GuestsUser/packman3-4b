#pragma once
#include "Grid.h"
#include <unordered_map>
#include <string>

class Food;

class Player {
	class Moving; //����p�����N���X

	int* playerImg; //�p�b�N�}���摜�n���h��
	int* killImg; //���S���[�V����
	bool isUpdate; //false��update���s�֎~
	bool isDraw; //��L��draw��
	int subX, subY, drawX, drawY; //�O���b�h�̓Y�����ƕ`�ʗp���W�A�`�ʗp���W�̓O���b�h�Y��������o�������W�Ƒ��x�ɂ���ē������h�b�g���������`�ʂɕK�v�Ȋe����H���s���΂��̈ʒu�ɕ\�����\�ȍ��W�����Ă���
	int speed; //���x�A���݂͏�Ԃɂ�炸���ȉ��̕�
	int speedCount; //���x�̒~�Ϗ󋵋L�^�A���t���[�������speed�����Z���AspeedCount/MOVABLE_SPEED�̒l���`�ʍ��W�𓮂���
	Direction nowDirection; //���݂̐i�s����
	Direction lastInput; //�Ō�̓��͕����ێ�
	Moving* xMove; //����N���X���́Ax�p
	Moving* yMove; //y�p

	int foodCount; //����̎c�@�ŐH�ׂ��G�T��
	int foodCountTotal; //�G�T��H�ׂ����v��
	std::unordered_map<std::string, Food*>* food; //�G�T��t���[�c�̔z��
	Grid** tile;

	//�����ʒu x14+4(���[�v�g���l����) y23

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }
};