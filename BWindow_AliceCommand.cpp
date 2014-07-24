// BWindow_AliceCommand.cpp

#include "BWindow_AliceCommand.h"
#include "WindowSkin.h"
#include "DXFont.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;

BWindow_AliceCommand::BWindow_AliceCommand() : Window_Selectable(){
}

void BWindow_AliceCommand::MySetup(){
	WINDOWAREA		frameArea(
		BWND_ALICECOMMAND_X, BWND_ALICECOMMAND_Y,
		BWND_ALICECOMMAND_W, BWND_ALICECOMMAND_H);
	WINDOWFONT	font(
		g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4, ALIGN_LEFT);
	Window_Selectable_Content content;
	strcpy_s(content.data[0], WND_SELECTABLE_STRLENGTH-1, _T("戦う"));
	strcpy_s(content.data[1], WND_SELECTABLE_STRLENGTH-1, _T("人形チェンジ"));
	strcpy_s(content.data[2], WND_SELECTABLE_STRLENGTH-1, _T("アリスの特技"));
	strcpy_s(content.data[3], WND_SELECTABLE_STRLENGTH-1, _T("逃げる"));
	Window_Selectable::Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, 16, 16, font, 100);
	SetVisible(true);
}

void BWindow_AliceCommand::Update(){
	Window_Selectable::Update();
}

void BWindow_AliceCommand::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}