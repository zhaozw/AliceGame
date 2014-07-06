// Func_Windows.cpp

#include "Func_Windows.h"

DWORD GetCntYMD(){
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	return stTime.wYear*10000+stTime.wMonth*100+stTime.wDay;
}

DWORD GetCntHMS(){
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	return stTime.wHour*10000+stTime.wMinute*100+stTime.wSecond;
}
