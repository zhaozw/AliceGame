// Func_AliceFile.cpp
#include "Func_AliceFile.h"

// このゲームのセーブデータに関する取り扱いを記述するファイル。
#include <stdio.h>
#include <fstream>
#include <vector>

#include "MyFiles.h"
#include "Game_FileHeader.h"
#include "Record_AliceInfo.h"
#include "Game_DollList.h"
#include "TempData.h"
#include "Common_Macro.h"

// ゲームデータを保存するためのグローバル変数群
extern Record_AliceInfo		r_aliceInfo;
extern TempData				g_temp;
extern Game_DollList		g_dollList;

// インデックスを指定するとファイル名を返す。
bool GetSaveGameFileName(LPTSTR str, int strLength, BYTE index){
	if(index<=0 || index>MAX_SAVEFILE) return false;
	if(strLength != SIZE_SAVEFILENAME) return false;
	TCHAR fileName[SIZE_SAVEFILENAME];
	wsprintf(fileName, "dat\\savefile%02d.dat", index);
	strcpy_s(str, SIZE_SAVEFILENAME-1, fileName);
	return true;
}

// ファイルが存在するかどうかを取得する
bool GetGameFileIsExist(BYTE index){
	TCHAR fileName[SIZE_SAVEFILENAME];
	std::basic_ifstream<TCHAR> fin;
	// ファイル名を取得
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	fin.open(fileName, std::ios::in|std::ios::binary); // ifstreamをTCHARで使用する
	if(!fin){
		// ファイルが存在しない
		return false;
	}
	return true;
}

// Game_FileHeaderクラスのポインタを渡すと、
// その内容に指定したインデックスのファイルのファイルヘッダを読み込む。
bool GetGameFileHeader(Game_FileHeader* pHeader, BYTE index){
	TCHAR fileName[SIZE_SAVEFILENAME];
	// ファイル名を取得する
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// ファイルが存在するかどうか判定する
	if(!GetGameFileIsExist(index)){
		return false;
	}
	// MyFilesクラス
	MyFiles			file;
	// ファイルを開く
	if(!file.LoadFilesFromDat(fileName)){
		return false;
	}
	// 復号化
	file.EncodeFileXOR(
		SAVEFILE_INDEX_FILEHEADER, 
		_T(SAVEFILE_CODE_FILEHEADER), (WORD)strlen(_T(SAVEFILE_CODE_FILEHEADER)));
	// ポインタの取得
	LPVOID pData = file.GetFilePointerByIndex(SAVEFILE_INDEX_FILEHEADER);
	// ファイルサイズが正しいかどうかの確認
	DWORD fileSize = file.GetFileSize(SAVEFILE_INDEX_FILEHEADER);
	// データの読み込み
	if(!pHeader->LoadFromBytes(pData, fileSize)){
		return false;
	}
	return true;
}

// ゲームデータを保存する
bool SaveGame(BYTE index){
	// 現在の時間情報を更新する
	r_aliceInfo.GetCntTime();

	// ファイル名の取得
	TCHAR fileName[SIZE_SAVEFILENAME];
	// ファイル名を取得する
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// MyFilesクラス
	MyFiles			file;

	// ゲーム保存用のヘッダを作成する
	Game_FileHeader fileHeader;
	fileHeader.data.alice_mp = r_aliceInfo.data.mp;
	fileHeader.data.savedYMD = r_aliceInfo.data.savedYMD;
	fileHeader.data.savedHMS = r_aliceInfo.data.savedHMS;
	fileHeader.data.playTime = r_aliceInfo.data.playTime;

	// ファイルヘッダの保存
	if(file.AddObjectToFiles(
		(LPVOID)&fileHeader.data, sizeof(Game_FileHeader_Data),
		_T("header"), SAVEFILE_INDEX_FILEHEADER) == INDEX_ERROR){
			file.ReleaseAll();
			return false;
	}
	file.EncodeFileXOR(
		SAVEFILE_INDEX_FILEHEADER, 
		_T(SAVEFILE_CODE_FILEHEADER), (WORD)strlen(_T(SAVEFILE_CODE_FILEHEADER)));

	// アリスの情報の保存
	Record_AliceInfo_Data aliceData = r_aliceInfo.data;
	if(file.AddObjectToFiles(
		(LPVOID)&aliceData, sizeof(Record_AliceInfo_Data),
		_T("aliceinfo"), SAVEFILE_INDEX_ALICEINFO) == INDEX_ERROR){
			file.ReleaseAll();
			return false;
	}
	file.EncodeFileXOR(
		SAVEFILE_INDEX_ALICEINFO, 
		_T(SAVEFILE_CODE_ALICEINFO), (WORD)strlen(_T(SAVEFILE_CODE_ALICEINFO)));

	// 人形リストの保存

	// ファイルを書き出す
	DWORD bytesOfFile = 0;
	if(!file.SaveFilesToRawFile(fileName, true, &bytesOfFile)){
		return false;
	}
	if(bytesOfFile <= 0) return false;

	if(!file.ReleaseAll()){
		return false;
	}
	return true;
}

