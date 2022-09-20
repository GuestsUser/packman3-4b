#include "DxLib.h"
#include "CoffeeBreak.h"
#include "GetKey.h"
#include "Title.h"
#include "Game.h"

CoffeeBreak::CoffeeBreak() {
	LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 16, 16, monsterImage);
	LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 16, 16, monstereyesImage);
	LoadDivGraph("Resource/image/akabei2.png", 4, 4, 1, 16, 16, monsterImage2);
	LoadDivGraph("Resource/image/akabei3_1.png", 2, 2, 1, 16, 16, monsterImage3);
	LoadDivGraph("Resource/image/akabei3.png", 2, 2, 1, 32, 32, monsterImage3_2);
	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, pacmanImage);

	PlaySoundFile("SE_BGM/PAC_15_CoffeBrake.wav", DX_PLAYTYPE_BACK);
	count = 0;
	round = WorldVal::Get<int>("nowStage");

}

CoffeeBreak::~CoffeeBreak() {

}

void CoffeeBreak::Update() {
	count++;
	if (*round==2) {
		if (count >= 660) {
			SetNext(new Game());
			StopSoundFile();
		}
	}
	else if (*round == 5) {
		if (count >= 510) {
			SetNext(new Game());
			StopSoundFile();
		}
	}
	else if (*round == 9|| *round == 13 || *round == 17) {
		if (count >= 540) {
			SetNext(new Game());
			StopSoundFile();
		}
	}
	else {
		SetNext(new Game());
		StopSoundFile();
	}
	
}

void CoffeeBreak::Draw() {
	if (*round == 2) {
		Manga1();
	}
	if (*round == 5) {
		Manga2();
	}
	if (*round == 9 || *round == 13 || *round == 17) {
		Manga3();
	}
	
	DrawBox(0, 0, 321, 721, GetColor(0, 0, 0), TRUE);
	DrawBox(960, 0, 1281, 721, GetColor(0, 0, 0), TRUE);
}

void CoffeeBreak::Manga1() {//660
	Pacmanmove1();
	monstermove1();
}
//ç∂320Å`âE960
void CoffeeBreak::Pacmanmove1() {

	if (count < 240) {
		if ((count / 5) % 2 == 0) {
			std::rotate(pacmananime.begin(), pacmananime.begin() + 1, pacmananime.end());
		}
		pacmanmove = pacmanmove + 3.5;
		DrawRotaGraph3(962 - pacmanmove, 370, 0, 0, 2, 2, 0, pacmanImage[pacmananime[0]], TRUE, FALSE);
	}
	else if (count > 360) {
		animecount++;
		if ((count / 3) % 2 == 0) {
			if (animecount >= 2) {
				std::rotate(bigpacmananime.begin(), bigpacmananime.begin() + 1, bigpacmananime.end());
				animecount = 0;
			}
		}
		pacmanmove = pacmanmove + 3.2;
		DrawRotaGraph3(218 + pacmanmove, 338, 0, 0, 4, 4, 0, pacmanImage[bigpacmananime[0]], TRUE, FALSE);
	}
	else
	{
		pacmanmove = 0;
	}
}
void CoffeeBreak::monstermove1() {
	if (count < 240) {
		if ((count / 15) % 2 == 0) {
			monsteranime = 1;
		}
		else {
			monsteranime = 0;
		}
		monstermove = monstermove + 3.6;
		DrawRotaGraph3(1010 - monstermove, 370, 0, 0, 2, 2, 0, monsterImage[monsteranime], TRUE, FALSE);
		DrawRotaGraph3(1010 - monstermove, 370, 0, 0, 2, 2, 0, monstereyesImage[1], TRUE, FALSE);
	}
	else if (count > 280) {
		if ((count / 15) % 2 == 0) {
			monsteranime = 16;
		}
		else {
			monsteranime = 17;
		}
		monstermove = monstermove + 2.2;
		DrawRotaGraph3(318 + monstermove, 370, 0, 0, 2, 2, 0, monsterImage[monsteranime], TRUE, FALSE);

	}
	else
	{
		monstermove = 0;
	}
}


void CoffeeBreak::Manga2() {//510
	monstermove2();
	Pacmanmove2();

}
void CoffeeBreak::Pacmanmove2() {
	if (count < 240) {
		if ((count / 5) % 2 == 0) {
			std::rotate(pacmananime.begin(), pacmananime.begin() + 1, pacmananime.end());
		}
		pacmanmove = pacmanmove + 3.5;
		DrawRotaGraph3(962 - pacmanmove, 370, 0, 0, 2, 2, 0, pacmanImage[pacmananime[0]], TRUE, FALSE);
	}
	else
	{
		pacmanmove = 0;
	}
}
void CoffeeBreak::monstermove2() {
	if (count < 510) {
		if (count < 185) {
			if ((count / 15) % 2 == 0) {
				monsteranime = 1;
			}
			else {
				monsteranime = 0;
			}
		}
		if (count < 135) {
			kugi = 10;
			monstereyesanime = 1;
			monstermove = monstermove + 3.5;
			monsteranime2 = 2;
		}
		else if (count < 185) {
			kugi = 0;
			monsteranime2 = 3;
			monstermove = monstermove + 0.5;
		}
		else if (count > 330) {
			monstermove = 510;
			monsteranime2 = 0;
			DrawRotaGraph3(600, 370, 0, 0, 2, 2, 0, monsterImage2[1], TRUE, FALSE);
			if (count > 380) {
				monstereyesanime = 3;
			}
			else {
				monstereyesanime = 0;
			}
		}
		DrawRotaGraph3(640 + kugi, 370, 0, 0, 2, 2, 0, monsterImage2[monsteranime2], TRUE, FALSE);
		if (count < 330) {
			DrawRotaGraph3(1110 - monstermove, 370, 0, 0, 2, 2, 0, monsterImage[monsteranime], TRUE, FALSE);
		}
		DrawRotaGraph3(1110 - monstermove, 370, 0, 0, 2, 2, 0, monstereyesImage[monstereyesanime], TRUE, FALSE);

	}
}


void CoffeeBreak::Manga3() {//540
	Pacmanmove3();
	monstermove3();
}
void CoffeeBreak::Pacmanmove3() {
	if (count < 240) {
		if ((count / 5) % 2 == 0) {
			std::rotate(pacmananime.begin(), pacmananime.begin() + 1, pacmananime.end());
		}
		pacmanmove = pacmanmove + 3.5;
		DrawRotaGraph3(962 - pacmanmove, 370, 0, 0, 2, 2, 0, pacmanImage[pacmananime[0]], TRUE, FALSE);
	}
	else
	{
		pacmanmove = 0;
	}
}
void CoffeeBreak::monstermove3() {
	if (count < 240) {
		if ((count / 15) % 2 == 0) {
			monsteranime = 1;
		}
		else {
			monsteranime = 0;
		}
		monstermove = monstermove + 3.5;
		DrawRotaGraph3(1110 - monstermove, 370, 0, 0, 2, 2, 0, monsterImage3[monsteranime], TRUE, FALSE);
		DrawRotaGraph3(1110 - monstermove, 370, 0, 0, 2, 2, 0, monstereyesImage[1], TRUE, FALSE);
	}
	else if (count > 330) {
		DrawRotaGraph3(318 + monstermove, 370, 0, 0, 1, 1, 0, monsterImage3_2[monsteranime], TRUE, FALSE);
		if ((count / 15) % 2 == 0) {
			monsteranime = 0;
		}
		else {
			monsteranime = 1;
		}
		monstermove = monstermove + 3.5;


	}
	else
	{
		monstermove = 0;
	}
}