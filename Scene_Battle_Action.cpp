// Scene_Battle_Action.cpp

#include "Scene_Battle.h"
#include <string.h>

bool Scene_Battle::InterpretAction(Game_BattleAction* pAction){
	if(pAction == NULL){ // �A�N�V�������s�K�؂ȏꍇ
		return false;
	}
	switch(pAction->GetType()){
	case Game_BattleAction::TYPE_CALLENEMYNAME:
		Action_CallEnemyName();
		break;
	case Game_BattleAction::TYPE_NONE:
	case Game_BattleAction::TYPE_UNDIFINED:
	default:
		// �^�C�v���K�؂łȂ��ꍇ
		return false;
		break;
	}
	return true;

}

bool Scene_Battle::InterpretCommand(Game_UnitCommand* pCmd, int phaze){
	switch(phaze){
	case COMMANDPHAZE_NOPHAZE:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_PRE_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_POST_ACTION:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	}
	return false;
}

bool Scene_Battle::InterpretCommand_NoPhaze(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Pre_Action(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Action(Game_UnitCommand* pCmd){
	return true;
}

bool Scene_Battle::InterpretCommand_Post_Action(Game_UnitCommand* pCmd){
	return true;
}


bool Scene_Battle::Action_CallEnemyName(){
	// ���ꂼ��̓G�ɂ��ă��b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	for(int n=0; n<enemiesNum; n++){
		// ���O���擾����
		enemies[n].GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
		// ���O�̑̍ق𐮂���
		strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
		strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�����ꂽ�I"));
		w_battleMsg.AddStockMsg(buf, strlen(buf));
		// w_battleMsg.SetText
	}

	return true;
}