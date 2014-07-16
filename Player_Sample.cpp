// Player_Sample.cpp

#include "Player_Sample.h"


#include <DxLib.h>

#include "DXInput.h"
#include "KeyConfig.h"
#include "Static_Game.h"

extern DXInput g_input;
extern KeyConfig g_key;

Player_Sample::Player_Sample(){
	x = WND_WIDTH/2;
	y = WND_HEIGHT/2;
}

bool Player_Sample::Update(){
	if(g_input.key & PAD_INPUT_LEFT){
		x -= 3.0f;
	}
	if(g_input.key & PAD_INPUT_UP){
		y -= 3.0f;
	}
	if(g_input.key & PAD_INPUT_RIGHT){
		x += 3.0f;
	}
	if(g_input.key & PAD_INPUT_DOWN){
		y += 3.0f;
	}
	return true;
}

void Player_Sample::Draw() const{
	DrawBox(x-2, y-2, x+2, y+2, GetColor(0, 255, 255), 1);
}