#include "Game.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include <deque>
Game::State Game::state = Game::State::start; //static•Ï”‚Ì’è‹`

Game::Game() :player(), map(GameMap(this, &player)),enemy(std::deque<EnemyAra*>()) {
	state = State::start; //‰Šú‰»–ˆ‰ñstart‚ğ‘ã“ü‚·‚é
	enemy.push_back(new EnemyRed(&player)); //Ô‚Ì“G‚ğ’Ç‰Á‚·‚é

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