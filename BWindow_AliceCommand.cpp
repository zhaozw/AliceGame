// BWindow_AliceCommand.cpp

#include "BWindow_AliceCommand.h"
#include "WindowSkin.h"
#include "DXFont.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;

BWindow_AliceCommand::BWindow_AliceCommand(){

}

void BWindow_AliceCommand::MySetup(){
	Window_Selectable_Content content;
	Window_Selectable::Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		BWND_ALICECOMMAND_X, BWND_ALICECOMMAND_Y,
		content,
		1,
		g_font.hInfo,
		FONTSIZE_INFO,
		FONTSIZE_INFO+4,
		false, false, ALIGN_LEFT);
	SetVisible(true);
	SetContent(_T("�키"), 0);
	SetContent(_T("�l�`�`�F���W"), 1);
	SetContent(_T("�A���X�̓��Z"), 2);
	SetContent(_T("������"), 3);
	SetAllColor(
		GetColor(255, 255, 255),
		GetColor(192, 192, 192),
		GetColor(64, 64, 64));
	// ���e�����ɃZ�b�g�A�b�v����
	SetDefParam();
}

void BWindow_AliceCommand::Update(){
	Window_Selectable::Update();
}

void BWindow_AliceCommand::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}