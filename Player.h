#pragma once
#include "Grid.h"
#include <unordered_map>
#include <string>

class Food;

class Player {
	class Moving; //動作用内部クラス

	int* playerImg; //パックマン画像ハンドル
	int* killImg; //死亡モーション
	bool isUpdate; //falseでupdate実行禁止
	bool isDraw; //上記のdraw版
	int subX, subY, drawX, drawY; //グリッドの添え字と描写用座標、描写用座標はグリッド添え字から出した座標と速度によって動いたドットを加えた描写に必要な各種加工を行えばその位置に表示が可能な座標を入れている
	int speed; //速度、現在は状態によらず一定な仮の物
	int speedCount; //速度の蓄積状況記録、毎フレームこれにspeedを加算し、speedCount/MOVABLE_SPEEDの値分描写座標を動かす
	Direction nowDirection; //現在の進行方向
	Direction lastInput; //最後の入力方向保持
	Moving* xMove; //動作クラス実体、x用
	Moving* yMove; //y用

	int foodCount; //今回の残機で食べたエサ個数
	int foodCountTotal; //エサを食べた合計個数
	std::unordered_map<std::string, Food*>* food; //エサやフルーツの配列
	Grid** tile;

	//初期位置 x14+4(ワープトンネル分) y23

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }
};