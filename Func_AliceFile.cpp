// Func_AliceFile.cpp
#include "Func_AliceFile.h"

// このゲームのセーブデータに関する取り扱いを記述するファイル。
#include <stdio.h>
#include <fstream>
#include <vector>

#include "MyFiles.h"
#include "Game_FileHeader.h"
#include "Game_AliceInfo.h"
#include "Game_DollList.h"
#include "TempData.h"
#include "Common_Macro.h"

// ゲームデータを保存するためのグローバル変数群
extern Game_AliceInfo		g_aliceInfo;
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
	g_aliceInfo.GetCntTime();

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
	fileHeader.data.alice_mp = g_aliceInfo.data.mp;
	fileHeader.data.savedYMD = g_aliceInfo.data.savedYMD;
	fileHeader.data.savedHMS = g_aliceInfo.data.savedHMS;
	fileHeader.data.playTime = g_aliceInfo.data.playTime;

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
	Game_AliceInfo_Data aliceData = g_aliceInfo.data;
	if(file.AddObjectToFiles(
		(LPVOID)&aliceData, sizeof(Game_AliceInfo_Data),
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
	g_aliceInfo.GetCntTime(true);
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
	if(!g_aliceInfo.LoadFromBytes(pData, fileSize)){
		return false;
	}

	// 人形リストの読み込み

	return true;
}

bool NewGame(){
	// グローバル変数を全て初期化する必要がある
	g_aliceInfo = Game_AliceInfo();
	// 現在の時間情報を更新する
	g_aliceInfo.GetCntTime(true);
	// 前からあるリストを解放し、新しいリストを作成する
	g_dollList.Release();
	g_dollList = Game_DollList();
	g_temp.Reset();
	GenerateInitialDoll();
	// g_aliceInfo.data.mp = 0;
	return true;
}

void GenerateInitialDoll(){
	// g_dollList.list.In
}