#include "Game.h"
Game::State Game::state = Game::State::start; //static変数の定義

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