// Window_Message.cpp

#include <Windows.h>
#include <tchar.h>
#include <DxLib.h>
#include "Window_Message.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "Func_Math.h"


extern WindowSkins		g_wndSkins;
extern DXFont			g_font;
extern DXInput			g_input;
extern KeyConfig		g_key;

//=====================================================
// Window_Message_Draw系

Window_Message_DrawLine::Window_Message_DrawLine(){
	Clear();
}

void Window_Message_DrawLine::Clear(){
	for(int c=0; c<WND_MSG_DRAWLENGTH; c++){
		for(int n=0; n<3; n++){
			chars[c].character[n] = 0x00;
		}
		chars[c].used = false;
		chars[c].flags = 0x0000; // 文字のフラグ
	}
	flags = 0x0000; // 行のフラグ
}

int Window_Message_DrawLine::GetStrLength() const{
	for(int c=0; c<WND_MSG_DRAWLENGTH; c++){
		if(!chars[c].used){
			return c;
		}
	}
	return WND_MSG_DRAWLENGTH;
}

bool Window_Message_DrawLine::Import(LPTSTR buf, int strLen){
	// 文字列について一文字ずつ判定を行う
	TCHAR* p = buf;
	if(p == NULL) return false;
	
	// まず文字列をクリアする
	Clear();
	int strCount = 0; // 表示する文字数換算で何文字目まで入ったか
	while((*p != '\0') && (strCount < strLen)){
		switch(_mbclen((BYTE*)p)){
		case 1:
			if(*p >= '0' && *p <= '9'){
				// 数字。一桁あたり一文字でそのままコピーする。
				chars[strCount].character[0] = *p;
				*p++;
				chars[strCount].character[1] = '\0';
				chars[strCount].character[2] = '\0';
				chars[strCount].used = true;
				chars[strCount].flags |= F_MSGCHAR_ONE_BYTE;
				strCount++;
			}else if(*p == _T('.')){
				// ピリオドは空行を表す
				*p++;
				for(int n=0; n<3; n++){
					chars[strCount].character[n] = _T('\0');
				}
				chars[strCount].used = false;
				chars[strCount].flags |= F_MSGCHAR_ENDMSG;
				strCount++;
			}else{
				// 特殊文字。半角文字全体をコピーした上で別途判定を行う。
				strCount++; // 現在は判定しない
			}
			break;
		case 2:
			// 全角文字。そのままコピーする。
			chars[strCount].character[0] = *p;
			*p++;
			chars[strCount].character[1] = *p;
			*p++;
			chars[strCount].character[2] = '\0';
			chars[strCount].used = true;
			strCount++;
			break;
		default:
			// エラー
			return false;
			break;
		}
	}
	return true;
}

void Window_Message_DrawLine::DrawContent(int hFont, int fontWidth,
	int x, int y, int count) const{
	// 一行分の内容を描画する。
	int strLength = (count == -1 ? GetStrLength() : count);
	strLength = min(WND_MSG_DRAWLENGTH, strLength);
	int tmpDrawX = x;
	for(int n=0; n<strLength; n++){
		DrawStringToHandle(tmpDrawX, y, chars[n].character, 
			GetColor(255, 255, 255), hFont);
		if(chars[n].flags & F_MSGCHAR_ONE_BYTE){
			tmpDrawX += fontWidth/2;
		}else{
			tmpDrawX += fontWidth;
		}
	}
}


Window_Message_DrawMsg::Window_Message_DrawMsg(){
	ClearAll();
}

void Window_Message_DrawMsg::ClearLine(int n){
	if(n<0 || n>= WND_MSG_DRAWLINE) return ;
	lines[n].Clear();
}

void Window_Message_DrawMsg::ClearAll(){
	for(int l=0; l<WND_MSG_DRAWLINE; l++){
		ClearLine(l);
	}
	// データを配置する位置を初期化
	index = 0;
}

void Window_Message_DrawMsg::DrawLine(
	int hFont, int fontWidth, int x, int y,
	int count, int historyCount) const{
		int tmpIndex = SeamLess(index-historyCount, WND_MSG_DRAWLINE);
		if(tmpIndex < WND_MSG_DRAWLINE){
			lines[tmpIndex].DrawContent(hFont, fontWidth, x, y, count);
		}
}

int Window_Message_DrawMsg::GetLineLength(int historyCount) const {
	int tmpIndex = SeamLess(index-historyCount, WND_MSG_DRAWLINE);
	return lines[tmpIndex].GetStrLength();
}

bool Window_Message_DrawMsg::ImportLine(LPTSTR buf){
	index = SeamLess(index+1, WND_MSG_DRAWLINE);
	return lines[index].Import(buf, strlen(buf));
}

