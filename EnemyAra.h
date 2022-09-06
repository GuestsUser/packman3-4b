#pragma once
#include "Grid.h"
class EnemyAra {
public:
    enum class Type { red, pink, blue, orange }; //敵の種類
private:
    bool reversOrder; //trueで次の移動先を強制的に反転方向に設定する

     //アカベイのポジション変数
    int posX; //現在マス、タイル配列から移動可能方向を取得する添え字にするにはWARP_AREA分足す必要あり
    int posY;
    int drawX; //描写用位置
    int drawY;

    int targetPos_x; //目標マスのポジション変数
    int targetPos_y;

    int speedLevel; //スピードレベル格納変数
    int speedCount;

    int center;
    int renderCenter;

    int count; //時間経過変数
    int attack; //攻撃状態切り替え変数
    int ijike; //イジケ状態切り替え変数

    int* enemyImage; //enemy画像格納用変数
    int* enemyImage_eye; //enemyの目の画像格納用変数

    Direction enemyVec; //敵の移動方向変数
    Type type; //敵の種類記憶
    Grid** tile; //マップタイル配列

    int ChangeSpeed();
    void Move(int move);
    void ModeChange();

    void SetCringeMove(); //イジケ状態時位置決定関数、これはオーバーライドする形式ではない
    void SetReversMove(); //反対方向へ移動方向を向ける関数

    int ClculatSubX(Direction angle) const; //指定方向の時x軸方向への動作に掛ける符号を返す
    int ClculatSubY(Direction angle) const; //上記のy版
    int ClculatLocalX(Direction angle)const; //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
    int ClculatLocalY(Direction angle)const; //上記のy版
protected:
    
public:
    EnemyAra();
    void Draw();
    void Update();
    
    virtual void SetAttackModeTarget() = 0; //追いかけモード中の狙いマス決定関数、オーバーライドして使う
    virtual void SetStandbyModeTarget() = 0; //上記の縄張りモード版
    virtual void SetWaitModeTarget() = 0; //巣の中の待機位置決定関数

    void SetUp(Type setType, Direction setDirection, int setX, int setY) { //継承先コンストラクタ内で必ず呼び出す必要あり、setTypeに敵種類、setDirectionに最初に向いてる方向、setX,Yに現在位置を座標で代入
        type = setType;
        drawX = setX;
        drawY = setY;
        SetStandbyModeTarget(); //待機状態の目標マスに設定
    }
    void SetReversOrder(bool set) { reversOrder = set; } //trueで次の移動先を強制的に反転方向に設定する

    Direction GetDirection() { return enemyVec; } //現在の移動方向を取得できる
    int ClculatTileX(Direction angle)const; //現在マスを返してくれる
    int ClculatTileY(Direction angle)const; //上記のy版

    void TargetSet(int setX, int setY) { //ターゲットマス指定、指定はワープエリア込みで考える
        targetPos_x = setX;
        targetPos_y = setY;
    }

    
    //void SetAttackModeTarget(); //テスト用実装
    //void SetStandbyModeTarget();
    //void SetWaitModeTarget();
};