#include "DxLib.h"
#include "Game.h"
#include "Food.h"
#include "ConstVal.h"
#include "Worldval.h"
#include <string>

Food::Food(Type set) :type(set), isEnable(true), x(0), y(0), handle(*WorldVal::Get<int[10]>("foodImage")) ,count(0){  } //setに使用したいタイプを入れる、何も指定しない場合通常エサになる

int Food::Eat() {
	int point = 0;
	switch (type) { //自身のタイプに応じて得点を返す
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
	isEnable = false; //食べられるとfalseになる
	return point;
}

void Food::Update() {

}

void Food::Draw() { //*8などのマスサイズは何処かに定数で宣言しておきたい
	if (Game::GetSceneState() == Game::State::start) { //スタート時の場合

	}
	//ゲームスタート前
	if (isEnable) {
		DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
	}

	//ゲームスタート中（画面が切り替わるまで）
	if (isEnable) { 
		if (type != Type::big) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
		else if (type == Type::big && (count / 10) % 2 == 0) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}

	//ゲームオーバー中（タイトルに戻るまで）（パワーエサを消す）
	if (isEnable) {
		if (type != Type::big) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}
	count++;
}

void Food::PosSetUp(const std::string& set) { //unordered_map用添え字から座標を取り出す関数
	int size = set.length();
	for (int i = 0; i < size; ++i) {
		if (set[i] == *"x") { //区切り文字が見つかった場合
			x = std::stoi(set.substr(0, i)); //前半がx
			y = std::stoi(set.substr(i + 1, size)); //後半がy
			return;
		}
	}
	//区切りが見つからなかった場合特に何も代入されない
}