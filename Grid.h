#pragma once

enum class Direction { up, left, down, right }; //移動方向
enum class Move { movable, block }; //movable=移動可能 block=移動不可

class Grid {
	Move player[4];
	Move enemy[4];
	//イジケ状態、やられ状態の敵のMoveも定義する、これを書いた時に定義しなかったのはイジケ状態にどういうスペルを振ればいいか思いつかなかったから

public:
	Grid();
};