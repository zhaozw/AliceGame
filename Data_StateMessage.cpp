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
	// 文字列のコピー
	strcpy_s(messages[index].message, STATEMESSAGE_BYTES-1, str);
}

bool Data_StateMessage_Each::GetStateMessage(LPTSTR buf, int index, Game_BattleUnit* pUnit){
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// 名前の取得
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
	// ベタ打ちでメッセージを入力

	// 戦闘不能
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは力尽きた！"));
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sを倒した！"));
	stateMessages[STATE_DEATH].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは立ち上がった！"));

	// 防御
	stateMessages[STATE_GUARD].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは身を守っている！"));
	stateMessages[STATE_GUARD].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは身を守っている！"));

	// 属性変更(無)
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が無くなった！"));
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が無くなった！"));
	stateMessages[STATE_TMPATTR_NONE].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が元に戻った！"));

	// 属性変更(太陽)
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは太陽の属性を得た！"));
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは太陽の属性になった！"));
	stateMessages[STATE_TMPATTR_SUN].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が元に戻った！"));

	// 属性変更(月)
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは月の属性を得た！"));
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは月の属性になった！"));
	stateMessages[STATE_TMPATTR_MOON].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が元に戻った！"));

	// 属性変更(星)
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_DOLL_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは星の属性を得た！"));
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_ENEMY_ADDED, STATEMESSAGE_TYPE_UNIT,
		_T("%sは星の属性になった！"));
	stateMessages[STATE_TMPATTR_STAR].SetMessage(
		STATEMESSAGE_INDEX_REMOVED, STATEMESSAGE_TYPE_UNIT,
		_T("%sの属性が元に戻った！"));



	return true;
}

bool Data_StateMessage::GetStateMessage(
	LPTSTR buf, WORD stateRefID, int index, Game_BattleUnit* pUnit){
		bool result = true;
		result = stateMessages[stateRefID].GetStateMessage(buf, index, pUnit);
		return result;
}
