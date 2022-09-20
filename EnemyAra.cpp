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
EnemyAra::MoveMode EnemyAra::moveMode = EnemyAra::MoveMode::standby; //実体定義

//初期化
EnemyAra::EnemyAra() {
    nowStage = *WorldVal::Get<int>("nowStage"); //現在ステージ数の取得
    timer = 0;
    moveMode = MoveMode::standby; //最初は待機状態
    state = State::neutral; //最初の見た目は通常状態
    imageState = state;

    isUpdate = true;
    isDraw = true;

    type = Type::red; //取り敢えずアカベイを代入
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
    warp = 0;   /*ワープ時のエネミーの移動速度*/

    speedCount = 0;

    reversOrder = false;

    tile = WorldVal::Get<Grid*>("map");
    enemyImage = *WorldVal::Get<int[20]>("enemyImage");
    enemyImage_eye = *WorldVal::Get<int[4]>("enemyImageEye");

}

void EnemyAra::SetUp(Type setType, Direction setDirection, int setX, int setY) { //継承先コンストラクタ内で必ず呼び出す必要あり、setTypeに敵種類、setDirectionに最初に向いてる方向、setX,Yに現在位置を座標で代入
    type = setType;
    drawX = setX;
    drawY = setY;
    enemyVec = setDirection;
    oldVec = enemyVec;
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    SetStandbyModeTarget(); //待機状態の目標マスに設定
}

void EnemyAra::Update() {
    if (isUpdate) {
        count++; //時間経過
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //敵と敵の目を表示
    if (isDraw) {
        int x = GetDrawX();
        int y = GetDrawY();
        int sub = (int)type * 2 + ((count / 6) % 2); //使用画像ナンバー
        int sub2 = (int)type * 2 + ((count / 12) % 2);

        if (state == State::cringe || (state >= State::wait && imageState == State::cringe)) { //状態がイジケ、若しくは待機、巣から抜ける状態でも画像がcringeを指している場合イジケ用画像描写
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
        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)oldVec], TRUE, FALSE); //oldVecは基本enemyVevを追跡してるがスコア表示中は追跡を止められるから表示の指定に丁度いい

        //デバッグ表示
        DrawHitBox(ClculatTileX(), ClculatTileY(), GetColor(255, 255, 255));
        DrawHitBox(targetPos_x, targetPos_y, GetColor(255, 255, 255));
        DrawTargetLine(ClculatTileX(), ClculatTileY(), targetPos_x, targetPos_y, GetColor(255, 255, 255));
    }
}

