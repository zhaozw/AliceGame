// BWindow_SelectEnemy.cpp

#include "BWindow_SelectEnemy.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Scene_Battle.h"
#include "Game_BattleEnemy.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;


BWindow_SelectEnemy::BWindow_SelectEnemy(){
	Window_Base::Window_Base();
	pScene = NULL;
}

void BWindow_SelectEnemy::MySetup(Scene_Battle* _pScene){
	WINDOWAREA	frameArea(
		BWND_SELECTENEMY_X, BWND_SELECTENEMY_Y,
		BWND_SELECTENEMY_W, BWND_SELECTENEMY_H);
	WINDOWFONT	font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	Window_Selectable_Content content;
	Window_Selectable::Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, 16, 16, font, 100);
	SetVisible(true);
	pScene = _pScene;
	enemyNum = 0;
}

void BWindow_SelectEnemy::Update(){
	// �X�V
	Window_Selectable::Update();
	switch(state){
	case UPDATING:
		break;
	case SUSPENDED:
		// SUSPENDED��Ԃ̔���
		state = UPDATING;
		break;
	}
	Update_Common();
}

void BWindow_SelectEnemy::OnOpened(){
	// �V�[���Ƃ̘A�g
	if(pScene == NULL) return;
	// �G�̐����擾
	enemyNum = pScene->GetEnemiesNum();
	// �`����e���쐬
	ClearContent();
	Game_BattleEnemy* pEnemy = NULL;
	TCHAR buf[BATTLEUNIT_NAME_BYTES];
	for(int n=0; n<enemyNum; n++){
		pEnemy = pScene->GetEnemyPtr(n);
		if(pEnemy != NULL){
			// ���O�̃Z�b�e�B���O
			pEnemy->GetName(buf, BATTLEUNIT_NAME_BYTES);
			SetContent(buf, n);
		}
	}
	// ���͂��ꂽ���O�ɍ��킹�ăE�B���h�E���L����
	// SetDefParam(true);
}

void BWindow_SelectEnemy::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}