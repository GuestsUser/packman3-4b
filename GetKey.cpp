#include "DxLib.h"
#include "GetKey.h"

#include <cmath>

int A_KEY = XINPUT_BUTTON_A;
int B_KEY = XINPUT_BUTTON_B;
int X_KEY = XINPUT_BUTTON_X;
int Y_KEY = XINPUT_BUTTON_Y;
int L_KEY = XINPUT_BUTTON_LEFT_SHOULDER;
int R_KEY = XINPUT_BUTTON_RIGHT_SHOULDER;
int POUSE_KEY = XINPUT_BUTTON_START;
int SELECT_KEY = XINPUT_BUTTON_BACK;
KeySystem* key;

KeySystem::KeySystem() :input{0} {
	for (int i = 0; i < key_vol+8; i++) { key_state[i] = KEY_FREE; hold_time[i] = 0; }
	SetJoypadDeadZone(DX_INPUT_PAD1, 0);//KeyInput�œ��͖��������s���Ă���̂ł�����̏����͐؂�AKeyInput�Ƃ�����̈Ⴂ�Ƃ��Ă�KeyInput��x���Ay���ʂɖ����͈͂����߂��鎖�ɂ���c�c
}

void KeySystem::KeyInput() {
	int c_key=0;
	if (GetJoypadXInputState(DX_INPUT_PAD1, &input) == -1) { return; }//�G���[�΍�

	for (int i = 0; i < key_vol; i++) {
		switch (i) {
		case 0:c_key = XINPUT_BUTTON_DPAD_UP; break;
		case 1:c_key = XINPUT_BUTTON_DPAD_DOWN; break;
		case 2:c_key = XINPUT_BUTTON_DPAD_LEFT; break;
		case 3:c_key = XINPUT_BUTTON_DPAD_RIGHT; break;
		case 4:c_key = A_KEY; break;
		case 5:c_key = B_KEY; break;
		case 6:c_key = X_KEY; break;
		case 7:c_key = Y_KEY; break;
		case 8:c_key = L_KEY; break;
		case 9:c_key = R_KEY; break;
		case 10:c_key = POUSE_KEY; break;
		case 11:c_key = SELECT_KEY; break;
		}
		if (input.Buttons[c_key]) {
			if (hold_time[i] > 0) { key_state[i] = KEY_HOLD; }
			else { key_state[i] = KEY_PUSH; }
			hold_time[i]++;
		}
		else {
			if (hold_time[i] > 0) { key_state[i] = KEY_PULL; }
			else { key_state[i] = KEY_FREE; }
			hold_time[i] = 0;
		}
	}

	//�X�e�B�b�N���͏�ԓ���
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:c_key = input.ThumbLY; break;
		case 1:c_key = input.ThumbLX; break;
		case 2:c_key = input.ThumbRY; break;
		case 3:c_key = input.ThumbRX; break;
		}

		tilt[(int)((floor(i / 2) + 1) * 2 - ((i % 2) + 1.0))] = c_key / SHORT_SIZE;//�X���̋��-1�`1�Ŋi�[����Atilt�͊i�[����lx�Aly�`�Ƃ����`�Ȃ̂ł���ɍ��킹���Y�����d�l
		short use_tilt_min = X_TILT_MIN * (i % 2) + Y_TILT_MIN * ((i + 1) % 2);//�X�e�B�b�N�X�����m�Œ�l�A������Ȃ�y���g�p�A���x

		for (int j = 0; j < 2; j++) {
			bool use = j == 0 ? c_key <= use_tilt_min * -1 : c_key >= use_tilt_min;//j��0�Ȃ�-�����`�F�b�N�A1�Ȃ�+����
			int sub = key_vol + j + (i % 2) * 2 + floor(i / 2) * 4;//����g�p����Y�����Akey_vol�ŃX�e�B�b�N���͏�Ԃ̔z��ʒu�Ɏ����Ă����Ai%2��xy�ؑցAi/2��LR�ؑցAj��+-�����ؑ�
			if (use) {
				if (hold_time[sub] > 0) { key_state[sub] = KEY_HOLD; }
				else { key_state[sub] = KEY_PUSH; }
				hold_time[sub]++;
				break;//������ɓ��͂��������ꍇ�ȍ~�͎��s���Ȃ�
			}
			//���͂̂Ȃ����������̓��Z�b�g����
			if (hold_time[sub] > 0) { key_state[sub] = KEY_PULL; }
			else { key_state[sub] = KEY_FREE; }
			hold_time[sub] = 0;
		}
	}
}

int KeySystem::GetKeyState(int request) {
	switch (request) {
	case XINPUT_BUTTON_DPAD_UP:return key_state[0]; break;
	case XINPUT_BUTTON_DPAD_DOWN:return key_state[1]; break;
	case XINPUT_BUTTON_DPAD_LEFT:return key_state[2]; break;
	case XINPUT_BUTTON_DPAD_RIGHT:return key_state[3]; break;

	case L_STICK_DOWN:return key_state[12]; break;
	case L_STICK_UP:return key_state[13]; break;
	case L_STICK_LEFT:return key_state[14]; break;
	case L_STICK_RIGHT:return key_state[15]; break;
	case R_STICK_DOWN:return key_state[16]; break;
	case R_STICK_UP:return key_state[17]; break;
	case R_STICK_LEFT:return key_state[18]; break;
	case R_STICK_RIGHT:return key_state[19]; break;
	}
	//�e��{�^���̓R���t�B�O�Ή����l���萔�Ő錾���ĂȂ��̂�switch�����p�ł��Ȃ������ׁAif�ōs��
	if (request == A_KEY) { return key_state[4]; }
	if (request == B_KEY) { return key_state[5]; }
	if (request == X_KEY) { return key_state[6]; }
	if (request == Y_KEY) { return key_state[7]; }
	if (request == L_KEY) { return key_state[8]; }
	if (request == R_KEY) { return key_state[9]; }
	if (request == POUSE_KEY) { return key_state[10]; }
	if (request == SELECT_KEY) { return key_state[11]; }
	return -1;//�����G���[
}
int KeySystem::GetKeyHoldTime(int request) {
	switch (request) {
	case XINPUT_BUTTON_DPAD_UP:return hold_time[0]; break;
	case XINPUT_BUTTON_DPAD_DOWN:return hold_time[1]; break;
	case XINPUT_BUTTON_DPAD_LEFT:return hold_time[2]; break;
	case XINPUT_BUTTON_DPAD_RIGHT:return hold_time[3]; break;

	case L_STICK_DOWN:return key_state[12]; break;
	case L_STICK_UP:return key_state[13]; break;
	case L_STICK_LEFT:return key_state[14]; break;
	case L_STICK_RIGHT:return key_state[15]; break;
	case R_STICK_DOWN:return key_state[16]; break;
	case R_STICK_UP:return key_state[17]; break;
	case R_STICK_LEFT:return key_state[18]; break;
	case R_STICK_RIGHT:return key_state[19]; break;
	}
	//�e��{�^���̓R���t�B�O�Ή����l���萔�Ő錾���ĂȂ��̂�switch�����p�ł��Ȃ������ׁAif�ōs��
	if (request == A_KEY) { return hold_time[4]; }
	if (request == B_KEY) { return hold_time[5]; }
	if (request == X_KEY) { return hold_time[6]; }
	if (request == Y_KEY) { return hold_time[7]; }
	if (request == L_KEY) { return hold_time[8]; }
	if (request == R_KEY) { return hold_time[9]; }
	if (request == POUSE_KEY) { return hold_time[10]; }
	if (request == SELECT_KEY) { return key_state[11]; }
	return -1;//�����G���[
}
