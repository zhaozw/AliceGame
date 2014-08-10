// Data_SkillText.cpp

#include "Data_SkillInfo.h"
#include "Static_Battle.h"

void Data_SkillMessage_Each::SetSkillMessage(BYTE _type, LPTSTR str, int strLen){
	int length = 0;
	if(strLen == -1){
		length = strlen(str);
	}else{
		length = strLen;
	}
	if(length > SKILLMESSAGE_BYTES) return;
	type = _type;
	// ������̃R�s�[
	strcpy_s(message, SKILLMESSAGE_BYTES-1, str);
}

bool Data_SkillMessage_Each::GetSkillMessage(LPTSTR buf, Game_BattleUnit* pUnit){
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// ���O�̎擾
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
	// �悤�������Ă���
	data[SKILL_WAIT].SetData(
		_T("�l�q������"),
		_T("�������܂���B"),
		_T("%s�͗l�q�����Ă���I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_NONE);

	// �S�̍U��
	data[SKILL_ALLRANGE].SetData(
		_T("�S�̍U��"),
		_T("�G�S�̂ɍU�����܂��B"),
		_T("%s�̍U���I"), SKILLMESSAGE_TYPE_UNIT,
		2, SKILLTARGET_OPPONENT_ALL);

	// �搧�U��
	data[SKILL_LOADOFF_ATTACK].SetData(
		_T("�搧�U��"),
		_T("�N�����������̂悤�ɑf�����U�����܂��B"),
		_T("%s�͕��̂悤�ɑf�����U�������I"), SKILLMESSAGE_TYPE_UNIT,
		2, SKILLTARGET_OPPONENT_ONE);

	// ��
	data[SKILL_HEAL1].SetData(
		_T("��"),
		_T("������̗̂̑͂��T�O���񕜂��܂��B"),
		_T("%s�͉񕜂̏p�����g�����I"), SKILLMESSAGE_TYPE_UNIT,
		2, SKILLTARGET_TEAM_ONE);

	// �΂�܂��e
	data[SKILL_WIDESHOT].SetData(
		_T("�΂�܂��e"),
		_T("�G�S�̂Ɍ������Ēe��������܂��B"),
		_T("%s�͂΂�܂��e��������I"), SKILLMESSAGE_TYPE_UNIT,
		4, SKILLTARGET_OPPONENT_ALL);

	// �N�i�C�e
	data[SKILL_KUNAISHOT].SetData(
		_T("�N�i�C�e"),
		_T("����̋Z�I���Ⴂ�قǈЗ͂��オ��܂��B"),
		_T("%s�̓N�i�C�e��������I"), SKILLMESSAGE_TYPE_UNIT,
		2, SKILLTARGET_OPPONENT_ONE);

	// �i�C�t�e
	data[SKILL_KNIFESHOT].SetData(
		_T("�i�C�t�e"),
		_T("����̖h��͂𖳎����ă_���[�W��^���܂��B"),
		_T("%s�̓i�C�t�e��������I"), SKILLMESSAGE_TYPE_UNIT,
		3, SKILLTARGET_OPPONENT_ONE);

	// �쌂
	data[SKILL_REIGEKI].SetData(
		_T("�쌂"),
		_T("�����̉e�����󂯂Ȃ��U��������܂��B"),
		_T("%s�͗쌂��������I"), SKILLMESSAGE_TYPE_UNIT,
		3, SKILLTARGET_OPPONENT_ONE);
	
	// ���e
	data[SKILL_PHOTONSHOT].SetData(
		_T("���e"),
		_T("�З͂����͂Ɉˑ�����e������܂��B"),
		_T("%s�͌��e��������I"), SKILLMESSAGE_TYPE_UNIT,
		3, SKILLTARGET_OPPONENT_ONE);

	// �C��
	data[SKILL_REPAIR].SetData(
		_T("�C��"),
		_T("������̂̂g�o���񕜂��܂��B"),
		_T("%s�̏C���I"), SKILLMESSAGE_TYPE_UNIT,
		3, SKILLTARGET_TEAM_ONE);

	// �S�̏C��
	data[SKILL_REPAIR_ALL].SetData(
		_T("�S�̏C��"),
		_T("�O��̖����S�̂̂g�o���񕜂��܂��B"),
		_T("%s�̑S�̏C���I"), SKILLMESSAGE_TYPE_UNIT,
		5, SKILLTARGET_TEAM_ALL);

	// �~�����j��
	data[SKILL_MJOLLNIR].SetData(
		_T("�~�����j��"),
		_T("�����̂ɍU���ˑ��̑�_���[�W��^���܂��B"),
		_T("%s�̓~�����j�����g�����I"), SKILLMESSAGE_TYPE_UNIT,
		6, SKILLTARGET_OPPONENT_ONE);

	// �ً}�C��
	data[SKILL_REPAIR_QUICK].SetData(
		_T("�ً}�C��"),
		_T("�N���������A������̂̂g�o���񕜂��܂��B"),
		_T("%s�ً̋}�C���I"), SKILLMESSAGE_TYPE_UNIT,
		4, SKILLTARGET_TEAM_ONE);

	// �q�[��
	data[SKILL_HEAL].SetData(
		_T("�q�[��"),
		_T("������̂̂g�o���񕜂��܂��B"),
		_T("%s�̓q�[���̎������������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// �ً}�C��
	data[SKILL_QUICKHEAL].SetData(
		_T("�N�C�b�N�q�[��"),
		_T("�N���������A������̂̂g�o���񕜂��܂��B"),
		_T("%s�̓N�C�b�N�q�[���̎������������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// ���G���`�����g
	data[SKILL_ENCHANT_NEUTRAL].SetData(
		_T("���G���`�����g"),
		_T("������̂ɖ�������t�����܂��B"),
		_T("%s�͖��̗͂��ĂыN�������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// ���z�G���`�����g
	data[SKILL_ENCHANT_SUN].SetData(
		_T("���z�G���`�����g"),
		_T("������̂ɑ��z������t�����܂��B"),
		_T("%s�͑��z�̗͂��ĂыN�������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// ���G���`�����g
	data[SKILL_ENCHANT_MOON].SetData(
		_T("���G���`�����g"),
		_T("������̂Ɍ�������t�����܂��B"),
		_T("%s�͌��̗͂��ĂыN�������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// ���G���`�����g
	data[SKILL_ENCHANT_STAR].SetData(
		_T("���G���`�����g"),
		_T("������̂ɐ�������t�����܂��B"),
		_T("%s�͐��̗͂��ĂыN�������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_TEAM_ONE);

	// �S�ǂ̎��
	data[SKILL_SUPERGUARD].SetData(
		_T("�S�ǂ̍\��"),
		_T("�ɂ߂ċ������̍\�������܂��B"),
		_T("%s�͓S�ǂ̍\����������I"), SKILLMESSAGE_TYPE_UNIT,
		0, SKILLTARGET_SELF);

	// �E�H�[���E�A���X
	data[SKILL_WALL_ALICE].SetData(
		_T("�E�H�[���E�A���X"),
		_T("�S���Ŏ��̍\�������܂��B"),
		_T("%s�����͋��x�Ȏ��̕ǂ�������I"), SKILLMESSAGE_TYPE_UNIT,
		1, SKILLTARGET_TEAM_ALL);

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
