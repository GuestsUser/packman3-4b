#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

//画像読み込み
void ImageLoading() {
	int* handle = new int[10];
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle);
	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
	WorldVal::Set("foodImage", handle);
	WorldVal::Set("playerOneImage", new int(LoadGraph("Resource/image/playerone.png")));//ゲームスタート時PlayerOne
	WorldVal::Set("readyImage", new int(LoadGraph("Resource/image/ready.png")));		//ゲームスタート時Ready!
	WorldVal::Set("clearImage1", new int(LoadGraph("Resource/image/Clear1.png")));		//ゲームクリア時（白）
	WorldVal::Set("clearImage2", new int(LoadGraph("Resource/image/Clear2.png")));		//ゲームクリア時（青）
	WorldVal::Set("gameOverImage", new int(LoadGraph("Resource/image/gameOver.png")));	//ゲームオーバー時
}

//画像削除
void ImageDel() {
	DeleteGraph(*WorldVal::Get<int>("mapImage"));
	DeleteGraph(*WorldVal::Get<int>("playerOneImage"));
	DeleteGraph(*WorldVal::Get<int>("readyImage"));
	DeleteGraph(*WorldVal::Get<int>("clearImage1"));
	DeleteGraph(*WorldVal::Get<int>("clearImage2"));
	DeleteGraph(*WorldVal::Get<int>("gameOverImage"));
	int* handle = *WorldVal::Get<int[10]>("foodImage");
	for (int i = 0; i < 10; ++i) { DeleteGraph(handle[i]); }
}
