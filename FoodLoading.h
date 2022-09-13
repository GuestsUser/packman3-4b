#pragma once

//基本的なことはMapLoadingと同様、Loadingによりステージ間で使いまわすエサを作成する

void FoodLoading(); //エサやフルーツの作成処理
void FoodDel(); //削除処理
void FoodIni(); //エサやフルーツの初期化処理、新しいステージに移行する若しくは新しくゲームを始める場合毎回呼び出すこと、この関数はステージ数のWorldValを新しくしてから呼び出す必要あり