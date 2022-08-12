#pragma once
class EnemyAra
{
public:
    EnemyAra();
    ~EnemyAra();

    //アカベイ用変数
    int akaPos_x;
    int akaPos_y;
    int akaPos_xright;
    int akaPos_yup;
    int akaPos_xleft;
    int akaPos_ydown;
    int akaSpeed;

    //アオスケ用変数
    int aoPos_x;
    int aoPos_y;
    int aoSpeed;

    //グズタ用変数
    int orangePos_x;
    int orangePos_y;
    int orangeSpeed;

    //ピンキー用変数
    int pinkPos_x;
    int pinkPos_y;
    int pinkSpeed;

    int targetPos_x;
    int targetPos_y;

    int distance[4];

    int minDistance;
    int enemyVec;

    int speedLevel;

    //enemy描画関数
    void enemyDraw();

    void enemyMove();

    void enemyUpdate();

    void enemyChangeSpeed();

private:

    //enemy画像格納用変数
    int enemyImage[20];

    //enemyの目の画像格納用変数
    int enemyImage_eye[4];


};