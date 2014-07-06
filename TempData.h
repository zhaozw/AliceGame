#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Game_AliceDoll.h"

// sceneParamに入れられるパラメータ群
#define TEMP_PARAM_FILE_NEWGAME		0
#define TEMP_PARAM_FILE_SAVEMODE	1
#define TEMP_PARAM_FILE_LOADMODE	2

// シーン間で情報をやりとりする時に一時的に情報を管理するのに用いるクラス。
// グローバル変数g_tempとして参照される。
// セーブデータにはこの内容は含めない。
class TempData{
public:
	// 同じシーンを複数の目的で使い回す場合のフラグ変数。
	int	sceneParam;
	// 現在のファイル番号。オートセーブなどの際に用いる。リセットされない。
	// ファイル番号そのままを習得する。
	BYTE	fileIndex;
	// 名前入力ウィンドウの入力結果を受け取る。
	WORD	enteredName[MAX_ENTERNAME];
	// 人形作成・合成時にシーンをまたいで情報を保持する。
	Game_AliceDoll_Essence	dollData;
	// 敵グループID。
	// これを指定した上で戦闘シーンに遷移する。
	WORD	enemyGroup;
public:
	// コンストラクタ
	TempData();
	// 内容のリセット
	void Reset();
};

#endif // TEMPDATA_H