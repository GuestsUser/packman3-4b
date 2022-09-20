#include "DxLib.h"
#include "Title.h"
#include "SceneManager.h"
#include "GetKey.h"
#include "Game.h"
#include "CoffeeBreak.h"
#include "Worldval.h"

Title::Title() {
	pos_x = 0;
	pos_y = 720;
	titleImage = LoadGraph("Resource/image/Title.png");
	push = false;
	round = WorldVal::Get<int>("nowStage");
}

Title::~Title() {
	DeleteGraph(titleImage);
}

void Title::Update() {
	score = WorldVal::Get<int>("score");
	hiscore = WorldVal::Get<int>("highScore");
	if (push == true && key->GetKeyState(A_KEY) == KEY_PUSH) { //A�{�^��(�΃{�^��)�������ꂽ�u��

		*WorldVal::Get<int>("score") = 0; //�X�R�A���Z�b�g
		SetNext(new Game()); //�Q�[���V�[���֑J��
		//*score = 0;
	}
	if (push == true && key->GetKeyState(Y_KEY) == KEY_PUSH) { //Y�{�^��(���F�{�^��)�������ꂽ�u��
		SetNext(new CoffeeBreak()); //�Q�[���V�[���֑J��
	}
	if (push == true && key->GetKeyState(X_KEY) == KEY_PUSH) { //X�{�^��(���F�{�^��)�������ꂽ�u�� �X�e�[�W���𑝂₷(�R�[�q�[�u���C�N�m�F�p�j
		*WorldVal::Get<int>("nowStage") += 1; //���X�e�[�W�ɃJ�E���g��i�߂�
		roundcount++;
	}
}

void Title::Draw() {
	Move();
	DrawGraph(pos_x, pos_y, titleImage, FALSE);
	SetFontSize(35);
	//DrawString(530, pos_y + 380, "Push A Start!", GetColor(210, 210, 210));
	DrawFormatString(350+pos_x, 100+pos_y, GetColor(255, 255, 255), "%7d", *score);
	DrawFormatString(700+pos_x, 100+pos_y, GetColor(255, 255, 255), "%7d", *hiscore);
	DrawFormatString(0 + pos_x, 0 + pos_y, GetColor(255, 255, 255), "%7d", roundcount);//roundcount��2,5,9,13,17�̎��R�[�q�[�u���C�N�������
}

void Title::Move() {
	if (pos_y == 0) {
		pos_y = 0;
		push = true;
	}
	else {
		pos_y -= SCROLL_SPEED;
	}
}
