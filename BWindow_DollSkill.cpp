// BWindow_DollSkill.cpp

#include "BWindow_DollSkill.h"
#include "WindowSkin.h"
#include "Record_AliceInfo.h"
#include "DXFont.h"
#include "Game_BattleDoll.h"
#include "Static_AliceDoll.h"
#include "Data_SkillInfo.h"
#include "Scene_Battle.h"
#include "BWindow_FocusedUnit.h"
#include "BWindow_DollCommand.h"

extern WindowSkins			g_wndSkins;
extern Record_AliceInfo		r_aliceInfo;
extern DXFont				g_font;
extern Data_SkillInfo		d_skillInfo;

BWindow_DollSkill::BWindow_DollSkill() : Window_Selectable(),
pTarget(NULL), pScene(NULL), pWndCommand(NULL){
	// select.canChooseInactive = true;
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		costMP[n] = 0;
	}
}

void BWindow_DollSkill::MySetup(Scene_Battle* _pScene, BWindow_DollCommand* _pWndCommand){
	Window_Selectable_Content content;
	WINDOWAREA		frameArea(
		BWND_DOLLSKILL_X, BWND_DOLLSKILL_Y,
		BWND_DOLLSKILL_W, BWND_DOLLSKILL_H);
	WINDOWFONT		font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+5, ALIGN_LEFT);
	ClearContent();
	SetGridSize(2, 4);
	Window_Selectable::Setup_FixPadding(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, BWND_DOLLSKILL_PX, BWND_DOLLSKILL_PY,
		font);
	pScene = _pScene;
	pTarget = NULL;
	pWndCommand = _pWndCommand;
	SetAllColor(WINDOWFONT_DEFCOLOR, WINDOWFONT_DEFICOLOR, WINDOWFONT_DEFNCOLOR);
}

void BWindow_DollSkill::OnOpened(){
	TCHAR	buf[MAX_SKILL_BYTES];
	ClearContent();
	// �l�`�̎����Ă���X�L���̔z����擾����B
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		// �X�L��ID��0�̏ꍇ�͖���
		if(pOwner->GetSkillID(n) != 0){
			d_skillInfo.GetSkillName(buf, pOwner->GetSkillID(n));
			SetContent(buf, n, true);
			costMP[n] = d_skillInfo.GetCostMP(pOwner->GetSkillID(n));
		}
	}
	select.index = 0;
	pTarget = NULL;

	// �X�L���̏���\������E�B���h�E���J���B
	pScene->OpenSkillAccLineWindow();
	// �X�L���̏��𔽉f������
	OnIndexChanged();
}

void BWindow_DollSkill::OnChildIsClosed(){
	// �ʒu�����ɖ߂�
	SetPosition(BWND_DOLLSKILL_X, BWND_DOLLSKILL_Y);
	// �q�E�B���h�E��Window_FocusedUnit���g�p
	BWindow_FocusedUnit* pFocusedUnitWindow = (BWindow_FocusedUnit*)pChildWindow;
	if(pFocusedUnitWindow->GetSelectIndex() != SELECTRESULT_CANCELED){
		// ���Z��I�������ꍇ
		// ���̃E�B���h�E���R�}���h�E�B���h�E������
		pTarget = pFocusedUnitWindow->GetTargetAsCommandTarget();
		Close(true, false);
		// �X�L���̏���\������E�B���h�E�����B
		pScene->CloseSkillAccLineWindow();
		if(pWndCommand){	
			pWndCommand->SetPhaze(BWND_DOLLCOMMAND_PHAZE_NONE);
		}
	}else{
		// �������Ȃ��i���Z�̑I���ɖ߂�j
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
	// strcpy_s(buf, 63, _T("���Ȃ��H�ׂ���"));
	pInfo->SetText(buf, strlen(buf));
}

void BWindow_DollSkill::Update(){
	int tmpSkillID = 0;
	BYTE targetType = 0x00;
	// �J�[�\���̈ړ����m�F����
	int oldIndex = select.index;
	Window_Selectable::Update();
	if(select.index != oldIndex){
		OnIndexChanged();
	}
	// �X�e�[�g�ɂ�镪��
	switch(state){
	case UPDATING:
		switch(select.CheckKey()){
		case SELECT2D_CHOOSE:
			if(costMP[select.index] <= r_aliceInfo.GetMP()){
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
			}else{
				// �I��s�̍���
			}
			break;
		case SELECT2D_CANCEL:
			if(cancelable){
				select.index = SELECTRESULT_CANCELED;
				pWndCommand->SetPhaze(BWND_DOLLCOMMAND_PHAZE_MAIN);
				Close(true, false);
				// �X�L���̏���\������E�B���h�E�����B
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

void BWindow_DollSkill::DrawContentItem(int index, BYTE color) const{
	// color�l�͎��ۂɂƂ͈Ⴄ���̂�p����
	bool canUse = (r_aliceInfo.GetMP() >= costMP[index]);
	BYTE useColor = (!canUse ? WND_SELECTABLE_COLOR_INACTIVE 
		: (index == select.index 
		? WND_SELECTABLE_COLOR_SELECTED 
		: WND_SELECTABLE_COLOR_ACTIVE));
	Window_Selectable::DrawContentItem(index, useColor);
	WINDOWAREA area = GetDrawArea(index);
	TCHAR buf[8];
	wsprintf(buf, _T("%d"), costMP[index]);
	int width = GetStrWidth(buf, strlen(buf), g_font.hInfo);
	DrawStr(area.x+area.w-width-2, area.y, buf, GetItemColor(useColor), g_font.hInfo); 
}