#include "Player.h"
#include "GetKey.h"
#include "Worldval.h"
#include "ConstVal.h"
#include "Food.h"
#include "Grid.h"
#include <unordered_map>
#include <string>

Player::Player() :isUpdate(true), isDraw(true), subX(17), subY(23), drawX(subX* TILE - WARP_AREA_X * TILE ), drawY(subY* TILE - WARP_AREA_Y * TILE - TILE / 2), speedCount(0), foodCount(0), foodCountTotal(0), playerImg(*WorldVal::Get<int[12]>("playerImage")), killImg(*WorldVal::Get<int[11]>("killImage")), food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), tile(WorldVal::Get<Grid*>("map")) {}

void Player::Update() {

}
void Player::Draw() {
	DrawRotaGraph3(SHIFT_X + drawX * X_RATE, SHIFT_Y + drawY * Y_RATE, 0, 0, X_RATE, Y_RATE, 0, playerImg[0], true);
}