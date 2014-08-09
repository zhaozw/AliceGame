// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"
#include "Window_Text.h" // 定数を使用
#include "Func_AliceFile.h"
#include "WindowSkin.h"

extern DXFont		g_font;
extern TempData		g_temp;		// 敵IDを指定するのに使用
extern AliceFile_140816		g_trialAliceFile;
extern WindowSkins	g_wndSkins;

Scene_TestBattle::Scene_TestBattle():Scene_Base(), s_main(TESTBATTLE_SELECT_NUM){

}

bool Scene_TestBattle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// シーン開始時にデータをセーブする
	g_trialAliceFile.Save();

	// 最初の場合はウィンドウを開く
	if(!g_trialAliceFile.data.firstHint){
		if(!OpenHintWindow()){
			return false;
		}
	}

	return true;
}

bool Scene_TestBattle::Terminate(){

	return true;
}

int Scene_TestBattle::Update(){
	if(w_hint.GetClosed()){
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
				if(s_main.index == MAX_TESTBATTLE){
					OpenHintWindow();
				}
				if(s_main.index == TESTBATTLE_SELECT_NUM-1){
					ReserveScene(SCENE_END, 60);
				}
			}
			break;
		case SELECT_CANCEL:
			s_main.index = TESTBATTLE_SELECT_NUM-1;
			break;
		}
	}
	// ウィンドウの更新
	w_hint.UpdateA();

	return SCENE_NONE;
}

void Scene_TestBattle::Draw() const{
	TCHAR	battleTitle[MAX_TESTBATTLE][128] = {
		_T("Battle1 はじめのいっぽ"), 
		_T("Battle2 人形と敵の属性"), 
		_T("Battle3 ステータスを確認する"), 
		_T("Battle4 魔力と技巧"), 
		_T("Battle5 魔力と技巧・挑戦編"), 
		_T("Battle6 アリスの魔力"), 
		_T("Battle7 アリスの魔力・挑戦編"), 
		_T("Battle8 敵の攻撃パターン"), 
		_T("Battle9 敵の攻撃パターン・挑戦編"), 
		_T("Battle10 ボス戦に挑もう"), 
	};

	TCHAR	menuTitle[MAX_TESTBATTLE_MENU][128] = {
		_T("説明ウィンドウの再表示"), 
		// _T("クレジット"), 
		_T("ゲームを終了する"), 
	};

	int color;
	for(int n=0; n<TESTBATTLE_SELECT_NUM; n++){
		if(s_main.index == n){
			if(g_trialAliceFile.data.tutorialBattle[n]){
				color = 0x00ffff40;
			}else{
				color = WINDOWFONT_DEFCOLOR;
			}
		}else if(s_main.isActive[n]){
			if(g_trialAliceFile.data.tutorialBattle[n]){
				color = 0x00d0d090;
			}else{
				color = WINDOWFONT_DEFICOLOR;
			}
		}else{
			color = WINDOWFONT_DEFNCOLOR;
		}
		if(n < MAX_TESTBATTLE){
			DrawStringToHandle(80, 50+30*n, battleTitle[n], color, 
				g_font.hInfo);
		}else{
			DrawStringToHandle(80, 50+30*n, menuTitle[n-MAX_TESTBATTLE], color, 
				g_font.hInfo);
		}
	}

	// ウィンドウの描画
	if(!w_hint.GetClosed()){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, WND_WIDTH, WND_HEIGHT, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if(w_hint.GetState() == Window_Base::CLOSING){
		g_trialAliceFile.data.firstHint = true;
	}
	w_hint.Draw();

	// シーン切り替えのフェードの描画
	DrawReserveFade();
}

bool Scene_TestBattle::OpenHintWindow(){
	return w_hint.OpenAndPlay(_T("dat_text\\tutorial_first.txt"), WND_HINT_ALICE);
}


