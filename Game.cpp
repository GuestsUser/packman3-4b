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

Game::State Game::state = Game::State::start; //static�ϐ��̒�`

Game::Game() :player(), enemy(std::deque<EnemyAra*>()), map(GameMap(this, &player, &enemy)), powerMode(PowerModeProcess(&player, &enemy)) {
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
	foodcount=WorldVal::Get<int>("foodCountTotal");
	map.Update();
	ui.UiUpdate();
	player.Update();
	powerMode.Update();
	EnemyAra::ModeChange(&enemy);
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Update(); }
	count++;
	
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
	if (*foodcount >= 244) {
		state = State::clear;
	}
}

void Game::Draw() {
	int* life;
	life = WorldVal::Get<int>("Life");
	map.Draw();
	ui.UiDraw();
	player.Draw();
	for (int i = 0; i < enemy.size(); ++i) { enemy[i]->Draw(); }
	DrawFormatString(50, 50, GetColor(255, 255, 255), "�c�@�F%d", *life);
}