#include "Worldval.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, void*>* WorldVal::gloval = nullptr; //static�ϐ���`

void WorldVal::Destruct() {
	for (auto itr : *gloval) { delete itr.second; } //�ێ�����S�Ă�void*���폜
	gloval->clear(); //�z������
	delete gloval; //����
}