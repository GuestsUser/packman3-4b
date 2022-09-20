#pragma once
#include "Grid.h"
#include <deque>
class EnemyAra {
public:
    enum class MoveMode { standby, attack }; //�꒣�胂�[�h���U�����[�h���̗񋓌^
    enum class State { neutral, cringe, damage, wait, ready }; //�G�̏�ԁA���̏�Ԃɉ����ă}�X�̈ړ��\�����擾�z���ς��鑼�A�ړ��挈��֐����ύX����
    enum class Type { red, pink, blue, orange }; //�G�̎��
private:
    static int nowStage; //���݃X�e�[�W��
    static int timer; //�꒣��A�ǂ��������[�h�̃��[�h�`�F���W�p�^�C�}�[
    static MoveMode moveMode; //�꒣��A�U���̃��[�h�`�F���W�͑S�G���ʂȂ̂�static
    State state; //��Ԃ͓G�ɂ�肯��Ȃ̂Œʏ�ϐ�
    State imageState; //state��wait��ready�̎��A���݉摜��ێ�����ׂ�state

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

    int speedCount;

    int center;
    int renderCenter;

    int count; //���Ԍo�ߕϐ�
    int warp;   //���[�v���X�s�[�h�؂�ւ�

    int* enemyImage; //enemy�摜�i�[�p�ϐ�
    int* enemyImage_eye; //enemy�̖ڂ̉摜�i�[�p�ϐ�

    Direction enemyVec; //�G�̈ړ������ϐ�
    Direction oldVec; //�����ԓG�̖ڂ̕����Œ�p
    Type type; //�G�̎�ދL��
    Grid** tile; //�}�b�v�^�C���z��

    int ChangeSpeed();
    void Move(int move);
    

    void SetCringeMove(); //�C�W�P��Ԏ��ʒu����֐��A����̓I�[�o�[���C�h����`���ł͂Ȃ�
    void SetReversMove(); //���Ε����ֈړ�������������֐�

    int ClculatSubX(Direction angle) const; //�w������̎�x�������ւ̓���Ɋ|���镄����Ԃ�
    int ClculatSubY(Direction angle) const; //��L��y��
    int ClculatLocalX()const; //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
    int ClculatLocalY()const; //��L��y��
    int ClculatLimitX(Direction angle)const; //���̈ʒu�ɒ������猻�݃}�X����ړ��\�������擾�������]������ʒu��Ԃ��Ă����
    int ClculatLimitY(Direction angle)const; //��L��y��

    const ::Move* ReadTile(int x, int y); //����state�ɉ�����[x][y]�ʒu�̈ړ��\�����z���Ԃ�

public:
    EnemyAra();
    void Draw();
    void Update();
    
    //Update�ADraw�̎��s�ێ擾�Ɛݒ�p�֐�
    void SetRunUpdate(bool set) { isUpdate = set; }
    void SetRunDraw(bool set) { isDraw = set; }
    bool GetRunUpdate() { return isUpdate; }
    bool GetRunDraw() { return isDraw; }

    int GetDrawX() const; //�\���n�֐��ɒ��ڎw��\�Ȓl��Ԃ�
    int GetDrawY() const; //��L��y��

    static void ModeChange(std::deque<EnemyAra*>* enemyList); //�꒣��A�ǂ��������[�h�̃��[�h�`�F���W�p�֐��A�V�[������1

    virtual void SetAttackModeTarget() = 0; //�ǂ��������[�h���̑_���}�X����֐��A�I�[�o�[���C�h���Ďg��
    virtual void SetStandbyModeTarget() = 0; //��L�̓꒣�胂�[�h��
    virtual void SetWaitModeTarget() = 0; //���̒��̑ҋ@�ʒu����֐�

    virtual int Spurt() { return -1; } //�ʏ�ȊO�̑��x������G�͂�����I�[�o�[���C�h���ē�����J�X�^������A�Ԃ�l-1�̓X�p�[�g�𗘗p���Ȃ�����

    void SetUp(Type setType, Direction setDirection, int setX, int setY); //�p����R���X�g���N�^���ŕK���Ăяo���K�v����AsetType�ɓG��ށAsetDirection�ɍŏ��Ɍ����Ă�����AsetX,Y�Ɍ��݈ʒu�����W�ő��
    void SetReversOrder(bool set) { //true�Ŏ��̈ړ���������I�ɔ��]�����ɐݒ肷��
        if (state == State::neutral || state == State::cringe) { reversOrder = set; } //�ʏ�ƃC�W�P��Ԃ̏ꍇ�������]���󂯕t����
    }

    Direction GetDirection() { return enemyVec; } //���݂̈ړ��������擾�ł���
    int ClculatTileX()const; //���݃}�X��Ԃ��Ă����
    int ClculatTileY()const; //��L��y��
    static int ClculatSpeedLevel() { return (nowStage > 0) + (nowStage >= 4) + (nowStage >= 21); } //���݂̑��x���x�����v�Z

    void TargetSet(int setX, int setY) { //�^�[�Q�b�g�}�X�w��A�w��̓��[�v�G���A���݂ōl����
        targetPos_x = setX;
        targetPos_y = setY;
    }

    void SetState(State set) { 
        if (state == State::wait || state == State::ready) { imageState = set; } //�G���ҋ@�A�����甲�����Ԃ̏ꍇ�摜�X�e�[�g��ύX����
        else { state = set; } //����ȊO�Ȃ�state��ύX����
    }
    void SetStateReinterpret(State set) { state = set; } //state�̏�ԂɊ֌W�Ȃ������Z�b�g�A�g�p�͔񏧗�
    static void SetMoveMode(MoveMode set) { moveMode = set; }

    State GetState() { return state; }
    State GetImageState() { return imageState; }
    static MoveMode GetMoveMode() { return moveMode; }
};