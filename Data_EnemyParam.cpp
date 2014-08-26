// Data_EnemyParam.cpp

#include "Data_EnemyParam.h"

#include <fstream>

#include "Game_AliceDoll.h"
#include "CsvReader.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYPARAMFILE		999

Data_EnemyParam_Each::Data_EnemyParam_Each(){
	data = DATA_ENEMYPARAM_EACH_DATA();
}

// �A�N�Z�T�֘A
void Data_EnemyParam_Each::SetActionPattern(int index, int paramIndex, int value){
	if(paramIndex < 0 || paramIndex >= ACTIONPATTERN_PARAMNUM){
		return;
	}
	switch(paramIndex){
	case ACTIONPATTERN_ACTIONTYPE:
		SetActionType(index, (WORD)value);
		break;
	case ACTIONPATTERN_SKILLID:
		SetActionSkillID(index, (WORD)value);
		break;
	case ACTIONPATTERN_ECOMMANDTARGET:
		SetActionTarget(index, (BYTE)value);
		break;
	case ACTIONPATTERN_PRIORITY:
		SetActionPriority(index, (WORD)value);
		break;
	}
}
int	Data_EnemyParam_Each::GetActionPattern(int index, int paramIndex){
	if(paramIndex < 0 || paramIndex >= ACTIONPATTERN_PARAMNUM){
		return -9999;
	}
	switch(paramIndex){
	case ACTIONPATTERN_ACTIONTYPE:
		(int)GetActionType(index);
		break;
	case ACTIONPATTERN_SKILLID:
		(int)GetActionSkillID(index);
		break;
	case ACTIONPATTERN_ECOMMANDTARGET:
		(int)GetActionTarget(index);
		break;
	case ACTIONPATTERN_PRIORITY:
		(int)GetActionPriority(index);
		break;
	}
	return 0;
}

ENEMYACTIONPATTERN* Data_EnemyParam_Each::GetActionPatternPtr(int index){
	if(index < 0 || index >= MAX_ACTIONPATTERN){
		return NULL;
	}
	if(data.actionPtn[index].priority == 0){
		return NULL;
	}
	return &data.actionPtn[index];
}

