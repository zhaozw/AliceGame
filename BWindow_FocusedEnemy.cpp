// BWindow_FocusedEnemy.cpp


#include "BWindow_FocusedEnemy.h"
#include "Static_Battle.h"
#include "Scene_Battle.h"
#include "WindowSkin.h"

extern	WindowSkins	g_wndSkins;

BWindow_FocusedEnemy::BWindow_FocusedEnemy() : s_enemy(MAX_BATTLEENEMY, 0, false, true){
	pScene = NULL;
	pEnemy = NULL;
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
	s_enemy.index = 0;
	CheckEnemyEnabled();
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

void BWindow_FocusedEnemy::CheckEnemyEnabled(){
	Game_BattleEnemy* pEnemy = NULL;
	if(pScene == NULL) return;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(n < pScene->GetEnemiesNum()){
			pEnemy = pScene->GetEnemyPtr(n);
		}else{
			pEnemy = NULL;
		}
		s_enemy.isActive[n] = (pEnemy != NULL);
	}
	s_enemy.maxSize = MAX_BATTLEENEMY;
}

void BWindow_FocusedEnemy::Update(){
	int oldIndex = s_enemy.index;
	switch(state){
	case UPDATING:
		switch(s_enemy.Move()){
		case SELECT_CHOOSE:
			break;
		}
		if(s_enemy.index != oldIndex){
			OnIndexChanged();
		}
		break;
	case SUSPENDED:
		state = UPDATING;
		break;
	}
}

void BWindow_FocusedEnemy::DrawContent() const{
	DrawBox(
		GetPositionX()-5, GetPositionY()-5,
		GetPositionX()+5, GetPositionY()+5,
		GetColor(255, 0, 0), 1);
}