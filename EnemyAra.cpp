#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include <math.h>

//初期化
EnemyAra::EnemyAra()
{
    akaPos_x = 400;//400
    akaPos_y = 280;//280
    aka_eye = 3;
    aka_img = 0;

    akaSpeed = 1;
    akaoldPos_x = 0;
    akaoldPos_y = 0;


    aoPos_x = 0;
    aoPos_y = 0;
    aoSpeed = 0;

    orangePos_x = 0;
    orangePos_y = 0;
    orangeSpeed = 0;

    pinkPos_x = 0;
    pinkPos_y = 0;
    pinkSpeed = 0;

    targetPos_x = 0;
    targetPos_y = 0;

    for (int i = 0; i < 4; i++)
    {
        distance[i] = 9999;
    }

    minDistance = 9999;
    enemyVec = 1;


    akaPos_xright = akaPos_x + TILE;
    akaPos_xleft = akaPos_x - TILE;
    akaPos_yup = akaPos_y - TILE;
    akaPos_ydown = akaPos_y + TILE;


    speedLevel = 1;

    okMove = 0;

    count = 0;
    attack = 0;

    ijike = 0;
    ijikeRandom = 0;

    enemyoldVec = 1;

    distanceUP = 0;
    distanceLeft = 0;
    distanceDown = 0;
    distanceRight = 0;

    LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 32, 32, enemyImage);
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
    DrawRotaGraph3(akaPos_x, akaPos_y, 0, 0,1,1,0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)//イジケじゃないなら
    {
        DrawRotaGraph3(akaPos_x, akaPos_y, 0, 0, 1, 1, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }
}

