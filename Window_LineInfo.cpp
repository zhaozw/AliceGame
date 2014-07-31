// Window_LineInfo.cpp

#include "Window_LineInfo.h"
#include <DxLib.h>

#include "DXFont.h"
#include "WindowSkin.h"

extern DXFont		g_font;
extern WindowSkins	g_wndSkins;

Window_LineInfo::Window_LineInfo() : Window_Text(){
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO);
	strcpy_s(text, WND_LINEINFO_BYTES, _T(""));
}

void Window_LineInfo::Setup(int x, int y, int w, BYTE _align){
	WINDOWAREA	frame(x, y, w, WND_LINEINFO_HEIGHT);
	WINDOWAREA	content(16, 16, w-32, FONTSIZE_INFO);
	frameArea.x = x;
	frameArea.y = y;
	Window_Text::Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE], frame, content, true);
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO);
	windowFont.align = _align;
	SetColor(GetColor(255,255,255));
}

void Window_LineInfo::SetText(LPTSTR buf, int length){
	strcpy_s(text, WND_LINEINFO_BYTES, buf); 
}

void Window_LineInfo::DrawContent() const{
	if(!GetActive()) return;
	int w = GetStrWidth(text, strlen(text), windowFont.hFont);
	int drawX = frameArea.x + contentArea.x;
	switch(windowFont.align){
	case ALIGN_CENTER:
		drawX += (contentArea.w - w)/2;
		break;
	case ALIGN_RIGHT:
		drawX += (contentArea.w - w);
		break;
	}
	DrawStringToHandle(drawX, frameArea.y + contentArea.y, text,
		windowFont.color, windowFont.hFont);
	// GetDrawDeltaX(, strlen(text));
}