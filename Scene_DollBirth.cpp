// Scene_DollBirth.cpp
#include "Scene_DollBirth.h"
#include "Func_MyGraphic.h"
#include "TempData.h"
#include "DXInput.h"
#include "KeyConfig.h"

extern TempData		g_temp;
extern DXInput		g_input;
extern KeyConfig	g_key;

Scene_DollBirth::Scene_DollBirth():Scene_Base(), w_name(){
}

bool Scene_DollBirth::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	// ウィンドウの初期化
	if(!InitWindow()){
		return false;
	}

	// 人形アニメーションの開始
	SetState(SCNSTATE_DOLLBIRTH_DOLLAPPEAR);
	SetAnime(SCNANIME_DOLLBIRTH_DOLLAPPEAR, SCNANIME_DOLLBIRTH_DOLLAPPEAR_TIME);
	return true;

}

bool Scene_DollBirth::InitWindow(){
	w_status.Setup(WND_WIDTH/2+50, 0+50);
	w_status.SetDoll(&g_temp.dollData);
	w_name.MySetup(NAMETYPE_DOLLNAME);
	return true;
}

bool Scene_DollBirth::Terminate(){

	return true;
}

int Scene_DollBirth::Update(){
	switch(state){
	case SCNSTATE_DOLLBIRTH_DOLLAPPEAR:
		if(GetAnimeEnded()){
			SetState(SCNSTATE_DOLLBIRTH_SHOWSTATUS);
			w_status.SetVisible(true);
			w_status.Open();
		}
		break;
	case SCNSTATE_DOLLBIRTH_SHOWSTATUS:
		// ウィンドウのアップデート
		w_status.Update();
		if(w_status.GetState() == Window_Base::IDLE 
			&& (g_input.pushedKey & g_key.input[BTN_CHOOSE])){
			w_name.SetVisible(true);
			w_name.Open();
			SetState(SCNSTATE_DOLLBIRTH_ENTERNAME);
		}
		break;
	case SCNSTATE_DOLLBIRTH_ENTERNAME:
		w_name.Update();
		if(w_name.GetState() == Window_Base::CLOSED){
			ReserveScene(SCENE_DOLLBIRTH, 40);
		}
		break;
	}
	return SCENE_NONE;

}

void Scene_DollBirth::Draw(){
	float exRate = 0.7;
	switch(state){
	case SCNSTATE_DOLLBIRTH_DOLLAPPEAR:
		exRate *= 1.0*(float)GetAnimeCount()/GetAnimeTime();
		break;
	}
	// 人形の描画
	DrawDollIllust(240, 300,
	g_temp.dollData.GetType(), g_temp.dollData.GetAttr(),
	exRate, 0);

	// ウィンドウの描画
	w_status.Draw();

	// 名前入力ウィンドウの描画
	w_name.Draw();

	DrawReserveFade();
}

