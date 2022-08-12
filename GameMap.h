#pragma once
class Grid;

class GameMap {
	class Staging; //ステージ用演出クラス

	Staging* staging; //READY!等の演出を纏めた内部クラス
	Grid** tile; //マップの二次元配列
	int map; //マップの画像ハンドル
public:
	GameMap();
	~GameMap();

	void Update();
	void Draw();

	
};