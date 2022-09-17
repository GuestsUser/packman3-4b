#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include "DebugUtility.h"
#include <unordered_map>
#include <string>
#include <math.h>
#include "DxLib.h"

class Movable {
public:
	enum class State { start, run, curve, stop, free };

private:
private:
	Player* player;
	State state;
	Direction direction;
	int* posEdit;
	int center; //マス内座標の中心位置、カーブ等の動作はここを目標に行う
public:
	Movable() :state(State::free), direction(Direction::left), posEdit(nullptr), center(TILE / 2 - 1) {}
	void SetUp(int* set, Player* setP) {
		posEdit = set;
		player = setP;
	}
	virtual void Update(int speed) = 0;
	virtual bool IsCurveInRange(int localPos) = 0; //現在の動作方向で曲がる事が可能な領域にいるかどうかチェックする、trueで曲がれる

	int GetMoveSub() { return -1 + 2 * (int)((int)direction / 2); } //移動方向に対応した符号返し、上、左はマイナス方向への移動、下、右がプラス方向への移動なので/2を利用した
	void Moving(int speed) { *posEdit += speed * GetMoveSub(); }
	bool IsMovable(int localPos)const { //現在進行方向にマス内座標中心を越えた時、進行可能かどうか判定する
		bool minus = localPos >= 0 && localPos <= 3; //判定範囲に入っていた場合true
		bool plus = localPos >= 3 && localPos < 8;
		bool isMovable = player->GetTileMovable(player->ClculatTileX(direction), player->ClculatTileY(direction), direction) == Move::movable; //移動可能だった場合true
		return (int)((int)direction / 2) > 0 ? !(plus && (!isMovable)) : !(minus && (!isMovable));
	}

	int GetCenter() const { return center; }
	State GetState() const { return state; }
	Direction GetDirection() const { return direction; }
	const int* ReadPos() const { return posEdit; }
	const Player* const ReadPlayer() { return player; }


	void SetState(State set) { state = set; }
	void SetDirection(Direction set) { direction = set; }

};

class XMove :public Movable {
	int target; //カーブ時この位置を目指す
public:
	XMove(int* editPos, Player* player) :target(3) { SetUp(editPos, player); }
	void Update(int speed) {
		switch (GetState())
		{
		case Movable::State::start:

			break;
		case Movable::State::run:
			if (!IsMovable(ReadPlayer()->ClculatLocalX(GetDirection()))) {
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::curve:
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalX(GetDirection()))) { 
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool left = localPos <= 6 && localPos > 3;
		bool right = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ? right : left;
	}
};

class YMove :public Movable {
	int target; //カーブ時この位置を目指す
public:
	YMove(int* editPos, Player* player) :target(3) { SetUp(editPos, player); }
	void Update(int speed) {
		switch (GetState())
		{
		case Movable::State::start:

			break;
		case Movable::State::run:
			if (!IsMovable(ReadPlayer()->ClculatLocalY(GetDirection()))) {
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::curve:
			if (!IsCurveInRange(ReadPlayer()->ClculatLocalY(GetDirection()))) {
				SetState(State::free);
				break;
			}
			Moving(speed);
			break;
		case Movable::State::stop:
			break;
		}
	}
	bool IsCurveInRange(int localPos) {
		bool up = localPos <= 6 && localPos > 3;
		bool down = localPos < 3 && localPos >= 1;
		return (int)((int)GetDirection() / 2) > 0 ?  down : up;
	}
};

class Player::Moving {
public:
private:
	Player* caller; //呼び出し元
	Movable* x;
	Movable* y;

	int safeZone; //マス内座標でsafeZone～TILE-safeZone内でないと新たに曲がる事ができない、その為の変数
	int speed; //速度、現在は状態によらず一定な仮の物
	int speedCount; //速度の蓄積状況記録、毎フレームこれにspeedを加算し、speedCount/MOVABLE_SPEEDの値分描写座標を動かす
	Direction nowDirection; //現在の進行方向
	Direction lastInput; //最後の入力方向保持
public:
	Moving(Player* player) :caller(player), safeZone(2), speed(16), speedCount(0), nowDirection(Direction::left), lastInput(nowDirection), x(new XMove(&caller->posX, caller)),y(new YMove(&caller->posY, caller)) {
		x->SetState(Movable::State::run);
		y->SetDirection(Direction::up);
	}

