#include "Game.h"
Game::State Game::state = Game::State::start; //static•Ï”‚Ì’è‹`

void Game::Update() {
	map.Update();
	player.Update();
}

void Game::Draw() {
	map.Draw();
	player.Draw();
}