#include "DxLib.h"
#include "GameMap.h"
#include "Grid.h"

class GameMap::Staging { //���o�n�A���̃t�@�C���Ɏ�荞�܂Ȃ��̂ŃN���X���ɒ��ڏ�������������ł���
	enum class State; //�O���錾
	using StagingFunc = void (GameMap::Staging::*)(); //�֐��|�C���^��using�錾�A�ȍ~Staging�N���X�̊֐��|�C���^��StagingFunc�Ŏg�p�\

	State state; //���s�̃X�e�[�^�X�ێ�
	GameMap* caller; //�Ăяo�����A�����ʂ���GameMap���̗l�X�Ȋ֐��ɃA�N�Z�X�ł���A�����N���X�Ȃ̂�private�ȗ̈�ɂ����ڃA�N�Z�X�ł���
	StagingFunc func; //���s�֐�
	int count; //���s���ԊǗ��Ƃ���
public:
	enum class State { start, run, end, free }; //���o�̎��s�󋵁Astart=�J�n���� run=���s�� end=�I�������u�� free=�����Ă��Ȃ�

	Staging(GameMap* set) :state(State::free), caller(set), func(Start) {} //�����ɂ͂��̃N���X���g�p����map�̃A�h���X������
	void Start() { //�Q�[���J�n����READY!���̉��o�A���x��1�̎��͉��y������

	}
	void Clear() { //�Q�[���N���A�̎��̉��o

	}
	void Miss() {  //�p�b�N�}�����~�X�������̉��o

	}
	void GameOver() {  //�c�@���Ȃ��Ȃ������̉��o

	}

	//GameMap�Ăяo���֐�
	void AnimeStartUp(StagingFunc set) { //Staging�̊e��public�֐��̃A�h���X�������count��0�AState��start�ɏ������������̊֐������s���Ă����
		//�Ⴆ��Start�A�j�������s�������ꍇ Staging�N���X�̃I�u�W�F�N�g->AnimeStartUp(Staging::Start); �Ŏw��ł���
		func = set;
		count = 0;
		state = State::start;
	}
	State GetRunState() { return state; } //���݂̎��s�󋵂�Ԃ��A�A�j�����I�������u�ԓ�����肽���ꍇ�A�j���̒�`�ŏI�������u��state��end�ɂ���΂����ŕԂ��Ă���l��end�̎��I�������u�Ԃ��Ɣ��f�ł���
	void Update() { //GameMap��Update�Ŗ���Ăяo�����ŃA�j���̎��s���߂��o�Ă���Ԃ͎w��A�j�������s���Ă����
		if (state != State::free) { (this->*func)(); } //State��free�ȊO�̏ꍇ�w�肳�ꂽ���o�̎��s
	}
};

GameMap::GameMap() {
	
}
GameMap::~GameMap() {

}
void GameMap::Draw() {

}
void GameMap::Update() {

}