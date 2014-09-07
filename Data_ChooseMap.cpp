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
	// �|�C���g�ɂ���
	// �|�C���g���G���A�ɑΉ�������
	// �G���A1
	point[1].posX = 300;
	point[1].posY = 400;
	point[1].areaID = 1;
	// �G���A2
	point[2].posX = 450;
	point[2].posY = 350;
	point[2].areaID = 2;

	//===========================================
	// �p�X�ɂ���
	// �p�X�ɂ��G���A���m������
	path[1].edge[0].pointID = 1;
	path[1].edge[0].direction = MAP_EAST;
	path[1].edge[1].pointID = 2;
	path[1].edge[1].direction = MAP_WEST;
	for(int n=0; n<MAX_CHAPTER; n++){
		if(!SetAreaToOpenPath(1, 0, n)) return false;
		// �_�~�[
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
		// �G���A�����ݒ�̏ꍇ
		path[pathID].condition[chapter].num = 0;
	}
	if(path[pathID].condition[chapter].num >= CHOOSEMAP_PATH_CONDITION_AREA_MAX){
		// ����ȏ�G���A��ݒ�ł��Ȃ�
		return false;
	}
	for(int n=0; n<CHOOSEMAP_PATH_CONDITION_AREA_MAX; n++){
		if(path[pathID].condition[chapter].areaID[n] == 0){
			// �G���AID�̑���ɐ���
			path[pathID].condition[chapter].areaID[n] = areaID;
			if(path[pathID].condition[chapter].num == CHOOSEMAP_PATH_CONDITION_DISABLED){
				// �p�X��L����
				path[pathID].condition[chapter].num = 0;
			}
			// �N���A����K�v�̂���G���A����1���₵��
			path[pathID].condition[chapter].num++;
		}
	}
	return true;
}

