// MyTask_ParticleEffect_Draw.cpp
// MyTask_ParticleEffectクラスの描画を記述する。

#include "Static_ParticleEffect.h"
#include "MyTask_ParticleEffect.h"
#include <DxLib.h>
#include "DXFont.h"
#include "Func_Math.h"
#include "Image.h"

extern DXFont	g_font;
extern Image	g_image;

#define INFOEFFECT_STRSIZE		32

void MyTask_ParticleEffect::Draw() const{
	TCHAR str[INFOEFFECT_STRSIZE];
	float f;
	int w;
	int a = 255;
	switch(typeID){
	case PARTICLE_DUMMY:
		// ここに描画内容を記す。
		break;
	case PARTICLE_SIGN_DAMAGE_WEAK:
	case PARTICLE_SIGN_DAMAGE_RESIST:
		a = max(0, min(255, min(32*GetExistTime(), 8*GetRestTime())));
		f = 0.8+0.3*GetExistRate();
		if(typeID == PARTICLE_SIGN_DAMAGE_RESIST){
			f *= 0.8;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawRotaGraph(x, y, f, 0, 
			g_image.chars.sign_damage[typeID - PARTICLE_SIGN_DAMAGE_WEAK],
			1);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}