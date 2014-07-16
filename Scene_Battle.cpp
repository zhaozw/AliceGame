// Scene_Battle.cpp

#include "Scene_Battle.h"

#include "Func_MyGraphic.h"
#include "TempData.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"

#include "MyTask_InfoEffect.h"

extern TempData		g_temp;
extern DXFont		g_font;
extern DXInput		g_input;
extern KeyConfig	g_key;
extern MyGroup*		gMyTask_InfoEffect;

Scene_Battle::Scene_Battle():Scene_Base(){
	phaze = PRE_BATTLE;
	enemyGroup = 0;
	dollsNum = 0;
	enemiesNum = 0;
}

bool Scene_Battle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// 各変数の初期化
	phaze = BEFORE_BATTLE;
	battleResult = BATTLERESULT_NONE;
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
	commandIndex = 0;

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

	// タスクグループの初期化
	gMyTask_InfoEffect->DeleteAllTask();
	return true;

}

bool Scene_Battle::Terminate(){

	return true;
}

int Scene_Battle::Update(){
	bool result = true;
	// ウィンドウやスプライトなどのアップデートを行う。
	UpdateObjects();
	// 次のアクションに移行する条件が満たされているかどうかの判定
	if(CheckNextAction()){
		// 次のアクションを実行する
		result = ExecuteAction();
		// 次のフェイズに移行する
		if(!result){
			NextPhaze();
		}	
	}

	// タスクを発生させるテスト
	if(sceneTime % 120 == 60){
		MyTask* pTask = gMyTask_InfoEffect->Call();
		if(pTask!=NULL){
			new (pTask) MyTask_InfoEffect(GetRand(200), GetRand(200), 0, 0, 0);
		}
	}

	// 戦闘終了の判断
	if(phaze == END_BATTLE){
		ReserveScene(GetNextScene(), 60);
	}
	return SCENE_NONE;

}

void Scene_Battle::UpdateObjects(){
	// バトルメッセージウィンドウのアップデート
	w_battleMsg.UpdateA();
	// 各コマンドウィンドウのアップデート
	w_aliceCommand.UpdateA();
	w_dollCommand.UpdateA();
	w_selectEnemy.UpdateA();
	w_focusedEnemy.UpdateA();

	// エフェクトのアップデート
	Update_MyTask_InfoEffect();
}

bool Scene_Battle::CheckBattleResult(){
	Game_BattleUnit* pUnit;
	bool skip;
	// 人形が全員戦闘不能の場合
	skip = false;
	for(int n=0; (n<MAX_BATTLEDOLL && !skip); n++){
		pUnit = (Game_BattleUnit*)GetDollPtr(n);
		if(pUnit != NULL){
			if(!pUnit->IsDead()){
				skip = true;
			}
		}
	}
	if(!skip){
		battleResult = BATTLERESULT_LOSE;
		return true;
	}

	// 敵が全員戦闘不能の場合
	skip = false;
	for(int n=0; (n<MAX_BATTLEENEMY && !skip); n++){
		pUnit = (Game_BattleUnit*)GetEnemyPtr(n);
		if(pUnit != NULL){
			if(!pUnit->IsDead()){
				skip = true;
			}
		}
	}
	if(!skip){
		battleResult = BATTLERESULT_VICTORY;
		return true;
	}
	return false;
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


void Scene_Battle::Draw() const{
	// スプライトの描画
	DrawDollsSprite();
	DrawEnemiesSprite();

	// バトルメッセージウィンドウの描画
	w_battleMsg.Draw();
	w_aliceCommand.Draw();
	w_dollCommand.Draw();
	w_selectEnemy.Draw();
	w_focusedEnemy.Draw();

	// エフェクトの描画
	Draw_MyTask_InfoEffect();

	// フェードの描画
	ResetDrawARGB();
	DrawReserveFade();
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

Game_BattleDoll* Scene_Battle::GetFrontDollPtr(WORD index, bool checkCanTarget){
	if(index >= NUM_BATTLEDOLL_FRONT) return NULL;
	Game_BattleDoll* pDoll = GetDollPtr(GetFrontIndex(index));
	if(checkCanTarget){
		if(!pDoll->CanTarget()){
			return NULL;
		}
	}
	return pDoll;
}

Game_BattleDoll* Scene_Battle::GetRandomDollPtr(){
	Game_BattleDoll* pDolls[NUM_BATTLEDOLL_FRONT];
	Game_BattleDoll* pTmpDoll = NULL;
	for(int n=0; n<NUM_BATTLEDOLL_FRONT; n++){
		pDolls[n] = NULL;
	}
	int index = 0;
	for(int n=0; n<NUM_BATTLEDOLL_FRONT; n++){
		pTmpDoll = GetFrontDollPtr(n);
		if(pTmpDoll != NULL){
			if(pTmpDoll->CanTarget()){
				pDolls[index] = pTmpDoll;
				index++;
			}
		}
	}
	if(index == 0) return NULL;
	return pDolls[GetRand(index-1)];
}

Game_BattleEnemy* Scene_Battle::GetRandomEnemyPtr(){
	Game_BattleEnemy* pEnemies[MAX_BATTLEENEMY];
	Game_BattleEnemy* pTmpEnemy = NULL;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pEnemies[n] = NULL;
	}
	int index = 0;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpEnemy = GetEnemyPtr(n);
		if(pTmpEnemy != NULL){
			if(pTmpEnemy->CanTarget()){
				pEnemies[index] = pTmpEnemy;
				index++;
			}
		}
	}
	if(index == 0) return NULL;
	return pEnemies[GetRand(index-1)];
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
		while(w_dollCommand.GetState() == Window_Base::CLOSED){
			// 現在何番目の人形のコマンドを選択しているか(最初は0)
			currentIndex++;
			// 全ての人形のコマンドを終えたら次へ
			if(currentIndex >= NUM_BATTLEDOLL_FRONT){
				return true;
			}else{
				// 戦闘可能な人形についてコマンド選択画面を開く
				if(GetDollPtr(GetFrontIndex(currentIndex))->CanTarget()){
					w_dollCommand.OpenWithActor(GetDollPtr(GetFrontIndex(currentIndex)));
				}
			}
		}
		break;
	case ENEMIES_COMMAND:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case BEFORE_TURN:
		// 今の所特に処理はなし
		return true;
		break;
	case BATTLE_DO:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case AFTER_TURN:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		// ステートの判定を行う。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case POST_BATTLE:
		// ウィンドウやオブジェクトが全て待機状態になっていることを確認してから次へ。
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	}
	return false;
}