	void Update() {
		//入力方向の変更処理、方向を押した瞬間、押されっぱなし何れかで入力方向を新しい物に交換する
		//左スティック、十字キーの両方から入力を取る
		//現在は同時押しされた場合優先を「上>左>下>右」の順にする為処理順を「右,下,左,上」の優先とは逆順で行っている(逆順にする事で優先度の低い方向を後から高い方で上書きできる)
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_RIGHT) <= KEY_HOLD || key->GetKeyState(L_STICK_RIGHT) <= KEY_HOLD) { lastInput = Direction::right; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_DOWN) <= KEY_HOLD || key->GetKeyState(L_STICK_DOWN) <= KEY_HOLD) { lastInput = Direction::down; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_LEFT) <= KEY_HOLD || key->GetKeyState(L_STICK_LEFT) <= KEY_HOLD) { lastInput = Direction::left; }
		if (key->GetKeyState(XINPUT_BUTTON_DPAD_UP) <= KEY_HOLD || key->GetKeyState(L_STICK_UP) <= KEY_HOLD) { lastInput = Direction::up; }

		//ワープトンネル処理
		if (caller->ClculatTileX(nowDirection) < 0) { caller->posX = (AREA_X + WARP_AREA_X) * TILE - (caller->center + caller->ClculatCenterRadX(nowDirection) + (8 - caller->ClculatLocalX(nowDirection))); }
		if (caller->ClculatTileX(nowDirection) >= AREA_X + WARP_AREA_X * 2) { caller->posX = -WARP_AREA_X * TILE + (caller->center + caller->ClculatCenterRadX(nowDirection) + caller->ClculatLocalX(nowDirection) + 1); }

		while (nowDirection != lastInput) { //while文を利用したのはbreakを適当な位置に挿入する事でelse文を消せる事が目的、ループさせたい訳ではない
			int subX = caller->ClculatTileX(nowDirection); //中心座標も加味した現在の所属マスx
			int subY = caller->ClculatTileY(nowDirection); //上記のy版
			bool yCurve = (int)lastInput % 2 == 0; //新しい方向が上下何れかになる場合true
			Movable* end = yCurve ? x : y; //移動を取りやめる軸
			Movable* start = yCurve ? y : x; //新しく移動を始める軸

			if ((Direction)(((int)nowDirection + 2) % 4) == lastInput) { //入力方向が反対方向だった場合
				nowDirection = lastInput; //方向を入力のあった方向に変更
				start->SetDirection(nowDirection); //新しい方向の設定
				start->SetState(Movable::State::run); //衝突等で移動終了になってる可能性があるのでrunに再設定
				break; //以降のwhile文内処理は実行しない
			}
			int localX = caller->ClculatLocalX(lastInput); //現在マス内での位置、新しい方向に合わせた物
			int localY = caller->ClculatLocalY(lastInput); //上記のy版

			//下記if文はwhileを用いない場合入れ子にするか1つのif文条件にまとめるかになったので多分見やすくなった…かも
			if ((!yCurve) && (!y->IsCurveInRange(localY))) { break; }
			if (yCurve && (!x->IsCurveInRange(localX))) { break; }
			//if (localX < safeZone - 1 || localX > TILE - safeZone) { break; } //範囲外判定、trueなら終了
			//if (localY < safeZone - 1 || localY > TILE - safeZone) { break; } //上記のy版
			if (x->GetState() == Movable::State::curve || y->GetState() == Movable::State::curve) { break; } //どちらかのタスクがカーブ移動中だった場合
			if (caller->tile[subX][subY].ReadPlayer()[(int)lastInput] == Move::block) { break; } //移動したい方向が移動不可だった場合

			//ここまで来れれば、方向転換可能域に入っている且つどの方向もカーブ中ではなく、最後に入力のあった方向が移動可能である
			end->SetDirection((Direction)(((((int)nowDirection % 2) + 1) % 2) + (int)((int)nowDirection / 2) * 2)); //2で割った時出てくる方向が同じだがxy軸だけ違う方向に変更
			nowDirection = lastInput; //方向を入力のあった方向に変更

			end->SetState(Movable::State::curve); //現在進む方向を曲がる処理に指定
			start->SetState(Movable::State::run); //新しい方向へ移動を開始する
			start->SetDirection(nowDirection); //移動を開始した軸へ新しい方向を設定

			break; //while抜け
		}
		speedCount += speed; //速度加算
		int move = speedCount / MOVABLE_SPEED; //今回の移動ドット数
		speedCount -= move * MOVABLE_SPEED; //移動に使った分のドットを取り除く

		x->Update(move); //座標移動
		y->Update(move);
	}

	Direction GetDirection() { return nowDirection; } //現在の進行方向の取得
};

Player::Player() :isUpdate(true), isDraw(true), renderCenter(3), center(3), rad(1), posX(13 * TILE + (TILE - 1)), posY(23 * TILE), move(new Moving(this)), foodCount(0),start(WorldVal::Get<int>("start")) ,life(WorldVal::Get<int>("Life")) , foodCountTotal(WorldVal::Get<int>("foodCountTotal")), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")), score(WorldVal::Get<int>("score")), highScore(WorldVal::Get<int>("highScore")), diecount(0), killnum(0) {}
Player::~Player() { delete move; }

