#include "DxLib.h"
#include "Ui.h"
#include "ScoreLoading.h"
#include "Player.h"
#include "Worldval.h"



GameUi::GameUi() {
	round = WorldVal::Get<int>("nowStage");
	score = WorldVal::Get<int>("score");
	hiscore = WorldVal::Get<int>("highScore");
	zanki = WorldVal::Get<int>("Life");
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, fruitImage);
	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, pacmanImage);
	hiscoreImage= LoadGraph("Resource/image/highScore.png");
	scoreImage = LoadGraph("Resource/image/1up.png");
	//count = 0;
	scorecount = 0;
	if (*round >= 8 && *round < 20) {
		for (int i = 0; i < *round - 7;i++) {
			std::rotate(roundfruit.begin(), roundfruit.begin() + 1, roundfruit.end());
		}
	}
	if(*round>=20){
		for (int i = 0; i < 12; i++) {
			std::rotate(roundfruit.begin(), roundfruit.begin() + 1, roundfruit.end());
	}
	}
}

GameUi::~GameUi() {
	
}

void GameUi::UiUpdate() {
	//count++;
	
}

void GameUi::UiDraw() {
	hiscoreDraw();
	scoreDraw();
	fruitUiDraw();
	pacmanUiDraw();
}

void GameUi::hiscoreDraw(){//ハイスコア表示
	DrawRotaGraph3(700, 100, 0, 0, 2, 2, 0, hiscoreImage, TRUE, FALSE);
		SetFontSize(35);
		DrawFormatString(720, 140, GetColor(255, 255, 255), "%7d", *hiscore);
}

void GameUi::scoreDraw() {//スコア表示と1UPの点滅 
	scorecount++;
	if ((scorecount/15)%2 ==0) {
		DrawRotaGraph3(700, 200, 0, 0, 2, 2, 0, scoreImage, TRUE, FALSE);
	}
	SetFontSize(35);
	DrawFormatString(720, 230, GetColor(255, 255, 255), "%7d", *score);
}

void GameUi::fruitUiDraw() {//ステージに応じた果物の表示
	if (*round >= 0 && *round < 8) {
		DrawRotaGraph3(700, 350, 0, 0, 2, 2, 0, fruitImage[2], TRUE, FALSE);

		if (*round >= 1 && *round < 8) {
			DrawRotaGraph3(750, 350, 0, 0, 2, 2, 0, fruitImage[3], TRUE, FALSE);

			if (*round >= 2 && *round < 8) {
				DrawRotaGraph3(800, 350, 0, 0, 2, 2, 0, fruitImage[4], TRUE, FALSE);

				if (*round >= 3 && *round < 8) {
					DrawRotaGraph3(850, 350, 0, 0, 2, 2, 0, fruitImage[4], TRUE, FALSE);

					if (*round >= 4 && *round < 8) {
						DrawRotaGraph3(700, 400, 0, 0, 2, 2, 0, fruitImage[5], TRUE, FALSE);

						if (*round >= 5 && *round < 8) {
							DrawRotaGraph3(750, 400, 0, 0, 2, 2, 0, fruitImage[5], TRUE, FALSE);

							if (*round >= 6 && *round < 8) {
								DrawRotaGraph3(800, 400, 0, 0, 2, 2, 0, fruitImage[6], TRUE, FALSE);

								if (*round >= 7 && *round < 8) {
									DrawRotaGraph3(850, 400, 0, 0, 2, 2, 0, fruitImage[6], TRUE, FALSE);
								}
							}
						}
					}
				}
			}
		}
	}
	if (*round >= 8) {
		DrawRotaGraph3(700, 350, 0, 0, 2, 2, 0, fruitImage[roundfruit[0]], TRUE, FALSE);
		DrawRotaGraph3(750, 350, 0, 0, 2, 2, 0, fruitImage[roundfruit[1]], TRUE, FALSE);
		DrawRotaGraph3(800, 350, 0, 0, 2, 2, 0, fruitImage[roundfruit[2]], TRUE, FALSE);
		DrawRotaGraph3(850, 350, 0, 0, 2, 2, 0, fruitImage[roundfruit[3]], TRUE, FALSE);
		DrawRotaGraph3(700, 400, 0, 0, 2, 2, 0, fruitImage[roundfruit[4]], TRUE, FALSE);
		DrawRotaGraph3(750, 400, 0, 0, 2, 2, 0, fruitImage[roundfruit[5]], TRUE, FALSE);
		DrawRotaGraph3(800, 400, 0, 0, 2, 2, 0, fruitImage[roundfruit[6]], TRUE, FALSE);
		DrawRotaGraph3(850, 400, 0, 0, 2, 2, 0, fruitImage[roundfruit[7]], TRUE, FALSE);
	}
}
	


void GameUi::pacmanUiDraw() {//パックマンの残機表示
	if (*zanki >= 1) {
		DrawRotaGraph3(700, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

		if (*zanki >= 2) {
			DrawRotaGraph3(750, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

			if (*zanki >= 3) {
				DrawRotaGraph3(800, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

				if (*zanki >= 4) {
					DrawRotaGraph3(700, 550, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

				}
			}
		}
	}
}