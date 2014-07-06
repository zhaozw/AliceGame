// Scene_Battle_Draw.cpp

#include "Scene_Battle.h"
#include "Static_Battle.h"

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