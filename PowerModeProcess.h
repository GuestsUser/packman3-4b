#pragma once
#include <deque>

class Player;
class EnemyAra;

class PowerModeProcess {
public:
	enum class State { start, run, end, free }; //���s�󋵌n�X�e�[�g
private:
	int time; //���s�c�莞��

	static State state; //���݂̎��s�󋵁A1�̂ݑ���
	Player* player; //�v���C���[�Q��
	std::deque<EnemyAra*>* enemy; //�G�l�~�[�Q��

	int ClculatIniTime(); //���݃X�e�[�W������s���Ԃ�Ԃ��֐�
public:
	PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy);

	void Update();
	void Draw() {} //�Ȃ�Ɏg�����͖���̕`�ʊ֐�

	static void PowerModeStart() { state = State::start; } //�p���[�G�T�擾��Ԃ̋N��
	static State GetState() { return state; } //���s�󋵂�Ԃ��Afree�Œʏ�Arun�Ńp���[�G�T���s��
};