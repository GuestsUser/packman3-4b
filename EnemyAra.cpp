#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "DebugUtility.h"
#include <math.h>
#include <deque>

//������
EnemyAra::EnemyAra() {
    isUpdate = true;
    isDraw = true;

    type = Type::red; //��芸�����A�J�x�C����
    center = 3;
    renderCenter = 4;

    drawX = 0;
    drawY = 0;
    limitX = 0;
    limitY = 0;

    enemyVec = Direction::left;

    targetPos_x = 0;
    targetPos_y = 0;

    speedLevel = 1;

    count = 0;
    attack = 0;

    ijike = 0;

    speedCount = 0;

    reversOrder = false;

    tile = WorldVal::Get<Grid*>("map");
    enemyImage = *WorldVal::Get<int[20]>("enemyImage");
    enemyImage_eye = *WorldVal::Get<int[4]>("enemyImageEye");

}

void EnemyAra::SetUp(Type setType, Direction setDirection, int setX, int setY) { //�p����R���X�g���N�^���ŕK���Ăяo���K�v����AsetType�ɓG��ށAsetDirection�ɍŏ��Ɍ����Ă�����AsetX,Y�Ɍ��݈ʒu�����W�ő��
    type = setType;
    drawX = setX;
    drawY = setY;
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    SetStandbyModeTarget(); //�ҋ@��Ԃ̖ڕW�}�X�ɐݒ�
}

void EnemyAra::Update() {
    if (isUpdate) {
        count++; //���Ԍo��
        ModeChange();
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //�G�ƓG�̖ڂ�\��
    if (isDraw) {
        int x = SHIFT_X + (drawX - renderCenter) * X_RATE;
        int y = SHIFT_Y + (drawY - renderCenter) * Y_RATE;
        int sub = (int)type * 2 + ((count / 4) % 2); //�g�p�摜�i���o�[
        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[sub], TRUE, FALSE);
        if (ijike == 0) { DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)enemyVec], TRUE, FALSE); } //�C�W�P����Ȃ��Ȃ�

        //�f�o�b�O�\��
        DrawHitBox(ClculatTileX(), ClculatTileY(), GetColor(255, 255, 255));
        DrawHitBox(targetPos_x, targetPos_y, GetColor(255, 255, 255));
        DrawTargetLine(ClculatTileX(), ClculatTileY(), targetPos_x, targetPos_y, GetColor(255, 255, 255));
    }
}

void EnemyAra::Move(int move) {
    bool useY = (int)enemyVec % 2 == 0; //���ݐi�s�������㉺���ꂩ�ɂȂ�ꍇtrue
    int* edit = useY ? &drawY : &drawX;
    int limit = useY ? limitY : limitX;
    int raw = useY ? ClculatTileY() * TILE + ClculatLocalY() : ClculatTileX() * TILE + ClculatLocalX();
    
    bool run = (int)((int)enemyVec / 2) == 0 ? raw <= limit : raw >= limit;

    while (run) { //�}�X�ړ����������ꍇ(while���g���Ă���͉̂��Lif����break��p��������������Ń��[�v�̈Ӑ}�͂Ȃ�)

        if (enemyVec == Direction::left && ClculatTileX() - 1 < 0) { drawX = (AREA_X + WARP_AREA_X) * TILE - (center + 1); }
        if (enemyVec == Direction::right && ClculatTileX() + 1 >= AREA_X + WARP_AREA_X * 2) { drawX = -WARP_AREA_X * TILE + (center + 1); }

        int currentTileX = ClculatTileX();
        int currentTileY = ClculatTileY();

        if (attack) { SetAttackModeTarget(); } //�^�[�Q�b�g�}�X�̐ݒ�(�ǂ��������[�h�̎�)
        else { SetStandbyModeTarget(); } //�^�[�Q�b�g�}�X(�꒣�胂�[�h)
        if (reversOrder) { SetReversMove(); break; } //���]�����ړ��͈ړ�������肷��̂ňȍ~�̈ړ��挈�菈����ʂ�K�v���Ȃ�����break
        if (ijike) { SetCringeMove(); break; } //�C�W�P��Ԃ̏ꍇ���ړ��挈��Ȃ̂ŏI�������break

        int max = pow(35, 2)*2;

        int distance[4] = { max ,max ,max ,max }; //�e��ړ��\�����ɐi�񂾃}�X����ڕW�}�X�ւ̋����ۑ��p
        int minDistance = max; //�ŒZ�����L�^�p
        int newDirection= ((int)enemyVec + 2) % 4; //�V�����ړ������A��芸�������Ε����ɐݒ肷�鎖�łǂ̃}�X���ړ��s�\�������ꍇ�����I�ɔ��Ε������ݒ肳���Ƃ����Z�i

        for (int i = 0; i < 4; i++) {
            if (((int)enemyVec + 2) % 4 == i) { continue; } //�����i�����Ε����������ꍇ��΂�
            if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::block) { continue; } //�ړ��s�Ȃ��΂�

            int x = currentTileX + ClculatSubX((Direction)i); //�����ł���pos�͌��݂̃}�X���W���w��
            int y = currentTileY + ClculatSubY((Direction)i);
            distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance[i]) { //�ڕW�}�X�Ƃ̍ŒZ�����𒲂ׂ�enemyVec�ɍŒZ�����̂��̂��i�[
                minDistance = distance[i];
                newDirection = i;
            }
        }
        if ((int)enemyVec % 2 != newDirection % 2) { *edit = limit - (useY ? WARP_AREA_Y : WARP_AREA_X) * TILE - center; } //�Ȃ���ꍇ���܂ł̎������~�b�g�𒴂��Ă����ꍇ���~�b�g���ɔ[�߂鏈��

        enemyVec = (Direction)newDirection; //�V���������ɐݒ�

        limitX = ClculatLimitX(enemyVec);
        limitY = ClculatLimitY(enemyVec);
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //���݂̈ړ������ɍ��킹�Ċe���Ɉړ��ʂ����Z�A���Z���Ă����
    drawY += move * ClculatSubY(enemyVec);

    //�ȉ��f�o�b�O�\�L
    SetFontSize(30);
    //DrawFormatString(700, 30, GetColor(255, 255, 255), "Time�F%.2lf", (double)count / 60);
    ////DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    //DrawFormatString(700, 100, GetColor(255, 255, 255), "�Z�G�l�~�[���");
    //DrawFormatString(700, 150, GetColor(255, 0, 0), "X�ʒu�F%d", ClculatTileX());
    //DrawFormatString(700, 200, GetColor(0, 0, 255), "Y�ʒu�F%d", ClculatTileY());
    //DrawFormatString(700, 250, GetColor(0, 255, 0), "�ړ������F%d", enemyVec);
}
//�X�s�[�h���x���ɂ���ăX�s�[�h��ς���
int EnemyAra::ChangeSpeed() {
    int move = 0; //����̍��W�ړ���
    int speed = 15; //����̓��쑬
    switch (speedLevel)
    {
    case 1:
        if (ijike == 1) { speed = 10; }
        break;
    case 2:
        speed = 17;
        break;
    case 3:
        speed = 19;
        break;
    case 4:
        speed = 19;
        break;
    }
    speedCount += speed; //����̑��x���J�E���g�ɉ��Z
    move = speedCount / MOVABLE_SPEED; //������W�ʂ̌v�Z
    speedCount -= move * MOVABLE_SPEED; //����Ɏg�������̃J�E���g����菜��

    return move; //����̓���ʂ�Ԃ�
}

