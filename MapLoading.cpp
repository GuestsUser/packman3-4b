#include "MapLoading.h"
#include "Grid.h"
#include "Worldval.h"
#include <deque>

void MapLoading() {
	Grid** grid = new Grid * [31]; //縦
	for (int i = 0; i < 31; ++i) { grid[i] = new Grid[36]; } //横、通常は28マスだが左右端のワープトンネルが画面外に4マスで系36マス

	//ここに1マスずつ移動可能方向を記してゆく……
	//Gridは初期化段階では全ての状態において四方向移動不能に設定されてるのでパックマンも敵も立ち入れない場所は設定しなくていい
	//下の関数はマス座標(1,2)のマスを、パックマン、敵、イジケ状態のみが下、右に動ける設定をしている(dequeは可変長引数、vectorのような物)

	//5列目(指定位置のみの処理)
	grid[5][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][5].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//6列目
	grid[6][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[6][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[6][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//7列目
	grid[7][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[7][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[7][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//8列目
	grid[8][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[8][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[8][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//9列目
	grid[9][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[9][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[9][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//10列目
	grid[10][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][8].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//11列目
	grid[11][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[11][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//12列目
	grid[12][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[12][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//13列目
	grid[13][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][11].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//14列目
	grid[14][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[14][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//15列目
	grid[15][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[15][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//16列目
	grid[16][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][8].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//17列目
	grid[17][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[17][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});

	WorldVal::Set("map", grid); //精製したグリッドをmapという名前で全体に共有する
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //全体領域からマップの取得
	for (int i = 0; i < 31; ++i) { delete[] grid[i]; } //各要素の削除
	delete[] grid; //全体の削除
}