// Scene_Battle_Calc.cpp

#include "Scene_Battle.h"
#include <algorithm>
#include "Data_StateMessage.h"
#include "Static_Skill.h"

extern Data_StateMessage d_stateMessage;

bool Scene_Battle::SetCommand(Game_UnitCommand cmd){
	if(commandIndex >= MAX_UNITCOMMAND) return false;
	cmd.SetUsed();
	commands[commandIndex] = cmd;
	commandIndex++;
	return true;
}

bool Scene_Battle::RemoveOneCommand(){
	if(commandIndex <= 0) return false;
	commandIndex--;
	commands[commandIndex].Reset();
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

bool Scene_Battle::GetCommandWindowIsCancelable(int currentIndex){
	for(int n=0; n<=commandIndex-1; n++){
		if(GetDollPtr(GetFrontIndex(n))->CanAct()){
			return true;
		}
	}
	return false;
}

Game_UnitCommand Scene_Battle::GetEnemyCommand(Game_BattleEnemy* pEnemy){
	// 仮に通常攻撃だけをセットする。
	Game_UnitCommand cmd;
	int resultIndex = 0;

	// ランダムで行動を選ぶためのインデックスの配列
	int indexArray[MAX_ACTIONPATTERN*9];
	for(int n=0; n<MAX_ACTIONPATTERN*9; n++){
		indexArray[n] = -1;
	}
	int indexArrayLength = 0;

	int max_priority = GetEnemyCommandMaxPriority(pEnemy);
	if(max_priority == 0){
		// 取れるコマンドがない場合は様子を見続ける
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(NULL);
		cmd.SetActionType(ACTIONTYPE_SKILL);
		cmd.SetSkillID(SKILL_WAIT);
		cmd.SetTargetType(ACTIONTARGET_NONE);
	}else{
		for(int n=0; n<MAX_ACTIONPATTERN; n++){
			switch(max_priority - GetEnemyCommandPriority(pEnemy, n)){
			case 0: // 最も行いやすい行動
				for(int i=0; i<9; i++){
					indexArray[indexArrayLength] = n;
					indexArrayLength++;
				}
				break;
			case 1: // 次に行いやすい行動
				for(int i=0; i<3; i++){
					indexArray[indexArrayLength] = n;
					indexArrayLength++;
				}
				break;
			case 2: // レア行動
				indexArray[indexArrayLength] = n;
				indexArrayLength++;
				break;
			}
		}
		// 入力された値の中から一つ選び出す
		if(indexArrayLength != 0){
			resultIndex = indexArray[GetRand(indexArrayLength-1)];
			cmd = MakeEnemyCommand(pEnemy, resultIndex);
		}
	}
	return cmd;
}

int Scene_Battle::GetEnemyCommandPriority(Game_BattleEnemy* pEnemy, int index){
	ENEMYACTIONPATTERN*	pAction;
	pAction = pEnemy->GetActionPatternPtr(index);
	float rate;
	if(pAction == NULL) return 0;
	// ここで行動条件の判定を行う
	// 条件を満たしていないものがあれば0を返す
	for(int n=0; n<2; n++){
		switch(pAction->conditionType[n]){
		case CONDITIONTYPE_ALWAYS:
			break;
		case CONDITIONTYPE_MAX_HP_RATE:
			rate = (float)100.0f*pEnemy->GetHP()/pEnemy->GetMaxHP();
			if(rate > pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		case CONDITIONTYPE_MIN_HP_RATE:
			rate = (float)100.0f*pEnemy->GetHP()/pEnemy->GetMaxHP();
			if(rate < pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		}
	}
	// 優先度を返す。
	return pAction->priority;
}

int Scene_Battle::GetEnemyCommandMaxPriority(Game_BattleEnemy* pEnemy){
	int result = 0;
	for(int n=0; n<MAX_ACTIONPATTERN; n++){
		result = max(result, GetEnemyCommandPriority(pEnemy, n));
	}
	// 優先度を返す。
	return result;
}

Game_UnitCommand Scene_Battle::MakeEnemyCommand(Game_BattleEnemy* pEnemy, int index){
	ENEMYACTIONPATTERN* pAction = pEnemy->GetActionPatternPtr(index);
	Game_UnitCommand cmd;
	cmd.Reset();
	switch(pAction->actionType){
	case ACTIONTYPE_NONE:
		cmd.SetEmpty();
		break;
	case ACTIONTYPE_ATTACK:
		cmd.SetActionType(ACTIONTYPE_ATTACK);
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(GetRandomDollPtr());
		cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
		break;
	case ACTIONTYPE_SKILL:
		cmd.SetActionType(ACTIONTYPE_SKILL);
		cmd.SetSkillID(pAction->skillID);
		cmd.SetOwner(pEnemy);
		switch(pAction->targetType){
		case TARGETTYPE_NONE:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_NONE);
			break;
		case TARGETTYPE_DOLL_RANDOM:
			cmd.SetTarget(GetRandomDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case TARGETTYPE_DOLL_ALL:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_DOLL_ALL);
			break;
		case TARGETTYPE_ENEMY_RANDOM:
			cmd.SetTarget(GetRandomEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case TARGETTYPE_ENEMY_ALL:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ALL);
			break;
		case TARGETTYPE_SELF:
			cmd.SetTarget(pEnemy);
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case TARGETTYPE_DOLL_HP_MIN:
			// これ以降は正しく設定されていない
			cmd.SetTarget(GetRandomDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case TARGETTYPE_DOLL_HP_MIN2:
			cmd.SetTarget(GetRandomDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case TARGETTYPE_ENEMY_HP_MIN:
			cmd.SetTarget(GetRandomEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case TARGETTYPE_ENEMY_HP_MIN2:
			cmd.SetTarget(GetRandomEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
	}
		break;
	case ACTIONTYPE_GUARD:
		cmd.SetActionType(ACTIONTYPE_GUARD);
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(NULL);
		cmd.SetTargetType(ACTIONTARGET_NONE);
		break;
	}
	return cmd;
}

bool Scene_Battle::SortUnitCommands(){
	// ソートを行う
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
	Game_BattleUnit* pUnit, WORD stateRefID,
	bool showMessage, int level){
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
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(enemies[n].GetIsUsed()){
			enemies[n].UpdateStateTurn();
		}
	}
}