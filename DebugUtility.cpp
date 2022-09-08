#include "DxLib.h"
#include "DebugUtility.h"
#include "ConstVal.h"

void DrawHitBox(int tileX, int tileY, unsigned int color) { 
	int x = (tileX - WARP_AREA_X) * TILE * X_RATE + SHIFT_X;
	int y = (tileY - WARP_AREA_Y) * TILE * Y_RATE + SHIFT_Y;
	DrawBox(x, y, x + TILE * X_RATE, y + TILE * Y_RATE, color, false); //�f�o�b�O�\����؂肽���ꍇ������R�����g�A�E�g����Ώ�����
}
void DrawTargetLine(int tX1, int tY1, int tX2, int tY2, unsigned int color) {
	int center = 3; //�e��摜�̒��S�A���ߑł��������C���͓G�ƃ^�[�Q�b�g�����ԖړI�Ȃ̂ł���ł������Ȃ�
	int x1 = (tX1 - WARP_AREA_X) * TILE * X_RATE + SHIFT_X + center;
	int y1 = (tY1 - WARP_AREA_Y) * TILE * Y_RATE + SHIFT_Y + center;
	int x2 = (tX2 - WARP_AREA_X) * TILE * X_RATE + SHIFT_X + center;
	int y2 = (tY2 - WARP_AREA_Y) * TILE * Y_RATE + SHIFT_Y + center;
	DrawLine(x1, y1, x2, y2, color);
}