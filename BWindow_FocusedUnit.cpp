// BWindow_FocusedUnit.cpp


#include "BWindow_FocusedUnit.h"
#include "Static_Battle.h"
#include "Scene_Battle.h"
#include "WindowSkin.h"

extern	WindowSkins	g_wndSkins;

BWindow_FocusedUnit::BWindow_FocusedUnit() : Window_Base(),
	s_target(MAX_BATTLEENEMY, 0, false, true){
		pScene = NULL;
		pOwner = NULL;
		pTarget = NULL;
		focusTarget = BWND_FOCUS_TARGET_NONE;
		focusType = BWND_FOCUS_TYPE_UNDIFINED;
		flags = 0x00;
}

void BWindow_FocusedUnit::MySetup(Scene_Battle* _pScene){
	WINDOWAREA frameArea(-100, -100, BWND_FOCUSEDENEMY_WIDTH, BWND_FOCUSEDENEMY_HEIGHT);
	Window_Base::Setup_FixPadding(
		&g_wndSkins.skin[WNDSKIN_NONE],
		frameArea, 16, 16, true);
	pScene = _pScene;
}


void BWindow_FocusedUnit::OnOpened(){
	pTarget = NULL;
	s_target.index = 0;
	CheckEnemyEnabled();
	if(focusTarget == BWND_FOCUS_TARGET_ONE_ENEMY){
		if(!SetDefaultIndex()){
			// �I���ɃG���[����������
			s_target.index = -1;
		}
	}else{
		s_target.index = 0;
	}
	OnIndexChanged();
}

void BWindow_FocusedUnit::OnIndexChanged(){
	Game_BattleEnemy*	pEnemy = NULL;
	if(pScene == NULL) return;
	switch(focusTarget){
	case BWND_FOCUS_TARGET_ONE_ENEMY:
		if(s_target.index >= 0 && s_target.index < MAX_BATTLEENEMY){
			pEnemy = pScene->GetEnemyPtr(s_target.index);
			if(pEnemy == NULL) return;
			SetPosition(pEnemy->GetDrawX(), pEnemy->GetDrawY());
			pTarget = (Game_BattleUnit*)pEnemy;
		}
		break;
	}
}

bool BWindow_FocusedUnit::SetDefaultIndex(){
	Game_BattleEnemy* pTmpTarget;
	if(pScene == NULL) return false;
	if(pOwner == NULL) return false;
	// �ԍ��̎Ⴂ���ɁA�����ŗL���ȓG�ɃJ�[�\�������킹�悤�Ƃ���B
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpTarget = pScene->GetEnemyPtr(n);
		if(pTmpTarget == NULL){
			continue;
		}
		if(!pTmpTarget->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pOwner->GetAttr(), pTmpTarget->GetAttr()) == ATTRAFFINITY_STRONG){
				s_target.index = n;
				return true;
		}
	}
	// �L���ȓG�����Ȃ���΁A���������ʂȓG�ɃJ�[�\�������킹�悤�Ƃ���B�B
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpTarget = pScene->GetEnemyPtr(n);
		if(pTmpTarget == NULL){
			continue;
		}
		if(!pTmpTarget->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pOwner->GetAttr(), pTmpTarget->GetAttr()) != ATTRAFFINITY_WEAK){
				s_target.index = n;
				return true;
		}
	}
	// �I�ׂ�G������ΑI��
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpTarget = pScene->GetEnemyPtr(n);
		if(pTmpTarget == NULL){
			continue;
		}
		if(!pTmpTarget->CanTarget()){
			continue;
		}
		s_target.index = n;
		return true;
	}
	s_target.index = -1;
	return false;
}

void BWindow_FocusedUnit::CheckEnemyEnabled(){
	Game_BattleEnemy* pTarget = NULL;
	if(pScene == NULL) return;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(n < pScene->GetEnemiesNum()){
			pTarget = pScene->GetEnemyPtr(n);
		}else{
			pTarget = NULL;
		}
		// �I���\���ǂ���
		if(pTarget == NULL){
			s_target.isActive[n] = false;
		}else if(!pTarget->CanTarget()){
			s_target.isActive[n] = false;
		}else{
			s_target.isActive[n] = true;
		}
	}
	s_target.maxSize = MAX_BATTLEENEMY;
}

