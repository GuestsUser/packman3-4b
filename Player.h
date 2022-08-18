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