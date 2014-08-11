// Window_HintMessage.cpp

#include "Window_HintMessage.h"
#include <iostream>
#include <fstream>
#include <DxLib.h>
#include "WindowSkin.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "Image.h"
#include "Sound.h"

extern WindowSkins		g_wndSkins;
extern DXFont			g_font;
extern DXInput			g_input;
extern KeyConfig		g_key;
extern Image			g_image;
extern Sound			g_sound;

Window_HintMessage::Window_HintMessage() : Window_Message(){
	// ウィンドウの情報をクリアする。
	Clear();
}

void Window_HintMessage::Clear(){
	// ファイル名リセット
	_tcscpy_s(fileName, MAX_PATH, _T(""));
	// ファイル位置リセット
	filePos = 0;
	lineCount = 0;
	isError = false;
	isTerminated = false;
	ClearBuffer();
	drawMsg.ClearAll();
	stockMsg.ClearAll();
}

void Window_HintMessage::ClearBuffer(){
	linePos = 0;
	for(int n=0; n<WND_MSG_DRAWLINE; n++){
		strcpy_s(buffer[n], WND_MSG_STOCKLENGTH-1, _T(""));
	}
}


bool Window_HintMessage::OpenAndPlay(LPTSTR fileName, WORD _typeID){
	// typeIDをセットする
	if(!SetupByTypeID(_typeID, true)){
		return false;
	}
	// ファイル名をセットし、開けるかどうかを確認する
	Clear();
	if(!SetFileName(fileName)){
		return false;
	}
	// ウィンドウを開く
	if(Open(false, false) != WNDOPEN_SUCCEED){
		return false;
	}
	return true;
}

bool Window_HintMessage::SetupByTypeID(WORD _typeID, bool check){
	switch(_typeID){
	case WND_HINT_SHANGHAI:
		Setup(&g_wndSkins.skin[WNDSKIN_BALLOON],
			GetWindowArea(200, 150, 600, 300),
			GetWindowArea(90, 85, 440, 130),
			true);
		SetFont(g_font.hTalk, FONTSIZE_TALK, FONTSIZE_TALK+8);
		SetColor(GetColor(128, 48, 32));
		SetFontWidth(FONTSIZE_TALK);
		SetMessageSpeed(0.4);
		break;
	case WND_HINT_ALICE:
		Setup(&g_wndSkins.skin[WNDSKIN_BALLOON],
			GetWindowArea(200, 150, 600, 300),
			GetWindowArea(90, 85, 440, 130),
			true);
		SetFont(g_font.hTalk, FONTSIZE_TALK, FONTSIZE_TALK+8);
		SetColor(GetColor(128, 48, 32));
		SetFontWidth(FONTSIZE_TALK);
		SetMessageSpeed(0.4);
		break;
	default:
		if(check){
			// 有効な値ではない(チェックする場合のみfalseを返す)
			return false;
		}
	}
	// 共通の設定
	// 最後の行以外はクリック待ちをしない
	readTypeFlag = 
		F_READTYPE_SKIPTOEMPTY | F_READTYPE_AUTOQUICK | F_READTYPE_PUSH;
	typeID = _typeID;
	return true;
}


bool Window_HintMessage::SetFileName(LPTSTR name){
	_tcscpy_s(fileName, MAX_PATH-1, name);
	filePos = 0;
	lineCount = 0;

	// ファイルを開く
	// (開けるかどうかの確認だけを行う)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return false;
	}

	// ファイルを閉じる
	fin.close();
	return true;
}

BYTE Window_HintMessage::NewPage(){
	bool isFirstPage = (lineCount == 0);
	// 宣言
	std::basic_ifstream<TCHAR> fin;
	bool isError = false;
	bool isEnd = false;			// 一ページ分の読み込みが終了したか
	bool isFileEnd = false;	// ファイル末端に達したか
	TCHAR tmpBuf[WND_MSG_STOCKLENGTH];
	strcpy_s(tmpBuf, WND_MSG_STOCKLENGTH-1, _T(""));

	// ファイルを開く
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return WND_HINT_NEWPAGE_ERROR;
	}
	if(fin.eof()){
		isTerminated = true;
		return WND_HINT_NEWPAGE_END;
	}

	// ファイル位置をセット
	fin.seekg(filePos, std::ios::beg);

	ClearBuffer();
	do{
		// ファイルを読み込んでbufferにコピーする
		// 1行読み込む
		fin.getline(tmpBuf, WND_MSG_STOCKLENGTH);
		lineCount++;
		// コマンドの判定
		switch(CheckCommand(tmpBuf)){
		case WND_HINT_CHKCMD_NEWPAGE:
			drawMsg.ClearAll();
			isEnd = true;
			break;
		case WND_HINT_CHKCMD_END:
			drawMsg.ClearAll();
			isFileEnd = true;
			isEnd = true;
			break;
		case WND_HINT_CHKCMD_NONE:
			// バッファの内容をコピー
			if(linePos < WND_MSG_DRAWLINE){
				strcpy_s(buffer[linePos], WND_MSG_STOCKLENGTH-1, tmpBuf);
				linePos++;
			}else{
				// エラー発生と見なす
				isError = true;
			}
		}
	}while(!isError && !isEnd);

	// ファイル位置を保存する
	filePos = fin.tellg();

	// バッファをstockLineに移動させる
	if(!FlushBuffer()){
		return WND_HINT_NEWPAGE_ERROR;
	}

	if(isFileEnd){
		if(!isFirstPage){
			g_sound.PlaySE(MYSE_MESSAGE_NEWPAGE, 0.8f);
		}
		return WND_HINT_NEWPAGE_END;
	}else{
		// ここで音を鳴らす
		if(!isFirstPage){
			g_sound.PlaySE(MYSE_MESSAGE_NEWPAGE, 0.8f);
		}
		return WND_HINT_NEWPAGE_OK;
	}
	// return isFileEnd ? WND_HINT_NEWPAGE_END : WND_HINT_NEWPAGE_OK;
}

