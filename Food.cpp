#include "DxLib.h"
#include "Game.h"
#include "Food.h"
#include "ConstVal.h"
#include "Worldval.h"
#include "PowerModeProcess.h"
#include <string>

Food::Food(Type set) :type(set), isEnable(true), x(0), y(0), handle(*WorldVal::Get<int[10]>("foodImage")), count(0), foodCount(WorldVal::Get<int>("foodCountTotal")), fruitsCount(WorldVal::Get<int>("fruitsDisplay")), num(0){ if (type != Type::food && type != Type::big) { isEnable = false; fruitEnable = false; } } //setに使用したいタイプを入れる、何も指定しない場合通常エサになる

int Food::Eat() {
	isEnable = false; //食べられるとfalseになる
	if (!(type == Food::Type::food || type == Food::Type::big)) {
		fruitEnable = true;	//フルーツのみ食べるとtrueになる（スコア表示用）
		num = 0;
	}
	return GetPoint();
}

void Food::Update() {
	++count;
	if (!(type == Food::Type::food || type == Food::Type::big))
	{
		if (PowerModeProcess::GetIsPause()) {
			--count;
			return;
		}
		if (*fruitsCount == 0)
		{
			if (*foodCount == 70) {

				isEnable = true;
				count = 0;
				(*fruitsCount)++;
			}
		}
		else if (*fruitsCount == 1)
		{
			if (*foodCount == 170) {

				isEnable = true;
				count = 0;
				(*fruitsCount)++;
			}
		}

		if (count == 10 * FPS)
		{
			isEnable = false;
		}
	}

	DrawFormatString(0, 200, GetColor(0, 255, 0), "%d", *foodCount);

}

void Food::Draw() { //*8などのマスサイズは何処かに定数で宣言しておきたい
	//count++;
	//ゲームスタート前
	if (Game::GetSceneState() == Game::State::start) {
		if (isEnable) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}

	//ゲームオーバー中（タイトルに戻るまで）（パワーエサを消す）
	if (Game::GetSceneState() == Game::State::gameover) {
		if (isEnable) {
			if (type != Type::big) {
				DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
			}
		}
	}

	if (isEnable) {
		if (type == Type::food) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
		else if (type != Type::food && type != Type::big) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
		else if (type == Type::big && (count / 10) % 2 == 0) {
			DrawRotaGraph3(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - TILE / 2 - WARP_AREA_Y * TILE) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, handle[(int)type], true);
		}
	}

	if (fruitEnable == true) {
		num++;
		SetFontSize(18);
		if (num <= 120) {
			DrawFormatString(SHIFT_X + (x * TILE - TILE / 2 - WARP_AREA_X * TILE) * X_RATE, SHIFT_Y + (y * TILE - WARP_AREA_Y * TILE) * Y_RATE, GetColor(255, 187, 255), "%d", GetPoint());
		}
		else {
			fruitEnable = false;
		}
	}
	
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

//エサのスコアを受け取ることができる
int Food::GetPoint() {
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
	return point;
}