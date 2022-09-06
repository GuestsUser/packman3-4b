#include "Game.h"
#include "Title.h"
Game::State Game::state = Game::State::start; //static�ϐ��̒�`

void Game::Update() {
	readycount++;
	if (key->GetKeyState(X_KEY) == KEY_PUSH) { //X�{�^��(�{�^��)�������ꂽ�u��
		SetNext(new(Title)); //�Q�[���V�[���֑J��
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