// Sprite_Base_Morph.cpp

#include "Sprite_Base.h"
#include "Func_Math.h"

#define SPMORPH_ACTIVATE_TIME	12
#define SPMORPH_ACTIVATE_VY		20


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
		// param = ì_ñ≈ÇµÇƒÇ¢ÇÈéûä‘
		morphSkipTime = p;
		morphTime = p;
		param.param = p;
		break;
	}

	if(morphTime == 0){
		// morphTimeÇ™ë„ì¸Ç≥ÇÍÇΩÇ©Ç«Ç§Ç©Çê¨å˜ÇÃîªífÇ∆Ç∑ÇÈ
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
	}
	return;
}
