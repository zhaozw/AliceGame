// Scene_Battle.cpp

#include "Scene_Battle.h"

#include "Func_MyGraphic.h"
#include "TempData.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"

extern TempData		g_temp;
extern DXFont		g_font;
extern DXInput		g_input;
extern KeyConfig	g_key;

Scene_Battle::Scene_Battle():Scene_Base(){
	phaze = PRE_BATTLE;
	subPhaze = ASSERT_ACTION;
	enemyGroup = 0;
	dollsNum = 0;
	enemiesNum = 0;
}

bool Scene_Battle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// 各変数の初期化
	phaze = BEFORE_BATTLE;
	subPhaze = ASSERT_ACTION;
	enemyGroup = g_temp.enemyGroup;
	// 敵と味方の初期化
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		dolls[n].Reset();
	}
	dollsNum = 0;

	for(int n=0; n<MAX_BATTLEENEMY; n++){
		enemies[n].Reset();
	}
	enemiesNum = 0;

	for(int n=0; n<MAX_UNITCOMMAND; n++){
		commands[n].Reset();
	}

	currentIndex = 0;
	// 味方と敵のセットアップ
	if(!SetupDolls()){
		return false;
	}
	if(!SetupEnemy()){
		return false;
	}
	// ウィンドウのセットアップ
	if(!SetupWindow()){
		return false;
	}
	// スプライトのセットアップ
	if(!SetupSprite()){
		return false;
	}
	return true;

}

bool Scene_Battle::Terminate(){

	return true;
}

int Scene_Battle::Update(){
	bool result = true;
	// 次のアクションに移行する条件が満たされているかどうかの判定
	if(CheckNextAction()){
		// 次のアクションを実行する
		result = ExecuteAction();

		// 次のフェイズに移行する
		if(!result){
			NextPhaze();
		}	
	}
	// ウィンドウやスプライトなどのアップデートを行う。
	UpdateObjects();

	return SCENE_NONE;

}

void Scene_Battle::UpdateObjects(){
	// バトルメッセージウィンドウのアップデート
	w_battleMsg.UpdateA();
	w_aliceCommand.UpdateA();
	w_dollCommand.UpdateA();
	w_selectEnemy.UpdateA();
	w_focusedEnemy.UpdateA();
}

bool Scene_Battle::AttachDollPtrToSprite(){
	Game_BattleDoll*	pDoll	= NULL;
	int					index	= 0;
	bool				result	= true;
	for(int i=0; i<NUM_BATTLEDOLL_FRONT; i++){
		s_dolls[i].ResetDollPtr();
		index = GetFrontIndex(i);
		pDoll = GetDollPtr(index);
		if(pDoll == NULL && i <= dollsNum){
			result = false;
		}
		s_dolls[i].SetDollPtr(pDoll);
	}
	return result;
}

void Scene_Battle::Draw(){
	// スプライトの描画
	DrawDollsSprite();
	DrawEnemiesSprite();

	// バトルメッセージウィンドウの描画
	w_battleMsg.Draw();
	w_aliceCommand.Draw();
	w_dollCommand.Draw();
	w_selectEnemy.Draw();
	w_focusedEnemy.Draw();

}

bool Scene_Battle::SetupWindow(){
	// バトルメッセージウィンドウ
	w_battleMsg.Setup(this);
	w_aliceCommand.MySetup();
	w_dollCommand.MySetup(this);
	w_selectEnemy.MySetup(this);
	w_focusedEnemy.MySetup(this);
	return true;
}

bool Scene_Battle::SetupSprite(){
	// 人形スプライト
	for(int i=0; i<NUM_BATTLEDOLL_FRONT; i++){
		s_dolls[i].SetPosition(i);
		s_dolls[i].SetVisible(true);
	}
	if(!AttachDollPtrToSprite()) return false;
	// 敵スプライト
	for(int i=0; i<MAX_BATTLEENEMY; i++){
		s_enemies[i].AttachBattleEnemy(&enemies[i]);
	}
	return true;
}

int Scene_Battle::GetFrontIndex(WORD position){
	int cntCount = 0;
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		if(dolls[n].GetFront()){
			if(cntCount == position){
				return n;
			}else{
				cntCount++;
			}
		}
	}
	return -1;
}


BYTE Scene_Battle::OpenSelectEnemyWindow(){
	return w_selectEnemy.Open();
}


