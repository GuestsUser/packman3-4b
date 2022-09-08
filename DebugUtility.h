#pragma once

void DrawHitBox(int tileX, int tileY, unsigned int color); //tileX,tileYにマス座標を渡すとその位置に当たり判定を描写してくれる
void DrawTargetLine(int tX1, int tY1, int tX2, int tY2, unsigned int color); //t1からt2へラインを描写する(t1,t2はどちらもマス座標)