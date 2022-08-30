#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include <unordered_map>
#include <string>
#include <math.h>

class Movable {
public:
	enum class State { start, run, curve, stop, free };

private:
	Player* player;
	State state;
	Direction direction;
	int* posEdit;
	int center; //�}�X�����W�̒��S�ʒu�A�J�[�u���̓���͂�����ڕW�ɍs��
public:
	Movable() :state(State::free), direction(Direction::left), posEdit(nullptr), center(TILE / 2 - 1) {}
	void SetUp(int* set, Player* setP) {
		posEdit = set;
		player = setP;
	}
	virtual void Update(int speed) = 0;
	virtual bool IsCurveInRange(int localPos) = 0; //���݂̓�������ŋȂ��鎖���\�ȗ̈�ɂ��邩�ǂ����`�F�b�N����Atrue�ŋȂ����

	int GetMoveSub() { return -1 + 2 * (int)((int)direction / 2); } //�ړ������ɑΉ����������Ԃ��A��A���̓}�C�i�X�����ւ̈ړ��A���A�E���v���X�����ւ̈ړ��Ȃ̂�/2�𗘗p����
	void Moving(int speed) { *posEdit += speed * GetMoveSub(); }

	int GetCenter() const { return center; }
	State GetState() const { return state; }
	Direction GetDirection() const { return direction; }
	const int* ReadPos() const { return posEdit; }
	const Player* const ReadPlayer() { return player; }

	void SetState(State set) { state = set; }
	void SetDirection(Direction set) { direction = set; }

};

class XMove :public Movable {
	int target; //�J�[�u�����̈ʒu��ڎw��
public:
	XMove(int* editPos, Player* player) :target(3) { SetUp(editPos, player); }
	void Update(int speed) {
		switch (GetState())
		{
		case Movable::State::start:

			break;
		case Movable::State::run:
			Moving(speed);
			break;
		case Movable::State::curve:
			Moving(speed);
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalX(GetDirection()))) { SetState(State::free); }
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool left = localPos <= 6 && localPos > 3;
		bool right = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ? left : right;
	}
};

class YMove :public Movable {
	int target; //�J�[�u�����̈ʒu��ڎw��
public:
	YMove(int* editPos, Player* player) :target(3) { SetUp(editPos, player); }
	void Update(int speed) {
		switch (GetState())
		{
		case Movable::State::start:

			break;
		case Movable::State::run:
			Moving(speed);
			break;
		case Movable::State::curve:
			Moving(speed);
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalY(GetDirection()))) { SetState(State::free); }
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool up = localPos <= 6 && localPos > 3;
		bool down = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ? up : down;
	}
};

class Player::Moving {
public:
private:
	Player* caller; //�Ăяo����
	Movable* x;
	Movable* y;

	int safeZone; //�}�X�����W��safeZone�`TILE-safeZone���łȂ��ƐV���ɋȂ��鎖���ł��Ȃ��A���ׂ̈̕ϐ�
	int speed; //���x�A���݂͏�Ԃɂ�炸���ȉ��̕�
	int speedCount; //���x�̒~�Ϗ󋵋L�^�A���t���[�������speed�����Z���AspeedCount/MOVABLE_SPEED�̒l���`�ʍ��W�𓮂���
	Direction nowDirection; //���݂̐i�s����
	Direction lastInput; //�Ō�̓��͕����ێ�
public:
	Moving(Player* player) :caller(player), safeZone(2), speed(16), speedCount(0), nowDirection(Direction::left), lastInput(nowDirection), x(new XMove(&caller->posX, caller)),y(new YMove(&caller->posY, caller)) {
		x->SetState(Movable::State::run);
		y->SetDirection(Direction::up);
	}

