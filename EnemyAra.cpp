#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "DebugUtility.h"
#include "PowerModeProcess.h"
#include <math.h>
#include <deque>
#include "MapLoading.h"

int EnemyAra::nowStage = 0;
int EnemyAra::timer = 0;
EnemyAra::MoveMode EnemyAra::moveMode = EnemyAra::MoveMode::standby; //���̒�`

//������
EnemyAra::EnemyAra() {
    nowStage = *WorldVal::Get<int>("nowStage"); //���݃X�e�[�W���̎擾
    timer = 0;
    moveMode = MoveMode::standby; //�ŏ��͑ҋ@���
    state = State::neutral; //�ŏ��̌����ڂ͒ʏ���
    imageState = state;

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
    oldVec = enemyVec;

    targetPos_x = 0;
    targetPos_y = 0;

    count = 0;
    warp = 0;   /*���[�v���̃G�l�~�[�̈ړ����x*/

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
    enemyVec = setDirection;
    oldVec = enemyVec;
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    SetStandbyModeTarget(); //�ҋ@��Ԃ̖ڕW�}�X�ɐݒ�
}

void EnemyAra::Update() {
    if (isUpdate) {
        count++; //���Ԍo��
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //�G�ƓG�̖ڂ�\��
    if (isDraw) {
        int x = GetDrawX();
        int y = GetDrawY();
        int sub = (int)type * 2 + ((count / 6) % 2); //�g�p�摜�i���o�[
        int sub2 = (int)type * 2 + ((count / 12) % 2);

        if (state == State::cringe || (state >= State::wait && imageState == State::cringe)) { //��Ԃ��C�W�P�A�Ⴕ���͑ҋ@�A�����甲�����Ԃł��摜��cringe���w���Ă���ꍇ�C�W�P�p�摜�`��
            int ijkeCount = PowerModeProcess::GetTimeLeft();
            if (ijkeCount >= 2 * FPS) {
                if (sub % 2 == 0) {
                    DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[16], TRUE, FALSE);
                }
                else {
                    DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[17], TRUE, FALSE);
                }
            }
            else {
                if ((count / 6) % 2 == 0) {
                    if (sub2 % 2 == 0) {
                        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[16], TRUE, FALSE);
                    }
                    else {
                        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[18], TRUE, FALSE);
                    }
                }
                else {
                    if (sub2 % 2 == 0) {
                        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[17], TRUE, FALSE);
                    }
                    else {
                        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[19], TRUE, FALSE);
                    }
                }
            }
            return;
        }
        if (state != State::damage && (!PowerModeProcess::GetIsPause())) {
            DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[sub], TRUE, FALSE);
        }
        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)oldVec], TRUE, FALSE); //oldVec�͊�{enemyVev��ǐՂ��Ă邪�X�R�A�\�����͒ǐՂ��~�߂��邩��\���̎w��ɒ��x����

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
        warp = 0;
        if (enemyVec == Direction::left && ClculatTileX() - 1 < 0) { drawX = (AREA_X + WARP_AREA_X) * TILE - (center + 1); }
        if (enemyVec == Direction::right && ClculatTileX() + 1 >= AREA_X + WARP_AREA_X * 2) { drawX = -WARP_AREA_X * TILE + (center + 1);}
        
        int tileX = ClculatTileX();
        int tileY = ClculatTileY();

        if (tileX - 1 < 9 && tileX - 1 > 2 && tileY == 14 || tileX + 1 > 26 && tileX + 1 < 33 && tileY == 14) { warp = 1; }   /*���[�v�̒ʘH�ɓ���Έړ����x��8�ɂȂ�*/
        if ((tileX >= 14 && tileX <= 21) && (tileY >= 12 && tileY <= 16)) { warp = 1; } //���̒��ɂ��鎞�����[�v���ɂ���

        if (reversOrder) { SetReversMove(); break; } //���]�����ړ��͈ړ�������肷��̂ňȍ~�̈ړ��挈�菈����ʂ�K�v���Ȃ�����break
        if (state == State::cringe) { SetCringeMove(); break; } //�C�W�P��Ԃ̏ꍇ���ړ��挈��Ȃ̂ŏI�������break
        if (state == State::damage) { //�����Ԃ̏ꍇ�^�[�Q�b�g�𑃂̎w��ʒu�֎w�肷�鏈��
            SetWaitModeTarget();
            if (tileX == targetPos_x && tileY == targetPos_y) { 
                state = State::neutral; } //�w��ʒu�ɒ������ꍇ�A���݂͒���neutral���w�肵�Ă��邪�Await����neutral�ֈڍs����v���O�������o�����wait�ɕύX�\��
        }
        if (state == State::neutral || state == State::ready) { //�ʏ��Ԃ̏ꍇ���샂�[�h�ɍ��킹���^�[�Q�b�g�w��
            if (moveMode == MoveMode::attack) { SetAttackModeTarget(); } //�^�[�Q�b�g�}�X�̐ݒ�(�ǂ��������[�h�̎�)
            else { SetStandbyModeTarget(); } //�^�[�Q�b�g�}�X(�꒣�胂�[�h)
        }

        int minDistance = -1; //�ŒZ�����L�^�p�A�G���͒������������\��������̂ŏ����l��-1�Ƃ���
        int newDirection= ((int)enemyVec + 2) % 4; //�V�����ړ������A��芸�������Ε����ɐݒ肷�鎖�łǂ̃}�X���ړ��s�\�������ꍇ�����I�ɔ��Ε������ݒ肳���Ƃ����Z�i
        const ::Move* grid = ReadTile(tileX, tileY); //���ݏ�������}�X�̈ړ��\�����z��A���݃X�e�[�g�ɉ�������

        for (int i = 0; i < 4; i++) {
            if (((int)enemyVec + 2) % 4 == i) { continue; } //�����i�����Ε����������ꍇ��΂�
            if (grid[i] == Move::block) { continue; } //�ړ��s�Ȃ��΂�

            int x = tileX + ClculatSubX((Direction)i); //�����ł���pos�͌��݂̃}�X���W���w��
            int y = tileY + ClculatSubY((Direction)i);
            int distance = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance || minDistance < 0) { //�ڕW�}�X�Ƃ̍ŒZ�����𒲂ׂ�enemyVec�ɍŒZ�����̂��̂��i�[
                minDistance = distance;
                newDirection = i;
            }
        }
        if ((int)enemyVec % 2 != newDirection % 2) { *edit = limit - (useY ? WARP_AREA_Y : WARP_AREA_X) * TILE - center; } //�Ȃ���ꍇ���܂ł̎������~�b�g�𒴂��Ă����ꍇ���~�b�g���ɔ[�߂鏈��

        enemyVec = (Direction)newDirection; //�V���������ɐݒ�
        if (!PowerModeProcess::GetIsPause()) { oldVec = enemyVec; } //�X�R�A�\�����������ꍇ�������̍X�V�����Ȃ�

        limitX = ClculatLimitX(enemyVec);
        limitY = ClculatLimitY(enemyVec);
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //���݂̈ړ������ɍ��킹�Ċe���Ɉړ��ʂ����Z�A���Z���Ă����
    drawY += move * ClculatSubY(enemyVec);

    //�ȉ��f�o�b�O�\�L
    SetFontSize(30);
}