void Data_EnemyParam_Each::SetActConditionPattern(
	int index, int conditionIndex, int type){
	data.actionPtn[index].conditionType[conditionIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionPattern(
	int index, int conditionIndex){
	return data.actionPtn[index].conditionType[conditionIndex];
}

void Data_EnemyParam_Each::SetActConditionParam(
	int index, int conditionIndex, int paramIndex, int type){
	data.actionPtn[index].conditionParam[conditionIndex][paramIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionParam(
	int index, int conditionIndex, int paramIndex){
	return data.actionPtn[index].conditionParam[conditionIndex][paramIndex];
}

Data_EnemyParam::Data_EnemyParam() : enemyList(){
}

bool Data_EnemyParam::Load(){
	enemyList.Reserve(DATANUM_ENEMYPARAM);
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_EnemyParam::LoadDataFromCsv(){
	// ���X�g�̉��
	enemyList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_EnemyParam_Each	tmpEnemy;
	// �t�@�C�������݂��Ȃ��ꍇ�����x���������烋�[�v�𔲂���
	int						nEmptyFile = 0;
	// ���Ԗڂ̓G�C���f�b�N�X�܂Ŗ��܂��Ă��邩
	int						index = 0;
	int						actionIndex = 0;

	for(int n=1; n<=MAX_ENEMYPARAMFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, CSVFILE_ENEMYPARAM, n);
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		if(reader.Open(fileName)){
			tmpEnemy = Data_EnemyParam_Each();
			nEmptyFile = 0; // ��t�@�C�����̃��Z�b�g
			index = 0;
			// �_�~�[�s
			reader.NextLine();
			// ���t�@�����X�pID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpEnemy.data.refID = (WORD)reader.GetIntValue(0, 0);
			}
			// �_�~�[�s
			reader.NextLine();
			// �G�̖��O�Ƒ����ƌo���l���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				// �o�b�t�@�ɒ��ڒl������
				reader.GetValue(0, tmpEnemy.data.name, BATTLEUNIT_NAME_BYTES-1);
				// ������ǂݎ��
				tmpEnemy.data.attr = (BYTE)reader.GetIntValue(1, DOLL_ATTR_NONE);
				// �o���l��ǂݎ��
				tmpEnemy.data.exp = (DWORD)reader.GetIntValue(2, 0);
			}
			// �_�~�[�s
			reader.NextLine();
			// �G�̊e�p�����[�^���擾����
			reader.Read();
			for(int i=0; i<NUM_ENEMYPARAM_DATA; i++){
				tmpEnemy.data.param[i] = reader.GetIntValue(i, 0);
			}
			reader.NextLine();
			// �X�e�[�g�̔z����擾����
			for(int i=0; i<MAX_INITIALSTATE; i++){
				reader.Read();
				tmpEnemy.SetInitialState(
					i,
					reader.GetIntValue(0, 0),
					reader.GetIntValue(1, 0),
					reader.GetIntValue(2, 0));
			}
			reader.NextLine();
			// �G�̍U���p�^�[�����擾����
			for(int i=0; i<MAX_ACTIONPATTERN; i++){
				// �e�s���͎O�s�ɕ����ċL�q����B
				// ��s�ځF�U���p�^�[�����A�X�L��ID�A�^�[�Q�b�g�̃^�C�v�A�D��x
				// ��s�ځA�O�s�ځF�����A�����Ɋւ���p�����[�^(3��)
				reader.Read();
				// ��s��
				tmpEnemy.SetActionPattern(i, 0,
					GetActionTypeFromChar(reader.GetCharacter(0)));
				tmpEnemy.SetActionPattern(i, 1,
					(DWORD)reader.GetIntValue(1, 0));
				tmpEnemy.SetActionPattern(i, 2,
					(BYTE)reader.GetIntValue(2, 0));
				tmpEnemy.SetActionPattern(i, 3,
					(WORD)reader.GetIntValue(3, 0));
				// ��s�ځA�O�s��
				for(int j=0; j<MAX_CONDITION; j++){
					reader.Read();
					tmpEnemy.SetActConditionPattern(
						i, j, reader.GetIntValue(0, 0));
					for(int k=0; k<MAX_CONDITIONPARAM; k++){
						tmpEnemy.SetActConditionParam(
							i, j, k, reader.GetIntValue(1+k, 0));
					}
				}
				// �_�~�[�s
				reader.NextLine();
			}
			// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
			enemyList.AddData(tmpEnemy);
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

bool Data_EnemyParam::LoadDataFromDat(){
	// �t�@�C�����J��
	std::basic_ifstream<TCHAR>	fin;
	TCHAR						fileName[MAX_PATH];

	DATA_ENEMYPARAM_EACH_DATA		copiedData;
	Data_EnemyParam_Each			data;
	// �f�[�^�̐��A�܂�ifstream�����������Ȃ�����f�[�^�̓ǂݍ��݂��s��
	for(DWORD n=0; n<MAX_ENEMYPARAMFILE; n++){
		wsprintf(fileName, DATFILE_ENEMYPARAM, n);
		fin.open(fileName,
			std::ios::in|std::ios::binary);
		if(fin){
			fin.read((char*)&copiedData, sizeof(DATA_ENEMYPARAM_EACH_DATA));
			data.data = copiedData;
			enemyList.AddData(data);
		}else{
		}
		fin.close();
		fin.clear();
	}
	return true;
}

bool Data_EnemyParam::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorList�̃f�[�^�����������o��
	// �t�@�C���ɏ����o��

	TCHAR						fileName[MAX_PATH];
	std::basic_ofstream<TCHAR>	fout;

	// �Í����̂��߂̃R�s�[���s���o�b�t�@
	// (2014�N�ăR�~�ł͈Í������s��Ȃ�
	DATA_ENEMYPARAM_EACH_DATA			copiedData;
	Data_EnemyParam_Each*				dataPtr;
	// �l�`�̐������f�[�^�̏����o�����s��
	DWORD length = enemyList.GetSize();
	// �f�[�^�̌����ŏ��ɏ����o��
	for(DWORD n=0; n<length; n++){
		// ���̂�Ԃ�
		dataPtr = enemyList.GetPointerByIndex(n);
		copiedData = dataPtr->data;
		wsprintf(fileName, DATFILE_ENEMYPARAM, n);
		fout.open(fileName,
			std::ios::out|std::ios::binary|std::ios::trunc);
		if(!fout){
			_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
			return false;
		}
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYPARAM_EACH_DATA));
		fout.close();
		fout.clear();
	}
	return true;
}

WORD Data_EnemyParam::GetActionTypeFromChar(TCHAR c){
	switch(c){
	case 'A':
		return COMMANDTYPE_ATTACK;
		break;
	case 'S':
		return COMMANDTYPE_SKILL;
		break;
	case 'G':
		return COMMANDTYPE_GUARD;
		break;
	case 'W':
	default:
		return COMMANDTYPE_NONE;
		break;
	}
}


Data_EnemyParam_Each* Data_EnemyParam::GetEnemyParam(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyParam_Each* pResult;
	int maxSize = enemyList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = enemyList.GetPointerByIndex(n);
		if(pResult->data.refID == _refID){
			// �~����ID�ƈ�v������̂�����΂����Ԃ�
			return pResult;
		}
	}
	return NULL;
}