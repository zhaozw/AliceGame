// Scene_ChooseMap.cpp

#include "Scene_ChooseMap.h"
#include "Data_ChooseMap.h"
#include "Record_ChooseMap.h"
#include "Record_AliceInfo.h"
#include "DXInput.h"
#include "KeyConfig.h"


extern Data_ChooseMap		d_chooseMap;
extern Record_ChooseMap		r_chooseMap;
extern Record_AliceInfo		r_aliceInfo;
extern DXInput				g_input;
extern KeyConfig			g_key;

Scene_ChooseMap::Scene_ChooseMap() : Scene_Base(){
}

bool Scene_ChooseMap::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// 各メンバ変数の更新
	moving = false;
	alicePosX = 0;
	alicePosY = 0;
	cntIndex = lastIndex = 1;
	phaze = PHAZE_EVENT;
	phazeTime = 0;
	openingIndex = 0;
	// 既に解放されているパス・ポイントの解放を行う
	RefreshPoints();
	// アリスの描画位置の更新
	UpdateAlicePos();
	// フェイズのセット
	SetPhaze(PHAZE_EVENT);

	return true;
}

bool Scene_ChooseMap::Terminate(){

	return true;
}

int Scene_ChooseMap::Update(){
	UpdateAlicePos();
	switch(phaze){
	case PHAZE_EVENT:
		break;
	case PHAZE_OPENPATH:
		// 本当は演出を行うが、ここでは一瞬で道が出来る。
		r_chooseMap.OpenPath(openingIndex);
		SetPhaze(PHAZE_CHECK);
		break;
	case PHAZE_OPENPOINT:
		// 本当は演出を行うが、ここでは一瞬でポイントが出来る。
		// r_chooseMap.OpenPoint(openingIndex);
		SetPhaze(PHAZE_CHECK);
		break;
	case PHAZE_STANDBY:
		if(!moving){
			// 入力を受け付ける
			CheckAliceMove();
		}
		break;
	case PHAZE_MENU:
		break;
	}
	phazeTime++;

	if(g_input.pushedKey & g_key.input[BTN_CANCEL]){
		ReserveScene(SCENE_CAMP, 10);
	}
	return SCENE_NONE;
}

bool Scene_ChooseMap::SetPhaze(enum CHOOSEMAP_PHAZE _phaze){
	enum CHOOSEMAP_PHAZE result = PHAZE_ERROR;
	openingIndex = 0;
	bool recursive = false;	// 再度SetPhazeを行うフラグ
	switch(_phaze){
	case PHAZE_EVENT:
		if(CheckEventHappen() != 0){
			result = PHAZE_EVENT;
		}else{
			result = PHAZE_OPENPATH;
			recursive = true;
		}
		break;
	case PHAZE_OPENPATH:
		openingIndex = CheckPathOpen();
		if(openingIndex != 0){
			result = PHAZE_OPENPATH;
		}else{
			result = PHAZE_OPENPOINT;
			recursive = true;
		}
		break;
	case PHAZE_OPENPOINT:
		openingIndex = CheckPointOpen();
		if(openingIndex != 0){
			result = PHAZE_OPENPOINT;
		}else{
			result = PHAZE_STANDBY;
			recursive = true;
		}
		break;
	case PHAZE_STANDBY:
		result = PHAZE_STANDBY;
		break;
	case PHAZE_CHECK:
		result = PHAZE_EVENT;
		recursive = true;
		break;
	}
	// resultに値が入った場合はそのフェイズに移行
	// そうでない場合はfalseを返す
	if(result == PHAZE_ERROR){
		return false;
	}else{
		if(recursive){
			SetPhaze(result);
		}else{
			phaze = result;
		}
		return true;
	}
}

WORD Scene_ChooseMap::CheckEventHappen(){
	return 0;
}

WORD Scene_ChooseMap::CheckPathOpen(){
	// 現在の記録からパスの解放を判定する
	return r_chooseMap.CheckPathOpen(r_aliceInfo.GetChapter());
}

WORD Scene_ChooseMap::CheckPointOpen(){
	// 現在の記録からポイントの解放を判定する
	for(int n=0; n<CHOOSEMAP_POINT_MAX; n++){
		if(!pointIsOpened[n]){
			if(CheckOpenPoint(n) != 0){
				return n;
			}
		}
	}
	return 0;
}

bool Scene_ChooseMap::CheckOpenPoint(WORD index){
	for(int n=0; n<CHOOSEMAP_PATH_MAX; n++){
		if(r_chooseMap.GetPathState(n) == CHOOSEMAP_PATHSTATE_OPENED){
			for(int j=0; j<2; j++){
				if(index == d_chooseMap.GetPathEdgeIndex(n, j==0)){
					return true;
				}
			}
		}
	}
	return false;
}

void Scene_ChooseMap::RefreshPoints(){
	for(int n=0; n<CHOOSEMAP_POINT_MAX; n++){
		if(CheckOpenPoint(n)){
			pointIsOpened[n] = true;
		}
	}
}

