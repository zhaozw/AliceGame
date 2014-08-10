// DXFont.cpp

#include <Windows.h>

#include "DXFont.h"
#include "DxLib.h"

DXFont::DXFont(){
	hInfo = 0;
	hStr = 0;
	hStrL = 0;
	hTinyInfo = 0;
}

bool DXFont::Load(){
	// フォント名
	TCHAR	fontName[64];
	TCHAR	fontNamePop[64];

	// 外部フォントを使用する場合はここで読み込んでおく
	// AddFontResourceEx(_T("フォント名"), FR_PRIVATE, NULL);

	// 使用するフォントを指定する
	// 該当するフォントが存在しない場合のために優先順位順にいくつか示しておく
	// ＭＳ 明朝とＭＳ ゴシックは日本語環境であれば必ず存在するはず
	TCHAR fontNames[4][64] = {
		// _T("フォント名"), // 外部フォントを使う場合
		_T("HGｺﾞｼｯｸM"),
		_T("HGSｺﾞｼｯｸM"),
		_T("メイリオ"),
		_T("ＭＳ ゴシック")};
	for(int i=0; i<4; i++){
		if(EnumFontNameEx2(fontName, 1, fontNames[i]) == 1){
			strcpy_s(fontName, 63, fontNames[i]);
			break;
		}
	}
	// ポップなフォントを使用する場合
	TCHAR fontNamesPop[4][64] = {
		// _T("フォント名"), // 外部フォントを使う場合
		_T("HG創英角ﾎﾟｯﾌﾟ体"),
		_T("HG丸ｺﾞｼｯｸM-PRO"),
		_T("メイリオ"),
		_T("ＭＳ ゴシック"),
	};
	for(int i=0; i<4; i++){
		if(EnumFontNameEx2(fontNamePop, 1, fontNamesPop[i]) == 1){
			strcpy_s(fontNamePop, 63, fontNamesPop[i]);
			break;
		}
	}


	// フォントの作成
	hInfo = CreateFontToHandle(fontName, FONTSIZE_INFO,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hStr = CreateFontToHandle(fontName, FONTSIZE_STR,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hStrL = CreateFontToHandle(fontName, FONTSIZE_STR_L,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hTinyInfo = CreateFontToHandle(fontName, FONTSIZE_TINYINFO,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hTalk = CreateFontToHandle(fontNamePop, FONTSIZE_TALK,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);

	// フォントのロード
	if(hInfo == -1) return false;
	if(hStr == -1) return false;
	if(hStrL == -1) return false;
	if(hTinyInfo == -1) return false;

	/*
	if((hInfo = CreateFontToHandle(fontName, FONTSIZE_INFO,
		-1, DX_FONTTYPE_ANTIALIASING)) == -1) return false;
		*/

	return true;
}

bool DXFont::Release(){

	// 外部フォントを使用した場合はここで開放する
	// RemoveFontResourceEx(_T("フォント名"), FR_PRIVATE, NULL);

	return true;
}