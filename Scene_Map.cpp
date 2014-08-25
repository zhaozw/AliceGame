// Scene_Map.cpp

#include "Scene_Map.h"
#include "Func_MyGraphic.h"
#include "TempData.h"
#include "DXInput.h"
#include "KeyConfig.h"

extern TempData		g_temp;
extern DXInput		g_input;
extern KeyConfig	g_key;

Scene_Map::Scene_Map():Scene_Base(){
}

bool Scene_Map::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);


}

bool Scene_Map::InitWindow(){
	return true;
}

bool Scene_Map::Terminate(){

	return true;
}

int Scene_Map::Update(){
	return SCENE_NONE;

}

void Scene_Map::Draw() const{

}
