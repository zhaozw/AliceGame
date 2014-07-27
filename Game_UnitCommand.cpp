// Game_UnitCommand.cpp

#include "Game_UnitCommand.h"
#include <Windows.h>

// �R���X�g���N�^
Game_UnitCommand::Game_UnitCommand() : 
pOwner(NULL), pTarget(NULL), actionType(ACTIONTYPE_NONE), targetType(ACTIONTARGET_NONE),
isUsed(false){
	Reset();
}

bool Game_UnitCommand::SortBySpd(
	const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
	// ��̗v�f�͌��ɉ������
	if(aLeft.IsEmpty()){
		return false;
	}else if(aRight.IsEmpty()){
		return true;
	}
	// �����܂łŁA�ǂ��炩�̍s������̏ꍇ��false��true��Ԃ���
	// ��͑f�������m���r
	int a = aLeft.pOwner->GetAmendedSpd();
	int b = aRight.pOwner->GetAmendedSpd();
	return  a>b;
};

void Game_UnitCommand::Reset(){
	pOwner = NULL;
	pTarget = NULL;
	actionType = ACTIONTYPE_NONE;
	targetType = ACTIONTARGET_NONE;
	isUsed = false;
	skillID = -1;
}

void Game_UnitCommand::SetEmpty(){
	// pOwner��isUsed�͎c���Ă���
	pTarget = NULL;
	actionType = ACTIONTYPE_NONE;
	targetType = ACTIONTARGET_NONE;
}