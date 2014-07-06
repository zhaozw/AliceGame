// Scene_File.cpp

#include "Scene_File.h"
#include "TempData.h"
#include "Func_AliceFile.h"
#include "DXFont.h"
#include "Window_Selectable.h"
#include "WindowSkin.h"

extern TempData g_temp;
extern DXFont	g_font;
extern WindowSkins g_wndSkins;

Scene_File::Scene_File() : s_file(MAX_SAVEFILE, 0, true, true, 0),
	w_yesno(){
	moving = 0x00;
	movingTime = 0;
	drawIndex = 0;
}

bool Scene_File::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// 変数の初期化
	for(int n=0; n<MAX_SAVEFILE; n++){
		isFile[n] = false;
	}
	// 現在のモードを読み込む。
	mode = g_temp.sceneParam;
	// 各ファイルからファイルヘッダを読み込む。
	// セーブデータが存在しないファイルはisFileをfalseにする。
	for(int n=0; n<MAX_SAVEFILE; n++){
		// +1は、選択肢は0から始まるため
		if(GetGameFileHeader(&header[n], n+1)){
			isFile[n] = true;
		}
	}
	// 各ファイルを選択可能にするか否かの判定
	switch(mode){
	case TEMP_PARAM_FILE_NEWGAME:
		// 全てのファイルを選択可能
		break;
	case TEMP_PARAM_FILE_SAVEMODE:
		// 全てのファイルを選択可能
		break;
	case TEMP_PARAM_FILE_LOADMODE:
		// データのないファイルは選択不可能
		for(int n=0; n<MAX_SAVEFILE; n++){
			s_file.isActive[n] = isFile[n];
		}
		break;
	}

	// ウィンドウの初期化
	InitWindow();

	// シーンステートの設定
	SetState(SCNSTATE_FILE_CHOOSEFILE);

	return true;
}

bool Scene_File::Terminate(){
	return true;
}

bool Scene_File::InitWindow(){
	// はい・いいえウィンドウの初期化
	w_yesno.Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		0, 0, g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4,
		true, ALIGN_CENTER);
	w_yesno.SetTitle(_T("ファイルを上書きしますか？"));
	w_yesno.SetAllColor(
		GetColor(255, 255, 255),
		GetColor(192, 192, 192),
		GetColor(64, 64, 64));
	w_yesno.SetDefParam();
	w_yesno.SetPositionH(WND_WIDTH/2);		// 画面中央に揃える
	w_yesno.SetPositionV(WND_HEIGHT/2);
	return true;
}

int Scene_File::Update(){
	switch(GetState()){
	case SCNSTATE_FILE_CHOOSEFILE:
		if(!SceneIsReserved()){
			if(moving == 0){
				switch(s_file.Move()){
				case SELECT_CHOOSE:
					switch(mode){
					case TEMP_PARAM_FILE_NEWGAME:
						if(isFile[s_file.index]){
							// 上書きするかどうかの確認
							SetState(SCNSTATE_FILE_ASKOVERWRITE);
							w_yesno.SetVisible(true);
							w_yesno.Open();
						}else{
							// ゲームを初期化して始める
							g_temp.fileIndex = s_file.index+1;
							// 全てのデータを初期化
							NewGame();
							ReserveScene(SCENE_CAMP, 90);
						}
						/*
						// ファイル番号を指定し、最初のシーンへ移動
						// +1は、選択肢が0から始まるのを補正するため
						g_temp.fileIndex = s_file.index+1;
						ReserveScene(SCENE_CAMP, 90);
						*/
						break;
					case TEMP_PARAM_FILE_LOADMODE:
						// ファイルのロードを行う。
						g_temp.fileIndex = s_file.index+1;
						LoadGame(s_file.index+1);
						ReserveScene(SCENE_CAMP, 60);
						break;
					}
					break;
				case SELECT_CANCEL:
					switch(mode){
					case TEMP_PARAM_FILE_NEWGAME:
					case TEMP_PARAM_FILE_LOADMODE:
						// タイトルに戻る
						ReserveScene(SCENE_TITLE, 20);
						break;
					}
					break;
				default:
					// 現在選択中のものが画面内に表示されているかどうかを判定する。
					if(abs(s_file.lastIndex-s_file.index) > 1){
						// 画面の端から端への移動
						if(s_file.index == 0){
							// ファイル末尾から0への移動
							drawIndex = 0;
							moving = 0x00;
						}else{
							// 0からファイル末尾への移動
							drawIndex = MAX_SAVEFILE-FILESELECT_FILE_PER_PAGE;
							moving = 0x00;
						}
					}else{
						if(s_file.index >= drawIndex+FILESELECT_FILE_PER_PAGE){
							moving = 0x01;
							movingTime = 0;
						}
						if(s_file.index < drawIndex){
							moving = 0x02;
							drawIndex--;
							movingTime = 0;
						}
					}
					break;
				}
			}else{
				movingTime++;
				if(movingTime >= FILESELECT_SCROLL_TIME){
					if(moving == 0x01){
						drawIndex++;
					}
					moving = 0x00;
					movingTime = 0;
					s_file.lastIndex = s_file.index;
				}
			}
		}
		break;
	case SCNSTATE_FILE_ASKOVERWRITE:
		w_yesno.Update();
		if(w_yesno.GetState() == Window_Base::CLOSED){
			// 決定された場合
			switch(w_yesno.GetResult()){
			case WINDOW_YESNO_YES:
				// ゲームを初期化して始める
				g_temp.fileIndex = s_file.index+1;
				// 全てのデータを初期化
				NewGame();
				ReserveScene(SCENE_CAMP, 90);
				break;
			case WINDOW_YESNO_NO:
				SetState(SCNSTATE_FILE_CHOOSEFILE);
				break;
			}
		}
		break;
	}
	return SCENE_NONE;
}

