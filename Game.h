#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"
#include "GameMap.h"

//�Q�[���V�[���A���݂͋�A����m�F�����������������Update���ɒǋL���Ă����Ăق���
//Update�̒�`��cpp�ɂ���(���݂͋�)
class Game :public Scene {
	GameMap map;
public:
	Game() :map(GameMap(this)) {}
	void Update();
	void Draw();
};