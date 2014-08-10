#ifndef SOUND_H
#define SOUND_H

#include <Windows.h>

class Sound;

// ゲームで使用するBGMの最大数を定義する。
#define MYGAME_MAX_BGM	10

// ゲームで使用するBGMのIDを列挙する。
#define BGM_DUMMY		0
#define BGM_MENU		1
#define BGM_BATTLE		2

// ゲームで使用するSEの最大数を定義する。
#define MYGAME_MAX_SE	30

// ゲームで使用するSEのIDを列挙する。
#define SE_DUMMY		0

//==================================================
// BGMクラス
// 
// 画像のハンドルをまとめて保持するグローバル変数。

class BGM{
	friend class Sound;
	int handle; // 曲のハンドル
	int loopPos; // ループ位置
	bool noLoop;
	int playPos; // 曲の現在の再生位置
public:
	// コンストラクタ
	BGM();
	int GetHandle(){ return handle; };
	int GetLoopPos(){ return loopPos; };
};

//==================================================
// Soundクラス
// 
// 画像のハンドルをまとめて保持するグローバル変数。
// グローバル変数g_soundから参照される。
// 

class Sound{
private:
	// BGM群を納めるハンドル。
	BGM	bgm[MYGAME_MAX_BGM];
	// SE群を納めるハンドル。
	int se[MYGAME_MAX_SE];
public:
	// コンストラクタ。
	// 全てのハンドルに-1を代入する。
	Sound();

	// ロード。
	// 失敗したらfalseを返す。
	bool LoadMusic();
	bool LoadSound();

	// BGMを、ID、ファイル名、ループ位置を指定して読み込む。
	bool LoadBGM(WORD id, LPTSTR fileName, int loopPos, bool noLoop=false);

	// BGMの再生を行う。
	bool PlayBGM(WORD bgmID, bool recall);

	// BGMの再生を止める。
	void StopBGM(WORD bgmID);

	// BGMの再生を一時的に停止させる。
	

	// 全BGMの再生を止める。
	void StopAllBGM();

	// BGMのボリュームを変更する。
	void SetVolumeBGM(WORD bgmID,int param);

	// SEの再生を行う。
	bool PlaySE(WORD seID, float volRate, bool reCall=true, bool stop=false);

};

bool CallMusic(int hMsc, bool reset, bool noLoop);

bool CallSound(int hSnd, float volRate, bool reCall, bool stop);

long CalcDB(int sound_val); 



#endif // SOUND_H