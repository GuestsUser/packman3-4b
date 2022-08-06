#pragma once

class Scene { //���̃N���X���p�����ăV�[��������Update�ɁA�`�ʏ�����Draw�ɒ�`����
	Scene* next; //�V�[���J�ڂ���ꍇ���V�[�����́A���̂܂܂̏ꍇ���g�A�E�B���h�E�����ꍇnullptr������
public:
	Scene() :next(this) {} //���������Ɏ��g�����Ă���
	virtual ~Scene() {} //�p���\�ȃN���X�̓f�X�g���N�^�ɉ��z�֐��w�肪�Ȃ��Ɛe�N���X�̃f�X�g���N�^�����Ăяo����Ȃ��̂�virtual�w������Ă���
	
	virtual void Update() = 0; //���t���[�����s���鏈���֐��A�����K�{
	virtual void Draw() {} //���t���[�����s����`�ʊ֐�

	bool SetNext(Scene* set){ //�V�[���`�F���W�p�A�����Ɏ��V�[���̎��̂�����
		if (next != this) { return false; } //���Ɏ��V�[���̎w�肪�Ȃ���Ă���ꍇ���s
		next = set; //���V�[����ݒ�
		return true; //������Ԃ�
	}
	Scene* GetNext() { return next; } //���V�[���̎擾
};