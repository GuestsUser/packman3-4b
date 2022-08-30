#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>

//èâä˙âª
EnemyAra::EnemyAra()
{
    akaPos_x = 17;//17
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

    attack = 0;

    speedCount = 0;

    okRand = 1;
    enemyRand = 0;

    nowDirection = Direction::left;
    tile = WorldVal::Get<Grid*>("map");

    LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 16, 16, enemyImage);
    LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 32, 32, enemyImage_eye);
}
//çÌèú
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
    //ìGÇ∆ìGÇÃñ⁄Çï\é¶
    DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE , SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE , 0, 0,X_RATE,Y_RATE,0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)//ÉCÉWÉPÇ∂Ç·Ç»Ç¢Ç»ÇÁ
    {
        DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, 1, 1, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }

}

void EnemyAra::enemyMove()
{
    akaPos_x = akaDraw_x / TILE;
    akaPos_y = akaDraw_y / TILE;

    if (ijike == 0)//ÉCÉWÉPÇ∂Ç·Ç»Ç¢Ç»ÇÁ
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

                if ((enemyoldVec + 2) % 4 == i) { continue; } //ç°âÒÇÃiÇ™îΩëŒï˚å¸ÇæÇ¡ÇΩèÍçáîÚÇŒÇ∑
                if (tile[akaPos_x][akaPos_y].ReadEnemy()[i] == Move::block) { continue; } //à⁄ìÆïsâ¬Ç»ÇÁîÚÇŒÇ∑
                
                int useY, useX;

                if (i == 0 || i == 2)
                {
                    useY = 1;
                    useX = 0;
                }//yé≤ï˚å¸Ç÷ÇÃà⁄ìÆÇ»ÇÁ1ÅAÇªÇ§Ç≈Ç»Ç¢Ç»ÇÁ0Ç…Ç»ÇÈ

                if (i == 1 || i == 3)
                {
                    useY = 0;
                    useX = 1;
                }
                int sub = -1 + 2 * (int)(i / 2 > 0); //êiÇﬁï˚å¸ÇÃïÑçÜÅAè„ÅAç∂Ç»ÇÁÉ}ÉCÉiÉXÅAâ∫ÅAâEÇ»ÇÁÉvÉâÉXÇèoÇ∑
                int x = akaPos_x + sub * useX; //Ç±Ç±Ç≈Ç†ÇÈposÇÕåªç›ÇÃÉ}ÉXç¿ïWÇéwÇ∑
                int y = akaPos_y + sub * useY;

                distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

                disCount++;

                //ñ⁄ïWÉ}ÉXÇ∆ÇÃç≈íZãóó£Çí≤Ç◊ÇƒenemyVecÇ…ç≈íZï˚å¸ÇÃÇ‡ÇÃÇäiî[
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
        else if (okMove == 1)//ìÆÇ¢ÇƒÇ¢Ç¢èÛë‘Ç»ÇÁ
        {
            //ç≈íZï˚å¸Ç™è„Ç»ÇÁ
            if (enemyVec == 0)
            {


                if (enemyoldVec != 0)
                {
                    enemyoldVec = 0;//è„ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                }

                //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                if (akaPos_y != akaPos_yup)
                {
                    akaDraw_y -= akaMove;
                    if (ijike == 0)
                    {
                        aka_eye = 0;

                        aka_anim++;
                        aka_img = aka_anim / 4 % 2;

                    }
                    
                }

                //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                if (akaPos_y == akaPos_yup)
                {
                    enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                    okMove = 0;//àÍèuìÆÇØÇ»Ç¢èÛë‘Ç…Ç∑ÇÈ
                }
            }
            //ç≈íZï˚å¸Ç™ç∂Ç»ÇÁ
            else if (enemyVec == 1)
            {


                if (enemyoldVec != 1)
                {
                    enemyoldVec = 1;//ç∂ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                }

                //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                if (akaPos_x != akaPos_xleft)
                {
                    akaDraw_x -= akaMove;
                    if (ijike == 0)
                    {
                        aka_eye = 3;

                        aka_anim++;
                        aka_img = aka_anim / 4 % 2;

                    }
                }

                //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                if (akaPos_x == akaPos_xleft)
                {
                    enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                    okMove = 0;//àÍèuìÆÇØÇ»Ç¢èÛë‘Ç…Ç∑ÇÈ
                }
            }
            //ç≈íZï˚å¸Ç™â∫Ç»ÇÁ
            else if (enemyVec == 2)
            {
                if (enemyoldVec != 2)
                {
                    enemyoldVec = 2;//â∫ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                }

                //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                if (akaPos_y != akaPos_ydown)
                {
                    akaDraw_y += akaMove;
                    if (ijike == 0)
                    {
                        aka_eye = 2;

                        aka_anim++;
                        aka_img = aka_anim / 4 % 2;

                    }
                }

                //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                if (akaPos_y == akaPos_ydown)
                {
                    enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                    okMove = 0;//àÍèuìÆÇØÇ»Ç¢èÛë‘Ç…Ç∑ÇÈ

                }
            }
            //ç≈íZï˚å¸Ç™âEÇ»ÇÁ
            else if (enemyVec == 3)
            {
                if (enemyoldVec != 3)
                {
                    enemyoldVec = 3;//âEï˚å¸èÛë‘Ç…Ç∑ÇÈ
                }

                //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                if (akaPos_x != akaPos_xright)
                {
                    akaDraw_x += akaMove;
                    if (ijike == 0)
                    {
                        aka_eye = 1;

                        aka_anim++;
                        aka_img = aka_anim / 4 % 2;

                    }
                }

                //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                if (akaPos_x == akaPos_xright)
                {
                    enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                    okMove = 0;//àÍèuìÆÇØÇ»Ç¢èÛë‘Ç…Ç∑ÇÈ
                }
            }
        }
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", count);
    DrawFormatString(0, 50, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(0, 100, GetColor(255, 0, 0), "%d", akaPos_x);
    DrawFormatString(0, 150, GetColor(0, 0, 255), "%d", akaPos_y);
    DrawFormatString(0, 200, GetColor(0, 255, 255), "%d", enemyVec);




}
//ÉXÉsÅ[ÉhÉåÉxÉãÇ…ÇÊÇ¡ÇƒÉXÉsÅ[ÉhÇïœÇ¶ÇÈ
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

        speedCount += akaSpeed;
        akaMove = speedCount / MOVABLE_SPEED;
        speedCount -= akaMove * MOVABLE_SPEED;

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

//çUåÇèÛë‘ÅAãxåeèÛë‘ÇÃêÿÇËë÷Ç¶
void EnemyAra::enemyMode()
{
    count++;//éûä‘åoâﬂ
    int flame = 60;//ÉtÉåÅ[ÉÄÉåÅ[Ég

    switch (speedLevel)
    {
    case 1:
        if (count >= 0 && count < 7 * flame)//0Å`7ïbÇÃéûãxåe
        {
            attack = 0;//ãxåeèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "ãxëß", attack);//143//136
        }
        else if (count >= 7 * flame && count < 27 * flame)//7Å`27ïbÇÃéûçUåÇ
        {
            attack = 1;//çUåÇèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "çUåÇ", attack);//143//136
        }
        else if (count >= 27 * flame && count < 34 * flame)//27Å`34ïbÇÃéûãxåe
        {
            attack = 0;//ãxåeèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "ãxëß", attack);//143//136
        }
        else if (count >= 34 * flame && count < 54 * flame)//34Å`54ïbÇÃéûçUåÇ
        {
            attack = 1;//çUåÇèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "çUåÇ", attack);//143//136

        }
        else if (count >= 54 * flame && count < 59 * flame)//54Å`59ïbÇÃéûãxåe
        {
            attack = 0;//ãxåeèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "ãxëß", attack);//143//136

        }
        else if (count >= 59 * flame && count < 79 * flame)//59Å`79ïbÇÃéûçUåÇ
        {
            attack = 1;//çUåÇèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "çUåÇ", attack);//143//136


        }
        else if (count >= 79 * flame && count < 84 * flame)//79Å`84ïbÇÃéûãxåe
        {
            attack = 0;//ãxåeèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "ãxëß", attack);//143//136


        }
        else if (count >= 84 * flame)//84ïbà»ç~ÇÕçUåÇ
        {
            attack = 1;//çUåÇèÛë‘
            DrawFormatString(0, 250, GetColor(0, 255, 255), "çUåÇ", attack);//143//136


        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (ijike == 0)//ÉCÉWÉPÇ∂Ç·Ç»Ç¢Ç»ÇÁ
    {
        if (attack == 1)//çUåÇèÛë‘Ç»ÇÁ
        {
            //ñ⁄ïWÉ}ÉXÇÉpÉbÉNÉ}ÉìÇÃÇ¢ÇÈÉ}ÉX
            targetPos_x = 5;
            targetPos_y = 0;
        }
        else if (attack == 0)//ãxåeèÛë‘Ç»ÇÁ
        {
            //ñ⁄ïWÉ}ÉXÇâEè„
            targetPos_x = 5;
            targetPos_y = 0;
        }
    }

}

//ÉCÉWÉPèÛë‘èàóù
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
                    akaDraw_x -= akaMove;
                }
                else if (akaPos_x < akaoldPos_x)
                {
                    akaDraw_x += akaMove;
                }
            }
            if (akaPos_y != akaoldPos_y)
            {
                if (akaPos_y > akaoldPos_y)
                {
                    akaDraw_y -= akaMove;
                }
                else if (akaPos_y < akaoldPos_y)
                {
                    akaDraw_y += akaMove;
                }
            }
            else if (akaPos_x == akaoldPos_x && akaPos_y == akaoldPos_y)
            {
                ijikeRandom = 1;
            }
        }
        else if (ijikeRandom == 1)
        {
            if (okRand == 1)
            {
                enemyRand = GetRand(3);
                okRand = 0;

            }
            if (okRand == 0)
            {


                if (tile[akaPos_x][akaPos_y].ReadEnemy()[enemyRand] == Move::movable)
                {
                    enemyVec = enemyRand;
                }


                //ç≈íZï˚å¸Ç™è„Ç»ÇÁ
                if (enemyVec == 0)
                {
                    if (enemyoldVec != 0)
                    {
                        enemyoldVec = 0;//è„ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                    }

                    //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                    if (akaPos_y != akaPos_yup)
                    {
                        akaDraw_y -= akaMove;
                    }

                    //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                    if (akaPos_y == akaPos_yup)
                    {
                        enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                        okRand = 1;
                    }
                }
                //ç≈íZï˚å¸Ç™ç∂Ç»ÇÁ
                else if (enemyVec == 1)
                {
                    if (enemyoldVec != 1)
                    {
                        enemyoldVec = 1;//ç∂ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                    }

                    //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                    if (akaPos_x != akaPos_xleft)
                    {
                        akaDraw_x -= akaMove;
                    }

                    //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                    if (akaPos_x == akaPos_xleft)
                    {
                        enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                        okRand = 1;
                    }
                }
                //ç≈íZï˚å¸Ç™â∫Ç»ÇÁ
                else if (enemyVec == 2)
                {
                    if (enemyoldVec != 2)
                    {
                        enemyoldVec = 2;//â∫ï˚å¸èÛë‘Ç…Ç∑ÇÈ
                    }

                    //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                    if (akaPos_y != akaPos_ydown)
                    {
                        akaDraw_y += akaMove;
                    }

                    //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                    if (akaPos_y == akaPos_ydown)
                    {
                        enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                        okRand = 1;

                    }
                }
                //ç≈íZï˚å¸Ç™âEÇ»ÇÁ
                else if (enemyVec == 3)
                {
                    if (enemyoldVec != 3)
                    {
                        enemyoldVec = 3;//âEï˚å¸èÛë‘Ç…Ç∑ÇÈ
                    }

                    //éüÇÃÉ}ÉXÇ‹Ç≈à⁄ìÆÇ∑ÇÈ
                    if (akaPos_x != akaPos_xright)
                    {
                        akaDraw_x += akaMove;
                    }

                    //éüÇÃÉ}ÉXÇ…Ç¬Ç¢ÇΩÇÁ
                    if (akaPos_x == akaPos_xright)
                    {
                        enemyVec = -1;//à⁄ìÆï˚å¸ÇàÍèuñ≥Ç≠Ç∑
                        okRand = 1;
                    }
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