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
	// ようすを見ている
	data[SKILL_WAIT].SetData(
		_T("様子を見る"),
		_T("何もしません。"),
		_T("%sは様子を見ている！"), SKILLMESSAGE_TYPE_UNIT,
		0, ACTIONTARGET_NONE);

	// 全体攻撃
	data[SKILL_ALLRANGE].SetData(
		_T("全体攻撃"),
		_T("敵全体に攻撃します。"),
		_T("%sの攻撃！"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ALL);

	// 先制攻撃
	data[SKILL_LOADOFF_ATTACK].SetData(
		_T("先制攻撃"),
		_T("誰よりも速く風のように素早く攻撃します。"),
		_T("%sは風のように素早く攻撃した！"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ONE);

	// 回復
	data[SKILL_HEAL1].SetData(
		_T("回復"),
		_T("味方一体の体力を５０％回復します。"),
		_T("%sは回復の術式を使った！"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_TEAM_ONE);

	// ばらまき弾
	data[SKILL_WIDESHOT].SetData(
		_T("ばらまき弾"),
		_T("敵全体に向かって弾幕を放ちます。"),
		_T("%sはばらまき弾を放った！"), SKILLMESSAGE_TYPE_UNIT,
		4, ACTIONTARGET_OPPONENT_ALL);

	// クナイ弾
	data[SKILL_KUNAISHOT].SetData(
		_T("クナイ弾"),
		_T("相手の技巧が低いほど威力が上がります。"),
		_T("%sはクナイ弾を放った！"), SKILLMESSAGE_TYPE_UNIT,
		2, ACTIONTARGET_OPPONENT_ONE);

	// ナイフ弾
	data[SKILL_KNIFESHOT].SetData(
		_T("ナイフ弾"),
		_T("相手の防御力を無視してダメージを与えます。"),
		_T("%sはナイフ弾を放った！"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);

	// 霊撃
	data[SKILL_REIGEKI].SetData(
		_T("霊撃"),
		_T("属性の影響を受けない攻撃を放ちます。"),
		_T("%sは霊撃を放った！"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);
	
	// 光弾
	data[SKILL_PHOTONSHOT].SetData(
		_T("光弾"),
		_T("威力が魔力に依存する弾を放ちます。"),
		_T("%sは光弾を放った！"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_OPPONENT_ONE);

	// 修復
	data[SKILL_REPAIR].SetData(
		_T("修復"),
		_T("味方一体のＨＰを回復します。"),
		_T("%sの修復！"), SKILLMESSAGE_TYPE_UNIT,
		3, ACTIONTARGET_TEAM_ONE);

	// 全体修復
	data[SKILL_REPAIR_ALL].SetData(
		_T("全体修復"),
		_T("前列の味方全体のＨＰを回復します。"),
		_T("%sの全体修復！"), SKILLMESSAGE_TYPE_UNIT,
		5, ACTIONTARGET_TEAM_ALL);

	// ミョルニル
	data[SKILL_MJOLLNIR].SetData(
		_T("ミョルニル"),
		_T("相手一体に攻撃依存の大ダメージを与えます。"),
		_T("%sはミョルニルを使った！"), SKILLMESSAGE_TYPE_UNIT,
		6, ACTIONTARGET_OPPONENT_ONE);

	// 緊急修復
	data[SKILL_REPAIR_QUICK].SetData(
		_T("緊急修復"),
		_T("誰よりも早く、味方一体のＨＰを回復します。"),
		_T("%sの緊急修復！"), SKILLMESSAGE_TYPE_UNIT,
		4, ACTIONTARGET_TEAM_ONE);

	// ヒール
	data[SKILL_HEAL].SetData(
		_T("ヒール"),
		_T("味方一体のＨＰを回復します。"),
		_T("%sはヒールの呪文を唱えた！"), SKILLMESSAGE_TYPE_UNIT,
		0, ACTIONTARGET_TEAM_ONE);

	// 緊急修復
	data[SKILL_QUICKHEAL].SetData(
		_T("クイックヒール"),
		_T("誰よりも早く、味方一体のＨＰを回復します。"),
		_T("%sはクイックヒールの呪文を唱えた！"), SKILLMESSAGE_TYPE_UNIT,
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
