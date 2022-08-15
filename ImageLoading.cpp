#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

void ImageLoading() {
	int* handle = new int[10];
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle); //âÊëúì«Ç›çûÇ›
	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
	WorldVal::Set("foodImage", handle);
}
void ImageDel() {
	DeleteGraph(*WorldVal::Get<int>("mapImage"));
	int* handle = *WorldVal::Get<int[10]>("foodImage");
	for (int i = 0; i < 10; ++i) { DeleteGraph(handle[i]); }
}
