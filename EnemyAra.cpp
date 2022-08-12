#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include <math.h>

//èâä˙âª
EnemyAra::EnemyAra()
{
    akaPos_x = 640;
    akaPos_y = 360;
    akaPos_xright = 0;
    akaPos_yup = 0;
    akaPos_xleft = 0;
    akaPos_ydown = 0;
    akaSpeed = 15;

    aoPos_x = 0;
    aoPos_y = 0;
    aoSpeed = 0;

    orangePos_x = 0;
    orangePos_y = 0;
    orangeSpeed = 0;

    pinkPos_x = 0;
    pinkPos_y = 0;
    pinkSpeed = 0;

    targetPos_x = 960;
    targetPos_y = 540;

    for (int i = 0; i < 4; i++)
    {
        distance[i] = 0;
    }

    minDistance = 999;
    enemyVec = 0;


    speedLevel = 1;

    LoadDivGraph("Resource / image / monster.png", 20, 20, 1, 32, 32, enemyImage);
    LoadDivGraph("Resource / image / eyes.png", 4, 4, 1, 32, 32, enemyImage_eye);
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
    DrawRotaGraph(akaPos_x, akaPos_y, 1.0f, 0, enemyImage[0], FALSE, FALSE);
    DrawRotaGraph(akaPos_x, akaPos_y, 1.0f, 0, enemyImage_eye[0], FALSE, FALSE);
}

void EnemyAra::enemyMove()
{
    akaPos_xright = akaPos_x + 32;
    akaPos_xleft = akaPos_x - 32;

    akaPos_yup = akaPos_y + 32;
    akaPos_ydown = akaPos_y - 32;
    
    distance[0] = sqrt(pow(fabs(double(akaPos_x) - double(targetPos_x)),2) + pow(fabs(double(akaPos_yup) - double(targetPos_y)),2));
    distance[1] = sqrt(pow(fabs(double(akaPos_xright) - double(targetPos_x)), 2) + pow(fabs(double(akaPos_y) - double(targetPos_y)), 2));
    distance[2] = sqrt(pow(fabs(double(akaPos_x) - double(targetPos_x)), 2) + pow(fabs(double(akaPos_ydown) - double(targetPos_y)), 2));
    distance[3] = sqrt(pow(fabs(double(akaPos_xleft) - double(targetPos_x)), 2) + pow(fabs(double(akaPos_y) - double(targetPos_y)), 2));

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
        if (akaPos_y < akaPos_yup)
        {
            akaPos_y += akaSpeed;
        }
    }
    else if (enemyVec == 1)
    {
        if (akaPos_x < akaPos_xright)
        {
            akaPos_x += akaSpeed;
        }
    }
    else if (enemyVec == 2)
    {
        if (akaPos_y > akaPos_ydown)
        {
            akaPos_y -= akaSpeed;
        }
    }
    else if (enemyVec == 3)
    {
        if (akaPos_x > akaPos_xleft)
        {
            akaPos_x -= akaSpeed;
        }
    }

}

void EnemyAra::enemyChangeSpeed()
{
    switch (speedLevel)
    {
        case 1:
            akaSpeed = 15;
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

void EnemyAra::enemyUpdate()
{
    enemyDraw();
    enemyMove();
    enemyChangeSpeed();
}