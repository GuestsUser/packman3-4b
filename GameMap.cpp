#include "DxLib.h"
#include "GameMap.h"
#include "Grid.h"

class GameMap::Staging { //演出系、他のファイルに取り込まないのでクラス内に直接処理を書き込んでいい
	enum class State; //前方宣言
	using StagingFunc = void (GameMap::Staging::*)(); //関数ポインタのusing宣言、以降Stagingクラスの関数ポインタはStagingFuncで使用可能

	State state; //実行のステータス保持
	GameMap* caller; //呼び出し元、これを通じてGameMap内の様々な関数にアクセスできる、内部クラスなのでprivateな領域にも直接アクセスできる
	StagingFunc func; //実行関数
	int count; //実行時間管理とかに
public:
	enum class State { start, run, end, free }; //演出の実行状況、start=開始命令 run=実行中 end=終了した瞬間 free=動いていない

	Staging(GameMap* set) :state(State::free), caller(set), func(Start) {} //引数にはこのクラスを使用するmapのアドレスを入れる
	void Start() { //ゲーム開始時のREADY!等の演出、レベル1の時は音楽も流す

	}
	void Clear() { //ゲームクリアの時の演出

	}
	void Miss() {  //パックマンがミスした時の演出

	}
	void GameOver() {  //残機がなくなった時の演出

	}

	//GameMap呼び出し関数
	void AnimeStartUp(StagingFunc set) { //Stagingの各種public関数のアドレスを入れるとcountを0、Stateをstartに初期化し引数の関数を実行してくれる
		//例えばStartアニメを実行したい場合 Stagingクラスのオブジェクト->AnimeStartUp(Staging::Start); で指定できる
		func = set;
		count = 0;
		state = State::start;
	}
	State GetRunState() { return state; } //現在の実行状況を返す、アニメが終了した瞬間等を取りたい場合アニメの定義で終了した瞬間stateをendにすればここで返ってくる値がendの時終了した瞬間だと判断できる
	void Update() { //GameMapのUpdateで毎回呼び出す事でアニメの実行命令が出ている間は指定アニメを実行してくれる
		if (state != State::free) { (this->*func)(); } //Stateがfree以外の場合指定された演出の実行
	}
};

GameMap::GameMap() {
	
}
GameMap::~GameMap() {

}
void GameMap::Draw() {

}
void GameMap::Update() {

}