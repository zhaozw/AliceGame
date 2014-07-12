// Game_UnitCommand.cpp

#include "Game_UnitCommand.h"
#include <Windows.h>

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Game_UnitCommand::Game_UnitCommand() : 
pOwner(NULL), pTarget(NULL), actionType(ACTIONTYPE_NONE), targetType(ACTIONTARGET_NONE),
isUsed(false){

}

bool Game_UnitCommand::SortBySpd(
	const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
	// ‹ó‚Ì—v‘f‚ÍŒã‚ë‚É‰Ÿ‚µ‚â‚é
	if(aLeft.IsEmpty()){
		return false;
	}else if(aRight.IsEmpty()){
		return true;
	}
	// ‚±‚±‚Ü‚Å‚ÅA‚Ç‚¿‚ç‚©‚Ìs“®‚ª‹ó‚Ìê‡‚Ífalse‚©true‚ð•Ô‚µ‚½
	// Œã‚Í‘f‘‚³“¯Žm‚ð”äŠr
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