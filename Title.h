#pragma once
#include "Scene.h"
#define SCROLL_SPEED 8	//��ʃX�N���[���̃X�s�[�h

class Title : public Scene {
public:
	Title();
	~Title();
	void Update();
	void Draw();
private:
	//���W�ϐ�
	int pos_x;
	int pos_y;
	//�^�C�g���摜�i�[�p�ϐ�
	int titleImage;
	//�{�^���������邩�ǂ���
	bool push;
	//�摜�X�N���[���p�֐�
	void Move();
};
