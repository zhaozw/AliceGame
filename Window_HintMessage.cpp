// Window_HintMessage.cpp

#include "Window_HintMessage.h"

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