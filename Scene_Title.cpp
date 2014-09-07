// Scene_Title.cpp

#include "Scene_Title.h"
#include "DXFont.h"
#include "TempData.h"
#include "Func_AliceFile.h"
#include "Record_AliceInfo.h"

extern DXFont				g_font;
extern TempData				g_temp;
extern Record_AliceInfo		r_aliceInfo;

Scene_Title::Scene_Title():Scene_Base(),
s_main(MAX_TITLE_MENU), s_chapter(MAX_CHAPTER-1, 0, false, true) {
	phaze = TITLE_PHAZE_MAIN;
}

bool Scene_Title::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// セーブファイルがあれば続きからに移動する
	bool canContinue = false;
	for(int n=0; n<MAX_SAVEFILE; n++){
		if(GetGameFileIsExist(n+1)){
			canContinue = true;
		}
	}
	if(canContinue){
		s_main.index = TITLE_MENU_CONTINUE;
	}else{
		s_main.index = TITLE_MENU_NEWGAME;
		s_main.isActive[TITLE_MENU_CONTINUE] = false;
	}

	// 選択肢の一部を無効化
	s_main.isActive[TITLE_MENU_STOCKDOLLS] = false;
	s_main.isActive[TITLE_MENU_RECORDS] = false;

	// クリアしていないチャプターを無効化


	return true;
}

bool Scene_Title::Terminate(){

	return true;
}

int Scene_Title::Update(){
	if(!SceneIsReserved())
		switch(phaze){
		case TITLE_PHAZE_MAIN:
			switch(s_main.Move()){
			case SELECT_CHOOSE:
				switch(s_main.index){
				case TITLE_MENU_NEWGAME:
					phaze = TITLE_PHAZE_CHAPTER;
					break;
				case TITLE_MENU_CONTINUE:
					g_temp.sceneParam = TEMP_PARAM_FILE_LOADMODE;
					ReserveScene(SCENE_FILE, 20);
					break;
				case TITLE_MENU_STOCKDOLLS:
					ReserveScene(SCENE_TESTBATTLE, 90);
					break;
				case TITLE_MENU_RECORDS:
					ReserveScene(SCENE_TESTBATTLE, 90);
					break;
				case TITLE_MENU_TESTBATTLE:
					ReserveScene(SCENE_TESTBATTLE, 10);
					break;
				case TITLE_MENU_OPTION:
					// ReserveScene(SCENE_TESTBATTLE, 10);
					break;
				case TITLE_MENU_EXIT:
					ReserveScene(SCENE_END, 90);
					break;
				}
				break;
			case SELECT_CANCEL:
				// インデックスがEXITに合っている時は終了する、
				// そうで無い場合はEXITに合わせる
				if(s_main.index == TITLE_MENU_EXIT){
					ReserveScene(SCENE_END, 90);
				}else{
					s_main.index = TITLE_MENU_EXIT;
				}
				break;
			}
			break;
		case TITLE_PHAZE_CHAPTER:
			switch(s_chapter.Move()){
			case SELECT_CHOOSE:
				// 決定キー
				// 章を決定してニューゲーム
				g_temp.sceneParam = TEMP_PARAM_FILE_NEWGAME;
				ReserveScene(SCENE_FILE, 20);
				break;
			case SELECT_CANCEL:
				// キャンセルキー
				phaze = TITLE_PHAZE_MAIN;
				s_main.index = 0;
				break;
			}
			break;
	}
	return SCENE_NONE;
}

void Scene_Title::Draw() const{
	TCHAR menuString[MAX_TITLE_MENU][64] = {
		_T("はじめから"),
		_T("つづきから"),
		_T("記憶の中の人形"),
		_T("トロフィー"),
		_T("戦闘チュートリアルへ"),
		_T("オプション"),
		_T("ゲームを終了")};

	TCHAR chapterString[MAX_CHAPTER][64] = {
		_T("妖精の夢(仮)"),
		_T("幽霊の夢(仮)"),
		_T("死者の夢(仮)"),
		_T("少女の夢(仮)"),
		_T("アリスの夢(仮)"),
		_T("テストプレイ用")
	};
	
	// 各メニューを描画する
	for(int n=0; n<MAX_TITLE_MENU; n++){
		DrawStringToHandle(200, 300+34*n, menuString[n],
			(n == s_main.index ? GetColor(255, 255, 255) : GetColor(96, 96, 96)),
			g_font.hInfo, 0, 0);
	}

	// シーン切り替えのフェードの描画
	DrawReserveFade();
}

