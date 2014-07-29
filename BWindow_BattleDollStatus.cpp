// BWindow_BattleDollStatus.cpp

#include "BWindow_BattleDollStatus.h"
#include "Scene_Battle.h"

BWindow_BattleDollStatus::BWindow_BattleDollStatus() : Window_SimpleDollStatus(){
}

void BWindow_BattleDollStatus::Setup(Scene_Battle* _pScene){
	Window_SimpleDollStatus::Setup(DRAWPTN_ALLSTATUS, true);
	pScene = _pScene;
}

void BWindow_BattleDollStatus::Update(){
	switch(state){
	case UPDATING:
		if(CheckClose()){
			Close(true, false);
			pScene->ResetInfoWindowID();
		}
	}
	Window_SimpleDollStatus::Update();
}
