// Scene_Battle_Calc.cpp

#include "Scene_Battle.h"
#include <algorithm>
#include "Data_StateMessage.h"

extern Data_StateMessage d_stateMessage;

bool Scene_Battle::SetCommand(Game_UnitCommand cmd){
	if(commandIndex >= MAX_UNITCOMMAND) return false;
	cmd.SetUsed();
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

int Scene_Battle::CalcDamage(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent,
	int param){
		int from = 0;		// 攻撃側のパラメータ
		int to = 0;			// 受け手側のパラメータ
		float rate = 1.0;	// 倍率
		float fix = 0.0;	// 定数
		float gRate = 1.0;	// 定数も含めた倍率
		int damage;			// 計算結果
		bool canMinus = false;	// 負数を認めるか否か
		switch(param){
		case CALCDAMAGE_ATTACK:
			from	= pAttacker->GetAtk();
			to		= pOpponent->GetDef();
			rate	= GetAttrRate(pAttacker->GetAttr(), pOpponent->GetAttr());
			break;
		}
		// 自分のステートによるダメージの補正
		if(pOpponent->IsState(STATE_GUARD)){
			// 防御
			rate *= 0.5;
		}

		damage = (int)(gRate*(rate*(from-to)+fix));
		if(canMinus){
			return min(DAMAGE_MAX, damage);
		}else{
			return min(DAMAGE_MAX, max(0, damage));
		}
}

BYTE Scene_Battle::GetAttrAffinity(BYTE attackerAttr, BYTE opponentAttr){
	switch(attackerAttr){
	case DOLL_ATTR_SUN:
		switch(opponentAttr){
		case DOLL_ATTR_MOON:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_STAR:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	case DOLL_ATTR_MOON:
		switch(opponentAttr){
		case DOLL_ATTR_STAR:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_SUN:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	case DOLL_ATTR_STAR:
		switch(opponentAttr){
		case DOLL_ATTR_SUN:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_MOON:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	}
	return ATTRAFFINITY_EVEN;
}

float Scene_Battle::GetAttrRate(BYTE attackerAttr, BYTE opponentAttr){
	switch(GetAttrAffinity(attackerAttr, opponentAttr)){
	case ATTRAFFINITY_EVEN:
		return 1.0;
		break;
	case ATTRAFFINITY_STRONG:
		return ATTRRATE_STRONG;
		break;
	case ATTRAFFINITY_WEAK:
		return ATTRRATE_WEAK;
		break;
	}
	return 1.0;
}

BYTE Scene_Battle::AddStateToUnit(
	Game_BattleUnit* pUnit, WORD stateRefID, bool showMessage){
		TCHAR buf[WND_MSG_STOCKLENGTH];
		BYTE result;
		if(pUnit == NULL){
			return ADDSTATE_ERROR;
		}
		// ステートの適用
		result = pUnit->AddState(stateRefID);
		// メッセージの追加
		if(showMessage){
			switch(result){
			case ADDSTATE_SUCCEED:
			case ADDSTATE_MULTIPLIED:
				// ステートになったときのメッセージを取得
				d_stateMessage.GetStateMessage(
					buf, stateRefID,
					STATEMESSAGE_INDEX_DOLL_ADDED, pUnit);
				// メッセージに追加
				AddStockMessage(buf);
				break;
			}
		}
		return result;
}

void Scene_Battle::UpdateStateTurn(){
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		if(dolls[n].GetIsUsed()){
			dolls[n].UpdateStateTurn();
		}
	}
}