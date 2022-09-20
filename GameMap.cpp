#include "DxLib.h"
#include "Game.h"
#include "Scene.h"
#include "GameMap.h"
#include "ConstVal.h"
#include "Grid.h"
#include "Worldval.h"
#include "Food.h"
#include "FoodLoading.h"
#include "Title.h"
#include "EnemyAra.h"
#include "Player.h"
#include <unordered_map>
#include <string>
#include <deque>
#include "CoffeeBreak.h"

class GameMap::Staging { //���o�n�A���̃t�@�C���Ɏ�荞�܂Ȃ��̂ŃN���X���ɒ��ڏ�������������ł���
public:
	enum class State { start, run, end, free }; //���o�̎��s�󋵁Astart=�J�n���� run=���s�� end=�I�������u�� free=�����Ă��Ȃ�
private:
	using StagingFunc = void (GameMap::Staging::*)(); //�֐��|�C���^��using�錾�A�ȍ~Staging�N���X�̊֐��|�C���^��StagingFunc�Ŏg�p�\

	State state; //���s�̃X�e�[�^�X�ێ�
	GameMap* caller; //�Ăяo�����A�����ʂ���GameMap���̗l�X�Ȋ֐��ɃA�N�Z�X�ł���A�����N���X�Ȃ̂�private�ȗ̈�ɂ����ڃA�N�Z�X�ł���
	StagingFunc func; //���s�֐�
	int count; //���s���ԊǗ��Ƃ���
	int i;
	int startImage1;	//Player One�摜�p
	int startImage2;	//Ready!�摜�p
	int clearImage1;	//�N���A�摜�i���j
	int clearImage2;	//�N���A�摜�i�j
	int gameOverImage;	//�Q�[���I�[�o�[�摜
	int startBGM;       //�Q�[���X�^�[�g���̉�
	int extendSE;		//�c�@Up��

public:
	//�����ɂ͂��̃N���X���g�p����map�̃A�h���X������
	Staging(GameMap* set) :state(State::free), caller(set), func(nullptr), count(0), 
		startImage1(*WorldVal::Get<int>("playerOneImage")), startImage2(*WorldVal::Get<int>("readyImage")),
		clearImage1(*WorldVal::Get<int>("clearImage1")), clearImage2(*WorldVal::Get<int>("clearImage2")),
		gameOverImage(*WorldVal::Get<int>("gameOverImage")),startBGM(*WorldVal::Get<int>("startBGM")),
		extendSE(*WorldVal::Get<int>("extendSE")){}

