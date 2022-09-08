#pragma once
#include "Grid.h"
#include <unordered_map>
#include <string>

class Food;

class Player {
	class Moving; //����p�����N���X

	int* playerImg; //�p�b�N�}���摜�n���h��
	int* killImg; //���S���[�V����
	int* score; //�X�R�A�̎Q��
	int* highScore; //�n�C�X�R�A�̎Q��

	bool isUpdate; //false��update���s�֎~
	bool isDraw; //��L��draw��
	int posX, posY; //�`�ʗp���W�A�`�ʗp���W�̓O���b�h�Y��������o�������W�Ƒ��x�ɂ���ē������h�b�g���������`�ʂɕK�v�Ȋe����H���s���΂��̈ʒu�ɕ\�����\�ȍ��W�����Ă���
	Moving* move; //����N���X����
	int rad; //�e������ɂ�蒆�S���W�𓮂����ׂɉ����Z���锼�a�̒l
	int center; //xy���ʂ̒��S���W
	int renderCenter; //xy���ʒ��S����������͕`�ʗp

	int foodCount; //����̎c�@�ŐH�ׂ��G�T��
	int foodCountTotal; //�G�T��H�ׂ����v��
	std::unordered_map<std::string, Food*>* food; //�G�T��t���[�c�̔z��
	Grid** tile;

	int actIndex = 0;			
	int maxMotion = 4;			//�A�j���[�V�����̐��i4�i�K�j
	int motionIndex;			//
	const int actSpeed = 2;		//�A�j���[�V�����̑����ݒ�
	int actWait;				//�A�j���[�V�����̑҂�����

	int animX;
	int animY;
	int diecount;
	int killnum;

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

	int GetPosX() const { return posX; }
	int GetPosY() const { return posY; }
	int GetCenter() const { return center; }
	int ClculatCenterRadX(Direction angle)const; //�e������ɂ����钆�Sx���W��Ԃ��Ă����
	int ClculatCenterRadY(Direction angle)const; //��L��y��
	int ClculatLocalX(Direction angle)const; //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
	int ClculatLocalY(Direction angle)const; //��L��y��
	int ClculatTileX(Direction angle)const; //���݃}�X��Ԃ��Ă����
	int ClculatTileY(Direction angle)const; //��L��y��
	Direction GetDirection()const; //���݈ړ�������Ԃ�

	Move GetTileMovable(int x, int y, Direction get) const { return tile[x][y].ReadPlayer()[(int)get]; } //�w��^�C���̎w������̈ړ��ۂ�Ԃ�
	void DieAnim();
};