void EnemyAra::enemyMove()
{
    if (ijike == 0)//イジケじゃないなら
    {
        if (okMove == 0)
        {
            for (int i = 0; i < 28 * X_RATE; i++)
            {
                for (int k = 0; k < 31 * Y_RATE; k++)
                {
                    if (akaPos_x == TILE * i + SHIFT_X && akaPos_y == TILE * k + SHIFT_Y)//マスについたとき
                    {
                        //現在マスを覚える
                        akaoldPos_x = akaPos_x;
                        akaoldPos_y = akaPos_y;

                        //目標マスとの距離計算
                        distanceUP = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_x)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_yup)), 2));
                        distanceLeft = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_xleft)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_y)), 2));
                        distanceDown = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_x)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_ydown)), 2));
                        distanceRight = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_xright)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_y)), 2));

                        if (enemyoldVec == 0)//向いてた方向が上なら
                        {
                            //距離を配列に格納
                            distance[0] = distanceUP;
                            distance[1] = distanceLeft;
                            distance[2] = 9999;
                            distance[3] = distanceRight;
                        }
                        else if (enemyoldVec == 1)//向いてた方向が左なら
                        {
                            //距離を配列に格納
                            distance[0] = distanceUP;
                            distance[1] = distanceLeft;
                            distance[2] = distanceDown;
                            distance[3] = 9999;
                        }
                        else if (enemyoldVec == 2)//向いてた方向が下なら
                        {
                            //距離を配列に格納
                            distance[0] = 9999;
                            distance[1] = distanceLeft;
                            distance[2] = distanceDown;
                            distance[3] = distanceRight;
                        }
                        else if (enemyoldVec == 3)//向いてた方向が右なら
                        {
                            //距離を配列に格納
                            distance[0] = distanceUP;
                            distance[1] = 9999;
                            distance[2] = distanceDown;
                            distance[3] = distanceRight;
                        }

                        okMove = 1;//敵を動いて良いようにする
                    }
                }
            }
        }
        else if (okMove == 1)//動いていい状態なら
        {
            //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
            for (int i = 0; i < 4; i++)
            {
                if (minDistance > distance[i])
                {
                    minDistance = distance[i];

                    enemyVec = i;
                }
            }

            //最短方向が上なら
            if (enemyVec == 0)
            {
                if (enemyoldVec != 0)
                {
                    enemyoldVec = 0;//上方向状態にする
                }

                //次のマスまで移動する
                if (akaPos_y != akaPos_yup)
                {
                    akaPos_y -= akaSpeed;
                    if (ijike == 0)
                    {
                        aka_eye = 0;

                        if (aka_img < 2)
                        {
                            aka_img++;
                        }
                        if (aka_img >= 2)
                        {
                            aka_img = 0;
                        }
                    }
                }

                //次のマスについたら
                if (akaPos_y == akaPos_yup)
                {
                    minDistance = 9999;//最短距離初期化
                    enemyVec = -1;//移動方向を一瞬無くす
                    okMove = 0;//一瞬動けない状態にする
                    akaPos_yup = akaPos_y - TILE;//動いた後のマスの次のマスの情報取得
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

                    akaPos_x -= akaSpeed;
                    if (ijike == 0)
                    {
                        aka_eye = 3;

                        if (aka_img < 2)
                        {
                            aka_img++;
                        }
                        if (aka_img >= 2)
                        {
                            aka_img = 0;
                        }
                    }
                }

                //次のマスについたら
                if (akaPos_x == akaPos_xleft)
                {
                    minDistance = 9999;//最短距離初期化
                    enemyVec = -1;//移動方向を一瞬無くす
                    okMove = 0;//一瞬動けない状態にする
                    akaPos_xleft = akaPos_x - TILE;//動いた後のマスの次のマスの情報取得
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
                    akaPos_y += akaSpeed;
                    if (ijike == 0)
                    {
                        aka_eye = 2;

                        if (aka_img < 2)
                        {
                            aka_img++;
                        }
                        if (aka_img >= 2)
                        {
                            aka_img = 0;
                        }
                    }
                }

                //次のマスについたら
                if (akaPos_y == akaPos_ydown)
                {
                    minDistance = 9999;//最短距離初期化
                    enemyVec = -1;//移動方向を一瞬無くす
                    okMove = 0;//一瞬動けない状態にする
                    akaPos_ydown = akaPos_y + TILE;//動いた後のマスの次のマスの情報取得

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
                    akaPos_x += akaSpeed;
                    if (ijike == 0)
                    {
                        aka_eye = 1;

                        if (aka_img < 2)
                        {
                            aka_img++;
                        }
                        if (aka_img >= 2)
                        {
                            aka_img = 0;
                        }
                    }
                }

                //次のマスについたら
                if (akaPos_x == akaPos_xright)
                {
                    minDistance = 9999;//最短距離初期化
                    enemyVec = -1;//移動方向を一瞬無くす
                    okMove = 0;//一瞬動けない状態にする
                    akaPos_xright = akaPos_x + TILE;//動いた後のマスの次のマスの情報取得
                }
            }
        }
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", count);
    DrawFormatString(0, 50, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(0, 100, GetColor(255, 0, 0), "%d", akaPos_x);
    DrawFormatString(0, 150, GetColor(0, 0, 255), "%d", akaPos_y);
    DrawFormatString(0, 200, GetColor(0, 255, 255), "%d", enemyVec);
    DrawFormatString(0, 250, GetColor(0, 255, 255), "%d", targetPos_x);
    DrawFormatString(0, 300, GetColor(0, 255, 255), "%d", targetPos_y);



}
//スピードレベルによってスピードを変える
void EnemyAra::enemyChangeSpeed()
{
    switch (speedLevel)
    {
    case 1:
        akaSpeed = 1;
        aoSpeed = 15;
        orangeSpeed = 15;
        pinkSpeed = 15;
        break;
    case 2:
        akaSpeed = 17;
        aoSpeed = 17;
        orangeSpeed = 17;
        pinkSpeed = 17;
        break;
    case 3:
        akaSpeed = 19;
        aoSpeed = 19;
        orangeSpeed = 19;
        pinkSpeed = 19;
        break;
    case 4:
        akaSpeed = 19;
        aoSpeed = 19;
        orangeSpeed = 19;
        pinkSpeed = 19;
        break;
    }
}

