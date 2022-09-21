#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include "DebugUtility.h"
#include "PowerModeProcess.h"
#include <unordered_map>
#include <string>
#include <math.h>
#include "DxLib.h"
#include "EnemyAra.h"

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
	void StopAdjust() { //��~�����̍ۍ��W����~�ʒu���I�[�o�[����\��������̂��Y��ɒ�~�ʒu�Ɏ~�߂鏈��
		int adjust = ((int)direction % 2 == 0 ? player->ClculatLocalY(direction) : player->ClculatLocalX(direction)) - 3; //�����ʒu��3����ǂꂾ������Ă��邩������
		*posEdit -= adjust;
	}
	bool IsMovable(int localPos)const { //���ݐi�s�����Ƀ}�X�����W���S���z�������A�i�s�\���ǂ������肷��
		bool minus = localPos >= 0 && localPos <= 3; //����͈͂ɓ����Ă����ꍇtrue
		bool plus = localPos >= 3 && localPos < 8;
		bool isMovable = player->GetTileMovable(player->ClculatTileX(direction), player->ClculatTileY(direction), direction) == Move::movable; //�ړ��\�������ꍇtrue
		return (int)((int)direction / 2) > 0 ? !(plus && (!isMovable)) : !(minus && (!isMovable));
	}

	int GetCenter() const { return center; }
	State GetState() const { return state; }
	Direction GetDirection() const { return direction; }
	const int* ReadPos() const { return posEdit; }
	const Player* const ReadPlayer() { return player; }

	//Player* EditPlayer() { return player; }
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
			if (!IsMovable(ReadPlayer()->ClculatLocalX(GetDirection()))) {
				StopAdjust();
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::curve:
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalX(GetDirection()))) { 
				//StopAdjust();
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool left = localPos <= 7 && localPos > 3;
		bool right = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ? right : left;
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
			if (!IsMovable(ReadPlayer()->ClculatLocalY(GetDirection()))) {
				StopAdjust();
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::curve:
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalY(GetDirection()))) {
				//StopAdjust();
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool up = localPos <= 7 && localPos > 3;
		bool down = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ?  down : up;
	}
};

class Player::Moving {
public:
private:
	Player* caller; //�Ăяo����
	Movable* x;
	Movable* y;
	EnemyAra* enemyara;
	Food* food;
	Player* player;
	int safeZone; //�}�X�����W��safeZone�`TILE-safeZone���łȂ��ƐV���ɋȂ��鎖���ł��Ȃ��A���ׂ̈̕ϐ�
	int speed; //���x�A���݂͏�Ԃɂ�炸���ȉ��̕�
	int speedCount; //���x�̒~�Ϗ󋵋L�^�A���t���[�������speed�����Z���AspeedCount/MOVABLE_SPEED�̒l���`�ʍ��W�𓮂���
	Direction nowDirection; //���݂̐i�s����
	Direction lastInput; //�Ō�̓��͕����ێ�

	int oldX, oldY; //��xy�}�X���W

