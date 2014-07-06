// Game_AliceDoll.cpp

#include <math.h>
#include "Game_AliceDoll.h"

DWORD Game_AliceDoll_Essence::dataSize=sizeof(Game_AliceDoll_Essence_Data);

Game_AliceDoll_Essence::Game_AliceDoll_Essence(){
	data.type = DOLL_TYPE_UNDIFINED;
	data.level = 1;
	data.exp = 0;
	data.serial = 0;
	for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
		data.attrStone[n] = DOLL_ATTR_NONE;
	}
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		data.paramLevel[n].growth = 0;
		data.paramLevel[n].potential = 0;
	}
}

Game_AliceDoll_Essence::~Game_AliceDoll_Essence(){
}

Game_AliceDoll_Essence::Game_AliceDoll_Essence(const Game_AliceDoll_Essence& i){
	data.type = i.data.type;
	data.level = i.data.level;
	data.exp = i.data.exp;
	data.serial = i.data.serial;
	for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
		data.attrStone[n] = i.data.attrStone[n];
	}
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		data.paramLevel[n].growth = i.data.paramLevel[n].growth;
		data.paramLevel[n].potential = i.data.paramLevel[n].potential;
	}
}

Game_AliceDoll_Essence &Game_AliceDoll_Essence::operator=(const Game_AliceDoll_Essence &i){
	data.type = i.data.type;
	data.level = i.data.level;
	data.exp = i.data.exp;
	data.serial = i.data.serial;
	for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
		data.attrStone[n] = i.data.attrStone[n];
	}
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		data.paramLevel[n].growth = i.data.paramLevel[n].growth;
		data.paramLevel[n].potential = i.data.paramLevel[n].potential;
	}
	return(*this);
}


DWORD Game_AliceDoll_Essence::GetGLevel(BYTE paramID) const{
	DWORD gLevel = 
		data.paramLevel[paramID].potential 
		+ data.paramLevel[paramID].growth 
		+ data.level*DOLL_LEVEL_FACTOR;
	return min(gLevel, DOLL_GLOBALLEVEL_MAX);
}

DWORD Game_AliceDoll_Essence::GetGeneralGLevel() const{
	return 0;
}

BYTE Game_AliceDoll_Essence::GetAttr() const{
	// 一番多いattrStoneの種類IDを返す。
	// 同じものが同数ある場合はDOLL_ATTR_NONEを返す。

	// 各石の数をカウント
	BYTE sNum[DOLL_ATTR_NUM-1] = {0, 0, 0};
	for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
		sNum[data.attrStone[n]-1]++;
	}
	// 石の数の最大数を調べる
	int max = 0;
	for(int n=0; n<DOLL_ATTR_NUM-1; n++){
		max = max(max, sNum[n]);
	}
	// 最大数の属性を取得する。
	// 複数あった場合はDOLL_ATTR_NONEを返す。
	BYTE result = DOLL_ATTR_NONE;
	for(int n=0; n<DOLL_ATTR_NUM-1; n++){
		if(sNum[n] == max){
			if(result == DOLL_ATTR_NONE){
				result = n+1;
			}else{
				// 複数属性が最大個数だった場合
				return DOLL_ATTR_NONE;
			}
		}
	}
	// 複数属性が最大個数の条件を満たさなかった場合、
	// 最大数であった属性を返す。
	return result;
}

bool Game_AliceDoll_Essence::ConvertDataToBytes(LPBYTE p, DWORD size){
	if(size != sizeof(Game_AliceDoll_Essence)) return false;
	if(memcpy_s((void*)p, size, (void*)&data, size) != 0){
		return false;
	}
	return true;
}

bool Game_AliceDoll_Essence::ConvertBytesToData(LPBYTE p, DWORD size){
	if(size != sizeof(Game_AliceDoll_Essence)) return false;
	if(memcpy_s((void*)&data, size, (void*)p, size) != 0){
		return false;
	}
	return true;
}
