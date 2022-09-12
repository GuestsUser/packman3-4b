#include "DxLib.h"
#include "EnemyAra.h"
#include "GetKey.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "DebugUtility.h"
#include <math.h>
#include <deque>

//初期化
EnemyAra::EnemyAra() {
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

void EnemyAra::SetUp(Type setType, Direction setDirection, int setX, int setY) { //継承先コンストラクタ内で必ず呼び出す必要あり、setTypeに敵種類、setDirectionに最初に向いてる方向、setX,Yに現在位置を座標で代入
    type = setType;
    drawX = setX;
    drawY = setY;
    limitX = ClculatLimitX(enemyVec);
    limitY = ClculatLimitY(enemyVec);
    SetStandbyModeTarget(); //待機状態の目標マスに設定
}

void EnemyAra::Update() {
    if (isUpdate) {
        count++; //時間経過
        ModeChange();
        Move(ChangeSpeed());
    }
}

void EnemyAra::Draw(){ //敵と敵の目を表示
    if (isDraw) {
        int x = SHIFT_X + (drawX - renderCenter) * X_RATE;
        int y = SHIFT_Y + (drawY - renderCenter) * Y_RATE;
        int sub = (int)type * 2 + ((count / 4) % 2); //使用画像ナンバー
        DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage[sub], TRUE, FALSE);
        if (ijike == 0) { DrawRotaGraph3(x, y, 0, 0, X_RATE, Y_RATE, 0, enemyImage_eye[(int)enemyVec], TRUE, FALSE); } //イジケじゃないなら

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

        if (enemyVec == Direction::left && ClculatTileX() - 1 < 0) { drawX = (AREA_X + WARP_AREA_X) * TILE - (center + 1); }
        if (enemyVec == Direction::right && ClculatTileX() + 1 >= AREA_X + WARP_AREA_X * 2) { drawX = -WARP_AREA_X * TILE + (center + 1); }

        int currentTileX = ClculatTileX();
        int currentTileY = ClculatTileY();

        if (attack) { SetAttackModeTarget(); } //ターゲットマスの設定(追いかけモードの時)
        else { SetStandbyModeTarget(); } //ターゲットマス(縄張りモード)
        if (reversOrder) { SetReversMove(); break; } //反転方向移動は移動先を決定するので以降の移動先決定処理を通る必要がないからbreak
        if (ijike) { SetCringeMove(); break; } //イジケ状態の場合も移動先決定なので終わったらbreak

        int max = pow(35, 2)*2;

        int distance[4] = { max ,max ,max ,max }; //各種移動可能方向に進んだマスから目標マスへの距離保存用
        int minDistance = max; //最短距離記録用
        int newDirection= ((int)enemyVec + 2) % 4; //新しい移動方向、取り敢えず反対方向に設定する事でどのマスも移動不能だった場合自動的に反対方向が設定されるという算段

        for (int i = 0; i < 4; i++) {
            if (((int)enemyVec + 2) % 4 == i) { continue; } //今回のiが反対方向だった場合飛ばす
            if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::block) { continue; } //移動不可なら飛ばす

            int x = currentTileX + ClculatSubX((Direction)i); //ここであるposは現在のマス座標を指す
            int y = currentTileY + ClculatSubY((Direction)i);
            distance[i] = pow(double(targetPos_x) - double(x), 2) + pow(double(targetPos_y) - double(y), 2);

            if (minDistance > distance[i]) { //目標マスとの最短距離を調べてenemyVecに最短方向のものを格納
                minDistance = distance[i];
                newDirection = i;
            }
        }
        if ((int)enemyVec % 2 != newDirection % 2) { *edit = limit - (useY ? WARP_AREA_Y : WARP_AREA_X) * TILE - center; } //曲がる場合今までの軸がリミットを超えていた場合リミット内に納める処理

        enemyVec = (Direction)newDirection; //新しい方向に設定

        limitX = ClculatLimitX(enemyVec);
        limitY = ClculatLimitY(enemyVec);
        break;
    }
    drawX += move * ClculatSubX(enemyVec); //現在の移動方向に合わせて各軸に移動量を加算、減算してくれる
    drawY += move * ClculatSubY(enemyVec);

    //以下デバッグ表記
    SetFontSize(30);
    //DrawFormatString(700, 30, GetColor(255, 255, 255), "Time：%.2lf", (double)count / 60);
    ////DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", okMove);
    //DrawFormatString(700, 100, GetColor(255, 255, 255), "〇エネミー情報");
    //DrawFormatString(700, 150, GetColor(255, 0, 0), "X位置：%d", ClculatTileX());
    //DrawFormatString(700, 200, GetColor(0, 0, 255), "Y位置：%d", ClculatTileY());
    //DrawFormatString(700, 250, GetColor(0, 255, 0), "移動方向：%d", enemyVec);
}
//スピードレベルによってスピードを変える
int EnemyAra::ChangeSpeed() {
    int move = 0; //今回の座標移動量
    int speed = 15; //今回の動作速
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
    speedCount += speed; //今回の速度をカウントに加算
    move = speedCount / MOVABLE_SPEED; //動作座標量の計算
    speedCount -= move * MOVABLE_SPEED; //動作に使った分のカウントを取り除く

    return move; //今回の動作量を返す
}