void EnemyAra::Move(int move) {

    bool useY = (int)enemyVec % 2 == 0; //現在進行方向が上下何れかになる場合true
    int* edit = useY ? &drawY : &drawX;
    int limit = useY ? limitY : limitX;
    int raw = useY ? ClculatTileY() * TILE + ClculatLocalY() : ClculatTileX() * TILE + ClculatLocalX();
    
    bool run = (int)((int)enemyVec / 2) == 0 ? raw <= limit : raw >= limit;

    while (run) { //マス移動があった場合(whileを使っているのは下記if文でbreakを用いたかったからでループの意図はない)
        warp = 0;
        if (enemyVec == Direction::left && ClculatTileX() - 1 < 0) { drawX = (AREA_X + WARP_AREA_X) * TILE - (center + 1); }
        if (enemyVec == Direction::right && ClculatTileX() + 1 >= AREA_X + WARP_AREA_X * 2) { drawX = -WARP_AREA_X * TILE + (center + 1);}
        
        int tileX = ClculatTileX();
        int tileY = ClculatTileY();

        if (tileX - 1 < 9 && tileX - 1 > 2 && tileY == 14 || tileX + 1 > 26 && tileX + 1 < 33 && tileY == 14) { warp = 1; }   /*ワープの通路に入れば移動速度が8になる*/
        if ((tileX >= 14 && tileX <= 21) && (tileY >= 12 && tileY <= 16)) { warp = 1; } //巣の中にいる時もワープ速にする

        if (reversOrder) { SetReversMove(); break; } //反転方向移動は移動先を決定するので以降の移動先決定処理を通る必要がないからbreak
        if (state == State::cringe) { SetCringeMove(); break; } //イジケ状態の場合も移動先決定なので終わったらbreak
        if (state == State::damage) { //やられ状態の場合ターゲットを巣の指定位置へ指定する処理
            SetWaitModeTarget();
            if (tileX == targetPos_x && tileY == targetPos_y) { 
                state = State::neutral; } //指定位置に着いた場合、現在は直接neutralを指定しているが、waitからneutralへ移行するプログラムが出来ればwaitに変更予定
        }
        if (state == State::neutral || state == State::ready) { //通常状態の場合動作モードに合わせたターゲット指定
            if (moveMode == MoveMode::attack) { SetAttackModeTarget(); } //ターゲットマスの設定(追いかけモードの時)
            else { SetStandbyModeTarget(); } //ターゲットマス(縄張りモード)
        }

        int minDistance = -1; //最短距離記録用、青敵等は長距離を示す可能性があるので初期値は-1とする
        int newDirection= ((int)enemyVec + 2) % 4; //新しい移動方向、取り敢えず反対方向に設定する事でどのマスも移動不能だった場合自動的に反対方向が設定されるという算段
        const ::Move* grid = ReadTile(tileX, tileY); //現在所属するマスの移動可能方向配列、現在ステートに応じた物

        for (int i = 0; i < 4; i++) {
            if (((int)enemyVec + 2) % 4 == i) { continue; } //今回のiが反対方向だった場合飛ばす
            if (grid[i] == Move::block) { continue; } //移動不可なら飛ばす

            int x = tileX + ClculatSubX((Direction)i); //ここであるposは現在のマス座標を指す
            int y = tileY + ClculatSubY((Direction)i);
            int distance = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance || minDistance < 0) { //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
                minDistance = distance;
                newDirection = i;
            }
        }
        if ((int)enemyVec % 2 != newDirection % 2) { *edit = limit - (useY ? WARP_AREA_Y : WARP_AREA_X) * TILE - center; } //曲がる場合今までの軸がリミットを超えていた場合リミット内に納める処理

        enemyVec = (Direction)newDirection; //新しい方向に設定
        if (!PowerModeProcess::GetIsPause()) { oldVec = enemyVec; } //スコア表示中だった場合旧方向の更新をしない

        limitX = ClculatLimitX(enemyVec);
        limitY = ClculatLimitY(enemyVec);
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //現在の移動方向に合わせて各軸に移動量を加算、減算してくれる
    drawY += move * ClculatSubY(enemyVec);

    //以下デバッグ表記
    SetFontSize(30);
}

