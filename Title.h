#pragma once
#include "Scene.h"
#define SCROLL_SPEED 8	//画面スクロールのスピード

class Title : public Scene {
public:
	Title();
	~Title();
	void Update();
	void Draw();
private:
	//座標変数
	int pos_x;
	int pos_y;
	//タイトル画像格納用変数
	int titleImage;
	//ボタンが押せるかどうか
	bool push;
	//画像スクロール用関数
	void Move();
};
