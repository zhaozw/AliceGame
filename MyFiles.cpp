// MyFiles.cpp

#include "MyFiles.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Common_Macro.h"

MyFiles::MyFiles(){
	fileNum = 0;
}

MyFiles::~MyFiles(){
}

WORD MyFiles::GetEmptyIndex(){
	for(WORD i=0; i<MAX_FILES; i++){
		if(CheckIndexIsEmpty(i)){ // 使用を示すビットが0の時
			if(fileInfo[i].pointer){
				_RPTF0(_CRT_WARN, "空のファイルにメモリが割り当てられています。\n");
				return INDEX_ERROR;
			}
			return i;
		}
	}
	_RPTF0(_CRT_WARN, "利用できる空のファイルがありません。\n");
	return INDEX_ERROR;
}

bool MyFiles::CheckIndexIsEmpty(WORD index){
	if(!IndexEnabled(index)) return false;
	return (fileInfo[index].flags & MYFILE_FLAG_USED) == 0x00;
}

LPVOID MyFiles::GetFilePointerByIndex(WORD index){
	if(!IndexEnabled(index)) return NULL;
	if(CheckIndexIsEmpty(index)) return NULL;
	return fileInfo[index].pointer; 
};


WORD MyFiles::GetNamedIndex(LPTSTR fileName, WORD fileNameLength){
	WORD length = fileNameLength;
	if(length == 0) length = _tcslen(fileName);
	bool isOK = true;
	for(int i=0; i<MAX_FILEPATH; i++){
		isOK = true;
		for(int j=0; j<length&&isOK; j++){
			if(fileName[j] != fileInfo[i].name[j]){
				// 名前が一致しない
				isOK = false;
			}
		}
		if(isOK &&
			fileInfo[i].name[length] == _T('\0')){
				// 名前が完全に一致した
				return i;
		}
	}
	return INDEX_ERROR;
}

void MyFiles::SetFileName(int index, LPTSTR fileName){
	for(int i=0; i<MAX_FILEPATH; i++){
		fileInfo[index].name[i] = _T('\0'); // 空文字で初期化する
	}
	_tcscpy_s(fileInfo[index].name, MAX_FILEPATH-1, fileName);	// ファイル名

	// 空文字で埋める！
	for(int i=_tcslen(fileInfo[index].name); i<MAX_FILEPATH; i++){
		fileInfo[index].name[i] = _T('\0'); // 空文字で初期化する
	}
}

void MyFiles::SetFileFlags(int index, WORD flag){
	fileInfo[index].flags |= flag;
}

bool MyFiles::InitializePointer(int index, DWORD size){
	// ファイルの内容をメモリ上に全て読み込む
	fileInfo[index].pointer = VirtualAlloc(NULL,
					size,
					MEM_COMMIT,
					PAGE_READWRITE);
	if(!fileInfo[index].pointer){ // エラーの場合はNULLが代入されている
		_RPTF0(_CRT_WARN, "VirtualAllocでエラーが発生しました。\n");
		return false;
	}
	return true;
}

bool MyFiles::LoadFilesFromTxt(LPTSTR fileName){
	if(fileNum > 0){
		ForceReleaseAll();
	}

	// テキストファイルの読み込みにはifstreamクラスを使用する
	// ファイル名を格納する
	TCHAR fileNames[MAX_FILES][MAX_PATH]; 

	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName); // ifstreamをTCHARで使用する
	if(!fin){
		// ファイルが存在しない
		_RPTF1(_CRT_WARN, "ファイル %s を開けません。\n", fileName);
		return false;
	}

	int count = 0;

	// ファイルを読み込む
	while(count < MAX_FILES && !fin.eof()){ // ファイルの最後まで読み込む
		fin.getline(fileNames[count], MAX_FILEPATH-1); // 1行目。コメント。
		if(_tcslen(fileNames[count]) <= 0){ // 空行は無視する
			continue;
		}
		_RPTF1(_CRT_WARN, "ファイル %s を追加リストに加えました。\n",
			fileNames[count]);
		count++;
	}
	fin.close();
	fin.clear();

	// ファイルの内容を読み込む
	// 各ファイルの読み込みには

	bool isOK = true;

	for(int i=0; i<count && isOK; i++){
		if(AddFileToFiles(fileNames[i], fileNames[i]) == -1){
			_RPTF1(_CRT_WARN, "ファイル %s が追加出来ませんでした。\n",
				fileNames[i]);
			isOK = false;
		}else{ // 正常な読み込みに成功
			_RPTF1(_CRT_WARN, "ファイル %s を追加しました。\n",
				fileNames[i]);
		}
	}

	if(!isOK){ // 何らかのエラーが出た場合はメモリを解放してfalseを返す
		ForceReleaseAll();
		return false;
	}

	return true;
}

