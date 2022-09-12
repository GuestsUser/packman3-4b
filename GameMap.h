#pragma once
#include <unordered_map>
#include <string>
#include <deque>

class Grid;
class Food;
class Game;
class Player;

class GameMap {
	class Staging; //�X�e�[�W�p���o�N���X

	std::deque<EnemyAra*>* enemy;
	Game* parent;
	Staging* staging; //READY!���̉��o��Z�߂������N���X
	Grid** tile; //�}�b�v�̓񎟌��z��
	Player* player;
	int map; //�}�b�v�̉摜�n���h��
	std::unordered_map<std::string, Food*>* food; //�G�T��ێ�����z��
	bool push;
	static bool Missflg;
public:
	GameMap(Game* set,Player* pacman, std::deque<EnemyAra*>* getEnemy);
	~GameMap();
	void Miss();
	void Restart();
	void Update();
	void Draw();

	
};