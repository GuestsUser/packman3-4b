#include "DxLib.h"
#include "CoffeeBreak.h"
#include "GetKey.h"
#include "Title.h"

CoffeeBreak::CoffeeBreak() {
	LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 32, 32, monsterImage);
	LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 32, 32, monstereyesImage);

	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, pacmanImage);

	PlaySoundFile("SE_BGM/PAC_15_CoffeBrake.wav", DX_PLAYTYPE_BACK);
	
}

CoffeeBreak::~CoffeeBreak() {
	
}

void CoffeeBreak::Update() {
	count++;
	if (count >= 660){
		SetNext(new Title());
		StopSoundFile();
	}
	if (key->GetKeyState(B_KEY) == KEY_PUSH) { //Aボタン(緑ボタン)が押された瞬間
		SetNext(new Title()); //ゲームシーンへ遷移
		StopSoundFile();
		
	}
	
}

void CoffeeBreak::Draw() {
	Manga1();
	Manga2();
	Manga3();
}

void CoffeeBreak::Manga1() {
	Pacmanmove1();
	monstermove1();
	DrawBox(0, 0, 321, 721, GetColor(0, 0, 0), TRUE);
	DrawBox(960, 0, 1281, 721, GetColor(0, 0, 0), TRUE);
}
//左320～右960
void CoffeeBreak::Pacmanmove1() {
	
	if (count < 240) {
		if ((count / 5) % 2==0) {
			std::rotate(pacmananime.begin(), pacmananime.begin() + 1, pacmananime.end());
		}
		pacmanmove = pacmanmove + 3.5;
		DrawRotaGraph3(962 - pacmanmove, 370, 0, 0, 2, 2, 0, pacmanImage[pacmananime[0]], TRUE, FALSE);
	}
	else if (count > 360) {
		animecount++;
		if ((count / 3) % 2 ==0) {
			if (animecount >=2) {
				std::rotate(bigpacmananime.begin(), bigpacmananime.begin() + 1, bigpacmananime.end());
				animecount = 0;
			}
		}
		pacmanmove = pacmanmove + 3.2;
		DrawRotaGraph3( 218+ pacmanmove, 338, 0, 0, 4, 4, 0, pacmanImage[bigpacmananime[0]], TRUE, FALSE);
	} 
	else 
	{
		pacmanmove = 0;
	}
}
void CoffeeBreak::monstermove1() {
	if (count<240) {
		if ((count / 15) % 2 == 0) {
			monsteranime = 1;
		}
		else {
			monsteranime = 0;
		}
		monstermove = monstermove + 3.6;
		DrawRotaGraph3(1010 - monstermove, 370, 0, 0, 1, 1, 0, monsterImage[monsteranime], TRUE, FALSE);
		DrawRotaGraph3(1010 - monstermove, 370, 0, 0, 1, 1, 0, monstereyesImage[3], TRUE, FALSE);
	}
	else if (count > 280) {
		if ((count / 15) % 2 == 0) {
			monsteranime = 16;
		}
		else {
			monsteranime = 17;
		}
		monstermove = monstermove + 2.2;
		DrawRotaGraph3(318 + monstermove, 370, 0, 0, 1, 1, 0, monsterImage[monsteranime], TRUE, FALSE);
		
	}
	else 
	{
		monstermove = 0;
	}
}


void CoffeeBreak::Manga2() {
	Pacmanmove2();
	monstermove2();
}
void CoffeeBreak::Pacmanmove2() {

}
void CoffeeBreak::monstermove2() {

}


void CoffeeBreak::Manga3() {
	Pacmanmove3();
	monstermove3();
}
void CoffeeBreak::Pacmanmove3() {

}
void CoffeeBreak::monstermove3() {

}