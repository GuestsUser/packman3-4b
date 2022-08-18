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

//�摜�ǂݍ���
//int* handle = new int[10];
//LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle); //�摜�ǂݍ���
//WorldVal::Set("foodImage", handle);
// 
////LoadDivGraph�̓s���㖈��V�����̈���|�C���^�^�ϐ��Ɋi�[���Ȃ��Ƃ����Ȃ��̂̓l�b�N
//handle = new int[12];
//LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, handle);
//WorldVal::Set("playerImage", handle);
//
//handle = new int[11];
//LoadDivGraph("Resource/image/dying.png", 11, 11, 1, 16, 16, handle);
//WorldVal::Set("killImage", handle);