#pragma once
#include "DxLib.h"

//���̃t�@�C�����C���N���[�h�����key�Ƃ����ϐ����g�p�\�ɂȂ�A��������L�[���͂Ɋւ���l�X�ȏ����󂯎���

constexpr short SHORT_SIZE = 32767; //short�ő�l�A�X�e�B�b�N�̌X����short�̒l�ŕԂ��Ă���炵���̂ł���ɏ����_���|�����
constexpr double X_TILT_MIN = SHORT_SIZE * 0.4; //�X�e�B�b�N�̌X�������ꖢ���̏ꍇ���͔���ɂ͂Ȃ�Ȃ��A�����x���p
constexpr double Y_TILT_MIN = SHORT_SIZE * 0.4; //��L��y���p

//GetKeyState�ŕԂ��Ă���l�AA�{�^��(�΃{�^��)�������������ǂ����ŏ������򂵂����ꍇ if (GetKeyState(A_KEY) == KEY_PUSH) { �������u�Ԃ̏��� } �̂悤�ȋ�ɂȂ�
extern constexpr int KEY_PUSH = 0; //�������u��
extern constexpr int KEY_HOLD = 1; //�������ςȂ�
extern constexpr int KEY_PULL = 2; //�������u��
extern constexpr int KEY_FREE = 3; //�������ςȂ�

//GetKeyState���ň����ɓn���ϐ��AA�{�^��(�΃{�^��)�̏�Ԃ��m�肽��������GetKeyState(A_KEY)�Ŏ擾�ł���
//���̃��X�g�ɍڂ��ĂȂ��悤�Ɍ���LT�ART�{�^���̏�Ԃ͎󂯎��Ȃ�
extern int A_KEY;
extern int B_KEY;
extern int X_KEY;
extern int Y_KEY;
extern int L_KEY;
extern int R_KEY;
extern int POUSE_KEY; //start
extern int SELECT_KEY; //back

//KeySystem�e�֐���request�ɃX�e�B�b�N�����N�G�X�g����ׂ�const�l�A���̑��{�^���Ƃ̏d����������100����ɑł��Ă���
//
extern constexpr int L_STICK_UP = 100;
extern constexpr int L_STICK_DOWN = 101;
extern constexpr int L_STICK_LEFT = 102;
extern constexpr int L_STICK_RIGHT = 103;
extern constexpr int R_STICK_UP = 104;
extern constexpr int R_STICK_DOWN = 105;
extern constexpr int R_STICK_LEFT = 106;
extern constexpr int R_STICK_RIGHT = 107;

//GetTilt�Ɏw�肷��X�e�B�b�N�X������
extern constexpr int LX_TILT = 0; //���X�e�B�b�N��x���̓������`�F�b�N����A-�Ȃ獶�A+�Ȃ�E�ɌX���Ă���
extern constexpr int LY_TILT = 1; //���X�e�B�b�Ny���̓���������A-�Ȃ牺�A+�Ȃ��ɌX���Ă���
extern constexpr int RX_TILT = 2; //��L�̉E�X�e�B�b�N�p
extern constexpr int RY_TILT = 3;

//Xinput�ł͏�����A�E�������v���X�炵���̂ŉ������ςȂ��z�񓙂�dulr(���A��A���A�E)�̏��Ԃŕ���ł���

class KeySystem {
private:
	const int key_vol = 12;
	int key_state[20];
	int hold_time[20];
	double tilt[4];
	XINPUT_STATE input;
public:
	KeySystem();
	//~KeySystem();
	void KeyInput(); //�L�[���͎�t�֐��A����𖈃t���[��1��Ăяo�����ŃL�[�̏�Ԃ��X�V����
	int GetKeyState(int request); //�w��L�[��������Ă邩�ǂ������擾�ł���A�����ɂ͎擾�������L�[���w�肷��
	int GetKeyHoldTime(int request); //�w��L�[���������ςȂ��A�������ςȂ��Ȃ炻�̃t���[�������擾�ł���
	double GetTilt(int request) { return tilt[request]; } //�w��X�e�B�b�N�̌X���̒l���擾�ł���
};

extern KeySystem* key; //�O���[�o���ϐ��錾�A�w�b�_�[�ɐ錾���ڂ��鎖�ő��t�@�C��������Ăяo���\�ɂȂ