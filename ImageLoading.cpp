#include "DxLib.h"
#include "ImageLoading.h"
#include "Worldval.h"

//�摜�ǂݍ���
void ImageLoading() {
	int* handle = new int[10];
	LoadDivGraph("Resource/image/item.png", 10, 10, 1, 16, 16, handle);
	WorldVal::Set("foodImage", handle);

	WorldVal::Set("mapImage", new int(LoadGraph("Resource/image/Stage.png")));
	WorldVal::Set("playerOneImage", new int(LoadGraph("Resource/image/playerone.png")));//�Q�[���X�^�[�g��PlayerOne
	WorldVal::Set("readyImage", new int(LoadGraph("Resource/image/ready.png")));		//�Q�[���X�^�[�g��Ready!
	WorldVal::Set("clearImage1", new int(LoadGraph("Resource/image/Clear1.png")));		//�Q�[���N���A���i���j
	WorldVal::Set("clearImage2", new int(LoadGraph("Resource/image/Clear2.png")));		//�Q�[���N���A���i�j
	WorldVal::Set("gameOverImage", new int(LoadGraph("Resource/image/gameOver.png")));	//�Q�[���I�[�o�[��

	//LoadDivGraph�̓s���㖈��V�����̈���|�C���^�^�ϐ��Ɋi�[���Ȃ��Ƃ����Ȃ��̂̓l�b�N
	handle = new int[12];
	LoadDivGraph("Resource/image/pacman.png", 12, 12, 1, 16, 16, handle); //�p�b�N�}���̉摜�ǂݍ���
	WorldVal::Set("playerImage", handle);

	handle = new int[11];
	LoadDivGraph("Resource/image/dying.png", 11, 11, 1, 16, 16, handle); //�p�b�N�}�����ꃂ�[�V�����ǂݍ���
	WorldVal::Set("killImage", handle);

	handle = new int[20];
	LoadDivGraph("Resource/image/monster.png", 20, 20, 1, 16, 16, handle); //�G�摜�ǂݍ���
	WorldVal::Set("enemyImage", handle);
	
	handle = new int[4];
	LoadDivGraph("Resource/image/eyes.png", 4, 4, 1, 16, 16, handle); //�G�̖ڂ̉摜�ǂݍ���
	WorldVal::Set("enemyImageEye", handle);
}



//�摜�폜
void ImageDel() {
	DeleteGraph(*WorldVal::Get<int>("mapImage"));
	DeleteGraph(*WorldVal::Get<int>("playerOneImage"));
	DeleteGraph(*WorldVal::Get<int>("readyImage"));
	DeleteGraph(*WorldVal::Get<int>("clearImage1"));
	DeleteGraph(*WorldVal::Get<int>("clearImage2"));
	DeleteGraph(*WorldVal::Get<int>("gameOverImage"));

	//�����ǂݍ��݉摜�̍폜
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
