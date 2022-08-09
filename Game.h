#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"

//ゲームシーン、現在は空、動作確認をしたい時こちらのUpdate等に追記していってほしい
//Updateの定義はcppにある(現在は空)
class Game :public Scene {
public:
	void Update();
	void Draw();
};