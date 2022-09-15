#pragma once
#include <deque>

class Player;
class EnemyAra;

class PowerModeProcess {
public:
	enum class State { start, run, end, free }; //実行状況系ステート
private:
	static int time; //実行残り時間
	static int drawTime; //敵を食べた時のスコア表示残り時間
	static int rawDrawTime; //スコア表示残り時間の初期値、値の初期化時これを入れる

	int combo; //1回のパワーエサで敵を食べた回数記録
	EnemyAra* target; //スコア表示のターゲットエネミー


	static State state; //現在の実行状況、1つのみ存在
	Player* player; //プレイヤー参照
	std::deque<EnemyAra*>* enemy; //エネミー参照

	int ClculatIniTime(); //現在ステージから実行時間を返す関数
	int ClculatScore(); //現在のコンボ値から加算スコアを計算
public:
	PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy);

	void Update();
	void Draw();

	void Hit(EnemyAra* set); //パワーエサ有効中にヒットが発生した時呼び出す関数
	static void PowerModeStart() { state = State::start; } //パワーエサ取得状態の起動
	static State GetState() { return state; } //実行状況を返す、freeで通常、runでパワーエサ実行中

	static int GetTimeLeft() { return time; } //現在の残り時間を取得する
};