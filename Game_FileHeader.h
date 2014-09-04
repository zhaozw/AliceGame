#ifndef GAME_FILEHEADER_H
#define GAME_FILEHEADER_H

#include <Windows.h>
#include "Record_AliceInfo.h"

struct Game_FileHeader_Data{
	int		playTime;		// プレイ時間(秒)
	WORD	alice_mp;		// アリスの魔力
	DWORD	savedYMD;		// セーブした年・月・日
	DWORD	savedHMS;		// セーブした時間・分・秒

	Game_FileHeader_Data(){
		playTime = 0;
		alice_mp = MAX_MP;
		savedYMD = 0;
		savedHMS = 0;
	}
};

// ファイルのロード時などに使用するファイルのヘッダデータを扱うクラス。
// セーブファイルの先頭に保存され、Scene_Fileなどで呼び出される。
class Game_FileHeader{
public:
	Game_FileHeader_Data		data;
public:
	// コンストラクタ
	Game_FileHeader();
	// バイト列からデータに内容をコピーする
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);
};

#endif // GAME_FILEHEADER_H