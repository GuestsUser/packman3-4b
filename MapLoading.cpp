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
	//grid[1][2].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});


	WorldVal::Set("map", grid); //精製したグリッドをmapという名前で全体に共有する
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //全体領域からマップの取得
	for (int i = 0; i < 31; ++i) { delete[] grid[i]; } //各要素の削除
	delete[] grid; //全体の削除
}