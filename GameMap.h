#pragma once
#include <unordered_map>
#include <string>
class Grid;
class Food;

class GameMap {
	class Staging; //�X�e�[�W�p���o�N���X

	Staging* staging; //READY!���̉��o��Z�߂������N���X
	Grid** tile; //�}�b�v�̓񎟌��z��
	int map; //�}�b�v�̉摜�n���h��
	std::unordered_map<std::string, Food*>* food; //�G�T��ێ�����z��
public:
	GameMap();
	~GameMap();

	void Update();
	void Draw();

	
};