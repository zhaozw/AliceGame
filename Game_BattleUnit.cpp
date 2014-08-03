// Game_BattleUnit.cpp

#include "Game_BattleUnit.h"
#include "Static_AliceDoll.h"
#include "Data_BattleState.h"
#include <tchar.h>
#include <algorithm>
#include <DxLib.h>

extern Data_BattleState		d_battleState;

// �����̏��Ԃŕ��בւ�
bool Game_BattleState::SortByCalc(
	const Game_BattleState& aLeft, const Game_BattleState& aRight){
		Data_BattleState_Each* pState;
		WORD left=0, right=0;
		if(aLeft.refID == 0){
			return false;
		}else if(aRight.refID == 0){
			return true;
		}
		/*
		// ���l�̏ꍇ��false��Ԃ��Ȃ���΂Ȃ炸�A
		// ���̏ꍇ�̓G���[����������
		if(aRight.refID == 0){
			return true;
		}else if(aLeft.refID == 0){
			return false;
		}
		*/
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
		return (left > right);
}

bool Game_BattleState::SortByDraw(
	const Game_BattleState& aLeft, const Game_BattleState& aRight){
		Data_BattleState_Each* pState;
		WORD left=0, right=0;
		if(aLeft.refID == 0){
			return false;
		}else if(aRight.refID == 0){
			return true;
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
		return (left > right);
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
	isUsed = false;

	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		stateArray[n].refID = 0;
	}
}

bool Game_BattleUnit::CanAct(){
	if(!isUsed) return false;
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(d_battleState.CheckFlagOfState(stateArray[n].refID, 
			STATE_FLAG_CANNOT_ACT)){
				// ��ł��A
				// �u���̃X�e�[�g�ł���΍U���ΏۂɂȂ�Ȃ��v�X�e�[�g�������
				// �U���ΏۂɂȂ�Ȃ��B
				return false;
		}
	}
	return true;
}

bool Game_BattleUnit::CanTarget(){
	if(!isUsed) return false;
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(d_battleState.CheckFlagOfState(stateArray[n].refID, 
			STATE_FLAG_CANNOT_TARGET)){
				// ��ł��A
				// �u���̃X�e�[�g�ł���΍U���ΏۂɂȂ�Ȃ��v�X�e�[�g�������
				// �U���ΏۂɂȂ�Ȃ��B
				return false;
		}
	}
	return true;
}

bool Game_BattleUnit::IsDead(){
	if(!isUsed) return false;
	return (CheckIsState(STATE_DEATH) != -1);
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
	// �L���ȃX�e�[�g�̐���Ԃ��B
	SortStateByCalc();
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(stateArray[n].refID == 0){
			return n;
		}
	}
	return BATTLEUNIT_STATE_MAX;
}

// �X�e�[�g��D��x���ɕ��בւ���B
void Game_BattleUnit::SortStateByCalc(){
	std::sort(stateArray, stateArray+BATTLEUNIT_STATE_MAX,
		Game_BattleState::SortByCalc);
}

// �X�e�[�g��`�揇�����ɕ��בւ���B
void Game_BattleUnit::SortStateByDraw(){
	std::sort(stateArray, stateArray+BATTLEUNIT_STATE_MAX,
		Game_BattleState::SortByDraw);
}

// �Q�Ɣԍ��̃X�e�[�g��ǉ�����B
BYTE Game_BattleUnit::AddState(WORD refID, int param, int param2){
	int n=-1;
	n = CheckIsState(refID);
	if(n == -1){
		n = GetStateNum();
		stateArray[n].refID = refID;
		stateArray[n].turn = 0;
		stateArray[n].param = param;
		stateArray[n].param2 = param2;
		AutoRemoveState(refID);
		SortStateByCalc();
		return ADDSTATE_SUCCEED;
	}else{
		// �d�˂����\���ǂ���
		// �����̂�����L�q���K���B��ŏC������B
		if(d_battleState.CheckFlagOfState(refID, STATE_FLAG_CAN_MULTIPLE)){
			stateArray[n].param += param;
			stateArray[n],param2 += param2;
			return ADDSTATE_MULTIPLIED;
		}else{
			// ���ɂ��̃X�e�[�g�ɂȂ��Ă���
			return ADDSTATE_ALREADY_ADDED;
		}
	}
}
	
void Game_BattleUnit::AutoRemoveState(WORD refID){
	// �����邱�Ƃɐ��������ꍇ�A�����ŊO���X�e�[�g�𔻒肷��
	switch(refID){
	case STATE_DEATH:
		RemoveState(STATE_TMPATTR_NONE, false);
		RemoveState(STATE_TMPATTR_SUN, false);
		RemoveState(STATE_TMPATTR_MOON, false);
		RemoveState(STATE_TMPATTR_STAR, false);
		break;
	case STATE_TMPATTR_NONE:
		RemoveState(STATE_TMPATTR_SUN, false);
		RemoveState(STATE_TMPATTR_MOON, false);
		RemoveState(STATE_TMPATTR_STAR, false);
		break;
	case STATE_TMPATTR_SUN:
		RemoveState(STATE_TMPATTR_NONE, false);
		RemoveState(STATE_TMPATTR_MOON, false);
		RemoveState(STATE_TMPATTR_STAR, false);
		break;
	case STATE_TMPATTR_MOON:
		RemoveState(STATE_TMPATTR_NONE, false);
		RemoveState(STATE_TMPATTR_SUN, false);
		RemoveState(STATE_TMPATTR_STAR, false);
		break;
	case STATE_TMPATTR_STAR:
		RemoveState(STATE_TMPATTR_NONE, false);
		RemoveState(STATE_TMPATTR_SUN, false);
		RemoveState(STATE_TMPATTR_MOON, false);
		break;
	}
}


