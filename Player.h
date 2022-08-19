#pragma once
#include <unordered_map>
#include <string>

class Grid;
class Food;

class Player {
	int* playerImg; //�p�b�N�}���摜�n���h��
	int* killImg; //���S���[�V����
	bool isUpdate; //false��update���s�֎~
	bool isDraw; //��L��draw��
	int subX, subY, drawX, drawY; //�O���b�h�̓Y�����ƕ`�ʗp���W�A�`�ʗp���W�͊g�嗦��K�p���Ă��Ȃ��ADraw�̕��œK�p����
	int speedCount; //���x�̒~�Ϗ󋵋L�^�A���t���[�������speed�����Z���AspeedCount/MOVABLE_SPEED�̒l���`�ʍ��W�𓮂���

	int foodCount; //����̎c�@�ŐH�ׂ��G�T��
	int foodCountTotal; //�G�T��H�ׂ����v��
	std::unordered_map<std::string, Food*>* food; //�G�T��t���[�c�̔z��
	Grid** tile;

	//�����ʒu x14+4(���[�v�g���l����) y23

public:
	Player();

	void Update();
	void Draw();

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }
};