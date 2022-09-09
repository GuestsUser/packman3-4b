#include "MapLoading.h"
#include "Grid.h"
#include "Worldval.h"
#include "ConstVal.h"
#include <deque>

void MapLoading() {
	Grid** grid = new Grid * [AREA_X + WARP_AREA_X * 2]; //���A�ʏ��28�}�X�������E�[�̃��[�v�g���l������ʊO��4�}�X�Ōn36�}�X
	for (int i = 0; i < AREA_X + WARP_AREA_X * 2; ++i) { grid[i] = new Grid[AREA_Y + WARP_AREA_Y]; } //�c

	//������1�}�X���ړ��\�������L���Ă䂭�c�c
	//Grid�͏������i�K�ł͑S�Ă̏�Ԃɂ����Ďl�����ړ��s�\�ɐݒ肳��Ă�̂Ńp�b�N�}�����G����������Ȃ��ꏊ�͐ݒ肵�Ȃ��Ă���
	//���̊֐��̓}�X���W(1,2)�̃}�X���A�p�b�N�}���A�G�A�C�W�P��Ԃ݂̂����A�E�ɓ�����ݒ�����Ă���(deque�͉ϒ������Avector�̂悤�ȕ�)

	//0��ځi�����j
	grid[0][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//1��ځi�����j
	grid[1][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//2��ځi�����j
	grid[2][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//3��ځi�����j
	grid[3][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//4��ځi�����j
	grid[4][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//5��ځi�����j
	grid[5][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][5].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][20].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][23].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][26].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[5][29].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//6��ځi�����j
	grid[6][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[6][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//7��ځi�����j
	grid[7][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][23].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][26].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[7][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//8��ځi�����j
	grid[8][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[8][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//9��ځi�����j
	grid[9][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[9][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//10��ځi�����j
	grid[10][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][8].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][14].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][17].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][20].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][23].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][26].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[10][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//11��ځi�����j
	grid[11][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[11][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//12��ځi�����j
	grid[12][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[12][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//13��ځi�����j
	grid[13][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][11].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][14].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][17].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][20].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][23].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][26].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[13][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//14��ځi�����j
	grid[14][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[14][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//15��ځi�����j
	grid[15][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[15][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//16��ځi�����j
	grid[16][1].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][8].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});	//�������ʍs
	grid[16][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][20].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][23].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //��������ʍs
	grid[16][26].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[16][29].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//17��ځi�����j
	grid[17][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[17][11].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::d});	//������
	grid[17][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//������
	grid[17][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//������
	grid[17][14].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::d});	//������
	grid[17][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[17][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//18��ځi�����j
	grid[18][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[18][11].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::d});	//������
	grid[18][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//������
	grid[18][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::d});	//������
	grid[18][14].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::d});	//������
	grid[18][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[18][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//19��ځi�����j
	grid[19][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][8].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //�E�����ʍs
	grid[19][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][20].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][23].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::e});  //�E������ʍs
	grid[19][26].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[19][29].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//20��ځi�����j
	grid[20][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[20][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//21��ځi�����j
	grid[21][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][17].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[21][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//22��ځi�����j
	grid[22][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][8].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][11].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][14].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][17].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][20].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][23].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][26].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[22][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//23��ځi�����j
	grid[23][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[23][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//24��ځi�����j
	grid[24][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[24][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//25��ځi�����j
	grid[25][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][8].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][12].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][13].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][14].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][15].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][16].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][17].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][18].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][19].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][20].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][23].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][26].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[25][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//26��ځi�����j
	grid[26][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[26][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//27��ځi�����j
	grid[27][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[27][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//28��ځi�����j
	grid[28][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][23].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][24].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][25].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][26].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[28][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//29��ځi�����j
	grid[29][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][20].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][23].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][26].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[29][29].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//30��ځi�����j
	grid[30][1].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][5].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][8].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][20].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][21].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][22].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][23].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][26].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][27].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][28].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});
	grid[30][29].Set(Move::movable, Move::movable, Move::block, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//31��ځi�����j
	grid[31][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//32��ځi�����j
	grid[32][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//33��ځi�����j
	grid[33][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//34��ځi�����j
	grid[34][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	//35��ځi�����j
	grid[35][14].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c, Chara::d});

	WorldVal::Set("map", grid); //���������O���b�h��map�Ƃ������O�őS�̂ɋ��L����
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //�S�̗̈悩��}�b�v�̎擾
	for (int i = 0; i < 36; ++i) { delete[] grid[i]; } //�e�v�f�̍폜
	delete[] grid; //�S�̂̍폜
}