bool MyFiles::LoadFilesFromDat(LPTSTR fileName){
	if(fileNum > 0){
		ForceReleaseAll();
	}

	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in|std::ios::binary); // ifstreamをTCHARで使用する
	if(!fin){
		// ファイルが存在しない
		_RPTF1(_CRT_WARN, "ファイル %s を開けません。\n", fileName);
		return false;
	}

	// データに含まれるファイル数を読み込む
	WORD dataFileNum;
	fin.read((char*)&dataFileNum, sizeof(WORD));

	if(dataFileNum > MAX_FILES || dataFileNum == 0){
		_RPTF0(_CRT_WARN, "ファイル数が正しくありません。\n");
		return false;
	}

	// ヘッダーを読み込む
	for(int i=0; i<dataFileNum; i++){
		// 頭から順に入れていく
		// ここではエラーがあった場合即座にfalseを返す

		// ファイル名
		fin.read((char*)fileInfo[i].name, sizeof(char)*MAX_FILEPATH);
		// ファイルサイズ
		fin.read((char*)&fileInfo[i].size, sizeof(DWORD));

		// 何かエラーがあった場合は即座に抜ける
		if(!fin.eof() && fin.fail()){
			ForceReleaseAll();
			return false;
		}
	}

	// データ本体を読み込む
	for(int i=0; i<dataFileNum; i++){
		if(!InitializePointer(i, fileInfo[i].size)){
			ForceReleaseAll();
			return false;
		}
		fin.read((char*)fileInfo[i].pointer, (sizeof(char))*fileInfo[i].size);
		// 何かエラーがあった場合は即座に抜ける
		if(!fin.eof() && fin.fail()){
			ForceReleaseAll();
			return false;
		}

		// ファイルが正しく読み込まれたためフラグを追加する
		ResetFileFlags(i);
		SetFileFlags(i, MYFILE_FLAG_USED);

		_RPTF2(_CRT_WARN, "ファイル %s をインデックス %d に加えました。\n",
			fileInfo[i].name, i);
		_RPTF1(_CRT_WARN, "ファイルサイズ : %d Bytes\n",
			fileInfo[i].size);
	}

	fileNum = dataFileNum;
	_RPTF1(_CRT_WARN, "ファイル %s を正しく読み込みました。\n", fileName);


	return true;
}

WORD MyFiles::AddObjectToFiles(void *pointer, DWORD size, LPTSTR objName, int i){
	// falseなのは開放を行わないため
	return AddBytesToFiles(pointer, size, objName, false, i);
}

WORD MyFiles::AddBytesToFiles(void* pointer, DWORD size, 
	LPTSTR objName, bool needToRelease, int i){
	// 追加する位置
	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // 空であるインデックスを取得する
	}else{
		index = i;
		// 使用されていないかどうかのチェック
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}
	if(index == INDEX_ERROR){
		return INDEX_ERROR;
	}

	// ポインタが空でないか
	if(pointer == NULL) return INDEX_ERROR;

	// ポインタを元にデータを割り当てる
	fileInfo[index].pointer = pointer;
	fileInfo[index].size = size;
	SetFileName(index, objName);
	fileInfo[index].flags = 0;
	SetFileFlags(index, MYFILE_FLAG_USED);
	if(!needToRelease){
		SetFileFlags(index, MYFILE_FLAG_COPYED);
	}

	fileNum++;
	return index;
}

