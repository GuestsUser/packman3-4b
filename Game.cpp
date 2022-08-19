#include "Game.h"

void Game::Update() {
	map.Update();
	player.Update();
}

void Game::Draw() {
	map.Draw();
	player.Draw();
	akabei.enemyUpdate();
}