#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include <math.h>
#include <deque>

//������
EnemyAra::EnemyAra() {
    isUpdate = true;
    isDraw = true;

    type = Type::red; //��芸�����A�J�x�C����
    posX = 13;//17
    posY = 11;//11

    center = 3;
    renderCenter = 3;

    drawX = posX * TILE + (TILE - 1);
    drawY = posY * TILE ;

    targetPos_x = 30;
    targetPos_y = 0;

    enemyVec = Direction::left;

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

void EnemyAra::Update() {
    if (isUpdate) {
        ModeChange();
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //�G�ƓG�̖ڂ�\��
    if (isDraw) {
        int sub = (int)type * 2 + ((count / 4) % 2); //�g�p�摜�i���o�[
        DrawRotaGraph3(SHIFT_X + (drawX - renderCenter) * X_RATE, SHIFT_Y + (drawY - renderCenter) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, enemyImage[sub], TRUE, FALSE);
        if (ijike == 0) { //�C�W�P����Ȃ��Ȃ�
            DrawRotaGraph3(SHIFT_X + (drawX - renderCenter) * X_RATE, SHIFT_Y + (drawY - renderCenter) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)enemyVec], TRUE, FALSE);
        }
    }
}

void EnemyAra::Move(int move) {
    int rawX = ClculatTileX(enemyVec) * TILE + ClculatLocalX(enemyVec);
    int rawY = ClculatTileY(enemyVec) * TILE + ClculatLocalY(enemyVec);
    int limitX = (ClculatTileX(enemyVec) + ClculatSubX(enemyVec)) * TILE + 3;
    int limitY = (ClculatTileY(enemyVec) + ClculatSubY(enemyVec)) * TILE + 4;

    bool run = false;
    switch (enemyVec) {
    case Direction::up: run = rawY - limitY <= 0; break;
    case Direction::left: run = rawX - limitX <= 0; break;
    case Direction::down: run = rawY - limitY >= 0; break;
    case Direction::right: run = rawX - limitX >= 0; break;
    }

    int currentTileX = (drawX + center) / TILE;
    int currentTileY = (drawY + center) / TILE;
    while (currentTileX!=posX || currentTileY != posY) { //�}�X�ړ����������ꍇ(while���g���Ă���͉̂��Lif����break��p��������������Ń��[�v�̈Ӑ}�͂Ȃ�)
        posX = currentTileX; //���ݏ����}�X��V�������ɕύX
        posY = currentTileY;
        currentTileX += WARP_AREA_X; //�������̕ϐ��͔z�񂩂�̎擾�p�ɕύX
        currentTileY += WARP_AREA_Y;

        if (attack) { SetAttackModeTarget(); } //�^�[�Q�b�g�}�X�̐ݒ�(�ǂ��������[�h�̎�)
        else { SetStandbyModeTarget(); } //�^�[�Q�b�g�}�X(�꒣�胂�[�h)
        if (reversOrder) { SetReversMove(); break; } //���]�����ړ��͈ړ�������肷��̂ňȍ~�̈ړ��挈�菈����ʂ�K�v���Ȃ�����break
        if (ijike) { SetCringeMove(); break; } //�C�W�P��Ԃ̏ꍇ���ړ��挈��Ȃ̂ŏI�������break

        int distance[4] = { 9999 ,9999 ,9999 ,9999 }; //�e��ړ��\�����ɐi�񂾃}�X����ڕW�}�X�ւ̋����ۑ��p
        int minDistance = 9999; //�ŒZ�����L�^�p
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
        enemyVec = (Direction)newDirection; //�V���������ɐݒ�
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //���݂̈ړ������ɍ��킹�Ċe���Ɉړ��ʂ����Z�A���Z���Ă����
    drawY += move * ClculatSubY(enemyVec);

    //�ȉ��f�o�b�O�\�L
    SetFontSize(30);
    DrawFormatString(700, 30, GetColor(255, 255, 255), "Time�F%.2lf", (double)count / 60);
    //DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    DrawFormatString(700, 100, GetColor(255, 255, 255), "�Z�G�l�~�[���");
    DrawFormatString(700, 150, GetColor(255, 0, 0), "X�ʒu�F%d", posX);
    DrawFormatString(700, 200, GetColor(0, 0, 255), "Y�ʒu�F%d", posY);
    DrawFormatString(700, 250, GetColor(0, 255, 0), "�ړ������F%d", enemyVec);
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
    count++;//���Ԍo��

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
    int currentTileX = posX + WARP_AREA_X;
    int currentTileY = posY + WARP_AREA_Y;
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
int EnemyAra::ClculatLocalX(Direction angle) const { return (posX + center + ClculatSubX(angle)) % TILE; } //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
int EnemyAra::ClculatLocalY(Direction angle) const { return (posY + center + ClculatSubY(angle)) % TILE; }
int EnemyAra::ClculatTileX(Direction angle) const { return (posX + center + ClculatSubX(angle)) / TILE + WARP_AREA_X; } //���݃}�X��Ԃ��Ă����
int EnemyAra::ClculatTileY(Direction angle) const { return (posY + center + ClculatSubY(angle)) / TILE + WARP_AREA_Y; }