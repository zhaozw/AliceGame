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
	// ������������v���C���Ԃ��v�Z���A���Z����
	DWORD addPlayTime = cntTime - lastSavedWinTime; // �~���b
	addPlayTime /= 1000; // �b
	data.playTime += addPlayTime; // �b���ŉ��Z
	lastSavedWinTime = cntTime;
}