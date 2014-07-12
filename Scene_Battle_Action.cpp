// Scene_Battle_Action.cpp

#include "Scene_Battle.h"
#include <string.h>

bool Scene_Battle::InterpretAction(Game_BattleAction* pAction){
	if(pAction == NULL){ // アクションが不適切な場合
		return false;
	}
	switch(pAction->GetType()){
	case Game_BattleAction::TYPE_CALLENEMYNAME:
		Action_CallEnemyName();
		break;
	case Game_BattleAction::TYPE_NONE:
	case Game_BattleAction::TYPE_UNDIFINED:
	default:
		// タイプが適切でない場合
		return false;
		break;
	}
	return true;

}

bool Scene_Battle::InterpretCommand(Game_UnitCommand* pCmd, int phaze){
	switch(phaze){
	case COMMANDPHAZE_NOPHAZE:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_PRE_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_POST_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	}
	return false;
}

bool Scene_Battle::InterpretCommand_NoPhaze(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Pre_Action(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Action(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Post_Action(Game_UnitCommand* pCmd){
	return true;
}


bool Scene_Battle::Action_CallEnemyName(){
	// それぞれの敵についてメッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	for(int n=0; n<enemiesNum; n++){
		// 名前を取得する
		enemies[n].GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
		// 名前の体裁を整える
		strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
		strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("が現れた！"));
		w_battleMsg.AddStockMsg(buf, strlen(buf));
		// w_battleMsg.SetText
	}

	return true;
}