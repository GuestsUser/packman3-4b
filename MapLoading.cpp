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
	//grid[1][2].Set(Move::block, Move::block, Move::movable, Move::movable, std::deque<Chara>{Chara::p, Chara::e, Chara::c});


	WorldVal::Set("map", grid); //���������O���b�h��map�Ƃ������O�őS�̂ɋ��L����
}

void MapDel() {
	Grid** grid = *WorldVal::Get<Grid**>("map"); //�S�̗̈悩��}�b�v�̎擾
	for (int i = 0; i < 31; ++i) { delete[] grid[i]; } //�e�v�f�̍폜
	delete[] grid; //�S�̂̍폜
}