// Config.cpp

#include "Config.h"
#include "Static_Game.h"
#include <DxLib.h>

Config::Config(){
		fullScreen = false; // フルスクリーンOFF
		skipFrame = false;

		SE		= DEF_VOLUME_SE; // 効果音 100%
		BGM		= DEF_VOLUME_BGM; // BGM 80%

		windowSize = DEF_WNDSIZE;		// デフォルトのウィンドウサイズ
		screenType = DEF_SCREENTYPE;	// 毎回確認する

		windowWidth = DEF_WND_WIDTH;
		windowHeight = DEF_WND_HEIGHT;
		screenWidth = DEF_SCRN_WIDTH;
		screenHeight = DEF_SCRN_HEIGHT;
}

bool Config::SetScreenMode(){
	// ウィンドウサイズを変更すると共に、変更に成功したウィンドウのサイズを取得する
	// フルスクリーンの場合、成功した値をwindowWidth, windowHeightに代入する。
	if(!fullScreen){
		if(SetGraphMode(windowWidth, windowHeight, 32) != DX_CHANGESCREEN_OK){	// 画面サイズの変更
			if(SetGraphMode(640, 480, 32) != DX_CHANGESCREEN_OK){	// 画面サイズの変更
				if(SetGraphMode(windowWidth, windowHeight, 16) != DX_CHANGESCREEN_OK){
					if(SetGraphMode(640, 480, 16) != DX_CHANGESCREEN_OK){
						if(SetGraphMode(windowWidth, windowHeight, 8) != DX_CHANGESCREEN_OK){
							if(SetGraphMode(640, 480, 8) != DX_CHANGESCREEN_OK){
								return false;
							}else{
								windowWidth = 640;
								windowHeight = 480;
							}
						}
					}else{
						windowWidth = 640;
						windowHeight = 480;
					}
				}
			}else{
				windowWidth = 640;
				windowHeight = 480;
			}
		}
	}else{
		if(SetGraphMode(screenWidth, screenHeight, 32) != DX_CHANGESCREEN_OK){	// 画面サイズの変更
			if(SetGraphMode(screenWidth, screenHeight, 16) != DX_CHANGESCREEN_OK){
				if(SetGraphMode(screenWidth, screenHeight, 8) != DX_CHANGESCREEN_OK) return false;
			}
		}
		windowWidth = screenWidth;
		windowHeight = screenHeight;
	}

	// スクリーンモードの変更
	if(ChangeWindowMode(!fullScreen) != DX_CHANGESCREEN_OK){
		MessageBox(NULL, 
			TEXT("ウィンドウモードの変更に失敗しました。\n解像度や色数が対応していない可能性があります。"),
			TEXT(""), MB_OK);
	}
	return true;
}

bool Config::LoadConfig(){
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	int bufInt;
	//==========================================
	// ファイルの呼び出し

	// ファイル名を取得
	// iniファイルからコンフィグ情報を読み出す。
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	bool result = false;
	bool kresult = true;

	do{ // エラーチェック
		// ウィンドウサイズを取得
		GetPrivateProfileString(TEXT("config"), TEXT("windowSize"),
			TEXT("-1"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= -1 || bufInt >= 5){
			windowSize = 3;
			break;
		}
		windowSize = bufInt;

		// ウィンドウモードを取得
		GetPrivateProfileString(TEXT("config"), TEXT("screenType"),
			TEXT("-1"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= -1 || bufInt >= 3){
			screenType = 0;
			break;
		}
		screenType = bufInt;

		// SEの音量
		GetPrivateProfileString(TEXT("config"), TEXT("SE"),
			TEXT("Error"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= 0 || bufInt >= MAX_VOLUME){
			SE = DEF_VOLUME_SE;
			break;
		}else{
			SE = bufInt;
		}

		// BGMの音量
		// エラーの場合は鳴らす
		GetPrivateProfileString(TEXT("config"), TEXT("BGM"),
			TEXT("Error"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= 0 || bufInt >= MAX_VOLUME){
			SE = DEF_VOLUME_BGM;
			break;
		}else{
			SE = bufInt;
		}
		result = true; // エラーなくここまで来た場合


	}while(0);

	// フルスクリーンかどうかの判定
	int iMsg;
	switch(screenType){
		case 0: // 選択
			iMsg = MessageBox(NULL, 
			"フルスクリーンで起動しますか？", "起動オプション",
			MB_YESNO | MB_ICONQUESTION);
			fullScreen = (iMsg == IDYES);
			break;
		case 1: // フルスクリーン
			fullScreen = true;
			break;
		case 2: // ウィンドウ
			fullScreen = false;
			break;
	}

	// 初期ファイルに不備があった場合は設定を保存し、メッセージを出す
	if(!result){
		if(!SaveConfig()) return false;
#ifdef MYGAME_CALL_DIALOG_OPTION
		MessageBox(NULL, "設定はオプションから変更できます。", "起動オプション", MB_OK);
#endif // MYGAME_CALL_DIALOG_OPTION
	}

	// ウィンドウサイズの設定
	SetWindowSize();

	return true;
}

void Config::SetWindowSize(){
	// ウィンドウサイズを換算
	switch(windowSize){
		case 0:
			windowWidth = WNDSIZE_W0;
			windowHeight = WNDSIZE_H0;
			break;
		case 1:
			windowWidth = WNDSIZE_W1;
			windowHeight = WNDSIZE_H1;
			break;
		case 2:
			windowWidth = WNDSIZE_W2;
			windowHeight = WNDSIZE_H2;
			break;
		case 3:
			windowWidth = WNDSIZE_W3;
			windowHeight = WNDSIZE_H3;
			break;
		case 4:
			windowWidth = WNDSIZE_W4;
			windowHeight = WNDSIZE_H4;
			break;
	}
}

bool Config::SaveConfig(){
	//==========================================
	// ファイルの作成
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];

	// ファイル名を取得
	// iniファイルからコンフィグ情報を読み出す。
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	// ウィンドウサイズ
	wsprintf(buf, "%d", windowSize);
	WritePrivateProfileString(TEXT("config"), TEXT("windowSize"), buf, ini_file);
	// ウィンドウタイプ
	wsprintf(buf, "%d", screenType);
	WritePrivateProfileString(TEXT("config"), TEXT("screenType"), buf, ini_file);
	// 効果音
	wsprintf(buf, "%d", SE);
	WritePrivateProfileString(TEXT("config"), TEXT("SE"), buf, ini_file);
	// BGM
	wsprintf(buf, "%d", BGM);
	WritePrivateProfileString(TEXT("config"), TEXT("BGM"), buf, ini_file);

	return true;
}
