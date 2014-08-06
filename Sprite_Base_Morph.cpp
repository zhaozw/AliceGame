// Sprite_Base_Morph.cpp

#include "Sprite_Base.h"
#include "Func_Math.h"

#define SPMORPH_ACTIVATE_TIME			12
#define SPMORPH_ACTIVATE_VY				20
#define SPMORPH_DAMAGE_DOLL_TIME		30
#define SPMORPH_DAMAGE_DOLL_SKIPTIME	15
#define SPMORPH_ENEMYATTACK_TIME		40
#define SPMORPH_ENEMYATTACK_SKIPTIME	20

bool Sprite_Base::SetMorphID(BYTE id, bool force, int p){
	if(!force && GetMorphing()){
		return false;
	}
	ResetMorph();
	morphID = id;
	switch(morphID){
	case SPMORPH_NONE:
		break;
	case SPMORPH_DISAPPEAR:
		morphSkipTime = p;
		morphTime = p;
		param.param = p;
		break;
	case SPMORPH_ACTIVATE:
		morphSkipTime = SPMORPH_ACTIVATE_TIME;
		morphTime = SPMORPH_ACTIVATE_TIME;
		break;
	case SPMORPH_DISACTIVATE:
		morphSkipTime = SPMORPH_ACTIVATE_TIME;
		morphTime = SPMORPH_ACTIVATE_TIME;
		break;
	case SPMORPH_BLINK:
		// param = 点滅している時間
		morphSkipTime = p;
		morphTime = p;
		param.param = p;
		break;
	case SPMORPH_ENEMYATTACK:
		// param = 使用しない
		morphSkipTime = SPMORPH_ENEMYATTACK_TIME;
		morphTime = SPMORPH_ENEMYATTACK_SKIPTIME;
		break;
	case SPMORPH_DAMAGE_DOLL:
		morphSkipTime = SPMORPH_DAMAGE_DOLL_SKIPTIME;
		morphTime = SPMORPH_DAMAGE_DOLL_TIME;
		break;
	}

	if(morphTime == 0){
		// morphTimeが代入されたかどうかを成功の判断とする
		ResetMorph();
		return false;
	}
	return true;
}

void Sprite_Base::UpdateMorph(){
	switch(morphID){
	case SPMORPH_NONE:
		break;
	case SPMORPH_DISAPPEAR:
		if(morphCount < morphTime){
			param.opacity = (int)PARAM(GetMorphRestRate()*255.0);
		}else{
			param.opacity = 255;
			visible = false;
		}
		break;
	case SPMORPH_ACTIVATE:
		param.dy = -SPMORPH_ACTIVATE_VY*GetMorphRate();
		break;
	case SPMORPH_DISACTIVATE:
		param.dy = -SPMORPH_ACTIVATE_VY*GetMorphRestRate();
		break;
	case SPMORPH_BLINK:
		if(morphCount < morphTime){
			param.hide = true;
		}else{
			param.hide = false;
		}
		break;
	case SPMORPH_ENEMYATTACK:
		if(morphCount < morphTime){
            float rate = min(1.0f,GetMorphRate());
            float div = 2.0f; // 演出の回数　好きな数に
            float d = 1.0f / div;
            float nd = fmodf(rate , d);
            
            rate = nd * div;

            param.param = (int)PARAM(rate*255.0f);
            param.dy = PARAM(rate*8.0f); // yの増加分は好きな数値に
		}else{
            param.dy = 0;
            param.param = 0;
		}
		break;
	}
	return;
}
