#pragma once
class Grid;

class GameMap {
	class Staging; //�X�e�[�W�p���o�N���X

	Staging* staging; //READY!���̉��o��Z�߂������N���X
	Grid** tile; //�}�b�v�̓񎟌��z��
	int map; //�}�b�v�̉摜�n���h��
public:
	GameMap();
	~GameMap();

	void Update();
	void Draw();

	
};