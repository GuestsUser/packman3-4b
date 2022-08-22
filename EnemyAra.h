#pragma once
class EnemyAra
{
public:
    EnemyAra();
    ~EnemyAra();

    //アカベイ用変数
    int akaPos_x;
    int akaPos_y;
    int aka_eye;
    int aka_img;
    int akaPos_xright;
    int akaPos_yup;
    int akaPos_xleft;
    int akaPos_ydown;
    int akaSpeed;
    int akaoldPos_x;
    int akaoldPos_y;


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

    int distance[3];
    int stagemas;

    int minDistance;
    int enemyVec;

    int speedLevel;

    int okMove;

    int count;
    int attack;

    int ijike;
    int ijikeRandom;

    int enemyoldVec;

    //enemy描画関数
    void enemyDraw();

    void enemyMove();

    void enemyUpdate();

    void enemyChangeSpeed();

    void enemyMode();

    void enemyIjike();

private:

    //enemy画像格納用変数
    int enemyImage[20];

    //enemyの目の画像格納用変数
    int enemyImage_eye[4];


};