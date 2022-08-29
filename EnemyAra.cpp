#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>

//初期化
EnemyAra::EnemyAra()
{
    akaPos_x = 17;//17
    akaPos_y = 11;//11

    center = 7;

    akaDraw_x = akaPos_x * TILE + (TILE - 1);
    akaDraw_y = akaPos_y * TILE + (TILE - 1) / 2;

    akaMas_x = 0;
    akaMas_y = 0;

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

    targetPos_x = 30;
    targetPos_y = 0;
    targetDrow_x = 0;
    targetDrow_y = 0;

    for (int i = 0; i < 4; i++)
    {
        distance[i] = 9999;
    }

    minDistance = 9999;
    enemyVec = 1;

    akaPos_yup = akaPos_y - 1;
    akaPos_xleft = akaPos_x - 1;
    akaPos_ydown = akaPos_y + 1;
    akaPos_xright = akaPos_x + 1;


    speedLevel = 1;

    okMove = 1;

    count = 0;
    attack = 0;

    ijike = 0;
    ijikeRandom = 0;

    enemyoldVec = 1;

    distanceUP = 0;
    distanceLeft = 0;
    distanceDown = 0;
    distanceRight = 0;

    disCount = 0;

    nowDirection = Direction::left;
    tile = WorldVal::Get<Grid*>("map");

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
    DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE , SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE , 0, 0,X_RATE,Y_RATE,0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)//イジケじゃないなら
    {
        DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, 1, 1, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }

}

void EnemyAra::enemyMove()
{
    akaPos_x = akaDraw_x / TILE;
    akaPos_y = akaDraw_y / TILE;

    if (ijike == 0)//イジケじゃないなら
    {

        if (okMove == 0)
        {

            akaPos_yup = akaPos_y - 1;
            akaPos_xleft = akaPos_x - 1;
            akaPos_ydown = akaPos_y + 1;
            akaPos_xright = akaPos_x + 1;

            minDistance = 9999;

            for (int i = 0; i < 4; i++)
            {
                distance[i] = 9999;

                if ((enemyoldVec + 2) % 4 == i) { continue; } //今回のiが反対方向だった場合飛ばす
                if (tile[akaPos_x + WARP_AREA_X][akaPos_y + WARP_AREA_Y].ReadEnemy()[i] == Move::block) { continue; } //移動不可なら飛ばす

                int useY = (int)(i % 2 == 0); //y軸方向への移動なら1、そうでないなら0になる
                int sub = -1 + 2 * (int)(i / 2 > 0); //進む方向の符号、上、左ならマイナス、下、右ならプラスを出す
                int x = akaPos_x + sub * useY; //ここであるposは現在のマス座標を指す
                int y = akaPos_y + sub * useY;

                distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

                disCount++;

                //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
                if (minDistance > distance[i])
                {
                    minDistance = distance[i];

                    enemyVec = i;
                }
            }

            if (disCount == 0)
            {
                if (enemyVec == 0)
                {
                    enemyVec = 2;
                }
                if (enemyVec == 1)
                {
                    enemyVec = 3;
                }
                if (enemyVec == 2)
                {
                    enemyVec = 0;
                }
                if (enemyVec == 3)
                {
                    enemyVec = 1;
                }
            }

            okMove = 1;

        }
        else if (okMove == 1)//動いていい状態なら
        {
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
                    akaDraw_y -= akaSpeed;
                    //if (ijike == 0)
                    //{
                    //    aka_eye = 0;

                    //    if (aka_img < 2)
                    //    {
                    //        aka_img++;
                    //    }
                    //    if (aka_img >= 2)
                    //    {
                    //        aka_img = 0;
                    //    }
                    //}
                }

                //次のマスについたら
                if (akaPos_y == akaPos_yup)
                {
                    minDistance = 9999;//最短距離初期化
                    enemyVec = -1;//移動方向を一瞬無くす
                    okMove = 0;//一瞬動けない状態にする
                    akaPos_yup = akaPos_y - 1;//動いた後のマスの次のマスの情報取得
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

                    akaDraw_x -= akaSpeed;
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
                    akaPos_xleft = akaPos_x - 1;//動いた後のマスの次のマスの情報取得
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
                    akaDraw_y += akaSpeed;
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
                    akaPos_ydown = akaPos_y + 1;//動いた後のマスの次のマスの情報取得

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
                    akaDraw_x += akaSpeed;
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
                    akaPos_xright = akaPos_x + 1;//動いた後のマスの次のマスの情報取得
                }
            }
        }
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", count);
    DrawFormatString(0, 50, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(0, 100, GetColor(255, 0, 0), "%d", akaPos_x);
    DrawFormatString(0, 150, GetColor(0, 0, 255), "%d", akaPos_y);
    DrawFormatString(0, 200, GetColor(0, 255, 255), "%d", enemyVec);
    DrawFormatString(0, 250, GetColor(0, 255, 255), "%d", akaDraw_x);//143//136
    DrawFormatString(0, 300, GetColor(0, 255, 255), "%d", akaDraw_y);//91//84



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
            targetPos_x = 5;
            targetPos_y = 0;
        }
        else if (attack == 0)//休憩状態なら
        {
            //目標マスを右上
            targetPos_x = 30;
            targetPos_y = 0;
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