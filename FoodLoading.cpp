#include "Food.h"
#include "FoodLoading.h"
#include "Worldval.h"
#include <unordered_map>
#include <string>

void FoodLoading() { //�G�T��t���[�c�̍쐬����
	std::unordered_map<std::string, Food*>* food = new std::unordered_map<std::string, Food*>();

	//MapLoading���l��240���̔z�u�������ɏ����Ă䂭�c�c
	//���L��̓}�X���W(3,2)�̏ꏊ�Ƀp���[�G�T��z�u����
	//�������ȗ������ꍇ�ʏ�G�T�ɂȂ�
	//�G�T���K�v�ȏꏊ�̂ݔz�u����A�}�b�v�S�}�X�ɒ��菄�点��K�v�͂Ȃ�
	//(*food)["3x2"] = new Food(Food::Type::big);

	WorldVal::Set("food", food);
	for (auto itr : *food) { itr.second->PosSetUp(itr.first); } //�z��Y��������z�u���W�̌���
}
void FoodDel() { //�폜����
	auto food = WorldVal::Get<std::unordered_map<std::string, Food*>>("food");
	for (auto get : *food) { delete get.second; } //food���̂̍폜
	delete food; //�S�̂̍폜
}