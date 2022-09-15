#pragma once
#include <deque>

class Player;
class EnemyAra;

class PowerModeProcess {
public:
	enum class State { start, run, end, free }; //実行状況系ステート
private:
	int time; //実行残り時間

	static State state; //現在の実行状況、1つのみ存在
	Player* player; //プレイヤー参照
	std::deque<EnemyAra*>* enemy; //エネミー参照

	int ClculatIniTime(); //現在ステージから実行時間を返す関数
public:
	PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy);

	void Update();
	void Draw() {} //なんに使うかは未定の描写関数

	static void PowerModeStart() { state = State::start; } //パワーエサ取得状態の起動
	static State GetState() { return state; } //実行状況を返す、freeで通常、runでパワーエサ実行中
};