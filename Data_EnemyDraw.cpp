// Data_EnemyDraw.cpp

#include "Data_EnemyDraw.h"

#include <fstream>

#include "CsvReader.h"
#include "Image.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYDRAWFILE		100

extern Image		g_image;

Data_EnemyDraw::Data_EnemyDraw(){
	drawList.Release();
}


bool Data_EnemyDraw::Load(){
#ifndef MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#endif // USE_ENCODED_CSV
}

bool Data_EnemyDraw::LoadDataFromCsv(){
	// ���X�g�̉��
	drawList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_EnemyDraw_Data		tmpDraw;

	strcpy_s(fileName, MAX_PATH-1, CSVFILE_ENEMYDRAW);
	if(reader.Open(fileName)){
		// �_�~�[�s
		reader.NextLine();
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		for(int n=0; n<MAX_ENEMYDRAWFILE; n++){
			tmpDraw = DATA_ENEMYDRAW_DATA();
			// ���t�@�����X�pID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpDraw.refID = (WORD)reader.GetIntValue(1, 0);
				// �摜�T�C�Y���擾
				tmpDraw.iWidth = reader.GetIntValue(2, 1);
				tmpDraw.iHeight = reader.GetIntValue(3, 1);
				// �`���ʒu���擾
				tmpDraw.cx = reader.GetFloatValue(4, 0);
				tmpDraw.cy = reader.GetFloatValue(5, 0);
				// �g��{�����擾
				tmpDraw.baseExRate = reader.GetFloatValue(6, 1.0);

				// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
				drawList.AddData(tmpDraw);
			}
		}
	}else{
		return false;
	}
	return true;
}

bool Data_EnemyDraw::LoadDataFromDat(){
	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_ENEMYDRAW,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "�ǂݍ��ݗp�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	DATA_ENEMYDRAW_DATA			copiedData;
	DWORD dataSize = 0;
	fin.read((char*)&dataSize, sizeof(DWORD));
	// �f�[�^�̐��A�܂�ifstream�����������Ȃ�����f�[�^�̓ǂݍ��݂��s��
	for(DWORD n=0; n<dataSize && !fin.eof() && fin; n++){
		fin.read((char*)&copiedData, sizeof(DATA_ENEMYDRAW_DATA));
		drawList.AddData(copiedData);
	}

	// �摜�n���h���̌��т��͖���蓮�ōs���K�v������
	DATA_ENEMYDRAW_DATA*		pData;
	for(int n=0; n<drawList.GetSize(); n++){
		pData = drawList.GetPointerByIndex(n);
		for(int i=0; i<DOLL_ATTR_NUM; i++){
			pData->hImg[i] = GetImgHandleByRefID(pData->refID, i);
		}
	}

	// �G���[�̊m�F
	if(!fin){
		fin.close();
		return false;
	}

	// �ǂݍ��ݏI��
	fin.close();

	return true;
}

bool Data_EnemyDraw::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorList�̃f�[�^�����������o��
	// �t�@�C���ɏ����o��
	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_ENEMYDRAW,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	// �Í����̂��߂̃R�s�[���s���o�b�t�@
	// (2014�N�ăR�~�ł͈Í������s��Ȃ�
	DATA_ENEMYDRAW_DATA			copiedData;
	DATA_ENEMYDRAW_DATA*		dataPtr;
	// �l�`�̐������f�[�^�̏����o�����s��
	DWORD length = drawList.GetSize();
	// �f�[�^�̌����ŏ��ɏ����o��
	fout.write((char*)&length, sizeof(DWORD));
	for(DWORD n=0; n<length; n++){
		// ���̂�Ԃ�
		dataPtr = drawList.GetPointerByIndex(n);
		copiedData = *dataPtr;
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYDRAW_DATA));
	}
	// �����o���I��
	fout.close();
	return true;


	/*
	DWORD fileSize = 0;
	void* dataPtr = NULL;
	std::basic_ofstream<TCHAR> fout;
	// dataPtr = drawList.SaveToString(&fileSize);

	if(fileSize != 0){
		// �t�@�C�����J��
		fout.open(DATFILE_ENEMYDRAW,
			std::ios::out|std::ios::binary|std::ios::trunc);
		if(!fout){
			_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
			return false;
		}
		// �f�[�^�������o��
		fout.write((char*)dataPtr, fileSize);
		// �����o���I��
		fout.close();
		// �m�ۂ����̈�̊J��
		VirtualFree(dataPtr, fileSize, MEM_DECOMMIT);
	}
	return true;
	*/
}

int Data_EnemyDraw::GetImgHandleByRefID(WORD refID, BYTE attr){
	// �G��ID�y�ё����Ɖ摜�̑Ή������߂�B
	// �����摜���Q�Ƃ��Ă��Ă����܂�Ȃ��B
	switch(refID){
	case ENEMYDRAW_SMALLFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_FAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_L_SNAIL:
		return g_image.enemy.snail[attr];
		break;
	case ENEMYDRAW_F_BUTTERFLY:
		return g_image.enemy.butterfly[attr];
		break;
	case ENEMYDRAW_SHIKABANE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_WINDCROW:
		return g_image.enemy.crow[attr];
		break;
	case ENEMYDRAW_HARPY:
		return g_image.enemy.harpy[attr];
		break;
	case ENEMYDRAW_HEALFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_INNOCENTBONE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_NECROMANCER:
		return g_image.enemy.cardinal;
		break;
	default:
		break;
	}
	return 0;
}

Data_EnemyDraw_Data* Data_EnemyDraw::GetEnemyDraw(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyDraw_Data* pResult = NULL;
	int maxSize = drawList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = drawList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->refID == _refID){
				// �~����ID�ƈ�v������̂�����΂����Ԃ�
				return pResult;
			}
		}
	}
	return NULL;
}
