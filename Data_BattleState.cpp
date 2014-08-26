// Data_BattleState.cpp

#include "Data_BattleState.h"
#include "CsvReader.h"

#include "Static_CompileMode.h"

#define MAX_BATTLESTATE			999

Data_BattleState_Each::Data_BattleState_Each(){
	Refresh();
}

void Data_BattleState_Each::Refresh(){
	refID = 0;
	calcOrder = 0;
	drawOrder = 0;
	iconIndex = 0;
	flags = 0x00000000;
	strcpy_s(stateName, STATENAME_LENGTH-1, _T(""));
}

void Data_BattleState_Each::SetStateName(LPTSTR name, int size){
	strcpy_s(stateName, STATENAME_LENGTH-1, name);
}

void Data_BattleState_Each::GetStateName(LPTSTR buf, int bufSize){
	strcpy_s(buf, bufSize-1, stateName);
}

Data_BattleState::Data_BattleState(){
}

bool Data_BattleState::Load(){
	stateList.Reserve(DATANUM_STATEINFO);
	return LoadDataFromCsv();
}



bool Data_BattleState::LoadDataFromCsv(){
	// ���X�g�̉��
	stateList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �X�e�[�g����ێ�����
	TCHAR					stateName[STATENAME_LENGTH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_BattleState_Each	tmpState;

	strcpy_s(fileName, MAX_PATH-1, CSVFILE_STATEINFO);
	if(reader.Open(fileName)){
		// �_�~�[�s
		reader.NextLine();
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		for(int n=0; n<MAX_BATTLESTATE; n++){
			tmpState.Refresh();
			// ���t�@�����X�pID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpState.SetRefID((WORD)reader.GetIntValue(1, 0));
			}
			// ���O���擾
			reader.GetValue(0, stateName, STATENAME_LENGTH);
			tmpState.SetStateName(stateName, STATENAME_LENGTH);
			// �����������擾
			tmpState.SetCalcOrder(reader.GetIntValue(2, 1));
			// �`�揇�����擾
			tmpState.SetDrawOrder(reader.GetIntValue(3, 0));
			// �A�C�R�����擾
			tmpState.SetIconIndex(reader.GetIntValue(4, 0));
			// �t���O���Z�b�g����
			tmpState.SetFlags(reader.GetIntValue(5, 0));
			// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
			stateList.AddData(tmpState);
		}
	}else{
		return false;
	}
	return true;
}

Data_BattleState_Each* Data_BattleState::GetBattleState(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_BattleState_Each* pResult = NULL;
	int maxSize = stateList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = stateList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// �~����ID�ƈ�v������̂�����΂����Ԃ�
				return pResult;
			}
		}
	}
	return NULL;
}

bool Data_BattleState::CheckFlagOfState(WORD _refID, DWORD _flag){
	Data_BattleState_Each* pResult = NULL;
	pResult = GetBattleState(_refID);
	if(pResult != NULL){
		if((pResult->GetFlags() & _flag) != 0){
			return true;
		}
	}
	return false;
}