//�U����ԁA�x�e��Ԃ̐؂�ւ�
void EnemyAra::ModeChange() {
    switch (speedLevel) {
    case 1:
        if (count == 0 || count == 27 * FPS || count == 54 * FPS || count == 79 * FPS) {
            attack = 0;//�x�e���
            reversOrder = true;
        }
        if (count == 7 * FPS || count == 34 * FPS || count == 59 * FPS || count == 84 * FPS) {
            attack = 1;///�U�����
            reversOrder = true;
        }
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }

    //�ȉ��f�o�b�O�\�L
    const char* debugMessage[2] = { "�x����" ,"�U����" };
    unsigned int color[2] = { GetColor(0, 255, 255) ,GetColor(255, 255, 0) };
    DrawFormatString(700, 300, color[attack], debugMessage[attack]);
}

void EnemyAra::SetCringeMove() {
    int currentTileX = ClculatTileX();
    int currentTileY = ClculatTileY();
    int revers = ((int)enemyVec + 2) % 4; //�i�s�����̔��Ε���
    std::deque<int> subList = std::deque<int>(); //�ړ��\�ȕ�����ۗL���铮�I�z��
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //�����i�����Ε����������ꍇ��΂�
        if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::movable) { subList.push_back(i); } //�ړ��\�Ȃ玝���Ă���
    }
    if (subList.size() <= 0) { enemyVec = (Direction)revers; } //�ǂ̕����ɂ������Ȃ��ꍇ�A�ړ������𔽑΂ɐݒ�
    else { enemyVec = (Direction)GetRand(subList[subList.size() - 1]); } //�ړ��\�ȕ������烉���_���ɕ��������o���A�ݒ肷��
}

void EnemyAra::SetReversMove() { 
    enemyVec = (Direction)(((int)enemyVec + 2) % 4); //��������𔽑΂ɐݒ肷��
    reversOrder = false; //���]���߂����s�����̂�false�ɂ���
}

int EnemyAra::ClculatSubX(Direction angle) const { return std::sin((360 - 90 * (int)angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(Direction angle) const { return std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int EnemyAra::ClculatLocalX() const { return (drawX + center) % TILE; } //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
int EnemyAra::ClculatLocalY() const { return (drawY + center) % TILE; }
int EnemyAra::ClculatTileX() const { return (drawX + center) / TILE + WARP_AREA_X; } //���݃}�X��Ԃ��Ă����
int EnemyAra::ClculatTileY() const { return (drawY + center) / TILE + WARP_AREA_Y; }
int EnemyAra::ClculatLimitX(Direction angle)const { return(ClculatTileX() + ClculatSubX(angle))* TILE + center; } //���̈ʒu�ɒ������猻�݃}�X����ړ��\�������擾�������]������ʒu��Ԃ��Ă����
int EnemyAra::ClculatLimitY(Direction angle)const { return (ClculatTileY() + ClculatSubY(angle)) * TILE + center; } //��L��y��