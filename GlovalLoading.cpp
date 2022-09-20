#include "GlovalLoading.h"
#include "Worldval.h"

void GlovalLoading() { //色々な全体向け変数の準備
	WorldVal::Set("foodCountTotal", new int(0)); //そのシーンでの食べたエサ個数
	WorldVal::Set("fruitsDisplay", new int(0)); //そのシーンでの表示させた個数
	WorldVal::Set("Life", new int(3)); //そのシーンでの食べたエサ個数
	WorldVal::Set("start", new int(0)); //そのシーンでの食べたエサ個数
	WorldVal::Set("nowStage", new int(0)); //現在のステージ数、0スタート
	WorldVal::Set("dieCount", new int(0)); //そのステージでやられた数
	WorldVal::Set("activeFoodCount", new int(0)); //そのライフでエサを食べたかず
	WorldVal::Set("enemyActive", new int(0)); //Game.cppで使用している敵の種類判定用

}