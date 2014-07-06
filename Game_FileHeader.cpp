// Game_FileHeader.cpp

#include "Game_FileHeader.h"
#include "Static_AliceInfo.h"

Game_FileHeader::Game_FileHeader():data(){
}

bool Game_FileHeader::LoadFromBytes(LPVOID pBytes, DWORD fileSize){
	if(fileSize != sizeof(data)){
		return false;
	}
	if(memcpy_s((void*)&data, sizeof(data), (void*)pBytes, fileSize) != 0){
		return false;
	}
	return true;
}