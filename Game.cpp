#include "Game.h"
#include "Player.h"
#include "EnemyAra.h"
#include "EnemyRed.h"
#include "EnemyPink.h"
#include "EnemyOrange.h"
#include "Enemyblue.h"
#include <deque>
#include "GameMap.h"

Game::State Game::state = Game::State::start; //static�ϐ��̒�`

Game::Game() :player(),enemy(std::deque<EnemyAra*>()), map(GameMap(this, &player, &enemy)) {
	state = State::start; //������������start��������
	enemy.push_back(new EnemyRed(&player, &enemy)); //�Ԃ̓G��ǉ�����
	enemy.push_back(new EnemyPink(&player));
	enemy.push_back(new EnemyOrange(&player));
	enemy.push_back(new Enemyblue(&player,enemy[0]));

	push = false;
	count = 0;
	number = 0; 
	
}

void Game::Update() {
	map.Update();
	ui.UiUpdate();
	player.Update();
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
		(enemy)[0]->SetState(EnemyAra::State::neutral);
		(enemy)[1]->SetState(EnemyAra::State::neutral);
		if (*activeFoodCount == 30 || count >= 300 && *enemyActive == 0) { (enemy)[3]->SetState(EnemyAra::State::neutral); *enemyActive = 1; count = 0; }/*�G�T��30�H�ׂ�or�G�T���Ō�ɐH�ׂĂ���5�b��ɎO�̖ڂ̓G���o��*/
		if (*activeFoodCount == 90 || count >= 300 && *enemyActive == 1) {(enemy)[2]->SetState(EnemyAra::State::neutral); }
	}
	else if (*dieCount >= 1) {	/*1�x���񂾂���*/
		(enemy)[0]->SetState(EnemyAra::State::neutral);
		if (*activeFoodCount == 7 || count >= 300 && *enemyActive == 0) { (enemy)[1]->SetState(EnemyAra::State::neutral); count = 0; *enemyActive = 1; }
		if(*activeFoodCount == 17 || count >= 300 && *enemyActive == 1){ (enemy)[3]->SetState(EnemyAra::State::neutral); count = 0; *enemyActive = 2;}
		if(*activeFoodCount == 32 || count >= 300 && *enemyActive == 2){ (enemy)[2]->SetState(EnemyAra::State::neutral); count = 0; *enemyActive = 3;}
	}
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	
	//�e�X�g
	Direction angle = player.GetDirection(); //�v���C���[����p
	int px = player.ClculatTileX(angle);
	int py = player.ClculatTileY(angle);
	for (int i = 0; i < enemy.size(); ++i) { 
		int ex = enemy[i]->ClculatTileX();
		int ey = enemy[i]->ClculatTileY();

		if (px == ex && py == ey) {
			state = State::miss;	/*State���~�X��*/
			break;
		}
	}
}

void Game::Draw() {
	int* life;
	life = WorldVal::Get<int>("Life");
	int* activeFoodCount;
	activeFoodCount = WorldVal::Get<int>("activeFoodCount");
	int* enemyActive;
	enemyActive = WorldVal::Get<int>("enemyActive");
	map.Draw();
	ui.UiDraw();
	player.Draw();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
	DrawFormatString(50, 50, GetColor(255, 255, 255), "�c�@�F%d", *life);
	DrawFormatString(600, 50, GetColor(255, 255, 255), "count%d", count);
	DrawFormatString(900, 50, GetColor(255, 255, 255), "fc%d", *activeFoodCount);
	DrawFormatString(900, 80, GetColor(255, 255, 255), "it%d", current);
	DrawFormatString(900, 110, GetColor(255, 255, 255), "enemyActive%d", *enemyActive);
}