// Data_SkillText.cpp

#include "Data_SkillInfo.h"
#include "Static_BattleUnit.h"

void Data_SkillMessage_Each::SetSkillMessage(BYTE _type, LPTSTR str, int strLen){
	int length = 0;
	if(strLen == -1){
		length = strlen(str);
	}else{
		length = strLen;
	}
	if(length > SKILLMESSAGE_BYTES) return;
	type = _type;
	// 文字列のコピー
	strcpy_s(message, SKILLMESSAGE_BYTES-1, str);
}

bool Data_SkillMessage_Each::GetSkillMessage(LPTSTR buf, Game_BattleUnit* pUnit){
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// 名前の取得
	if(pUnit != NULL){
		pUnit->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	}else{
		strcpy_s(nameBuf, BATTLEUNIT_NAME_BYTES-1, _T(""));
	}
	switch(type){
	case SKILLMESSAGE_TYPE_NONE:
		return false;
		break;
	case SKILLMESSAGE_TYPE_CONST:
		strcpy_s(buf, SKILLMESSAGE_BYTES-1, message);
		return true;
		break;
	case SKILLMESSAGE_TYPE_UNIT:
		wsprintf(buf, message, nameBuf);
		return true;
	}
	return true;
}

Data_SkillInfo::Data_SkillInfo() : assertMessages(), subMessages(){
	for(int n=0; n<MAX_SKILL; n++){
		strcpy_s(skillName[n], MAX_SKILL_BYTES-1, _T(""));
		strcpy_s(account[n], SKILLACC_BYTES-1, _T(""));
		targetType[n] = ACTIONTARGET_NONE;
	}
}

bool Data_SkillInfo::Load(){
	return SetSkillData();
}

bool Data_SkillInfo::SetSkillData(){
	// ようすを見ている
	strcpy_s(skillName[SKILL_WAIT], MAX_SKILL_BYTES-1, _T("様子を見る"));
	targetType[SKILL_WAIT] = ACTIONTARGET_NONE;
	assertMessages[SKILL_WAIT].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%sは様子を見ている！"));
	strcpy_s(account[SKILL_WAIT], SKILLACC_BYTES-1, _T("何もしません。"));

	// 全体攻撃
	strcpy_s(skillName[SKILL_ALLRANGE], MAX_SKILL_BYTES-1, _T("全体攻撃"));
	targetType[SKILL_ALLRANGE] = ACTIONTARGET_OPPONENT_ALL;
	assertMessages[SKILL_ALLRANGE].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%sの攻撃！"));
	strcpy_s(account[SKILL_ALLRANGE], SKILLACC_BYTES-1, _T("敵全体に攻撃します。"));

	// 先制攻撃
	strcpy_s(skillName[SKILL_LOADOFF_ATTACK], MAX_SKILL_BYTES-1, _T("先制攻撃"));
	targetType[SKILL_LOADOFF_ATTACK] = ACTIONTARGET_OPPONENT_ONE;
	assertMessages[SKILL_LOADOFF_ATTACK].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%sは風のように素早く攻撃した！"));
	strcpy_s(account[SKILL_LOADOFF_ATTACK], SKILLACC_BYTES-1,
		_T("誰よりも速く風のように素早く攻撃します。"));

	// 回復
	strcpy_s(skillName[SKILL_HEAL1], MAX_SKILL_BYTES-1, _T("回復"));
	targetType[SKILL_HEAL1] = ACTIONTARGET_TEAM_ONE;
	assertMessages[SKILL_HEAL1].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%sは回復の術式を使った！"));
	strcpy_s(account[SKILL_HEAL1], SKILLACC_BYTES-1,
		_T("味方一体の体力を５０％回復します。"));

	return true;
}

bool Data_SkillInfo::GetSkillName(LPTSTR buf, WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	strcpy_s(buf, MAX_SKILL_BYTES-1, skillName[skillID]);
	return true;
}

bool Data_SkillInfo::GetSkillAccount(LPTSTR buf, WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	strcpy_s(buf, SKILLACC_BYTES-1, account[skillID]);
	return true;
}


BYTE Data_SkillInfo::GetTargetType(WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return ACTIONTARGET_NONE;
	return targetType[skillID];
}


bool Data_SkillInfo::GetAssertMessage(LPTSTR buf, WORD skillID, Game_BattleUnit* pUnit){
	bool result = true;
	result = assertMessages[skillID].GetSkillMessage(buf, pUnit);
	return result;
}

bool Data_SkillInfo::GetSubMessage(LPTSTR buf, WORD refID, Game_BattleUnit* pUnit){
	bool result = true;
	result = subMessages[refID].GetSkillMessage(buf, pUnit);
	return result;
}
