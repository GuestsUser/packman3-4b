#include "Game.h"
#include "Title.h"
Game::State Game::state = Game::State::start; //static変数の定義

void Game::Update() {
	readycount++;
	if (key->GetKeyState(X_KEY) == KEY_PUSH) { //Xボタン(青ボタン)が押された瞬間
		SetNext(new(Title)); //ゲームシーンへ遷移
	}
	map.Update();
	//if (readycount >= 240) {
		player.Update();
		akabei.enemyUpdate();
	//}
}

void Game::Draw() {
	map.Draw();
	//if (readycount >= 120) {
		player.Draw();
		akabei.enemyDraw();
	//}
}