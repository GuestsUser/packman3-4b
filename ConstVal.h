#pragma once
constexpr float PI = 3.141592653589793; //円周率
constexpr int FPS = 60; //1秒でUpdateを実行する回数
constexpr int WINDOW_X = 1280;
constexpr int WINDOW_Y = 720;

constexpr int TILE = 8; //このドット数で1マス

constexpr int SHIFT_X = 192; //ゲーム画面の描写をこの数値分ずらす
constexpr int SHIFT_Y = 112; //上記のy版

constexpr int X_RATE = 2; //xの拡大倍率
constexpr int Y_RATE = 2; //yの拡大倍率

constexpr int AREA_X = 28; //xマス数
constexpr int AREA_Y = 31; //yマス数
constexpr int WARP_AREA_X = 4; //ワープトンネルのサイズx
constexpr int WARP_AREA_Y = 0; //上記のy版

constexpr int MOVABLE_SPEED = 16; //1ドット進む為に必要な速度

constexpr int HIGH_SCORE_INI = 10000; //ハイスコア初期値
constexpr int EXTEND_QUOTA = 70; //残機アップに必要なスコア
constexpr int EXTEND_LIMIT = 1; //残機アップ可能回数
constexpr int INI_LIFE = 3; //残機初期