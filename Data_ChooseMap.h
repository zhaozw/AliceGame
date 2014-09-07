// Data_ChooseMap.h

#pragma once

#include "Static_Map.h"
#include "Static_Game.h"
#include <Windows.h>

//==============================================
// Data_ChooseMap�N���X
// �G���A�I����ʂɂ�����f�[�^�������B
// �O���[�o���ϐ�d_chooseMap����Q�Ƃ����B
//
// ���̈ړ��Ɋւ��ẮAData_ChooseMap_Path�\���̂�����̎�̂ƂȂ�B
// Data_ChooseMap_Path�\���̂̃����o�ł���Data_ChooseMap_Path_Edge�\���̂�
// ���̓��̗��[�̃|�C���g�̃|�C���gID�ƁA���̃|�C���g����ǂ̕����L�[������������
// �ړ����铹�ł��邩��ێ����Ă���B
// �v���C���[������L�[�����������A���݃v���C���[������|�C���g��ID�ƕ����L�[�ɂ����
// �eData_ChooseMap_Path�\���̂��X�L�������A
// �ړ�����悤�ȃp�X������΁A����ɉ����ăv���C���[���ړ�������B
// 
// ���e�͏͂��ƂɁA�ꕔ�d�����A�ꕔ�قȂ��Ă��邪�A
// �͂��Ƃ�d_chooseMap�ɕʂ̒l��ǂݍ��ނ��Ƃ͂����A
// �S�Ă̏͂̏����܂Ƃ߂ēǂݍ��ށB


// �G���A�I���}�b�v�ɂ�����A���̗��[�̏���ێ�����\���́B
typedef struct Data_ChooseMap_Path_Edge{
	// ���̒[�����Ԃ̃|�C���g�ɐڑ�����Ă��邩
	WORD					pointID;
	// ���̃|�C���g����ǂ���̕����ɐڑ�����Ă��邩
	BYTE					direction;	
	Data_ChooseMap_Path_Edge(){
		pointID = 0;
		direction = 0;
	};
} DATA_CHOOSEMAP_PATH_EDGE;

// �`���v�^�[���Ƃ́A���̉��������ێ�����\���́B
#define CHOOSEMAP_PATH_CONDITION_AREA_MAX		3
#define CHOOSEMAP_PATH_CONDITION_DISABLED		(CHOOSEMAP_PATH_CONDITION_AREA_MAX+1)
typedef struct Data_ChooseMap_Path_Condition{
	BYTE	areaID[CHOOSEMAP_PATH_CONDITION_AREA_MAX];	// ���̉���Ɋ֘A����G���A�Q�B
	BYTE	num;						// ��L�̃G���A�Q�̂����A�N���A����K�v��	
										// ����G���A���B�������AareaID��0�̏ꍇ�͏����B
										// 0�ɂ���ƁA�ŏ�����J����Ă��铹�B
	Data_ChooseMap_Path_Condition(){
		for(int n=0; n<CHOOSEMAP_PATH_CONDITION_AREA_MAX; n++){
			areaID[n] = 0;
		}
		num = CHOOSEMAP_PATH_CONDITION_DISABLED; // �g�p���Ȃ����`�F�b�N�B
	};
} DATA_CHOOSEMAP_PATH_CONDITION;

// �G���A�I���}�b�v�ɂ����铹�̏���ێ�����\���́B
// �p�XID��0�Ԃ͎g�p���Ȃ��B
typedef struct Data_ChooseMap_Path{
	DATA_CHOOSEMAP_PATH_EDGE				edge[2];
	DATA_CHOOSEMAP_PATH_CONDITION			condition[MAX_CHAPTER];
	Data_ChooseMap_Path() : edge(), condition(){
	};
} DATA_CHOOSEMAP_PATH;

// �G���A�I���}�b�v�ɂ�����|�C���g�̏���ێ�����\���́B
// �|�C���gID��0�Ԃ͎g�p���Ȃ��B
typedef struct Data_ChooseMap_Point{
	BYTE					areaID;		// �G���A��ID�B�ǂ��ł��Ȃ��ꍇ��0�B
	int						posX;
	int						posY;		// ���W�B
	Data_ChooseMap_Point(){
		areaID = 0;
	}
}DATA_CHOOSEMAP_POINT;


// �G���A�I���}�b�v�ɂ�����X�|�b�g����̏���ێ�����\���́B
typedef struct Data_ChooseMap_Spot{
	bool					opened;		// �X�|�b�g���������Ă��邩�ۂ�
	Data_ChooseMap_Spot(){
		opened = false;
	}
}DATA_CHOOSEMAP_SPOT;

