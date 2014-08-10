// BWindow_FocusedUnit.cpp


#include "BWindow_FocusedUnit.h"
#include "Static_Battle.h"
#include "Scene_Battle.h"
#include "WindowSkin.h"
#include "Sprite_BattleDoll.h"
#include "Func_Graphics.h"
#include "Image.h"

extern	WindowSkins	g_wndSkins;
extern	Image		g_image;	

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
	switch(focusTarget){
	case BWND_FOCUS_TARGET_ONE_ENEMY:
		CheckEnemyEnabled();
		if(!SetDefaultEnemyIndex()){
			// 選択にエラーが発生した
			s_target.index = -1;
		}
		break;
	case BWND_FOCUS_TARGET_ONE_DOLL:
		CheckDollEnabled();
		if(!SetDefaultDollIndex()){
			// 選択にエラーが発生した
			s_target.index = -1;
		}
		break;
	default:
		s_target.index = 0;
		break;
	}
	switch(focusType){
	case BWND_FOCUS_TYPE_SKILL:
		// ウィンドウの位置を人形が見やすい位置に移動する
		if(focusTarget == BWND_FOCUS_TARGET_ONE_DOLL 
			|| focusTarget == BWND_FOCUS_TARGET_ALL_DOLLS){
				pScene->GetWndDollSkillPtr()->SetPosition(
					BWND_DOLLSKILL_X, BWND_DOLLSKILL_Y-260);
		}
		break;
	}
	OnIndexChanged();
}

void BWindow_FocusedUnit::OnIndexChanged(){
	Game_BattleEnemy*	pEnemy = NULL;
	Game_BattleDoll*	pDoll = NULL;
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
	case BWND_FOCUS_TARGET_ONE_DOLL:
		if(s_target.index >= 0 && s_target.index < NUM_BATTLEDOLL_FRONT){
			pDoll = pScene->GetFrontDollPtr(s_target.index);
			if(pDoll == NULL) return;
			pTarget = (Game_BattleUnit*)pDoll;
		}		
	}
}


bool BWindow_FocusedUnit::SetDefaultEnemyIndex(){
	Game_BattleEnemy* pTmpTarget;
	if(pScene == NULL) return false;
	if(pOwner == NULL) return false;
	// 番号の若い順に、属性で有利な敵にカーソルを合わせようとする。
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpTarget = pScene->GetEnemyPtr(n);
		if(pTmpTarget == NULL){
			continue;
		}
		if(!pTmpTarget->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pOwner->GetAmendedAttr(), pTmpTarget->GetAmendedAttr()) == ATTRAFFINITY_STRONG){
				s_target.index = n;
				return true;
		}
	}
	// 有利な敵がいなければ、相性が普通な敵にカーソルを合わせようとする。。
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpTarget = pScene->GetEnemyPtr(n);
		if(pTmpTarget == NULL){
			continue;
		}
		if(!pTmpTarget->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pOwner->GetAmendedAttr(), pTmpTarget->GetAmendedAttr()) != ATTRAFFINITY_WEAK){
				s_target.index = n;
				return true;
		}
	}
	// 選べる敵が居れば選ぶ
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

bool BWindow_FocusedUnit::SetDefaultDollIndex(){
	Game_BattleDoll* pTmpTarget;
	if(pScene == NULL) return false;
	if(pOwner == NULL) return false;
	// 選べる敵が居れば選ぶ
	for(int n=0; n<NUM_BATTLEDOLL_FRONT; n++){
		pTmpTarget = pScene->GetFrontDollPtr(n);
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
		// 選択可能かどうか
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

void BWindow_FocusedUnit::CheckDollEnabled(){
	Game_BattleDoll* pTarget = NULL;
	if(pScene == NULL) return;
	for(int n=0; n<NUM_BATTLEDOLL_FRONT; n++){
		pTarget = pScene->GetFrontDollPtr(n);
		// 選択可能かどうか
		if(pTarget == NULL){
			s_target.isActive[n] = false;
		}else if(!pTarget->CanTarget()){
			s_target.isActive[n] = false;
		}else{
			s_target.isActive[n] = true;
		}
	}
	s_target.maxSize = NUM_BATTLEDOLL_FRONT;
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
	Window_Base::Update();
}

void BWindow_FocusedUnit::DrawContent() const{
	if(!GetActive()) return;
	Game_BattleEnemy*	pTmpEnemy = NULL;
	switch(focusTarget){
	case BWND_FOCUS_TARGET_ONE_ENEMY:
		DrawCntEnemy((Game_BattleEnemy*)pTarget);
		break;
	case BWND_FOCUS_TARGET_ALL_ENEMIES:
		// 全ての敵についてループする
		for(int n=0; n<MAX_BATTLEENEMY; n++){
			if(n < pScene->GetEnemiesNum()){
				pTmpEnemy = pScene->GetEnemyPtr(n);
				if(pTmpEnemy->CanTarget()){
					DrawCntEnemy(pTmpEnemy);
				}
			}
		}
		break;
	case BWND_FOCUS_TARGET_ONE_DOLL:
		DrawCntDoll(s_target.index);
		break;
	case BWND_FOCUS_TARGET_ALL_DOLLS:
		for(BYTE n=0; n<NUM_BATTLEDOLL_FRONT; n++){
			DrawCntDoll(n);
		}
		break;
	}
}

void BWindow_FocusedUnit::DrawCntEnemy(Game_BattleEnemy* p) const {
	int tmpX=0, tmpY=0;
	tmpX = p->GetDrawX();
	tmpY = p->GetDrawY()+20;
	int dltY = 0;
	dltY = 8*sin(2.0*M_PI*activeCount/35); 
	
	DrawRotaGraph(tmpX, tmpY+dltY, 1.0, 0,
		g_image.icon.cursor[1], 1);
	/*
	DrawBox(
		tmpX-5, tmpY+dltY-5,
		tmpX+5, tmpY+dltY+5,
		GetColor(
		GetRainbowR(activeCount*20),
		GetRainbowG(activeCount*20),
		GetRainbowB(activeCount*20)
		), 1);
		*/
}

void BWindow_FocusedUnit::DrawCntDoll(BYTE n) const {
	int tmpX=0, tmpY=0;
	tmpX = SPRITE_BATTLEDOLL_IX+n*SPRITE_BATTLEDOLL_DX+SPRITE_BATTLEDOLL_WIDTH/2;
	tmpY = SPRITE_BATTLEDOLL_IY-20 + 8*sin(2.0*M_PI*activeCount/35);

	DrawRotaGraph(tmpX, tmpY, 1.0, 0,
		g_image.icon.cursor[0], 1);

	/*
	DrawBox(
		tmpX-5, tmpY-5,
		tmpX+5, tmpY+5,
		GetColor(255, 0, 0), 1);
		*/
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

BYTE BWindow_FocusedUnit::ConvertTargetTypeToFocusType(BYTE skillTarget){
	switch(skillTarget){
	case SKILLTARGET_TEAM_ONE:
		return BWND_FOCUS_TARGET_ONE_DOLL;
		break;
	case SKILLTARGET_TEAM_ALL:
		return BWND_FOCUS_TARGET_ALL_DOLLS;
		break;
	case SKILLTARGET_OPPONENT_ONE:
		return BWND_FOCUS_TARGET_ONE_ENEMY;
		break;
	case SKILLTARGET_OPPONENT_ALL:
		return BWND_FOCUS_TARGET_ALL_ENEMIES;
		break;
	default:
		return BWND_FOCUS_TARGET_NONE;
	}
	return BWND_FOCUS_TARGET_NONE;
}
