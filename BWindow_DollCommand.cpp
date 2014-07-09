// BWindow_DollCommand.cpp

#include "BWindow_DollCommand.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Scene_Battle.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;

BWindow_DollCommand::BWindow_DollCommand(){

}

void BWindow_DollCommand::MySetup(Scene_Battle* _pScene){
	Window_Selectable_Content content;
	Window_Selectable::Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		BWND_DOLLCOMMAND_X, BWND_DOLLCOMMAND_Y,
		content,
		1,
		g_font.hInfo,
		FONTSIZE_INFO,
		FONTSIZE_INFO+4,
		false, false, ALIGN_LEFT);
	SetVisible(true);
	SetContent(_T("攻撃"), 0);
	SetContent(_T("特技"), 1);
	SetContent(_T("防御"), 2);
	SetAllColor(
		GetColor(255, 255, 255),
		GetColor(192, 192, 192),
		GetColor(64, 64, 64));
	// 内容を元にセットアップする
	SetDefParam();
	pScene = _pScene;
	Refresh();
}

void BWindow_DollCommand::Refresh(){
	commandIndex = 0;
	subIndex = -1;
	targetIndex = 0;
}

void BWindow_DollCommand::Update(){
	Window_Selectable::Update();
	switch(state){
	case UPDATING:
		if(select.CheckKey() == SELECT2D_CHOOSE){
			switch(GetSelectIndex()){
			case BWND_DOLLCOMMAND_ATTACK:
				// 攻撃相手選択ウィンドウを開く
				commandIndex = BWND_DOLLCOMMAND_ATTACK;
				OpenChildWindow((Window_Base*)pScene->GetWndSelectEnemyPtr());
				break;
			case BWND_DOLLCOMMAND_SKILL:
				// スキル選択ウィンドウを開く
				commandIndex = BWND_DOLLCOMMAND_SKILL;
				break;
			case BWND_DOLLCOMMAND_GUARD:
				// 防御コマンドを選択して終了
				commandIndex = BWND_DOLLCOMMAND_GUARD;
				break;
			}
		}
		break;
	case SUSPENDED:
		// SUSPENDED状態の判定
		state = UPDATING;
		break;
	}
}

void BWindow_DollCommand::CheckAutoClose(){
	switch(GetSelectIndex()){
	case BWND_DOLLCOMMAND_ATTACK:
	case BWND_DOLLCOMMAND_SKILL:
		autoClose = false;
		break;
	case BWND_DOLLCOMMAND_GUARD:
		autoClose = true;
		break;
	}
}

void BWindow_DollCommand::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}