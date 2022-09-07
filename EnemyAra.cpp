#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>
#include <deque>

//初期化
EnemyAra::EnemyAra() {
    isUpdate = true;
    isDraw = true;

    type = Type::red; //取り敢えずアカベイを代入
    posX = 13;//17
    posY = 11;//11

    center = 3;
    renderCenter = 3;

    drawX = posX * TILE + (TILE - 1);
    drawY = posY * TILE ;

    targetPos_x = 30;
    targetPos_y = 0;

    enemyVec = Direction::left;

    speedLevel = 1;

    count = 0;
    attack = 0;

    ijike = 0;

    speedCount = 0;

    reversOrder = false;

    tile = WorldVal::Get<Grid*>("map");
    enemyImage = *WorldVal::Get<int[20]>("enemyImage");
    enemyImage_eye = *WorldVal::Get<int[4]>("enemyImageEye");

}

void EnemyAra::Update() {
    if (isUpdate) {
        ModeChange();
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //敵と敵の目を表示
    if (isDraw) {
        int sub = (int)type * 2 + ((count / 4) % 2); //使用画像ナンバー
        DrawRotaGraph3(SHIFT_X + (drawX - renderCenter) * X_RATE, SHIFT_Y + (drawY - renderCenter) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, enemyImage[sub], TRUE, FALSE);
        if (ijike == 0) { //イジケじゃないなら
            DrawRotaGraph3(SHIFT_X + (drawX - renderCenter) * X_RATE, SHIFT_Y + (drawY - renderCenter) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)enemyVec], TRUE, FALSE);
        }
    }
}

void EnemyAra::Move(int move) {
    int rawX = ClculatTileX(enemyVec) * TILE + ClculatLocalX(enemyVec);
    int rawY = ClculatTileY(enemyVec) * TILE + ClculatLocalY(enemyVec);
    int limitX = (ClculatTileX(enemyVec) + ClculatSubX(enemyVec)) * TILE + 3;
    int limitY = (ClculatTileY(enemyVec) + ClculatSubY(enemyVec)) * TILE + 4;

    bool run = false;
    switch (enemyVec) {
    case Direction::up: run = rawY - limitY <= 0; break;
    case Direction::left: run = rawX - limitX <= 0; break;
    case Direction::down: run = rawY - limitY >= 0; break;
    case Direction::right: run = rawX - limitX >= 0; break;
    }

    int currentTileX = (drawX + center) / TILE;
    int currentTileY = (drawY + center) / TILE;
    while (currentTileX!=posX || currentTileY != posY) { //マス移動があった場合(whileを使っているのは下記if文でbreakを用いたかったからでループの意図はない)
        posX = currentTileX; //現在所属マスを新しい物に変更
        posY = currentTileY;
        currentTileX += WARP_AREA_X; //こっちの変数は配列からの取得用に変更
        currentTileY += WARP_AREA_Y;

        if (attack) { SetAttackModeTarget(); } //ターゲットマスの設定(追いかけモードの時)
        else { SetStandbyModeTarget(); } //ターゲットマス(縄張りモード)
        if (reversOrder) { SetReversMove(); break; } //反転方向移動は移動先を決定するので以降の移動先決定処理を通る必要がないからbreak
        if (ijike) { SetCringeMove(); break; } //イジケ状態の場合も移動先決定なので終わったらbreak

        int distance[4] = { 9999 ,9999 ,9999 ,9999 }; //各種移動可能方向に進んだマスから目標マスへの距離保存用
        int minDistance = 9999; //最短距離記録用
        int newDirection= ((int)enemyVec + 2) % 4; //新しい移動方向、取り敢えず反対方向に設定する事でどのマスも移動不能だった場合自動的に反対方向が設定されるという算段

        for (int i = 0; i < 4; i++) {
            if (((int)enemyVec + 2) % 4 == i) { continue; } //今回のiが反対方向だった場合飛ばす
            if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::block) { continue; } //移動不可なら飛ばす

            int x = currentTileX + ClculatSubX((Direction)i); //ここであるposは現在のマス座標を指す
            int y = currentTileY + ClculatSubY((Direction)i);
            distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance[i]) { //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
                minDistance = distance[i];
                newDirection = i;
            }
        }
        enemyVec = (Direction)newDirection; //新しい方向に設定
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //現在の移動方向に合わせて各軸に移動量を加算、減算してくれる
    drawY += move * ClculatSubY(enemyVec);

    //以下デバッグ表記
    SetFontSize(30);
    DrawFormatString(700, 30, GetColor(255, 255, 255), "Time：%.2lf", (double)count / 60);
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(700, 100, GetColor(255, 255, 255), "〇エネミー情報");
    DrawFormatString(700, 150, GetColor(255, 0, 0), "X位置：%d", posX);
    DrawFormatString(700, 200, GetColor(0, 0, 255), "Y位置：%d", posY);
    DrawFormatString(700, 250, GetColor(0, 255, 0), "移動方向：%d", enemyVec);
}
//スピードレベルによってスピードを変える
int EnemyAra::ChangeSpeed() {
    int move = 0; //今回の座標移動量
    int speed = 15; //今回の動作速
    switch (speedLevel)
    {
    case 1:
        if (ijike == 1) { speed = 10; }
        break;
    case 2:
        speed = 17;
        break;
    case 3:
        speed = 19;
        break;
    case 4:
        speed = 19;
        break;
    }
    speedCount += speed; //今回の速度をカウントに加算
    move = speedCount / MOVABLE_SPEED; //動作座標量の計算
    speedCount -= move * MOVABLE_SPEED; //動作に使った分のカウントを取り除く

    return move; //今回の動作量を返す
}

