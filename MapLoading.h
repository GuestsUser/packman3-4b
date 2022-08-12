#pragma once

//mainとかにインクルードしてメインループ突入前にMapLoadingを呼び出す
//この配列は相当な要素数なのでステージ毎に作ったり消したりすると重くなると思ったのでmainで予め確保する方法を取る

void MapLoading(); //マップの作成処理
void MapDel(); //マップ削除