#ifndef FUNC_WINDOWS_H
#define FUNC_WINDOWS_H

#include <Windows.h>

// Windowsの機能を使う関数。

// 現在の時間をYYYYMMDDの形で取得する。
DWORD GetCntYMD();

// 現在の時間をHHMMSSの形で取得する。
DWORD GetCntHMS();

#endif // FUNC_WINDOWS_H