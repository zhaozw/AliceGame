// Window_HintMessage.cpp

#include "Window_HintMessage.h"

Window_HintMessage::Window_HintMessage() : Window_Message(){
	// ウィンドウの情報をクリアする。
	Clear();
}

void Window_HintMessage::Clear(){
	// ファイル名リセット
	_tcscpy_s(fileName, MAX_PATH, _T(""));
	// ファイル位置リセット
	filePos = 0;

}