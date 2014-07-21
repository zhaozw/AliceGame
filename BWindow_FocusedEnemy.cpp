// BWindow_FocusedEnemy.cpp


#include "BWindow_FocusedEnemy.h"
#include "Static_Battle.h"
#include "Scene_Battle.h"
#include "WindowSkin.h"

extern	WindowSkins	g_wndSkins;

BWindow_FocusedEnemy::BWindow_FocusedEnemy() : s_enemy(MAX_BATTLEENEMY, 0, false, true){
	pScene = NULL;
	pDoll = NULL;
	pEnemy = NULL;
	focusAll = false;
}

void BWindow_FocusedEnemy::MySetup(Scene_Battle* _pScene){
	Window_Base::Setup(
		&g_wndSkins.skin[WNDSKIN_NONE],
		-100, -100, 
		BWND_FOCUSEDENEMY_WIDTH,
		BWND_FOCUSEDENEMY_HEIGHT, 
		0, 0, true);
	pScene = _pScene;
}


void BWindow_FocusedEnemy::OnOpened(){
	pEnemy = NULL;
	s_enemy.index = 0;
	CheckEnemyEnabled();
	if(!SetDefaultIndex()){
		// �I���ɃG���[����������
		s_enemy.index = -1;
	}
	OnIndexChanged();
}

void BWindow_FocusedEnemy::OnIndexChanged(){
	if(pScene == NULL) return;
	if(s_enemy.index >= 0 && s_enemy.index < MAX_BATTLEENEMY){
		pEnemy = pScene->GetEnemyPtr(s_enemy.index);
		if(pEnemy == NULL) return;
		SetPosition(pEnemy->GetDrawX(), pEnemy->GetDrawY());
	}
}

bool BWindow_FocusedEnemy::SetDefaultIndex(){
	Game_BattleEnemy* pTmpEnemy;
	if(pScene == NULL) return false;
	if(pDoll == NULL) return false;
	// �ԍ��̎Ⴂ���ɁA�����ŗL���ȓG�ɃJ�[�\�������킹�悤�Ƃ���B
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpEnemy = pScene->GetEnemyPtr(n);
		if(pTmpEnemy == NULL){
			continue;
		}
		if(!pTmpEnemy->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pDoll->GetAttr(), pTmpEnemy->GetAttr()) == ATTRAFFINITY_STRONG){
				s_enemy.index = n;
				return true;
		}
	}
	// �L���ȓG�����Ȃ���΁A���������ʂȓG�ɃJ�[�\�������킹�悤�Ƃ���B�B
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpEnemy = pScene->GetEnemyPtr(n);
		if(pTmpEnemy == NULL){
			continue;
		}
		if(!pTmpEnemy->CanTarget()){
			continue;
		}
		if(pScene->GetAttrAffinity(
			pDoll->GetAttr(), pTmpEnemy->GetAttr()) != ATTRAFFINITY_WEAK){
				s_enemy.index = n;
				return true;
		}
	}
	// �I�ׂ�G������ΑI��
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpEnemy = pScene->GetEnemyPtr(n);
		if(pTmpEnemy == NULL){
			continue;
		}
		if(!pTmpEnemy->CanTarget()){
			continue;
		}
		s_enemy.index = n;
		return true;
	}
	s_enemy.index = -1;
	return false;
}

void BWindow_FocusedEnemy::CheckEnemyEnabled(){
	Game_BattleEnemy* pEnemy = NULL;
	if(pScene == NULL) return;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(n < pScene->GetEnemiesNum()){
			pEnemy = pScene->GetEnemyPtr(n);
		}else{
			pEnemy = NULL;
		}
		// �I���\���ǂ���
		if(pEnemy == NULL){
			s_enemy.isActive[n] = false;
		}else if(!pEnemy->CanTarget()){
			s_enemy.isActive[n] = false;
		}else{
			s_enemy.isActive[n] = true;
		}
	}
	s_enemy.maxSize = MAX_BATTLEENEMY;
}

void BWindow_FocusedEnemy::Update(){
	int oldIndex = s_enemy.index;
	switch(state){
	case UPDATING:
		switch(s_enemy.Move()){
		case SELECT_CHOOSE:
			Close(true, true);
			break;
		case SELECT_CANCEL:
			s_enemy.index = SELECTRESULT_CANCELED;
			Close(true, true);
			break;
		}
		if(s_enemy.index != oldIndex){
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

void BWindow_FocusedEnemy::DrawContent() const{
	Game_BattleEnemy*	pTmpEnemy = NULL;
	if(pEnemy == NULL) return;
	if(!GetActive()) return;
	if(!focusAll){
		DrawCntEnemy(pEnemy);
	}else{
		// �S�Ă̓G�ɂ��ă��[�v����
		for(int n=0; n<MAX_BATTLEENEMY; n++){
			if(n < pScene->GetEnemiesNum()){
				pTmpEnemy = pScene->GetEnemyPtr(n);
				DrawCntEnemy(pTmpEnemy);
			}
		}
	}
}

void BWindow_FocusedEnemy::DrawCntEnemy(Game_BattleEnemy* p) const {
	int tmpX=0, tmpY=0;
	tmpX = p->GetDrawX();
	tmpY = p->GetDrawY()+20;
	DrawBox(
		tmpX-5, tmpY-5,
		tmpX+5, tmpY+5,
		GetColor(255, 0, 0), 1);
}