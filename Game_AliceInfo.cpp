// Game_AliceInfo.cpp

#include "Game_AliceInfo.h"
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include "Func_Windows.h"

Game_AliceInfo::Game_AliceInfo() : data(){

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

bool Game_AliceInfo::AddMP(int p){
	if(p < 0) return SubMP(-p);
	bool result = true;
	if(data.mp + p > data.maxMP) result = false;
	data.mp = min(data.maxMP, data.mp+p);
	return result;
}

bool Game_AliceInfo::SubMP(int p){
	if(p < 0) return AddMP(-p);
	bool result = true;
	if(data.mp < p) result = false;
	data.mp = max(0, data.mp-p);
	return result;
}
