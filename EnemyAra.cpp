#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>
#include <deque>

//������
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
//�폜
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
    //�G�ƓG�̖ڂ�\��
    DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE , SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE , 0, 0, X_RATE, Y_RATE,0, enemyImage[aka_img], TRUE, FALSE);
    if (ijike == 0)//�C�W�P����Ȃ��Ȃ�
    {
        DrawRotaGraph3(SHIFT_X + (akaDraw_x - WARP_AREA_X * TILE - center) * X_RATE, SHIFT_Y + (akaDraw_y - WARP_AREA_Y * TILE - center) * Y_RATE, 0, 0, 1, 1, 0, enemyImage_eye[aka_eye], TRUE, FALSE);
    }

}

void EnemyAra::enemyMove() {
    int currentTileX = akaDraw_x / TILE;
    int currentTileY = akaDraw_y / TILE;
    while (currentTileX != akaPos_x || currentTileY != akaPos_y) { //�}�X�ړ����������ꍇ(while���g���Ă���͉̂��Lif����break��p��������������Ń��[�v�̈Ӑ}�͂Ȃ�)
        if (attack) { SetAttackModeTarget(); } //�^�[�Q�b�g�}�X�̐ݒ�(�ǂ��������[�h�̎�)
        else { SetStandbyModeTarget(); } //�^�[�Q�b�g�}�X(�꒣�胂�[�h)
        if (reversOrder) { SetReversMove(); break; } //���]�����ړ��͈ړ�������肷��̂ňȍ~�̈ړ��挈�菈����ʂ�K�v���Ȃ�����break
        if (ijike) { SetCringeMove(); break; } //�C�W�P��Ԃ̏ꍇ���ړ��挈��Ȃ̂ŏI�������break

        int distance[4] = { 9999 ,9999 ,9999 ,9999 }; //�e��ړ��\�����ɐi�񂾃}�X����ڕW�}�X�ւ̋����ۑ��p
        int minDistance = 9999; //�ŒZ�����L�^�p
        int newDirection= (enemyVec + 2) % 4; //�V�����ړ������A��芸�������Ε����ɐݒ肷�鎖�łǂ̃}�X���ړ��s�\�������ꍇ�����I�ɔ��Ε������ݒ肳���Ƃ����Z�i

        for (int i = 0; i < 4; i++) {
            if ((enemyVec + 2) % 4 == i) { continue; } //�����i�����Ε����������ꍇ��΂�
            if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::block) { continue; } //�ړ��s�Ȃ��΂�

            //int useY, useX;

            //if (i == 0 || i == 2)
            //{
            //    useY = 1;
            //    useX = 0;
            //}//y�������ւ̈ړ��Ȃ�1�A�����łȂ��Ȃ�0�ɂȂ�

            //if (i == 1 || i == 3)
            //{
            //    useY = 0;
            //    useX = 1;
            //}
            //int sub = -1 + 2 * (int)(i / 2 > 0); //�i�ޕ����̕����A��A���Ȃ�}�C�i�X�A���A�E�Ȃ�v���X���o��
            //int x = akaPos_x + sub * useX; //�����ł���pos�͌��݂̃}�X���W���w��
            //int y = akaPos_y + sub * useY;

            int x = currentTileX + ClculatSubX(i); //�����ł���pos�͌��݂̃}�X���W���w��
            int y = currentTileY + ClculatSubY(i);
            distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance[i]) { //�ڕW�}�X�Ƃ̍ŒZ�����𒲂ׂ�enemyVec�ɍŒZ�����̂��̂��i�[
                minDistance = distance[i];
                newDirection = i;
            }
        }
        enemyVec = newDirection; //�V���������ɐݒ�
        break;
    }
    akaPos_x = currentTileX; //���ݏ����}�X��V�������ɕύX
    akaPos_y = currentTileY;

    akaDraw_x += akaMove * ClculatSubX(enemyVec); //���݂̈ړ������ɍ��킹�Ċe���Ɉړ��ʂ����Z�A���Z���Ă����
    akaDraw_y += akaMove * ClculatSubY(enemyVec);
    aka_eye = enemyVec; //�ڂ̌����̎w��
    aka_anim++;
    aka_img = aka_anim / 4 % 2;

    SetFontSize(30);
    DrawFormatString(700, 30, GetColor(255, 255, 255), "Time�F%.2lf", (double)count / 60);
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(700, 100, GetColor(255, 255, 255), "�Z�G�l�~�[���");
    DrawFormatString(700, 150, GetColor(255, 0, 0), "X�ʒu�F%d", akaPos_x);
    DrawFormatString(700, 200, GetColor(0, 0, 255), "Y�ʒu�F%d", akaPos_y);
    DrawFormatString(700, 250, GetColor(0, 255, 0), "�ړ������F%d", enemyVec);
}
//�X�s�[�h���x���ɂ���ăX�s�[�h��ς���
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

