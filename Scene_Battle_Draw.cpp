// Scene_Battle_Draw.cpp

#include "Scene_Battle.h"
#include "Static_Battle.h"

#include "Image.h"

extern Image g_image;

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
}