WORD MyFiles::AddFileToFiles(LPTSTR fileName, LPTSTR newName, WORD i, bool useNewName){
	std::basic_ifstream<TCHAR> fin;
	DWORD tmpFileSize = 0;

	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // 空であるインデックスを取得する
	}else{
		index = i;
		// 使用されていないかどうかのチェック
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}

	if(index == INDEX_ERROR){
		_RPTF0(_CRT_WARN, "インデックスの取得に失敗しました。\n");
		return INDEX_ERROR;
	}else{
		_RPTF2(_CRT_WARN, "インデックス%dに%sを追加します。\n", index, fileName);
	}

	// ファイルを開く
	fin.open(fileName, std::ios::in|std::ios::binary);
	if(!fin){
		// ファイルが存在しない
		_RPTF1(_CRT_WARN, "ファイル %s を開けません。\n", fileName);
		return INDEX_ERROR;
	}

	// ファイルのサイズを取得する
	tmpFileSize = (DWORD)fin.seekg(0, std::ios::end).tellg();
	fin.seekg(0, std::ios::beg); // ポインタ位置を最初に戻す
	if(tmpFileSize == 0){
		_RPTF0(_CRT_WARN, "ファイルサイズが0です。\n");
		return INDEX_ERROR;
	}

	// メモリの割り当て
	if(!InitializePointer(index, tmpFileSize)){
		return INDEX_ERROR;
	}

	// ファイル全体を読み込む
	fin.read((char*)fileInfo[index].pointer, tmpFileSize);

	// エラーチェック
	if(fin.fail() || fin.bad()){
		_RPTF0(_CRT_WARN, "ファイルの読み込み時にエラーが発生しました。\n");
		return INDEX_ERROR;
	}

	// ファイルヘッダに情報を格納する
	SetFileName(index, (useNewName?newName:fileName));
	fileInfo[index].size = tmpFileSize;
	ResetFileFlags(index);
	SetFileFlags(index, MYFILE_FLAG_USED);
	fNeedToRelease = true;	// 全体としてもデータが読み込まれた
	fileNum++; // 正常に読み込まれたファイルの追加

	// ファイルのリフレッシュ
	fin.close();
	fin.clear();

	return index; // 格納されたファイル番号
}

WORD MyFiles::AddFilePartToFiles(LPTSTR fileName, LPTSTR newName,
		DWORD offset, DWORD length, WORD i, bool useNewName){
	std::basic_ifstream<TCHAR> fin;
	DWORD tmpFileSize = 0;

	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // 空であるインデックスを取得する
	}else{
		index = i;
		// 使用されていないかどうかのチェック
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}

	if(index == INDEX_ERROR){
		_RPTF0(_CRT_WARN, "インデックスの取得に失敗しました。\n");
		return INDEX_ERROR;
	}else{
		_RPTF2(_CRT_WARN, "インデックス%dに%sを追加します。\n", index, fileName);
	}

	// ファイルを開く
	fin.open(fileName, std::ios::in|std::ios::binary);
	if(!fin){
		// ファイルが存在しない
		_RPTF1(_CRT_WARN, "ファイル %s を開けません。\n", fileName);
		return INDEX_ERROR;
	}

	// ファイルのサイズを取得する
	DWORD fileLast = (DWORD)fin.seekg(0, std::ios::end).tellg();
	if(fileLast < offset+length){
		_RPTF0(_CRT_WARN, "必要なファイルサイズがありません。\n");
		return INDEX_ERROR;
	}
	
	// メモリの割り当て
	if(!InitializePointer(index, length)){
		return INDEX_ERROR;
	}

	// ポインタの位置をオフセットに合わせる
	fin.seekg(offset, std::ios::beg);
	// ファイルの一部を読み込む
	fin.read((char*)fileInfo[index].pointer, length);

	// エラーチェック
	if(fin.fail() || fin.bad()){
		_RPTF0(_CRT_WARN, "ファイルの読み込み時にエラーが発生しました。\n");
		return INDEX_ERROR;
	}

	// ファイルヘッダに情報を格納する
	SetFileName(index, (useNewName?newName:fileName));
	fileInfo[index].size = length;
	ResetFileFlags(index);
	SetFileFlags(index, MYFILE_FLAG_USED);
	fNeedToRelease = true;	// 全体としてもデータが読み込まれた
	fileNum++; // 正常に読み込まれたファイルの追加

	// ファイルのリフレッシュ
	fin.close();
	fin.clear();

	return index; // 格納されたファイル番号
}

