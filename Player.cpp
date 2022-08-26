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
	Player* caller; //呼び出し元
	Mode type; //x,yどちらの方向を使用するか

	int speed; //速度、現在は状態によらず一定な仮の物
	int speedCount; //速度の蓄積状況記録、毎フレームこれにspeedを加算し、speedCount/MOVABLE_SPEEDの値分描写座標を動かす
	Direction nowDirection; //現在の進行方向
	Direction lastInput; //最後の入力方向保持
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
	if (isUpdate) { //bool変数に停止命令(false)が入れられている場合実行しない

		Direction old = lastInput; //今までの入力方向記憶用
		//入力方向の変更処理、方向を押した瞬間、押されっぱなし何れかで入力方向を新しい物に交換する
		//左スティック、十字キーの両方から入力を取る
		//現在は同時押しされた場合優先を「上>左>下>右」の順にする為処理順を「右,下,左,上」の優先とは逆順で行っている(逆順にする事で優先度の低い方向を後から高い方で上書きできる)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }
		
		if (old != lastInput) { //今までと違う方向に入力が確認された場合

		}

		speedCount += speed;
		tile[subX][subY].ReadPlayer()[(int)lastInput] == Move::block;

		int* edit = (int)nowDirection % 2 == 0 ? &posY : &posX; //余りが0の場合上下(y方向) 1なら左右(x方向)を操作する為のエイリアス
		*edit += speedCount / MOVABLE_SPEED * (-1 + 2 * (((int)nowDirection) / 2)); //値が2以上の場合xだろうがyだろうか加算方向に動く、それ以下なら減算方向という仕組み
		speedCount -= speedCount / MOVABLE_SPEED * MOVABLE_SPEED; //移動に使った分のドットを取り除く

		if (subX != posX / TILE || subY != posY / TILE) { //マス移動があった場合

		}
	}
}
void Player::Draw() {
	if (isDraw) { //bool変数に停止命令(false)が入れられている場合実行しない
		//画像サイズ-1の半分(小数点切り捨て)を引いて描写する事でマスの中心位置にいる場合表示もそのマスの中心位置となる
		DrawRotaGraph3(SHIFT_X + (posX - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (posY - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
	}
}