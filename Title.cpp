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
	if (push == true && key->GetKeyState(A_KEY) == KEY_PUSH) { //Aボタン(緑ボタン)が押された瞬間

		*WorldVal::Get<int>("score") = 0; //スコアリセット
		SetNext(new Game()); //ゲームシーンへ遷移
		//*score = 0;
	}
	if (push == true && key->GetKeyState(Y_KEY) == KEY_PUSH) { //Yボタン(黄色ボタン)が押された瞬間
		SetNext(new CoffeeBreak()); //ゲームシーンへ遷移
	}
	if (push == true && key->GetKeyState(X_KEY) == KEY_PUSH) { //Xボタン(黄色ボタン)が押された瞬間 ステージ数を増やす(コーヒーブレイク確認用）
		*WorldVal::Get<int>("nowStage") += 1; //次ステージにカウントを進める
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
	DrawFormatString(0 + pos_x, 0 + pos_y, GetColor(255, 255, 255), "%7d", roundcount);//roundcountが2,5,9,13,17の時コーヒーブレイクが流れる
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
