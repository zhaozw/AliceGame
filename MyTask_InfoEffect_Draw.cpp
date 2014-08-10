// MyTask_InfoEffect_Draw.cpp
// MyTask_InfoEffectクラスの描画を記述する。

#include "Static_InfoEffect.h"
#include "MyTask_InfoEffect.h"
#include <DxLib.h>
#include "DXFont.h"
#include "Func_Math.h"
#include "Image.h"
#include "Func_Graphics.h"

extern DXFont	g_font;
extern Image	g_image;

#define INFOEFFECT_STRSIZE		32

void MyTask_InfoEffect::Draw() const{
	TCHAR str[INFOEFFECT_STRSIZE];
	float f;
	int w;
	int a = 255;
	switch(typeID){
	case INFO_DAMAGENUM_ENEMY:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_m,
			NUM_DAMAGE_M_WIDTH-8, 4, 1, false, false);
		break;
	case INFO_DAMAGENUM_ENEMY_STRONG:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_l,
			NUM_DAMAGE_L_WIDTH-12, 4, 1, false, false);
		break;
	case INFO_DAMAGENUM_ENEMY_RESIST:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_s,
			NUM_DAMAGE_S_WIDTH-8, 4, 1, false, false);
		break;
	case INFO_DAMAGENUM_DOLL:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_m,
			NUM_DAMAGE_M_WIDTH-8, 4, 1, false, false);
		break;
	case INFO_DAMAGENUM_DOLL_STRONG:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_l,
			NUM_DAMAGE_L_WIDTH-12, 4, 1, false, false);
		break;
	case INFO_DAMAGENUM_DOLL_RESIST:
		a = PARAM(12*(GetLifeTime()-existTime));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		f = min(0, 0.4*existTime*(existTime-20));
		DrawNum(param, x, y+f,
			g_image.chars.num_damage_s,
			NUM_DAMAGE_S_WIDTH-8, 4, 1, false, false);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}