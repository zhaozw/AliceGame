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
	// �X�N���[���̍쐬�Ȃǂ��s��

	return true;
}

bool Game_BGEffect::Terminate(){
	// �摜�n���h���̉���Ȃǂ��s��

	return true;
}

bool Game_BGEffect::SetTypeID(WORD id){
	// �l�̑��
	typeID = id;
	time = 0;

	// ����������(typeID�l�ɂ�蕪�򂷂�)
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

	// ���Ԓl�̑���
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