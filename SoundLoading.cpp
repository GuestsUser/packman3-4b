#include "DxLib.h"
#include "SoundLoading.h"
#include "Worldval.h"

//���ǂݍ���
void SoundLoading() {
	WorldVal::Set("startBGM", new int(LoadSoundMem("SE_BGM/PAC_2_StartMusic1.wav")));//�Q�[���X�^�[�g��BGM
	WorldVal::Set("eatSE1", new int(LoadSoundMem("SE_BGM/pac_eat_1.wav")));//�G�T��H�ׂ���
	WorldVal::Set("eatSE2", new int(LoadSoundMem("SE_BGM/pac_eat_2.wav")));//�G�T��H�ׂ���
	WorldVal::Set("fruitSE", new int(LoadSoundMem("SE_BGM/PAC_10_Fruit1.wav")));//�t���[�c�^�[�Q�b�g��H�ׂ���
	WorldVal::Set("dieSE", new int(LoadSoundMem("SE_BGM/PAC_14_Return1.wav")));//�p�b�N�}�������S�������̉�
	WorldVal::Set("enemyMoveSE", new int(LoadSoundMem("SE_BGM/PAC_5_MonsterDefault1.wav")));//�G��������
	WorldVal::Set("squrtSE1", new int(LoadSoundMem("SE_BGM/PAC_6_Spurt1.wav")));//�G���X�p�[�g�������̉� 124,125,122,123
	WorldVal::Set("squrtSE2", new int(LoadSoundMem("SE_BGM/PAC_7_Spurt2.wav")));//�G���X�p�[�g�������̉� 64
	WorldVal::Set("squrtSE3", new int(LoadSoundMem("SE_BGM/PAC_8_Spurt3.wav")));//�G���X�p�[�g�������̉� 31,30
	WorldVal::Set("squrtSE4", new int(LoadSoundMem("SE_BGM/PAC_9_Spurt4.wav")));//�G���X�p�[�g�������̉� 16
	WorldVal::Set("extendSE", new int(LoadSoundMem("SE_BGM/PAC_4_Extend.wav")));//�c�@up��
	WorldVal::Set("eatSE3", new int(LoadSoundMem("SE_BGM/PAC_12_Eat1.wav")));//�G��H�ׂ���
	WorldVal::Set("damageSE",new int(LoadSoundMem("SE_BGM/PAC_13_Return1.wav")));//�G�������ԂɂȂ��Ă���Ԃ̉�
	WorldVal::Set("cringeSE", new int(LoadSoundMem("SE_BGM/PAC_11_MonsterIjike1.wav")));//�G����������ԂɂȂ��Ă���Ƃ��̉�
}



//���폜
void SoundDel() {
	DeleteSoundMem(*WorldVal::Get<int>("startBGM"));
	DeleteSoundMem(*WorldVal::Get<int>("eatSE1"));
	DeleteSoundMem(*WorldVal::Get<int>("eatSE2"));
	DeleteSoundMem(*WorldVal::Get<int>("fruitSE"));
	DeleteSoundMem(*WorldVal::Get<int>("dieSE"));
	DeleteSoundMem(*WorldVal::Get<int>("enemyMoveSE"));
	DeleteSoundMem(*WorldVal::Get<int>("squrtSE1"));
	DeleteSoundMem(*WorldVal::Get<int>("squrtSE2"));
	DeleteSoundMem(*WorldVal::Get<int>("squrtSE3"));
	DeleteSoundMem(*WorldVal::Get<int>("squrtSE4"));
	DeleteSoundMem(*WorldVal::Get<int>("extendSE"));
	DeleteSoundMem(*WorldVal::Get<int>("eatSE3"));
	DeleteSoundMem(*WorldVal::Get<int>("damageSE"));
	DeleteSoundMem(*WorldVal::Get<int>("cringeSE"));
}
