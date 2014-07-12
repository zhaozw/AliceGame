// Game_BattleAction.cpp

#include "Game_BattleAction.h"

// Game_BattleActionクラス

Game_BattleAction::Game_BattleAction(){
	Clear();
}

// 代入演算子
Game_BattleAction &Game_BattleAction::operator=(const Game_BattleAction &action){
	pActor = action.pActor;
	pOpponent = action.pOpponent;
	type = action.type;
	flags = action.flags;
	param = action.param;

	return(*this);  // ここは決まり文句。これにより s1=s2=s3; などといった記述が可能になる。
}

void Game_BattleAction::Clear(){
	pActor = NULL;
	pOpponent = NULL;
	type = TYPE_UNDIFINED;
	flags = 0;
	param = 0;
}

// Game_BattleActionStackクラス

Game_BattleActionStack::Game_BattleActionStack():data(){
	cntIndex = 0;
}

Game_BattleAction Game_BattleActionStack::GetCntData(){
	if(cntIndex < 0 || cntIndex > MAX_BATTLEACTIONSTACK) return data[0];
	return data[cntIndex];
}

bool Game_BattleActionStack::Push(Game_BattleAction action){
	if(cntIndex < MAX_BATTLEACTIONSTACK){
		// 新しく積む
		cntIndex++;
		// 内容をそのまま代入？
		data[cntIndex] = action;
	}else{
		return false;
	}
	return true;
}

Game_BattleAction Game_BattleActionStack::Pop(){
	Game_BattleAction result;
	if(cntIndex <= 0 || cntIndex > MAX_BATTLEACTIONSTACK){
		// エラー
		result = data[0];
	}else{
		cntIndex--;
		result = data[cntIndex+1]; // さっきまで指していたデータ
		data[cntIndex+1].Clear();
	}
	return result;
}

Game_BattleAction Game_BattleActionStack::Pop_NoRemove(){
	Game_BattleAction result;
	if(cntIndex <= 0 || cntIndex > MAX_BATTLEACTIONSTACK){
		// エラー
		result = data[0];
	}else{
		// インデックスをずらさずにデータを取り出す
		result = data[cntIndex];
	}
	return result;
}


void Game_BattleActionStack::ClearAll(){
	for(int n=0; n<=MAX_BATTLEACTIONSTACK; n++){
		data[n].Clear();
	}
}
