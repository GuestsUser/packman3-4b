#include "Game.h"
#include "Player.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include "EnemyPink.h"
#include "EnemyOrange.h"
#include "Enemyblue.h"
#include "PowerModeProcess.h"
#include <deque>
#include "GameMap.h"

Game::State Game::state = Game::State::start; //static変数の定義

Game::Game() :player(), enemy(std::deque<EnemyAra*>()), powerMode(PowerModeProcess(&player, &enemy)), sound(Sound(&powerMode,&player,&enemy)), map(GameMap(this, &player, &enemy, &sound)){
	state = State::start; //初期化時毎回startを代入する
	enemy.push_back(new EnemyRed(&player, &enemy)); //赤の敵を追加する
	enemy.push_back(new EnemyPink(&player));
	enemy.push_back(new EnemyOrange(&player));
	enemy.push_back(new Enemyblue(&player,enemy[0]));

	push = false;
	count = 0;
	number = 0;
}

void Game::Update() {
	foodcount=WorldVal::Get<int>("foodCountTotal");
	map.Update();
	ui.UiUpdate();
	player.Update();
	powerMode.Update();
	sound.Update();
	sound.spurtSound();
	EnemyAra::ModeChange(&enemy);
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	count++;
	
	//テスト
	Direction angle = player.GetDirection(); //プレイヤー動作角
	int px = player.ClculatTileX(angle);
	int py = player.ClculatTileY(angle);
	for (int i = 0; i < enemy.size(); ++i) {
		if (enemy[i]->GetState() == EnemyAra::State::damage) { continue; } //やられ状態なら当たり判定処理を取らない
		int ex = enemy[i]->ClculatTileX();
		int ey = enemy[i]->ClculatTileY();

		if (px == ex && py == ey) {
			if (powerMode.GetState() == PowerModeProcess::State::run) { powerMode.Hit(enemy[i]); break; } //パワーエサ有効ならパワーエサ実行クラスに接触を通知
			else { state = State::miss; break; } /*Stateをミスに*/
		}
	}
	if (*foodcount >= 244) {
		state = State::clear;
	}
	/*DrawBox(0, 315, 200, 370, GetColor(255, 0, 0), TRUE);
	DrawBox(400, 360, 500, 380, GetColor(255, 0, 0), TRUE);*/
}

void Game::Draw() {
	int* life;
	life = WorldVal::Get<int>("Life");
	map.Draw();
	player.Draw();
	powerMode.Draw();
	for (int i = enemy.size() - 1; i >= 0; --i) { enemy[i]->Draw(); } //[0]に入ってるアカベイが優先表示されるよう逆順実行
	DrawFormatString(50, 50, GetColor(255, 255, 255), "残機：%d", *life);
	DrawBox(100, 250, 192, 450, GetColor(0, 0, 0), TRUE);
	DrawBox(640, 250, 732, 450, GetColor(0, 0, 0), TRUE);
	ui.UiDraw();
}