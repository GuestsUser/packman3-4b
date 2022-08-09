#pragma once
#include <unordered_map>
#include <string>

//�V�[�����ׂ����l�ێ��N���X
//���̂�private�ϐ���static�Ƃ��Ċm�ۂ��Ă���̂Ŗ��O��ԉ������Z�q����A�N�Z�X����
//WorldVal::Set("test",new int(4)); ����Ȋ����Anew int�̕��̌^�͍D���Ȍ^���g����
//int get=WorldVal::Get<int>("test"); ����ȕ��Ɏ��o���A<int>�̕����͎��o���^�ɍ��킹�ĕς���
//WorldVal::Del("test"); �����"test"�̒l���폜�ł���
class WorldVal {
	static std::unordered_map<std::string, void*>* gloval; //Set�Ŏ󂯎����key�̃R�s�[���L�[�Ƃ��ĂȂ��ꍇ�L�[�����ł��鋰�ꂠ��
public:
	static void SetUp() { if (gloval == nullptr) { gloval = new std::unordered_map<std::string, void*>(); } } //�l��ێ���������ϐ����󂾂����ꍇ����
	static void Destruct(); //�E�B���h�E����鎞�A�S�����̂���ŌĂяo��

	template<class T> static T* Get(const std::string& key) {
		auto itr = gloval->find<std::string>(key);
		if (itr != gloval->end()) { return static_cast<T*>(itr->second); } //�v�f�����������ꍇ�ڕW�̌^�ɃL���X�g���ĕԂ�
		return nullptr; //������Ȃ�������nullptr�ŕԂ�
	}
	static void Set(const std::string& key, void* date) { (*gloval)[key] = date; } 
	static void Del(const std::string& key) {
		auto itr=gloval->find<std::string>(key);
		if (itr != gloval->end()) { //�v�f�����������ꍇ�������� 
			delete itr->second; //void*�̃f�X�g���N�^���Ăяo��
			gloval->erase(itr); //�v�f���폜����
		}
	}

	//���̐����֎~
	WorldVal() = delete;
	WorldVal(const WorldVal&) = delete;
};