#include "Food.h"
#include "FoodLoading.h"
#include "Worldval.h"
#include <unordered_map>
#include <string>

void FoodLoading() { //�G�T��t���[�c�̍쐬����
	std::unordered_map<std::string, Food*>* food = new std::unordered_map<std::string, Food*>();

	//MapLoading���l��240���̔z�u�������ɏ����Ă䂭�c�c
	//���L��̓}�X���W(1,1)�̏ꏊ�Ƀp���[�G�T��z�u����
	//�������ȗ������ꍇ�ʏ�G�T�ɂȂ�
	//�G�T���K�v�ȏꏊ�̂ݔz�u����A�}�b�v�S�}�X�ɒ��菄�点��K�v�͂Ȃ�
	//(*food)["1x1"] = new Food(Food::Type::big);
	//(*food)["2x1"] = new Food();
	//(*food)["3x1"] = new Food();

	//�G�T,�p���[�G�T�̔z�u
	//5���
	(*food)["5x1"] = new Food();
	(*food)["5x2"] = new Food();
	(*food)["5x3"] = new Food(Food::Type::big);
	(*food)["5x4"] = new Food();
	(*food)["5x5"] = new Food();
	(*food)["5x6"] = new Food();
	(*food)["5x7"] = new Food();
	(*food)["5x8"] = new Food();
	(*food)["5x20"] = new Food();
	(*food)["5x21"] = new Food();
	(*food)["5x22"] = new Food();
	(*food)["5x23"] = new Food(Food::Type::big);
	(*food)["5x26"] = new Food();
	(*food)["5x27"] = new Food();
	(*food)["5x28"] = new Food();
	(*food)["5x29"] = new Food();
	//6���
	(*food)["6x1"] = new Food();
	(*food)["6x5"] = new Food();
	(*food)["6x8"] = new Food();
	(*food)["6x20"] = new Food();
	(*food)["6x23"] = new Food();
	(*food)["6x26"] = new Food();
	(*food)["6x29"] = new Food();
	//7���
	(*food)["7x1"] = new Food();
	(*food)["7x5"] = new Food();
	(*food)["7x8"] = new Food();
	(*food)["7x20"] = new Food();
	(*food)["7x23"] = new Food();
	(*food)["7x24"] = new Food();
	(*food)["7x25"] = new Food();
	(*food)["7x26"] = new Food();
	(*food)["7x29"] = new Food();
	//8���
	(*food)["8x1"] = new Food();
	(*food)["8x5"] = new Food();
	(*food)["8x8"] = new Food();
	(*food)["8x20"] = new Food();
	(*food)["8x26"] = new Food();
	(*food)["8x29"] = new Food();
	//9���
	(*food)["9x1"] = new Food();
	(*food)["9x5"] = new Food();
	(*food)["9x8"] = new Food();
	(*food)["9x20"] = new Food();
	(*food)["9x26"] = new Food();
	(*food)["9x29"] = new Food();
	//10���
	(*food)["10x1"] = new Food();
	(*food)["10x2"] = new Food();
	(*food)["10x3"] = new Food();
	(*food)["10x4"] = new Food();
	(*food)["10x5"] = new Food();
	(*food)["10x6"] = new Food();
	(*food)["10x7"] = new Food();
	(*food)["10x8"] = new Food();
	(*food)["10x9"] = new Food();
	(*food)["10x10"] = new Food();
	(*food)["10x11"] = new Food();
	(*food)["10x12"] = new Food();
	(*food)["10x13"] = new Food();
	(*food)["10x14"] = new Food();
	(*food)["10x15"] = new Food();
	(*food)["10x16"] = new Food();
	(*food)["10x17"] = new Food();
	(*food)["10x18"] = new Food();
	(*food)["10x19"] = new Food();
	(*food)["10x20"] = new Food();
	(*food)["10x21"] = new Food();
	(*food)["10x22"] = new Food();
	(*food)["10x23"] = new Food();
	(*food)["10x24"] = new Food();
	(*food)["10x25"] = new Food();
	(*food)["10x26"] = new Food();
	(*food)["10x29"] = new Food();
	//11���
	(*food)["11x1"] = new Food();
	(*food)["11x5"] = new Food();
	(*food)["11x20"] = new Food();
	(*food)["11x23"] = new Food();
	(*food)["11x29"] = new Food();
	//12���
	(*food)["12x1"] = new Food();
	(*food)["12x5"] = new Food();
	(*food)["12x20"] = new Food();
	(*food)["12x23"] = new Food();
	(*food)["12x29"] = new Food();
	//13���
	(*food)["13x1"] = new Food();
	(*food)["13x5"] = new Food();
	(*food)["13x6"] = new Food();
	(*food)["13x7"] = new Food();
	(*food)["13x8"] = new Food();
	(*food)["13x20"] = new Food();
	(*food)["13x23"] = new Food();
	(*food)["13x24"] = new Food();
	(*food)["13x25"] = new Food();
	(*food)["13x26"] = new Food();
	(*food)["13x29"] = new Food();
	//14���
	(*food)["14x1"] = new Food();
	(*food)["14x5"] = new Food();
	(*food)["14x8"] = new Food();
	(*food)["14x20"] = new Food();
	(*food)["14x23"] = new Food();
	(*food)["14x26"] = new Food();
	(*food)["14x29"] = new Food();
	//15���
	(*food)["15x1"] = new Food();
	(*food)["15x5"] = new Food();
	(*food)["15x8"] = new Food();
	(*food)["15x20"] = new Food();
	(*food)["15x23"] = new Food();
	(*food)["15x26"] = new Food();
	(*food)["15x29"] = new Food();
	//16���
	(*food)["16x1"] = new Food();
	(*food)["16x2"] = new Food();
	(*food)["16x3"] = new Food();
	(*food)["16x4"] = new Food();
	(*food)["16x5"] = new Food();
	(*food)["16x8"] = new Food();
	(*food)["16x20"] = new Food();
	(*food)["16x21"] = new Food();
	(*food)["16x22"] = new Food();
	(*food)["16x23"] = new Food();
	(*food)["16x26"] = new Food();
	(*food)["16x27"] = new Food();
	(*food)["16x28"] = new Food();
	(*food)["16x29"] = new Food();
	//17���
	(*food)["17x5"] = new Food();
	(*food)["17x29"] = new Food();
	//18���
	(*food)["18x5"] = new Food();
	(*food)["18x29"] = new Food();
	//19���
	(*food)["19x1"] = new Food();
	(*food)["19x2"] = new Food();
	(*food)["19x3"] = new Food();
	(*food)["19x4"] = new Food();
	(*food)["19x5"] = new Food();
	(*food)["19x8"] = new Food();
	(*food)["19x20"] = new Food();
	(*food)["19x21"] = new Food();
	(*food)["19x22"] = new Food();
	(*food)["19x23"] = new Food();
	(*food)["19x26"] = new Food();
	(*food)["19x27"] = new Food();
	(*food)["19x28"] = new Food();
	(*food)["19x29"] = new Food();
	//20���
	(*food)["20x1"] = new Food();
	(*food)["20x5"] = new Food();
	(*food)["20x8"] = new Food();
	(*food)["20x20"] = new Food();
	(*food)["20x23"] = new Food();
	(*food)["20x26"] = new Food();
	(*food)["20x29"] = new Food();
	//21���
	(*food)["21x1"] = new Food();
	(*food)["21x5"] = new Food();
	(*food)["21x8"] = new Food();
	(*food)["21x20"] = new Food();
	(*food)["21x23"] = new Food();
	(*food)["21x26"] = new Food();
	(*food)["21x29"] = new Food();
	//22���
	(*food)["22x1"] = new Food();
	(*food)["22x5"] = new Food();
	(*food)["22x6"] = new Food();
	(*food)["22x7"] = new Food();
	(*food)["22x8"] = new Food();
	(*food)["22x20"] = new Food();
	(*food)["22x23"] = new Food();
	(*food)["22x24"] = new Food();
	(*food)["22x25"] = new Food();
	(*food)["22x26"] = new Food();
	(*food)["22x29"] = new Food();
	//23���
	(*food)["23x1"] = new Food();
	(*food)["23x5"] = new Food();
	(*food)["23x20"] = new Food();
	(*food)["23x23"] = new Food();
	(*food)["23x29"] = new Food();
	//24���
	(*food)["24x1"] = new Food();
	(*food)["24x5"] = new Food();
	(*food)["24x20"] = new Food();
	(*food)["24x23"] = new Food();
	(*food)["24x29"] = new Food();
	//25���
	(*food)["25x1"] = new Food();
	(*food)["25x2"] = new Food();
	(*food)["25x3"] = new Food();
	(*food)["25x4"] = new Food();
	(*food)["25x5"] = new Food();
	(*food)["25x6"] = new Food();
	(*food)["25x7"] = new Food();
	(*food)["25x8"] = new Food();
	(*food)["25x9"] = new Food();
	(*food)["25x10"] = new Food();
	(*food)["25x11"] = new Food();
	(*food)["25x12"] = new Food();
	(*food)["25x13"] = new Food();
	(*food)["25x14"] = new Food();
	(*food)["25x15"] = new Food();
	(*food)["25x16"] = new Food();
	(*food)["25x17"] = new Food();
	(*food)["25x18"] = new Food();
	(*food)["25x19"] = new Food();
	(*food)["25x20"] = new Food();
	(*food)["25x21"] = new Food();
	(*food)["25x22"] = new Food();
	(*food)["25x23"] = new Food();
	(*food)["25x24"] = new Food();
	(*food)["25x25"] = new Food();
	(*food)["25x26"] = new Food();
	(*food)["25x29"] = new Food();
	//26���
	(*food)["26x1"] = new Food();
	(*food)["26x5"] = new Food();
	(*food)["26x8"] = new Food();
	(*food)["26x20"] = new Food();
	(*food)["26x26"] = new Food();
	(*food)["26x29"] = new Food();
	//27���
	(*food)["27x1"] = new Food();
	(*food)["27x5"] = new Food();
	(*food)["27x8"] = new Food();
	(*food)["27x20"] = new Food();
	(*food)["27x26"] = new Food();
	(*food)["27x29"] = new Food();
	//28���
	(*food)["28x1"] = new Food();
	(*food)["28x5"] = new Food();
	(*food)["28x8"] = new Food();
	(*food)["28x20"] = new Food();
	(*food)["28x23"] = new Food();
	(*food)["28x24"] = new Food();
	(*food)["28x25"] = new Food();
	(*food)["28x26"] = new Food();
	(*food)["28x29"] = new Food();
	//29���
	(*food)["29x1"] = new Food();
	(*food)["29x5"] = new Food();
	(*food)["29x8"] = new Food();
	(*food)["29x20"] = new Food();
	(*food)["29x23"] = new Food();
	(*food)["29x26"] = new Food();
	(*food)["29x29"] = new Food();
	//30���
	(*food)["30x1"] = new Food();
	(*food)["30x2"] = new Food();
	(*food)["30x3"] = new Food(Food::Type::big);
	(*food)["30x4"] = new Food();
	(*food)["30x5"] = new Food();
	(*food)["30x6"] = new Food();
	(*food)["30x7"] = new Food();
	(*food)["30x8"] = new Food();
	(*food)["30x20"] = new Food();
	(*food)["30x21"] = new Food();
	(*food)["30x22"] = new Food();
	(*food)["30x23"] = new Food(Food::Type::big);
	(*food)["30x26"] = new Food();
	(*food)["30x27"] = new Food();
	(*food)["30x28"] = new Food();
	(*food)["30x29"] = new Food();

	WorldVal::Set("food", food);
	for (auto itr : *food) { itr.second->PosSetUp(itr.first); } //�z��Y��������z�u���W�̌���
}
void FoodDel() { //�폜����
	auto food = WorldVal::Get<std::unordered_map<std::string, Food*>>("food");
	for (auto get : *food) { delete get.second; } //food���̂̍폜
	delete food; //�S�̂̍폜
}