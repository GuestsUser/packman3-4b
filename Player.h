#pragma once
#include <unordered_map>
#include <string>

class Grid;
class Food;

class Player {
	int* playerImg; //パックマン画像ハンドル
	int* killImg; //死亡モーション
	bool isUpdate; //falseでupdate実行禁止
	bool isDraw; //上記のdraw版

	int foodCount; //今回の残機で食べたエサ個数
	int foodCountTotal; //エサを食べた合計個数
	std::unordered_map<std::string, Food*>* food; //エサやフルーツの配列
	Grid** tile;

public:
	Player();

};

//画像読み込み
//int* handle = new int[10];
//LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle); //画像読み込み
//WorldVal::Set("foodImage", handle);
// 
////LoadDivGraphの都合上毎回新しい領域をポインタ型変数に格納しないといけないのはネック
//handle = new int[12];
//LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, handle);
//WorldVal::Set("playerImage", handle);
//
//handle = new int[11];
//LoadDivGraph("Resource/image/dying.png", 11, 11, 1, 16, 16, handle);
//WorldVal::Set("killImage", handle);