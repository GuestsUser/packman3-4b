#include "DxLib.h"
#include "SoundLoading.h"
#include "Worldval.h"

//音読み込み
void SoundLoading() {
	WorldVal::Set("startBGM", new int(LoadSoundMem("SE_BGM/PAC_2_StartMusic.wav")));//ゲームスタート時BGM
	WorldVal::Set("eatSE1", new int(LoadSoundMem("SE_BGM/pac_eat_1.wav")));//エサを食べた音
	WorldVal::Set("eatSE2", new int(LoadSoundMem("SE_BGM/pac_eat_2.wav")));//エサを食べた音
	WorldVal::Set("fruitSE", new int(LoadSoundMem("SE_BGM/PAC_10_Fruit.wav")));//フルーツターゲットを食べた音
	WorldVal::Set("dieSE", new int(LoadSoundMem("SE_BGM/PAC_14_Return.wav")));//パックマンが死亡した時の音
	WorldVal::Set("enemyMoveSE", new int(LoadSoundMem("SE_BGM/PAC_5_MonsterDefault.wav")));//敵が動く音
	WorldVal::Set("spurtSE1", new int(LoadSoundMem("SE_BGM/PAC_6_Spurt1.wav")));//敵がスパートした時の音 124,125,122,123
	WorldVal::Set("spurtSE2", new int(LoadSoundMem("SE_BGM/PAC_7_Spurt2.wav")));//敵がスパートした時の音 64
	WorldVal::Set("spurtSE3", new int(LoadSoundMem("SE_BGM/PAC_8_Spurt3.wav")));//敵がスパートした時の音 31,30
	WorldVal::Set("spurtSE4", new int(LoadSoundMem("SE_BGM/PAC_9_Spurt4.wav")));//敵がスパートした時の音 16
	WorldVal::Set("extendSE", new int(LoadSoundMem("SE_BGM/PAC_4_Extend.wav")));//残機up音
	WorldVal::Set("eatSE3", new int(LoadSoundMem("SE_BGM/PAC_12_Eat.wav")));//敵を食べた音
}



//音削除
void SoundDel() {
	DeleteSoundMem(*WorldVal::Get<int>("startBGM"));
	DeleteSoundMem(*WorldVal::Get<int>("eatSE1"));
	DeleteSoundMem(*WorldVal::Get<int>("eatSE2"));
	DeleteSoundMem(*WorldVal::Get<int>("fruitSE"));
	DeleteSoundMem(*WorldVal::Get<int>("dieSE"));
	DeleteSoundMem(*WorldVal::Get<int>("enemyMoveSE"));
	DeleteSoundMem(*WorldVal::Get<int>("spurtSE1"));
	DeleteSoundMem(*WorldVal::Get<int>("spurtSE2"));
	DeleteSoundMem(*WorldVal::Get<int>("spurtSE3"));
	DeleteSoundMem(*WorldVal::Get<int>("spurtSE4"));
	DeleteSoundMem(*WorldVal::Get<int>("extendSE"));
}
