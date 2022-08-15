#pragma once
#include <string>

class Food {
public:
	enum class Type { food, big, cherry, strawberry, orange, apple, melon, galaxian, bell, key };
private:
	Type type; //エサの種類
	bool isEnable; //trueならこのエサはまだ食べられてない
	int handle[10]; //画像ハンドル
	int x; //マス座標x
	int y; //上記のy
public:
	Food(Type set = Type::food); //setに使用したいタイプを入れる、何も指定しない場合通常エサになる
	int Eat(); //エサの除去、返り値は食べたエサの得点
	Type GetType() { return type; } //エサのタイプを返す

	void Update();
	void Draw();

	void PosSetUp(const std::string& set); //unordered_map用添え字から座標を取り出す関数
	//フルーツが時限で消えるとかパワーエサが点滅するとかはまた後で……
};