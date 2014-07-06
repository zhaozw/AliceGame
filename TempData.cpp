// TempData.cpp

#include "TempData.h"

TempData::TempData(){
	fileIndex = 0;
	Reset();
}

void TempData::Reset(){
	sceneParam = 0;
	for(int n=0; n<MAX_ENTERNAME; n++){
		enteredName[n] = 0;
	}
	enemyGroup = 0;
	dollData = Game_AliceDoll_Essence();
}