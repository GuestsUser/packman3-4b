#pragma once
class EnemyAra
{
public:
    EnemyAra();
    ~EnemyAra();

    //�A�J�x�C�p�ϐ�
    int akaPos_x;
    int akaPos_y;
    int akaPos_xright;
    int akaPos_yup;
    int akaPos_xleft;
    int akaPos_ydown;
    int akaSpeed;

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

    int targetPos_x;
    int targetPos_y;

    int distance[4];

    int minDistance;
    int enemyVec;

    int speedLevel;

    //enemy�`��֐�
    void enemyDraw();

    void enemyMove();

    void enemyUpdate();

    void enemyChangeSpeed();

private:

    //enemy�摜�i�[�p�ϐ�
    int enemyImage[20];

    //enemy�̖ڂ̉摜�i�[�p�ϐ�
    int enemyImage_eye[4];


};