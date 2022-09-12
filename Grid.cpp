#include "Grid.h"

//Grid::Grid() :
//	player{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	enemy{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	cringe{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	damage{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	wait{ Move::movable,Move::movable ,Move::movable ,Move::movable }{ } //初期化、全ての状態の移動可能方向をブロックする

Grid::Grid() :
	player{ Move::block,Move::block ,Move::block ,Move::block },
	enemy{ Move::block,Move::block ,Move::block ,Move::block },
	cringe{ Move::block,Move::block ,Move::block ,Move::block },
	damage{ Move::block,Move::block ,Move::block ,Move::block },
	wait{ Move::block,Move::block ,Move::block ,Move::block }{ } //初期化、全ての状態の移動可能方向をブロックする

void Grid::Set(Move up, Move left, Move down, Move right, std::deque<Chara> set) {
	Move moveData[4] = { up,left,down,right }; //新しい移動方向設定
	if (set.size() <= 0) { //setの引数省略は全指定扱い(デフォルト実引数ではstatic以外のクラス内オブジェクトを引数に取れないのでこっちで定義した感じ)
		for (int i = 0; i < 4; ++i) { 
			player[i] = moveData[i];
			enemy[i] = moveData[i];
			cringe[i] = moveData[i];
			damage[i] = moveData[i];
			wait[i] = moveData[i];
		}
		return;
	}
	for (Chara get : set) { //指定状態に移動方向を設定する
		Move* edit = nullptr;
		switch (get) { //set内で指定されたキャラクターの移動方向を設定する
		case Chara::p: edit = player; break;
		case Chara::e: edit = enemy; break;
		case Chara::c: edit = cringe; break;
		case Chara::d: edit = damage; break;
		case Chara::w: edit = wait; break;
		}
		for (int i = 0; i < 4; ++i) { edit[i] = moveData[i]; } //アドレス置き換えだとスコープ抜けで消滅しそうだから値のループコピー
	}
}