#pragma once
#include "GetKey.h"
#include <algorithm>
#include <array>


class GameUi{
public:
    GameUi();
    ~GameUi();
    void UiUpdate();
    void UiDraw();
    void hiscoreDraw();
    void scoreDraw();
    void pacmanUiDraw();//パックマン残機
    void fruitUiDraw();//ステージ果物
    int* score;      
    int* hiscore;
    int* zanki ;//パックマンの残機数(仮）
    int scorecount; //1upが点滅するカウント
    int round=1;  //ラウンド
    int count;
    
private:
    
    
    //果物画像格納用変数
    int fruitImage[10];

    //パックマン残機画像格納用変数
    int pacmanImage[12];

    int hiscoreImage;
    int scoreImage;
    std::array<int, 20 > roundfruit{ 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9 };
};

