#include "Game.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include "EnemyPink.h"
#include "EnemyOrange.h"
#include "Enemyblue.h"
#include <deque>

Game::State Game::state = Game::State::start; //static変数の定義

Game::Game() :player(), map(GameMap(this, &player)),enemy(std::deque<EnemyAra*>()) {
	state = State::start; //初期化時毎回startを代入する
	enemy.push_back(new EnemyRed(&player)); //赤の敵を追加する
	enemy.push_back(new EnemyPink(&player));
	enemy.push_back(new EnemyOrange(&player));
	enemy.push_back(new Enemyblue(&player,enemy[0]));

	count = 0;
}

void Game::Update() {
	map.Update();
	ui.UiUpdate();
	if (count >= 240) {
		player.Update();
		for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	}
	count++;
}

void Game::Draw() {
	map.Draw();
	ui.UiDraw();
	if (count >= 120) {
		player.Draw();
		for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
	}
}