#include "DxLib.h"
#include "SoundLoading.h"
#include "Worldval.h"

//���ǂݍ���
void SoundLoading() {
	//�ǂݍ���
	int handle1 = LoadSoundMem("SE_BGM/PAC_2_StartMusic1.wav");
	int handle2 = LoadSoundMem("SE_BGM/pac_eat_1.wav");
	int handle3 = LoadSoundMem("SE_BGM/pac_eat_2.wav");
	int handle4 = LoadSoundMem("SE_BGM/PAC_10_Fruit1.wav");
	int handle5 = LoadSoundMem("SE_BGM/PAC_14_Return1.wav");
	int handle6 = LoadSoundMem("SE_BGM/PAC_5_MonsterDefault1.wav");
	int handle7 = LoadSoundMem("SE_BGM/PAC_6_Spurt1.wav");
	int handle8 = LoadSoundMem("SE_BGM/PAC_7_Spurt2.wav");
	int handle9 = LoadSoundMem("SE_BGM/PAC_8_Spurt3.wav");
	int handle10 = LoadSoundMem("SE_BGM/PAC_9_Spurt4.wav");
	int handle11 = LoadSoundMem("SE_BGM/PAC_4_Extend.wav");
	int handle12 = LoadSoundMem("SE_BGM/PAC_12_Eat1.wav");
	int handle13 = LoadSoundMem("SE_BGM/PAC_13_Return1.wav");
	int handle14 = LoadSoundMem("SE_BGM/PAC_11_MonsterIjike1.wav");
	//���̒���
	ChangeVolumeSoundMem(255, handle1);
	ChangeVolumeSoundMem(255, handle2);
	ChangeVolumeSoundMem(255, handle3);
	ChangeVolumeSoundMem(255, handle4);
	ChangeVolumeSoundMem(255, handle5);
	ChangeVolumeSoundMem(200, handle6);
	ChangeVolumeSoundMem(200, handle7);
	ChangeVolumeSoundMem(200, handle8);
	ChangeVolumeSoundMem(200, handle9);
	ChangeVolumeSoundMem(200, handle10);
	ChangeVolumeSoundMem(255, handle11);
	ChangeVolumeSoundMem(255, handle12);
	ChangeVolumeSoundMem(255, handle13);
	ChangeVolumeSoundMem(255, handle14);

	WorldVal::Set("startBGM", new int(handle1));//�Q�[���X�^�[�g��BGM
	WorldVal::Set("eatSE1", new int(handle2));//�G�T��H�ׂ���
	WorldVal::Set("eatSE2", new int(handle3));//�G�T��H�ׂ���
	WorldVal::Set("fruitSE", new int(handle4));//�t���[�c�^�[�Q�b�g��H�ׂ���
	WorldVal::Set("dieSE", new int(handle5));//�p�b�N�}�������S�������̉�
	WorldVal::Set("enemyMoveSE", new int(handle6));//�G��������
	WorldVal::Set("squrtSE1", new int(handle7));//�G���X�p�[�g�������̉� 124,125,122,123
	WorldVal::Set("squrtSE2", new int(handle8));//�G���X�p�[�g�������̉� 64
	WorldVal::Set("squrtSE3", new int(handle9));//�G���X�p�[�g�������̉� 31,30
	WorldVal::Set("squrtSE4", new int(handle10));//�G���X�p�[�g�������̉� 16
	WorldVal::Set("extendSE", new int(handle11));//�c�@up��
	WorldVal::Set("eatSE3", new int(handle12));//�G��H�ׂ���
	WorldVal::Set("damageSE", new int(handle13));//�G�������ԂɂȂ��Ă���Ԃ̉�
	WorldVal::Set("cringeSE", new int(handle14));//�G����������ԂɂȂ��Ă���Ƃ��̉�
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
