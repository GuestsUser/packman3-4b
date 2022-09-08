#pragma once
#include "Grid.h"
class EnemyAra {
public:
    enum class Type { red, pink, blue, orange }; //�G�̎��
private:
    bool reversOrder; //true�Ŏ��̈ړ���������I�ɔ��]�����ɐݒ肷��
    bool isUpdate; //false��update���s�֎~
    bool isDraw; //��L��draw��

     //�A�J�x�C�̃|�W�V�����ϐ�
    int drawX; //�`�ʗp�ʒu
    int drawY;

    int limitX;
    int limitY;

    int targetPos_x; //�ڕW�}�X�̃|�W�V�����ϐ�
    int targetPos_y;

    int speedLevel; //�X�s�[�h���x���i�[�ϐ�
    int speedCount;

    int center;
    int renderCenter;

    int count; //���Ԍo�ߕϐ�
    int attack; //�U����Ԑ؂�ւ��ϐ�
    int ijike; //�C�W�P��Ԑ؂�ւ��ϐ�

    int* enemyImage; //enemy�摜�i�[�p�ϐ�
    int* enemyImage_eye; //enemy�̖ڂ̉摜�i�[�p�ϐ�

    Direction enemyVec; //�G�̈ړ������ϐ�
    Type type; //�G�̎�ދL��
    Grid** tile; //�}�b�v�^�C���z��

    int ChangeSpeed();
    void Move(int move);
    void ModeChange();

    void SetCringeMove(); //�C�W�P��Ԏ��ʒu����֐��A����̓I�[�o�[���C�h����`���ł͂Ȃ�
    void SetReversMove(); //���Ε����ֈړ�������������֐�

    int ClculatSubX(Direction angle) const; //�w������̎�x�������ւ̓���Ɋ|���镄����Ԃ�
    int ClculatSubY(Direction angle) const; //��L��y��
    int ClculatLocalX()const; //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
    int ClculatLocalY()const; //��L��y��
    int ClculatLimitX(Direction angle)const; //���̈ʒu�ɒ������猻�݃}�X����ړ��\�������擾�������]������ʒu��Ԃ��Ă����
    int ClculatLimitY(Direction angle)const; //��L��y��
public:
    EnemyAra();
    void Draw();
    void Update();
    
    //Update�ADraw�̎��s�ێ擾�Ɛݒ�p�֐�
    void SetRunUpdate(bool set) { isUpdate = set; }
    void SetRunDraw(bool set) { isDraw = set; }
    bool GetRunUpdate() { return isUpdate; }
    bool GetRunDraw() { return isDraw; }

    virtual void SetAttackModeTarget() = 0; //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
    virtual void SetStandbyModeTarget() = 0; //��L�̓꒣�胂�[�h��
    virtual void SetWaitModeTarget() = 0; //���̒��̑ҋ@�ʒu����֐�

    void SetUp(Type setType, Direction setDirection, int setX, int setY); //�p����R���X�g���N�^���ŕK���Ăяo���K�v����AsetType�ɓG��ށAsetDirection�ɍŏ��Ɍ����Ă�����AsetX,Y�Ɍ��݈ʒu�����W�ő��
    void SetReversOrder(bool set) { reversOrder = set; } //true�Ŏ��̈ړ���������I�ɔ��]�����ɐݒ肷��

    Direction GetDirection() { return enemyVec; } //���݂̈ړ��������擾�ł���
    int ClculatTileX()const; //���݃}�X��Ԃ��Ă����
    int ClculatTileY()const; //��L��y��

    void TargetSet(int setX, int setY) { //�^�[�Q�b�g�}�X�w��A�w��̓��[�v�G���A���݂ōl����
        targetPos_x = setX;
        targetPos_y = setY;
    }
};