#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include <unordered_map>
#include <string>

class Player::Moving {
public:
	enum class Mode { x, y };
	enum class State { start, run, curve, stop, free };
private:
	Player* caller; //�Ăяo����
	Mode type; //x,y�ǂ���̕������g�p���邩

	int speed; //���x�A���݂͏�Ԃɂ�炸���ȉ��̕�
	int speedCount; //���x�̒~�Ϗ󋵋L�^�A���t���[�������speed�����Z���AspeedCount/MOVABLE_SPEED�̒l���`�ʍ��W�𓮂���
	Direction nowDirection; //���݂̐i�s����
	Direction lastInput; //�Ō�̓��͕����ێ�
public:
	Moving(Player* player, Mode mode) :caller(player), type(mode), speed(16), speedCount(0), nowDirection(Direction::left) {}

	void Update() {

	}
};

Player::Player() :nowDirection(Direction::left), lastInput(Direction::left), isUpdate(true), isDraw(true), center(7), rad(1), speed(16), subX(17), subY(23), posX(13 * TILE + (TILE - 1)), posY(subY* TILE + (TILE - 1) / 2), speedCount(0), foodCount(0), foodCountTotal(0), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")) {}
Player::~Player() {
	delete xMove;
	delete yMove;
}

void Player::Update() {
	if (isUpdate) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�

		Direction old = lastInput; //���܂ł̓��͕����L���p
		//���͕����̕ύX�����A�������������u�ԁA��������ςȂ����ꂩ�œ��͕�����V�������Ɍ�������
		//���X�e�B�b�N�A�\���L�[�̗���������͂����
		//���݂͓����������ꂽ�ꍇ�D����u��>��>��>�E�v�̏��ɂ���׏��������u�E,��,��,��v�̗D��Ƃ͋t���ōs���Ă���(�t���ɂ��鎖�ŗD��x�̒Ⴂ�������ォ�獂�����ŏ㏑���ł���)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }
		
		if (old != lastInput) { //���܂łƈႤ�����ɓ��͂��m�F���ꂽ�ꍇ

		}

		speedCount += speed;
		tile[subX][subY].ReadPlayer()[(int)lastInput] == Move::block;

		int* edit = (int)nowDirection % 2 == 0 ? &posY : &posX; //�]�肪0�̏ꍇ�㉺(y����) 1�Ȃ獶�E(x����)�𑀍삷��ׂ̃G�C���A�X
		*edit += speedCount / MOVABLE_SPEED * (-1 + 2 * (((int)nowDirection) / 2)); //�l��2�ȏ�̏ꍇx���낤��y���낤�����Z�����ɓ����A����ȉ��Ȃ猸�Z�����Ƃ����d�g��
		speedCount -= speedCount / MOVABLE_SPEED * MOVABLE_SPEED; //�ړ��Ɏg�������̃h�b�g����菜��

		if (subX != posX / TILE || subY != posY / TILE) { //�}�X�ړ����������ꍇ

		}
	}
}
void Player::Draw() {
	if (isDraw) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		//�摜�T�C�Y-1�̔���(�����_�؂�̂�)�������ĕ`�ʂ��鎖�Ń}�X�̒��S�ʒu�ɂ���ꍇ�\�������̃}�X�̒��S�ʒu�ƂȂ�
		DrawRotaGraph3(SHIFT_X + (posX - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (posY - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
	}
}