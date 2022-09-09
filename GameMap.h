#pragma once
#include <unordered_map>
#include <string>

class Grid;
class Food;
class Scene;
class Player;

class GameMap {
	class Staging; //�X�e�[�W�p���o�N���X

	Scene* parent;
	Staging* staging; //READY!���̉��o��Z�߂������N���X
	Grid** tile; //�}�b�v�̓񎟌��z��
	Player* player;
	int map; //�}�b�v�̉摜�n���h��
	std::unordered_map<std::string, Food*>* food; //�G�T��ێ�����z��
	bool push;
	static bool Missflg;
public:
	GameMap(Scene* set,Player* pacman);
	~GameMap();
	void Miss();
	void Update();
	void Draw();

	
};