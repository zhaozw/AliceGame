// Scene_Battle_Command.cpp

#include "Scene_Battle.h"
#include "Game_BattleAction.h"

bool Scene_Battle::InterpretCommand(Game_UnitCommand* pCmd, int phaze){
	if(pCmd == NULL) return false;
	if(pCmd->IsEmpty()) return false;
	switch(phaze){
	case COMMANDPHAZE_NOPHAZE:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_ASSERT:
		return InterpretCommand_Assert(pCmd);
		break;
	case COMMANDPHAZE_PRE_ACTION:
		return InterpretCommand_Pre_Action(pCmd);
		break;
	case COMMANDPHAZE_ACTION:
		return InterpretCommand_Action(pCmd);
		break;
	case COMMANDPHAZE_POST_ACTION:
		return InterpretCommand_Post_Action(pCmd);
		break;
	}
	return false;
}


bool Scene_Battle::InterpretCommand_NoPhaze(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:

		break;
	case ACTIONTYPE_ERROR:
		return false;
		break;
	}
	return true;
}

bool Scene_Battle::InterpretCommand_Assert(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		action.Clear();
		action.SetActor(pCmd->GetOwner());
		action.SetOpponent(pCmd->GetTarget());
		action.SetType(Game_BattleAction::TYPE_ASSERTATTACK);
		actionStack.Push(action);
		break;
	case ACTIONTYPE_ERROR:
		return false;
		break;
	}
	return true;
}


bool Scene_Battle::InterpretCommand_Pre_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_ERROR:
		return false;
		break;
	}
	return true;
}

bool Scene_Battle::InterpretCommand_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	Game_BattleUnit*		pOwner = pCmd->GetOwner();
	Game_BattleUnit*		pTarget = pCmd->GetTarget();
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		// 通常攻撃
		action.Clear();
		action.SetActor(pOwner);
		action.SetOpponent(pTarget);
		action.SetType(Game_BattleAction::TYPE_DAMAGE);
		action.ClearFlag();
		action.SetParam(CalcDamage(pOwner, pTarget, CALCDAMAGE_ATTACK));
		actionStack.Push(action);
		break;
	case ACTIONTYPE_ERROR:
		return false;
		break;
	}
	return true;
}

bool Scene_Battle::InterpretCommand_Check_Death(Game_UnitCommand* pCmd){
	// 行動は何であれ、死亡したかどうかの判定を必ず行う
	Game_BattleAction action;
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		// dolls[n].CheckDie();
	}
	for(int n=0; n<MAX_BATTLEENEMY; n++){
	}
	return true;
}

bool Scene_Battle::InterpretCommand_Post_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_ERROR:
		return false;
		break;
	}
	return true;
}


