// Sprite_Base.cpp

#include "Sprite_Base.h"

Sprite_Base::Sprite_Base() : param(){
	ix = iy = 0;
	cx = cy = 0;
	width = height = 1;
	visible = false;
	ResetMorph();
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
	// 時間を進める
	if(GetMorphing()){
		morphCount++;
		if(morphCount > morphTime){
			ResetMorph();
		}
	}
	// 各morphごとの更新
	UpdateMorph();
}

void Sprite_Base::ResetMorph(){
	morphID = SPMORPH_NONE;
	morphCount = 0;
	morphTime = 0;
	morphSkipTime = 0;
}


