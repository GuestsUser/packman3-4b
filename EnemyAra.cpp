#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>
#include <deque>

//初期化
EnemyAra::EnemyAra()
{
    akaPos_x = 16;//17
    akaPos_y = 11;//11

    center = 7;

    akaDraw_x = akaPos_x * TILE + (TILE - 1);
    akaDraw_y = akaPos_y * TILE + (TILE - 1) / 2;

    akaMas_x = 0;
    akaMas_y = 0;

    akaMove = 15;

    aka_eye = 3;
    aka_img = 0;
    aka_anim = 0;

    akaSpeed = 15;
    akaoldPos_x = 0;
    akaoldPos_y = 0;

    targetPos_x = 30;
    targetPos_y = 0;
    targetDrow_x = 0;
    targetDrow_y = 0;

    enemyVec = 1;

    akaPos_yup = akaPos_y - 1;
    akaPos_xleft = akaPos_x - 1;
    akaPos_ydown = akaPos_y + 1;
    akaPos_xright = akaPos_x + 1;


    speedLevel = 1;

    count = 0;
    attack = 0;

    ijike = 0;

    okIjikeMove = 1;

    ijikeRandom = 0;
    ijikeHanten = 0;

    enemyoldVec = 1;

    distanceUP = 0;
    distanceLeft = 0;
    distanceDown = 0;
    distanceRight = 0;


    okRand = 1;
    enemyRand = 0;

    speedCount = 0;

    hantenMode = 0;
    okHanten = 0;

    nowDirection = Direction::left;
    tile = WorldVal::Get<Grid*>("map");

    reversOrder = false;

    LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 16, 16, enemyImage);
    LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 32, 32, enemyImage_eye);
}
//削除
EnemyAra::~EnemyAra()
{
    int i;

    for (i = 0; i < 20; i++)
    {
        DeleteGraph(enemyImage[i]);
    }

    for (i = 0; i < 4; i++)
    {
        DeleteGraph(enemyImage_eye[i]);
    }
}

void EnemyAra::enemyDraw()
{
    //敵と敵の目を表示
    DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE , SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE , 0, 0, X_RATE, Y_RATE,0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)//イジケじゃないなら
    {
        DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, 1, 1, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }

}

void EnemyAra::enemyMove() {
    int currentTileX = akaDraw_x / TILE;
    int currentTileY = akaDraw_y / TILE;
    while (currentTileX != akaPos_x || currentTileY != akaPos_y) { //マス移動があった場合(whileを使っているのは下記if文でbreakを用いたかったからでループの意図はない)
        if (attack) { SetAttackModeTarget(); } //ターゲットマスの設定(追いかけモードの時)
        else { SetStandbyModeTarget(); } //ターゲットマス(縄張りモード)
        if (reversOrder) { SetReversMove(); break; } //反転方向移動は移動先を決定するので以降の移動先決定処理を通る必要がないからbreak
        if (ijike) { SetCringeMove(); break; } //イジケ状態の場合も移動先決定なので終わったらbreak

        int distance[4] = { 9999 ,9999 ,9999 ,9999 }; //各種移動可能方向に進んだマスから目標マスへの距離保存用
        int minDistance = 9999; //最短距離記録用
        int newDirection= (enemyVec + 2) % 4; //新しい移動方向、取り敢えず反対方向に設定する事でどのマスも移動不能だった場合自動的に反対方向が設定されるという算段

        for (int i = 0; i < 4; i++) {
            if ((enemyVec + 2) % 4 == i) { continue; } //今回のiが反対方向だった場合飛ばす
            if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::block) { continue; } //移動不可なら飛ばす

            //int useY, useX;

            //if (i == 0 || i == 2)
            //{
            //    useY = 1;
            //    useX = 0;
            //}//y軸方向への移動なら1、そうでないなら0になる

            //if (i == 1 || i == 3)
            //{
            //    useY = 0;
            //    useX = 1;
            //}
            //int sub = -1 + 2 * (int)(i / 2 > 0); //進む方向の符号、上、左ならマイナス、下、右ならプラスを出す
            //int x = akaPos_x + sub * useX; //ここであるposは現在のマス座標を指す
            //int y = akaPos_y + sub * useY;

            int x = currentTileX + ClculatSubX(i); //ここであるposは現在のマス座標を指す
            int y = currentTileY + ClculatSubY(i);
            distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance[i]) { //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
                minDistance = distance[i];
                newDirection = i;
            }
        }
        enemyVec = newDirection; //新しい方向に設定
        break;
    }
    akaPos_x = currentTileX; //現在所属マスを新しい物に変更
    akaPos_y = currentTileY;

    akaDraw_x += akaMove * ClculatSubX(enemyVec); //現在の移動方向に合わせて各軸に移動量を加算、減算してくれる
    akaDraw_y += akaMove * ClculatSubY(enemyVec);
    aka_eye = enemyVec; //目の向きの指定
    aka_anim++;
    aka_img = aka_anim / 4 % 2;

    SetFontSize(30);
    DrawFormatString(700, 30, GetColor(255, 255, 255), "Time：%.2lf", (double)count / 60);
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(700, 100, GetColor(255, 255, 255), "〇エネミー情報");
    DrawFormatString(700, 150, GetColor(255, 0, 0), "X位置：%d", akaPos_x);
    DrawFormatString(700, 200, GetColor(0, 0, 255), "Y位置：%d", akaPos_y);
    DrawFormatString(700, 250, GetColor(0, 255, 0), "移動方向：%d", enemyVec);
}
//スピードレベルによってスピードを変える
void EnemyAra::enemyChangeSpeed()
{
    switch (speedLevel)
    {
    case 1:
        if (ijike == 0)
        {
            akaSpeed = 15;
        }
        if (ijike == 1)
        {
            akaSpeed = 10;
        }
        break;
    case 2:
        akaSpeed = 17;
        break;
    case 3:
        akaSpeed = 19;
        break;
    case 4:
        akaSpeed = 19;
        break;
    }
    speedCount += akaSpeed;
    akaMove = speedCount / MOVABLE_SPEED;
    speedCount -= akaMove * MOVABLE_SPEED;
}

