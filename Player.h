#pragma once
#include "Grid.h"
#include <unordered_map>
#include <string>

class Food;

class Player {
	class Moving; //動作用内部クラス

	int* playerImg; //パックマン画像ハンドル
	int* killImg; //死亡モーション
	int* score; //スコアの参照
	int* highScore; //ハイスコアの参照

	bool isUpdate; //falseでupdate実行禁止
	bool isDraw; //上記のdraw版
	int posX, posY; //描写用座標、描写用座標はグリッド添え字から出した座標と速度によって動いたドットを加えた描写に必要な各種加工を行えばその位置に表示が可能な座標を入れている
	Moving* move; //動作クラス実体
	int rad; //各種向きにより中心座標を動かす為に加減算する半径の値
	int center; //xy共通の中心座標
	int renderCenter; //xy共通中心だがこちらは描写用

	int foodCount; //今回の残機で食べたエサ個数
	int foodCountTotal; //エサを食べた合計個数
	std::unordered_map<std::string, Food*>* food; //エサやフルーツの配列
	Grid** tile;

	int actIndex = 0;			
	int maxMotion = 4;			//アニメーションの数（4段階）
	int motionIndex;			//
	const int actSpeed = 2;		//アニメーションの速さ設定
	int actWait;				//アニメーションの待ち時間

	int animX;
	int animY;
	int diecount;
	int killnum;

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

	int GetPosX() const { return posX; }
	int GetPosY() const { return posY; }
	int GetCenter() const { return center; }
	int ClculatCenterRadX(Direction angle)const; //各種方向における中心x座標を返してくれる
	int ClculatCenterRadY(Direction angle)const; //上記のy版
	int ClculatLocalX(Direction angle)const; //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
	int ClculatLocalY(Direction angle)const; //上記のy版
	int ClculatTileX(Direction angle)const; //現在マスを返してくれる
	int ClculatTileY(Direction angle)const; //上記のy版
	Direction GetDirection()const; //現在移動方向を返す

	Move GetTileMovable(int x, int y, Direction get) const { return tile[x][y].ReadPlayer()[(int)get]; } //指定タイルの指定方向の移動可否を返す
	void DieAnim();
};