void BWindow_FocusedUnit::Update(){
	int oldIndex = s_target.index;
	switch(state){
	case UPDATING:
		switch(s_target.Move()){
		case SELECT_CHOOSE:
			Close(true, true);
			break;
		case SELECT_CANCEL:
			s_target.index = SELECTRESULT_CANCELED;
			Close(true, true);
			break;
		}
		if(s_target.index != oldIndex){
			OnIndexChanged();
		}
		
		break;
	case SUSPENDED:
		state = UPDATING;
		break;
	case CLOSED:
		break;
	}
}

void BWindow_FocusedUnit::DrawContent() const{
	if(!GetActive()) return;
	Game_BattleEnemy*	pTmpEnemy = NULL;
	switch(focusTarget){
	case BWND_FOCUS_TARGET_ONE_ENEMY:
		DrawCntEnemy((Game_BattleEnemy*)pTarget);
		break;
	case BWND_FOCUS_TARGET_ALL_ENEMIES:
		// �S�Ă̓G�ɂ��ă��[�v����
		for(int n=0; n<MAX_BATTLEENEMY; n++){
			if(n < pScene->GetEnemiesNum()){
				pTmpEnemy = pScene->GetEnemyPtr(n);
				DrawCntEnemy(pTmpEnemy);
			}
		}
		break;
	case BWND_FOCUS_TARGET_ONE_DOLL:
		break;
	case BWND_FOCUS_TARGET_ALL_DOLLS:
		break;
	}
}

void BWindow_FocusedUnit::DrawCntEnemy(Game_BattleEnemy* p) const {
	int tmpX=0, tmpY=0;
	tmpX = p->GetDrawX();
	tmpY = p->GetDrawY()+20;
	DrawBox(
		tmpX-5, tmpY-5,
		tmpX+5, tmpY+5,
		GetColor(255, 0, 0), 1);
}

void BWindow_FocusedUnit::OpenWithParam(
	Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
	BYTE _focusTarget, BYTE _focusType, BYTE _flags){
		SetParam(_pOwner, _pTarget, _focusTarget, _focusType, _flags);
		Open(false, true);
}

void BWindow_FocusedUnit::SetParam(
	Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
	BYTE _focusTarget, BYTE _focusType, BYTE _flags){
		pOwner = _pOwner;
		pTarget = _pTarget;
		focusTarget = _focusTarget;
		focusType = _focusType;
		flags = _flags;
}

Game_BattleUnit* BWindow_FocusedUnit::GetTargetAsCommandTarget(){
	switch(focusTarget){
	case BWND_FOCUS_TARGET_ONE_DOLL:
	case BWND_FOCUS_TARGET_FIXED_DOLL:
		return (Game_BattleUnit*)pScene->GetFrontDollPtr(s_target.index);
		break;
	case BWND_FOCUS_TARGET_ONE_ENEMY:
	case BWND_FOCUS_TARGET_FIXED_ENEMY:
		return (Game_BattleUnit*)pScene->GetEnemyPtr(s_target.index);
		break;
	default:
		return NULL;
		break;
	}
	return NULL;
}

BYTE BWindow_FocusedUnit::ConvertTargetTypeToFocusType(BYTE targetType){
	switch(targetType){
	case ACTIONTARGET_TEAM_ONE:
		return BWND_FOCUS_TARGET_ONE_DOLL;
		break;
	case ACTIONTARGET_TEAM_ALL:
		return BWND_FOCUS_TARGET_ALL_DOLLS;
		break;
	case ACTIONTARGET_OPPONENT_ONE:
		return BWND_FOCUS_TARGET_ONE_ENEMY;
		break;
	case ACTIONTARGET_OPPONENT_ALL:
		return BWND_FOCUS_TARGET_ALL_ENEMIES;
		break;
	default:
		return BWND_FOCUS_TARGET_NONE;
	}
	return BWND_FOCUS_TARGET_NONE;
}
