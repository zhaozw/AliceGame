// Data_DollParam.cpp

#include "Data_DollParam.h"

#include <Windows.h>
#include <string.h>
#include <tchar.h>
#include <fstream>

#include "CsvReader.h"
#include "Static_CompileMode.h"

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

void Data_DollParam_Each::GetName(LPTSTR buf, int bufSize){
	strcpy_s(buf, bufSize-1, typeName);
}

void Data_DollParam_Each::SetName(LPTSTR name){
	strcpy_s(typeName, DOLL_TYPENAME_BYTES-1, name);
}


//======================================================
// Data_DollParam�N���X

Data_DollParam::Data_DollParam() : dollList(){
}

bool Data_DollParam::Load(){
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_DollParam::LoadDataFromCsv(){
	TCHAR	fileName[MAX_PATH]; 
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		wsprintf(fileName, _T("dat_doll\\doll%02d.csv"), n+1);
		if(!dollList[n].Load(fileName)){
			return false;
		}
	}
	return true;
}

bool Data_DollParam::LoadDataFromDat(){
	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_DOLLPARAM,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "�ǂݍ��ݗp�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	TCHAR			copiedTypeName[DOLL_TYPENAME_BYTES];
	LEVELTOPARAM	copiedLTP;
	LEVELUPBONUS	copiedBonus;
	// �l�`�̐������f�[�^�̏����o�����s��
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		fin.read((char*)copiedTypeName, sizeof(TCHAR)*DOLL_TYPENAME_BYTES);
		dollList[n].SetName(copiedTypeName);
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			fin.read((char*)&copiedLTP, sizeof(LEVELTOPARAM));
			dollList[n].SetLvToP(i, copiedLTP);
		}
		for(int i=0; i<DOLL_LEVEL_MAX; i++){
			fin.read((char*)&copiedBonus, sizeof(LEVELUPBONUS));
			dollList[n].SetLvBonus(i, copiedBonus);
		}
	}

	// �ǂݍ��ݏI��
	fin.close();
	return true;
}

bool Data_DollParam::EncodeCsv(){
	// �f�[�^��ǂݍ���
	if(!LoadDataFromCsv()) return false;
	// �t�@�C���ɏ����o��
	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_DOLLPARAM,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	// �Í����̂��߂̃R�s�[���s���o�b�t�@
	// (2014�N�ăR�~�ł͈Í������s��Ȃ�
	TCHAR		 copiedTypeName[DOLL_TYPENAME_BYTES];
	LEVELTOPARAM copiedLTP;
	LEVELUPBONUS copiedBonus;
	// �l�`�̐������f�[�^�̏����o�����s��
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		dollList[n].GetName(copiedTypeName, DOLL_TYPENAME_BYTES);
		fout.write((char*)copiedTypeName, sizeof(TCHAR)*DOLL_TYPENAME_BYTES);
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			copiedLTP = dollList[n].GetLvToP(i);
			fout.write((char*)&copiedLTP, sizeof(LEVELTOPARAM));
		}
		for(int i=0; i<DOLL_LEVEL_MAX; i++){
			copiedBonus = dollList[n].GetLvBonus(i);
			fout.write((char*)&copiedBonus, sizeof(LEVELUPBONUS));
		}
	}
	// �����o���I��
	fout.close();
	return true;

}



int Data_DollParam::GetParamFromLv(BYTE dollType, BYTE paramType, int lv){
	if(dollType <= 0 || dollType > DOLL_TYPE_MAX) return -9999;
	return dollList[dollType-1].GetParamFromLv(paramType, lv);
}
