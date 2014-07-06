// CsvReader.cpp

#include "CsvReader.h"
#include <iostream>
#include <fstream>

CsvReader::CsvReader(){
	Reset();
}

CsvReader::~CsvReader(){
}

bool CsvReader::Open(LPTSTR name){
	_tcscpy_s(fileName, MAX_PATH-1, name);
	filePos = 0;
	lineNum = 0;

	// �t�@�C�����J��
	// (�J���邩�ǂ����̊m�F�������s��)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		return false;
	}

	// �t�@�C�������
	fin.close();
	return true;
}

DWORD CsvReader::GetMaxLine(){
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];

	DWORD lineNum=0;

	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(fin.eof()){
		return 0;
	}
	if(!fin){
		return 0;
	}

	WORD lineLng;
	bool isEnd = false;
	while(!fin.eof() && fin){
		// 1�s�ǂݍ���
		fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
		lineLng = _tcslen(buf);
		if(lineLng > 0 && buf[0] != _T('\n')){
			isEnd = false;
			for(int i=0; i<lineLng && !isEnd; i++){
				if(buf[i] != _T(' ') || buf[i] != _T('\n')){ // ���s�E�󔒂݂̗̂�̓J�E���g���Ȃ�
					lineNum++;
					isEnd = true; // ���[�v����E�o
					break;
				}
			}
		}
	}

	// �������ǂݍ��߂��s����Ԃ�
	return lineNum;
}

WORD CsvReader::Read(){
	// �ꎞ�I�Ƀt�@�C����ǂݍ���ł����o�b�t�@
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];
	WORD bufLng;	

	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(fin.eof()){
		return CSV_READ_END;
	}
	if(!fin){
		return CSV_READ_ERROR;
	}

	// ���݂̃t�@�C���ǂݍ��݈ʒu�Ɉړ�����
	fin.seekg(filePos, std::ios::beg);

	// 1�s�ǂݍ���
	fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
	bufLng = _tcslen(buf);

	// �t�@�C���ʒu��ۑ�����
	filePos = fin.tellg();

	// �Ƃ��Ƃƃt�@�C�������
	fin.close();

	// �ǂݍ��񂾕����񂪋�̏ꍇ
	if(bufLng == 0){
		valueNum = 0;
		return CSV_READ_NODATA;
	}

	WORD tmpValueNum = 0; // ���݉��Ԗڂ̍��ڂɕ��������Ă��邩
	WORD tmpValuePos = 0; // ���݂̍��ڂ̕�����
	// �������ŏ�����ǂݍ���ł���
	bool isEnd = false;
	for(int i=0; i<=bufLng && !isEnd; i++){ // ���[��'\0'�܂Ŋ܂�
		switch(buf[i]){
		case _T('\0'):
		case _T('\n'):		// �ǂݍ��݂̏I�[
			value[tmpValueNum][tmpValuePos] = '\0';
			tmpValueNum++;
			isEnd = true;
			break;
		case _T(','):		// �J���} : ���̒l��
			value[tmpValueNum][tmpValuePos] = '\0';
			tmpValueNum++;
			tmpValuePos = 0;
			if(tmpValueNum >= CSV_MAX_COLUMN){
				isEnd = true;
			}
			break;
		case _T(' '):		// �� : �l�̐擪�ł���Ζ�������
			if(tmpValuePos > 0){
				value[tmpValueNum][tmpValuePos] = buf[i];
				tmpValuePos++;
			}
			break;
		default:			// ���̑��̕��� : �l���p��
			value[tmpValueNum][tmpValuePos] = buf[i];
			tmpValuePos++;
			break;
		}
	}

	// �ǂݍ��߂Ȃ��ꍇ
	if(tmpValueNum == 0){
		valueNum = 0;
		return CSV_READ_NODATA;
	}

	// �s���J�E���g�𑝂₷
	// ��������s�͖���
	lineNum++;
	valueNum = tmpValueNum;

	return CSV_READ_NOERROR;
}