bool MyFiles::SaveFilesToRawFile(LPTSTR fileName, bool hideName, DWORD* sizeInBytes){
	*sizeInBytes = 0;

	// 現在読み込まれているファイル数を記録する
	if(fileNum <= 0){
		*sizeInBytes = 0;
		return true;
	}

	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(fileName, std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
		*sizeInBytes = 0;
		return false;
	}

	// ファイル数を記録する(WORD型)
	fout.write((char*)&fileNum, sizeof(WORD));
	*sizeInBytes += sizeof(WORD);

	// 各ファイルのヘッダを記録する
	// (ファイル名とファイルサイズ)
	TCHAR tmpName[MAX_FILEPATH];
	int cntFileNum = 0;
	for(int i=0; i<MAX_FILES && cntFileNum<fileNum; i++){
		// 必ずしもインデックス順に並んでいるわけではないので
		if((fileInfo[i].flags & MYFILE_FLAG_USED) == 0x00) continue;
		if((fileInfo[i].flags & MYFILE_FLAG_PROTECTED) != 0x00){
			cntFileNum++; // カウンタは増加させるが書き出さない
			continue;
		}

		// ファイルが使用されている場合
		if(!hideName){
			_tcscpy_s(tmpName, sizeof(TCHAR)*(MAX_FILEPATH-1), fileInfo[i].name);
		}else{
			_tcscpy_s(tmpName, sizeof(TCHAR)*(MAX_FILEPATH-1), _T("dummy.dat"));
		}
		// 実際の書き出し
		fout.write((char*)tmpName, sizeof(TCHAR)*MAX_FILEPATH);
		// ファイルサイズの書き出し
		fout.write((char*)&fileInfo[i].size, sizeof(DWORD));
		*sizeInBytes += (sizeof(TCHAR)*MAX_FILEPATH + sizeof(DWORD));
		_RPTF2(_CRT_WARN, "ファイルを連結します : %s, %d bytes\n", 
			tmpName, fileInfo[i].size);
		// カウンタの増加
		cntFileNum++;
	}

	if(cntFileNum < fileNum){ // 書き出せたファイルの数が予想と異なる
		_RPTF0(_CRT_WARN, "利用可能なファイル数が予想と異なります。\n");
		fout.close();
		*sizeInBytes = 0;
		return false;
	}

	_RPTF0(_CRT_WARN, "ファイルヘッダの書き出しを正しく行いました。\n");
	_RPTF1(_CRT_WARN, "合計サイズ : %d bytes\n", 
		*sizeInBytes);

	// 実際のデータの書き出し
	cntFileNum = 0;
	for(int i=0; i<MAX_FILES && cntFileNum<fileNum; i++){
		// 必ずしもインデックス順に並んでいるわけではないので
		if((fileInfo[i].flags & MYFILE_FLAG_USED) == 0x00) continue;
		if((fileInfo[i].flags & MYFILE_FLAG_PROTECTED) != 0x00){
			cntFileNum++; // カウンタは増加させるが書き出さない
			continue;
		}

		// ファイルが存在する場合は書き出す
		fout.write((char*)fileInfo[i].pointer, fileInfo[i].size); 

		// 書き出したバイト数の増加
		*sizeInBytes += fileInfo[i].size;

		_RPTF2(_CRT_WARN, "ファイルを連結しました : %s, %d bytes\n", 
			fileInfo[i].name, fileInfo[i].size);
		_RPTF1(_CRT_WARN, "合計サイズ : %d bytes\n", 
			*sizeInBytes);

		// カウンタの増加
		cntFileNum++;
	}

	if(cntFileNum < fileNum){ // 書き出せたファイルの数が予想と異なる
		_RPTF0(_CRT_WARN, "予想されたファイル数を書き出せないまま終了しました。\n");
		fout.close();
		return false;
	}

	// 終了の告知
	_RPTF1(_CRT_WARN, "ファイル %s へ書き出しを正しく終了しました。\n", fileName);
	_RPTF1(_CRT_WARN, "合計サイズ : %d bytes\n", *sizeInBytes);

	// 書き出し終了
	fout.close();

	return true;
}

