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
    int akaMove;

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

    //目標マスのポジション変数
    int targetPos_x;
    int targetPos_y;
    int targetDrow_x;
    int targetDrow_y;

    //敵の移動方向変数
    int enemyVec;
    
    //スピードレベル格納変数
    int speedLevel;

    //時間経過変数
    int count;
    //攻撃状態切り替え変数
    int attack;

    //イジケ状態切り替え変数
    int ijike;
    int okIjikeMove;
    int ijikeRandom;
    int ijikeHanten;

    //敵の移動する前の向き格納変数
    int enemyoldVec;

    // 目標マスとの距離を入れる変数
    int distanceUP;
    int distanceLeft;
    int distanceDown;
    int distanceRight;

    int speedCount;

    int enemyRand;
    int okRand;

    int hantenMode;
    int okHanten;

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
    bool reversOrder; //trueで次の移動先を強制的に反転方向に設定する

    //enemy画像格納用変数
    int enemyImage[20];

    //enemyの目の画像格納用変数
    int enemyImage_eye[4];

    //virtual void SetAttackModeTarget() = 0; //追いかけモード中の狙いマス決定関数、オーバーライドして使う
    //virtual void SetStandbyModeTarget() = 0; //上記の縄張りモード版
    //virtual void SetWaitModeTarget() = 0; //巣の中の待機位置決定関数

    void SetAttackModeTarget(); //テスト用実装
    void SetStandbyModeTarget();
    void SetWaitModeTarget();

    void SetCringeMove(); //イジケ状態時位置決定関数、これはオーバーライドする形式ではない
    void SetReversMove(); //反対方向へ移動方向を向ける関数
    int ClculatSubX(int angle) const; //指定方向の時x軸方向への動作に掛ける符号を返す
    int ClculatSubY(int angle) const; //上記のy版

    void SetReversOrder(bool set) { reversOrder = set; }
};