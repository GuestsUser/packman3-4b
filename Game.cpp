#include "Game.h"
Game::State Game::state = Game::State::start; //static変数の定義

void Game::Update() {
	map.Update();
	player.Update();
}

void Game::Draw() {
	map.Draw();
	player.Draw();
	akabei.enemyUpdate();
}