void Scene_File::Draw(){
	// 描画可能範囲の設定
	SetDrawArea(
		0, DRAW_FILE_BASEY-5,
		400, 
		DRAW_FILE_BASEY+DRAW_FILE_WLH*FILESELECT_FILE_PER_PAGE-DRAW_FILE_MARGINY+5);
	// 各ファイルの描画
	int baseY = DRAW_FILE_BASEY;
	switch(moving){
	case 1:
		baseY -= DRAW_FILE_WLH*movingTime/FILESELECT_SCROLL_TIME;
		break;
	case 2:
		baseY -= DRAW_FILE_WLH*(FILESELECT_SCROLL_TIME-movingTime)
			/FILESELECT_SCROLL_TIME;
		break;
	}
	int cntN;

	for(int n=0; n<FILESELECT_FILE_PER_PAGE+1; n++){
		cntN = (n+drawIndex+MAX_SAVEFILE)%MAX_SAVEFILE;
		if(isFile[cntN]){
			DrawSaveFile(40, baseY+(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)*n,
				cntN, s_file.index==cntN, s_file.isActive[cntN]);
		}else{
			DrawEmptyFile(40, baseY+(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)*n,
				cntN, s_file.index==cntN, s_file.isActive[cntN]);
		}
	}

	SetDrawArea(0, 0, WND_WIDTH, WND_HEIGHT);
	// 選択中のファイルの詳細表示
	DrawSelectedFile(420, 40, s_file.index);
	// ウィンドウの描画
	w_yesno.Draw();
	// シーンフェードの描画
	DrawReserveFade();
}

void Scene_File::DrawSaveFile(int x, int y, BYTE index,
	bool isActive, bool canSelect) const{
		int	pT, pH, pM, pS;	// プレイ時間計算用の変数
		int sT, sY, sM, sD, sH, sMi;	// セーブ時間計算用の変数
		// プレイ時間の計算
		pT = header[index].data.playTime;
		pH = (int)(pT / 3600);
		pT -= pH*3600;
		pM = (int)(pT / 60);
		pT -= pM*60;
		pS = pT;
		// セーブ時間の計算
		sT = header[index].data.savedYMD;
		sY = (int)(sT / 10000);
		sT -= sY*10000;
		sM = (int)(sT / 100);
		sT -= sM*100;
		sD = sT;
		// セーブ時間の計算
		sT = header[index].data.savedHMS;
		sH = (int)(sT / 10000);
		sT -= sH*10000;
		sMi = (int)(sT / 100);


		DrawBox(x, y, x+DRAW_FILE_WIDTH, y+DRAW_FILE_HEIGHT,
			(isActive?GetColor(255, 255, 255):GetColor(64, 64, 64)), 0);
		int n = 
			canSelect  
			? (isActive ? 255 : 160) : 64;
		TCHAR buf[64];
		wsprintf(buf, _T("ファイル%02d"), index+1);
		DrawStringToHandle(x, y, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("%02d/%02d/%02d"), sY, sM, sD);
		DrawStringToHandle(x, y+30, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("%02d:%02d"), sH, sMi);
		DrawStringToHandle(x+200, y+30, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("プレイ時間　%02d:%02d"), pH, pM);
		DrawStringToHandle(x, y+60, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("魔力　%03d"), header[index].data.alice_mp);
		DrawStringToHandle(x+240, y+60, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
}

void Scene_File::DrawEmptyFile(int x, int y, BYTE index,
	bool isActive, bool canSelect) const{
		DrawBox(x, y, x+DRAW_FILE_WIDTH, y+DRAW_FILE_HEIGHT,
			(isActive?GetColor(255, 255, 255):GetColor(64, 64, 64)), 0);
		int n = 
			canSelect  
			? (isActive ? 255 : 160) : 64;
		TCHAR buf[64];
		wsprintf(buf, _T("ファイル%02d"), index+1);
		DrawStringToHandle(x, y, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		DrawStringToHandle(x, y+32, _T("ファイルが存在しません。"), GetColor(255, 255, 255),
			g_font.hInfo, 0, 0);
}

void Scene_File::DrawSelectedFile(int x, int y, BYTE index){
	DrawBox(x, y, x+DRAW_SELECTED_WIDTH, y+DRAW_SELECTED_HEIGHT,
		GetColor(255, 255, 255), 0);
}