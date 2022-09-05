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
    int akaMove;

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

    //�ڕW�}�X�̃|�W�V�����ϐ�
    int targetPos_x;
    int targetPos_y;
    int targetDrow_x;
    int targetDrow_y;

    //�G�̈ړ������ϐ�
    int enemyVec;
    
    //�X�s�[�h���x���i�[�ϐ�
    int speedLevel;

    //���Ԍo�ߕϐ�
    int count;
    //�U����Ԑ؂�ւ��ϐ�
    int attack;

    //�C�W�P��Ԑ؂�ւ��ϐ�
    int ijike;
    int okIjikeMove;
    int ijikeRandom;
    int ijikeHanten;

    //�G�̈ړ�����O�̌����i�[�ϐ�
    int enemyoldVec;

    // �ڕW�}�X�Ƃ̋���������ϐ�
    int distanceUP;
    int distanceLeft;
    int distanceDown;
    int distanceRight;

    int speedCount;

    int enemyRand;
    int okRand;

    int hantenMode;
    int okHanten;

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
    bool reversOrder; //true�Ŏ��̈ړ���������I�ɔ��]�����ɐݒ肷��

    //enemy�摜�i�[�p�ϐ�
    int enemyImage[20];

    //enemy�̖ڂ̉摜�i�[�p�ϐ�
    int enemyImage_eye[4];

    //virtual void SetAttackModeTarget() = 0; //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
    //virtual void SetStandbyModeTarget() = 0; //��L�̓꒣�胂�[�h��
    //virtual void SetWaitModeTarget() = 0; //���̒��̑ҋ@�ʒu����֐�

    void SetAttackModeTarget(); //�e�X�g�p����
    void SetStandbyModeTarget();
    void SetWaitModeTarget();

    void SetCringeMove(); //�C�W�P��Ԏ��ʒu����֐��A����̓I�[�o�[���C�h����`���ł͂Ȃ�
    void SetReversMove(); //���Ε����ֈړ�������������֐�
    int ClculatSubX(int angle) const; //�w������̎�x�������ւ̓���Ɋ|���镄����Ԃ�
    int ClculatSubY(int angle) const; //��L��y��

    void SetReversOrder(bool set) { reversOrder = set; }
};