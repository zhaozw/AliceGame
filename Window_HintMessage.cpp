// Window_HintMessage.cpp

#include "Window_HintMessage.h"
#include <iostream>
#include <fstream>

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

bool Window_HintMessage::SetFileName(LPTSTR name){
	_tcscpy_s(fileName, MAX_PATH-1, name);
	filePos = 0;
	lineCount = 0;

	// ファイルを開く
	// (開けるかどうかの確認だけを行う)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return false;
	}

	// ファイルを閉じる
	fin.close();
	return true;
}