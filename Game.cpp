#include "Game.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include "EnemyPink.h"
#include "EnemyOrange.h"
#include "Enemyblue.h"
#include <deque>
#include "GameMap.h"
Game::State Game::state = Game::State::start; //static•Ï”‚Ì’è‹`

Game::Game() :player(), map(GameMap(this, &player)),enemy(std::deque<EnemyAra*>()) {
	state = State::start; //‰Šú‰»–ˆ‰ñstart‚ğ‘ã“ü‚·‚é
	enemy.push_back(new EnemyRed(&player)); //Ô‚Ì“G‚ğ’Ç‰Á‚·‚é
	enemy.push_back(new EnemyPink(&player));
	enemy.push_back(new EnemyOrange(&player));
	enemy.push_back(new Enemyblue(&player,enemy[0]));

	push = false;
	count = 0;
	number = 0;
}

void Game::Update() {
	map.Update();
	player.Update();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	count++;
	if (key->GetKeyState(X_KEY) == KEY_PUSH) {	/*XƒL[‚ğ‰Ÿ‚µ‚½‚ç*/
		enemy[0]->SetRunUpdate(false);	/*“G‚Ì“®‚«‚ğ~‚ß‚éi‰¼j*/
		enemy[1]->SetRunUpdate(false);	/*“G‚Ì“®‚«‚ğ~‚ß‚éi‰¼j*/
		enemy[2]->SetRunUpdate(false);	/*“G‚Ì“®‚«‚ğ~‚ß‚éi‰¼j*/
		enemy[3]->SetRunUpdate(false);	/*“G‚Ì“®‚«‚ğ~‚ß‚éi‰¼j*/
		player.SetRunUpdate(false);	/*Player‚Ì“®‚«‚ğ~‚ß‚é*/
		push = true;
	}
	if (push == true) {
		number++;
		if (number == 60) {
			enemy[0]->SetRunDraw(false);/*“G‚Ì•`‰æ‚ğÁ‚·*/
			enemy[1]->SetRunDraw(false);/*“G‚Ì•`‰æ‚ğÁ‚·*/
			enemy[2]->SetRunDraw(false);/*“G‚Ì•`‰æ‚ğÁ‚·*/
			enemy[3]->SetRunDraw(false);/*“G‚Ì•`‰æ‚ğÁ‚·*/
			state = State::miss;	/*State‚ğƒ~ƒX‚É*/
		}
	}
}

void Game::Draw() {
	int* life;
	life = WorldVal::Get<int>("Life");
	map.Draw();
	player.Draw();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
	DrawFormatString(50, 50, GetColor(255, 255, 255), "c‹@F%d", *life);
}