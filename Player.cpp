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
	if (isUpdate) { //bool変数に停止命令(false)が入れられている場合実行しない

		//入力方向の変更処理、方向を押した瞬間、押されっぱなし何れかで入力方向を新しい物に交換する
		//左スティック、十字キーの両方から入力を取る
		//現在は同時押しされた場合優先を「上>左>下>右」の順にする為処理順を「右,下,左,上」の優先とは逆順で行っている(逆順にする事で優先度の低い方向を後から高い方で上書きできる)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }
		
		speedCount += speed;

	}
}
void Player::Draw() {
	if (isDraw) { //bool変数に停止命令(false)が入れられている場合実行しない
		//xはそのまま左上原点描写、yはプレイヤー画像サイズとタイルサイズの違いからタイルの半分だけ上にずらして描写を行っている
		DrawRotaGraph3(SHIFT_X + (drawX - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (drawY - WARP_AREA_Y * TILE - TILE / 2) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
	}
}