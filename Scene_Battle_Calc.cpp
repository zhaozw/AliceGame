// Scene_Battle_Calc.cpp

#include "Scene_Battle.h"
#include <algorithm>

bool Scene_Battle::SetCommand(Game_UnitCommand cmd){
	if(commandIndex >= MAX_UNITCOMMAND) return false;
	commands[commandIndex] = cmd;
	commandIndex++;
	return true;
}

bool Scene_Battle::SetEnemyCommands(){
	// 敵それぞれについてコマンドをセットする。

	// 敵のポインタ
	Game_BattleEnemy*	pEnemy = NULL;
	// 追加するコマンド
	Game_UnitCommand	cmd;

	for(int n=0; n<enemiesNum; n++){
		pEnemy = GetEnemyPtr(n);
		if(pEnemy != NULL){
			cmd = GetEnemyCommand(pEnemy);
			SetCommand(cmd);
		}
	}
	return true;
}


Game_UnitCommand Scene_Battle::GetEnemyCommand(Game_BattleEnemy* pEnemy){
	// 仮に通常攻撃だけをセットする。
	Game_UnitCommand cmd;
	// ターゲット
	Game_BattleDoll* pTarget;
	// 通常攻撃
	cmd.SetOwner(pEnemy);
	cmd.SetTarget(GetRandomDollPtr());
	cmd.SetActionType(ACTIONTYPE_ATTACK);
	cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
	return cmd;
}

bool Scene_Battle::SortUnitCommands(){
	std::sort(commands, commands+MAX_UNITCOMMAND, Game_UnitCommand::SortBySpd);
	return true;
}

void Scene_Battle::ClearCommands(){
	for(int n=0; n<MAX_UNITCOMMAND; n++){
		commands[n].Reset();
	}
	commandIndex = 0;
}