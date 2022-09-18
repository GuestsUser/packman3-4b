#pragma once
#include "Grid.h"
#include <deque>
class EnemyAra {
public:
    enum class MoveMode { standby, attack }; //縄張りモードか攻撃モードかの列挙型
    enum class State { neutral, cringe, damage, wait, ready }; //敵の状態、この状態に応じてマスの移動可能方向取得配列を変える他、移動先決定関数も変更する
    enum class Type { red, pink, blue, orange }; //敵の種類
private:
    static int nowStage; //現在ステージ数
    static int timer; //縄張り、追いかけモードのモードチェンジ用タイマー
    static MoveMode moveMode; //縄張り、攻撃のモードチェンジは全敵共通なのでstatic
    State state; //状態は敵によりけりなので通常変数
    State imageState; //stateがwaitやreadyの時、現在画像を保持する為のstate

    bool reversOrder; //trueで次の移動先を強制的に反転方向に設定する
    bool isUpdate; //falseでupdate実行禁止
    bool isDraw; //上記のdraw版

     //アカベイのポジション変数
    int drawX; //描写用位置
    int drawY;

    int limitX;
    int limitY;

    int targetPos_x; //目標マスのポジション変数
    int targetPos_y;

    int speedCount;

    int center;
    int renderCenter;

    int count; //時間経過変数
    int warp;   //ワープ時スピード切り替え

    int* enemyImage; //enemy画像格納用変数
    int* enemyImage_eye; //enemyの目の画像格納用変数

    Direction enemyVec; //敵の移動方向変数
    Direction oldVec; //やられ状態敵の目の方向固定用
    Type type; //敵の種類記憶
    Grid** tile; //マップタイル配列

    int ChangeSpeed();
    void Move(int move);
    

    void SetCringeMove(); //イジケ状態時位置決定関数、これはオーバーライドする形式ではない
    void SetReversMove(); //反対方向へ移動方向を向ける関数

    int ClculatSubX(Direction angle) const; //指定方向の時x軸方向への動作に掛ける符号を返す
    int ClculatSubY(Direction angle) const; //上記のy版
    int ClculatLocalX()const; //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
    int ClculatLocalY()const; //上記のy版
    int ClculatLimitX(Direction angle)const; //この位置に着いたら現在マスから移動可能方向を取得し方向転換する位置を返してくれる
    int ClculatLimitY(Direction angle)const; //上記のy版

    const ::Move* ReadTile(int x, int y); //現在stateに応じて[x][y]位置の移動可能方向配列を返す

public:
    EnemyAra();
    void Draw();
    void Update();
    
    //Update、Drawの実行可否取得と設定用関数
    void SetRunUpdate(bool set) { isUpdate = set; }
    void SetRunDraw(bool set) { isDraw = set; }
    bool GetRunUpdate() { return isUpdate; }
    bool GetRunDraw() { return isDraw; }

    int GetDrawX() const; //表示系関数に直接指定可能な値を返す
    int GetDrawY() const; //上記のy版

    static void ModeChange(std::deque<EnemyAra*>* enemyList); //縄張り、追いかけモードのモードチェンジ用関数、シーン内で1

    virtual void SetAttackModeTarget() = 0; //追いかけモード中の狙いマス決定関数、オーバーライドして使う
    virtual void SetStandbyModeTarget() = 0; //上記の縄張りモード版
    virtual void SetWaitModeTarget() = 0; //巣の中の待機位置決定関数

    virtual int Spurt() { return -1; } //通常以外の速度がある敵はこれをオーバーライドして動作をカスタムする、返り値-1はスパートを利用しない扱い

    void SetUp(Type setType, Direction setDirection, int setX, int setY); //継承先コンストラクタ内で必ず呼び出す必要あり、setTypeに敵種類、setDirectionに最初に向いてる方向、setX,Yに現在位置を座標で代入
    void SetReversOrder(bool set) { //trueで次の移動先を強制的に反転方向に設定する
        if (state == State::neutral || state == State::cringe) { reversOrder = set; } //通常とイジケ状態の場合だけ反転を受け付ける
    }

    Direction GetDirection() { return enemyVec; } //現在の移動方向を取得できる
    int ClculatTileX()const; //現在マスを返してくれる
    int ClculatTileY()const; //上記のy版
    static int ClculatSpeedLevel() { return (nowStage > 0) + (nowStage >= 4) + (nowStage >= 21); } //現在の速度レベルを計算

    void TargetSet(int setX, int setY) { //ターゲットマス指定、指定はワープエリア込みで考える
        targetPos_x = setX;
        targetPos_y = setY;
    }

    void SetState(State set) { 
        if (state == State::wait || state == State::ready) { imageState = set; } //敵が待機、巣から抜ける状態の場合画像ステートを変更する
        else { state = set; } //それ以外ならstateを変更する
    }
    void SetStateReinterpret(State set) { state = set; } //stateの状態に関係なく強制セット、使用は非奨励
    static void SetMoveMode(MoveMode set) { moveMode = set; }

    State GetState() { return state; }
    State GetImageState() { return imageState; }
    static MoveMode GetMoveMode() { return moveMode; }
};