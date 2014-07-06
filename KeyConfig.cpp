// KeyConfig.cpp

#include "KeyConfig.h"
#include "Static_Game.h"

KeyConfig::KeyConfig(){
	ResetConfig();
}

bool KeyConfig::LoadKeyConfig(){
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	TCHAR buf2[16];
	//==========================================
	// ファイルの呼び出し

	// ファイル名を取得
	// iniファイルからコンフィグ情報を読み出す。
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	bool result = true;


	do{ // エラーチェック
		// キーコンフィグの設定
		for(int i=0; i<5 && result; i++){
			// キーコンフィグの取得
			// デフォルト値のIはダミー
			sprintf_s(buf2, 16, "button%1d", i);
			GetPrivateProfileString(_T("config"), buf2,
				_T("I"), buf, sizeof(buf), ini_file);
			input[i] = KeyToInt(buf[0]);
			if(input[i] == 0){ // エラーが発生した場合
				result = false;
			}
		}

		if(!result){
			ResetConfig();
		}
	}while(0);

	// 初期ファイルに不備があった場合は設定を保存し、メッセージを出す
	if(!result){
		if(!SaveKeyConfig()) return false;
	}

	return true;
}

bool KeyConfig::SaveKeyConfig(){
	//==========================================
	// ファイルの作成
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	TCHAR buf2[16];

	// ファイル名を取得
	// iniファイルからコンフィグ情報を読み出す。
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	// キーコンフィグ
	strcpy_s(buf, 255, TEXT("")); // クリア
	buf[1] = '\0'; // ここから1文字のデータが続く
	for(int i=0; i<5; i++){
		buf[0] = IntToKey(input[i]); // ショットボタン
		if(buf[0] == 'I') return false;
		sprintf_s(buf2, 16, "button%1d", i);
		WritePrivateProfileString(TEXT("config"), buf2, buf, ini_file);
	}
	return true;
}

int KeyConfig::KeyToInt(TCHAR c){
	// キーと整数(PAD_INPUT_..)を対応させる
	switch(c){
		case 'A':
			return (int)PAD_INPUT_A;
			break;
		case 'B':
			return (int)PAD_INPUT_B;
			break;
		case 'C':
			return (int)PAD_INPUT_C;
			break;
		case 'X':
			return (int)PAD_INPUT_X;
			break;
		case 'Y':
			return (int)PAD_INPUT_Y;
			break;
		case 'Z':
			return (int)PAD_INPUT_Z;
			break;
		case 'L':
			return (int)PAD_INPUT_L;
			break;
		case 'R':
			return (int)PAD_INPUT_R;
			break;
		case 'E':
			return (int)PAD_INPUT_START;
			break;
		case 'M':
			return (int)PAD_INPUT_M;
			break;
		case 'S':
			// 左Shiftキーを11番目のボタンに対応
			return (int)PAD_INPUT_11;
			break;
		case 'T':
			// 右Shiftキーを12番目のボタンに対応
			return (int)PAD_INPUT_12;
			break;
		default: // エラー
			return 0;
			break;
	}
	// エラー
	return 0;
}

TCHAR KeyConfig::IntToKey(int n){
	switch(n){
		case PAD_INPUT_A:
			return 'A';
			break;
		case PAD_INPUT_B:
			return 'B';
			break;
		case PAD_INPUT_C:
			return 'C';
			break;
		case PAD_INPUT_X:
			return 'X';
			break;
		case PAD_INPUT_Y:
			return 'Y';
			break;
		case PAD_INPUT_Z:
			return 'Z';
			break;
		case PAD_INPUT_L:
			return 'L';
			break;
		case PAD_INPUT_R:
			return 'R';
			break;
		case PAD_INPUT_START:
			return 'E';
			break;
		case PAD_INPUT_M:
			return 'M';
			break;
		case PAD_INPUT_11:
			return 'S';
			break;
		case PAD_INPUT_12:
			return 'T';
			break;
		default:
			return 'I';
			break;
	}
	return 'I';
}

void KeyConfig::ResetConfig(){
	input[0] = DEF_INPUT_0;
	input[1] = DEF_INPUT_1;
	input[2] = DEF_INPUT_2;
	input[3] = DEF_INPUT_3;
	input[4] = DEF_INPUT_4;
}