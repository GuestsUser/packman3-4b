#include "DxLib.h"
#include "Game.h"
#include "Scene.h"
#include "GameMap.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "Food.h"
#include <unordered_map>
#include <string>
#include "Title.h"
#include "EnemyAra.h"
#include "Player.h"
#include "SoundLoading.h"
#include <deque>

class GameMap::Staging { //演出系、他のファイルに取り込まないのでクラス内に直接処理を書き込んでいい
public:
	enum class State { start, run, end, free }; //演出の実行状況、start=開始命令 run=実行中 end=終了した瞬間 free=動いていない
private:
	using StagingFunc = void (GameMap::Staging::*)(); //関数ポインタのusing宣言、以降Stagingクラスの関数ポインタはStagingFuncで使用可能

	State state; //実行のステータス保持
	GameMap* caller; //呼び出し元、これを通じてGameMap内の様々な関数にアクセスできる、内部クラスなのでprivateな領域にも直接アクセスできる
	StagingFunc func; //実行関数
	SoundLoading se;//音関係
	int count; //実行時間管理とかに
	int i;
	int startImage1;	//Player One画像用
	int startImage2;	//Ready!画像用
	int clearImage1;	//クリア画像（白）
	int clearImage2;	//クリア画像（青）
	int gameOverImage;	//ゲームオーバー画像

public:
	//引数にはこのクラスを使用するmapのアドレスを入れる
	Staging(GameMap* set) :state(State::free), caller(set), func(nullptr), count(0), 
		startImage1(*WorldVal::Get<int>("playerOneImage")), startImage2(*WorldVal::Get<int>("readyImage")),
		clearImage1(*WorldVal::Get<int>("clearImage1")), clearImage2(*WorldVal::Get<int>("clearImage2")),
		gameOverImage(*WorldVal::Get<int>("gameOverImage")){
		PlaySoundMem(se.seHandle[1], DX_PLAYTYPE_BACK, TRUE);
	}

	void Start() { //ゲーム開始時のREADY!等の演出、レベル1の時は音楽も流す
		std::deque<EnemyAra*>* enemy = caller->parent->EditEnemy();

		if (state == State::start) {
			caller->parent->EditPlayer()->SetRunUpdate(false);
			caller->parent->EditPlayer()->SetRunDraw(false);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(false);
				(*enemy)[i]->SetRunDraw(false);

			}
			state = State::run;
		}
		int* start;
		start = WorldVal::Get<int>("start");
		if (*start >= 1 && count == 0) {
			count = 121;
		}
		if (count == 121) {
			caller->parent->EditPlayer()->SetRunDraw(true);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunDraw(true);
			}
		}
		if (count <= 120) {
			//Player one表示
			DrawRotaGraph3(SHIFT_X + 149, SHIFT_Y + 176, 0, 0, X_RATE, Y_RATE, 0, startImage1, TRUE, FALSE);
		}
		if (count <= 240) {
			//Ready!表示
			DrawRotaGraph3(SHIFT_X + 176, SHIFT_Y + 272, 0, 0, X_RATE, Y_RATE, 0, startImage2, TRUE, FALSE);
		}
		else {
			state = State::free; //アニメ状態を終了済みに書き換える
			Game::SetSceneState(Game::State::run); //演出が終了した時間でゲームシーンの状態をゲーム中に変更する
			caller->parent->EditPlayer()->SetRunUpdate(true);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(true);
			}
		}

		count++;
		*start += 1;
	}

	void Clear() { //ゲームクリアの時の演出
		if ((count / 12) % 2 == 0) {
			//白画像
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage1, TRUE, FALSE);
		}
		else {
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage2, TRUE, FALSE);
		}
		//4回点滅したら（1回の点滅で24count）
		if (count >= 95) {
			state = State::free;	//アニメ状態を終了済みに書き換える
			caller->parent->SetNext(new Title());
		}
		count++;
	}

	void Miss() {  //パックマンがミスした時の演出
		int* life;
		life = WorldVal::Get<int>("Life");
		enemy[0]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		enemy[1]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		enemy[2]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		enemy[3]->SetRunUpdate(false);	/*敵の動きを止める（仮）*/
		caller->player->SetRunUpdate(false);	/*Playerの動きを止める*/
		if (count >= 60) {
			caller->player->DieAnim();
		}
		if (*life >= 1) {
			if (count >= 220) {
				*life -= 1;
				(*caller->food)["17x17"]->SetEnable(false);
				caller->parent->SetNext(new Game());
			}
		}
		else if (*life <= 0) {
			GameOver();
			if (count >= 220) {
				//AnimeStartUp(&Staging::GameOver);
			}
			//AnimeStartUp(&GameOver);
		}
		count++;
	}

	void Restart() {
		/*number++;
		if (number >= 120) {
			caller->parent->SetNext(new Game());
		}*/
	}
		
	void GameOver() {  //残機がなくなった時3の演出
		if (count <= 180) {

			DrawRotaGraph3(SHIFT_X + 149, SHIFT_Y + 176, 0, 0, X_RATE, Y_RATE, 0, startImage1, TRUE, FALSE);
			DrawRotaGraph3(SHIFT_X + 145, SHIFT_Y + 273, 0, 0, X_RATE, Y_RATE, 0, gameOverImage, TRUE, FALSE);
		}
		if (count == 180) {
			int* life;
			life = WorldVal::Get<int>("Life");
			*life = INI_LIFE;

			int* start;
			start = WorldVal::Get<int>("start");
			*start = 0;
			//シーンを次のステージにする（次ラウンド）
			//今はタイトルに戻るようにする
			caller->parent->SetNext(new Title());
		}
		count++;
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

GameMap::GameMap(Game* set,Player* pacman) :staging(new Staging(this)), tile(WorldVal::Get<Grid*>("map")), map(*WorldVal::Get<int>("mapImage")),food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), parent(set),player(pacman) {
	staging->AnimeStartUp(&Staging::Start);
}
GameMap::~GameMap() {
	delete staging; //こちらで精製した実体の削除
}
void GameMap::Draw() {
	//map画像の描画をここに記入
	DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, map, TRUE, FALSE);
	staging->Update(); //アニメの処理と描写を行う
	
	for (auto itr : *food) { itr.second->Draw(); } //食べ物描写
}
void GameMap::Update() {
	for (auto itr : *food) { itr.second->Update(); } //食べ物処理実行
	switch (Game::GetSceneState()) {
	case Game::State::start:
			break;
	case Game::State::miss:
		staging->AnimeStartUp(&Staging::Miss);
		//staging->Restart();
		Game::SetSceneState(Game::State::run);
		break;
	}
}