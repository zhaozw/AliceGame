// Data_DollParam.cpp

#include "Data_DollParam.h"

#include <Windows.h>
#include <string.h>
#include <tchar.h>

#include "CsvReader.h"

//======================================================
// Data_DollParam_Each�N���X

Data_DollParam_Each::Data_DollParam_Each() : LvToP(), LvBonus(){
}

bool Data_DollParam_Each::Load(LPTSTR fileName){
	CsvReader reader;
	// �t�@�C�����J��
	if(!reader.Open(fileName)){
		return false;
	}
	// ���O��ǂݍ���
	reader.Read();
	reader.GetValue(0, typeName, DOLL_TYPENAME_BYTES);
	// ��s��ǂ�
	reader.Read();
	// �p�����[�^�̏㏸����ǂݍ���
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		// ��s�ǂ�
		reader.Read();
		// �W��3���擾����
		// ���₷���̂��߂�0�Ԗڂ̗v�f�͔\�͒l�����g�p�B
		LvToP[n].a = reader.GetFloatValue(1);
		LvToP[n].b = reader.GetFloatValue(2);
		LvToP[n].c = reader.GetFloatValue(3);
	}
	// ��s��ǂ�
	reader.Read();
	// ���x���A�b�v�{�[�i�X��ǂݍ���
	for(int n=0; n<DOLL_LEVEL_MAX; n++){
		// ��s�ǂ�
		reader.Read();
		// �e�p�����[�^���擾����
		for(int m=0; m<DOLL_PARAM_MAX; m++){
			LvBonus[n].growth[m] = reader.GetIntValue(m+1, 0);
		}
		LvBonus[n].skillID = reader.GetIntValue(DOLL_PARAM_MAX+1, 0);
	}
	return true;
}

int Data_DollParam_Each::GetParamFromLv(BYTE paramType, int lv){
	if(paramType >= DOLL_PARAM_MAX) return 0;
	return (int)(LvToP[paramType].a * lv*lv + LvToP[paramType].b * lv 
		+ LvToP[paramType].c); 
}

//======================================================
// Data_DollParam�N���X

Data_DollParam::Data_DollParam() : dollList(){
}

bool Data_DollParam::Load(){
	TCHAR	fileName[MAX_PATH]; 
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		wsprintf(fileName, _T("dat_doll\\doll%02d.csv"), n+1);
		if(!dollList[n].Load(fileName)){
			return false;
		}
	}
	return true;
}

int Data_DollParam::GetParamFromLv(BYTE dollType, BYTE paramType, int lv){
	if(dollType <= 0 || dollType > DOLL_TYPE_MAX) return -9999;
	return dollList[dollType-1].GetParamFromLv(paramType, lv);
}
