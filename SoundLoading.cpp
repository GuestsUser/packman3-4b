#include "DxLib.h"
#include "SoundLoading.h"
#include "Worldval.h"

//音読み込み
void SoundLoading() {
	//読み込み
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
	//音の調整
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

	WorldVal::Set("startBGM", new int(handle1));//ゲームスタート時BGM
	WorldVal::Set("eatSE1", new int(handle2));//エサを食べた音
	WorldVal::Set("eatSE2", new int(handle3));//エサを食べた音
	WorldVal::Set("fruitSE", new int(handle4));//フルーツターゲットを食べた音
	WorldVal::Set("dieSE", new int(handle5));//パックマンが死亡した時の音
	WorldVal::Set("enemyMoveSE", new int(handle6));//敵が動く音
	WorldVal::Set("squrtSE1", new int(handle7));//敵がスパートした時の音 124,125,122,123
	WorldVal::Set("squrtSE2", new int(handle8));//敵がスパートした時の音 64
	WorldVal::Set("squrtSE3", new int(handle9));//敵がスパートした時の音 31,30
	WorldVal::Set("squrtSE4", new int(handle10));//敵がスパートした時の音 16
	WorldVal::Set("extendSE", new int(handle11));//残機up音
	WorldVal::Set("eatSE3", new int(handle12));//敵を食べた音
	WorldVal::Set("damageSE", new int(handle13));//敵がやられ状態になっている間の音
	WorldVal::Set("cringeSE", new int(handle14));//敵がいじけ状態になっているときの音
}



//音削除
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
