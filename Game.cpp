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

Game::Game() :player(), enemy(std::deque<EnemyAra*>()), powerMode(PowerModeProcess(&player, &enemy,&sound)), sound(Sound(&powerMode,&player,&enemy)), map(GameMap(this, &player, &enemy, &sound)){
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
	//sound.spurtSound();
	EnemyAra::ModeChange(&enemy);
	int* dieCount;
	dieCount = WorldVal::Get<int>("dieCount");
	int* activeFoodCount;
	activeFoodCount = WorldVal::Get<int>("activeFoodCount");
	int* enemyActive;
	enemyActive = WorldVal::Get<int>("enemyActive");
	

	if (*activeFoodCount > current) {
		count = 0;
		current++;
	}
	else {
		count++;
	}

	if (*dieCount == 0) {
		if ((enemy)[0]->GetState() == EnemyAra::State::wait) { (enemy)[0]->SetStateReinterpret(EnemyAra::State::ready); }
		if ((enemy)[1]->GetState() == EnemyAra::State::wait) { (enemy)[1]->SetStateReinterpret(EnemyAra::State::ready); }
		if ((enemy)[3]->GetState() == EnemyAra::State::wait && *activeFoodCount == 30 || count >= 300 && *enemyActive == 0) { (enemy)[3]->SetStateReinterpret(EnemyAra::State::ready); *enemyActive = 1; count = 0; }/*エサを30個食べるorエサを最後に食べてあら5秒後に三体目の敵が出現*/
		if ((enemy)[2]->GetState() == EnemyAra::State::wait && *activeFoodCount == 90 || count >= 300 && *enemyActive == 1) {(enemy)[2]->SetStateReinterpret(EnemyAra::State::ready); }
	}
	else if (*dieCount >= 1) {	/*1度死んだあと*/
		if((enemy)[1]->GetState() == EnemyAra::State::wait){(enemy)[0]->SetStateReinterpret(EnemyAra::State::ready);}
		if((enemy)[1]->GetState() == EnemyAra::State::wait && *activeFoodCount == 7 || count >= 300 && *enemyActive == 0) { (enemy)[1]->SetStateReinterpret(EnemyAra::State::ready); count = 0; *enemyActive = 1; }
		if((enemy)[3]->GetState() == EnemyAra::State::wait && *activeFoodCount == 17 || count >= 300 && *enemyActive == 1){ (enemy)[3]->SetStateReinterpret(EnemyAra::State::ready); count = 0; *enemyActive = 2;}
		if((enemy)[2]->GetState() == EnemyAra::State::wait && *activeFoodCount == 32 || count >= 300 && *enemyActive == 2){ (enemy)[2]->SetStateReinterpret(EnemyAra::State::ready); count = 0; *enemyActive = 3;}
	}
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	
	//テスト
	Direction angle = player.GetDirection(); //プレイヤー動作角
	int px = player.ClculatTileX(angle);
	int py = player.ClculatTileY(angle);
	for (int i = 0; i < enemy.size(); ++i) {
		if (enemy[i]->GetState() != EnemyAra::State::neutral && enemy[i]->GetState() != EnemyAra::State::cringe) { continue; } //通常、イジケ状態以外なら判定は取らない
		int ex = enemy[i]->ClculatTileX();
		int ey = enemy[i]->ClculatTileY();

		if (px == ex && py == ey) {
			if (enemy[i]->GetState()==EnemyAra::State::cringe) { powerMode.Hit(enemy[i]); break; } //イジケ状態ならパワーエサ実行クラスに接触を通知
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
	int* activeFoodCount;
	activeFoodCount = WorldVal::Get<int>("activeFoodCount");
	int* enemyActive;
	enemyActive = WorldVal::Get<int>("enemyActive");
	int* dieCount;
	dieCount = WorldVal::Get<int>("dieCount");
	map.Draw();
	player.Draw();
	powerMode.Draw();
	for (int i = enemy.size() - 1; i >= 0; --i) { enemy[i]->Draw(); } //[0]に入ってるアカベイが優先表示されるよう逆順実行
	DrawFormatString(50, 50, GetColor(255, 255, 255), "残機：%d", *life);
	DrawBox(100, 250, 192, 450, GetColor(0, 0, 0), TRUE);
	DrawBox(640, 250, 732, 450, GetColor(0, 0, 0), TRUE);
	ui.UiDraw();
}