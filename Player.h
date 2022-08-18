#pragma once
#include <unordered_map>
#include <string>

class Grid;
class Food;

class Player {
	int* playerImg; //�p�b�N�}���摜�n���h��
	int* killImg; //���S���[�V����
	bool isUpdate; //false��update���s�֎~
	bool isDraw; //��L��draw��

	int foodCount; //����̎c�@�ŐH�ׂ��G�T��
	int foodCountTotal; //�G�T��H�ׂ����v��
	std::unordered_map<std::string, Food*>* food; //�G�T��t���[�c�̔z��
	Grid** tile;

public:
	Player();

};