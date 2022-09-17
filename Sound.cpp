#include "Sound.h"
#include "Worldval.h"
#include "PowerModeProcess.h"
#include "DxLib.h"

Sound::Sound():powerMode(PowerModeProcess(&player, &enemy))
{
	count1 = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	count5 = 0;

	enemyMoveSE = *WorldVal::Get<int>("enemyMoveSE");
	spurtSE1 = *WorldVal::Get<int>("spurtSE1");
	spurtSE2 = *WorldVal::Get<int>("spurtSE2");
	spurtSE3 = *WorldVal::Get<int>("spurtSE3");
	spurtSE4 = *WorldVal::Get<int>("spurtSE4");

	foodcount = WorldVal::Get<int>("foodCountTotal");

	isUpdate = false;
}

void Sound::Update()
{
	if (isUpdate)
	{
		if (powerMode.GetState() == PowerModeProcess::State::free)
		{
			if (count1 == 0)
			{
				PlaySoundMem(enemyMoveSE, DX_PLAYTYPE_LOOP);
				count1 = 1;
			}
		}
	}
}

void Sound::spurtSound()
{
	if (isUpdate)
	{
		foodcount = WorldVal::Get<int>("foodCountTotal");

		if (*foodcount == 116)//116
		{
			if (count2 == 0)
			{
				StopSoundMem(enemyMoveSE);
				count2 = 1;
			}
			if (count2 == 1)
			{
				PlaySoundMem(spurtSE1, DX_PLAYTYPE_LOOP);
				count2 = 2;
			}
		}
		else if (*foodcount == 180)//180
		{
			if (count3 == 0)
			{
				StopSoundMem(spurtSE1);
				count3 = 1;
			}
			if (count3 == 1)
			{
				PlaySoundMem(spurtSE2, DX_PLAYTYPE_LOOP);
				count3 = 2;
			}
		}
		else if (*foodcount == 212)//212
		{
			if (count4 == 0)
			{
				StopSoundMem(spurtSE2);
				count4 = 1;
			}
			if (count4 == 1)
			{
				PlaySoundMem(spurtSE3, DX_PLAYTYPE_LOOP);
				count4 = 2;
			}
		}
		else if (*foodcount == 228)//228
		{
			if (count5 == 0)
			{
				StopSoundMem(spurtSE3);
				count5 = 1;
			}
			if (count5 == 1)
			{
				PlaySoundMem(spurtSE3, DX_PLAYTYPE_LOOP);
				count5 = 2;
			}
		}
	}
}