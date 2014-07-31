// BWindow_DollSkill.cpp

#include "BWindow_DollSkill.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Game_BattleDoll.h"
#include "Static_AliceDoll.h"
#include "Data_SkillInfo.h"
#include "Scene_Battle.h"
#include "BWindow_FocusedUnit.h"
#include "BWindow_DollCommand.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;
extern Data_SkillInfo		d_skillInfo;

BWindow_DollSkill::BWindow_DollSkill() : Window_Selectable(),
pTarget(NULL), pScene(NULL), pWndCommand(NULL){

}

void BWindow_DollSkill::MySetup(Scene_Battle* _pScene, BWindow_DollCommand* _pWndCommand){
	Window_Selectable_Content content;
	WINDOWAREA		frameArea(
		BWND_DOLLSKILL_X, BWND_DOLLSKILL_Y,
		BWND_DOLLSKILL_W, BWND_DOLLSKILL_H);
	WINDOWFONT		font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+5, ALIGN_CENTER);
	ClearContent();
	SetGridSize(2, 4);
	Window_Selectable::Setup_FixPadding(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, BWND_DOLLSKILL_PX, BWND_DOLLSKILL_PY,
		font);
	pScene = _pScene;
	pTarget = NULL;
	pWndCommand = _pWndCommand;
}

void BWindow_DollSkill::OnOpened(){
	TCHAR	buf[MAX_SKILL_BYTES];
	ClearContent();
	// 人形の持っているスキルの配列を取得する。
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		// スキルIDが0の場合は無効
		if(pOwner->GetSkillID(n) != 0){
			d_skillInfo.GetSkillName(buf, pOwner->GetSkillID(n));
			SetContent(buf, n, true);
		}
	}
	select.index = 0;
	pTarget = NULL;

	// スキルの情報を表示するウィンドウを開く。
	pScene->OpenSkillAccLineWindow();
	// スキルの情報を反映させる
	OnIndexChanged();
}

void BWindow_DollSkill::OnChildIsClosed(){
	// 位置を元に戻す
	SetPosition(BWND_DOLLSKILL_X, BWND_DOLLSKILL_Y);
	// 子ウィンドウはWindow_FocusedUnitを使用
	BWindow_FocusedUnit* pFocusedUnitWindow = (BWindow_FocusedUnit*)pChildWindow;
	if(pFocusedUnitWindow->GetSelectIndex() != SELECTRESULT_CANCELED){
		// 特技を選択した場合
		// このウィンドウもコマンドウィンドウも閉じる
		pTarget = pFocusedUnitWindow->GetTargetAsCommandTarget();
		Close(true, false);
		// スキルの情報を表示するウィンドウを閉じる。
		pScene->CloseSkillAccLineWindow();
		if(pWndCommand){	
			pWndCommand->SetPhaze(BWND_DOLLCOMMAND_PHAZE_NONE);
		}
	}else{
		// 何もしない（特技の選択に戻る）
		state = UPDATING;
		if(pWndCommand){	
			pWndCommand->SetPhaze(BWND_DOLLCOMMAND_PHAZE_TARGET);
		}
	}
}

void BWindow_DollSkill::OnIndexChanged(){
	Window_LineInfo* pInfo = pScene->GetSkillAccLinePtr();
	TCHAR buf[64];
	int tmpSkillID = pOwner->GetSkillID(select.index);
	d_skillInfo.GetSkillAccount(buf, tmpSkillID);
	// strcpy_s(buf, 63, _T("うなぎ食べたい"));
	pInfo->SetText(buf, strlen(buf));
}

void BWindow_DollSkill::Update(){
	int tmpSkillID = 0;
	BYTE targetType = 0x00;
	// カーソルの移動を確認する
	int oldIndex = select.index;
	Window_Selectable::Update();
	if(select.index != oldIndex){
		OnIndexChanged();
	}
	// ステートによる分岐
	switch(state){
	case UPDATING:
		switch(select.CheckKey()){
		case SELECT2D_CHOOSE:
			tmpSkillID = pOwner->GetSkillID(select.index);
			targetType = d_skillInfo.GetTargetType(tmpSkillID);
			if(tmpSkillID == 0) return;
			if(targetType != ACTIONTARGET_NONE){
				pScene->GetWndFocusedUnitPtr()->SetParam(
					pOwner, NULL,
					BWindow_FocusedUnit::ConvertTargetTypeToFocusType(targetType),
					BWND_FOCUS_TYPE_SKILL);
				OpenChildWindow((Window_Base*)pScene->GetWndFocusedUnitPtr(), true);
				pWndCommand->SetPhaze(BWND_DOLLCOMMAND_PHAZE_TARGET);
			}
			break;
		case SELECT2D_CANCEL:
			if(cancelable){
				select.index = SELECTRESULT_CANCELED;
				Close(true, false);
				// スキルの情報を表示するウィンドウを閉じる。
				pScene->CloseSkillAccLineWindow();
				break;
			}
			break;
		}
		break;
	case SUSPENDED:
		state = UPDATING;
		break;
	}
}

void BWindow_DollSkill::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}