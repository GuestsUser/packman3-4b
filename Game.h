#pragma once
#include "Scene.h"
#include "Worldval.h"
#include "GetKey.h"

//�Q�[���V�[���A���݂͋�A����m�F�����������������Update���ɒǋL���Ă����Ăق���
//Update�̒�`��cpp�ɂ���(���݂͋�)
class Game :public Scene {
public:
	void Update();
	void Draw();
};