//攻撃状態、休憩状態の切り替え
void EnemyAra::ModeChange() {
    count++;//時間経過

    switch (speedLevel) {
    case 1:
        if (count == 0 || count == 27 * FPS || count == 54 * FPS || count == 79 * FPS) {
            attack = 0;//休憩状態
            reversOrder = true;
        }
        if (count == 7 * FPS || count == 34 * FPS || count == 59 * FPS || count == 84 * FPS) {
            attack = 1;///攻撃状態
            reversOrder = true;
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }

    //以下デバッグ表記
    const char* debugMessage[2] = { "休息中" ,"攻撃中" };
    unsigned int color[2] = { GetColor(0, 255, 255) ,GetColor(255, 255, 0) };
    DrawFormatString(700, 300, color[attack], debugMessage[attack]);
}

void EnemyAra::SetCringeMove() {
    int currentTileX = posX + WARP_AREA_X;
    int currentTileY = posY + WARP_AREA_Y;
    int revers = ((int)enemyVec + 2) % 4; //進行方向の反対方向
    std::deque<int> subList = std::deque<int>(); //移動可能な方向を保有する動的配列
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //今回のiが反対方向だった場合飛ばす
        if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::movable) { subList.push_back(i); } //移動可能なら持っておく
    }
    if (subList.size() <= 0) { enemyVec = (Direction)revers; } //どの方向にも動けない場合、移動方向を反対に設定
    else { enemyVec = (Direction)GetRand(subList[subList.size() - 1]); } //移動可能な方向からランダムに方向を取り出し、設定する
}

void EnemyAra::SetReversMove() { 
    enemyVec = (Direction)(((int)enemyVec + 2) % 4); //動作方向を反対に設定する
    reversOrder = false; //反転命令を実行したのでfalseにする
}

int EnemyAra::ClculatSubX(Direction angle) const { return std::sin((360 - 90 * (int)angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(Direction angle) const { return std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int EnemyAra::ClculatLocalX(Direction angle) const { return (posX + center + ClculatSubX(angle)) % TILE; } //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
int EnemyAra::ClculatLocalY(Direction angle) const { return (posY + center + ClculatSubY(angle)) % TILE; }
int EnemyAra::ClculatTileX(Direction angle) const { return (posX + center + ClculatSubX(angle)) / TILE + WARP_AREA_X; } //現在マスを返してくれる
int EnemyAra::ClculatTileY(Direction angle) const { return (posY + center + ClculatSubY(angle)) / TILE + WARP_AREA_Y; }