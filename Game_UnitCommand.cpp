// Game_UnitCommand.cpp

#include "Game_UnitCommand.h"
#include <Windows.h>

// �R���X�g���N�^
Game_UnitCommand::Game_UnitCommand() : 
pOwner(NULL), pTarget(NULL), actionType(ACTIONTYPE_NONE), targetType(ACTIONTARGET_NONE){

}

void Game_UnitCommand::Reset(){
	pOwner = NULL;
	pTarget = NULL;
	actionType = ACTIONTYPE_NONE;
	targetType = ACTIONTARGET_NONE;
}