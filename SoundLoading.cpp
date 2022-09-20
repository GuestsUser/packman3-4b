#include "DxLib.h"
#include "SoundLoading.h"
#include "Worldval.h"

//音読み込み
void SoundLoading() {
	WorldVal::Set("startBGM", new int(LoadSoundMem("SE_BGM/PAC_2_StartMusic1.wav")));//ゲームスタート時BGM
	WorldVal::Set("eatSE1", new int(LoadSoundMem("SE_BGM/pac_eat_1.wav")));//エサを食べた音
	WorldVal::Set("eatSE2", new int(LoadSoundMem("SE_BGM/pac_eat_2.wav")));//エサを食べた音
	WorldVal::Set("fruitSE", new int(LoadSoundMem("SE_BGM/PAC_10_Fruit1.wav")));//フルーツターゲットを食べた音
	WorldVal::Set("dieSE", new int(LoadSoundMem("SE_BGM/PAC_14_Return1.wav")));//パックマンが死亡した時の音
	WorldVal::Set("enemyMoveSE", new int(LoadSoundMem("SE_BGM/PAC_5_MonsterDefault1.wav")));//敵が動く音
	WorldVal::Set("squrtSE1", new int(LoadSoundMem("SE_BGM/PAC_6_Spurt1.wav")));//敵がスパートした時の音 124,125,122,123
	WorldVal::Set("squrtSE2", new int(LoadSoundMem("SE_BGM/PAC_7_Spurt2.wav")));//敵がスパートした時の音 64
	WorldVal::Set("squrtSE3", new int(LoadSoundMem("SE_BGM/PAC_8_Spurt3.wav")));//敵がスパートした時の音 31,30
	WorldVal::Set("squrtSE4", new int(LoadSoundMem("SE_BGM/PAC_9_Spurt4.wav")));//敵がスパートした時の音 16
	WorldVal::Set("extendSE", new int(LoadSoundMem("SE_BGM/PAC_4_Extend.wav")));//残機up音
	WorldVal::Set("eatSE3", new int(LoadSoundMem("SE_BGM/PAC_12_Eat1.wav")));//敵を食べた音
	WorldVal::Set("damageSE",new int(LoadSoundMem("SE_BGM/PAC_13_Return1.wav")));//敵がやられ状態になっている間の音
	WorldVal::Set("cringeSE", new int(LoadSoundMem("SE_BGM/PAC_11_MonsterIjike1.wav")));//敵がいじけ状態になっているときの音
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
