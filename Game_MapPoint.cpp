// Game_MapPoint.cpp

#include "Game_MapPoint.h"
#include "Static_Map.h"

Game_MapPoint::Game_MapPoint(){
	id = 0;
	type = MAPPOINT_TYPE_NONE;
	param = 0;
	for(int i=0; i<4; i++){
		pointID[i] = 0;
		pathID[i] = 0;
	}
	posX = posY = 0;
	state = MAPPOINT_STATE_NONE;
}

void Game_MapPoint::Clear(){
}

void Game_MapPoint::Draw() const{
}

Game_MapPath::Game_MapPath(){
	id = 0;
}

void Game_MapPath::Draw() const{
}