bool Scene_Battle::ExecuteAction(){
	Game_BattleAction	nextAction;
	Game_UnitCommand*	unitCommand;		// コピーでなく参照を使用する
	bool				loop = false;
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
	case ENEMIES_COMMAND:
		// すぐさま次のフェイズに移行する。
		return false;
		break;
	case BEFORE_TURN:
		// アクションスタックの内容を順に実行する。
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){ // 条件2
			do{
				// 永遠ループの防止(ループして戻ってきた時)
				loop = false;
				// コマンドリストの内容を順に実行する。
				// それぞれのコマンドにおいてアクションスタックはリセットされている。
				// 次のコマンドのインデックスを取得
				commandIndex++;
				unitCommand = &commands[commandIndex];
				// 次のコマンドがない場合は終了する(条件4)
				if(unitCommand->IsEmpty()){
					return false;
				}
				// コマンドを解釈してアクションスタックに追加
				if(InterpretCommand(unitCommand, COMMANDPHAZE_START_TURN) == 0){
					// 何も処理を行わなかった場合
					loop = true;
				}
			}while(loop);
		}else{
			InterpretAction(&nextAction);
		}
		break;
	case BATTLE_DO:
		// この場所に来る条件としては、
		// 次のアクションスタックを解釈する時と、
		// アクションスタックが空になって、次のコマンドのフェイズの解釈に進む場合、
		// 一つのコマンドの処理が終わって次のコマンドに進む場合、
		// そして全てのコマンドの処理が終わった場合がある。
		// 最後の場合のみBATTLE_DOフェイズの終了判定となる。
		// 条件分岐としては、
		// 1.アクションスタックがある場合
		//   (コマンドの解釈により追加される)
		//   →とりあえず全てのアクションスタックを処理する
		// 2.アクションスタックがない場合
		//   (順番に処理していって無くなった場合)
		//   →コマンドのフェイズを一つ進める。
		//     何も処理がない場合はループする。
		// 3.コマンドのフェイズが最後まで行ったとき（②とも重なる）
		//   次のコマンドの解釈に進む。
		// 　コマンドのフェイズが最後でない場合、かつ
		//   何も処理がない場合はループする。
		// 4.全てのコマンドの解釈が終わった場合
		//   BATTLE_DOを終了する。

		// アクションスタックの内容を順に実行する。
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){ // 条件2
			do{
				// 永遠ループの防止(ループして戻ってきた時)
				loop = false;
				// コマンドリストの内容を順に実行する。
				// 各コマンドごとに、行動前、実際の行動、行動後、とフェイズに分かれる。
				// それぞれのフェイズにおいてアクションスタックはリセットされている。
				if(commandPhaze == COMMANDPHAZE_NOPHAZE){
					// コマンドの処理が終わった場合(条件3)
					// 次のコマンドのインデックスを取得
					commandIndex++;
					unitCommand = &commands[commandIndex];
					commandPhaze = COMMANDPHAZE_FIRSTPHAZE;
					// 次のコマンドがない場合は終了する(条件4)
					if(unitCommand->IsEmpty()){
						commandPhaze = COMMANDPHAZE_NOPHAZE;
						return false;
					}
					// コマンドを解釈してアクションスタックに追加
					if(InterpretCommand(unitCommand, commandPhaze) == 0){
						// 何も処理を行わなかった場合
						loop = true;
					}
				}else if(commandPhaze != COMMANDPHAZE_LASTPHAZE){
					// コマンドを解釈してアクションスタックに追加
					unitCommand = &commands[commandIndex];
					// フェイズが途中(次にまだフェイズがある)の場合
					commandPhaze++;
					// コマンドを解釈してアクションスタックに追加
					if(InterpretCommand(unitCommand, commandPhaze) == 0){
						// 何も処理を行わなかった場合
						loop = true;
					}
					// break; // 解釈は行わずにbreakする
				}else{
					// 最終フェイズの解釈を終えた場合(条件3→コマンド処理終了へ)
					// コマンドの解釈は行わずに次のコマンドへ
					commandPhaze = COMMANDPHAZE_NOPHAZE;
					if(CheckBattleResult()){
						// 戦闘の結果が決した場合は
						// すぐさま次のフェイズ(POST_BATTLE)へ
						return false;
					}
				}
			}while(loop);
		}else{
			InterpretAction(&nextAction);
		}
		break;
	case AFTER_TURN:
		return false;
		break;
	case POST_BATTLE:
		// アクションスタックの内容を順に実行する。
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){
			return false;
		}
		InterpretAction(&nextAction);
		break;
	case END_BATTLE:
		// そこから動かない
		return true;
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
	case DOLLS_COMMAND:
		phaze = ENEMIES_COMMAND;
		break;
	case ENEMIES_COMMAND:
		phaze = BEFORE_TURN;
		break;
	case BEFORE_TURN:
		phaze = BATTLE_DO;
		break;
	case BATTLE_DO:
		if(battleResult == BATTLERESULT_NONE){
			phaze = AFTER_TURN;
		}else{
			phaze = POST_BATTLE;
		}
		break;
	case AFTER_TURN:
		phaze = ALICE_COMMAND;
		break;
	case POST_BATTLE:
		phaze = END_BATTLE;
		break;
	}

	// アクションスタックの解放
	actionStack.ClearAll();

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
	case ENEMIES_COMMAND:
		SetupEnemiesCommand();
		break;
	case BEFORE_TURN:
		SetupBeforeTurn();
		break;
	case BATTLE_DO:
		SetupBattleDo();
		break;
	case AFTER_TURN:
		SetupAfterTurn();
		break;
	case POST_BATTLE:
		SetupPostBattle();
		break;
	case END_BATTLE:
		// 即座にシーン移動
		break;
	}
}

