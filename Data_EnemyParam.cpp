// Data_EnemyParam.cpp

#include "Data_EnemyParam.h"
#include "Game_AliceDoll.h"
#include "CsvReader.h"

#define MAX_ENEMYPARAMFILE		999

Data_EnemyParam_Each::Data_EnemyParam_Each(){
	Refresh();
}

void Data_EnemyParam_Each::Refresh(){
	refID = 0;
	attr = DOLL_ATTR_NONE;
	exp = 0;
	for(int n=0; n<BATTLEUNIT_PARAM_NUM-1; n++){
		param[n] = 0;
	}
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _T(""));
	// �e�U���p�^�[���̃��Z�b�g
	for(int n=0; n<MAX_ACTIONPATTERN; n++){
		actionPtn[n].actionType = COMMANDTYPE_ERROR;
		actionPtn[n].skillID = 0;
		actionPtn[n].targetType = ACTIONTARGET_NONE;
		actionPtn[n].priority = 0;
		// �U�������̃��Z�b�g
		for(int i=0; i<MAX_CONDITION; i++){
			actionPtn[n].conditionType[i] = CONDITIONTYPE_ALWAYS;
			for(int j=0; j<MAX_CONDITIONPARAM; j++){
				actionPtn[n].conditionParam[i][j] = 0;
			}
		}
	}
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
	if(actionPtn[index].priority == 0){
		return NULL;
	}
	return &actionPtn[index];
}

void Data_EnemyParam_Each::SetActConditionPattern(
	int index, int conditionIndex, int type){
	actionPtn[index].conditionType[conditionIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionPattern(
	int index, int conditionIndex){
	return actionPtn[index].conditionType[conditionIndex];
}

void Data_EnemyParam_Each::SetActConditionParam(
	int index, int conditionIndex, int paramIndex, int type){
	actionPtn[index].conditionParam[conditionIndex][paramIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionParam(
	int index, int conditionIndex, int paramIndex){
	return actionPtn[index].conditionParam[conditionIndex][paramIndex];
}

Data_EnemyParam::Data_EnemyParam() : enemyList(){
}

bool Data_EnemyParam::Load(){
	return LoadDataFromCsv();
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
		sprintf_s(fileName, MAX_PATH-1, "dat_enemy\\enemy%03d.csv", n);
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		if(reader.Open(fileName)){
			tmpEnemy.Refresh();
			nEmptyFile = 0; // ��t�@�C�����̃��Z�b�g
			index = 0;
			// �_�~�[�s
			reader.NextLine();
			// ���t�@�����X�pID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpEnemy.SetRefID((WORD)reader.GetIntValue(0, 0));
			}
			// �_�~�[�s
			reader.NextLine();
			// �G�̖��O�Ƒ����ƌo���l���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				// �o�b�t�@�ɒ��ڒl������
				reader.GetValue(0, tmpEnemy.GetNamePtr(), BATTLEUNIT_NAME_BYTES-1);
				// ������ǂݎ��
				tmpEnemy.SetAttr((BYTE)reader.GetIntValue(1, DOLL_ATTR_NONE));
				// �o���l��ǂݎ��
				tmpEnemy.SetExp((DWORD)reader.GetIntValue(2, 0));
			}
			// �_�~�[�s
			reader.NextLine();
			// �G�̊e�p�����[�^���擾����
			reader.Read();
			for(int i=0; i<NUM_ENEMYPARAM_DATA; i++){
				tmpEnemy.SetParam(i, reader.GetIntValue(i, 0));
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
		if(pResult->GetRefID() == _refID){
			// �~����ID�ƈ�v������̂�����΂����Ԃ�
			return pResult;
		}
	}
	return NULL;
}