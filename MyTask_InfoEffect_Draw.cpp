// MyTask_InfoEffect_Draw.cpp
// MyTask_InfoEffectクラスの描画を記述する。

#include "Static_InfoEffect.h"
#include "MyTask_InfoEffect.h"
#include <DxLib.h>
#include "DXFont.h"
#include "Func_Math.h"

extern DXFont	g_font;

#define INFOEFFECT_STRSIZE		32
void MyTask_InfoEffect::Draw() const{
	TCHAR str[INFOEFFECT_STRSIZE];
	float f;
	int a = 255;
	switch(typeID){
	case INFO_DAMAGENUM_ENEMY:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		wsprintf(str, "%d", param);
		DrawStringToHandle(x, 
			y + f - FONTSIZE_INFO,
			str, GetColor(255, 255, 255),
			g_font.hStrL);
		break;
	}
}