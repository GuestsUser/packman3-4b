#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include <math.h>

//èâä˙âª
EnemyAra::EnemyAra()
{
    akaPos_x = 416;
    akaPos_y = 288;
    aka_eye = 0;
    aka_img = 0;
    akaPos_xright = akaPos_x + 16;
    akaPos_xleft = akaPos_x - 16;
    akaPos_yup = akaPos_y - 16;
    akaPos_ydown = akaPos_y + 16;
    akaSpeed = 1;
    akaAltPos_x = 0;
    akaAltPos_y = 0;


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
        distance[i] = 0;
    }

    minDistance = 9999;
    enemyVec = 3;


    speedLevel = 1;

    okMove = 1;

    count = 0;
    attack = 0;

    ijike = 0;
    ijikeRandom = 0;

    LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 32, 32, enemyImage);
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
    DrawRotaGraph(akaPos_x, akaPos_y, 1.0f, 0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)
    {
        DrawRotaGraph(akaPos_x, akaPos_y, 1.0f, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }
}

void EnemyAra::enemyMove()
{
    if (ijike == 0)
    {
        if (okMove == 0)
        {
            for (int i = 0; i < 28; i++)
            {
                for (int k = 0; k < 31; k++)
                {
                    if (akaPos_x == 16 * i + 192 && akaPos_y == 16 * k + 112)
                    {
                        okMove = 1;
                        akaAltPos_x = akaPos_x;
                        akaAltPos_y = akaPos_y;
                        distance[0] = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_x)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_yup)), 2));
                        distance[1] = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_xright)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_y)), 2));
                        distance[2] = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_x)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_ydown)), 2));
                        distance[3] = sqrt(pow(fabs(double(targetPos_x) - double(akaPos_xleft)), 2) + pow(fabs(double(targetPos_y) - double(akaPos_y)), 2));
                    }
                }
            }
        }
        else if (okMove == 1)
        {
            for (int i = 0; i < 4; i++)
            {
                if (minDistance > distance[i])
                {
                    minDistance = distance[i];

                    enemyVec = i;

                }
            }

            if (enemyVec == 0)
            {
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
                if (akaPos_y == akaPos_yup)
                {
                    minDistance = 9999;
                    enemyVec = -1;
                    okMove = 0;
                    akaPos_yup = akaPos_y - 16;
                    akaPos_ydown = akaPos_y + 16;
                }
            }
            else if (enemyVec == 1)
            {
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
                if (akaPos_x == akaPos_xright)
                {
                    minDistance = 9999;
                    enemyVec = -1;
                    okMove = 0;
                    akaPos_xright = akaPos_x + 16;
                    akaPos_xleft = akaPos_x - 16;
                }
            }
            else if (enemyVec == 2)
            {

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
                if (akaPos_y == akaPos_ydown)
                {
                    minDistance = 9999;
                    enemyVec = -1;
                    okMove = 0;
                    akaPos_yup = akaPos_y - 16;
                    akaPos_ydown = akaPos_y + 16;

                }
            }
            else if (enemyVec == 3)
            {
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
                if (akaPos_x == akaPos_xleft)
                {
                    minDistance = 9999;
                    enemyVec = -1;
                    okMove = 0;
                    akaPos_xright = akaPos_x + 16;
                    akaPos_xleft = akaPos_x - 16;
                }
            }
        }
    }

    DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", count);
    DrawFormatString(0, 50, GetColor(255, 255, 255), "%d", attack);
    DrawFormatString(0, 100, GetColor(255, 0, 0), "%d", targetPos_x);
    DrawFormatString(0, 150, GetColor(0, 0, 255), "%d", targetPos_y);
    DrawFormatString(0, 200, GetColor(0, 255, 255), "%d", enemyVec);
    DrawFormatString(0, 250, GetColor(0, 255, 255), "%d", minDistance);


}

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

void EnemyAra::enemyMode()
{
    count++;
    int flame = 60;

    switch (speedLevel)
    {
    case 1:
        if (count >= 0 && count < 7 * flame)
        {
            attack = 0;
        }
        else if (count >= 7 * flame && count < 27 * flame)
        {
            attack = 1;
        }
        else if (count >= 27 * flame && count < 34 * flame)
        {
            attack = 0;

        }
        else if (count >= 34 * flame && count < 54 * flame)
        {
            attack = 1;

        }
        else if (count >= 54 * flame && count < 59 * flame)
        {
            attack = 0;
        }
        else if (count >= 59 * flame && count < 79 * flame)
        {
            attack = 1;

        }
        else if (count >= 79 * flame && count < 84 * flame)
        {
            attack = 0;

        }
        else if (count >= 84 * flame)
        {
            attack = 1;

        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (ijike == 0)
    {
        if (attack == 1)
        {
            targetPos_x = 192;
            targetPos_y = 608;
        }
        else if (attack == 0)
        {
            targetPos_x = 640;
            targetPos_y = 112;
        }
    }

}

void EnemyAra::enemyIjike()
{
    if (ijike == 1)
    {
        aka_img = 16;

        if (ijikeRandom == 0)
        {
            if (akaPos_x != akaAltPos_x)
            {
                if (akaPos_x > akaAltPos_x)
                {
                    akaPos_x -= akaSpeed;
                }
                else if (akaPos_x < akaAltPos_x)
                {
                    akaPos_x += akaSpeed;
                }
            }
            if (akaPos_y != akaAltPos_y)
            {
                if (akaPos_y > akaAltPos_y)
                {
                    akaPos_y -= akaSpeed;
                }
                else if (akaPos_y < akaAltPos_y)
                {
                    akaPos_y += akaSpeed;
                }
            }
            else if (akaPos_x == akaAltPos_x && akaPos_y == akaAltPos_y)
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
    enemyIjike();
}