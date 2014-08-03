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

	// ‚Î‚ç‚Ü‚«’e
	data[SKILL_WIDESHOT].SetData(
		_T("‚Î‚ç‚Ü‚«’e"),
		_T("“G‘S‘Ì‚ÉŒü‚©‚Á‚Ä’e–‹‚ð•ú‚¿‚Ü‚·B"),
		_T("%s‚Í‚Î‚ç‚Ü‚«’e‚ð•ú‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		4, ACTIONTARGET_OPPONENT_ALL);

	// ƒNƒiƒC’e
	data[SKILL_KUNAISHOT].SetData(
		_T("ƒNƒiƒC’e"),
		_T("‘ŠŽè‚Ì‹ZI‚ª’á‚¢‚Ù‚ÇˆÐ—Í‚ªã‚ª‚è‚Ü‚·B"),
		_T("%s‚ÍƒNƒiƒC’e‚ð•ú‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ONE);

	// ƒiƒCƒt’e
	data[SKILL_KNIFESHOT].SetData(
		_T("ƒiƒCƒt’e"),
		_T("‘ŠŽè‚Ì–hŒä—Í‚ð–³Ž‹‚µ‚Äƒ_ƒ[ƒW‚ð—^‚¦‚Ü‚·B"),
		_T("%s‚ÍƒiƒCƒt’e‚ð•ú‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);

	// —ìŒ‚
	data[SKILL_REIGEKI].SetData(
		_T("—ìŒ‚"),
		_T("‘®«‚Ì‰e‹¿‚ðŽó‚¯‚È‚¢UŒ‚‚ð•ú‚¿‚Ü‚·B"),
		_T("%s‚Í—ìŒ‚‚ð•ú‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);
	
	// Œõ’e
	data[SKILL_PHOTONSHOT].SetData(
		_T("Œõ’e"),
		_T("ˆÐ—Í‚ª–‚—Í‚ÉˆË‘¶‚·‚é’e‚ð•ú‚¿‚Ü‚·B"),
		_T("%s‚ÍŒõ’e‚ð•ú‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);

	// C•œ
	data[SKILL_REPAIR].SetData(
		_T("C•œ"),
		_T("–¡•ûˆê‘Ì‚Ì‚g‚o‚ð‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚ÌC•œI"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_TEAM_ONE);

	// ‘S‘ÌC•œ
	data[SKILL_REPAIR_ALL].SetData(
		_T("‘S‘ÌC•œ"),
		_T("‘O—ñ‚Ì–¡•û‘S‘Ì‚Ì‚g‚o‚ð‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚Ì‘S‘ÌC•œI"), SKILLMESSAGE_TYPE_UNIT,
		5, ACTIONTARGET_TEAM_ALL);

	// ƒ~ƒ‡ƒ‹ƒjƒ‹
	data[SKILL_MJOLLNIR].SetData(
		_T("ƒ~ƒ‡ƒ‹ƒjƒ‹"),
		_T("‘ŠŽèˆê‘Ì‚ÉUŒ‚ˆË‘¶‚Ì‘åƒ_ƒ[ƒW‚ð—^‚¦‚Ü‚·B"),
		_T("%s‚Íƒ~ƒ‡ƒ‹ƒjƒ‹‚ðŽg‚Á‚½I"), SKILLMESSAGE_TYPE_UNIT,
		6, ACTIONTARGET_OPPONENT_ONE);

	// ‹Ù‹}C•œ
	data[SKILL_REPAIR_QUICK].SetData(
		_T("‹Ù‹}C•œ"),
		_T("’N‚æ‚è‚à‘‚­A–¡•ûˆê‘Ì‚Ì‚g‚o‚ð‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚Ì‹Ù‹}C•œI"), SKILLMESSAGE_TYPE_UNIT,
		4, ACTIONTARGET_TEAM_ONE);

	// ƒq[ƒ‹
	data[SKILL_HEAL].SetData(
		_T("ƒq[ƒ‹"),
		_T("–¡•ûˆê‘Ì‚Ì‚g‚o‚ð‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚Íƒq[ƒ‹‚ÌŽô•¶‚ð¥‚¦‚½I"), SKILLMESSAGE_TYPE_UNIT,
		0, ACTIONTARGET_TEAM_ONE);

	// ‹Ù‹}C•œ
	data[SKILL_QUICKHEAL].SetData(
		_T("ƒNƒCƒbƒNƒq[ƒ‹"),
		_T("’N‚æ‚è‚à‘‚­A–¡•ûˆê‘Ì‚Ì‚g‚o‚ð‰ñ•œ‚µ‚Ü‚·B"),
		_T("%s‚ÍƒNƒCƒbƒNƒq[ƒ‹‚ÌŽô•¶‚ð¥‚¦‚½I"), SKILLMESSAGE_TYPE_UNIT,
		0, ACTIONTARGET_TEAM_ONE);
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
