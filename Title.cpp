#include "DxLib.h"
#include "Title.h"
#include "SceneManager.h"
#include "GetKey.h"
#include "Game.h"

Title::Title() {
	pos_x = 0;
	pos_y = 720;
	titleImage = LoadGraph("Resource/image/Title.png");
	push = false;
}

Title::~Title() {
	DeleteGraph(titleImage);
}

void Title::Update() {
	if (push == true && key->GetKeyState(A_KEY) == KEY_PUSH) { //A�{�^��(�΃{�^��)�������ꂽ�u��
		SetNext(new Game()); //�Q�[���V�[���֑J��
	}
}

void Title::Draw() {
	Move();
	DrawGraph(pos_x, pos_y, titleImage, FALSE);
	SetFontSize(35);
	DrawString(530, pos_y + 380, "Push A Start!", GetColor(210, 210, 210));
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
