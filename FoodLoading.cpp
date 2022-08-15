#include "Food.h"
#include "FoodLoading.h"
#include "Worldval.h"
#include <unordered_map>
#include <string>

void FoodLoading() { //エサやフルーツの作成処理
	std::unordered_map<std::string, Food*>* food = new std::unordered_map<std::string, Food*>();

	//MapLoading同様に240個分の配置をここに書いてゆく……
	//下記例はマス座標(3,2)の場所にパワーエサを配置する
	//引数を省略した場合通常エサになる
	//エサが必要な場所のみ配置する、マップ全マスに張り巡らせる必要はない
	//(*food)["3x2"] = new Food(Food::Type::big);

	WorldVal::Set("food", food);
	for (auto itr : *food) { itr.second->PosSetUp(itr.first); } //配列添え字から配置座標の決定
}
void FoodDel() { //削除処理
	auto food = WorldVal::Get<std::unordered_map<std::string, Food*>>("food");
	for (auto get : *food) { delete get.second; } //food実体の削除
	delete food; //全体の削除
}