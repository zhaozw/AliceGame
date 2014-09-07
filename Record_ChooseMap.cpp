// Record_ChooseMap.cpp

#include "Record_ChooseMap.h"
#include "Data_ChooseMap.h"

extern Data_ChooseMap		d_chooseMap;

Record_ChooseMap::Record_ChooseMap() : data(){
}

bool Record_ChooseMap::Initialize(){
	// ������u1-1�v���J��
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
		// ����Ώۂ́A���ݕ��Ă���p�X�Ɍ���B
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
	// �f�[�^�x�[�X���Q�Ƃ���B
	for(WORD n=1; n<CHOOSEMAP_PATH_MAX; n++){
		if(GetPathState(n) != CHOOSEMAP_PATHSTATE_OPENED) continue;
		// �w�肵���p�X���A���݂̈ʒu�ƕ����L�[�ňړ��o����p�X���ǂ�����Ԃ��B
		if(d_chooseMap.CheckPathMove(n, pointID, direction) != 0){
			return true;
		}
	}
	return false;
}

// �A�N�Z�T�n
bool Record_ChooseMap::AddStageOfArea(WORD chapter, int areaID){
	if(areaID <= 0 || areaID >= CHOOSEMAP_AREA_MAX){
		return false;
	}else if(data.stageOfArea[areaID] == 0){
		// �܂��G���A���J������Ă��Ȃ�
		return false;
	}else if(GetAreaIsCleared(chapter, areaID)){
		// ���ɃN���A�ς݂ł���
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
	// �f�[�^�x�[�X�̒l�Ƃ̔�r
	// �S�}�b�v���N���A�����stageOfArea�̒l��stageNum�̒l���1�傫���Ȃ�
	if(d_chooseMap.GetStageNum(areaID, chapter) == data.stageOfArea[areaID]-1){
		return true;
	}
	return false;
}