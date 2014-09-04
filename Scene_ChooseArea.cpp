// Scene_ChooseArea.cpp

#include "Scene_ChooseArea.h"

Scene_ChooseArea::Scene_ChooseArea() : Scene_Base(){
}

bool Scene_ChooseArea::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}


bool Scene_ChooseArea::Terminate(){

	return true;
}

int Scene_ChooseArea::Update(){
	return SCENE_NONE;
}

void Scene_ChooseArea::Draw() const{
}