int EnemyAra::ChangeSpeed() { //�X�s�[�h���x���ɂ���ăX�s�[�h��ς���
    int cringe = 10; //�C�W�P��ԑ�
    int damage = 28; //�C�W�P��ԂŐH�ׂ��đ��ɖ߂��ԑ��A���̒l
    int tunnel = 8; //���[�v�g���l����
    int speed = Spurt(); //����̓��쑬�A�Ƃ肠�����ʏ푬

    int move = 0; //����̍��W�ړ���
    switch (ClculatSpeedLevel()) { //���x���ɍ��킹�����x���
    case 0:
        if (speed < 0) { speed = 15; } //�X�p�[�g�s�g�p�̏ꍇ�{���̒ʏ푬������
        break;
    case 1:
        if (speed < 0) { speed = 17; }
        cringe = 11;
        tunnel = 9;
        break;
    case 2:
        if (speed < 0) { speed = 19; }
        cringe = 12;
        tunnel = 10;
        break;
    case 3:
        if (speed < 0) { speed = 19; }
        cringe = 9;
        tunnel = 10;
        break;
    }

    while (true) { //break�g���������烋�[�v�Abreak��p���鎖�ŏ����ɗD��x��݂��邱�Ƃ��ł���
        if (state == State::damage) { speed = damage; break; } //�����ԂȂ炻�̑��x�ɂ���
        if (state == State::cringe) { speed = cringe; break; } //�C�W�P��ԂȂ炻�̑��x�ɂ���
        if (warp && state == State::neutral) { speed = tunnel; } //���[�v�g���l���G���A���Ȃ�w�葬�ɁA�ʏ��ԈȊO�Ȃ�G���A���ł��ʏ푬�A�ŏI�I�ɂ�ready�ɕύX���ׂ�
        break; //���ɏ����ɓ��Ă͂܂�Ȃ��ꍇ�ʏ푬

    }

    speedCount += speed; //����̑��x���J�E���g�ɉ��Z
    move = speedCount / MOVABLE_SPEED; //������W�ʂ̌v�Z
    speedCount -= move * MOVABLE_SPEED; //����Ɏg�������̃J�E���g����菜��

    return move; //����̓���ʂ�Ԃ�
}

