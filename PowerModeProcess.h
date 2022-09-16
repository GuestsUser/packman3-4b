#pragma once
#include <deque>

class Player;
class EnemyAra;

class PowerModeProcess {
public:
	enum class State { start, run, end, free }; //���s�󋵌n�X�e�[�g
private:
	static int time; //���s�c�莞��
	static int drawTime; //�G��H�ׂ����̃X�R�A�\���c�莞��
	static int rawDrawTime; //�X�R�A�\���c�莞�Ԃ̏����l�A�l�̏����������������

	int combo; //1��̃p���[�G�T�œG��H�ׂ��񐔋L�^
	EnemyAra* target; //�X�R�A�\���̃^�[�Q�b�g�G�l�~�[


	static State state; //���݂̎��s�󋵁A1�̂ݑ���
	Player* player; //�v���C���[�Q��
	std::deque<EnemyAra*>* enemy; //�G�l�~�[�Q��

	int ClculatIniTime(); //���݃X�e�[�W������s���Ԃ�Ԃ��֐�
	int ClculatScore(); //���݂̃R���{�l������Z�X�R�A���v�Z
public:
	PowerModeProcess(Player* setPlayer, std::deque<EnemyAra*>* setEnemy);

	void Update();
	void Draw();

	void Hit(EnemyAra* set); //�p���[�G�T�L�����Ƀq�b�g�������������Ăяo���֐�
	static void PowerModeStart() { state = State::start; } //�p���[�G�T�擾��Ԃ̋N��
	static State GetState() { return state; } //���s�󋵂�Ԃ��Afree�Œʏ�Arun�Ńp���[�G�T���s��

	static int GetTimeLeft() { return time; } //���݂̎c�莞�Ԃ��擾����
	static bool GetIsPause() { return drawTime > 0; } //�|�[�Y���̃X�R�A�\�����������Ă����true
};