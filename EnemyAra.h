#pragma once
#include "Grid.h"
class EnemyAra
{
public:
    EnemyAra();
    ~EnemyAra();

    //アカベイのポジション変数
    int akaPos_x;
    int akaPos_y;
    int akaDraw_x;
    int akaDraw_y;
    int akaMas_x;
    int akaMas_y;

    int aka_anim;

    int center;
    //画像番号格納変数
    int aka_eye;
    int aka_img;
    //現在マスの上下左右のマスのポジション変数
    int akaPos_xright;
    int akaPos_yup;
    int akaPos_xleft;
    int akaPos_ydown;
    //アカベイの移動量変数
    int akaSpeed;
    //アカベイの1マス前のポジション変数
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

    //目標マスのポジション変数
    int targetPos_x;
    int targetPos_y;
    int targetDrow_x;
    int targetDrow_y;
    
    //目標マスとの距離格納変数
    int distance[4];

    //目標マスとの最短距離格納変数
    int minDistance;

    //敵の移動方向変数
    int enemyVec;
    
    //スピードレベル格納変数
    int speedLevel;

    //敵が動いていいかの変数
    int okMove;

    //時間経過変数
    int count;
    //攻撃状態切り替え変数
    int attack;

    //イジケ状態切り替え変数
    int ijike;
    int ijikeRandom;

    //敵の移動する前の向き格納変数
    int enemyoldVec;

    // 目標マスとの距離を入れる変数
    int distanceUP;
    int distanceLeft;
    int distanceDown;
    int distanceRight;

    int disCount;

    int speedCount;


    Direction nowDirection;

    Grid** tile;

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