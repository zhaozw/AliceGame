// Sprite_Base.cpp

#include "Sprite_Base.h"

Sprite_Base::Sprite_Base(){
	ix = iy = 0;
	dx = dy = 0;
	width = height = 0;
	angle = 0;
	exRate = 1.0f;
	visible = false;
	animeID = ANIME_NONE;
	animeCount = 0;
	animeTime = ANIME_TIME_NONE;
	animeSkipTime = ANIME_SKIPTIME_NONE;
	state = IDLE;
}

Sprite_Base::Sprite_Base(float x, float y){
	Sprite_Base();
	SetPos(x, y);
}

Sprite_Base::Sprite_Base(float x, float y, int w, int h){
	Sprite_Base();
	SetPos(x, y);
	SetSize(w, h);
}

void Sprite_Base::Update(){
	if(state == ANIME_NOT_SKIP || state == ANIME_SKIP){
		animeCount++;
		if(animeCount >= animeSkipTime && state == ANIME_NOT_SKIP){
			state = ANIME_SKIP;
		}
	}
}