bool Scene_Battle::CheckNextAction(){
	switch(phaze){
	case BEFORE_BATTLE:
		// すぐさま次のフェイズに移行する
		return true;
		break;
	case PRE_BATTLE:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case ALICE_COMMAND:
		// アリスのコマンドウィンドウが閉じていることを確認してから次へ。
		if(w_aliceCommand.GetState() == Window_Base::CLOSED){
			return true;
		}
		break;
	case ALICE_COMMAND_DO:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case DOLLS_COMMAND:
		// ウィンドウが閉じていて、かつインデックスが
		// 終了状態であれば次へ
		if(w_dollCommand.GetState() == Window_Base::CLOSED){
			// 入力した結果を保存する
			if(currentIndex > 0){
				commands[currentIndex].Reset();

			}
			// 現在何番目の人形のコマンドを選択しているか(最初は0)
			currentIndex++;
			// 全ての人形のコマンドを終えたら次へ
			if(currentIndex >= NUM_BATTLEDOLL_FRONT){
				return true;
			}else{
				w_dollCommand.Open();
			}
		}
		break;
	}
	return false;
}


bool Scene_Battle::ExecuteAction(){
	Game_BattleAction nextAction;
	switch(phaze){
	case BEFORE_BATTLE:
		// すぐさま次のフェイズに移行する。
		return false;
		break;
	case PRE_BATTLE:
		// アクションスタックの内容を順に実行する。
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){
			return false;
		}
		InterpretAction(&nextAction);
		break;
	case ALICE_COMMAND:
		// すぐさま次のフェイズに移行する。
		return false;
		break;
	case ALICE_COMMAND_DO:
		// アクションスタックの内容を順に実行する。
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){
			return false;
		}
		InterpretAction(&nextAction);
		break;
	case DOLLS_COMMAND:
		// すぐさま次のフェイズに移行する。
		return false;
		break;
	}
	return true;
}

void Scene_Battle::NextPhaze(){
	// 変化前のphaze値でswitch分岐
	switch(phaze){
	case BEFORE_BATTLE:
		phaze = PRE_BATTLE;
		break;
	case PRE_BATTLE:
		phaze = ALICE_COMMAND;
		break;
	case ALICE_COMMAND:
		phaze = ALICE_COMMAND_DO;
		break;
	case ALICE_COMMAND_DO:
		phaze = DOLLS_COMMAND;
		break;
	}

	// アクションスタックの解放
	actionStack.ClearAll();

	// コマンドの解放
	ClearCommands();

	// 変化後のphaze値でswitch分岐
	switch(phaze){
	case BEFORE_BATTLE:
		break;
	case PRE_BATTLE:
		SetupPreBattle();
		break;
	case ALICE_COMMAND:
		SetupAliceCommand();
		break;
	case ALICE_COMMAND_DO:
		SetupAliceCommandDo();
		break;
	case DOLLS_COMMAND:
		SetupDollsCommand();
		break;
	}
}

void Scene_Battle::SetupPreBattle(){
	Game_BattleAction action;
	// スタックなので逆順に積んでいく。

	// 各キャラクターのステートに応じた状態表示。
	
	// 各敵キャラの名前を表示。
	action.SetType(Game_BattleAction::TYPE_CALLENEMYNAME);
	action.SetActor(NULL);
	action.SetOpponent(NULL);
	action.SetFlags(0x00000000);
	action.SetParam(0);
	actionStack.Push(action);
	ExecuteAction(); // 最初の1フレームでIDLEにならないように
}

void Scene_Battle::SetupAliceCommand(){
	// アリスのコマンドウィンドウを開く
	w_aliceCommand.Open();
}

void Scene_Battle::SetupAliceCommandDo(){
	Game_BattleAction action;
	switch(w_aliceCommand.GetResult()){
	case ALICE_COMMAND_BATTLE:
		// 何もしない
		break;
	case ALICE_COMMAND_UNITCHANGE:
		break;
	case ALICE_COMMAND_SPECIAL:
		break;
	case ALICE_COMMAND_ESCAPE:
		// ダミーのコメントを入力
		action.SetType(Game_BattleAction::TYPE_CALLENEMYNAME);
		action.SetActor(NULL);
		action.SetOpponent(NULL);
		action.SetFlags(0x00000000);
		action.SetParam(0);
		actionStack.Push(action);
		break;
	}
}

void Scene_Battle::SetupDollsCommand(){
	// コマンド入力を促すウィンドウを開く
	// 最初にインクリメントが行われて0になるので-1から始める。
	currentIndex = -1;

}

