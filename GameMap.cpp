#include "DxLib.h"
#include "Game.h"
#include "Scene.h"
#include "GameMap.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "Food.h"
#include <unordered_map>
#include <string>
#include "Title.h"
#include "Player.h"

class GameMap::Staging { //���o�n�A���̃t�@�C���Ɏ�荞�܂Ȃ��̂ŃN���X���ɒ��ڏ�������������ł���
public:
	enum class State { start, run, end, free }; //���o�̎��s�󋵁Astart=�J�n���� run=���s�� end=�I�������u�� free=�����Ă��Ȃ�
private:
	using StagingFunc = void (GameMap::Staging::*)(); //�֐��|�C���^��using�錾�A�ȍ~Staging�N���X�̊֐��|�C���^��StagingFunc�Ŏg�p�\

	State state; //���s�̃X�e�[�^�X�ێ�
	GameMap* caller; //�Ăяo�����A�����ʂ���GameMap���̗l�X�Ȋ֐��ɃA�N�Z�X�ł���A�����N���X�Ȃ̂�private�ȗ̈�ɂ����ڃA�N�Z�X�ł���
	StagingFunc func; //���s�֐�
	int count; //���s���ԊǗ��Ƃ���
	int startImage1;	//Player One�摜�p
	int startImage2;	//Ready!�摜�p
	int clearImage1;	//�N���A�摜�i���j
	int clearImage2;	//�N���A�摜�i�j
	int gameOverImage;	//�Q�[���I�[�o�[�摜
public:
	//�����ɂ͂��̃N���X���g�p����map�̃A�h���X������
	Staging(GameMap* set) :state(State::free), caller(set), func(nullptr), count(0), 
		startImage1(*WorldVal::Get<int>("playerOneImage")), startImage2(*WorldVal::Get<int>("readyImage")),
		clearImage1(*WorldVal::Get<int>("clearImage1")), clearImage2(*WorldVal::Get<int>("clearImage2")),
		gameOverImage(*WorldVal::Get<int>("gameOverImage")){}

	void Start() { //�Q�[���J�n����READY!���̉��o�A���x��1�̎��͉��y������
		if (count <= 120) {
			//Player one�\��
			DrawRotaGraph3(SHIFT_X + 149, SHIFT_Y + 176, 0, 0, X_RATE, Y_RATE, 0, startImage1, TRUE, FALSE);
		}
		if (count <= 240) {
			//Ready!�\��
			DrawRotaGraph3(SHIFT_X + 176, SHIFT_Y + 272, 0, 0, X_RATE, Y_RATE, 0, startImage2, TRUE, FALSE);
		}
		else {
			state = State::free; //�A�j����Ԃ��I���ς݂ɏ���������
			Game::SetSceneState(Game::State::run); //���o���I���������ԂŃQ�[���V�[���̏�Ԃ��Q�[�����ɕύX����
		}
		count++;
	}

	void Clear() { //�Q�[���N���A�̎��̉��o
		if ((count / 12) % 2 == 0) {
			//���摜
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage1, TRUE, FALSE);
		}
		else {
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage2, TRUE, FALSE);
		}
		//4��_�ł�����i1��̓_�ł�24count�j
		if (count >= 95) {
			state = State::free;	//�A�j����Ԃ��I���ς݂ɏ���������
			caller->parent->SetNext(new Title());
		}
		count++;
	}

	void Miss() {  //�p�b�N�}�����~�X�������̉��o
		caller->player->DieAnim();
	}

	void GameOver() {  //�c�@���Ȃ��Ȃ������̉��o
		if (count <= 180) {
			DrawRotaGraph3(SHIFT_X + 149, SHIFT_Y + 176, 0, 0, X_RATE, Y_RATE, 0, startImage1, TRUE, FALSE);
			DrawRotaGraph3(SHIFT_X + 145, SHIFT_Y + 273, 0, 0, X_RATE, Y_RATE, 0, gameOverImage, TRUE, FALSE);
		}
		if (count == 180) {
			//�V�[�������̃X�e�[�W�ɂ���i�����E���h�j
			//���̓^�C�g���ɖ߂�悤�ɂ���
			caller->parent->SetNext(new Title());
		}
		count++;
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

GameMap::GameMap(Scene* set,Player* pacman) :staging(new Staging(this)), tile(WorldVal::Get<Grid*>("map")), map(*WorldVal::Get<int>("mapImage")),food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), parent(set),player(pacman) {
	staging->AnimeStartUp(&Staging::Miss);
}
GameMap::~GameMap() {
	delete staging; //������Ő����������̂̍폜
}
void GameMap::Draw() {
	//map�摜�̕`��������ɋL��
	DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, map, TRUE, FALSE);
	staging->Update(); //�A�j���̏����ƕ`�ʂ��s��
	for (auto itr : *food) { itr.second->Draw(); } //�H�ו��`��
}
void GameMap::Update() {

}