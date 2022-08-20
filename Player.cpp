#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include <unordered_map>
#include <string>

Player::Player() :lastInput(Direction::left), isUpdate(true), isDraw(true), speed(16), subX(17), subY(23), drawX(subX* TILE), drawY(subY* TILE), speedCount(0), foodCount(0), foodCountTotal(0), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")) {}

void Player::Update() {
	if (isUpdate) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�

		//���͕����̕ύX�����A�������������u�ԁA��������ςȂ����ꂩ�œ��͕�����V�������Ɍ�������
		//���X�e�B�b�N�A�\���L�[�̗���������͂����
		//���݂͓����������ꂽ�ꍇ�D����u��>��>��>�E�v�̏��ɂ���׏��������u�E,��,��,��v�̗D��Ƃ͋t���ōs���Ă���(�t���ɂ��鎖�ŗD��x�̒Ⴂ�������ォ�獂�����ŏ㏑���ł���)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }
		
		speedCount += speed;

	}
}
void Player::Draw() {
	if (isDraw) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		//x�͂��̂܂܍��㌴�_�`�ʁAy�̓v���C���[�摜�T�C�Y�ƃ^�C���T�C�Y�̈Ⴂ����^�C���̔���������ɂ��炵�ĕ`�ʂ��s���Ă���
		DrawRotaGraph3(SHIFT_X + (drawX - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (drawY - WARP_AREA_Y * TILE - TILE / 2) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
	}
}