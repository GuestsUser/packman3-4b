#pragma once

enum class Direction { up, left, down, right }; //�ړ�����
enum class Move { movable, block }; //movable=�ړ��\ block=�ړ��s��

class Grid {
	Move player[4];
	Move enemy[4];
	//�C�W�P��ԁA�����Ԃ̓G��Move����`����A��������������ɒ�`���Ȃ������̂̓C�W�P��Ԃɂǂ������X�y����U��΂������v�����Ȃ���������

public:
	Grid();
};