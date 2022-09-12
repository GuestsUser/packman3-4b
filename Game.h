#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Ui.h"
#include "Player.h"
#include "EnemyAra.h"
#include <deque>

//ゲームシーン、現在は空、動作確認をしたい時こちらのUpdate等に追記していってほしい
//Updateの定義はcppにある(現在は空)

class Game :public Scene {
public:
	enum class State { start, run, miss, gameover, clear }; //ゲーム状況を表す列挙型、start=ゲーム開始前, run=ゲーム中, miss=プレイヤーミス時, gameover=残機が無い時ミス演出後これにする, clear=全てのエサを食べた時
private:
	GameMap map;
	Player player;
	GameUi ui;
	std::deque<EnemyAra*> enemy;
	static State state; //Foodに次レベルに移行する度Gameの内容を入れ替えたくなかったのでstatic変数にしてヘッダーさえインクルードしておけばいつでもアクセスできる
	int count;
	int number;
	int StartTime;
	bool push;
public:
	Game();
	void Update();
	void Draw();

	Player* EditPlayer() { return &player; }
	std::deque<EnemyAra*>* EditEnemy() { return &enemy; }

	static State GetSceneState() { return state; } //現在のゲーム状況の取得
	static void SetSceneState(State set) { state = set; } //ゲーム状況の書き換え
};