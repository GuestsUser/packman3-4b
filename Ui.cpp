#include "DxLib.h"
#include "Ui.h"



GameUi::GameUi() {
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, fruitImage);
	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, pacmanImage);
	hiscoreImage= LoadGraph("Resource/image/highScore.png");
	scoreImage = LoadGraph("Resource/image/1up.png");
	
	
}

GameUi::~GameUi() {

}

void GameUi::UiUpdate() {
	if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) == KEY_PUSH) { 
		zanki++;
	}
	if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) == KEY_PUSH) {
		zanki--;
	}
	if (key->GetKeyState(B_KEY) == KEY_PUSH) { //Bボタン(赤ボタン)が押された瞬間
		round++;
		if (round >= 9&& round <21) {
			std::rotate(roundfruit.begin(), roundfruit.begin() + 1, roundfruit.end());
		}
	}
	if (key->GetKeyState(X_KEY) == KEY_PUSH) { score=score+1000; }
	if (key->GetKeyState(Y_KEY) == KEY_PUSH) { score = 0; }
}

void GameUi::UiDraw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Round %d", round);
	DrawFormatString(0, 50, GetColor(255, 255, 255), "残機 %d", zanki);


	hiscoreDraw();
	scoreDraw();
	fruitUiDraw();
	pacmanUiDraw();
}

void GameUi::hiscoreDraw(){//ハイスコア表示
	DrawRotaGraph3(700, 100, 0, 0, 2, 2, 0, hiscoreImage, TRUE, FALSE);
	//DrawGraph(700, 100, hiscoreImage, FALSE);
	DrawFormatString(750, 150, GetColor(255, 255, 255), "%7d", hiscore);
	if (hiscore < score) {
		hiscore = score;
	}
}

void GameUi::scoreDraw() {//スコア表示と1UPの点滅 
	scorecount++;
	if ((scorecount/15)%2 ==0) {
		DrawRotaGraph3(700, 200, 0, 0, 2, 2, 0, scoreImage, TRUE, FALSE);
	}
	DrawFormatString(750, 250, GetColor(255, 255, 255), "%7d", score);
}

void GameUi::fruitUiDraw() {//ステージに応じた果物の表示
	if (round >= 1 && round < 9) {
		DrawRotaGraph3(700, 350, 0, 0, 2, 2, 0, fruitImage[2], TRUE, FALSE);

		if (round >= 2 && round < 9) {
			DrawRotaGraph3(750, 350, 0, 0, 2, 2, 0, fruitImage[3], TRUE, FALSE);

			if (round >= 3 && round < 9) {
				DrawRotaGraph3(800, 350, 0, 0, 2, 2, 0, fruitImage[4], TRUE, FALSE);

				if (round >= 4 && round < 9) {
					DrawRotaGraph3(850, 350, 0, 0, 2, 2, 0, fruitImage[4], TRUE, FALSE);

					if (round >= 5 && round < 9) {
						DrawRotaGraph3(700, 400, 0, 0, 2, 2, 0, fruitImage[5], TRUE, FALSE);

						if (round >= 6 && round < 9) {
							DrawRotaGraph3(750, 400, 0, 0, 2, 2, 0, fruitImage[5], TRUE, FALSE);

							if (round >= 7 && round < 9) {
								DrawRotaGraph3(800, 400, 0, 0, 2, 2, 0, fruitImage[6], TRUE, FALSE);

								if (round >= 8 && round < 9) {
									DrawRotaGraph3(850, 400, 0, 0, 2, 2, 0, fruitImage[6], TRUE, FALSE);
								}
							}
						}
					}
				}
			}
		}
	}
	if (round >= 9) {
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
	if (zanki >= 1) {
		DrawRotaGraph3(700, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

		if (zanki >= 2) {
			DrawRotaGraph3(750, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

			if (zanki >= 3) {
				DrawRotaGraph3(800, 500, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

				if (zanki >= 4) {
					DrawRotaGraph3(700, 550, 0, 0, 2, 2, 0, pacmanImage[4], TRUE, FALSE);

				}
			}
		}
	}
}