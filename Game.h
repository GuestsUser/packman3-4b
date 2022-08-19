#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Player.h"
#include "EnemyAra.h"

//ゲームシーン、現在は空、動作確認をしたい時こちらのUpdate等に追記していってほしい
//Updateの定義はcppにある(現在は空)
class Game :public Scene {
	GameMap map;
	Player player;
	EnemyAra akabei;
public:
	Game() :map(GameMap(this)), player() {}
	void Update();
	void Draw();
};