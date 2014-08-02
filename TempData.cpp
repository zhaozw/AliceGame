// TempData.cpp

#include "TempData.h"

TempData::TempData() : dollData(){
	sceneParam = 0;
	fileIndex = 0;
	battleType = TEMP_BTYPE_NORMAL;
	battleID = 0;
	enemyGroup = 0;
	Reset();
}

void TempData::Reset(){
	sceneParam = 0;
	for(int n=0; n<MAX_ENTERNAME; n++){
		enteredName[n] = 0;
	}
	battleType = 0;
	battleID = 0;
	enemyGroup = 0;
	dollData = Game_AliceDoll_Essence();
}