//攻撃状態、休憩状態の切り替え
void EnemyAra::enemyMode()
{
    count++;//時間経過

    switch (speedLevel)
    {
    case 1:
        if (count >= 0 && count < 7 * FPS)//0～7秒の時休憩
        {
            attack = 0;//休憩状態

            DrawFormatString(700, 300, GetColor(0, 255, 255), "休息中");
        }
        else if (count >= 7 * FPS && count < 27 * FPS)//7～27秒の時攻撃
        {
            attack = 1;//攻撃状態

            DrawFormatString(700, 300, GetColor(255, 255, 0), "攻撃中");
        }
        else if (count >= 27 * FPS && count < 34 * FPS)//27～34秒の時休憩
        {
            attack = 0;//休憩状態

            DrawFormatString(700, 300, GetColor(0, 255, 255), "休息中");
        }
        else if (count >= 34 * FPS && count < 54 * FPS)//34～54秒の時攻撃
        {
            attack = 1;//攻撃状態

            DrawFormatString(700, 300, GetColor(255, 255, 0), "攻撃中");
        }
        else if (count >= 54 * FPS && count < 59 * FPS)//54～59秒の時休憩
        {
            attack = 0;//休憩状態

            DrawFormatString(700, 300, GetColor(0, 255, 255), "休息中");
        }
        else if (count >= 59 * FPS && count < 79 * FPS)//59～79秒の時攻撃
        {
            attack = 1;//攻撃状態

            DrawFormatString(700, 300, GetColor(255, 255, 0), "攻撃中");
        }
        else if (count >= 79 * FPS && count < 84 * FPS)//79～84秒の時休憩
        {
            attack = 0;//休憩状態

            DrawFormatString(700, 300, GetColor(0, 255, 255), "休息中");
        }
        else if (count >= 84 * FPS)//84秒以降は攻撃
        {
            attack = 1;//攻撃状態

            DrawFormatString(700, 300, GetColor(255, 255, 0), "攻撃中");
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (ijike == 0)//イジケじゃないなら
    {
        if (attack == 1)//攻撃状態なら
        {
            //目標マスをパックマンのいるマス
            targetPos_x = 5;
            targetPos_y = 0;


            if (count == 7 * FPS || count == 34 * FPS || count == 59 * FPS || count == 84 * FPS) {
                hantenMode = 1;
            }

            if (hantenMode == 1) {
                if (enemyVec == 0) {
                    enemyVec = 2;
                    hantenMode = 0;
                }
                else if (enemyVec == 1) {
                    enemyVec = 3;
                    hantenMode = 0;
                }
                else if (enemyVec == 2) {
                    enemyVec = 0;
                    hantenMode = 0;
                }
                else if (enemyVec == 3) {
                    enemyVec = 1;
                    hantenMode = 0;
                }
            }
        }
        else if (attack == 0)//休憩状態なら
        {
            //目標マスを右上

            targetPos_x = 30;
            targetPos_y = 30;

            if (count == 27 * FPS || count == 54 * FPS || count == 79 * FPS) {
                hantenMode = 1;
            }

            if (hantenMode == 1) {
                if (enemyVec == 0) {
                    enemyVec = 2;
                    hantenMode = 0;
                }
                else if (enemyVec == 1) {
                    enemyVec = 3;
                    hantenMode = 0;
                }
                else if (enemyVec == 2) {
                    enemyVec = 0;
                    hantenMode = 0;
                }
                else if (enemyVec == 3) {
                    enemyVec = 1;
                    hantenMode = 0;
                }
            }
        }
    }

}

//イジケ状態処理
void EnemyAra::enemyIjike()
{
    if (ijike == 1)
    {
        aka_img = 16;

        if (okIjikeMove == 0)
        {
            akaPos_yup = akaPos_y - 1;
            akaPos_xleft = akaPos_x - 1;
            akaPos_ydown = akaPos_y + 1;
            akaPos_xright = akaPos_x + 1;

            ijikeHanten = 1;
            okIjikeMove = 1;
        }

        if (ijikeRandom == 0 && okIjikeMove == 1)
        {
            if (ijikeHanten == 1)
            {
                if (enemyVec == 0)
                {
                    enemyVec = 2;
                    ijikeHanten = 0;
                }
                else if (enemyVec == 1)
                {
                    enemyVec = 3;
                    ijikeHanten = 0;
                }
                else if (enemyVec == 2)
                {
                    enemyVec = 0;
                    ijikeHanten = 0;
                }
                else if (enemyVec == 3)
                {
                    enemyVec = 1;
                    ijikeHanten = 0;
                }
            }

            if (enemyVec == 0)
            {
                if (enemyoldVec != 0)
                {
                    enemyoldVec = 0;//上方向状態にする
                }

                //次のマスまで移動する
                if (akaPos_y != akaPos_yup)
                {
                    akaDraw_y -= akaMove;
                }

                //次のマスについたら
                if (akaPos_y == akaPos_yup)
                {
                    okIjikeMove = 0;//一瞬動けない状態にする
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //最短方向が左なら
            else if (enemyVec == 1)
            {
                if (enemyoldVec != 1)
                {
                    enemyoldVec = 1;//左方向状態にする
                }

                //次のマスまで移動する
                if (akaPos_x != akaPos_xleft)
                {
                    akaDraw_x -= akaMove;
                }

                //次のマスについたら
                if (akaPos_x == akaPos_xleft)
                {
                    okIjikeMove = 0;//一瞬動けない状態にする
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //最短方向が下なら
            else if (enemyVec == 2)
            {
                if (enemyoldVec != 2)
                {
                    enemyoldVec = 2;//下方向状態にする
                }

                //次のマスまで移動する
                if (akaPos_y != akaPos_ydown)
                {
                    akaDraw_y += akaMove;
                }

                //次のマスについたら
                if (akaPos_y == akaPos_ydown)
                {
                    okIjikeMove = 0;//一瞬動けない状態にする
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //最短方向が右なら
            else if (enemyVec == 3)
            {
                if (enemyoldVec != 3)
                {
                    enemyoldVec = 3;//右方向状態にする
                }

                //次のマスまで移動する
                if (akaPos_x != akaPos_xright)
                {
                    akaDraw_x += akaMove;
                }

                //次のマスについたら
                if (akaPos_x == akaPos_xright)
                {
                    okIjikeMove = 0;//一瞬動けない状態にする
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
        }
    }
}

void EnemyAra::enemyUpdate()
{
    enemyDraw();
    enemyMode();
    enemyMove();
    enemyChangeSpeed();
    //enemyIjike();
}

void EnemyAra::SetCringeMove() {
    int revers = (enemyoldVec + 2) % 4; //進行方向の反対方向
    std::deque<int> subList = std::deque<int>(); //移動可能な方向を保有する動的配列
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //今回のiが反対方向だった場合飛ばす
        if (tile[akaPos_x][akaPos_y].ReadEnemy()[i] == Move::movable) { subList.push_back(i); } //移動可能なら持っておく
    }
    if (subList.size() <= 0) { enemyVec = revers; } //どの方向にも動けない場合、移動方向を反対に設定
    else { enemyVec = GetRand(subList[subList.size() - 1]); } //移動可能な方向からランダムに方向を取り出し、設定する
}

void EnemyAra::SetReversMove() { 
    enemyVec = (enemyoldVec + 2) % 4; //動作方向を反対に設定する
    reversOrder = false; //反転命令を実行したのでfalseにする
}

int EnemyAra::ClculatSubX(int angle) const { return std::sin((360 - 90 * angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(int angle) const { return std::sin((360 - 90 * angle + 270) * (PI / 180)); }

void EnemyAra::SetAttackModeTarget() {
    targetPos_x = 30;
    targetPos_y = 30;
}
void EnemyAra::SetStandbyModeTarget() {
    targetPos_x = 5;
    targetPos_y = 0;
}
void EnemyAra::SetWaitModeTarget() {
    targetPos_x = 16;
    targetPos_y = 13;
}