int Scene_Battle::GetNextScene(){
	// 体験版
	return SCENE_TESTBATTLE;
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
		/*
		// ダミーのコメントを入力
		action.SetType(Game_BattleAction::TYPE_CALLENEMYNAME);
		action.SetActor(NULL);
		action.SetOpponent(NULL);
		action.SetFlags(0x00000000);
		action.SetParam(0);
		actionStack.Push(action);
		*/
		break;
	}
}

void Scene_Battle::SetupDollsCommand(){
	// コマンド入力を促すウィンドウを開く
	// 最初にインクリメントが行われて0になるので-1から始める。
	currentIndex = -1;
	// コマンドが入る。
	commandIndex = 0;
	// コマンドの配列をクリアする。
	ClearCommands();
}

void Scene_Battle::SetupEnemiesCommand(){
	// 各敵キャラのコマンドをセットする
	SetEnemyCommands();
	// コマンドリストをシャッフルする
	SortUnitCommands();
}

void Scene_Battle::SetupBeforeTurn(){
	// 各キャラクターのステートなどを判定
	commandIndex = -1;
	commandPhaze = COMMANDPHAZE_START_TURN;
}

void Scene_Battle::SetupBattleDo(){
	// 最初に処理するコマンドにインデックスを合わせる
	// 最初にインクリメントが行われて0になるので-1から始める。
	commandIndex = -1;
	commandPhaze = COMMANDPHAZE_NOPHAZE;
}


void Scene_Battle::SetupAfterTurn(){
	// 本来はここに置くものではない
	UpdateStateTurn();
}

void Scene_Battle::SetupPostBattle(){
	Game_BattleAction action;
	// コマンドの解放
	ClearCommands();
	// アクションスタックの解放
	actionStack.ClearAll();
	switch(battleResult){
	case BATTLERESULT_VICTORY:
		action.SetType(Game_BattleAction::TYPE_CALLVICTORY);
		action.SetActor(NULL);
		action.SetOpponent(NULL);
		action.SetFlags(0x00000000);
		action.SetParam(0);
		actionStack.Push(action);
		ExecuteAction(); // 最初の1フレームでIDLEにならないように
		break;
	case BATTLERESULT_LOSE:
		action.SetType(Game_BattleAction::TYPE_CALLLOSE);
		action.SetActor(NULL);
		action.SetOpponent(NULL);
		action.SetFlags(0x00000000);
		action.SetParam(0);
		actionStack.Push(action);
		ExecuteAction(); // 最初の1フレームでIDLEにならないように
		break;
	}
}