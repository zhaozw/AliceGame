// BWindow_DollCommand.cpp

#include "BWindow_DollCommand.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Scene_Battle.h"
#include "Sprite_BattleDoll.h"
#include "Data_SkillInfo.h"


extern WindowSkins			g_wndSkins;
extern DXFont				g_font;
extern Data_SkillInfo		d_skillInfo;

BWindow_DollCommand::BWindow_DollCommand() : Window_Selectable(){
	pScene = NULL;
	pActor = NULL;
	commandIndex = -1;
	subIndex = -1;
	targetIndex = 0;
	cancelable = false;
	phaze = BWND_DOLLCOMMAND_PHAZE_NONE;
}

void BWindow_DollCommand::MySetup(Scene_Battle* _pScene){
	WINDOWAREA	frameArea(
		BWND_DOLLCOMMAND_X, BWND_DOLLCOMMAND_Y,
		BWND_DOLLCOMMAND_W, BWND_DOLLCOMMAND_H);
	WINDOWFONT	font(
		g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4, ALIGN_CENTER);
	Window_Selectable_Content content;
	SetContent(_T("�U��"), 0, true);
	SetContent(_T("���Z"), 1, true);
	SetContent(_T("�h��"), 2, true);
	SetRowByContentSize(1);
	Window_Selectable::Setup_FixContentWidth(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, BWND_DOLLCOMMAND_W-32, 16, font);
	SetVisible(true);
	// ���e�����ɃZ�b�g�A�b�v����
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

void BWindow_DollCommand::OnOpened(){
	Window_Selectable::OnOpened();
	// �X�L���R�}���h��I���\��
	if(pActor != NULL){
		if(pActor->GetSkillID(0) == 0){
			// �X�L���R�}���h�I��s��
			select.isActive[BWND_DOLLCOMMAND_SKILL] = false;
		}
	}
}

void BWindow_DollCommand::Refresh(){
	select.Reset();
	commandIndex = 0;
	subIndex = -1;
	targetIndex = 0;
	phaze = BWND_DOLLCOMMAND_PHAZE_MAIN;
}

void BWindow_DollCommand::Update(){
	switch(state){
	case UPDATING:
		switch(select.CheckKey()){
		case SELECT2D_CHOOSE:
			switch(GetSelectIndex()){
			case BWND_DOLLCOMMAND_ATTACK:
				// �U������I���E�B���h�E���J��
				commandIndex = BWND_DOLLCOMMAND_ATTACK;
				pScene->GetWndFocusedUnitPtr()->SetParam(
					pActor, NULL, BWND_FOCUS_TARGET_ONE_ENEMY, BWND_FOCUS_TYPE_ATTACK);
				OpenChildWindow((Window_Base*)pScene->GetWndFocusedUnitPtr(), true);
				phaze = BWND_DOLLCOMMAND_PHAZE_TARGET;
				break;
			case BWND_DOLLCOMMAND_SKILL:
				commandIndex = BWND_DOLLCOMMAND_SKILL;
				pScene->GetWndDollSkillPtr()->SetDoll(pActor);
				OpenChildWindow((Window_Base*)pScene->GetWndDollSkillPtr(), false);
				phaze = BWND_DOLLCOMMAND_PHAZE_SKILL;
				break;
			case BWND_DOLLCOMMAND_GUARD:
				// �h��R�}���h��I�����ďI��
				commandIndex = BWND_DOLLCOMMAND_GUARD;
				SetCommandAndClose();
				break;
			}
			break;
		case SELECT2D_CANCEL:
			if(cancelable){
				// �O�̐l�`�ɖ߂�B
				commandIndex = -1;
				SetCommandAndClose();
			}					
			break;
		}
		break;
	case SUSPENDED:
		// SUSPENDED��Ԃ̔���
		state = UPDATING;
		break;
	}
	Window_Selectable::Update();
}

void BWindow_DollCommand::OnChildIsClosed(){
	// �q�E�B���h�E�̃n���h�����擾
	BWindow_FocusedUnit*	pFocusWindow = NULL;
	BWindow_DollSkill*		pDollSkill = NULL;

	switch(GetSelectIndex()){
	case BWND_DOLLCOMMAND_ATTACK:
		pFocusWindow = (BWindow_FocusedUnit*)pChildWindow;
		if(pFocusWindow == NULL) return;
		// ����L�[���L�����Z���L�[���ŕ���
		if(pFocusWindow->GetSelectIndex() == SELECTRESULT_CANCELED){
			// �������Ȃ�
			state = UPDATING;
		}else{
			// �U���Ƃ��ă^�[�Q�b�g���擾����
			targetIndex = pFocusWindow->GetSelectIndex();
			SetCommandAndClose();
		}
		break;
	case BWND_DOLLCOMMAND_SKILL:
		pDollSkill = (BWindow_DollSkill*)pChildWindow;
		if(pDollSkill == NULL) return;
		// ����L�[���L�����Z���L�[���ŕ���
		if(pDollSkill->GetSelectIndex() == SELECTRESULT_CANCELED){
			// �������Ȃ�
			state = UPDATING;
		}else{
			SetCommandAndClose();
			/*
			// �U���Ƃ��ă^�[�Q�b�g���擾����
			targetIndex = pFocusWindow->GetSelectIndex();
			SetCommandAndClose();
			*/
		}
		break;
	}
	phaze = BWND_DOLLCOMMAND_PHAZE_MAIN;
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
	// �E�B���h�E�̎擾
	BWindow_FocusedUnit*	pFocusWindow = NULL; 
	BWindow_DollSkill*		pSkillWindow = NULL;
	// �A�N�V�����X�^�b�N�ɒǉ��������
	Game_UnitCommand	cmd;
	// �^�[�Q�b�g�̌`�����󂯎��
	BYTE				targetType = 0;
	BYTE				cntSkillID = 0;

	switch(commandIndex){
	case BWND_DOLLCOMMAND_ATTACK:
		pFocusWindow = (BWindow_FocusedUnit*)pChildWindow;
		cmd.SetOwner((Game_BattleUnit*)pActor);
		cmd.SetTarget(pFocusWindow->GetTarget());
		cmd.SetActionType(ACTIONTYPE_ATTACK);
		cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
		pScene->SetCommand(cmd);
		state = Window_Base::IDLE;
		Close();
		break;
	case BWND_DOLLCOMMAND_SKILL:
		pSkillWindow = (BWindow_DollSkill*)pChildWindow;
		cmd.SetOwner((Game_BattleUnit*)pActor);
		cmd.SetActionType(ACTIONTYPE_SKILL);
		cntSkillID = pActor->GetSkillID(pSkillWindow->GetSelectIndex());
		if(cntSkillID > 0){
			targetType = d_skillInfo.GetTargetType(cntSkillID); // �X�L���̃^�[�Q�b�g
			targetType = ConvertSkillTargetToTarget(targetType); // �l�`���猩���^�[�Q�b�g
			cmd.SetTargetType(targetType);
			cmd.SetTarget(pSkillWindow->GetTarget());
			cmd.SetSkillID(cntSkillID);
			pScene->SetCommand(cmd);
		}
		state = Window_Base::IDLE;
		Close();
		break;
	case BWND_DOLLCOMMAND_GUARD:
		pFocusWindow = (BWindow_FocusedUnit*)pChildWindow;
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
		// �L�����Z���̏ꍇ�A���������ɕ���
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

BYTE BWindow_DollCommand::ConvertSkillTargetToTarget(BYTE skillTarget){
	switch(skillTarget){
	case ACTIONTARGET_TEAM_ONE:
	case ACTIONTARGET_SELF:
		return ACTIONTARGET_DOLL_ONE;
		break;
	case ACTIONTARGET_TEAM_ALL:
		return ACTIONTARGET_DOLL_ALL;
		break;
	case ACTIONTARGET_OPPONENT_ONE:
		return ACTIONTARGET_ENEMY_ONE;
		break;
	case ACTIONTARGET_OPPONENT_ALL:
		return ACTIONTARGET_ENEMY_ALL;
		break;
	}
	return ACTIONTARGET_NONE;
}