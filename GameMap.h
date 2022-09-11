#pragma once
#include <unordered_map>
#include <string>

class Grid;
class Food;
class Game;
class Player;

class GameMap {
	class Staging; //ステージ用演出クラス

	Game* parent;
	Staging* staging; //READY!等の演出を纏めた内部クラス
	Grid** tile; //マップの二次元配列
	Player* player;
	int map; //マップの画像ハンドル
	std::unordered_map<std::string, Food*>* food; //エサを保持する配列
	bool push;
	static bool Missflg;
public:
	GameMap(Game* set,Player* pacman);
	~GameMap();
	void Miss();
	void Restart();
	void Update();
	void Draw();

	
};