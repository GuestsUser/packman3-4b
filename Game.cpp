#include "Game.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include "EnemyPink.h"
#include <deque>
#include "GameMap.h"
Game::State Game::state = Game::State::start; //static変数の定義

Game::Game() :player(), map(GameMap(this, &player)),enemy(std::deque<EnemyAra*>()) {
	state = State::start; //初期化時毎回startを代入する
	enemy.push_back(new EnemyRed(&player)); //赤の敵を追加する
	enemy.push_back(new EnemyPink(&player));
	push = false;
	count = 0;
	number = 0;
}

void Game::Update() {
	map.Update();
	player.Update();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	count++;
	if (key->GetKeyState(X_KEY) == KEY_PUSH) {	/*Xキーを押したら*/
		enemy[0]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		enemy[1]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		//enemy[2]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		//enemy[3]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		player.SetRunUpdate(false);	/*Playerの動きを止める*/
		push = true;
	}
	if (push == true) {
		number++;
		if (number == 60) {
			enemy[0]->SetRunDraw(false);/*敵の描画を消す*/
			enemy[1]->SetRunDraw(false);/*敵の描画を消す*/
			//enemy[2]->SetRunDraw(false);/*敵の描画を消す*/
			//enemy[3]->SetRunDraw(false);/*敵の描画を消す*/
			state = State::miss;	/*Stateをミスに*/
		}
	}
}

void Game::Draw() {
	int* life;
	life = WorldVal::Get<int>("Life");
	map.Draw();
	player.Draw();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
	DrawFormatString(50, 50, GetColor(255, 255, 255), "残機：%d", *life);
}