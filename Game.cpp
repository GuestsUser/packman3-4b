#include "Game.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include <deque>
Game::State Game::state = Game::State::start; //static変数の定義

Game::Game() :player(), map(GameMap(this, &player)),enemy(std::deque<EnemyAra*>()) {
	state = State::start; //初期化時毎回startを代入する
	enemy.push_back(new EnemyRed(&player)); //赤の敵を追加する

}

void Game::Update() {
	map.Update();
	player.Update();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
}

void Game::Draw() {
	map.Draw();
	player.Draw();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
}