#include "Game.h"
Game::State Game::state = Game::State::start; //static�ϐ��̒�`

void Game::Update() {
	map.Update();
	player.Update();
}

void Game::Draw() {
	map.Draw();
	player.Draw();
}