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
	loopWidth = loopHeight = 1; // �s�ӂ�div0�h�~
}

bool Game_BGEffect::Initialize(){
	// �X�N���[���̍쐬�Ȃǂ��s��

	return true;
}

bool Game_BGEffect::Terminate(){
	// �摜�n���h���̉���Ȃǂ��s��

	return true;
}

#define DUMMYTILE_SIZE		48

bool Game_BGEffect::SetTypeID(WORD id){
	// �l�̑��
	typeID = id;
	time = 0;

	// ����������(typeID�l�ɂ�蕪�򂷂�)
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

	// ���Ԓl�̑���
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