// Data_StateMessage.cpp

#include "Data_StateMessage.h"
#include "Game_BattleUnit.h"

Data_StateMessage_Each::Data_StateMessage_Each(){
}

void Data_StateMessage_Each::SetMessage(int index, BYTE _type, LPTSTR str, int strLen){
	int length = 0;
	if(strLen == -1){
		length = strlen(str);
	}else{
		length = strLen;
	}
	if(length > STATEMESSAGE_BYTES) return;
	messages[index].type = _type;
	// ������̃R�s�[
	strcpy_s(messages[index].message, STATEMESSAGE_BYTES-1, str);
}

bool Data_StateMessage_Each::GetStateMessage(LPTSTR buf, int index, Game_BattleUnit* pUnit){
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// ���O�̎擾
	if(pUnit != NULL){
		pUnit->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	}else{
		strcpy_s(nameBuf, BATTLEUNIT_NAME_BYTES-1, _T(""));
	}
	switch(messages[index].type){
	case STATEMESSAGE_TYPE_NONE:
		return false;
		break;
	case STATEMESSAGE_TYPE_CONST:
		strcpy_s(buf, STATEMESSAGE_BYTES-1, messages[index].message);
		return true;
		break;
	case STATEMESSAGE_TYPE_UNIT:
		wsprintf(buf, messages[index].message, nameBuf);
		return true;
	}
	return true;
}

Data_StateMessage::Data_StateMessage() : stateMessages(){
}

bool Data_StateMessage::Load(){
	return SetStateMessages();
}

bool Data_StateMessage::SetStateMessages(){
	// �x�^�ł��Ń��b�Z�[�W�����

	// �퓬�s�\
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͗͐s�����I"));
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s��|�����I"));
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͗����オ�����I"));

	// �h��
	stateMessages[STATE_GUARD].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͐g������Ă���I"));
	stateMessages[STATE_GUARD].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͐g������Ă���I"));

	// �����ύX(��)
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑����������Ȃ����I"));
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑����������Ȃ����I"));
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑��������ɖ߂����I"));

	// �����ύX(���z)
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͑��z�̑����𓾂��I"));
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͑��z�̑����ɂȂ����I"));
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑��������ɖ߂����I"));

	// �����ύX(��)
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͌��̑����𓾂��I"));
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͌��̑����ɂȂ����I"));
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑��������ɖ߂����I"));

	// �����ύX(��)
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͐��̑����𓾂��I"));
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�͐��̑����ɂȂ����I"));
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%s�̑��������ɖ߂����I"));



	return true;
}

bool Data_StateMessage::GetStateMessage(
	LPTSTR buf, WORD stateRefID, int index, Game_BattleUnit* pUnit){
		bool result = true;
		result = stateMessages[stateRefID].GetStateMessage(buf, index, pUnit);
		return result;
}
