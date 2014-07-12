// Game_UnitCommand.cpp

#include "Game_UnitCommand.h"
#include <Windows.h>

// コンストラクタ
Game_UnitCommand::Game_UnitCommand() : 
pOwner(NULL), pTarget(NULL), actionType(ACTIONTYPE_NONE), targetType(ACTIONTARGET_NONE),
isUsed(false){

}

bool Game_UnitCommand::SortBySpd(
	const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
	// 空の要素は後ろに押しやる
	if(aLeft.IsEmpty()){
		return false;
	}else if(aRight.IsEmpty()){
		return true;
	}
	// ここまでで、どちらかの行動が空の場合はfalseかtrueを返した
	// 後は素早さ同士を比較
	int a = aLeft.pOwner->GetSpd();
	int b = aRight.pOwner->GetSpd();
	return  a>b;
};

void Game_UnitCommand::Reset(){
	pOwner = NULL;
	pTarget = NULL;
	actionType = ACTIONTYPE_NONE;
	targetType = ACTIONTARGET_NONE;
	isUsed = false;
}