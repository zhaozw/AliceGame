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
	// ·‚µˆø‚«‚©‚çƒvƒŒƒCŠÔ‚ğŒvZ‚µA‰ÁZ‚·‚é
	DWORD addPlayTime = cntTime - lastSavedWinTime; // ƒ~ƒŠ•b
	addPlayTime /= 1000; // •b
	data.playTime += addPlayTime; // •b”‚Å‰ÁZ
	lastSavedWinTime = cntTime;
}