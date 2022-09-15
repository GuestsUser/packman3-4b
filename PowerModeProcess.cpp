#include "PowerModeProcess.h"
#include "EnemyAra.h"
#include "Player.h"
#include "Worldval.h"
#include "ConstVal.h"

PowerModeProcess::State PowerModeProcess::state = PowerModeProcess::State::free; //実体定義
int PowerModeProcess::time = 0;

PowerModeProcess::PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy) :player(setPlayer),enemy(setEnemy) { //作成時未実行状態に初期化
	time = 0;
	state = State::free;
}

void PowerModeProcess::Update() {
	switch (state) {
	case PowerModeProcess::State::start:
		if (time <= 0) { //パワーモードが持続していた場合敵反転を実行しないif文
			for (int i = 0; i < enemy->size(); ++i) { (*enemy)[i]->SetReversOrder(true); } //敵反転命令
		}
		time = ClculatIniTime(); //新しい実行時間入れ
		if (time <= 0) { return; } //新しい時間が0なら反転させて終わり

		player->SetState(Player::State::power); //プレイヤーの状態をパワーエサ有効状態に変更
		for (int i = 0; i < enemy->size(); ++i) { 
			EnemyAra::State enemyState = (*enemy)[i]->GetState();
			if (enemyState == EnemyAra::State::neutral || enemyState == EnemyAra::State::wait) { (*enemy)[i]->SetState(EnemyAra::State::cringe); } //通常、待機状態の敵にのみイジケ状態を付与する
		}
		state = State::run; //実行中に変更

		break;
	case PowerModeProcess::State::run:
		--time;
		if (time <= 0) {
			player->SetState(Player::State::neutral); //プレイヤーの状態を通常状態に変更
			for (int i = 0; i < enemy->size(); ++i) {
				EnemyAra::State enemyState = (*enemy)[i]->GetState();
				if (enemyState == EnemyAra::State::cringe) { (*enemy)[i]->SetState(EnemyAra::State::neutral); } //待機状態解除方法によってはバグを生む可能性あり
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
