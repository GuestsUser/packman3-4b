#include "MapLoading.h"
#include "Grid.h"
#include "Worldval.h"
#include "ConstVal.h"
#include <deque>

void MapLoading() {
	Grid** grid = new Grid * [AREA_X + WARP_AREA_X * 2]; //横、通常は28マスだが左右端のワープトンネルが画面外に4マスで系36マス
	for (int i = 0; i < AREA_X + WARP_AREA_X * 2; ++i) { grid[i] = new Grid[AREA_Y + WARP_AREA_Y]; } //縦

	//ここに1マスずつ移動可能方向を記してゆく……
	//Gridは初期化段階では全ての状態において四方向移動不能に設定されてるのでパックマンも敵も立ち入れない場所は設定しなくていい
	//下の関数はマス座標(1,2)のマスを、パックマン、敵、イジケ状態のみが下、右に動ける設定をしている(dequeは可変長引数、vectorのような物)

	//0列目（完了）
	grid[0][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//1列目（完了）
	grid[1][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//2列目（完了）
	grid[2][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//3列目（完了）
	grid[3][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//4列目（完了）
	grid[4][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//5列目（完了）
	grid[5][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][5].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][20].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][23].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][26].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][29].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//6列目（完了）
	grid[6][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//7列目（完了）
	grid[7][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][23].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][26].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//8列目（完了）
	grid[8][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//9列目（完了）
	grid[9][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//10列目（完了）
	grid[10][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][8].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][14].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][17].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][20].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][23].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][26].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//11列目（完了）
	grid[11][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//12列目（完了）
	grid[12][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//13列目（完了）
	grid[13][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][11].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][14].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][17].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][20].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][23].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][26].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//14列目（完了）
	grid[14][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//15列目（完了）
	grid[15][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//16列目（完了）
	grid[16][1].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][8].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});	//左上一方通行
	grid[16][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][20].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][23].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //左下一方通行
	grid[16][26].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][29].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//17列目（完了）
	grid[17][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[17][11].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::d});	//やられ状態
	grid[17][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//やられ状態
	grid[17][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//やられ状態
	grid[17][14].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::d});	//やられ状態
	grid[17][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//18列目（完了）
	grid[18][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[18][11].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::d});	//やられ状態
	grid[18][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//やられ状態
	grid[18][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//やられ状態
	grid[18][14].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::d});	//やられ状態
	grid[18][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//19列目（完了）
	grid[19][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][8].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //右上一方通行
	grid[19][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][20].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][23].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //右下一方通行
	grid[19][26].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][29].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//20列目（完了）
	grid[20][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//21列目（完了）
	grid[21][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//22列目（完了）
	grid[22][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][8].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][11].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][14].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][17].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][20].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][23].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][26].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//23列目（完了）
	grid[23][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//24列目（完了）
	grid[24][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//25列目（完了）
	grid[25][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][8].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][14].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][17].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][20].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][23].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][26].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//26列目（完了）
	grid[26][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//27列目（完了）
	grid[27][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//28列目（完了）
	grid[28][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][23].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][26].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//29列目（完了）
	grid[29][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//30列目（完了）
	grid[30][1].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][5].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][8].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][20].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][23].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][26].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][29].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//31列目（完了）
	grid[31][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//32列目（完了）
	grid[32][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//33列目（完了）
	grid[33][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//34列目（完了）
	grid[34][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//35列目（完了）
	grid[35][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	WorldVal::Set("map", grid); //精製したグリッドをmapという名前で全体に共有する
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //全体領域からマップの取得
	for (int i = 0; i < 36; ++i) { delete[] grid[i]; } //各要素の削除
	delete[] grid; //全体の削除
}