// �e�G���A�̃X�e�[�W�Ȃǂ̏���ێ�����\���́B
typedef struct Data_ChooseMap_Area{
	// �}�b�v��ID�B�`���v�^�[���Ƃɔh���B
	// 
	WORD				mapID[MAX_CHAPTER*CHOOSEMAP_STAGE_MAX];	
	Data_ChooseMap_Area(){
		for(int n=0; n<MAX_CHAPTER*CHOOSEMAP_STAGE_MAX; n++){
			mapID[n] = 0;
		}
	}
}DATA_CHOOSEMAP_AREA;


// �G���A�I���}�b�v�S�̂̏���ێ�����N���X�B
class Data_ChooseMap{
protected:
	// �|�C���g�̏��B
	DATA_CHOOSEMAP_POINT		point[CHOOSEMAP_POINT_MAX];
	// �p�X�̏��B
	DATA_CHOOSEMAP_PATH			path[CHOOSEMAP_PATH_MAX];
	// �X�|�b�g�̏��B
	DATA_CHOOSEMAP_SPOT			spot[CHOOSEMAP_SPOT_MAX];
	// �X�e�[�W�̏��B
	DATA_CHOOSEMAP_AREA			area[CHOOSEMAP_AREA_MAX];

public:
	// �R���X�g���N�^
	Data_ChooseMap();

	// �f�[�^��ǂݍ��ށB
	bool Load();
	bool LoadDataByHand();		// ����͂œ����
	bool LoadDataFromCsv();
	bool LoadDataFromDat();
	bool EncodeCsv();

	// �p�XID�A�|�C���g�A�������w�肷��ƁA���̃p�X�����̃|�C���g�ƕ�����
	// �ړ����邩��Ԃ��B
	// ���̊֐��ł͈ʒu�֌W�݂̂𔻕ʂ��A
	// ���ۂɈړ��o���邩�ǂ���(�Q�[���̐i���ɂ���ĕς��)�͔��肵�Ȃ��B
	bool CheckPathMove(WORD pathID, WORD pointID, BYTE direction) const;

	// �A�N�Z�T�n
	// �|�C���g�̍��W���擾����B
	int GetPointX(int index){
		if(index > 0 || index < CHOOSEMAP_POINT_MAX){
			return point[index].posX;
		}
		return 0;
	}
	int GetPointY(int index){
		if(index > 0 || index < CHOOSEMAP_POINT_MAX){
			return point[index].posY;
		}
		return 0;
	}

	// �p�X�̗��[�̃|�C���g�̃C���f�b�N�X���擾����B
	// isRoot : �p�X�̏o����(�֋X���߂Ă��邾���ŁA�Ӗ��͂Ȃ�)
	WORD	GetPathEdgeIndex(int index, bool isRoot){
		if(index > 0 || index < CHOOSEMAP_PATH_MAX){
			return path[index].edge[(isRoot?0:1)].pointID;
		}
		return 0;
	}

	// �p�X�̉���ɕK�v�ȃG���A��ݒ肷��B
	bool	SetAreaToOpenPath(WORD pathID, WORD areaID, BYTE chapter);

	// �e�G���A�̃X�e�[�W�����擾����B
	int	GetStageNum(int areaID, int chapter){
		for(int n=0; n<CHOOSEMAP_STAGE_MAX; n++){
			if(area[areaID].mapID[n+chapter*CHOOSEMAP_STAGE_MAX] == 0){
				// ID��0�̃}�b�v�͎g�p����Ȃ��B
				// �]���āA���̎���n���G���A���Ƃ̃X�e�[�W���B
				return n;
			}
		}
		return CHOOSEMAP_STAGE_MAX;
	}

	// �p�X�̉���ɕK�v�ȃG���A���擾����B
	WORD	GetAreaToOpenPath(WORD pathID, int index, BYTE chapter){
		return path[pathID].condition[chapter].areaID[index];
	}
	BYTE	GetAreaNumToOpenPath(WORD pathID, BYTE chapter){
		return path[pathID].condition[chapter].num;
	}

	// �G���A�Ƀ}�b�vID���Z�b�g����B
	void SetMapID(WORD mapID, WORD chapter, WORD areaID, WORD mapIndex){
		area[areaID].mapID[mapIndex+chapter*CHOOSEMAP_STAGE_MAX] = mapID;
	}

	// �G���A�̃}�b�vID���擾����B
	WORD GetMapID(WORD chapter, WORD areaID, WORD mapIndex){
		return area[areaID].mapID[mapIndex+chapter*CHOOSEMAP_STAGE_MAX];
	}




};