// Scene_Sample.cpp
// 基本的には現在のデータを表示するだけのシーン。
// ランキング入りした場合はランクインも表示する。

#include "Scene_Sample.h"

// 追加ヘッダファイル
#include "MyTask.h"
#include "MyTask_Sample.h"

#include "Static_Game.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "GlobalData.h"

#include "Player_Sample.h"

extern DXInput g_input;
extern KeyConfig g_key;
extern GlobalData g_dat;

extern MyGroup* gMyTask_Sample;


Scene_Sample::Scene_Sample():Scene_Base(){
}

bool Scene_Sample::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}

bool Scene_Sample::Terminate(){

	return true;
}

int Scene_Sample::Update(){
	// タスクを毎フレーム追加する
	MyTask* pTask = gMyTask_Sample->Call();
	if(pTask!=NULL){
		new (pTask) MyTask_Sample();
	}

	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]){
		ReserveScene(SCENE_END, 120);
	}

	// タスクを毎フレーム更新する
	Update_MyTask_Sample();

	// 自機との接触の判定
	Check_MyTask_Sample_Burst(player.GetX(), player.GetY());

	// 敵同士の連鎖爆発の判定
	Check_MyTask_Sample_Chain_Burst();

	// オブジェクトではない
	player.Update();

	return SCENE_NONE;
}

void Scene_Sample::Draw() const{
	// 得点の描画
	DrawBox(0, WND_HEIGHT-20, g_dat.score, WND_HEIGHT-15, GetColor(132, 132, 132), 1);

	int div = 32;
	// 縦線
	for(int lx = 0; lx < WND_WIDTH; lx += div){
		DrawLine(lx, 0, lx, WND_HEIGHT, GetColor(64, 64, 64), 1);
	}
	// 横線
	for(int ly = 0; ly < WND_HEIGHT; ly += div){
		DrawLine(0, ly, WND_WIDTH, ly, GetColor(64, 64, 64), 1);
	}

	Draw_MyTask_Sample();

	DrawReserveFade();



	// オブジェクトではない
	player.Draw();
}

