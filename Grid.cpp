#include "Grid.h"

//Grid::Grid() :
//	player{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	enemy{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	cringe{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	damage{ Move::movable,Move::movable ,Move::movable ,Move::movable },
//	wait{ Move::movable,Move::movable ,Move::movable ,Move::movable }{ } //�������A�S�Ă̏�Ԃ̈ړ��\�������u���b�N����

Grid::Grid() :
	player{ Move::block,Move::block ,Move::block ,Move::block },
	enemy{ Move::block,Move::block ,Move::block ,Move::block },
	cringe{ Move::block,Move::block ,Move::block ,Move::block },
	damage{ Move::block,Move::block ,Move::block ,Move::block },
	wait{ Move::block,Move::block ,Move::block ,Move::block }{ } //�������A�S�Ă̏�Ԃ̈ړ��\�������u���b�N����

void Grid::Set(Move up, Move left, Move down, Move right, std::deque<Chara> set) {
	Move moveData[4] = { up,left,down,right }; //�V�����ړ������ݒ�
	if (set.size() <= 0) { //set�̈����ȗ��͑S�w�舵��(�f�t�H���g�������ł�static�ȊO�̃N���X���I�u�W�F�N�g�������Ɏ��Ȃ��̂ł������Œ�`��������)
		for (int i = 0; i < 4; ++i) { 
			player[i] = moveData[i];
			enemy[i] = moveData[i];
			cringe[i] = moveData[i];
			damage[i] = moveData[i];
			wait[i] = moveData[i];
		}
		return;
	}
	for (Chara get : set) { //�w���ԂɈړ�������ݒ肷��
		Move* edit = nullptr;
		switch (get) { //set���Ŏw�肳�ꂽ�L�����N�^�[�̈ړ�������ݒ肷��
		case Chara::p: edit = player; break;
		case Chara::e: edit = enemy; break;
		case Chara::c: edit = cringe; break;
		case Chara::d: edit = damage; break;
		case Chara::w: edit = wait; break;
		}
		for (int i = 0; i < 4; ++i) { edit[i] = moveData[i]; } //�A�h���X�u���������ƃX�R�[�v�����ŏ��ł�����������l�̃��[�v�R�s�[
	}
}