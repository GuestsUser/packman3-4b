#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Player.h"

//ゲームシーン、現在は空、動作確認をしたい時こちらのUpdate等に追記していってほしい
//Updateの定義はcppにある(現在は空)
class Game :public Scene {
public:
	enum class State { start, run, miss, gameover, clear }; //ゲーム状況を表す列挙型
private:
	GameMap map;
	Player player;
	State state;
public:
	Game() :map(GameMap(this)), player(), state(State::start) {}
	void Update();
	void Draw();

	State GetSceneState() const { return state; } //現在のゲーム状況の取得
	void SetSceneState(State set) { state = set; } //ゲーム状況の書き換え
};