	void ChangeSpeed();
public:
	Moving(Player* player) :caller(player), oldX(0), oldY(0), safeZone(2), speed(16), speedCount(0), nowDirection(Direction::left), lastInput(nowDirection), x(new XMove(&caller->posX, caller)),y(new YMove(&caller->posY, caller)) {
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

		//���[�v�g���l������
		if (caller->ClculatTileX(nowDirection) < 0) { caller->posX = (AREA_X + WARP_AREA_X) * TILE - (caller->center + caller->ClculatCenterRadX(nowDirection) + (8 - caller->ClculatLocalX(nowDirection))); }
		if (caller->ClculatTileX(nowDirection) >= AREA_X + WARP_AREA_X * 2) { caller->posX = -WARP_AREA_X * TILE + (caller->center + caller->ClculatCenterRadX(nowDirection) + caller->ClculatLocalX(nowDirection) + 1); }

		while (nowDirection != lastInput) { //while���𗘗p�����̂�break��K���Ȉʒu�ɑ}�����鎖��else���������鎖���ړI�A���[�v����������ł͂Ȃ�
			int subX = caller->ClculatTileX(nowDirection); //���S���W�������������݂̏����}�Xx
			int subY = caller->ClculatTileY(nowDirection); //��L��y��
			bool yCurve = (int)lastInput % 2 == 0; //�V�����������㉺���ꂩ�ɂȂ�ꍇtrue
			Movable* end = yCurve ? x : y; //�ړ�������߂鎲
			Movable* start = yCurve ? y : x; //�V�����ړ����n�߂鎲

			if ((Direction)(((int)nowDirection + 2) % 4) == lastInput) { //���͕��������Ε����������ꍇ
				nowDirection = lastInput; //��������͂̂����������ɕύX
				start->SetDirection(nowDirection); //�V���������̐ݒ�
				start->SetState(Movable::State::run); //�Փ˓��ňړ��I���ɂȂ��Ă�\��������̂�run�ɍĐݒ�
				break; //�ȍ~��while���������͎��s���Ȃ�
			}
			int localX = caller->ClculatLocalX(lastInput); //���݃}�X���ł̈ʒu�A�V���������ɍ��킹����
			int localY = caller->ClculatLocalY(lastInput); //��L��y��

			//���Lif����while��p���Ȃ��ꍇ����q�ɂ��邩1��if�������ɂ܂Ƃ߂邩�ɂȂ����̂ő������₷���Ȃ����c����
			if ((!yCurve) && (!y->IsCurveInRange(localY))) { break; }
			if (yCurve && (!x->IsCurveInRange(localX))) { break; }
			//if (localX < safeZone - 1 || localX > TILE - safeZone) { break; } //�͈͊O����Atrue�Ȃ�I��
			//if (localY < safeZone - 1 || localY > TILE - safeZone) { break; } //��L��y��
			if (x->GetState() == Movable::State::curve || y->GetState() == Movable::State::curve) { break; } //�ǂ��炩�̃^�X�N���J�[�u�ړ����������ꍇ
			if (caller->tile[subX][subY].ReadPlayer()[(int)lastInput] == Move::block) { break; } //�ړ��������������ړ��s�������ꍇ

			//�����܂ŗ����΁A�����]���\��ɓ����Ă��銎�ǂ̕������J�[�u���ł͂Ȃ��A�Ō�ɓ��͂̂������������ړ��\�ł���
			end->SetDirection((Direction)(((((int)nowDirection % 2) + 1) % 2) + (int)((int)nowDirection / 2) * 2)); //2�Ŋ��������o�Ă����������������xy�������Ⴄ�����ɕύX
			nowDirection = lastInput; //��������͂̂����������ɕύX

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
		ChangeSpeed();
	}

	Direction GetDirection() { return nowDirection; } //���݂̐i�s�����̎擾
};

void Player::Moving::ChangeSpeed() {
	DrawFormatString(0, 150, GetColor(255, 0, 0), "%d", speed);

	int x = caller->ClculatTileX(caller->move->GetDirection());
	int y = caller->ClculatTileY(caller->move->GetDirection());
	if (oldX == x && oldY == y) { return; } //�}�X�ړ����Ȃ������ꍇ���x�ύX�͖���
	oldX = x; //�V�������ɍX�V
	oldY = y;

	Player::State playerState = caller->GetState();
	std::string sub = std::to_string(x) + "x" + std::to_string(y); //�G�T�A�z�z��擾�p�Y����
	auto itr = caller->food->find(sub); //�G�T�z����Ɏw��Y�������L�[�Ɏ��G�T�����邩���ׂ�
	int eatspeed = 0;
	if (itr != caller->food->end() && itr->second->GetEnable()) {//�w��ʒu�ɃG�T���z�u����Ă��銎�G�T���H�ׂ����Ԃł���ꍇ
		Food::Type type = itr->second->GetType(); //�H�ׂ����̎��
		if (type == Food::Type::food) { eatspeed = 1; }
		if (type == Food::Type::big) { eatspeed = 2; }

	}
	
	switch (enemyara->ClculatSpeedLevel()) { //���x���ɍ��킹�����x��
	case 0:
		if (playerState == Player::State::neutral) {
			if (eatspeed == 0) { speed = 16; }//�����H�ׂĂȂ���
			if (eatspeed == 1) { speed = 15; }//�ʏ�G�T��H�ׂ���
			if (eatspeed == 2) { speed = 13; }//�p���[�G�T��H�ׂ���
		}
		if (playerState == Player::State::power) {//�t�]���Ă鎞
			if (eatspeed == 0) { speed = 18; }//�����H�ׂĂȂ���
			if (eatspeed == 1) { speed = 17; }//�ʏ�G�T��H�ׂ���
			if (eatspeed == 2) { speed = 15; }//�p���[�G�T��H�ׂ���
		}
		break;
	case 1:
		if (playerState == Player::State::neutral) {
			if (eatspeed == 0) { speed = 18; }//�����H�ׂĂȂ���
			if (eatspeed == 1) { speed = 17; }//�ʏ�G�T��H�ׂ���
			if (eatspeed == 2) { speed = 15; }//�p���[�G�T��H�ׂ���
		}
		if (playerState == Player::State::power) {//�t�]���Ă鎞
			if (eatspeed == 0) { speed = 19; }//�����H�ׂĂȂ���
			if (eatspeed == 1) { speed = 18; }//�ʏ�G�T��H�ׂ���
			if (eatspeed == 2) { speed = 16; }//�p���[�G�T��H�ׂ���
		}
		break;
	case 2:
		if (eatspeed == 0) { speed = 20; }//�����H�ׂĂȂ���
		if (eatspeed == 1) { speed = 19; }//�ʏ�G�T��H�ׂ���
		if (eatspeed == 2) { speed = 17; }//�p���[�G�T��H�ׂ���
		break;
	case 3:
		if (eatspeed == 0) { speed = 18; }//�����H�ׂĂȂ���
		if (eatspeed == 1) { speed = 17; }//�ʏ�G�T��H�ׂ���
		if (eatspeed == 2) { speed = 15; }//�p���[�G�T��H�ׂ���
		break;
	}
}

Player::Player() :isUpdate(false), isDraw(true), renderCenter(3), center(3), rad(1), posX(13 * TILE + (TILE - 3)), posY(23 * TILE), move(new Moving(this)), state(State::neutral), foodCount(0),start(WorldVal::Get<int>("start")) ,life(WorldVal::Get<int>("Life")) , foodCountTotal(WorldVal::Get<int>("foodCountTotal")), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")), score(WorldVal::Get<int>("score")), highScore(WorldVal::Get<int>("highScore")), diecount(0), killnum(0),eatSE1(*WorldVal::Get<int>("eatSE1")), eatSE2(*WorldVal::Get<int>("eatSE2")), dieSE(*WorldVal::Get<int>("dieSE")), fruitSE(*WorldVal::Get<int>("fruitSE")), extendSE(*WorldVal::Get<int>("extendSE")) {}
Player::~Player() { delete move; }

void Player::Update() {
	int* lifeUp;
	lifeUp = WorldVal::Get<int>("lifeUp");
	int* activeFoodCount;
	activeFoodCount = WorldVal::Get<int>("activeFoodCount");
	if (isUpdate) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		move->Update();
		int* life;
		life = WorldVal::Get<int>("Life");
		std::string sub = std::to_string(ClculatTileX(move->GetDirection())) + "x" + std::to_string(ClculatTileY(move->GetDirection())); //�G�T�A�z�z��擾�p�Y����
		auto itr = food->find(sub); //�G�T�z����Ɏw��Y�������L�[�Ɏ��G�T�����邩���ׂ�
		if (itr != food->end() && itr->second->GetEnable()) { //�w��ʒu�ɃG�T���z�u����Ă��銎�G�T���H�ׂ����Ԃł���ꍇ
			*score += itr->second->Eat(); //�G�T��H�ׂ�
			Food::Type type = itr->second->GetType(); //�H�ׂ����̎��
			
			if (type == Food::Type::food || type == Food::Type::big) { //��ނ��G�T�A�p���[�G�T�̏ꍇ�H�ׂ������J�E���g����
				++foodCount;
				++(*activeFoodCount);
				++(*foodCountTotal);
				if (foodCount % 2 == 0) {
					PlaySoundMem(eatSE1, DX_PLAYTYPE_BACK);
				}
				else {
					PlaySoundMem(eatSE2, DX_PLAYTYPE_BACK);
				}
			}
			else {
				PlaySoundMem(fruitSE, DX_PLAYTYPE_BACK);
			}
			if (type == Food::Type::big) { PowerModeProcess::PowerModeStart(); } //�p���[�G�T�̎擾�ŋt�]��Ԃɂ���
			if (*score >= *highScore) { *highScore = *score; } //�n�C�X�R�A���l���傫���Ȃ����ꍇ�n�C�X�R�A�̒l���X�V����
			if (*score - i >= EXTEND_QUOTA &&  EXTEND_LIMIT > *lifeUp) {/*score��EXTEND_LIMIT���傫�����c�@�A�b�v�����񐔂�EXTEND_LIMIT��菭�Ȃ�������c�@�A�b�v*/
				*lifeUp += 1;
				*life += 1;
				i += 10000;
				PlaySoundMem(extendSE, DX_PLAYTYPE_BACK);
			}
		}
	}
	DrawFormatString(400, 50, GetColor(255, 255, 255), "�G�T%d", *activeFoodCount);
}