void Scene_ChooseMap::UpdateAlicePos(){
	if(!moving){
		// ポイントの位置にアリスを移動させる
		alicePosX = d_chooseMap.GetPointX(cntIndex);
		alicePosY = d_chooseMap.GetPointY(cntIndex);
	}
}

bool Scene_ChooseMap::CheckAliceMove(){
	BYTE		direction = MAP_NODIRECTION;
	// 入力された方向キーを方角に変換
	switch(g_input.digitalDir){
	case 8:
		direction = MAP_NORTH;
		break;
	case 6:
		direction = MAP_EAST;
		break;
	case 2:
		direction = MAP_SOUTH;
		break;
	case 4:
		direction = MAP_WEST;
		break;
	}
	return false;
}

void Scene_ChooseMap::Draw() const{
	// 背景の描画
	DrawBG();
	// マップの描画
	DrawMap();
	// キャラクターの描画
	DrawCharacters();
	DrawCommand();
	DrawReserveFade();
}

void Scene_ChooseMap::DrawBG() const{
}

void Scene_ChooseMap::DrawMap() const{
	DrawPaths();
	DrawPoints();
}

void Scene_ChooseMap::DrawPoint(int index) const{
	int cx=0, cy=0;
	BYTE	state = 0;		// 0:未出現、 1:攻略中、2:クリア済み
							// 3:攻略中(アリスの現在の場所)、
							// 4:クリア済み(アリスの現在の場所)
	cx = d_chooseMap.GetPointX(index);
	cy = d_chooseMap.GetPointY(index);
	// ※この記述は間違い。ポイントIDとエリアIDを混同している。
	if(pointIsOpened[index]){
		if(index == cntIndex){
			state = 4;
		}else{
			state = 2;
		}
	}else if(r_chooseMap.GetStageOfArea(index) > 0){
		if(index == cntIndex){
			state = 3;
		}else{
			state = 1;
		}
	}

	switch(state){
	case 0:
		break;
	case 1:
		DrawBox(cx-10, cy-5, cx+10, cy+5, GetColor(127,127,127), 1);
		break;
	case 2:
		DrawBox(cx-10, cy-5, cx+10, cy+5, GetColor(255,255,255), 1);
		break;
	case 3:
		DrawBox(cx-10, cy-5, cx+10, cy+5, GetColor(255, 127, 0), 1);
		break;
	case 4:
		DrawBox(cx-10, cy-5, cx+10, cy+5, GetColor(127, 255, 0), 1);
		break;
	}
}

void Scene_ChooseMap::DrawPoints() const{
	for(int n=1; n<CHOOSEMAP_POINT_MAX; n++){
		DrawPoint(n);
	}
}

void Scene_ChooseMap::DrawPath(int index) const{
	// 両端の座標を取得する
	WORD p=0;
	float px[2], py[2];
	for(int i=0; i<2; i++){
		p = d_chooseMap.GetPathEdgeIndex(index, i!=0);
		px[i] = d_chooseMap.GetPointX(p);
		py[i] = d_chooseMap.GetPointY(p);
	}
	switch(r_chooseMap.GetPathState(index)){
	case CHOOSEMAP_PATHSTATE_NONE:
		return;
	case CHOOSEMAP_PATHSTATE_OPENED:
		DrawLine(px[0], py[0], px[1], py[1], GetColor(96, 96, 96), 3);
		break;
	}
}

void Scene_ChooseMap::DrawPaths() const{
	for(int n=1; n<CHOOSEMAP_PATH_MAX; n++){
		DrawPath(n);
	}
}

void Scene_ChooseMap::DrawCharacters() const{
	DrawAlice();
	if(!moving && phaze == PHAZE_STANDBY){
		DrawAliceDirection(alicePosX, alicePosY);
	}
}

// アリスの描画を行う。
void Scene_ChooseMap::DrawAlice() const{
	DrawBox(alicePosX-15, alicePosY-40, alicePosX+15, alicePosY,
		GetColor(0, 255, 0), 1);
}

// アリスが移動出来ることを示す矢印を描画する。
void Scene_ChooseMap::DrawAliceDirection(int aliceX, int aliceY) const{
	for(BYTE n=MAP_NORTH; n<MAP_WEST; n++){
		if(r_chooseMap.CheckAliceDirection(cntIndex, n)){
			DrawDirection(aliceX, aliceY, n);
		}
	}
}

void Scene_ChooseMap::DrawDirection(int aliceX, int aliceY, BYTE direction) const{
	switch(direction){
	case MAP_NORTH:
		DrawBox(aliceX-5, aliceY-40, aliceX+5, aliceY-30, GetColor(255, 0, 0), 1);
		break;
	case MAP_EAST:
		DrawBox(aliceX+30, aliceY-5, aliceX+40, aliceY+5, GetColor(255, 0, 0), 1);
		break;
	case MAP_SOUTH:
		DrawBox(aliceX-5, aliceY+30, aliceX+5, aliceY+40, GetColor(255, 0, 0), 1);
		break;
	case MAP_WEST:
		DrawBox(aliceX-40, aliceY-5, aliceX-30, aliceY+5, GetColor(255, 0, 0), 1);
		break;
	}
}

void Scene_ChooseMap::DrawCommand() const{
}