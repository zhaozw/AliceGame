#ifndef CONFIG_H
#define CONFIG_H

#include <Windows.h>
#include "Static_Game.h"

//========================================
// コンフィグに関する定数

// ウィンドウサイズの列挙
#define WNDSIZE_W0			320
#define WNDSIZE_H0			240
#define WNDSIZE_W1			512
#define WNDSIZE_H1			384
#define WNDSIZE_W2			640
#define WNDSIZE_H2			480
#define WNDSIZE_W3			800
#define WNDSIZE_H3			600
#define WNDSIZE_W4			960
#define WNDSIZE_H4			720

// デフォルトのウィンドウサイズ
#define DEF_WNDSIZE			2
#define DEF_SCREENTYPE		2
#define DEF_WND_WIDTH		(WND_WIDTH)
#define DEF_WND_HEIGHT		(WND_HEIGHT)
#define DEF_SCRN_WIDTH		640
#define DEF_SCRN_HEIGHT		480

#define MAX_VOLUME			100
#define DEF_VOLUME_SE		100
#define DEF_VOLUME_BGM		80

//========================================
// Configクラス
// ゲーム全体に関わる設定を扱うクラス。
// 主にオプションで変更可能な情報を管理する。
// iniファイルを直接いじることも出来るが、ロードの際に
// 値をチェックするため不正な値は入れられない。
// 
class Config{
	//========================================
	// 変数
public:
	//=========================================
	// 画面設定関連
	bool	fullScreen;	// フルスクリーンの時はtrue。
						// コンフィグでは直接指定しない。
	int		windowWidth; // ウィンドウモードでの描画解像度
	int		windowHeight;
	int		screenWidth; // フルスクリーン時の描画解像度。
	int		screenHeight;
	TCHAR	windowSize; // ウィンドウサイズを指定するID。
							// 0 : 320×240
							// 1 : 512×384
							// 2 : 640×480
							// 3 : 800×600(デフォルト)
							// 4 : 960×720
	TCHAR	screenType; // ゲーム開始時の設定。
						// 0 : 毎回選択する。
						// 1 : フルスクリーン。
						// 2 : ウィンドウモード。

	// 音量関連
	unsigned char SE;				// 0～100で指定。効果音の音量を設定する。
	unsigned char BGM;				// 0～100で指定。BGMの音量を設定する。

	// コマ落ち・処理落ちの設定
	bool skipFrame;

	//========================================
	// 関数
	Config();

	bool SetScreenMode();	// フルスクリーン時の画面モードを調整
	void SetWindowSize();	// ウィンドウサイズの値を具体的な値に変換する。
	bool LoadConfig();
	bool SaveConfig();
};

#endif // CONFIG_H