int EnemyAra::ChangeSpeed() { //スピードレベルによってスピードを変える
    int cringe = 10; //イジケ状態速
    int damage = 28; //イジケ状態で食べられて巣に戻る状態速、仮の値
    int tunnel = 8; //ワープトンネル速
    int speed = Spurt(); //今回の動作速、とりあえず通常速

    int move = 0; //今回の座標移動量
    switch (ClculatSpeedLevel()) { //レベルに合わせた速度代入
    case 0:
        if (speed < 0) { speed = 15; } //スパート不使用の場合本来の通常速を入れる
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

    while (true) { //break使いたいからループ、breakを用いる事で処理に優先度を設けることができる
        if (state == State::damage) { speed = damage; break; } //やられ状態ならその速度にする
        if (state == State::cringe) { speed = cringe; break; } //イジケ状態ならその速度にする
        if (warp && state == State::neutral) { speed = tunnel; } //ワープトンネルエリア内なら指定速に、通常状態以外ならエリア内でも通常速、最終的にはreadyに変更すべき
        break; //特に条件に当てはまらない場合通常速

    }

    speedCount += speed; //今回の速度をカウントに加算
    move = speedCount / MOVABLE_SPEED; //動作座標量の計算
    speedCount -= move * MOVABLE_SPEED; //動作に使った分のカウントを取り除く

    return move; //今回の動作量を返す
}

void EnemyAra::ModeChange(std::deque<EnemyAra*>* enemyList) { //攻撃状態、休憩状態の切り替え
    for (int i = 0; i < enemyList->size(); ++i) { //敵のステートチェック
        State state = (*enemyList)[i]->state;

        if (state == State::cringe || state == State::damage || (!(*enemyList)[i]->isUpdate) || (!(*enemyList)[i]->isDraw)) { return; } //cringe、damageの敵がいる場合モードチェンジカウントを進めない、UpdateやDrawを実行しない止まった敵がいる場合も進めない
    }

    bool standby = timer == 25 * FPS || timer == 50 * FPS; //休憩切替条件、取り敢えずスピードレベル2、3の物を入れている
    bool attack = timer == 5 * FPS || timer == 30 * FPS || timer == 55 * FPS; //攻撃切替条件、上記と同様にレベル2、3の値

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

    if (standby) { moveMode = MoveMode::standby; } //休憩状態
    if (attack) { moveMode = MoveMode::attack; } //攻撃状態

    if (standby || attack) { for (int i = 0; i < enemyList->size(); ++i) { (*enemyList)[i]->reversOrder = true; } } //モードチェンジした場合全敵に反転命令

    ++timer; //タイマーカウント

    //以下デバッグ表記
    const char* debugMessage[2] = { "休息中" ,"攻撃中" };
    unsigned int color[2] = { GetColor(0, 255, 255) ,GetColor(255, 255, 0) };
    int sub = (int)moveMode;
    SetFontSize(35);
    DrawFormatString(0, 50, color[sub], debugMessage[sub]);
}

void EnemyAra::SetCringeMove() {
    int currentTileX = ClculatTileX();
    int currentTileY = ClculatTileY();
    const ::Move* grid = ReadTile(currentTileX, currentTileY); //現在所属するマスの移動可能方向配列、現在ステートに応じた物
    int revers = ((int)enemyVec + 2) % 4; //進行方向の反対方向
    std::deque<int> subList = std::deque<int>(); //移動可能な方向を保有する動的配列
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //今回のiが反対方向だった場合飛ばす
        if (grid[i] == Move::movable) { subList.push_back(i); } //移動可能なら持っておく
    }
    if (subList.size() <= 0) { enemyVec = (Direction)revers; } //どの方向にも動けない場合、移動方向を反対に設定
    else { enemyVec = (Direction)subList[GetRand(subList.size() - 1)]; } //移動可能な方向からランダムに方向を取り出し、設定する
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
}

void EnemyAra::SetReversMove() { 
    enemyVec = (Direction)(((int)enemyVec + 2) % 4); //動作方向を反対に設定する
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    reversOrder = false; //反転命令を実行したのでfalseにする
}

int EnemyAra::GetDrawX() const { return SHIFT_X + (drawX - renderCenter) * X_RATE; }
int EnemyAra::GetDrawY() const { return SHIFT_Y + (drawY - renderCenter) * Y_RATE; }

int EnemyAra::ClculatSubX(Direction angle) const { return std::sin((360 - 90 * (int)angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(Direction angle) const { return std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int EnemyAra::ClculatLocalX() const { return (drawX + center) % TILE; } //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
int EnemyAra::ClculatLocalY() const { return (drawY + center) % TILE; }
int EnemyAra::ClculatTileX() const { return (drawX + center) / TILE + WARP_AREA_X; } //現在マスを返してくれる
int EnemyAra::ClculatTileY() const { return (drawY + center) / TILE + WARP_AREA_Y; }
int EnemyAra::ClculatLimitX(Direction angle)const { return(ClculatTileX() + ClculatSubX(angle))* TILE + center; } //この位置に着いたら現在マスから移動可能方向を取得し方向転換する位置を返してくれる
int EnemyAra::ClculatLimitY(Direction angle)const { return (ClculatTileY() + ClculatSubY(angle)) * TILE + center; } //上記のy版

const ::Move* EnemyAra::ReadTile(int x, int y) {
    switch (state) {
    case EnemyAra::State::cringe: return tile[x][y].ReadCringe();
    case EnemyAra::State::damage: return tile[x][y].ReadDamage();
    case EnemyAra::State::wait: return tile[x][y].ReadWait();
    default: return tile[x][y].ReadEnemy(); //通常、巣から抜ける状態の場合どちらも通常状態の配列を返す
    }
}
