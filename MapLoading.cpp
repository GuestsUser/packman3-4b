#include "MapLoading.h"
#include "Grid.h"
#include "Worldval.h"
#include <deque>

void MapLoading() {
	Grid** grid = new Grid * [31]; //�c
	for (int i = 0; i < 31; ++i) { grid[i] = new Grid[36]; } //���A�ʏ��28�}�X�������E�[�̃��[�v�g���l������ʊO��4�}�X�Ōn36�}�X

	//������1�}�X���ړ��\�������L���Ă䂭�c�c
	//Grid�͏������i�K�ł͑S�Ă̏�Ԃɂ����Ďl�����ړ��s�\�ɐݒ肳��Ă�̂Ńp�b�N�}�����G����������Ȃ��ꏊ�͐ݒ肵�Ȃ��Ă���
	//���̊֐��̓}�X���W(1,2)�̃}�X���A�p�b�N�}���A�G�A�C�W�P��Ԃ݂̂����A�E�ɓ�����ݒ�����Ă���(deque�͉ϒ������Avector�̂悤�ȕ�)

	//5���(�w��ʒu�݂̂̏���)
	grid[5][1].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][5].Set(Move::movable, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[5][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//6���
	grid[6][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[6][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[6][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//7���
	grid[7][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[7][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[7][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//8���
	grid[8][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[8][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[8][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//9���
	grid[9][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[9][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[9][8].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//10���
	grid[10][1].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][5].Set(Move::movable, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][8].Set(Move::movable, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[10][11].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//11���
	grid[11][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[11][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//12���
	grid[12][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[12][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//13���
	grid[13][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][5].Set(Move::block, Move::movable, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][6].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][7].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][8].Set(Move::movable, Move::block, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[13][11].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//14���
	grid[14][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[14][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//15���
	grid[15][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[15][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//16���
	grid[16][1].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][2].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][3].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][4].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][5].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][8].Set(Move::block, Move::movable, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][9].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][10].Set(Move::movable, Move::block, Move::movable, Move::block, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[16][11].Set(Move::movable, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	//17���
	grid[17][5].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});
	grid[17][11].Set(Move::block, Move::movable, Move::block, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});

	WorldVal::Set("map", grid); //���������O���b�h��map�Ƃ������O�őS�̂ɋ��L����
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //�S�̗̈悩��}�b�v�̎擾
	for (int i = 0; i < 31; ++i) { delete[] grid[i]; } //�e�v�f�̍폜
	delete[] grid; //�S�̂̍폜
}