void EnemyAra::ModeChange(std::deque<EnemyAra*>* enemyList) { //�U����ԁA�x�e��Ԃ̐؂�ւ�
    for (int i = 0; i < enemyList->size(); ++i) { //�G�̃X�e�[�g�`�F�b�N
        State state = (*enemyList)[i]->state;

        if (state == State::cringe || state == State::damage || (!(*enemyList)[i]->isUpdate) || (!(*enemyList)[i]->isDraw)) { return; } //cringe�Adamage�̓G������ꍇ���[�h�`�F���W�J�E���g��i�߂Ȃ��AUpdate��Draw�����s���Ȃ��~�܂����G������ꍇ���i�߂Ȃ�
    }

    bool standby = timer == 25 * FPS || timer == 50 * FPS; //�x�e�ؑ֏����A��芸�����X�s�[�h���x��2�A3�̕������Ă���
    bool attack = timer == 5 * FPS || timer == 30 * FPS || timer == 55 * FPS; //�U���ؑ֏����A��L�Ɠ��l�Ƀ��x��2�A3�̒l

    switch (ClculatSpeedLevel()) {
    case 0:
        standby = timer == 27 * FPS || timer == 54 * FPS || timer == 79 * FPS;
        attack = timer == 7 * FPS || timer == 34 * FPS || timer == 59 * FPS || timer == 84 * FPS;
        break;
    case 1:
        standby = timer == 27 * FPS || timer == 54 * FPS ;
        attack = timer == 7 * FPS || timer == 34 * FPS || timer == 59 * FPS;
        break;
    }

    if (standby) { moveMode = MoveMode::standby; } //�x�e���
    if (attack) { moveMode = MoveMode::attack; } //�U�����

    if (standby || attack) { for (int i = 0; i < enemyList->size(); ++i) { (*enemyList)[i]->reversOrder = true; } } //���[�h�`�F���W�����ꍇ�S�G�ɔ��]����

    ++timer; //�^�C�}�[�J�E���g

    //�ȉ��f�o�b�O�\�L
    const char* debugMessage[2] = { "�x����" ,"�U����" };
    unsigned int color[2] = { GetColor(0, 255, 255) ,GetColor(255, 255, 0) };
    int sub = (int)moveMode;
    SetFontSize(35);
    DrawFormatString(0, 50, color[sub], debugMessage[sub]);
}

void EnemyAra::SetCringeMove() {
    int currentTileX = ClculatTileX();
    int currentTileY = ClculatTileY();
    const ::Move* grid = ReadTile(currentTileX, currentTileY); //���ݏ�������}�X�̈ړ��\�����z��A���݃X�e�[�g�ɉ�������
    int revers = ((int)enemyVec + 2) % 4; //�i�s�����̔��Ε���
    std::deque<int> subList = std::deque<int>(); //�ړ��\�ȕ�����ۗL���铮�I�z��
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //�����i�����Ε����������ꍇ��΂�
        if (grid[i] == Move::movable) { subList.push_back(i); } //�ړ��\�Ȃ玝���Ă���
    }
    if (subList.size() <= 0) { enemyVec = (Direction)revers; } //�ǂ̕����ɂ������Ȃ��ꍇ�A�ړ������𔽑΂ɐݒ�
    else { enemyVec = (Direction)subList[GetRand(subList.size() - 1)]; } //�ړ��\�ȕ������烉���_���ɕ��������o���A�ݒ肷��
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
}

void EnemyAra::SetReversMove() { 
    enemyVec = (Direction)(((int)enemyVec + 2) % 4); //��������𔽑΂ɐݒ肷��
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    reversOrder = false; //���]���߂����s�����̂�false�ɂ���
}

int EnemyAra::GetDrawX() const { return SHIFT_X + (drawX - renderCenter) * X_RATE; }
int EnemyAra::GetDrawY() const { return SHIFT_Y + (drawY - renderCenter) * Y_RATE; }

int EnemyAra::ClculatSubX(Direction angle) const { return std::sin((360 - 90 * (int)angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(Direction angle) const { return std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int EnemyAra::ClculatLocalX() const { return (drawX + center) % TILE; } //���݃}�X�̍����(0,0)�Ƃ��ă}�X���łǂ̈ʒu�ɂ��邩��Ԃ��Ă����
int EnemyAra::ClculatLocalY() const { return (drawY + center) % TILE; }
int EnemyAra::ClculatTileX() const { return (drawX + center) / TILE + WARP_AREA_X; } //���݃}�X��Ԃ��Ă����
int EnemyAra::ClculatTileY() const { return (drawY + center) / TILE + WARP_AREA_Y; }
int EnemyAra::ClculatLimitX(Direction angle)const { return(ClculatTileX() + ClculatSubX(angle))* TILE + center; } //���̈ʒu�ɒ������猻�݃}�X����ړ��\�������擾�������]������ʒu��Ԃ��Ă����
int EnemyAra::ClculatLimitY(Direction angle)const { return (ClculatTileY() + ClculatSubY(angle)) * TILE + center; } //��L��y��

const ::Move* EnemyAra::ReadTile(int x, int y) {
    switch (state) {
    case EnemyAra::State::cringe: return tile[x][y].ReadCringe();
    case EnemyAra::State::damage: return tile[x][y].ReadDamage();
    case EnemyAra::State::wait: return tile[x][y].ReadWait();
    default: return tile[x][y].ReadEnemy(); //�ʏ�A�����甲�����Ԃ̏ꍇ�ǂ�����ʏ��Ԃ̔z���Ԃ�
    }
}
