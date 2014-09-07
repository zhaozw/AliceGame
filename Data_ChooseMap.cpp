// Data_ChooseMap.cpp

#include "Data_ChooseMap.h"
#include "Static_Map.h"

Data_ChooseMap::Data_ChooseMap() : point(), path(), spot(), area(){
}

bool Data_ChooseMap::Load(){
	return LoadDataByHand();
#ifndef MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#endif // USE_ENCODED_CSV
}

bool Data_ChooseMap::LoadDataByHand(){

	//===========================================
	// ポイントについて
	// ポイントをエリアに対応させる
	// エリア1
	point[1].posX = 300;
	point[1].posY = 400;
	point[1].areaID = 1;
	// エリア2
	point[2].posX = 450;
	point[2].posY = 350;
	point[2].areaID = 2;

	//===========================================
	// パスについて
	// パスによりエリア同士を結ぶ
	path[1].edge[0].pointID = 1;
	path[1].edge[0].direction = MAP_EAST;
	path[1].edge[1].pointID = 2;
	path[1].edge[1].direction = MAP_WEST;
	for(int n=0; n<MAX_CHAPTER; n++){
		if(!SetAreaToOpenPath(1, 0, n)) return false;
		// ダミー
		path[1].condition[n].num = 0;
	}
	return true;
}


bool Data_ChooseMap::CheckPathMove(WORD pathID, WORD pointID, BYTE direction) const{
	for(int j=0; j<2; j++){
		if(path[pathID].edge[j].pointID == pointID 
			&& path[pathID].edge[j].direction == direction){
			return true;
		}
	}
	return false;
}

bool Data_ChooseMap::LoadDataFromCsv(){
	return true;
}

bool Data_ChooseMap::LoadDataFromDat(){
	return true;
}

bool Data_ChooseMap::EncodeCsv(){
	return true;
}


bool Data_ChooseMap::SetAreaToOpenPath(WORD pathID, WORD areaID, BYTE chapter){
	if(path[pathID].condition[chapter].num == CHOOSEMAP_PATH_CONDITION_AREA_MAX+1){
		// エリアが未設定の場合
		path[pathID].condition[chapter].num = 0;
	}
	if(path[pathID].condition[chapter].num >= CHOOSEMAP_PATH_CONDITION_AREA_MAX){
		// これ以上エリアを設定できない
		return false;
	}
	for(int n=0; n<CHOOSEMAP_PATH_CONDITION_AREA_MAX; n++){
		if(path[pathID].condition[chapter].areaID[n] == 0){
			// エリアIDの代入に成功
			path[pathID].condition[chapter].areaID[n] = areaID;
			if(path[pathID].condition[chapter].num == CHOOSEMAP_PATH_CONDITION_DISABLED){
				// パスを有効に
				path[pathID].condition[chapter].num = 0;
			}
			// クリアする必要のあるエリア数を1増やした
			path[pathID].condition[chapter].num++;
		}
	}
	return true;
}