void Window_Message_DrawMsg::BlankLine(){
	index = SeamLess(index+1, WND_MSG_DRAWLINE);
	TCHAR str[] = _T("."); // ピリオドで空行を表す 
	lines[index].Import(str, strlen(str));
}

//=====================================================
// Window_Message_Stock系


Window_Message_StockLine::Window_Message_StockLine(){
}

void Window_Message_StockLine::Clear(){
	strcpy_s(chars, WND_MSG_STOCKLENGTH, _T(""));
}

bool Window_Message_StockLine::IsEmpty(){
	return (strlen(chars) == 0);
}

Window_Message_StockMsg::Window_Message_StockMsg(){
	ClearAll();
	index = 0;
	emptyIndex = 0;
}

void Window_Message_StockMsg::ClearLine(int n){
	if(n<0 || n>= WND_MSG_STOCKLINE) return;
	lines[n].Clear();
}

void Window_Message_StockMsg::ClearAll(){
	for(int l=0; l<WND_MSG_STOCKLINE; l++){
		ClearLine(l);
	}
	// データを配置する位置を初期化
	index = 0;
}

bool Window_Message_StockMsg::AddMsg(LPTSTR str, int strlen){
	// 長さがおかしくないかのチェック
	if(strlen >= WND_MSG_STOCKLENGTH) return false;
	if(emptyIndex >= WND_MSG_STOCKLINE){
		return false;
	}
	// バッファに空きがあるかのチェック
	if(!lines[emptyIndex].IsEmpty()) return false;
	// 空行に対して内容をコピーする
	strcpy_s(lines[emptyIndex].chars, WND_MSG_STOCKLENGTH, str);
	// 空ではなくなったのでインデックスをずらす
	emptyIndex = SeamLess(emptyIndex+1, WND_MSG_STOCKLINE);
	return true;
}

bool Window_Message_StockMsg::ReadLine(LPTSTR buf, bool discard){
	// 空行の場合はfalseを返す
	if(IsEmpty()) return false;
	// 読み込むべき行の内容をコピーする
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, lines[index].chars);
	// 行送り
	if(discard) DiscardLine();
	return true;
}

void Window_Message_StockMsg::DiscardLine(){
	// 現在の行を空にする
	strcpy_s(lines[index].chars, WND_MSG_STOCKLENGTH-1, _T(""));	
	// indexはemptyIndexを追い越してはいけない
	if(index != emptyIndex) index++;
	index = SeamLess(index, WND_MSG_STOCKLINE);
}

//=====================================================
// Window_Message

Window_Message::Window_Message() : Window_Text(){
	// メンバの初期化
	ResetAll();
}

void Window_Message::Setup(WindowSkin* pSkin, int _x, int _y, int _w, int _h, int _px, int _py, bool _visible){
	// 初期化
	Window_Base::Setup(pSkin, _x, _y, _w, _h, _px, _py, _visible);
	// 仮の値
	SetColor(GetColor(255, 255, 255));
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	SetFontWidth(FONTSIZE_INFO);
	// 全てリセットする
	ResetAll();
}

void Window_Message::ResetAll(){
	// 内容のクリア
	drawMsg.ClearAll();
	stockMsg.ClearAll();

	// 変数の初期化
	linePos = 0;
	lineCount = 0;
	lineCountMin = 0;
	clickWaitCount = 0;
	clickWaitTime = -1;
	subState = WNDSUBSTATE_NOTEXT;
	fontWidth = 0;
	messageSpeed = WND_MSG_DEFSPD;
	readTypeFlag = F_READTYPE_QUICK;
}

bool Window_Message::AddStockMsg(LPTSTR str, int strlen){
	// 表示待ち文書にメッセージを追加
	if(!stockMsg.AddMsg(str, strlen)){
		return false;
	}
	// 現在のステートに関わらずステートをビジー状態にする
	// (主にIDLE状態からUPDATING状態に変化)
	state = UPDATING;
	return true;
}

void Window_Message::Update(){
	bool flag = false;
	switch(state){
	case UPDATING:
		// 表示中の行が更新中であれば更新する。
		// 更新が終了している場合は次の行を読み込むか、
		// もしくはストックがない場合はIDLE状態にする。
		switch(subState){
		case WNDSUBSTATE_NOTEXT:
			// テキストがない状態
			// ストック状態のテキストがあれば読み込む。
			// ない場合はIDLE状態になる。
			if(stockMsg.IsEmpty()){
				state = IDLE;
			}else{
				NewLine(false);
			}
			break;
		case WNDSUBSTATE_READING:
			// テキストを読んでいる状態
			UpdateLine();
			// クラス独自の更新
			ExUpdate();
			// 改行判定
			CheckNewLine(
				((g_input.pushedKey & g_key.input[BTN_CHOOSE]) != 0),
				((g_input.key & g_key.input[BTN_CANCEL]) != 0));
			// IDLE状態になるかどうかの確認
			// (クラス独自の内容)
			if(CheckIsIdle()){
				subState = WNDSUBSTATE_NOTEXT;
				state = IDLE;
			}
			break;
			/*
		case WNDSUBSTATE_CLICKWAIT:
			// クリック待ちの状態
			// クリックされた場合、あるいは待ち時間を過ぎた場合は
			// テキストがない状態になる。
			subState = WNDSUBSTATE_NOTEXT;
			break;
			*/
		case WNDSUBSTATE_UNDIFINED:
			// よく分からない状態。
			break;
		}
		break;
	case SUSPENDED:
		state = IDLE;
		break;
	case IDLE:
		break;
	}
}

