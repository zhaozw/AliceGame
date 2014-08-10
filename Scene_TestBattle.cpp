// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"
#include "Window_Text.h" // 定数を使用
#include "Func_AliceFile.h"
#include "WindowSkin.h"
#include "Image.h"
#include "Sound.h"

extern DXFont				g_font;
extern TempData				g_temp;		// 敵IDを指定するのに使用
extern AliceFile_140816		g_trialAliceFile;
extern WindowSkins			g_wndSkins;
extern Image				g_image;
extern Sound				g_sound;

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

	backX = backY = 0;
	return true;
}

bool Scene_TestBattle::Terminate(){
	g_sound.StopBGM(BGM_MENU);
	return true;
}

#define BACKTILE_SIZE				48


int Scene_TestBattle::Update(){
	if(sceneTime == 2){
		g_sound.PlayBGM(BGM_MENU, false);
	}

	// 背景の更新
	float backVX=0, backVY=0, angle=0;
	int n=0;
	for(int a=0;a<MAX_TESTBATTLE;a++){
		n += (int)g_trialAliceFile.data.tutorialBattle[a];
	}
	// angle = 2.0*((float)s_main.index+(s_main.index%2==1?1.8:0))+0.35;
	angle = 2.0*n+0.35;
	if(!SceneIsReserved()){
		backVX = (0.5+0.02*n)*sin(angle);
		backVY = (0.5+0.02*n)*cos(angle);
	}
	backX += backVX;
	backY += backVY;
	if(backX > BACKTILE_SIZE) backX -= BACKTILE_SIZE;
	if(backX < 0) backX += BACKTILE_SIZE;
	if(backY > BACKTILE_SIZE) backY -= BACKTILE_SIZE;
	if(backY < 0) backY += BACKTILE_SIZE;

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
				if(s_main.index == MAX_TESTBATTLE+1){
					g_trialAliceFile.data.tutorialHint
						= !g_trialAliceFile.data.tutorialHint;
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

#define TESTBATTLE_SHADOWCOLOR		0x00c0c0c0
#define TESTBATTLE_SHADOWCOLOR2		0x00e0e0e0
#define TESTBATTLE_SELECTEDCOLOR	0x00ff6000
#define TESTBATTLE_UNSELECTEDCOLOR	0x00909090
#define TESTBATTLE_SELECTEDCOLOR2	0x00f0c000
#define TESTBATTLE_UNSELECTEDCOLOR2	0x00a0a060

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
		_T("Readmeシャンハイ"), 
		_T("シャンハイ解説"), 
		_T("ゲームを終了する"), 
	};

	// 背景の描画
	int tmpX = backX-BACKTILE_SIZE;
	int tmpY = backY-BACKTILE_SIZE;
	while(tmpY < WND_HEIGHT){
		while(tmpX < WND_WIDTH){
			DrawGraph(tmpX, tmpY, g_image.icon.tile, 0);
			tmpX += BACKTILE_SIZE;
		}
		tmpY += BACKTILE_SIZE;
		tmpX = backX - BACKTILE_SIZE;
	}

	// 背景の枠の描画
	DrawBox(90, 45, 580, 475, GetColor(127, 191, 159), 1);
	DrawBox(50, 30, 540, 460, GetColor(223, 239, 232), 1);

	// 文字の描画
	int color;
	for(int n=0; n<TESTBATTLE_SELECT_NUM; n++){
		if(s_main.index == n){
			if(g_trialAliceFile.data.tutorialBattle[n] == 0x02){
				color = TESTBATTLE_SELECTEDCOLOR2;
			}else{
				color = TESTBATTLE_SELECTEDCOLOR;
			}
		}else if(s_main.isActive[n]){
			if(g_trialAliceFile.data.tutorialBattle[n] == 0x02){
				color = TESTBATTLE_UNSELECTEDCOLOR2;
			}else{
				color = TESTBATTLE_UNSELECTEDCOLOR;
			}
		}else{
			color = WINDOWFONT_DEFNCOLOR;
		}
		if(n < MAX_TESTBATTLE){
			DrawStringToHandle(80+3, 50+30*n+3, 
				battleTitle[n],
				(s_main.index == n ? TESTBATTLE_SHADOWCOLOR2 : TESTBATTLE_SHADOWCOLOR), 
				g_font.hInfo);
			DrawStringToHandle(80-((n==s_main.index)?4:0),
				50+30*n, battleTitle[n], color, 
				g_font.hInfo);
			// クリアマーク
			if(g_trialAliceFile.data.tutorialBattle[n] == 0x02){
				DrawRotaGraph(
					90 + GetStrWidth(battleTitle[n], strlen(battleTitle[n]), g_font.hInfo),
					50+30*n+5, 
					1.0, 0.35*sin(0.7*n),
					g_image.icon.cleared,
					1);
			}
		}else{
			DrawStringToHandle(80+3, 50+30*n+3, 
				menuTitle[n-MAX_TESTBATTLE],
				(s_main.index == n ? TESTBATTLE_SHADOWCOLOR2 : TESTBATTLE_SHADOWCOLOR), 
				g_font.hInfo);
			DrawStringToHandle(80-((n==s_main.index)?4:0),
				50+30*n, menuTitle[n-MAX_TESTBATTLE], color, 
				g_font.hInfo);
		}
	}

	// 説明ウィンドウ表示する/しないの表示
	DrawStringToHandle(360+3, 50+30*11+3,
		g_trialAliceFile.data.tutorialHint ? 
		_T("毎回表示") : _T("初回のみ"),
		TESTBATTLE_SHADOWCOLOR,
		(s_main.index == 11) ? TESTBATTLE_SHADOWCOLOR2 : TESTBATTLE_SHADOWCOLOR,
		g_font.hInfo);
	DrawStringToHandle(360-((s_main.index==11)?4:0), 50+30*11,
		g_trialAliceFile.data.tutorialHint ? 
		_T("毎回表示") : _T("初回のみ"),
		(s_main.index == 11) ? TESTBATTLE_SELECTEDCOLOR : TESTBATTLE_UNSELECTEDCOLOR,
		g_font.hInfo);


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


