#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

//画像読み込み
void ImageLoading() {
	int* handle = new int[10];
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle);
	WorldVal::Set("foodImage", handle);

	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
	WorldVal::Set("playerOneImage", new int(LoadGraph("Resource/image/playerone.png")));//ゲームスタート時PlayerOne
	WorldVal::Set("readyImage", new int(LoadGraph("Resource/image/ready.png")));		//ゲームスタート時Ready!
	WorldVal::Set("clearImage1", new int(LoadGraph("Resource/image/Clear1.png")));		//ゲームクリア時（白）
	WorldVal::Set("clearImage2", new int(LoadGraph("Resource/image/Clear2.png")));		//ゲームクリア時（青）
	WorldVal::Set("gameOverImage", new int(LoadGraph("Resource/image/gameOver.png")));	//ゲームオーバー時

	//LoadDivGraphの都合上毎回新しい領域をポインタ型変数に格納しないといけないのはネック
	handle = new int[12];
	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, handle); //パックマンの画像読み込み
	WorldVal::Set("playerImage", handle);

	handle = new int[11];
	LoadDivGraph("Resource/image/dying.png", 11, 11, 1, 16, 16, handle); //パックマンやられモーション読み込み
	WorldVal::Set("killImage", handle);

	handle = new int[20];
	LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 16, 16, handle); //敵画像読み込み
	WorldVal::Set("enemyImage", handle);
	
	handle = new int[4];
	LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 16, 16, handle); //敵の目の画像読み込み
	WorldVal::Set("enemyImageEye", handle);
}



//画像削除
void ImageDel() {
	DeleteGraph(*WorldVal::Get<int>("mapImage"));
	DeleteGraph(*WorldVal::Get<int>("playerOneImage"));
	DeleteGraph(*WorldVal::Get<int>("readyImage"));
	DeleteGraph(*WorldVal::Get<int>("clearImage1"));
	DeleteGraph(*WorldVal::Get<int>("clearImage2"));
	DeleteGraph(*WorldVal::Get<int>("gameOverImage"));

	//分割読み込み画像の削除
	int* handle = *WorldVal::Get<int[10]>("foodImage");
	for (int i = 0; i < 10; ++i) { DeleteGraph(handle[i]); }

	handle = *WorldVal::Get<int[12]>("playerImage");
	for (int i = 0; i < 12; ++i) { DeleteGraph(handle[i]); }

	handle = *WorldVal::Get<int[11]>("killImage");
	for (int i = 0; i < 11; ++i) { DeleteGraph(handle[i]); }

	handle = *WorldVal::Get<int[20]>("enemyImage");
	for (int i = 0; i < 20; ++i) { DeleteGraph(handle[i]); }

	handle = *WorldVal::Get<int[4]>("enemyImageEye");
	for (int i = 0; i < 4; ++i) { DeleteGraph(handle[i]); }
}
