#include "DxLib.h"
#include "PowerModeProcess.h"
#include "EnemyAra.h"
#include "Player.h"
#include "Worldval.h"
#include "ConstVal.h"
#include <math.h>

PowerModeProcess::State PowerModeProcess::state = PowerModeProcess::State::free; //実体定義
int PowerModeProcess::time = 0;
int PowerModeProcess::rawDrawTime = 120; //仮の値
int PowerModeProcess::drawTime = rawDrawTime;

PowerModeProcess::PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy) :player(setPlayer), enemy(setEnemy), combo(0), target(nullptr), eatSE3(*WorldVal::Get<int>("eatSE3")) { //作成時未実行状態に初期化
	time = 0;
	drawTime = 0;
	state = State::free;
}

void PowerModeProcess::Update() {
	switch (state) {
	case PowerModeProcess::State::start:
		if (time <= 0) { //パワーモードが持続していた場合敵反転を実行しないif文
			for (int i = 0; i < enemy->size(); ++i) { (*enemy)[i]->SetReversOrder(true); } //敵反転命令
		}
		combo = 0; //コンボの初期化
		time = ClculatIniTime(); //新しい実行時間入れ
		if (time <= 0) { return; } //新しい時間が0なら反転させて終わり

		player->SetState(Player::State::power); //プレイヤーの状態をパワーエサ有効状態に変更
		for (int i = 0; i < enemy->size(); ++i) { 
			EnemyAra::State enemyState = (*enemy)[i]->GetState();
			if (enemyState != EnemyAra::State::damage) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //やられ状態以外ならイジケ状態を付与する
		}
		state = State::run; //実行中に変更

		break;
	case PowerModeProcess::State::run:
		if (drawTime > 0) { break; } //スコア表示中は実行停止
		--time; //カウントダウン
		
		if (time <= 0) {
			player->SetState(Player::State::neutral); //プレイヤーの状態を通常状態に変更
			for (int i = 0; i < enemy->size(); ++i) {
				EnemyAra::State enemyState = (*enemy)[i]->GetState();
				if (enemyState != EnemyAra::State::damage) { (*enemy)[i]->SetState(EnemyAra::State::neutral); } //やられ状態以外の敵は通常にする
			}
			state = State::free; //実行状況を解放状態に変更
		}
		break;
	case PowerModeProcess::State::end:
		break;
	case PowerModeProcess::State::free:
		break;
	}
}

void PowerModeProcess::Draw() {
	if (drawTime > 0) { //描写時間が0超過時のみ実行
		if (drawTime == 1) { //次で終わりの場合終了処理を通る
			//エネミー、プレイヤーの処理、表示の再開
			for (int i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(true);
				(*enemy)[i]->SetRunDraw(true);
			}
			player->SetRunUpdate(true);
			player->SetRunDraw(true);
			drawTime = 0;
			return;
		}
		SetFontSize(18);
		DrawFormatString(target->GetDrawX(), target->GetDrawY(), GetColor(0, 255, 255), "%d", ClculatScore()); //スコア表示
		--drawTime;
	}
}

void PowerModeProcess::Hit(EnemyAra* set) {
	target = set; //スコア表示のターゲットを指定
	drawTime = rawDrawTime; //残り表示時間の初期化
	for (int i = 0; i < enemy->size(); ++i) {
		if ((*enemy)[i]->GetState() == EnemyAra::State::damage) { continue; } //やられ状態の敵は止めない
		(*enemy)[i]->SetRunUpdate(false); //処理の非実行
		(*enemy)[i]->SetRunDraw(false); //非表示化
	}
	player->SetRunUpdate(false); //処理の非実行
	player->SetRunDraw(false); //非表示化
	target->SetState(EnemyAra::State::damage); //ターゲット敵をやられ状態に設定
	++combo; //コンボ値を加算
	*WorldVal::Get<int>("score") += ClculatScore(); //スコア加算

	//ここにse鳴らしを入れる
	PlaySoundMem(eatSE3,DX_PLAYTYPE_BACK);

}

int PowerModeProcess::ClculatIniTime() {
	switch (*WorldVal::Get<int>("nowStage")) { //現在ステージ数に合わせて返す時間を変える
	case 0:
		return 6 * FPS; 

	case 1: case 5: case 9:
		return 5 * FPS;

	case 2:
		return 4 * FPS;

	case 3: case 13:
		return 3 * FPS;

	case 4: case 6: case 7: case 10:
		return 2 * FPS;

	case 8: case 11: case 12: case 14: case 15: case 17:
		return 1 * FPS;

	default: return 0;
	}
}

int PowerModeProcess::ClculatScore() { return 100 * pow(2, combo); }