// Game_BattleUnit.cpp

#include "Game_BattleUnit.h"
#include "Static_AliceDoll.h"
#include "Data_BattleState.h"
#include <tchar.h>
#include <algorithm>

extern Data_BattleState		d_battleState;

// 処理の順番で並べ替え
bool Game_BattleState::SortByCalc(
	const Game_BattleState& aLeft, const Game_BattleState& aRight){
		Data_BattleState_Each* pState;
		WORD left=0, right=0;
		if(aRight.refID == 0){
			return true;
		}else if(aLeft.refID == 0){
			return false;
		}
		pState = d_battleState.GetBattleState(aRight.refID);
		if(pState == NULL){
			return true;
		}
		right = pState->GetCalcOrder();
		pState = d_battleState.GetBattleState(aLeft.refID);
		if(pState == NULL){
			return false;
		}
		left = pState->GetCalcOrder();
		return left > right;
}

bool Game_BattleState::SortByDraw(
	const Game_BattleState& aLeft, const Game_BattleState& aRight){
		Data_BattleState_Each* pState;
		WORD left=0, right=0;
		if(aRight.refID == 0){
			return true;
		}else if(aLeft.refID == 0){
			return false;
		}
		pState = d_battleState.GetBattleState(aRight.refID);
		if(pState == NULL){
			return true;
		}
		right = pState->GetDrawOrder();
		pState = d_battleState.GetBattleState(aLeft.refID);
		if(pState == NULL){
			return false;
		}
		left = pState->GetDrawOrder();
		return left > right;
}


Game_BattleUnit::Game_BattleUnit(){
	Reset();
}

void Game_BattleUnit::Reset(int n){
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _T(""));
	for(int index=0; index<BATTLEUNIT_PARAM_NUM; index++){
		param[index] = 0;
	}
	attr = DOLL_ATTR_NONE;
	isFront = true;
	position = n;

	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		stateArray[n].refID = 0;
	}
}

bool Game_BattleUnit::CanAct(){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(d_battleState.CheckFlagOfState(stateArray[n].refID, 
			STATE_FLAG_CANNOT_ACT)){
				// 一つでも、
				// 「このステートであれば攻撃対象にならない」ステートがあれば
				// 攻撃対象にならない。
				return false;
		}
	}
	return true;
}

bool Game_BattleUnit::CanTarget(){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(d_battleState.CheckFlagOfState(stateArray[n].refID, 
			STATE_FLAG_CANNOT_TARGET)){
				// 一つでも、
				// 「このステートであれば攻撃対象にならない」ステートがあれば
				// 攻撃対象にならない。
				return false;
		}
	}
	return true;
}

int Game_BattleUnit::GetRawParam(BYTE index){
	if(index >= BATTLEUNIT_PARAM_NUM){
		return BATTLEUNIT_PARAM_ERROR;
	}
	return param[index];
}

int Game_BattleUnit::GetCalcParam(BYTE index){
	if(index >= BATTLEUNIT_PARAM_NUM){
		return BATTLEUNIT_PARAM_ERROR;
	}
	return param[index];
}

int Game_BattleUnit::GetStateNum(){
	return 0;
}

// ステートを優先度順に並べ替える。
void Game_BattleUnit::SortStateByCalc(){
	std::sort(stateArray, stateArray+BATTLEUNIT_STATE_MAX,
		Game_BattleState::SortByCalc);
}

// ステートを描画順序順に並べ替える。
void Game_BattleUnit::SortStateByDraw(){
	std::sort(stateArray, stateArray+BATTLEUNIT_STATE_MAX,
		Game_BattleState::SortByDraw);
}

// 参照番号のステートを追加する。
BYTE Game_BattleUnit::AddState(WORD refID){
	int n=-1;
	n = CheckIsState(refID);
	if(n == -1){
		n = GetStateNum();
		stateArray[n].refID = refID;
		stateArray[n].turn = 0;
		stateArray[n].level = 1;
		SortStateByCalc();
		return ADDSTATE_SUCCEED;
	}else{
		// 重ねがけ可能かどうか
		if(d_battleState.CheckFlagOfState(refID, STATE_FLAG_CAN_MULTIPLE)){
			stateArray[n].level++;
			return ADDSTATE_MULTIPLIED;
		}else{
			// 既にそのステートになっている
			return ADDSTATE_ALREADY_ADDED;
		}
	}
}
	
// 参照番号のステートに罹患している場合、それを解除する。
void Game_BattleUnit::RemoveState(WORD refID, bool sort){
	int n=-1;
	n = CheckIsState(refID);
	if(n != -1){
		stateArray[n].refID = 0;
		stateArray[n].turn = 0;
		stateArray[n].level = 0;
	}
}

void Game_BattleUnit::UpdateStateTurn(){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		// ターン終了後に解除するかどうかの判定
		if((d_battleState.GetBattleState(stateArray[n].refID)->GetFlags()
			& STATE_FLAG_REMOVE_AT_TURNEND) != 0){
				RemoveState(stateArray[n].refID, false);
		}
		// ターン数を増加させる
		if(stateArray[n].refID != 0){
			stateArray[n].turn++;
		}
	}
}

int Game_BattleUnit::CheckIsState(WORD stateRefID){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(stateArray[n].refID == stateRefID){
			return n;
		}
	}
	return -1;
}

bool Game_BattleUnit::SetName(LPTSTR _name, int nameLength){
	// if(nameLength == -1) nameLength = strlen(name);
	// if(nameLength > BATTLEUNIT_NAME_BYTES-1) return false;
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _name);
	return true;
}

void Game_BattleUnit::GetName(LPTSTR buf, int bufSize){
	if(bufSize < BATTLEUNIT_NAME_BYTES) return;
	strcpy_s(buf, BATTLEUNIT_NAME_BYTES-1, name);
}

void Game_BattleUnit::SetParam(
	int hp, int maxHP, int atk, int def, int spd, int mgc, int tec){
		SetHP(hp);
		SetMaxHP(maxHP);
		SetAtk(atk);
		SetDef(def);
		SetSpd(spd);
		SetMgc(mgc);
		SetTec(tec);
}

bool Game_BattleUnit::Damage(int d){
	param[BATTLEUNIT_PARAM_HP] -= d;
	if(param[BATTLEUNIT_PARAM_HP] <= 0){
		param[BATTLEUNIT_PARAM_HP] = 0;
		return false;
	}
	return true;
}