//�U����ԁA�x�e��Ԃ̐؂�ւ�
void EnemyAra::enemyMode()
{
    count++;//���Ԍo��

    switch (speedLevel)
    {
    case 1:
        if (count >= 0 && count < 7 * FPS)//0�`7�b�̎��x�e
        {
            attack = 0;//�x�e���

            DrawFormatString(700, 300, GetColor(0, 255, 255), "�x����");
        }
        else if (count >= 7 * FPS && count < 27 * FPS)//7�`27�b�̎��U��
        {
            attack = 1;//�U�����

            DrawFormatString(700, 300, GetColor(255, 255, 0), "�U����");
        }
        else if (count >= 27 * FPS && count < 34 * FPS)//27�`34�b�̎��x�e
        {
            attack = 0;//�x�e���

            DrawFormatString(700, 300, GetColor(0, 255, 255), "�x����");
        }
        else if (count >= 34 * FPS && count < 54 * FPS)//34�`54�b�̎��U��
        {
            attack = 1;//�U�����

            DrawFormatString(700, 300, GetColor(255, 255, 0), "�U����");
        }
        else if (count >= 54 * FPS && count < 59 * FPS)//54�`59�b�̎��x�e
        {
            attack = 0;//�x�e���

            DrawFormatString(700, 300, GetColor(0, 255, 255), "�x����");
        }
        else if (count >= 59 * FPS && count < 79 * FPS)//59�`79�b�̎��U��
        {
            attack = 1;//�U�����

            DrawFormatString(700, 300, GetColor(255, 255, 0), "�U����");
        }
        else if (count >= 79 * FPS && count < 84 * FPS)//79�`84�b�̎��x�e
        {
            attack = 0;//�x�e���

            DrawFormatString(700, 300, GetColor(0, 255, 255), "�x����");
        }
        else if (count >= 84 * FPS)//84�b�ȍ~�͍U��
        {
            attack = 1;//�U�����

            DrawFormatString(700, 300, GetColor(255, 255, 0), "�U����");
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if (ijike == 0)//�C�W�P����Ȃ��Ȃ�
    {
        if (attack == 1)//�U����ԂȂ�
        {
            //�ڕW�}�X���p�b�N�}���̂���}�X
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
        else if (attack == 0)//�x�e��ԂȂ�
        {
            //�ڕW�}�X���E��

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

//�C�W�P��ԏ���
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
                    enemyoldVec = 0;//�������Ԃɂ���
                }

                //���̃}�X�܂ňړ�����
                if (akaPos_y != akaPos_yup)
                {
                    akaDraw_y -= akaMove;
                }

                //���̃}�X�ɂ�����
                if (akaPos_y == akaPos_yup)
                {
                    okIjikeMove = 0;//��u�����Ȃ���Ԃɂ���
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //�ŒZ���������Ȃ�
            else if (enemyVec == 1)
            {
                if (enemyoldVec != 1)
                {
                    enemyoldVec = 1;//��������Ԃɂ���
                }

                //���̃}�X�܂ňړ�����
                if (akaPos_x != akaPos_xleft)
                {
                    akaDraw_x -= akaMove;
                }

                //���̃}�X�ɂ�����
                if (akaPos_x == akaPos_xleft)
                {
                    okIjikeMove = 0;//��u�����Ȃ���Ԃɂ���
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //�ŒZ���������Ȃ�
            else if (enemyVec == 2)
            {
                if (enemyoldVec != 2)
                {
                    enemyoldVec = 2;//��������Ԃɂ���
                }

                //���̃}�X�܂ňړ�����
                if (akaPos_y != akaPos_ydown)
                {
                    akaDraw_y += akaMove;
                }

                //���̃}�X�ɂ�����
                if (akaPos_y == akaPos_ydown)
                {
                    okIjikeMove = 0;//��u�����Ȃ���Ԃɂ���
                    ijikeHanten = 0;
                    ijikeRandom = 1;
                }
            }
            //�ŒZ�������E�Ȃ�
            else if (enemyVec == 3)
            {
                if (enemyoldVec != 3)
                {
                    enemyoldVec = 3;//�E������Ԃɂ���
                }

                //���̃}�X�܂ňړ�����
                if (akaPos_x != akaPos_xright)
                {
                    akaDraw_x += akaMove;
                }

                //���̃}�X�ɂ�����
                if (akaPos_x == akaPos_xright)
                {
                    okIjikeMove = 0;//��u�����Ȃ���Ԃɂ���
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
    int revers = (enemyoldVec + 2) % 4; //�i�s�����̔��Ε���
    std::deque<int> subList = std::deque<int>(); //�ړ��\�ȕ�����ۗL���铮�I�z��
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //�����i�����Ε����������ꍇ��΂�
        if (tile[akaPos_x][akaPos_y].ReadEnemy()[i] == Move::movable) { subList.push_back(i); } //�ړ��\�Ȃ玝���Ă���
    }
    if (subList.size() <= 0) { enemyVec = revers; } //�ǂ̕����ɂ������Ȃ��ꍇ�A�ړ������𔽑΂ɐݒ�
    else { enemyVec = GetRand(subList[subList.size() - 1]); } //�ړ��\�ȕ������烉���_���ɕ��������o���A�ݒ肷��
}

void EnemyAra::SetReversMove() { 
    enemyVec = (enemyoldVec + 2) % 4; //��������𔽑΂ɐݒ肷��
    reversOrder = false; //���]���߂����s�����̂�false�ɂ���
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