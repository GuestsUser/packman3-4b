#pragma once
#include "Scene.h"
#include <algorithm>
#include <array>

class CoffeeBreak : public Scene {
public:
    CoffeeBreak();
    ~CoffeeBreak();
    void Update();
    void Draw();
    void Manga1();
    void Manga2();
    void Manga3();
    void Pacmanmove1();
    void Pacmanmove2();
    void Pacmanmove3();
    void monstermove1();
    void monstermove2();
    void monstermove3();
private:
    //敵画像格納用変数
    int monstereyesImage[4];
    int monsterImage[20];
    int monsterImage3[2];
    
    
    //パックマン画像格納用変数
    int pacmanImage[12];

    //パックマンの動くスピード
    double pacmanmove;
    //敵の動く動くスピード
    double monstermove;
    //時間
    int count;

    int animecount;
    int monsteranime;
    std::array<int, 4 > pacmananime{ 3, 4, 5, 4 };
    std::array<int, 4 > bigpacmananime{ 9, 10, 11, 10 };
};