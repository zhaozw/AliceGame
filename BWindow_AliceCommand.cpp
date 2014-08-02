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
	SetContent(_T("戦う"), 0, true);
	SetContent(_T("人形チェンジ"), 1, true);
	SetContent(_T("アリスの特技"), 2, true);
	SetContent(_T("逃げる"), 3, true);
	SetRowByContentSize(1);
	Window_Selectable::Setup_FixContentWidth_Auto(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, 16, font);
	SetVisible(true);

	// 現状コマンドは使用できない
	select.isActive[1] = false;
	select.isActive[2] = false;
}

void BWindow_AliceCommand::Update(){
	Window_Selectable::Update();
}

void BWindow_AliceCommand::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}