void Window_Message::ExUpdate(){
}

bool Window_Message::CheckIsIdle(){
	return false;
}

void Window_Message::NewLine(bool force){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	// 新しい行をストックから読み込む。
	if(stockMsg.ReadLine(buf, true)){
		// 描画用の行に読み込んだ内容をコピーして解釈させる
		drawMsg.ImportLine(buf);
	}else{
		// 読み込む行がない場合、空行を差し込む
		drawMsg.BlankLine();
	}
	// メッセージ読み込み中状態にする
	subState = WNDSUBSTATE_READING;
	// drawMsg.NextLine();
	linePos = 0;
	lineCount = 0;
	clickWaitCount = 0;
}

void Window_Message::UpdateLine(){
	// 現在の行が最後までいった場合はクリック待ち状態になる。
	lineCount++;
	if(readTypeFlag & F_READTYPE_NOWAIT){
		// 瞬間表示
		linePos = GetLineLength();
	}else{
		linePos = messageSpeed * lineCount;
	}
	// 文章の表示が終わっている場合
	if(linePos >= GetLineLength()){
		clickWaitCount++;
	}
}

bool Window_Message::CheckNewLine(bool chooseKey, bool skipKey){
	// 改行するかどうか
	bool flag = false;

	if(linePos >= GetLineLength()){
		// 文章が表示完了している時
		if((readTypeFlag & F_READTYPE_AUTOPLAY) == 0x0000){
			// 常時自動進行フラグが立っていなければ
			// 文章の表示が終わっている場合、いずれかのボタンで先に
			if(chooseKey){
				// 決定キー
				flag = true;
			}
			if(skipKey && (readTypeFlag & F_READTYPE_AUTOQUICK)){
				// スキップキーが有効な場合
				flag = true;
			}
		}
		// 時間経過によるスキップ
		if(clickWaitTime != -1){
			if(clickWaitCount >= clickWaitTime){
				flag = true;
			}
		}
		// 次に文章がある場合のスキップ
		if(readTypeFlag & F_READTYPE_PUSH){
			if(CheckStockMsg()){
				flag = true;
			}
		}
		// 常時スキップ
		if(readTypeFlag & F_READTYPE_FLOOD){
			flag = true;
		}
		// ストックが空行であってもキーで進めるか
		if(!(readTypeFlag & F_READTYPE_BLANKLINE)){
			if(StockIsEmpty()){
				flag = false;
			}
		}
	}else{
		// 文章が表示し終わっていない場合
		if(lineCount > lineCountMin){
			// 瞬間表示可能
			if((readTypeFlag & F_READTYPE_QUICK) != 0x0000){
				if(chooseKey){
					lineCount = 9999; // 一気に行の終わりまで表示
					if((readTypeFlag & F_READTYPE_DIRECTQUICK) != 0x0000){
						// 即座に改行
						flag = true;
					}
				}
			}
			if((readTypeFlag & F_READTYPE_AUTOQUICK) != 0x0000){
				if(skipKey){
					lineCount = 9999; // 一気に行の終わりまで表示
					if((readTypeFlag & F_READTYPE_DIRECTQUICK) != 0x0000){
						// 即座に改行
						flag = true;
					}
				}
			}
		}
	}

	// 実際の改行を行う
	if(flag) NewLine(false);
	return flag;
}

bool Window_Message::CheckStockMsg(){
	return false;
}

int Window_Message::GetLineLength(){
	return drawMsg.GetLineLength();
}

void Window_Message::DrawContent() const{
	// 表示方法は各クラスに派生する。
}

void Window_Message::DrawLine(int dx, int dy, int historyCount) const{
	// 指定した一行を描画する
	drawMsg.DrawLine(hFont, fontWidth, x+dx, y+dy,
		(historyCount==0 ? linePos : -1), historyCount);
}

void Window_Message::DrawCurrentLine(int dx, int dy) const{
}

void Window_Message::DrawHistoryLine(int dx, int dy, int historyCount) const{
	if(historyCount >= WND_MSG_DRAWLINE) return;
	int tmpIndex = SeamLess(drawMsg.GetIndex()-historyCount, WND_MSG_DRAWLINE);
}