//攻撃状態、休憩状態の切り替え
void EnemyAra::enemyMode()
{
    count++;//時間経過
    int flame = 60;//フレームレート

    switch (speedLevel)
    {
    case 1:
        if (count >= 0 && count < 7 * flame)//0～7秒の時休憩
        {
            attack = 0;//休憩状態
        }
        else if (count >= 7 * flame && count < 27 * flame)//7～27秒の時攻撃
        {
            attack = 1;//攻撃状態
        }
        else if (count >= 27 * flame && count < 34 * flame)//27～34秒の時休憩
        {
            attack = 0;//休憩状態

        }
        else if (count >= 34 * flame && count < 54 * flame)//34～54秒の時攻撃
        {
            attack = 1;//攻撃状態

        }
        else if (count >= 54 * flame && count < 59 * flame)//54～59秒の時休憩
        {
            attack = 0;//休憩状態
        }
        else if (count >= 59 * flame && count < 79 * flame)//59～79秒の時攻撃
        {
            attack = 1;//攻撃状態

        }
        else if (count >= 79 * flame && count < 84 * flame)//79～84秒の時休憩
        {
            attack = 0;//休憩状態

        }
        else if (count >= 84 * flame)//84秒以降は攻撃
        {
            attack = 1;//攻撃状態

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
            targetPos_x = 192;
            targetPos_y = 608;
        }
        else if (attack == 0)//休憩状態なら
        {
            //目標マスを右上
            targetPos_x = 640;
            targetPos_y = 112;
        }
    }

}

//イジケ状態処理
void EnemyAra::enemyIjike()
{
    if (ijike == 1)
    {
        aka_img = 16;

        if (ijikeRandom == 0)
        {
            if (akaPos_x != akaoldPos_x)
            {
                if (akaPos_x > akaoldPos_x)
                {
                    akaPos_x -= akaSpeed;
                }
                else if (akaPos_x < akaoldPos_x)
                {
                    akaPos_x += akaSpeed;
                }
            }
            if (akaPos_y != akaoldPos_y)
            {
                if (akaPos_y > akaoldPos_y)
                {
                    akaPos_y -= akaSpeed;
                }
                else if (akaPos_y < akaoldPos_y)
                {
                    akaPos_y += akaSpeed;
                }
            }
            else if (akaPos_x == akaoldPos_x && akaPos_y == akaoldPos_y)
            {
                ijikeRandom = 1;
            }
        }
        else if (ijikeRandom == 1)
        {
            for (int i = 0; i < 28; i++)
            {
                for (int k = 0; k < 31; k++)
                {
                    if (akaPos_x == 16 * i + 192 && akaPos_y == 16 * k + 112)
                    {
                        int a = GetRand(3);
                        enemyVec = a;
                    }
                }
            }

            if (enemyVec == 0)
            {
                aka_eye = 0;
                if (akaPos_y != akaPos_yup)
                {
                    akaPos_y -= akaSpeed;
                }
                if (akaPos_y == akaPos_yup)
                {
                    akaPos_yup = akaPos_y - 32;
                    akaPos_ydown = akaPos_y + 32;
                }
            }
            else if (enemyVec == 1)
            {
                aka_eye = 1;
                if (akaPos_x != akaPos_xright)
                {
                    akaPos_x += akaSpeed;
                }
                if (akaPos_x == akaPos_xright)
                {
                    akaPos_xright = akaPos_x + 32;
                    akaPos_xleft = akaPos_x - 32;
                }
            }
            else if (enemyVec == 2)
            {
                aka_eye = 2;

                if (akaPos_y != akaPos_ydown)
                {
                    akaPos_y += akaSpeed;
                }
                if (akaPos_y == akaPos_ydown)
                {
                    akaPos_yup = akaPos_y - 32;
                    akaPos_ydown = akaPos_y + 32;
                }
            }
            else if (enemyVec == 3)
            {
                aka_eye = 3;

                if (akaPos_x != akaPos_xleft)
                {
                    akaPos_x -= akaSpeed;
                }
                if (akaPos_x == akaPos_xleft)
                {
                    akaPos_xright = akaPos_x + 32;
                    akaPos_xleft = akaPos_x - 32;
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