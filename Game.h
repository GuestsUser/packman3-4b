#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Player.h"

//�Q�[���V�[���A���݂͋�A����m�F�����������������Update���ɒǋL���Ă����Ăق���
//Update�̒�`��cpp�ɂ���(���݂͋�)
class Game :public Scene {
public:
	enum class State { start, run, miss, gameover, clear }; //�Q�[���󋵂�\���񋓌^
private:
	GameMap map;
	Player player;
	State state;
public:
	Game() :map(GameMap(this)), player(), state(State::start) {}
	void Update();
	void Draw();

	State GetSceneState() const { return state; } //���݂̃Q�[���󋵂̎擾
	void SetSceneState(State set) { state = set; } //�Q�[���󋵂̏�������
};