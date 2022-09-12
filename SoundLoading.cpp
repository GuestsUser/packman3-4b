#include "SoundLoading.h"
#include "DxLib.h"

//âπì«Ç›çûÇ›
SoundLoading::SoundLoading()
{
	seHandle[0] = LoadSoundMem("SE_BGM/PAC_1_Credit.wav");
	seHandle[1] = LoadSoundMem("SE_BGM/PAC_2_StartMusic.wav");
	seHandle[2] = LoadSoundMem("SE_BGM/PAC_3_Cookie.wav");
	seHandle[3] = LoadSoundMem("SE_BGM/PAC_4_Extend.wav");
	seHandle[4] = LoadSoundMem("SE_BGM/PAC_5_MonsterDefault.wav");
	seHandle[5] = LoadSoundMem("SE_BGM/PAC_6_Spurt1.wav");
	seHandle[6] = LoadSoundMem("SE_BGM/PAC_7_Spurt2.wav");
	seHandle[7] = LoadSoundMem("SE_BGM/PAC_8_Spurt3.wav");
	seHandle[8] = LoadSoundMem("SE_BGM/PAC_9_Spurt4.wav");
	seHandle[9] = LoadSoundMem("SE_BGM/PAC_10_Fruit.wav");
	seHandle[10] = LoadSoundMem("SE_BGM/PAC_11_MonsterIjike.wav");
	seHandle[11] = LoadSoundMem("SE_BGM/PAC_12_Eat.wav");
	seHandle[12] = LoadSoundMem("SE_BGM/PAC_13_Return.wav");
	seHandle[13] = LoadSoundMem("SE_BGM/PAC_14_Return.wav");
	seHandle[14] = LoadSoundMem("SE_BGM/PAC_15_CoffeBrake.wav");
}
//âπçÌèú
SoundLoading::~SoundLoading()
{
	for (int i = 0; i < 15; i++)
	{
		DeleteSoundMem(seHandle[i]);
	}
}


