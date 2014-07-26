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
	// •¶Žš—ñ‚ÌƒRƒs[
	strcpy_s(message, SKILLMESSAGE_BYTES-1, str);
}

bool Data_SkillMessage_Each::GetSkillMessage(LPTSTR buf, Game_BattleUnit* pUnit){
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// –¼‘O‚ÌŽæ“¾
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
		targetType[n] = ACTIONTARGET_NONE;
	}
}

bool Data_SkillInfo::Load(){
	return SetSkillData();
}

bool Data_SkillInfo::SetSkillData(){
	// ‚æ‚¤‚·‚ðŒ©‚Ä‚¢‚é
	strcpy_s(skillName[SKILL_WAIT], MAX_SKILL_BYTES-1, _T("—lŽq‚ðŒ©‚é"));
	targetType[SKILL_WAIT] = ACTIONTARGET_NONE;
	assertMessages[SKILL_WAIT].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%s‚Í—lŽq‚ðŒ©‚Ä‚¢‚éI"));

	// ‘S‘ÌUŒ‚
	strcpy_s(skillName[SKILL_ALLRANGE], MAX_SKILL_BYTES-1, _T("‘S‘ÌUŒ‚"));
	targetType[SKILL_ALLRANGE] = ACTIONTARGET_OPPONENT_ALL;
	assertMessages[SKILL_ALLRANGE].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%s‚ÌUŒ‚I"));

	// æ§UŒ‚
	strcpy_s(skillName[SKILL_LOADOFF_ATTACK], MAX_SKILL_BYTES-1, _T("æ§UŒ‚"));
	targetType[SKILL_LOADOFF_ATTACK] = ACTIONTARGET_OPPONENT_ONE;
	assertMessages[SKILL_LOADOFF_ATTACK].SetSkillMessage(
		SKILLMESSAGE_TYPE_UNIT, _T("%s‚Í•—‚Ì‚æ‚¤‚É‘f‘‚­UŒ‚‚µ‚½I"));

	return true;
}

bool Data_SkillInfo::GetSkillName(LPTSTR buf, WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	strcpy_s(buf, MAX_SKILL_BYTES-1, skillName[skillID]);
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
