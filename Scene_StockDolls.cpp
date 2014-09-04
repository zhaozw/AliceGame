// Scene_StockDolls.cpp

#include "Scene_StockDolls.h"

Scene_StockDolls::Scene_StockDolls() : Scene_Base(){
}

bool Scene_StockDolls::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}

bool Scene_StockDolls::Terminate(){

	return true;
}

int Scene_StockDolls::Update(){
	return SCENE_NONE;
}

void Scene_StockDolls::Draw() const{
}