void Player::Draw() {
	if (isDraw) { //bool�ϐ��ɒ�~����(false)��������Ă���ꍇ���s���Ȃ�
		//�摜�T�C�Y-1�̔���(�����_�؂�̂�)�������ĕ`�ʂ��鎖�Ń}�X�̒��S�ʒu�ɂ���ꍇ�\�������̃}�X�̒��S�ʒu�ƂȂ�

		int actMotion[] = { 0,1,2,1, };
		Direction angle = move->GetDirection(); //���݂̐i�s����
		int moveAnim = (int)move->GetDirection() * 3;

		if (isUpdate) {
			//�p�b�N�}�����c�܂��͉��Ɉړ����Ă��鎞
			if (posX - animX != 0 || posY - animY != 0) {
				//�ړ��A�j������
				if (--actWait <= 0) {
					actIndex++;
					actWait = actSpeed;
					actIndex %= maxMotion;
				}
			}
			else {
				if (actIndex == 0) {
					actIndex += 2;
				}
			}

			animX = posX;
			animY = posY;
		}

		motionIndex = actMotion[actIndex] + moveAnim;



		DrawFormatString(0, 10, GetColor(255, 255, 255), "%2d", motionIndex);
		//DrawCircle(SHIFT_X + (posX + ClculatCenterRadX(angle)) * X_RATE, SHIFT_Y + (posY+ ClculatCenterRadY(angle)) * Y_RATE,65 * X_RATE,GetColor(0,255,0),false);
		if ((*foodCountTotal) != 244) {
			DrawRotaGraph3(SHIFT_X + (posX - renderCenter + ClculatCenterRadX(angle)) * X_RATE, SHIFT_Y + (posY - renderCenter + ClculatCenterRadY(angle)) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[motionIndex], true);
		}
		else {
			DrawRotaGraph3(SHIFT_X + (posX - renderCenter + ClculatCenterRadX(angle)) * X_RATE, SHIFT_Y + (posY - renderCenter + ClculatCenterRadY(angle)) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
		}

		//DrawHitBox(ClculatTileX(angle), ClculatTileY(angle), GetColor(255, 189, 78)); //�f�o�b�O�\��
	}
}

int Player::ClculatCenterRadX(Direction angle) const { return rad * std::sin((360 - 90 * (int)angle) * (PI / 180)); }  //�e������ɍ��킹��rad�̕�����ς��鎖�Œ��S���W�̐������s��
int Player::ClculatCenterRadY(Direction angle) const { return rad * std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int Player::ClculatLocalX(Direction angle) const {
	int raw = posX + center + ClculatCenterRadX(angle); //x�̒��S�ʒu���o��
	int sub = raw / TILE; //�}�X���W���o��
	//return raw - sub * TILE; //�}�X���W��ʏ���W�ɖ߂����Ń}�X�̍���ʏ���W�����܂�x���S�ʒu��������΃}�X���̈ʒu������o����
	return raw % TILE;
}
int Player::ClculatLocalY(Direction angle) const {
	int raw = posY + center + ClculatCenterRadY(angle);
	int sub = raw / TILE;
	//return raw - sub * TILE;
	return raw % TILE;
}
int Player::ClculatTileX(Direction angle) const { return (posX + center + ClculatCenterRadX(angle)) / TILE + WARP_AREA_X; }
int Player::ClculatTileY(Direction angle) const { return (posY + center + ClculatCenterRadY(angle)) / TILE + WARP_AREA_Y; }

Direction Player::GetDirection()const { return move->GetDirection(); }

void Player::DieAnim()
{
	isUpdate = false;
	isDraw = false;
	diecount++;
	if (diecount == 1) {
		PlaySoundMem(dieSE, DX_PLAYTYPE_BACK);
	}
	DrawRotaGraph3(SHIFT_X + (posX - renderCenter) * X_RATE, SHIFT_Y + (posY - renderCenter) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, killImg[killnum], true);

	if (diecount % 7 == 0)
	{
		killnum++;
	}
}
void Player::Restart() {
}