// Record_ChooseMap.h

#pragma once

#include "Static_Map.h"
#include <Windows.h>

//=============================================
// �G���A�I����ʂ̃N���A��Ԃ�\���f�[�^�B
// �ǂ̓����J�ʂ��Ă��邩�̔���ƁA
// �e�G���A�̃N���A�X�e�[�W����ۑ�����B
// �܂��A���X�̊J����Ԃɂ��Ă��܂߂�B

typedef struct Record_ChooseMap_Data{
	BYTE		stageOfArea[CHOOSEMAP_AREA_MAX];	// �G���A���Ƃɐi�߂Ă���X�e�[�W�̐��B
													// 0���Ƃ��̃G���A������Ă��Ȃ��A
													// 1���ƃG���A�����ꂽ����A
													// 2���Ƃ��̃G���A�̃X�e�[�W��1�N���A������ԁB
	BYTE		pathState[CHOOSEMAP_PATH_MAX];		// �e���̏�ԁB
	bool		spotOpened[CHOOSEMAP_SPOT_MAX];		// �X�|�b�g���������Ă��邩�ۂ��B
	// �R���X�g���N�^
	Record_ChooseMap_Data(){
		for(int n=0; n<CHOOSEMAP_AREA_MAX; n++){
			stageOfArea[n] = 0;
		}
		for(int n=0; n<CHOOSEMAP_PATH_MAX; n++){
			pathState[n] = CHOOSEMAP_PATHSTATE_NONE;
		}
		for(int n=0; n<CHOOSEMAP_SPOT_MAX; n++){
			spotOpened[n] = false;
		}
	}
} RECORD_CHOOSEMAP_DATA;

// �O���[�o���ϐ� r_chooseArea����Q�Ƃ����B
class Record_ChooseMap{
private:
	RECORD_CHOOSEMAP_DATA		data;
public:
	// �R���X�g���N�^
	Record_ChooseMap();

	// ������
	// (�G���A1�̂݃v���C�\�ɂ���)
	bool Initialize();

	// �o�C�g�񂩂�f�[�^�ɓ��e���R�s�[����
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);

	// pathState���X�V����B
	// �����Ƃ��āA��ɍs����̂ł͂Ȃ��V�[���̐擪�ɂ�����
	// ���s����A�p�X���ʍs�\���ǂ����̔�����s���B
	// �V���ɊJ���ꂽ�p�X������ꍇ�A
	// ���̃p�X��pathState�̒l���X�V���A
	// �J���ꂽ�p�X��pathID��Ԃ��B
	WORD	CheckPathOpen(BYTE chapter);

	// �A�N�Z�T�n

	// �A���X�����݂̃|�C���g�������̕����Ɉړ��o���邩��Ԃ��B
	bool		CheckAliceDirection(WORD pointID, BYTE direction) const;

	// �w�肵���p�X���ʍs�\���ǂ�����Ԃ��B
	BYTE		GetPathState(WORD pathID) const{ return data.pathState[pathID]; };

	// �G���A�̃X�e�[�W���̎擾
	BYTE		GetStageOfArea(int index){
		if(index <= 0 || index >= CHOOSEMAP_AREA_MAX){
			return 0;
		}else{
			return data.stageOfArea[index];
		}
	};
	// �G���A���J������B
	// ��̓I�ɂ́A�w�肵���C���f�b�N�X��stageOfArea�l��1�ɂ���B
	bool		OpenArea(int index){
		if(index <= 0 || index >= CHOOSEMAP_AREA_MAX){
			return false;
		}else if(data.stageOfArea[index] > 0){
			return false;
		}else{
			data.stageOfArea[index] = 1;
			return true;
		}
	};
	// �G���A�̃X�e�[�W�N���A����1���₷�B
	// ���ɑS�X�e�[�W�J���ς݂̎��͉�����Ȃ��B
	bool		AddStageOfArea(WORD chapter, int areaID);
	// �G���A���N���A�ς݂ł��邩�ǂ������擾����B
	bool		GetAreaIsCleared(WORD chapter, int areaID);

	// �p�X���J���B
	bool		OpenPath(int index){
		data.pathState[index] = CHOOSEMAP_PATHSTATE_OPENED;
		return true;
	}



	// �f�[�^���擾����
	RECORD_CHOOSEMAP_DATA		GetData(){ return data; };
};