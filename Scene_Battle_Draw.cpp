// Scene_Battle_Draw.cpp

#include "Scene_Battle.h"
#include "Static_Battle.h"

#include "Image.h"
#include "DXFont.h"
#include "Record_AliceInfo.h"

extern Image g_image;
extern DXFont g_font;
extern Record_AliceInfo	r_aliceInfo;

void Scene_Battle::DrawBG() const{
}

void Scene_Battle::DrawDollsSprite() const {
	for(int n=0; n<NUM_BATTLEDOLL_FRONT; n++){
		s_dolls[n].Draw();
	}
}

void Scene_Battle::DrawEnemiesSprite() const{
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		s_enemies[n].Draw();
	}
}

void Scene_Battle::DrawBattleInfo() const{
	// ‘®«ŠÖŒW‚ð•\‚·}‚Ì•`‰æ
	DrawRotaGraph(725, 60, 0.24, 0, 
		g_image.icon.attr_graph, 1);

	// ƒAƒŠƒX‚Ì–‚—Í‚ð•`‰æ
	TCHAR buf[16];
	int w = 0;
	switch(phaze){
	case DOLLS_COMMAND:
	case ALICE_COMMAND:
		wsprintf(buf, _T("Žc‚è–‚—Í:%d"), r_aliceInfo.GetMP());
		w = GetStrWidth(buf, strlen(buf), g_font.hInfo);
		DrawStringToHandle(150-w/2, 378-FONTSIZE_INFO, buf, GetColor(255,255,255), g_font.hInfo);
	}
	// DrawStringToHandle(WND_WIDTH-w-36, 370-FONTSIZE_INFO, buf, GetColor(255,255,255), g_font.hInfo);
}