bool Window_HintMessage::FlushBuffer(){
	// stockMsgに値をコピーする
	for(int n=0; n<linePos; n++){
		stockMsg.AddMsg(buffer[n], strlen(buffer[n]));
	}
	ClearBuffer();
	return true;
}

WORD Window_HintMessage::CheckCommand(LPTSTR buf){
	if(buf == NULL) return WND_HINT_CHKCMD_ERROR;
	if(buf[0] != '#') return WND_HINT_CHKCMD_NONE;
	int bufLng = strlen(buf);
	bool isEnd = false;
	int num = 0;		// スペース区切りの単語の数
	int pos = 0;		// 現在の単語を読む位置

	// 宣言
	TCHAR value[4][16];
	for(int n=0; n<4; n++){
		strcpy_s(value[n], 16-1, _T(""));
	}

	// 文字を最初から読み込んでいく
	for(int i=1; (i<=bufLng && !isEnd); i++){ // 末端の'\0'まで含む(先頭の#は除く)
		switch(buf[i]){
		case _T('\0'):
		case _T('\n'):		// 読み込みの終端
			value[num][pos] = '\0';
			num++;
			isEnd = true;
			break;
		case _T(','):		// カンマ : 次の値へ
			value[num][pos] = '\0';
			num++;
			pos = 0;
			if(num >= 4){
				isEnd = true;
			}
			break;
		case _T(' '):		// 空白 : 値の先頭であれば無視する
			if(pos > 0){ // 先頭であるか
				value[num][pos] = buf[i];
				pos++;
			}
			break;
		default:			// その他の文字 : 値を継続
			value[num][pos] = buf[i];
			pos++;
			break;
		}
	}

	// コマンドの判定を行う
	if(_tcscmp(value[0], _T("newpage")) == 0){
		return WND_HINT_CHKCMD_NEWPAGE;
	}
	if(_tcscmp(value[0], _T("exit")) == 0){
		return WND_HINT_CHKCMD_END;
	}
	
	// どのコマンドにも当てはまらないエラー
	return WND_HINT_CHKCMD_ERROR;
}

void Window_HintMessage::ExUpdate(){
	switch(state){
	case UPDATING:

		break;
	case IDLE:
		if(!isTerminated){
			// 次のページを読み込む。
			switch(NewPage()){
			case WND_HINT_NEWPAGE_OK:
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_OVERFLOW:
				isError = true;
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_END:
				isTerminated = true; // すぐさま閉じるのではなく、最後の文章を表示して閉じる
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_ERROR:
				isError = true;
				Close();
				break;
			}
		}else{
			// 内容をクリアしてから閉じる
			Clear();
			Close();
		}
		break;
	}
}

bool Window_HintMessage::CheckIsIdle(){
	// 最後の行を表示し終わって、クリックされたらIDLEになる。
	// (そして次の行が読み込まれる)
	if(state == UPDATING){
		if(linePos >= GetLineLength()){
			if(StockIsEmpty()){
				if((g_input.pushedKey & g_key.input[BTN_CHOOSE]) != 0){
					return true;
				}
			}
		}
	}
	return false;
}

void Window_HintMessage::DrawFrameBack() const{
	if(!GetActive()) return;
	int tmpY = 0;
	switch(typeID){
	case WND_HINT_ALICE:
	case WND_HINT_SHANGHAI:
		// キャラクターの描画
		tmpY = -15*sin(2.0*M_PI*activeCount/400);
		DrawRotaGraphF(
			frameArea.x-50, frameArea.y+frameArea.h/2+tmpY,
			0.8, 0, g_image.icon.doll[0][3][0], 1);
	}
}

void Window_HintMessage::DrawContent() const{
	if(!GetActive()) return;
	bool waitClick = false;
	if(state == UPDATING ){
		if(linePos >= GetLineLength()){
			if(StockIsEmpty()){
				waitClick = true;
			}
		}
	}
		

	switch(typeID){
	case WND_HINT_ALICE:
	case WND_HINT_SHANGHAI:
		// 文章の描画
		for(int n=0; n<WND_MSG_DRAWLINE; n++){
			if(n <= drawMsg.GetIndex() || true){
				DrawLineByIndex(0, windowFont.lineHeight*n, n);
			}
		}
		// クリック待ち記号の描画
		if(waitClick){
			DrawGraph(
				frameArea.x + contentArea.x + contentArea.w - 16,
				frameArea.y + contentArea.y 
				+ contentArea.h + 8 + 6*sin(2*M_PI*activeCount/30),
				g_image.icon.cursor[0], 1);
			// DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), 1);
		}
	}
}