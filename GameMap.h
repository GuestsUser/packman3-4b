#pragma once
#include <unordered_map>
#include <string>
class Grid;
class Food;
class Scene;

class GameMap {
	class Staging; //ステージ用演出クラス

	Scene* parent;
	Staging* staging; //READY!等の演出を纏めた内部クラス
	Grid** tile; //マップの二次元配列
	int map; //マップの画像ハンドル
	std::unordered_map<std::string, Food*>* food; //エサを保持する配列
public:
	GameMap(Scene* set);
	~GameMap();

	void Update();
	void Draw();

	
};