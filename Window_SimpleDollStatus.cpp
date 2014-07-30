// Window_SimpleDollStatus.cpp

#include "Window_SimpleDollStatus.h"
#include <DxLib.h>

#include "Game_BattleDoll.h"
#include "Game_AliceDoll.h"
#include "WindowSkin.h"
#include "Sprite_BattleDoll.h"
#include "Data_DollParam.h"

extern WindowSkins		g_wndSkins;
extern Data_DollParam	d_dollParam;

Window_SimpleDollStatus::Window_SimpleDollStatus() : Window_Info(){
	pBattleDoll = NULL;
	pCampDoll = NULL;
	isBattle = true;
	drawPtn = DRAWPTN_ALLSTATUS;
}

void Window_SimpleDollStatus::Setup(BYTE _drawPtn, bool _isBattle){
	WINDOWAREA frame;
	WINDOWAREA content;
	frame.x = 0;
	frame.y = 0;

	int width = 0;
	int height = 0;
	int frameSize = 0;
	switch (_drawPtn){
	case DRAWPTN_ALLSTATUS:
		width = 128;
		height = 160;
		frameSize = 16;
		break;
	case DRAWPTN_BATTLESTATUS:
		width = SPRITE_BATTLEDOLL_DX*3 - 40;
		height = 168;
		frame.x = SPRITE_BATTLEDOLL_IX + 20;
		frame.y = SPRITE_BATTLEDOLL_IY - height - 16;
		frameSize = 16;
		break;
	}

	// ‘å‚«‚³‚ğŒˆ’è
	frame.w = width;
	frame.h = height;
	content.x = frameSize;
	content.y = frameSize;
	content.w = width - frameSize * 2;
	content.h = height - frameSize * 2;

	// ƒEƒBƒ“ƒhƒE‚ÌƒZƒbƒgƒAƒbƒv
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
	if(!GetActive()) return;
	switch(drawPtn){
	case DRAWPTN_BATTLESTATUS:
		DrawContent_BattleStatus();
		break;
	}

}

void Window_SimpleDollStatus::DrawContent_BattleStatus() const{
	if(pBattleDoll == NULL) return;
	// –¼‘O‚Ì•`‰æ
	TCHAR buf[64];
	TCHAR buf2[8];
	int width = 0;
	int cntY = frameArea.y;
	int cx = frameArea.x + frameArea.w/2;
	int param = 0;
	pBattleDoll->GetName(buf, 64);
	width = GetStrWidth(buf, strlen(buf), windowFont.hFont);
	cntY += 24;
	DrawStr(cx-width/2, cntY, buf, windowFont.color, windowFont.hFont);
	// lŒ`‚Ìí—Ş‚Æ‘®«‚Ì•`‰æ
	cntY += FONTSIZE_INFO+4;
	d_dollParam.GetTypeName(pBattleDoll->GetDollType(), buf, 64);
	if(pBattleDoll->GetAttr() != DOLL_ATTR_NONE){
		strcat_s(buf, 64, _T("i"));
		switch(pBattleDoll->GetAttr()){
		case DOLL_ATTR_SUN:
			strcpy_s(buf2, 7, _T("‘¾—z"));
			break;
		case DOLL_ATTR_MOON:
			strcpy_s(buf2, 7, _T("Œ"));
			break;
		case DOLL_ATTR_STAR:
			strcpy_s(buf2, 7, _T("¯"));
			break;
		}
		strcat_s(buf, 64, buf2);
		strcat_s(buf, 64, _T("j"));
	}
	DrawStr(frameArea.x+32, cntY, buf, windowFont.color, windowFont.hFont);

	// HP/Å‘åHP‚Ì•`‰æ
	wsprintf(buf, _T("‚g‚oF%d/%d"), pBattleDoll->GetHP(), pBattleDoll->GetMaxHP());
	width = GetStrWidth(buf, strlen(buf), windowFont.hFont);
	DrawStr(frameArea.x+frameArea.w-32-width, cntY, buf, windowFont.color, windowFont.hFont);

	// Šeƒpƒ‰ƒ[ƒ^‚Ì•`‰æ
	cntY += FONTSIZE_INFO+8;
	TCHAR paramName[][8] = {
		"UŒ‚", "•q·", "–‚—Í", "‹ZI"};
	for(int j=0; j<2; j++){
		for(int i=0; i<2; i++){
			switch(i+j*2){
			case 0:
				param = pBattleDoll->GetAtk();
				break;
			case 1:
				param = pBattleDoll->GetSpd();
				break;
			case 2:
				param = pBattleDoll->GetMgc();
				break;
			case 3:
				param = pBattleDoll->GetTec();
				break;
			}
			wsprintf(buf, _T("%sF%d"), paramName[i+j*2], param);
			DrawStr(
				frameArea.x+80+i*176, cntY + j*(FONTSIZE_INFO+4),
				buf, windowFont.color, windowFont.hFont);
		}
	}

	/*
	TCHAR status[][12] = {
		"‚k‚–",
		"‚g‚o",
		"UŒ‚",
		"•q·",
		"–‚—Í",
		"‹ZI",
	};
	// –¼‘O‚Ì•`‰æ
	// í‘°‚Ì•`‰æ
	*/
}

void Window_SimpleDollStatus::DrawContent_Camp() const{
}