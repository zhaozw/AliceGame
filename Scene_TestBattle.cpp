// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"

extern DXFont		g_font;
extern TempData		g_temp;		// 敵IDを指定するのに使用

Scene_TestBattle::Scene_TestBattle():Scene_Base(), s_main(MAX_TESTBATTLE+1){
}

bool Scene_TestBattle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	return true;
}

bool Scene_TestBattle::Terminate(){

	return true;
}

int Scene_TestBattle::Update(){
	switch(s_main.Move()){
	case SELECT_CHOOSE:
		switch(s_main.index){
		case 0:
			g_temp.enemyGroup = 1;
			ReserveScene(SCENE_BATTLE, 60);
			break;
		case MAX_TESTBATTLE:
			ReserveScene(SCENE_END, 60);
		}
		break;
	case SELECT_CANCEL:
		s_main.index = MAX_TESTBATTLE;
		break;
	}
	return SCENE_NONE;
}

void Scene_TestBattle::Draw(){
	TCHAR	battleTitle[MAX_TESTBATTLE][128] = {
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
		_T("テスト"), 
	};

	int color;
	for(int n=0; n<MAX_TESTBATTLE+1; n++){
		if(s_main.index == n){
			color = GetColor(255, 255, 255);
		}else{
			color = GetColor(96, 96, 192);
		}
		if(n != MAX_TESTBATTLE){
			DrawStringToHandle(50, 50+30*n, battleTitle[n], color, 
				g_font.hInfo);
		}else{
			DrawStringToHandle(50, 50+30*n, _T("ゲームを終了する"), color, 
				g_font.hInfo);
		}
	}
	// シーン切り替えのフェードの描画
	DrawReserveFade();
}

