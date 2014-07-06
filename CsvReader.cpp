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

	// ファイルを開く
	// (開けるかどうかの確認だけを行う)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		return false;
	}

	// ファイルを閉じる
	fin.close();
	return true;
}

DWORD CsvReader::GetMaxLine(){
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];

	DWORD lineNum=0;

	// ファイルを開く
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
		// 1行読み込む
		fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
		lineLng = _tcslen(buf);
		if(lineLng > 0 && buf[0] != _T('\n')){
			isEnd = false;
			for(int i=0; i<lineLng && !isEnd; i++){
				if(buf[i] != _T(' ') || buf[i] != _T('\n')){ // 改行・空白のみの列はカウントしない
					lineNum++;
					isEnd = true; // ループから脱出
					break;
				}
			}
		}
	}

	// 正しく読み込めた行数を返す
	return lineNum;
}

WORD CsvReader::Read(){
	// 一時的にファイルを読み込んでおくバッファ
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];
	WORD bufLng;	

	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(fin.eof()){
		return CSV_READ_END;
	}
	if(!fin){
		return CSV_READ_ERROR;
	}

	// 現在のファイル読み込み位置に移動する
	fin.seekg(filePos, std::ios::beg);

	// 1行読み込む
	fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
	bufLng = _tcslen(buf);

	// ファイル位置を保存する
	filePos = fin.tellg();

	// とっととファイルを閉じる
	fin.close();

	// 読み込んだ文字列が空の場合
	if(bufLng == 0){
		valueNum = 0;
		return CSV_READ_NODATA;
	}

	WORD tmpValueNum = 0; // 現在何番目の項目に文字を入れているか
	WORD tmpValuePos = 0; // 現在の項目の文字数
	// 文字を最初から読み込んでいく
	bool isEnd = false;
	for(int i=0; i<=bufLng && !isEnd; i++){ // 末端の'\0'まで含む
		switch(buf[i]){
		case _T('\0'):
		case _T('\n'):		// 読み込みの終端
			value[tmpValueNum][tmpValuePos] = '\0';
			tmpValueNum++;
			isEnd = true;
			break;
		case _T(','):		// カンマ : 次の値へ
			value[tmpValueNum][tmpValuePos] = '\0';
			tmpValueNum++;
			tmpValuePos = 0;
			if(tmpValueNum >= CSV_MAX_COLUMN){
				isEnd = true;
			}
			break;
		case _T(' '):		// 空白 : 値の先頭であれば無視する
			if(tmpValuePos > 0){
				value[tmpValueNum][tmpValuePos] = buf[i];
				tmpValuePos++;
			}
			break;
		default:			// その他の文字 : 値を継続
			value[tmpValueNum][tmpValuePos] = buf[i];
			tmpValuePos++;
			break;
		}
	}

	// 読み込めない場合
	if(tmpValueNum == 0){
		valueNum = 0;
		return CSV_READ_NODATA;
	}

	// 行数カウントを増やす
	// ただし空行は無効
	lineNum++;
	valueNum = tmpValueNum;

	return CSV_READ_NOERROR;
}

WORD CsvReader::NextLine(LPTSTR v, WORD strLen){
	// 一時的にファイルを読み込んでおくバッファ
	TCHAR buf[CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)];
	// WORD bufLng;	

	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(fin.eof()){
		return CSV_READ_END;
	}
	if(!fin){
		return CSV_READ_ERROR;
	}

	// 現在のファイル読み込み位置に移動する
	fin.seekg(filePos, std::ios::beg);

	// 1行読み込む
	fin.getline(buf, CSV_MAX_COLUMN*(CSV_MAX_TEXT+1)-1);
	// bufLng = _tcslen(buf);
	if(v != 0){
		_tcscpy_s(v, strLen*sizeof(TCHAR), buf);
	}

	// ファイル位置を保存する
	filePos = fin.tellg();

	// とっととファイルを閉じる
	fin.close();

	// 正常な場合の戻り値は0
	return CSV_READ_NOERROR;
}

void CsvReader::Reset(){
	// ファイル名リセット
	_tcscpy_s(fileName, MAX_PATH, _T(""));

	// ファイル位置リセット
	filePos = 0;

	// データリセット
	for(int i=0; i<CSV_MAX_COLUMN; i++){
		_tcscpy_s(value[i], CSV_MAX_TEXT-1, _T(""));
	}

	// 値のリセット
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
	std::streamoff cntFilePos;	// 関数内でのファイル位置
	TCHAR tmpBuf[CSV_MAX_TEXT];

	// ファイルの位置に移動
	if(fromHead){
		cntFilePos = 0;
	}else{
		cntFilePos = filePos;
	}

	// 1行ずつ読み込み、指定された文字列を持つ行を探す
	WORD isOK=CSV_READ_NOERROR;
	bool isFound=false;
	bool matching = true;

	while(isOK==CSV_READ_NOERROR && !isFound){
		// ファイルにエラーがなく、文字列が見つかっていない限り
		isOK = NextLine(tmpBuf, CSV_MAX_TEXT); // 値をコピーする
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
		// 見つかった位置に移動
		return true;
	}else{
		// 移動しない
		return false;
	}

	return true;
}