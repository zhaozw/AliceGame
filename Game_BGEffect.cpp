// Game_BGEffect.cpp

#include "Game_BGEffect.h"
#include "Image.h"
#include <DxLib.h>
#include "Static_Game.h"

extern Image	g_image;

Game_BGEffect::Game_BGEffect(){
	typeID = GAME_BG_TYPE_NONE;
	param = 0;
	time = 0;
	posX = posY = 0;
	loopWidth = loopHeight = 1; // 不意のdiv0防止
}

bool Game_BGEffect::Initialize(){
	// スクリーンの作成などを行う

	return true;
}

bool Game_BGEffect::Terminate(){
	// 画像ハンドルの解放などを行う

	return true;
}

#define DUMMYTILE_SIZE		48

bool Game_BGEffect::SetTypeID(WORD id){
	// 値の代入
	typeID = id;
	time = 0;

	// 初期化処理(typeID値により分岐する)
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		loopWidth = DUMMYTILE_SIZE;
		loopHeight = DUMMYTILE_SIZE;
		break;
	default:
		return false;
		break;
	}
	return true;
}

void Game_BGEffect::Update(){
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		posX += 0.3f;
		posY += 0.2f;
		if(posX > loopWidth) posX -= loopWidth;
		if(posY > loopHeight) posY -= loopHeight;
		break;
	}

	// 時間値の増加
	time++;
}

void Game_BGEffect::Draw() const{
	int tmpX=0, tmpY=0;
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		tmpX = posX-loopWidth;
		tmpY = posY-loopHeight;
		while(tmpY < WND_HEIGHT){
			while(tmpX < WND_WIDTH){
				DrawGraph(tmpX, tmpY, g_image.icon.tile, 0);
				tmpX += DUMMYTILE_SIZE;
			}
			tmpY += loopHeight;
			tmpX = posX - loopWidth;
		}
		break;
	}
}

void Game_BGEffect::SetRandTime(){
	time = GetRand(32767);
}