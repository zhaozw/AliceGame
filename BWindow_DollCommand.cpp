// BWindow_DollCommand.cpp

#include "BWindow_DollCommand.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Scene_Battle.h"
#include "Sprite_BattleDoll.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;

BWindow_DollCommand::BWindow_DollCommand(){

}

void BWindow_DollCommand::MySetup(Scene_Battle* _pScene){
	WINDOWAREA	frameArea(
		BWND_DOLLCOMMAND_X, BWND_DOLLCOMMAND_Y,
		BWND_DOLLCOMMAND_W, BWND_DOLLCOMMAND_H);
	WINDOWFONT	font(
		g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4, ALIGN_CENTER);
	Window_Selectable_Content content;
	SetContent(_T("攻撃"), 0, true);
	SetContent(_T("特技"), 1, true);
	SetContent(_T("防御"), 2, true);
	SetRowByContentSize(1);
	Window_Selectable::Setup_FixContentWidth(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, BWND_DOLLCOMMAND_W-32, 16, font);
	SetVisible(true);
	// 内容を元にセットアップする
	pScene = _pScene;
	Refresh();
}

void BWindow_DollCommand::OpenWithActor(Game_BattleDoll* pDoll, bool _cancelable){
	TCHAR buf[BATTLEUNIT_NAME_BYTES];
	pActor = pDoll;
	pDoll->GetName(buf, BATTLEUNIT_NAME_BYTES);
	MySetup(pScene);
	SetTitle(buf, g_font.hInfo, FONTSIZE_INFO+16);
	select.index = 0;
	commandIndex = 0;
	cancelable = _cancelable;
	Open();
}

void BWindow_DollCommand::Refresh(){
	commandIndex = 0;
	subIndex = -1;
	targetIndex = 0;
}

void BWindow_DollCommand::Update(){
	switch(state){
	case UPDATING:
		switch(select.CheckKey()){
		case SELECT2D_CHOOSE:
			switch(GetSelectIndex()){
			case BWND_DOLLCOMMAND_ATTACK:
				// 攻撃相手選択ウィンドウを開く
				commandIndex = BWND_DOLLCOMMAND_ATTACK;
				pScene->GetWndFocusedEnemyPtr()->SetFocusAll(false);
				pScene->GetWndFocusedEnemyPtr()->SetDoll(pActor);
				OpenChildWindow((Window_Base*)pScene->GetWndFocusedEnemyPtr(), true);
				break;
			case BWND_DOLLCOMMAND_SKILL:
				commandIndex = BWND_DOLLCOMMAND_SKILL;
				pScene->GetWndDollSkillPtr()->SetDoll(pActor);
				OpenChildWindow((Window_Base*)pScene->GetWndDollSkillPtr(), false);
				break;
			case BWND_DOLLCOMMAND_GUARD:
				// 防御コマンドを選択して終了
				commandIndex = BWND_DOLLCOMMAND_GUARD;
				SetCommandAndClose();
				break;
			}
			break;
		case SELECT2D_CANCEL:
			if(cancelable){
				// 前の人形に戻る。
				commandIndex = -1;
				SetCommandAndClose();
			}					
			break;
		}
		break;
	case SUSPENDED:
		// SUSPENDED状態の判定
		state = UPDATING;
		break;
	}
	Window_Selectable::Update();
}

void BWindow_DollCommand::OnChildIsClosed(){
	// 子ウィンドウのハンドルを取得
	BWindow_FocusedEnemy*	pFocusWindow = NULL;
	BWindow_DollSkill*		pDollSkill = NULL;

	switch(GetSelectIndex()){
	case BWND_DOLLCOMMAND_ATTACK:
		pFocusWindow = (BWindow_FocusedEnemy*)pChildWindow;
		if(pFocusWindow == NULL) return;
		// 決定キーかキャンセルキーかで分岐
		if(pFocusWindow->GetSelectIndex() == SELECTRESULT_CANCELED){
			// 何もしない
			state = UPDATING;
		}else{
			// 攻撃としてターゲットを取得する
			targetIndex = pFocusWindow->GetSelectIndex();
			SetCommandAndClose();
		}
		break;
	case BWND_DOLLCOMMAND_SKILL:
		pDollSkill = (BWindow_DollSkill*)pChildWindow;
		if(pDollSkill == NULL) return;
		// 決定キーかキャンセルキーかで分岐
		if(pDollSkill->GetSelectIndex() == SELECTRESULT_CANCELED){
			// 何もしない
			state = UPDATING;
		}else{
			/*
			// 攻撃としてターゲットを取得する
			targetIndex = pFocusWindow->GetSelectIndex();
			SetCommandAndClose();
			*/
		}
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

bool BWindow_DollCommand::SetCommandAndClose(){
	// ウィンドウの取得
	BWindow_FocusedEnemy* pFocusWindow = (BWindow_FocusedEnemy*)pChildWindow;
	// アクションスタックに追加するもの
	Game_UnitCommand cmd;

	switch(commandIndex){
	case BWND_DOLLCOMMAND_ATTACK:
		cmd.SetOwner((Game_BattleUnit*)pActor);
		cmd.SetTarget(pFocusWindow->GetEnemyPtr());
		cmd.SetActionType(ACTIONTYPE_ATTACK);
		cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
		pScene->SetCommand(cmd);
		state = Window_Base::IDLE;
		Close();
		break;
	case BWND_DOLLCOMMAND_SKILL:
		cmd.SetOwner((Game_BattleUnit*)pActor);
		cmd.SetTarget(pFocusWindow->GetEnemyPtr());
		cmd.SetActionType(ACTIONTYPE_ATTACK);
		cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
		pScene->SetCommand(cmd);
		state = Window_Base::IDLE;
		Close();
		break;
	case BWND_DOLLCOMMAND_GUARD:
		cmd.SetOwner((Game_BattleUnit*)pActor);
		cmd.SetTarget(NULL);
		cmd.SetActionType(ACTIONTYPE_GUARD);
		cmd.SetTargetType(ACTIONTARGET_NONE);
		pScene->SetCommand(cmd);
		state = Window_Base::IDLE;
		Close();
		break;
	case -1:
		cmd.Reset();
		state = Window_Base::IDLE;
		// キャンセルの場合、何もせずに閉じる
		Close();
		break;
	}
	return true;
}

BYTE BWindow_DollCommand::Close(bool force, bool sudden){
	Sprite_BattleDoll* pSprite=NULL;
	if(pScene != NULL){
		pSprite = pScene->GetDollSprite(pActor);
		pSprite->SetMorphID(SPMORPH_DISACTIVATE, true);
	}
	return Window_Base::Close();
}