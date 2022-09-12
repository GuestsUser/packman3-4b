#pragma once
#include "GetKey.h"
#include <algorithm>
#include <array>


class GameUi{
public:
    GameUi();
    ~GameUi();
    void UiUpdate();
    void UiDraw();
    void hiscoreDraw();
    void scoreDraw();
    void pacmanUiDraw();//�p�b�N�}���c�@
    void fruitUiDraw();//�X�e�[�W�ʕ�
    int* score;      
    int* hiscore;
    int* zanki ;//�p�b�N�}���̎c�@��(���j
    int scorecount; //1up���_�ł���J�E���g
    int round=1;  //���E���h
    int count;
    
private:
    
    
    //�ʕ��摜�i�[�p�ϐ�
    int fruitImage[10];

    //�p�b�N�}���c�@�摜�i�[�p�ϐ�
    int pacmanImage[12];

    int hiscoreImage;
    int scoreImage;
    std::array<int, 20 > roundfruit{ 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9 };
};