// �Q�Ɣԍ��̃X�e�[�g�ɜ늳���Ă���ꍇ�A�������������B
void Game_BattleUnit::RemoveState(WORD refID, bool sort){
	int n=-1;
	n = CheckIsState(refID);
	if(n != -1){
		stateArray[n].refID = 0;
		stateArray[n].turn = 0;
		stateArray[n].param = 0;
		stateArray[n].param2 = 0;
	}
	if(sort){
		SortStateByCalc();
	}
}

WORD Game_BattleUnit::CheckStateTurn(){
	Data_BattleState_Each *pState = NULL;
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(stateArray[n].refID != 0){
			// �^�[���I����ɉ������邩�ǂ����̔���
			pState = d_battleState.GetBattleState(stateArray[n].refID);
			if(pState != NULL){
				if((pState->GetFlags()
					& STATE_FLAG_REMOVE_AT_TURNEND) != 0){
						// RemoveState(stateArray[n].refID, false);
						// �^�[���I����̎��������̓��b�Z�[�W��\�������A
						// �����ŉ������s��
						// �����Ƃɂ��悤�Ǝv�������ǁA����ς蕶�͂��o���B
						return stateArray[n].refID;
				}
			}
			// �^�[�����ŉ��������X�e�[�g�̉���
			switch(stateArray[n].refID){
			case STATE_TMPATTR_NONE:
			case STATE_TMPATTR_SUN:
			case STATE_TMPATTR_MOON:
			case STATE_TMPATTR_STAR:
				if(stateArray[n].turn >= stateArray[n].param){
					// �߂��Ŏ��ۂ̃X�e�[�g�������s����
					// RemoveState(stateArray[n].refID, false);
					return stateArray[n].refID;
				}
				break;
			}
		}
	}
	return 0;
}

void Game_BattleUnit::UpdateStateTurn(){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
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

int Game_BattleUnit::GetStateParam(WORD stateRefID){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(stateArray[n].refID == stateRefID){
			return stateArray[n].param;
		}
	}
	return -1;
}

int Game_BattleUnit::GetStateParam2(WORD stateRefID){
	for(int n=0; n<BATTLEUNIT_STATE_MAX; n++){
		if(stateArray[n].refID == stateRefID){
			return stateArray[n].param2;
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

BYTE Game_BattleUnit::GetAmendedAttr(){
	BYTE tmpAttr = GetAttr();
	if(IsState(STATE_TMPATTR_NONE)){
		tmpAttr = DOLL_ATTR_NONE;
	}
	if(IsState(STATE_TMPATTR_SUN)){
		tmpAttr = DOLL_ATTR_SUN;
	}
	if(IsState(STATE_TMPATTR_MOON)){
		tmpAttr = DOLL_ATTR_MOON;
	}
	if(IsState(STATE_TMPATTR_STAR)){
		tmpAttr = DOLL_ATTR_STAR;
	}
	return tmpAttr;
}

void Game_BattleUnit::SetRandomAttr(){
	attr = (BYTE)GetRand(DOLL_ATTR_NUM-1);
}

bool Game_BattleUnit::Damage(int d){
	param[BATTLEUNIT_PARAM_HP] -= d;
	if(param[BATTLEUNIT_PARAM_HP] <= 0){
		param[BATTLEUNIT_PARAM_HP] = 0;
		return false;
	}
	return true;
}

void Game_BattleUnit::Heal(int v){
	param[BATTLEUNIT_PARAM_HP] += v;
	if(param[BATTLEUNIT_PARAM_HP] >= param[BATTLEUNIT_PARAM_MAXHP]){
		param[BATTLEUNIT_PARAM_HP] = param[BATTLEUNIT_PARAM_MAXHP];
	}
}


bool Game_BattleUnit::CheckDie(){
	// ���ɐ퓬�s�\���ۂ�
	if(CheckIsState(STATE_DEATH) != -1) return false;
	// HP��0�ȉ��̎��͐퓬�s�\��K�p
	if(param[BATTLEUNIT_PARAM_HP] <= 0){
		return true;
	}
	return false;
}

int Game_BattleUnit::GetAmendedSpd(){
	int amended = 5000 + GetSpd();
	int tmp=0;
	tmp = GetStateParam(STATE_SUBSPD_UP);
	if(tmp != -1){
		amended += tmp*1000;
	}
	tmp = GetStateParam(STATE_SUBSPD_DOWN);
	if(tmp != -1){
		amended -= tmp*1000;
	}
	return amended;
}