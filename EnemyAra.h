#pragma once
#include "Grid.h"
class EnemyAra
{
public:
    EnemyAra();
    ~EnemyAra();

    //�A�J�x�C�̃|�W�V�����ϐ�
    int akaPos_x;
    int akaPos_y;
    int akaDraw_x;
    int akaDraw_y;
    int akaMas_x;
    int akaMas_y;

    int aka_anim;

    int center;
    //�摜�ԍ��i�[�ϐ�
    int aka_eye;
    int aka_img;
    //���݃}�X�̏㉺���E�̃}�X�̃|�W�V�����ϐ�
    int akaPos_xright;
    int akaPos_yup;
    int akaPos_xleft;
    int akaPos_ydown;
    //�A�J�x�C�̈ړ��ʕϐ�
    int akaSpeed;
    //�A�J�x�C��1�}�X�O�̃|�W�V�����ϐ�
    int akaoldPos_x;
    int akaoldPos_y;


    //�A�I�X�P�p�ϐ�
    int aoPos_x;
    int aoPos_y;
    int aoSpeed;

    //�O�Y�^�p�ϐ�
    int orangePos_x;
    int orangePos_y;
    int orangeSpeed;

    //�s���L�[�p�ϐ�
    int pinkPos_x;
    int pinkPos_y;
    int pinkSpeed;

    //�ڕW�}�X�̃|�W�V�����ϐ�
    int targetPos_x;
    int targetPos_y;
    int targetDrow_x;
    int targetDrow_y;
    
    //�ڕW�}�X�Ƃ̋����i�[�ϐ�
    int distance[4];

    //�ڕW�}�X�Ƃ̍ŒZ�����i�[�ϐ�
    int minDistance;

    //�G�̈ړ������ϐ�
    int enemyVec;
    
    //�X�s�[�h���x���i�[�ϐ�
    int speedLevel;

    //�G�������Ă������̕ϐ�
    int okMove;

    //���Ԍo�ߕϐ�
    int count;
    //�U����Ԑ؂�ւ��ϐ�
    int attack;

    //�C�W�P��Ԑ؂�ւ��ϐ�
    int ijike;
    int ijikeRandom;

    //�G�̈ړ�����O�̌����i�[�ϐ�
    int enemyoldVec;

    // �ڕW�}�X�Ƃ̋���������ϐ�
    int distanceUP;
    int distanceLeft;
    int distanceDown;
    int distanceRight;

    int disCount;

    int speedCount;


    Direction nowDirection;

    Grid** tile;

    //enemy�`��֐�
    void enemyDraw();

    void enemyMove();

    void enemyUpdate();

    void enemyChangeSpeed();

    void enemyMode();

    void enemyIjike();

private:

    //enemy�摜�i�[�p�ϐ�
    int enemyImage[20];

    //enemy�̖ڂ̉摜�i�[�p�ϐ�
    int enemyImage_eye[4];


};