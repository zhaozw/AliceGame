// Game_BGEffect.cpp

#include "Game_BGEffect.h"
#include "Image.h"
#include <DxLib.h>

Game_BGEffect::Game_BGEffect(){
	typeID = GAME_BG_TYPE_NONE;
	param = 0;
	time = 0;
	posX = posY = 0;
}

bool Game_BGEffect::Initialize(){
	// スクリーンの作成などを行う

	return true;
}

bool Game_BGEffect::Terminate(){
	// 画像ハンドルの解放などを行う

	return true;
}

bool Game_BGEffect::SetTypeID(WORD id){
	// 値の代入
	typeID = id;
	time = 0;

	// 初期化処理(typeID値により分岐する)
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
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
		break;
	}

	// 時間値の増加
	time++;
}

void Game_BGEffect::Draw() const{
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		break;
	}
}

void Game_BGEffect::SetRandTime(){
	time = GetRand(32767);
}