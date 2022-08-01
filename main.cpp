//この部分のコメントアウトを外すとデバッグ終了時にnewの開放し忘れをメモリ数で通知してくれる
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )

#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //デバッグ表示を可能にする
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) { return -1; }//初期化と異常が認められた場合の終了
	SetDrawScreen(DX_SCREEN_BACK);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//_RPTF1(_CRT_WARN, "%s\n", "test"); //デバッグ表示
	}
	DxLib_End();// ＤＸライブラリ使用の終了処理

	return 0;
}