#include "DxLib.h"
#include "Game.h"
#include "Food.h"
#include "ConstVal.h"
#include "Worldval.h"
#include <string>

Food::Food(Type set) :type(set), isEnable(true), x(0), y(0), handle(*WorldVal::Get<int[10]>("foodImage")) ,count(0){  } //set�Ɏg�p�������^�C�v������A�����w�肵�Ȃ��ꍇ�ʏ�G�T�ɂȂ�

int Food::Eat() {
	int point = 0;
	switch (type) { //���g�̃^�C�v�ɉ����ē��_��Ԃ�
	case Type::food: point = 10; break;
	case Type::big: point = 50; break;
	case Type::cherry: point = 100; break;
	case Type::strawberry: point = 300; break;
	case Type::orange: point = 500; break;
	case Type::apple: point = 700; break;
	case Type::melon: point = 1000; break;
	case Type::galaxian: point = 2000; break;
	case Type::bell: point = 3000; break;
	case Type::key: point = 5000; break;
	}
	isEnable = false; //�H�ׂ����false�ɂȂ�
	return point;
}

void Food::Update() {

}

void Food::Draw() { //*8�Ȃǂ̃}�X�T�C�Y�͉������ɒ萔�Ő錾���Ă�������
	if (Game::GetSceneState() == Game::State::start) { //�X�^�[�g���̏ꍇ

	}
	//�Q�[���X�^�[�g�O
	if (isEnable) {
		DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
	}

	//�Q�[���X�^�[�g���i��ʂ��؂�ւ��܂Łj
	if (isEnable) { 
		if (type != Type::big) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
		else if (type == Type::big && (count / 10) % 2 == 0) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}

	//�Q�[���I�[�o�[���i�^�C�g���ɖ߂�܂Łj�i�p���[�G�T�������j
	if (isEnable) {
		if (type != Type::big) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}
	count++;
}

void Food::PosSetUp(const std::string& set) { //unordered_map�p�Y����������W�����o���֐�
	int size = set.length();
	for (int i = 0; i < size; ++i) {
		if (set[i] == *"x") { //��؂蕶�������������ꍇ
			x = std::stoi(set.substr(0, i)); //�O����x
			y = std::stoi(set.substr(i + 1, size)); //�㔼��y
			return;
		}
	}
	//��؂肪������Ȃ������ꍇ���ɉ����������Ȃ�
}