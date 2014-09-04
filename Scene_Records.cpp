// Scene_Records.cpp

#include "Scene_Records.h"

Scene_Records::Scene_Records() : Scene_Base(){
}

bool Scene_Records::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}

bool Scene_Records::Terminate(){

	return true;
}

int Scene_Records::Update(){
	return SCENE_NONE;
}

void Scene_Records::Draw() const{
}