bool MyFiles::SaveFileToRawFileByIndex(int index, LPTSTR outName, bool useRawName){
	if(index >= MAX_FILES) return false; // インデックスが正しくない

	// 実際に書き出すファイル名の取得
	TCHAR realOutName[MAX_FILEPATH];
	if(useRawName){
		_tcscpy_s(realOutName, MAX_FILEPATH-1, fileInfo[index].name);
	}else{
		_tcscpy_s(realOutName, MAX_FILEPATH-1, outName);
	}

	// インデックスのデータを書き出す

	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(realOutName, std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルのオープンに失敗しました。\n");
		return false;
	}

	// ファイルが使用可能かのチェック
	if((fileInfo[index].flags & MYFILE_FLAG_USED) == 0){
		_RPTF1(_CRT_WARN, "インデックス%dのファイルは使われていません。\n", index);
		return false;
	}

	// データを書き出す
	fout.write((char*)fileInfo[index].pointer, fileInfo[index].size);
	_RPTF1(_CRT_WARN, "ファイル %s を正しく書き出しました。\n", realOutName);
	_RPTF1(_CRT_WARN, "書き出したバイト数 : %d Bytes\n", fileInfo[index].size);

	// ファイルを閉じる
	fout.close();


	return true;
	
}

bool MyFiles::SaveFileToRawFileByName(LPTSTR searchName, LPTSTR outName, bool useRawName){
	int index = GetNamedIndex(searchName);
	if(index == INDEX_ERROR){
		return false;
	}

	return SaveFileToRawFileByIndex(index, outName, useRawName);
}

bool MyFiles::EncodeFileXOR(WORD index, LPTSTR code, WORD codeLength){
	WORD pos;
	// ファイルが使用可能かどうかのチェック
	if(index >= MAX_FILES) return false; // インデックスが正しくない
	if(CheckIndexIsEmpty(index)){
		_RPTF0(_CRT_WARN, "指定されたインデックスのファイルは使用されていません。\n");
		return false;
	}

	// 無理矢理排他的論理和が使える形に変更する
	BYTE* b = static_cast<BYTE*>(fileInfo[index].pointer);

	// 実際の排他的論理和を行う
	for(DWORD i=0; i<fileInfo[index].size; i++){
		pos = ((i+17)%codeLength); // ちょっとずらした位置を暗号化
		b[i] = b[i]^code[pos];
	}
	return true;
}

bool MyFiles::CompareFiles(WORD index, WORD index2){
	// ファイルサイズの比較
	if(index >= MAX_FILES) return false; // インデックスが正しくない
	if(index2 >= MAX_FILES) return false; // インデックスが正しくない
	if(fileInfo[index].size != fileInfo[index2].size) return false;

	// 無理矢理排他的論理和が使える形に変更する
	BYTE* b = static_cast<BYTE*>(fileInfo[index].pointer);
	BYTE* b2 = static_cast<BYTE*>(fileInfo[index2].pointer);

	// 実際の排他的論理和を行う
	for(DWORD i=0; i<fileInfo[index].size; i++){
		if(b[i] != b2[i]) return false;
	}

	// 最後まで一致した場合はtrueを返す
	return true;
}

bool MyFiles::Release(int index){
	if(fNeedToRelease) return ForceRelease(index, true);
	return true;
}

bool MyFiles::ReleaseAll(){
	if(fNeedToRelease) return ForceReleaseAll(true);
	return true;
}

bool MyFiles::ForceRelease(int index, bool checkUsed){
	if(!checkUsed || ((fileInfo[index].flags & MYFILE_FLAG_USED) != 0x00)){
		if((fileInfo[index].flags & MYFILE_FLAG_COPYED) == 0x00){ 
			// コピーされたものである場合は解放しない
			VirtualFree(fileInfo[index].pointer, fileInfo[index].size, 
				MEM_DECOMMIT);
			fileInfo[index].flags = 0x00;
			fileInfo[index].pointer = NULL;
			SetFileName(index, _T(""));
			fileInfo[index].size = 0;
			// SAFE_DELETE(fileInfo[index].pointer);
		}
	}
	return true;
}

bool MyFiles::ForceReleaseAll(bool checkUsed){
	for(int i=0; i<MAX_FILES; i++){ // 全ファイルのデータを解放
		ForceRelease(i, checkUsed);
	}
	fileNum = 0;
	return true;
}