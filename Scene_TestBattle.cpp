// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"
#include "Window_Text.h" // 定数を使用

extern DXFont		g_font;
extern TempData		g_temp;		// 敵IDを指定するのに使用

Scene_TestBattle::Scene_TestBattle():Scene_Base(), s_main(TESTBATTLE_SELECT_NUM){

}

bool Scene_TestBattle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	for(int n=2; n<MAX_TESTBATTLE; n++){
		s_main.isActive[n] = false;
	}
	return true;
}

bool Scene_TestBattle::Terminate(){

	return true;
}

int Scene_TestBattle::Update(){
	switch(s_main.Move()){
	case SELECT_CHOOSE:
		if(s_main.index < MAX_TESTBATTLE){
			g_temp.battleType = TEMP_BTYPE_TUTORIAL;
			g_temp.battleID = s_main.index+1;
			// チュートリアル戦闘のIDを指定
			g_temp.enemyGroup = s_main.index+1;
			ReserveScene(SCENE_BATTLE, 60);
			break;
		}else{
			if(s_main.index == TESTBATTLE_SELECT_NUM-1){
				ReserveScene(SCENE_END, 60);
			}
		}
		break;
	case SELECT_CANCEL:
		s_main.index = TESTBATTLE_SELECT_NUM-1;
		break;
	}
	return SCENE_NONE;
}

void Scene_TestBattle::Draw() const{
	TCHAR	battleTitle[MAX_TESTBATTLE][128] = {
		_T("はじめのいっぽ"), 
		_T("人形と敵の属性"), 
		_T("ステータスを確認する"), 
		_T("アリスの魔力"), 
		_T("魔力と技巧"), 
		_T("戦闘テスト6"), 
		_T("戦闘テスト7"), 
		_T("戦闘テスト8"), 
		_T("戦闘テスト9"), 
		_T("戦闘テスト10"), 
	};

	TCHAR	menuTitle[MAX_TESTBATTLE_MENU][128] = {
		// _T("モンスター図鑑"), 
		// _T("クレジット"), 
		_T("ゲームを終了する"), 
	};

	int color;
	for(int n=0; n<TESTBATTLE_SELECT_NUM; n++){
		if(s_main.index == n){
			color = WINDOWFONT_DEFCOLOR;
		}else if(s_main.isActive[n]){
			color = WINDOWFONT_DEFICOLOR;
		}else{
			color = WINDOWFONT_DEFNCOLOR;
		}
		if(n < MAX_TESTBATTLE){
			DrawStringToHandle(50, 50+30*n, battleTitle[n], color, 
				g_font.hInfo);
		}else{
			DrawStringToHandle(50, 50+30*n, menuTitle[n-MAX_TESTBATTLE], color, 
				g_font.hInfo);
		}
	}
	// シーン切り替えのフェードの描画
	DrawReserveFade();
}

