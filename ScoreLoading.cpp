#include "ScoreLoading.h"
#include "Worldval.h"
#include "ConstVal.h"

void ScoreLoading() { //�X�R�A�A�n�C�X�R�A�Ɏg���ϐ��̏���
	WorldVal::Set("score", new int(0));
	WorldVal::Set("highScore", new int(HIGH_SCORE_INI));
}
void ScoreDel() { //�X�R�A�A�n�C�X�R�A�p�ϐ��̍폜
	delete WorldVal::Get<int>("score");
	delete WorldVal::Get<int>("highScore");
}