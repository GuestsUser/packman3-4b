//���̕����̃R�����g�A�E�g���O���ƃf�o�b�O�I������new�̊J�����Y������������Œʒm���Ă����
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )

#include "DxLib.h"
#include "ConstVal.h"
#include "Title.h"
#include "GetKey.h"
#include "SceneManager.h"
#include "Worldval.h"
#include "FoodLoading.h"
#include "ImageLoading.h"
#include "MapLoading.h"
#include "ScoreLoading.h"
//�ŏ��Ɏ��s�������V�[���̃w�b�_�[���C���N���[�h���Ă���

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�f�o�b�O�\�����\�ɂ���
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) { return -1; }		//�������ƈُ킪�F�߂�ꂽ�ꍇ�̏I��

	int fps = 1000000 / FPS; //����l��ς����1�b�Ԃɍs�������񐔂�ύX�ł���
	LONGLONG now = GetNowHiPerformanceCount();
	LONGLONG old = now;

	//�E�B���h�E�̏����ݒ�
	SetWindowText("PAC MAN");			//��ʃ^�C�g���ݒ�
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);		//��ʃ��[�h�̐ݒ�
	SetBackgroundColor(0, 0, 0);		//��ʂ̔w�i�F�̐ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	WorldVal::SetUp(); //�V�[�����ׂ����ϐ����L�N���X�̏�����
	key = new KeySystem(); //�L�[���͎�t�p�N���X�̎��̍쐬
	SceneManager* scm = new SceneManager(new Title()); //�����ɍŏ��Ɏ��s�������V�[�����̂�����

	ImageLoading();
	FoodLoading();
	MapLoading();
	ScoreLoading();

	while (ProcessMessage() == 0 && (!CheckHitKey(KEY_INPUT_ESCAPE))) {
		//_RPTF1(_CRT_WARN, "%s\n", "test"); //�f�o�b�O�\��

		now = GetNowHiPerformanceCount(); //���ݎ����̎擾
		if (now - old > fps) { //�O�t���[���̌��ݎ����Ƃ̍������s�^�C�~���O�ɂȂ��Ă����ꍇ�Q�[�������A�`�ʂ̎��s
			key->KeyInput(); //�L�[���͍X�V
			old = now - (now - old); //�������s�^�C�~���O�ȏゾ�����ꍇ���̂܂�old�Ɍ��ݎ���������Ɛ؂�̂Ă��Ă��܂��̂�old������s�^�C�~���O���ߕ����������Œ��ߕ������������`�ɂ���
			ClearDrawScreen(); //��ʂ̏�����
			if (!scm->Update()) { break; } //�E�B���h�E�����w�����o����Ă���I��
			scm->Draw(); //��ʕ`��
		}
		ScreenFlip();
	}
	ImageDel();
	FoodDel();
	MapDel();
	//ScoreDel();
	WorldVal::Destruct(); //�l���L�̎��̔j��
	delete key;
	delete scm;
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;
}