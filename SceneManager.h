#pragma once
class Scene;

class SceneManager { //�V�[���Ǘ��p�N���X�A���C���Ɉ�����Update��Draw���Ăяo�����Ŏg�p����
	Scene* run; //���s����V�[�����̂������Ă���
public:
	SceneManager(Scene* ini) :run(ini) {} //�ŏ��ɓǂݍ��݂����V�[���̃C���X�^���X�������ɓ����
	//~SceneManager();

	bool Update(); //���s����V�[���̏��������s����A�E�B���h�E�����ꍇ�Ԃ�l��false�ɂȂ�
	void Draw(); //���s�V�[���̕`�ʂ��s��
};