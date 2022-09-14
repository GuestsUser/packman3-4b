#pragma once
#include <string>
//�G�T�A�p���[�G�T��H�ׂ����̓p�b�N�}���̕��ŃJ�E���g���Ă��Ăق����A�X�e�[�W�N���A�����ɗp����

class Food {
public:
	enum class Type { food, big, cherry, strawberry, orange, apple, melon, galaxian, bell, key };
	enum class Quantity{one , two  , no};
private:
	Type type; //�G�T�̎��
	bool isEnable; //true�Ȃ炱�̃G�T�͂܂��H�ׂ��ĂȂ�
	bool fruitEnable;
	int* handle; //�摜�n���h��
	int x; //�}�X���Wx
	int y; //��L��y
	int count;
	int num;
	int* foodCount;//�G�T�̎�������擾
	int* fruitsCount;//�t���[�c�̎�������擾

	int GetPoint();
public:
	Food(Type set = Type::food); //set�Ɏg�p�������^�C�v������A�����w�肵�Ȃ��ꍇ�ʏ�G�T�ɂȂ�
	int Eat(); //�G�T�̏����A�Ԃ�l�͐H�ׂ��G�T�̓��_

	void SetType(Type set) { type = set; } //�G�T�̎�ނ̍Đݒ�
	Type GetType() { return type; } //�G�T�̃^�C�v��Ԃ�

	void Update();
	void Draw();

	void SetEnable(bool set) { isEnable = set; } //�G�T�̗L����Ԃ̐ݒ�
	bool GetEnable() { return isEnable; } //�L����Ԃ̎擾 

	void PosSetUp(const std::string& set); //unordered_map�p�Y����������W�����o���֐�
	//�t���[�c�������ŏ�����Ƃ��p���[�G�T���_�ł���Ƃ��͂܂���Łc�c
};