WORD CsvReader::NextLine(LPTSTR v, WORD strLen){
	// �ꎞ�I�Ƀt�@�C����ǂݍ���ł����o�b�t�@
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];
	// WORD bufLng;	

	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(fin.eof()){
		return CSV_READ_END;
	}
	if(!fin){
		return CSV_READ_ERROR;
	}

	// ���݂̃t�@�C���ǂݍ��݈ʒu�Ɉړ�����
	fin.seekg(filePos, std::ios::beg);

	// 1�s�ǂݍ���
	fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
	// bufLng = _tcslen(buf);
	if(v != 0){
		_tcscpy_s(v, strLen*sizeof(TCHAR), buf);
	}

	// �t�@�C���ʒu��ۑ�����
	filePos = fin.tellg();

	// �Ƃ��Ƃƃt�@�C�������
	fin.close();

	// ����ȏꍇ�̖߂�l��0
	return CSV_READ_NOERROR;
}

void CsvReader::Reset(){
	// �t�@�C�������Z�b�g
	_tcscpy_s(fileName, MAX_PATH, _T(""));

	// �t�@�C���ʒu���Z�b�g
	filePos = 0;

	// �f�[�^���Z�b�g
	for(int i=0; i<CSV_MAX_COLUMN; i++){
		_tcscpy_s(value[i], CSV_MAX_TEXT-1, _T(""));
	}

	// �l�̃��Z�b�g
	lineNum = 0;
	valueNum = 0;
}

void CsvReader::GetValue(WORD i, LPTSTR v, WORD strLen){
	if(!Used(i)){
		_tcscpy_s(v, strLen, _T("Error"));
	}else{
		_tcscpy_s(v, strLen, value[i]);
	}
	return;
}

int CsvReader::GetIntValue(WORD i, int errorValue){
	if(!Used(i)){ return errorValue; };
	return _ttoi(value[i]);
}

float CsvReader::GetFloatValue(WORD i, float errorValue){
	if(!Used(i)){ return errorValue; };
	return (float)(_ttof(value[i]));
}

TCHAR CsvReader::GetCharacter(WORD i, TCHAR errorValue, WORD charPos){
	if(charPos > strlen(value[i])-1) return errorValue;
	return value[i][charPos];
}

char CsvReader::GetCharValue(WORD i, char errorValue){
	if(!Used(i)){ return errorValue; };
	int iv = min(128, max(-127, _ttoi(value[i])));	
	return (char)iv;
}

bool CsvReader::Seek(LPTSTR word, WORD strlen, bool fromHead, bool goNextLine){
	std::streamoff cntFilePos;	// �֐����ł̃t�@�C���ʒu
	TCHAR tmpBuf[CSV_MAX_TEXT];

	// �t�@�C���̈ʒu�Ɉړ�
	if(fromHead){
		cntFilePos = 0;
	}else{
		cntFilePos = filePos;
	}

	// 1�s���ǂݍ��݁A�w�肳�ꂽ����������s��T��
	WORD isOK=CSV_READ_NOERROR;
	bool isFound=false;
	bool matching = true;

	while(isOK==CSV_READ_NOERROR && !isFound){
		// �t�@�C���ɃG���[���Ȃ��A�����񂪌������Ă��Ȃ�����
		isOK = NextLine(tmpBuf, CSV_MAX_TEXT); // �l���R�s�[����
		if(isOK == CSV_READ_NOERROR){
			break;
		}
		matching = true;
		for(int j=0; j<strlen; j++){
			if(word[j] != tmpBuf[j]){
				matching = false;
			}
		}
		if(matching){
			isFound = true;
		}
	}

	if(isFound){
		// ���������ʒu�Ɉړ�
		return true;
	}else{
		// �ړ����Ȃ�
		return false;
	}

	return true;
}