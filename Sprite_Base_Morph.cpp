// Sprite_Base_Morph.cpp

#include "Sprite_Base.h"

bool Sprite_Base::SetMorphID(BYTE id, bool force, int p){
	if(!force && GetMorphing()){
		return false;
	}
	ResetMorph();
	morphID = id;
	switch(morphID){
	case SPMORPH_NONE:
		break;
	}

	if(morphTime == 0){
		// morphTime‚ª‘ã“ü‚³‚ê‚½‚©‚Ç‚¤‚©‚ğ¬Œ÷‚Ì”»’f‚Æ‚·‚é
		ResetMorph();
		return false;
	}
	return true;
}

void Sprite_Base::UpdateMorph(){
	switch(morphID){
	case SPMORPH_NONE:
		break;
	}
	return;
}
