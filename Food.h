#pragma once
#include <string>

class Food {
public:
	enum class Type { food, big, cherry, strawberry, orange, apple, melon, galaxian, bell, key };
private:
	Type type; //�G�T�̎��
	bool isEnable; //true�Ȃ炱�̃G�T�͂܂��H�ׂ��ĂȂ�
	int handle[10]; //�摜�n���h��
	int x; //�}�X���Wx
	int y; //��L��y
public:
	Food(Type set = Type::food); //set�Ɏg�p�������^�C�v������A�����w�肵�Ȃ��ꍇ�ʏ�G�T�ɂȂ�
	int Eat(); //�G�T�̏����A�Ԃ�l�͐H�ׂ��G�T�̓��_
	Type GetType() { return type; } //�G�T�̃^�C�v��Ԃ�

	void Update();
	void Draw();

	void PosSetUp(const std::string& set); //unordered_map�p�Y����������W�����o���֐�
	//�t���[�c�������ŏ�����Ƃ��p���[�G�T���_�ł���Ƃ��͂܂���Łc�c
};