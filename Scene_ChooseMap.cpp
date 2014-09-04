// Scene_ChooseMap.cpp

#include "Scene_ChooseMap.h"

Scene_ChooseMap::Scene_ChooseMap() : Scene_Base(){
}

bool Scene_ChooseMap::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}

bool Scene_ChooseMap::Terminate(){

	return true;
}

int Scene_ChooseMap::Update(){
	return SCENE_NONE;
}

void Scene_ChooseMap::Draw() const{
}

