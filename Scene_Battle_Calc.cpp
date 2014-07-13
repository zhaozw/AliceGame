// Scene_Battle_Calc.cpp

#include "Scene_Battle.h"
#include <algorithm>
#include "Data_StateMessage.h"

extern Data_StateMessage d_stateMessage;

bool Scene_Battle::SetCommand(Game_UnitCommand cmd){
	if(commandIndex >= MAX_UNITCOMMAND) return false;
	cmd.SetUsed();
	commands[commandIndex] = cmd;
	commandIndex++;
	return true;
}

bool Scene_Battle::SetEnemyCommands(){
	// �G���ꂼ��ɂ��ăR�}���h���Z�b�g����B

	// �G�̃|�C���^
	Game_BattleEnemy*	pEnemy = NULL;
	// �ǉ�����R�}���h
	Game_UnitCommand	cmd;

	for(int n=0; n<enemiesNum; n++){
		pEnemy = GetEnemyPtr(n);
		if(pEnemy != NULL){
			cmd = GetEnemyCommand(pEnemy);
			SetCommand(cmd);
		}
	}
	return true;
}


Game_UnitCommand Scene_Battle::GetEnemyCommand(Game_BattleEnemy* pEnemy){
	// ���ɒʏ�U���������Z�b�g����B
	Game_UnitCommand cmd;
	// �^�[�Q�b�g
	Game_BattleDoll* pTarget;
	// �ʏ�U��
	cmd.SetOwner(pEnemy);
	cmd.SetTarget(GetRandomDollPtr());
	cmd.SetActionType(ACTIONTYPE_ATTACK);
	cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
	return cmd;
}

bool Scene_Battle::SortUnitCommands(){
	std::sort(commands, commands+MAX_UNITCOMMAND, Game_UnitCommand::SortBySpd);
	return true;
}

void Scene_Battle::ClearCommands(){
	for(int n=0; n<MAX_UNITCOMMAND; n++){
		commands[n].Reset();
	}
	commandIndex = 0;
}

int Scene_Battle::CalcDamage(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent,
	int param){
		int from = 0;		// �U�����̃p�����[�^
		int to = 0;			// �󂯎葤�̃p�����[�^
		float rate = 1.0;	// �{��
		float fix = 0.0;	// �萔
		float gRate = 1.0;	// �萔���܂߂��{��
		int damage;			// �v�Z����
		bool canMinus = false;	// ������F�߂邩�ۂ�
		switch(param){
		case CALCDAMAGE_ATTACK:
			from	= pAttacker->GetAtk();
			to		= pOpponent->GetDef();
			rate	= GetAttrRate(pAttacker->GetAttr(), pOpponent->GetAttr());
			break;
		}
		// �����̃X�e�[�g�ɂ��_���[�W�̕␳
		if(pOpponent->IsState(STATE_GUARD)){
			// �h��
			rate *= 0.5;
		}

		damage = (int)(gRate*(rate*(from-to)+fix));
		if(canMinus){
			return min(DAMAGE_MAX, damage);
		}else{
			return min(DAMAGE_MAX, max(0, damage));
		}
}

BYTE Scene_Battle::GetAttrAffinity(BYTE attackerAttr, BYTE opponentAttr){
	switch(attackerAttr){
	case DOLL_ATTR_SUN:
		switch(opponentAttr){
		case DOLL_ATTR_MOON:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_STAR:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	case DOLL_ATTR_MOON:
		switch(opponentAttr){
		case DOLL_ATTR_STAR:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_SUN:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	case DOLL_ATTR_STAR:
		switch(opponentAttr){
		case DOLL_ATTR_SUN:
			return ATTRAFFINITY_STRONG;
			break;
		case DOLL_ATTR_MOON:
			return ATTRAFFINITY_WEAK;
			break;
		}
		break;
	}
	return ATTRAFFINITY_EVEN;
}

float Scene_Battle::GetAttrRate(BYTE attackerAttr, BYTE opponentAttr){
	switch(GetAttrAffinity(attackerAttr, opponentAttr)){
	case ATTRAFFINITY_EVEN:
		return 1.0;
		break;
	case ATTRAFFINITY_STRONG:
		return ATTRRATE_STRONG;
		break;
	case ATTRAFFINITY_WEAK:
		return ATTRRATE_WEAK;
		break;
	}
	return 1.0;
}

BYTE Scene_Battle::AddStateToUnit(
	Game_BattleUnit* pUnit, WORD stateRefID, bool showMessage){
		TCHAR buf[WND_MSG_STOCKLENGTH];
		BYTE result;
		if(pUnit == NULL){
			return ADDSTATE_ERROR;
		}
		// �X�e�[�g�̓K�p
		result = pUnit->AddState(stateRefID);
		// ���b�Z�[�W�̒ǉ�
		if(showMessage){
			switch(result){
			case ADDSTATE_SUCCEED:
			case ADDSTATE_MULTIPLIED:
				// �X�e�[�g�ɂȂ����Ƃ��̃��b�Z�[�W���擾
				d_stateMessage.GetStateMessage(
					buf, stateRefID,
					STATEMESSAGE_INDEX_DOLL_ADDED, pUnit);
				// ���b�Z�[�W�ɒǉ�
				AddStockMessage(buf);
				break;
			}
		}
		return result;
}

void Scene_Battle::UpdateStateTurn(){
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		if(dolls[n].GetIsUsed()){
			dolls[n].UpdateStateTurn();
		}
	}
}