	void Update() {
		//���͕����̕ύX�����A�������������u�ԁA��������ςȂ����ꂩ�œ��͕�����V�������Ɍ�������
		//���X�e�B�b�N�A�\���L�[�̗���������͂����
		//���݂͓����������ꂽ�ꍇ�D����u��>��>��>�E�v�̏��ɂ���׏��������u�E,��,��,��v�̗D��Ƃ͋t���ōs���Ă���(�t���ɂ��鎖�ŗD��x�̒Ⴂ�������ォ�獂�����ŏ㏑���ł���)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }

		int subX = caller->ClculatTileX(nowDirection) + WARP_AREA_X; //���S���W�������������݂̏����}�Xx
		int subY = caller->ClculatTileY(nowDirection) + WARP_AREA_Y; //��L��y��

		while (nowDirection != lastInput) { //while���𗘗p�����̂�break��K���Ȉʒu�ɑ}�����鎖��else���������鎖���ړI�A���[�v����������ł͂Ȃ�
			bool yCurve = (int)lastInput % 2 == 0; //�V�����������㉺���ꂩ�ɂȂ�ꍇtrue
			Movable* end = yCurve ? x : y; //�ړ�������߂鎲
			Movable* start = yCurve ? y : x; //�V�����ړ����n�߂鎲

			if ((Direction)(((int)nowDirection + 2) % 4) == lastInput) { //���͕��������Ε����������ꍇ
				nowDirection = lastInput; //��������͂̂����������ɕύX
				subX = caller->ClculatTileX(nowDirection) + WARP_AREA_X; //�����ύX�ɍ��킹�����݃}�X���X�V
				subY = caller->ClculatTileY(nowDirection) + WARP_AREA_Y;
				start->SetDirection(nowDirection); //�V���������̐ݒ�
				break; //�ȍ~��while���������͎��s���Ȃ�
			}
			int localX = caller->ClculatLocalX(nowDirection); //���݃}�X���ł̈ʒu
			int localY = caller->ClculatLocalY(nowDirection); //��L��y��

			//���Lif����while��p���Ȃ��ꍇ����q�ɂ��邩1��if�������ɂ܂Ƃ߂邩�ɂȂ����̂ő������₷���Ȃ����c����
			if ((!yCurve) && (!y->IsCurveInRange(localY))) { break; }
			if (yCurve && (!x->IsCurveInRange(localX))) { break; }
			//if (localX < safeZone - 1 || localX > TILE - safeZone) { break; } //�͈͊O����Atrue�Ȃ�I��
			//if (localY < safeZone - 1 || localY > TILE - safeZone) { break; } //��L��y��
			if (x->GetState() == Movable::State::curve || y->GetState() == Movable::State::curve) { break; } //�ǂ��炩�̃^�X�N���J�[�u�ړ����������ꍇ
			if (caller->tile[subX][subY].ReadPlayer()[(int)lastInput] == Move::block) { break; } //�ړ��������������ړ��s�������ꍇ

			//�����܂ŗ����΁A�����]���\��ɓ����Ă��銎�ǂ̕������J�[�u���ł͂Ȃ��A�Ō�ɓ��͂̂������������ړ��\�ł���
			nowDirection = lastInput; //��������͂̂����������ɕύX
			subX = caller->ClculatTileX(nowDirection) + WARP_AREA_X; //�����ύX�ɍ��킹�����݃}�X���X�V
			subY = caller->ClculatTileY(nowDirection) + WARP_AREA_Y;

			end->SetState(Movable::State::curve); //���ݐi�ޕ������Ȃ��鏈���Ɏw��
			start->SetState(Movable::State::run); //�V���������ֈړ����J�n����
			start->SetDirection(nowDirection); //�ړ����J�n�������֐V����������ݒ�

			break; //while����
		}
		speedCount += speed; //���x���Z
		int move = speedCount / MOVABLE_SPEED; //����̈ړ��h�b�g��
		speedCount -= move * MOVABLE_SPEED; //�ړ��Ɏg�������̃h�b�g����菜��

		x->Update(move); //���W�ړ�
		y->Update(move);
	}

	Direction GetDirection() { return nowDirection; } //���݂̐i�s�����̎擾
};

Player::Player() :isUpdate(true), isDraw(true), center(7), rad(1), posX(13 * TILE + (TILE - 1)), posY(23 * TILE + (TILE - 1) / 2), move(new Moving(this)), foodCount(0), foodCountTotal(0), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")) {}
Player::~Player() { delete move; }

void Player::Update() {
	if (isUpdate) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		move->Update();
		
	}
}
void Player::Draw() {
	if (isDraw) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		//�摜�T�C�Y-1�̔���(�����_�؂�̂�)�������ĕ`�ʂ��鎖�Ń}�X�̒��S�ʒu�ɂ���ꍇ�\�������̃}�X�̒��S�ʒu�ƂȂ�
		Direction angle = move->GetDirection(); //���݂̐i�s����
		DrawRotaGraph3(SHIFT_X + (posX - ClculatCenterX(angle)) * X_RATE, SHIFT_Y + (posY - ClculatCenterY(angle)) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
	}
}

int Player::ClculatCenterX(Direction angle) const { return center + rad * std::sin((360 - 90 * (int)angle) * (PI / 180)); }  //�e������ɍ��킹��rad�̕�����ς��鎖�Œ��S���W�̐������s��
int Player::ClculatCenterY(Direction angle) const { return center + rad * std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int Player::ClculatLocalX(Direction angle) const {
	int raw = posX + ClculatCenterX(angle); //x�̒��S�ʒu���o��
	int sub = raw / TILE; //�}�X���W���o��
	//return raw - sub * TILE; //�}�X���W��ʏ���W�ɖ߂����Ń}�X�̍���ʏ���W�����܂�x���S�ʒu��������΃}�X���̈ʒu������o����
	return raw % TILE;
}
int Player::ClculatLocalY(Direction angle) const {
	int raw = posY + ClculatCenterY(angle);
	int sub = raw / TILE;
	//return raw - sub * TILE;
	return raw % TILE;
}
int Player::ClculatTileX(Direction angle) const { return (posX + ClculatCenterX(angle)) / TILE + WARP_AREA_X; }
int Player::ClculatTileY(Direction angle) const { return (posY + ClculatCenterY(angle)) / TILE + WARP_AREA_Y; }