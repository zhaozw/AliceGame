// Record_ChooseMap.cpp

#include "Record_ChooseMap.h"
#include "Data_ChooseMap.h"

extern Data_ChooseMap		d_chooseMap;

Record_ChooseMap::Record_ChooseMap() : data(){
}

bool Record_ChooseMap::Initialize(){
	// いわゆる「1-1」を開く
	data.stageOfArea[1] = 1;
	return true;
}


bool Record_ChooseMap::LoadFromBytes(LPVOID pBytes, DWORD fileSize){
	if(fileSize != sizeof(data)){
		return false;
	}
	if(memcpy_s((void*)&data, fileSize, (void*)pBytes, fileSize) != 0){
		return false;
	}
	return true;
}


WORD Record_ChooseMap::CheckPathOpen(BYTE chapter){
	WORD tmp;
	int num = 0;
	for(WORD n=1; n<CHOOSEMAP_PATH_MAX; n++){
		// 判定対象は、現在閉じているパスに限る。
		if(GetPathState(n) == CHOOSEMAP_PATHSTATE_NONE){
			num = 0;
			for(int i=0; i<CHOOSEMAP_PATH_CONDITION_AREA_MAX; i++){
				tmp = d_chooseMap.GetAreaToOpenPath(n, i, chapter);
				if(tmp != 0){
					if(GetAreaIsCleared(chapter, tmp)){
						num++;
					}
				}
			}
			if(num >= d_chooseMap.GetAreaNumToOpenPath(n, chapter)){
				return n;
			}
		}
	}
	return 0;
}

bool Record_ChooseMap::CheckAliceDirection(WORD pointID, BYTE direction) const{
	// データベースを参照する。
	for(WORD n=1; n<CHOOSEMAP_PATH_MAX; n++){
		if(GetPathState(n) != CHOOSEMAP_PATHSTATE_OPENED) continue;
		// 指定したパスが、現在の位置と方向キーで移動出来るパスかどうかを返す。
		if(d_chooseMap.CheckPathMove(n, pointID, direction) != 0){
			return true;
		}
	}
	return false;
}

// アクセサ系
bool Record_ChooseMap::AddStageOfArea(WORD chapter, int areaID){
	if(areaID <= 0 || areaID >= CHOOSEMAP_AREA_MAX){
		return false;
	}else if(data.stageOfArea[areaID] == 0){
		// まだエリアが開放されていない
		return false;
	}else if(GetAreaIsCleared(chapter, areaID)){
		// 既にクリア済みである
		return false;
	}else{
		data.stageOfArea[areaID]++;
		return true;
	}
}

bool Record_ChooseMap::GetAreaIsCleared(WORD chapter, int areaID){
	if(areaID <= 0 || areaID >= CHOOSEMAP_AREA_MAX){
		return false;
	}
	// データベースの値との比較
	// 全マップをクリアするとstageOfAreaの値はstageNumの値より1大きくなる
	if(d_chooseMap.GetStageNum(areaID, chapter) == data.stageOfArea[areaID]-1){
		return true;
	}
	return false;
}