//���̕����̃R�����g�A�E�g���O���ƃf�o�b�O�I������new�̊J�����Y������������Œʒm���Ă����
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )

#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�f�o�b�O�\�����\�ɂ���
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) { return -1; }//�������ƈُ킪�F�߂�ꂽ�ꍇ�̏I��
	SetDrawScreen(DX_SCREEN_BACK);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//_RPTF1(_CRT_WARN, "%s\n", "test"); //�f�o�b�O�\��
	}
	DxLib_End();// �c�w���C�u�����g�p�̏I������

	return 0;
}