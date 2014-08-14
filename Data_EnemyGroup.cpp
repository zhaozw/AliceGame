// Data_EnemyGroup.cpp

#include "Data_EnemyGroup.h"

#include <fstream>

#include "CsvReader.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYGROUPFILE		999


Data_EnemyGroup::Data_EnemyGroup(){
}

bool Data_EnemyGroup::Load(){
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_EnemyGroup::LoadDataFromCsv(){
	// ���X�g�̉��
	groupList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_EnemyGroup_Data	tmpGroup;
	// �t�@�C�������݂��Ȃ��ꍇ�����x���������烋�[�v�𔲂���
	int						nEmptyFile = 0;
	// ���Ԗڂ̓G�C���f�b�N�X�܂Ŗ��܂��Ă��邩
	int						index = 0;

	for(int n=1; n<=MAX_ENEMYGROUPFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, CSVFILE_ENEMYGROUP, n);
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		if(reader.Open(fileName)){
			nEmptyFile = 0; // ��t�@�C�����̃��Z�b�g
			index = 0;
			tmpGroup = DATA_ENEMYGROUP_DATA();
			// �_�~�[�s
			reader.NextLine();
			// �O���[�vID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpGroup.refID = ((WORD)reader.GetIntValue(0, 0));
			}
			// �_�~�[�s
			reader.NextLine();
			// �G��ID�Ƃ��̕`��ʒu�y�ё������擾����
			for(int i=0; i<MAX_BATTLEENEMY; i++){
				if(reader.Read() == CSV_READ_NOERROR){
					if(reader.GetIntValue(0, 0) != 0){
						tmpGroup.enemy[index].refID = (WORD)reader.GetIntValue(0, 0);
						tmpGroup.enemy[index].drawX = (WORD)reader.GetIntValue(1, 0);
						tmpGroup.enemy[index].drawY = (WORD)reader.GetIntValue(2, 0);
						tmpGroup.enemy[index].attr = (BYTE)reader.GetIntValue(3, 0);
						index++;
					}
				}
			}
			// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
			groupList.AddData(tmpGroup);
		}else{
			nEmptyFile++;
			if(nEmptyFile > 100){
				// ��t�@�C�����������ꍇ�A���[�v�𔲂���
				break;
			}
		}
	}
	return true;
}

bool Data_EnemyGroup::LoadDataFromDat(){
	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_ENEMYGROUP,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "�ǂݍ��ݗp�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	DATA_ENEMYGROUP_DATA			copiedData;
	DWORD dataSize = 0;
	fin.read((char*)&dataSize, sizeof(DWORD));
	// �f�[�^�̐��A�܂�ifstream�����������Ȃ�����f�[�^�̓ǂݍ��݂��s��
	for(DWORD n=0; n<dataSize && !fin.eof() && fin; n++){
		fin.read((char*)&copiedData, sizeof(DATA_ENEMYGROUP_DATA));
		groupList.AddData(copiedData);
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

bool Data_EnemyGroup::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorList�̃f�[�^�����������o��
	// �t�@�C���ɏ����o��
	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_ENEMYGROUP,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	// �Í����̂��߂̃R�s�[���s���o�b�t�@
	// (2014�N�ăR�~�ł͈Í������s��Ȃ�
	DATA_ENEMYGROUP_DATA			copiedData;
	DATA_ENEMYGROUP_DATA*			dataPtr;
	// �l�`�̐������f�[�^�̏����o�����s��
	DWORD length = groupList.GetSize();
	// �f�[�^�̌����ŏ��ɏ����o��
	fout.write((char*)&length, sizeof(DWORD));
	for(DWORD n=0; n<length; n++){
		// ���̂�Ԃ�
		dataPtr = groupList.GetPointerByIndex(n);
		copiedData = *dataPtr;
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYGROUP_DATA));
	}
	// �����o���I��
	fout.close();
	return true;
}

Data_EnemyGroup_Data* Data_EnemyGroup::GetEnemyGroup(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyGroup_Data* pResult = NULL;
	int maxSize = groupList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = groupList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->refID == _refID){
				// �~����ID�ƈ�v������̂�����΂����Ԃ�
				return pResult;
			}
		}
	}
	return NULL;
}

