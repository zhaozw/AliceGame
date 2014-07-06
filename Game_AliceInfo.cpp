// Game_AliceInfo.cpp

#include "Game_AliceInfo.h"
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include "Func_Windows.h"

Game_AliceInfo::Game_AliceInfo():data(){

}

bool Game_AliceInfo::LoadFromBytes(LPVOID pBytes, DWORD fileSize){
	if(fileSize != sizeof(data)){
		return false;
	}
	if(memcpy_s((void*)&data, fileSize, (void*)pBytes, fileSize) != 0){
		return false;
	}
	return true;
}

void Game_AliceInfo::GetCntTime(bool load){
	if(load){
		lastSavedWinTime = GetTickCount();
	}
	data.savedYMD = GetCntYMD();
	data.savedHMS = GetCntHMS();
	DWORD cntTime = GetTickCount();
	// 差し引きからプレイ時間を計算し、加算する
	DWORD addPlayTime = cntTime - lastSavedWinTime; // ミリ秒
	addPlayTime /= 1000; // 秒
	data.playTime += addPlayTime; // 秒数で加算
	lastSavedWinTime = cntTime;
}