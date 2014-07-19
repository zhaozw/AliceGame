// MyTask_ParticleEffect_Draw.cpp
// MyTask_ParticleEffectクラスの描画を記述する。

#include "Static_ParticleEffect.h"
#include "MyTask_ParticleEffect.h"
#include <DxLib.h>
#include "DXFont.h"
#include "Func_Math.h"

extern DXFont	g_font;

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
	}
}