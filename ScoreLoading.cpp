#include "ScoreLoading.h"
#include "Worldval.h"
#include "ConstVal.h"

void ScoreLoading() { //スコア、ハイスコアに使う変数の準備
	WorldVal::Set("score", new int(0));
	WorldVal::Set("highScore", new int(HIGH_SCORE_INI));
}
void ScoreDel() { //スコア、ハイスコア用変数の削除
	delete WorldVal::Get<int>("score");
	delete WorldVal::Get<int>("highScore");
}