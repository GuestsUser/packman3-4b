#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Ui.h"
#include "Player.h"
#include "EnemyAra.h"
#include <deque>

//�Q�[���V�[���A���݂͋�A����m�F�����������������Update���ɒǋL���Ă����Ăق���
//Update�̒�`��cpp�ɂ���(���݂͋�)

class Game :public Scene {
public:
	enum class State { start, run, miss, gameover, clear }; //�Q�[���󋵂�\���񋓌^�Astart=�Q�[���J�n�O, run=�Q�[����, miss=�v���C���[�~�X��, gameover=�c�@���������~�X���o�ケ��ɂ���, clear=�S�ẴG�T��H�ׂ���
private:
	GameMap map;
	Player player;
	GameUi ui;
	std::deque<EnemyAra*> enemy;
	static State state; //Food�Ɏ����x���Ɉڍs����xGame�̓��e�����ւ������Ȃ������̂�static�ϐ��ɂ��ăw�b�_�[�����C���N���[�h���Ă����΂��ł��A�N�Z�X�ł���
	int count;
	int number;
	int StartTime;
	bool push;
public:
	Game();
	void Update();
	void Draw();

	Player* EditPlayer() { return &player; }
	std::deque<EnemyAra*>* EditEnemy() { return &enemy; }

	static State GetSceneState() { return state; } //���݂̃Q�[���󋵂̎擾
	static void SetSceneState(State set) { state = set; } //�Q�[���󋵂̏�������
};