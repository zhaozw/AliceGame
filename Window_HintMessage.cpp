// Window_HintMessage.cpp

#include "Window_HintMessage.h"
#include <iostream>
#include <fstream>

Window_HintMessage::Window_HintMessage() : Window_Message(){
	// �E�B���h�E�̏����N���A����B
	Clear();
}

void Window_HintMessage::Clear(){
	// �t�@�C�������Z�b�g
	_tcscpy_s(fileName, MAX_PATH, _T(""));
	// �t�@�C���ʒu���Z�b�g
	filePos = 0;
}

bool Window_HintMessage::SetFileName(LPTSTR name){
	_tcscpy_s(fileName, MAX_PATH-1, name);
	filePos = 0;
	lineCount = 0;

	// �t�@�C�����J��
	// (�J���邩�ǂ����̊m�F�������s��)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return false;
	}

	// �t�@�C�������
	fin.close();
	return true;
}