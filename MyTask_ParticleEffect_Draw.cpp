// MyTask_ParticleEffect_Draw.cpp
// MyTask_ParticleEffect�N���X�̕`����L�q����B

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
		// �����ɕ`����e���L���B
		break;
	}
}