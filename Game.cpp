#include "Game.h"
Game::State Game::state = Game::State::start; //static•Ï”‚Ì’è‹`

void Game::Update() {
	map.Update();
	player.Update();
	//gameui.UiUpdate();
}

void Game::Draw() {
	gameui.UiDraw();
	map.Draw();
	player.Draw();
}