	void Start() { //�Q�[���J�n����READY!���̉��o�A���x��1�̎��͉��y������
		int* life;
		life = WorldVal::Get<int>("Life");
		std::deque<EnemyAra*>* enemy = caller->parent->EditEnemy();

		if (state == State::start) {
			caller->parent->EditPlayer()->SetRunUpdate(false);
			caller->parent->EditPlayer()->SetRunDraw(false);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(false);
				(*enemy)[i]->SetRunDraw(false);

			}
			state = State::run;
		}
		int* start;
		start = WorldVal::Get<int>("start");
		if (*start<=0) {
			PlaySoundMem(startBGM, DX_PLAYTYPE_BACK, TRUE);
		}
		if (*start >= 1 && count == 0) {
			count = 121;
		}
		if(count ==120){ *life -= 1;}
		if (count == 121)
		{
			
			caller->parent->EditPlayer()->SetRunDraw(true);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunDraw(true);
			}
		}
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
			caller->parent->EditPlayer()->SetRunUpdate(true);
			for (i = 0; i < enemy->size(); ++i) {
				(*enemy)[i]->SetRunUpdate(true);
			}
			caller->sound->SetSEUpdate(true);
		}

		count++;
		*start += 1;
	}

	void Clear() { //�Q�[���N���A�̎��̉��o
		caller->sound->isUpdate = false;
		(*caller->enemy)[0]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[1]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[2]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[3]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		caller->player->SetRunUpdate(false);	/*Player�̓������~�߂�*/

		if (count >= 120) {
			(*caller->enemy)[0]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[1]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[2]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[3]->SetRunDraw(false);/*�G�̕`�������*/
		}
		if (count >= 120 && (count / 12) % 2 == 0) {
			int* dieCount = WorldVal::Get<int>("dieCount");
			*dieCount = 0;
			int* activeFoodCount = WorldVal::Get<int>("activeFoodCount");
			*activeFoodCount = 0;
			int* enemyActive = WorldVal::Get<int>("enemyActive");
			*enemyActive = 0;
		}

		if ((count / 12) % 2 == 0) {
			//���摜
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage1, TRUE, FALSE);
		}
		else {
			DrawRotaGraph3(SHIFT_X, SHIFT_Y, 0, 0, X_RATE, Y_RATE, 0, clearImage2, TRUE, FALSE);
		}
		//4��_�ł�����95�i1��̓_�ł�24count�j
		if (count >= 215) {
			state = State::free;	//�A�j����Ԃ��I���ς݂ɏ���������

			*WorldVal::Get<int>("nowStage") += 1; //���X�e�[�W�ɃJ�E���g��i�߂�
			FoodIni(); //�G�T��Ԃ̏�����
			caller->parent->SetNext(new CoffeeBreak()); //���X�e�[�W�Ɉڍs
		}
		count++;
	}

	void Miss() {  //�p�b�N�}�����~�X�������̉��o
		caller->sound->StopSound();
		//StopSoundMem(caller->sound->cringeSE);
		StopSoundMem(caller->sound->damageSE);
		caller->sound->isUpdate = false;
		StopSoundMem(extendSE);

		int* dieCount;
		dieCount = WorldVal::Get<int>("dieCount");
		*dieCount += 1;

		int* life;
		life = WorldVal::Get<int>("Life");

		int* enemyActive;
		enemyActive = WorldVal::Get<int>("enemyActive");
		*enemyActive = 0;

		int* activeFoodCount;
		activeFoodCount = WorldVal::Get<int>("activeFoodCount");
		*activeFoodCount = 0;
		(*caller->enemy)[0]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[1]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[2]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		(*caller->enemy)[3]->SetRunUpdate(false);	/*�G�̓������~�߂�i���j*/
		caller->player->SetRunUpdate(false);	/*Player�̓������~�߂�*/

		if (count >= 60) {
			(*caller->enemy)[0]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[1]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[2]->SetRunDraw(false);/*�G�̕`�������*/
			(*caller->enemy)[3]->SetRunDraw(false);/*�G�̕`�������*/
			caller->player->DieAnim();
		}

		if (*life >= 1) {
			if (count >= 240) {
				*life -= 1;
				(*caller->food)["17x17"]->SetEnable(false);
				caller->parent->SetNext(new Game());
			}
		}
		else if (*life <= 0) {
			if (count >= 240) {
				AnimeStartUp(&Staging::GameOver);
			}
		}
		count++;
	}

	void Restart() {
		/*number++;
		if (number >= 120) {
			caller->parent->SetNext(new Game());
		}*/
	}
		
	void GameOver() {  //�c�@���Ȃ��Ȃ�����3�̉��o
		int* dieCount;
		dieCount = WorldVal::Get<int>("dieCount");
		*dieCount = 0;
		int* activeFoodCount;
		activeFoodCount = WorldVal::Get<int>("activeFoodCount");
		*activeFoodCount = 0;
		int* enemyActive;
		enemyActive = WorldVal::Get<int>("enemyActive");
		*enemyActive = 0;
		if (count <= 180) {

			DrawRotaGraph3(SHIFT_X + 149, SHIFT_Y + 176, 0, 0, X_RATE, Y_RATE, 0, startImage1, TRUE, FALSE);
			DrawRotaGraph3(SHIFT_X + 145, SHIFT_Y + 273, 0, 0, X_RATE, Y_RATE, 0, gameOverImage, TRUE, FALSE);
		}
		if (count == 180) {
			//�e�평����
			*WorldVal::Get<int>("Life") = INI_LIFE;
			*WorldVal::Get<int>("nowStage") = 0;
			*WorldVal::Get<int>("start") = 0;
			FoodIni();

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

GameMap::GameMap(Game* set,Player* pacman, std::deque<EnemyAra*>* getEnemy,Sound* se) :staging(new Staging(this)), tile(WorldVal::Get<Grid*>("map")), map(*WorldVal::Get<int>("mapImage")),food(WorldVal::Get<std::unordered_map<std::string, Food*>>("food")), parent(set),player(pacman),enemy(getEnemy),sound(se) {
	staging->AnimeStartUp(&Staging::Start);
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
	for (auto itr : *food) { itr.second->Update(); } //�H�ו��������s

	if (staging->GetRunState() != Staging::State::free) { return; } //���o�n�������s�̏ꍇ�����ȍ~�����s
	switch (Game::GetSceneState()) {
	case Game::State::start:
			break;
	case Game::State::miss:
		staging->AnimeStartUp(&Staging::Miss);
		Game::SetSceneState(Game::State::run);
		break;
	case Game::State::clear:
		staging->AnimeStartUp(&Staging::Clear);
	}
}