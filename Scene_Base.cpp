// Scene_Base.cpp

#include "Scene_Base.h"
#include "Config.h"
#include "DXInput.h"

extern DXInput g_input;
#ifdef MYGAME_USE_2P
extern DXInput g_input_2P;
#endif // MYGAME_USE_2P
extern int hDrawWindow;
extern Config g_cfg;

Scene_Base::Scene_Base(){
	sceneTime = 0;
	fDrawSkip = false;

	state = 0;
	anime = 0;
	animeCount = 0;
	animeTime = 0;
}

// 各シーン共通の初期化処理。
bool Scene_Base::Initialize(bool fSkipFrame){
	sceneTime = 0;
#ifdef MYGAME_USE_TIMECTRL
	timectrl.Reset();
	timectrl.SetSkipFrame(fSkipFrame);
#endif // MYGAME_USE_TIMECTRL
	reservedScene = SCENE_NONE;
	reservedCount = 0;
	reservedCount_max = 0;
	state = 0;
	stateTime = 0;
	return true;
}

int Scene_Base::Play(){
	int nextScene = SCENE_NONE;
	while(nextScene == SCENE_NONE){
		if(ProcessMessage() != 0){
			return SCENE_END;
		}
		sceneTime+=1;
		stateTime+=1;
		if(reservedScene != SCENE_NONE){
			reservedCount++; // シーンの予約がある場合、カウントを増やす
			if(reservedCount > reservedCount_max){
				return reservedScene;
			}
		}
#ifdef MYGAME_USE_TIMECTRL
		timectrl.Regulate();
#endif // MYGAME_USE_TIMECTRL
		Input();
		nextScene = Update();
		UpdateAnime(); // アニメのアップデート 
#ifdef MYGAME_USE_TIMECTRL
		if(timectrl.GetDrawFlag() && !fDrawSkip){	
#else // MYGAME_USE_TIMECTRL
		if(!fDrawSkip){
#endif // MYGAME_USE_TIMECTRL
			// 描画対象を描画可能な画像に
			SetDrawScreen(hDrawWindow);
			DrawBox(0, 0, WND_WIDTH, WND_HEIGHT, GetColor(0,0,0), 1);
			ClearDrawScreen();
			Draw();
			SetDrawScreen(DX_SCREEN_BACK); // 裏画面に描画
			// 画像の拡大をバイリニアに
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			// 裏画面全体に描画可能な画像を描画
			if(g_cfg.fullScreen){
				SetDrawArea(0, 0, g_cfg.screenWidth, g_cfg.screenHeight);
				if(g_cfg.screenWidth != WND_WIDTH){
					DrawExtendGraph(0, 0, g_cfg.screenWidth, 
						g_cfg.screenHeight, hDrawWindow, 0);
				}else{
					DrawGraph(0, 0, hDrawWindow, 0);
				}
			}else{
				SetDrawArea(0, 0, g_cfg.windowWidth, g_cfg.windowHeight);
				if(g_cfg.windowWidth != WND_WIDTH){
					DrawExtendGraph(0, 0, g_cfg.windowWidth, 
						g_cfg.windowHeight, hDrawWindow, 0);
				}else{
					DrawGraph(0, 0, hDrawWindow, 0);
				}
			}

			// 描画を反映
			ScreenFlip();
		}
#ifdef MYGAME_USE_TIMECTRL
		timectrl.Wait();
#endif // MYGAME_USE_TIMECTRL
		// 描画スキップフラグの解除
		fDrawSkip = false;
	}
	return nextScene;
}

bool Scene_Base::Terminate(){
	return true;
}

bool Scene_Base::Input(){
	g_input.getInput(false);
#ifdef MYGAME_USE_2P
	g_input.getInput(true);
#endif // MYGAME_USE_2P
	return true;
}

void Scene_Base::SetDrawSkip(bool f){
	fDrawSkip = f;
}

void Scene_Base::DrawReserveFade(int color) const{
	if(reservedCount > 1){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, GetFadeRate()*255);
		DrawBox(0, 0, WND_WIDTH, WND_HEIGHT, color, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}	
}