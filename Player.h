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
	int subX, subY, drawX, drawY; //グリッドの添え字と描写用座標、描写用座標は拡大率を適用していない、Drawの方で適用する
	int speedCount; //速度の蓄積状況記録、毎フレームこれにspeedを加算し、speedCount/MOVABLE_SPEEDの値分描写座標を動かす

	int foodCount; //今回の残機で食べたエサ個数
	int foodCountTotal; //エサを食べた合計個数
	std::unordered_map<std::string, Food*>* food; //エサやフルーツの配列
	Grid** tile;

	//初期位置 x14+4(ワープトンネル分) y23

public:
	Player();

	void Update();
	void Draw();

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }
};