#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"
#include "Player.h"

//�Q�[���V�[���A���݂͋�A����m�F�����������������Update���ɒǋL���Ă����Ăق���
//Update�̒�`��cpp�ɂ���(���݂͋�)
class Game :public Scene {
	GameMap map;
	Player player;
public:
	Game() :map(GameMap(this)), player() {}
	void Update();
	void Draw();
};