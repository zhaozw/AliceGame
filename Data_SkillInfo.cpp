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

Data_SkillInfo_Each::Data_SkillInfo_Each() : assertMessage(){
	strcpy_s(skillName, MAX_SKILL_BYTES-1, _T(""));
	strcpy_s(account, SKILLACC_BYTES-1, _T(""));
	costMP =0;
	targetType = ACTIONTARGET_NONE;
}

void Data_SkillInfo_Each::SetData(
	LPTSTR _skillName,
	LPTSTR _account,
	LPTSTR _assertMsg, BYTE _assertMsgType,
	int _costMP, BYTE _targetType){
		strcpy_s(skillName, MAX_SKILL_BYTES-1, _skillName);
		strcpy_s(account, SKILLACC_BYTES-1, _account);
		assertMessage.SetSkillMessage(_assertMsgType, _assertMsg);
		costMP = _costMP;
		targetType = _targetType;
}

void Data_SkillInfo_Each::GetSkillName(LPTSTR buf){
	strcpy_s(buf, MAX_SKILL_BYTES-1, skillName);
}

void Data_SkillInfo_Each::GetSkillAccount(LPTSTR buf){
	strcpy_s(buf, SKILLACC_BYTES-1, account);
}

Data_SkillInfo::Data_SkillInfo() : data(), subMessages(){
}

bool Data_SkillInfo::Load(){
	return SetSkillData();
}

bool Data_SkillInfo::SetSkillData(){
	// ‚æ‚¤‚·‚ðŒ©‚Ä‚¢‚é
	data[SKILL_WAIT].SetData(
		_T("—lŽq‚ðŒ©‚é"),
		_T("‰½‚à‚µ‚Ü‚¹‚ñB"),
		_T("%s‚Í—lŽq‚ðŒ©‚Ä‚¢‚éI"), SKILLMESSAGE_TYPE_UNIT,
		0, ACTIONTARGET_NONE);

	// ‘S‘ÌUŒ‚
	data[SKILL_ALLRANGE].SetData(
		_T("‘S‘ÌUŒ‚"),
		_T("“G‘S‘Ì‚ÉUŒ‚‚µ‚Ü‚·B"),
		_T("%s‚ÌUŒ‚I"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ALL);

	// æ§UŒ‚
	data[SKILL_LOADOFF_ATTACK].SetData(
		_T("æ§UŒ‚"),
		_T("’N‚æ‚è‚à‘¬‚­•—‚Ì‚æ‚¤‚É‘f‘‚­UŒ‚‚µ‚Ü‚·B"),
		_T("%s‚Í•—‚Ì‚æ‚¤‚É‘f‘‚­UŒ‚‚µ‚½I"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ONE);

	// ‰ñ•œ
	data[SKILL_HEAL1].SetData(
		_T("‰ñ•œ"),
		_T("–¡•ûˆê‘Ì‚Ì‘Ì—Í‚ð‚T‚O“‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚Í‰ñ•œ‚ÌpŽ®‚ðŽg‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_TEAM_ONE);

	return true;
}

bool Data_SkillInfo::GetSkillName(LPTSTR buf, WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	data[skillID].GetSkillName(buf);
	return true;
}

bool Data_SkillInfo::GetSkillAccount(LPTSTR buf, WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	data[skillID].GetSkillAccount(buf);
	return true;
}

bool Data_SkillInfo::GetAssertMessage(LPTSTR buf, WORD skillID, Game_BattleUnit* pUnit){
	if(skillID == 0 || skillID >= MAX_SKILL) return false;
	data[skillID].GetAssertMessage(buf, pUnit);
	return true;
}

BYTE Data_SkillInfo::GetTargetType(WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return ACTIONTARGET_NONE;
	return data[skillID].GetTargetType();
}

int Data_SkillInfo::GetCostMP(WORD skillID){
	if(skillID == 0 || skillID >= MAX_SKILL) return 0;
	return data[skillID].GetCostMP();
}



bool Data_SkillInfo::GetSubMessage(LPTSTR buf, WORD refID, Game_BattleUnit* pUnit){
	if(refID == 0 || refID >= MAX_SKILL_SUBMESSAGE) return false;
	bool result = true;
	result = subMessages[refID].GetSkillMessage(buf, pUnit);
	return result;
}
