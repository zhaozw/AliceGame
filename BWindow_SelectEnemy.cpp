// BWindow_SelectEnemy.cpp

#include "BWindow_SelectEnemy.h"
#include "WindowSkin.h"
#include "DXFont.h"

extern WindowSkins			g_wndSkins;
extern DXFont				g_font;


BWindow_SelectEnemy::BWindow_SelectEnemy(){

}

void BWindow_SelectEnemy::MySetup(Game_BattleEnemy* _pEnemies){
	Window_Selectable_Content content;
	Window_Selectable::Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		BWND_SELECTENEMY_X, BWND_SELECTENEMY_Y,
		content,
		1,
		g_font.hInfo,
		FONTSIZE_INFO,
		FONTSIZE_INFO+4,
		false, false, ALIGN_LEFT);
	SetVisible(true);
	SetAllColor(
		GetColor(255, 255, 255),
		GetColor(192, 192, 192),
		GetColor(64, 64, 64));
	// 内容を元にセットアップする
	SetDefParam();

	pEnemies = _pEnemies;
	enemyNum = 0;
}

void BWindow_SelectEnemy::Update(){
	// 敵の数のアップデートを行う
	UpdateEnemyNum();
	Window_Selectable::Update();
}

void BWindow_SelectEnemy::UpdateEnemyNum(){

}

void BWindow_SelectEnemy::DrawContent() const{
	Window_Selectable::DrawContent();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}