void Player::Update() {
	int* activeFoodCount;
	activeFoodCount = WorldVal::Get<int>("activeFoodCount");

	if (isUpdate) { //bool変数に停止命令(false)が入れられている場合実行しない
		move->Update();
		std::string sub = std::to_string(ClculatTileX(move->GetDirection())) + "x" + std::to_string(ClculatTileY(move->GetDirection())); //エサ連想配列取得用添え字
		auto itr = food->find(sub); //エサ配列内に指定添え字をキーに持つエサがあるか調べる
		if (itr != food->end() && itr->second->GetEnable()) { //指定位置にエサが配置されている且つエサが食べられる状態である場合
			*score += itr->second->Eat(); //エサを食べる
			Food::Type type = itr->second->GetType(); //食べた物の種類
			if (type == Food::Type::food || type == Food::Type::big) { //種類がエサ、パワーエサの場合食べた個数をカウントする
				++foodCount;
				++(*activeFoodCount);
				++(*foodCountTotal);
			}
			if (*score >= *highScore) { *highScore = *score; } //ハイスコアより値が大きくなった場合ハイスコアの値を更新する
		}
	}
	DrawFormatString(400, 50, GetColor(255, 255, 255), "エサ%d", *activeFoodCount);
}

void Player::Draw() {
	if (isDraw) { //bool変数に停止命令(false)が入れられている場合実行しない
		//画像サイズ-1の半分(小数点切り捨て)を引いて描写する事でマスの中心位置にいる場合表示もそのマスの中心位置となる

		int actMotion[] = { 0,1,2,1, };
		Direction angle = move->GetDirection(); //現在の進行方向
		int moveAnim = (int)move->GetDirection() * 3;

		//パックマンが縦または横に移動している時
		if (posX - animX != 0 || posY - animY != 0) {
			//移動アニメ処理
			if (--actWait <= 0) {
				actIndex++;
				actWait = actSpeed;
				actIndex %= maxMotion;
			}
		}
		else {
			if (actIndex == 0) {
				actIndex += 2;
			}
		}

		animX = posX;
		animY = posY;
		motionIndex = actMotion[actIndex] + moveAnim;



		DrawFormatString(0, 10, GetColor(255, 255, 255), "%2d", motionIndex);
		DrawCircle(SHIFT_X + (posX + ClculatCenterRadX(angle)) * X_RATE, SHIFT_Y + (posY+ ClculatCenterRadY(angle)) * Y_RATE,65 * X_RATE,GetColor(0,255,0),false);
		DrawRotaGraph3(SHIFT_X + (posX - renderCenter + ClculatCenterRadX(angle)) * X_RATE, SHIFT_Y + (posY - renderCenter + ClculatCenterRadY(angle)) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[motionIndex], true);

		DrawHitBox(ClculatTileX(angle), ClculatTileY(angle), GetColor(255, 189, 78)); //デバッグ表示
	}
}

int Player::ClculatCenterRadX(Direction angle) const { return rad * std::sin((360 - 90 * (int)angle) * (PI / 180)); }  //各種方向に合わせてradの符号を変える事で中心座標の精製を行う
int Player::ClculatCenterRadY(Direction angle) const { return rad * std::sin((360 - 90 * (int)angle + 270) * (PI / 180)); }
int Player::ClculatLocalX(Direction angle) const {
	int raw = posX + center + ClculatCenterRadX(angle); //xの中心位置を出す
	int sub = raw / TILE; //マス座標を出す
	//return raw - sub * TILE; //マス座標を通常座標に戻す事でマスの左上通常座標が求まりx中心位置から引けばマス内の位置を割り出せる
	return raw % TILE;
}
int Player::ClculatLocalY(Direction angle) const {
	int raw = posY + center + ClculatCenterRadY(angle);
	int sub = raw / TILE;
	//return raw - sub * TILE;
	return raw % TILE;
}
int Player::ClculatTileX(Direction angle) const { return (posX + center + ClculatCenterRadX(angle)) / TILE + WARP_AREA_X; }
int Player::ClculatTileY(Direction angle) const { return (posY + center + ClculatCenterRadY(angle)) / TILE + WARP_AREA_Y; }

Direction Player::GetDirection()const { return move->GetDirection(); }

void Player::DieAnim()
{
	isUpdate = false;
	isDraw = false;
	diecount++;
	//Direction angle = move->GetDirection(); //現在の進行方向
	DrawRotaGraph3(SHIFT_X + (posX - renderCenter/* + ClculatCenterRadX(angle)*/) * X_RATE, SHIFT_Y + (posY - renderCenter/* +*//* ClculatCenterRadY(angle)*/) * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, killImg[killnum], true);

	if (diecount % 10 == 0)
	{
		killnum++;
		//if (killnum > 10)
		//{
		//	killnum = 0;
		//}
	}
}
void Player::Restart() {
}