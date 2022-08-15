#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

void ImageLoading() {
	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
}
void ImageDel() {
	DeleteGraph(*WorldVal::Get<int>("mapImage"));
}