//攻撃状態、休憩状態の切り替え
void EnemyAra::ModeChange() {
    switch (speedLevel) {
    case 1:
        if (count == 0 || count == 27 * FPS || count == 54 * FPS || count == 79 * FPS) {
            attack = 0;//休憩状態
            reversOrder = true;
        }
        if (count == 7 * FPS || count == 34 * FPS || count == 59 * FPS || count == 84 * FPS) {
            attack = 1;///攻撃状態
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

    //以下デバッグ表記
    const char* debugMessage[2] = { "休息中" ,"攻撃中" };
    unsigned int color[2] = { GetColor(0, 255, 255) ,GetColor(255, 255, 0) };
    DrawFormatString(700, 300, color[attack], debugMessage[attack]);
}

void EnemyAra::SetCringeMove() {
    int currentTileX = ClculatTileX();
    int currentTileY = ClculatTileY();
    int revers = ((int)enemyVec + 2) % 4; //進行方向の反対方向
    std::deque<int> subList = std::deque<int>(); //移動可能な方向を保有する動的配列
    for (int i = 0; i < 4; i++){
        if (revers == i) { continue; } //今回のiが反対方向だった場合飛ばす
        if (tile[currentTileX][currentTileY].ReadEnemy()[i] == Move::movable) { subList.push_back(i); } //移動可能なら持っておく
    }
    if (subList.size() <= 0) { enemyVec = (Direction)revers; } //どの方向にも動けない場合、移動方向を反対に設定
    else { enemyVec = (Direction)GetRand(subList[subList.size() - 1]); } //移動可能な方向からランダムに方向を取り出し、設定する
}

void EnemyAra::SetReversMove() { 
    enemyVec = (Direction)(((int)enemyVec + 2) % 4); //動作方向を反対に設定する
    reversOrder = false; //反転命令を実行したのでfalseにする
}

int EnemyAra::ClculatSubX(Direction angle) const { return std::sin((360 - 90 * (int)angle) * (PI / 180)); }
int EnemyAra::ClculatSubY(Direction angle) const { return std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int EnemyAra::ClculatLocalX() const { return (drawX + center) % TILE; } //現在マスの左上を(0,0)としてマス内でどの位置にいるかを返してくれる
int EnemyAra::ClculatLocalY() const { return (drawY + center) % TILE; }
int EnemyAra::ClculatTileX() const { return (drawX + center) / TILE + WARP_AREA_X; } //現在マスを返してくれる
int EnemyAra::ClculatTileY() const { return (drawY + center) / TILE + WARP_AREA_Y; }
int EnemyAra::ClculatLimitX(Direction angle)const { return(ClculatTileX() + ClculatSubX(angle))* TILE + center; } //この位置に着いたら現在マスから移動可能方向を取得し方向転換する位置を返してくれる
int EnemyAra::ClculatLimitY(Direction angle)const { return (ClculatTileY() + ClculatSubY(angle)) * TILE + center; } //上記のy版