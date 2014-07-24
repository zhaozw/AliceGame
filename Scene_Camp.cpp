// Scene_Camp.cpp

#include "Scene_Camp.h"
#include "DXFont.h"
#include "Func_Math.h"
#include "Func_AliceFile.h"
#include "TempData.h"
#include "WindowSkin.h"
#include <DxLib.h>

extern DXFont		g_font;
extern TempData		g_temp;
extern WindowSkins		g_wndSkins;

Scene_Camp::Scene_Camp():Scene_Base(),
	s_main(MAX_CAMP_MENU), infoIndex(CAMP_INFO_NONE), infoTime(0){
}

bool Scene_Camp::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	for(int n=0; n<MAX_CAMP_MENU; n++){
		menu_anime1[n] = 0;
		menu_anime2[n] = 0;
	}

	// ウィンドウの初期化
	InitWindow();
	// シーンステートの設定
	SetState(SCNSTATE_CAMP_CHOOSEMENU);

	return true;
}

bool Scene_Camp::Terminate(){

	return true;
}

bool Scene_Camp::InitWindow(){
	WINDOWAREA	frameArea(0, 0, 300, 300);
	WINDOWAREA	contentArea(16, 16, 300-32, 300-32);
	WINDOWFONT	font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4,
		WINDOWFONT_DEFCOLOR, WINDOWFONT_DEFICOLOR, WINDOWFONT_DEFNCOLOR);
		
	// はい・いいえウィンドウの初期化
	w_yesno.Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, contentArea, font,
		true);
	w_yesno.SetTitle(_T("ゲームを終了しますか？"), g_font.hInfo);
	w_yesno.SetPositionH(WND_WIDTH/2);		// 画面中央に揃える
	w_yesno.SetPositionV(WND_HEIGHT/2);
	return true;
}

int Scene_Camp::Update(){
	if(!SceneIsReserved()){
		switch(state){
		case SCNSTATE_CAMP_CHOOSEMENU:
			switch(s_main.Move()){
			case SELECT_CHOOSE:
				switch(s_main.index){
				case CAMP_MENU_CREATE:
					ReserveScene(SCENE_DOLLCREATE, 20);
					break;
				case CAMP_MENU_SAVE:
					// セーブを行う
					if(SaveGame(g_temp.fileIndex)){
						SetInfo(CAMP_INFO_SAVE);
					}
					break;
				case CAMP_MENU_EXIT:
					// 上書きするかどうかの確認
					SetState(SCNSTATE_CAMP_ASKQUITGAME);
					w_yesno.SetVisible(true);
					w_yesno.Open();
					break;
				}
				break;
			}
			break;
		case SCNSTATE_CAMP_ASKQUITGAME:
			w_yesno.Update();
			if(w_yesno.GetState() == Window_Base::CLOSED){
				// 決定された場合
				switch(w_yesno.GetResult()){
				case WINDOW_YESNO_YES:
					// LoadGame(s_file.index+1);
					ReserveScene(SCENE_TITLE, 120);
					break;
				case WINDOW_YESNO_NO:
					SetState(SCNSTATE_CAMP_CHOOSEMENU);
					break;
				}
			}
			break;
		}
	}

	// メニューのアニメーション
	for(int n=0; n<MAX_CAMP_MENU; n++){
		// アニメ1
		// フォーカスが合っている時はプラス、
		// フォーカスが外れるとマイナスになる
		if(s_main.index == n){
			menu_anime1[n] += (WORD)(0.1*(CAMP_ANIME1_TIME-menu_anime1[n]));
		}else{
			menu_anime1[n] = (WORD)(0.2*menu_anime1[n]);
		}
		// アニメ2
		// フォーカスが当たった時、アニメーションを開始する。
		// フォーカスに関わらずアニメーションを行う。
		if(s_main.index == n && menu_anime2[n]==0){
			menu_anime2[n] = 1;
		}
		if(menu_anime2[n] > 0){
			menu_anime2[n]++;
			if(menu_anime2[n] >= CAMP_ANIME2_TIME){
				if(s_main.index == n){
					// アニメーションが終わっても
					// まだフォーカスが当たっている場合
					menu_anime2[n] = CAMP_ANIME2_TIME;
				}else{
					// フォーカスが外れている
					menu_anime2[n] = 0;
				}
			}
		}
	}
	// 画面下部の情報の更新
	if(infoTime > 0){
		infoTime++;
		if(infoTime > CAMP_INFO_TIME){
			infoTime = 0;
			infoIndex = 0;
		}
	}

	return SCENE_NONE;
}

void Scene_Camp::Draw() const{
	int w; // 描画する文字の幅

	// メニューの文字
	TCHAR menuString[MAX_CAMP_MENU][64] = {
		_T("ダンジョンへ（未実装）"),
		_T("チーム編成（未実装）"),
		_T("人形の作成（未実装）"),
		_T("セーブ"),
		_T("ゲームを終了（タイトルに戻る）")};

	// 情報の文字
		TCHAR infoString[MAX_CAMP_INFO][128] = {
			_T("データをセーブしました。"),
			_T("休息して魔力を回復しました。")
		};

	// 各メニューを描画する
	for(int n=0; n<MAX_CAMP_MENU; n++){
		// menu_anime1は最大1000
		// menu_anime2は最大10
		DrawStringToHandle(
			100-0.04*menu_anime1[n],
			80+60*n,
			menuString[n],
			(n == s_main.index 
			? (menu_anime2[n] == 0 
				? GetColor(255, 255, 255) 
				: GetColor(255, 255, PARAM(30*menu_anime2[n])))
			: GetColor(96, 96, 96)),
			g_font.hInfo, 0, 0);

	}

	// ウィンドウの描画
	w_yesno.Draw();

	// 画面下の情報の描画
	if(infoIndex != CAMP_INFO_NONE && infoIndex <= MAX_CAMP_INFO){
		w = GetDrawFormatStringWidthToHandle(g_font.hInfo, infoString[infoIndex-1]);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,
			min(infoTime*60, 6*PARAM(CAMP_INFO_TIME-infoTime)));
		DrawStringToHandle((WND_WIDTH-w)/2, WND_HEIGHT-80, 
			infoString[infoIndex-1], GetColor(255, 255, 255),
			g_font.hInfo);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawReserveFade();
}

