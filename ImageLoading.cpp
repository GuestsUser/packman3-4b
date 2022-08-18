#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

//�摜�ǂݍ���
void ImageLoading() {
	int* handle = new int[10];
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle);
	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
	WorldVal::Set("foodImage", handle);
	WorldVal::Set("playerOneImage", new int(LoadGraph("Resource/image/playerone.png")));//�Q�[���X�^�[�g��PlayerOne
	WorldVal::Set("readyImage", new int(LoadGraph("Resource/image/ready.png")));		//�Q�[���X�^�[�g��Ready!
	WorldVal::Set("clearImage1", new int(LoadGraph("Resource/image/Clear1.png")));		//�Q�[���N���A���i���j
	WorldVal::Set("clearImage2", new int(LoadGraph("Resource/image/Clear2.png")));		//�Q�[���N���A���i�j
	WorldVal::Set("gameOverImage", new int(LoadGraph("Resource/image/gameOver.png")));	//�Q�[���I�[�o�[��
}

//�摜�폜
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