// ゲームデータを読み込む
bool LoadGame(BYTE index){
	// 現在の時間情報を更新する
	r_aliceInfo.GetCntTime(true);
	// ファイル名の取得
	TCHAR fileName[SIZE_SAVEFILENAME];
	// ファイルのポインタを受け取る
	LPVOID pData = NULL;
	// ファイルサイズ
	DWORD fileSize;
	// ファイル名を取得する
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// ファイルが存在するかどうか判定する
	if(!GetGameFileIsExist(index)){
		return false;
	}

	// MyFilesクラス
	MyFiles			file;

	// ファイルを開く
	if(!file.LoadFilesFromDat(fileName)){
		return false;
	}

	// ヘッダファイルは読み込む必要がない

	// アリスの情報ファイルを読み込む
	// 復号化
	file.EncodeFileXOR(
		SAVEFILE_INDEX_ALICEINFO, 
		_T(SAVEFILE_CODE_ALICEINFO), (WORD)strlen(_T(SAVEFILE_CODE_ALICEINFO)));
	// ポインタの取得
	pData = file.GetFilePointerByIndex(SAVEFILE_INDEX_ALICEINFO);
	// ファイルサイズが正しいかどうかの確認
	fileSize = file.GetFileSize(SAVEFILE_INDEX_ALICEINFO);
	if(!r_aliceInfo.LoadFromBytes(pData, fileSize)){
		return false;
	}

	// 人形リストの読み込み

	return true;
}

bool NewGame(){
	// グローバル変数を全て初期化する必要がある
	r_aliceInfo = Record_AliceInfo();
	// 現在の時間情報を更新する
	r_aliceInfo.GetCntTime(true);
	// 前からあるリストを解放し、新しいリストを作成する
	g_dollList.Release();
	g_dollList = Game_DollList();
	g_temp.Reset();
	GenerateInitialDoll();
	// r_aliceInfo.data.mp = 0;
	return true;
}

void GenerateInitialDoll(){
	// g_dollList.list.In
}

// 2014夏コミの体験版に関するクラス。
AliceFile_140816::AliceFile_140816(){
	Reset();
}

void AliceFile_140816::Reset(){
	data.firstHint = false;
	for(int n=0; n<ALICEFILE_140816_TUTORIAL; n++){
		data.tutorialBattle[n] = 0;
	}
	data.tutorialHint = false;
	for(int n=0; n<10; n++){
		data.forFuture[n] = 0;
	}
}

// 体験版のデータを保存する。
bool AliceFile_140816::Save(){
	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(ALICEFILE_140816_FILENAME,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
		return false;
	}

	// 現在のデータのコピーを取り、暗号化
	ALICEFILE_140816_DATA copiedData;
	copiedData = data;
	int dataSize = sizeof(ALICEFILE_140816_DATA)*sizeof(char);
	void* pData = static_cast<void*>(&copiedData);
	BYTE* byte_casted_data = static_cast<BYTE*>(pData);		// 上の行と合わせて無理やりバイト列に変換

	// データに対して直接排他的論理和を行う
	int pos;
	TCHAR code[ALICEFILE_140816_XORCODE_LENGTH+1];
	strcpy_s(code, ALICEFILE_140816_XORCODE_LENGTH+1, ALICEFILE_140816_XORCODE);
	TCHAR code2[ALICEFILE_140816_XORCODE2_LENGTH+1];
	strcpy_s(code2, ALICEFILE_140816_XORCODE2_LENGTH+1, ALICEFILE_140816_XORCODE2);
	for(int i=0; i<dataSize; i++){
		pos = ((i+3)%strlen(ALICEFILE_140816_XORCODE)); // ちょっとずらした位置で暗号化
		byte_casted_data[i] = byte_casted_data[i]^code[pos];
		pos = ((i+7)%strlen(ALICEFILE_140816_XORCODE2)); 
		byte_casted_data[i] = byte_casted_data[i]^code2[pos];
	}

	// 実際の書き出し
	fout.write((char*)&copiedData, dataSize);

	// 書き出し終了
	fout.close();
	return true;
}

// 体験版のデータをロードする。
bool AliceFile_140816::Load(){
	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(ALICEFILE_140816_FILENAME,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "読み込み用ファイルが開けませんでした。\n");
		return false;
	}

	// ファイルから内容を読み込む
	ALICEFILE_140816_DATA loadedData;
	int dataSize = sizeof(ALICEFILE_140816_DATA)*sizeof(char);
	fin.read((char*)&loadedData, dataSize);
	if(!fin){
		_RPTF0(_CRT_WARN, "ファイルの内容が読み込めませんでした。\n");
		return false;
	}

	// 復号
	void* pData = static_cast<void*>(&loadedData);
	BYTE* byte_casted_data = static_cast<BYTE*>(pData);		// 上の行と合わせて無理やりバイト列に変換
	// データに対して直接排他的論理和を行う
	int pos;
	TCHAR code[ALICEFILE_140816_XORCODE_LENGTH+1];
	strcpy_s(code, ALICEFILE_140816_XORCODE_LENGTH+1, ALICEFILE_140816_XORCODE);
	TCHAR code2[ALICEFILE_140816_XORCODE2_LENGTH+1];
	strcpy_s(code2, ALICEFILE_140816_XORCODE2_LENGTH+1, ALICEFILE_140816_XORCODE2);
	for(int i=0; i<dataSize; i++){
		pos = ((i+3)%strlen(ALICEFILE_140816_XORCODE)); // ちょっとずらした位置で暗号化
		byte_casted_data[i] = byte_casted_data[i]^code[pos];
		pos = ((i+7)%strlen(ALICEFILE_140816_XORCODE2)); 
		byte_casted_data[i] = byte_casted_data[i]^code2[pos];
	}

	// 復号後のデータをコピーする
	data = loadedData;

	// 読み込み終了
	fin.close();
	return true;
}
