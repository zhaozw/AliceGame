// Game_BattleUnit.cpp

#include "Game_BattleUnit.h"
#include "Static_AliceDoll.h"
#include <tchar.h>

Game_BattleUnit::Game_BattleUnit(){
	Reset();
}

void Game_BattleUnit::Reset(int n){
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _T(""));
	for(int index=0; index<BATTLEUNIT_PARAM_NUM; index++){
		param[index] = 0;
	}
	attr = DOLL_ATTR_NONE;
	isFront = true;
	position = n;
}

bool Game_BattleUnit::CanTarget(){
	// ‰¼B
	return true;
}

int Game_BattleUnit::GetRawParam(BYTE index){
	if(index >= BATTLEUNIT_PARAM_NUM){
		return BATTLEUNIT_PARAM_ERROR;
	}
	return param[index];
}

int Game_BattleUnit::GetCalcParam(BYTE index){
	if(index >= BATTLEUNIT_PARAM_NUM){
		return BATTLEUNIT_PARAM_ERROR;
	}
	return param[index];
}

bool Game_BattleUnit::SetName(LPTSTR _name, int nameLength){
	// if(nameLength == -1) nameLength = strlen(name);
	// if(nameLength > BATTLEUNIT_NAME_BYTES-1) return false;
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _name);
	return true;
}

void Game_BattleUnit::GetName(LPTSTR buf, int bufSize){
	if(bufSize < BATTLEUNIT_NAME_BYTES) return;
	strcpy_s(buf, BATTLEUNIT_NAME_BYTES-1, name);
}

void Game_BattleUnit::SetParam(
	int hp, int maxHP, int atk, int def, int spd, int mgc, int tec){
		SetHP(hp);
		SetMaxHP(maxHP);
		SetAtk(atk);
		SetDef(def);
		SetSpd(spd);
		SetMgc(mgc);
		SetTec(tec);
}
