// Window_SimpleDollStatus.cpp

#include "Window_SimpleDollStatus.h"
#include "Game_BattleDoll.h"
#include "Game_AliceDoll.h"
#include "WindowSkin.h"

extern WindowSkins g_wndSkins;

Window_SimpleDollStatus::Window_SimpleDollStatus() : Window_Info(){
	pBattleDoll = NULL;
	pCampDoll = NULL;
	isBattle = true;
	drawPtn = DRAWPTN_ALLSTATUS;
}

void Window_SimpleDollStatus::Setup(BYTE _drawPtn, bool _isBattle){
	WINDOWAREA frame;
	WINDOWAREA content;
	int width = 0;
	int height = 0;
	int frameSize = 0;
	switch (_drawPtn){
	case DRAWPTN_ALLSTATUS:
		width = 128;
		height = 160;
		frameSize = 16;
		break;
	}

	// ëÂÇ´Ç≥ÇåàíË
	frame.x = 0;
	frame.y = 0;
	frame.w = width;
	frame.h = height;
	content.x = frameSize;
	content.y = frameSize;
	content.w = width - frameSize * 2;
	content.h = height - frameSize * 2;

	// ÉEÉBÉìÉhÉEÇÃÉZÉbÉgÉAÉbÉv
	Window_Info::Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE], frame, content);
	drawPtn = _drawPtn;
	isBattle = _isBattle;
}

void Window_SimpleDollStatus::OpenWithBattleDoll(Game_BattleDoll* _pDoll, int _x, int _y){
	pBattleDoll = _pDoll;
	SetPosition(_x, _y);
}

void Window_SimpleDollStatus::OpenWithCampDoll(Game_AliceDoll* _pDoll, int _x, int _y){
	pCampDoll = _pDoll;
	SetPosition(_x, _y);
}

bool Window_SimpleDollStatus::ChangeRefBattleDoll(Game_BattleDoll* _pDoll){
	if (pBattleDoll != _pDoll){
		pBattleDoll = _pDoll;
		ContentChanged();
		return true;
	}
	return false;
}

bool Window_SimpleDollStatus::ChangeRefCampDoll(Game_AliceDoll* _pDoll){
	if (pCampDoll != _pDoll){
		pCampDoll = _pDoll;
		ContentChanged();
		return true;
	}
	return false;
}

void Window_SimpleDollStatus::Update(){
	Window_Info::Update();
}

void Window_SimpleDollStatus::DrawContent() const{
	if (isBattle){
		DrawContent_Battle();
	}else{
		DrawContent_Camp();
	}

}

void Window_SimpleDollStatus::DrawContent_Battle() const{
	TCHAR status[][12] = {
		"ÇkÇñ",
		"ÇgÇo",
		"çUåÇ",
		"ïqè∑",
		"ñÇóÕ",
		"ãZçI",
	};
	// ñºëOÇÃï`âÊ
	// éÌë∞ÇÃï`âÊ

}

void Window_SimpleDollStatus::DrawContent_Camp() const{
}