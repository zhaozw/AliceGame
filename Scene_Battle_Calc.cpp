// Scene_Battle_Calc.cpp

#include "Scene_Battle.h"
#include <algorithm>
#include "Data_StateMessage.h"
#include "Static_Skill.h"

extern Data_StateMessage d_stateMessage;

bool Scene_Battle::SetCommand(Game_UnitCommand cmd){
	if(commandIndex >= MAX_UNITCOMMAND) return false;
	cmd.SetUsed();
	commands[commandIndex] = cmd;
	commandIndex++;
	return true;
}

bool Scene_Battle::RemoveOneCommand(){
	if(commandIndex <= 0) return false;
	commandIndex--;
	commands[commandIndex].Reset();
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

bool Scene_Battle::GetCommandWindowIsCancelable(int currentIndex){
	for(int n=0; n<=commandIndex-1; n++){
		if(GetDollPtr(GetFrontIndex(n))->CanAct()){
			return true;
		}
	}
	return false;
}

Game_UnitCommand Scene_Battle::GetEnemyCommand(Game_BattleEnemy* pEnemy){
	// ���ɒʏ�U���������Z�b�g����B
	Game_UnitCommand cmd;
	int resultIndex = 0;
	int cntPriority = 0;

	// �����_���ōs����I�Ԃ��߂̃C���f�b�N�X�̔z��
	int indexArray[MAX_ACTIONPATTERN*9];
	for(int n=0; n<MAX_ACTIONPATTERN*9; n++){
		indexArray[n] = -1;
	}
	int indexArrayLength = 0;

	int max_priority = GetEnemyCommandMaxPriority(pEnemy);
	if(max_priority == 0){
		// ����R�}���h���Ȃ��ꍇ�͗l�q����������
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(NULL);
		cmd.SetActionType(COMMANDTYPE_SKILL);
		cmd.SetSkillID(SKILL_WAIT);
		cmd.SetTargetType(ACTIONTARGET_NONE);
	}else{
		for(int n=0; n<MAX_ACTIONPATTERN; n++){
			cntPriority = GetEnemyCommandPriority(pEnemy, n);
			if(cntPriority != 0){
				switch(max_priority - GetEnemyCommandPriority(pEnemy, n)){
				case 0: // �ł��s���₷���s��
					for(int i=0; i<9; i++){
						indexArray[indexArrayLength] = n;
						indexArrayLength++;
					}
					break;
				case 1: // ���ɍs���₷���s��
					for(int i=0; i<3; i++){
						indexArray[indexArrayLength] = n;
						indexArrayLength++;
					}
					break;
				case 2: // ���A�s��
					indexArray[indexArrayLength] = n;
					indexArrayLength++;
					break;
				}
			}
		}
		// ���͂��ꂽ�l�̒������I�яo��
		if(indexArrayLength != 0){
			resultIndex = indexArray[GetRand(indexArrayLength-1)];
			cmd = MakeEnemyCommand(pEnemy, resultIndex);
		}
	}
	return cmd;
}

int Scene_Battle::GetEnemyCommandPriority(Game_BattleEnemy* pEnemy, int index){
	ENEMYACTIONPATTERN*	pAction;
	pAction = pEnemy->GetActionPatternPtr(index);
	float rate;
	if(pAction == NULL) return 0;
	// �����ōs�������̔�����s��
	// �����𖞂����Ă��Ȃ����̂������0��Ԃ�
	for(int n=0; n<2; n++){
		switch(pAction->conditionType[n]){
		case CONDITIONTYPE_ALWAYS:
			break;
		case CONDITIONTYPE_MAX_HP_RATE:
			rate = (float)100.0f*pEnemy->GetHP()/pEnemy->GetMaxHP();
			if(rate > pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		case CONDITIONTYPE_MIN_HP_RATE:
			rate = (float)100.0f*pEnemy->GetHP()/pEnemy->GetMaxHP();
			if(rate < pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		case CONDITIONTYPE_PERIODIC:
			if(turn % pAction->conditionParam[n][0]
				!= pAction->conditionParam[n][1]){
				return 0;
			}
			break;
		case CONDITIONTYPE_PERIODIC2:
			if(pEnemy->GetSelfTurn() % pAction->conditionParam[n][0]
				!= pAction->conditionParam[n][1]){
				return 0;
			}
			break;
		case CONDITIONTYPE_MAX_HP_RATE_P:
			rate = 100.0f*GetMinimumHPRate();
			if(rate > pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		case CONDITIONTYPE_ATTR:
			if(pEnemy->GetAmendedAttr() != pAction->conditionParam[n][0]){
				return 0;
			}
			break;
		}
	}
	// �D��x��Ԃ��B
	return pAction->priority;
}

int Scene_Battle::GetEnemyCommandMaxPriority(Game_BattleEnemy* pEnemy){
	int result = 0;
	for(int n=0; n<MAX_ACTIONPATTERN; n++){
		result = max(result, GetEnemyCommandPriority(pEnemy, n));
	}
	// �D��x��Ԃ��B
	return result;
}

Game_UnitCommand Scene_Battle::MakeEnemyCommand(Game_BattleEnemy* pEnemy, int index){
	ENEMYACTIONPATTERN* pAction = pEnemy->GetActionPatternPtr(index);
	Game_UnitCommand cmd;
	cmd.Reset();
	if(pAction == NULL){
		cmd.SetEmpty();
		return cmd;
	}
	switch(pAction->actionType){
	case COMMANDTYPE_NONE:
		cmd.SetEmpty();
		break;
	case COMMANDTYPE_ATTACK:
		cmd.SetActionType(COMMANDTYPE_ATTACK);
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(GetRandomDollPtr());
		cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
		break;
	case COMMANDTYPE_SKILL:
		cmd.SetActionType(COMMANDTYPE_SKILL);
		cmd.SetSkillID(pAction->skillID);
		cmd.SetOwner(pEnemy);
		switch(pAction->targetType){
		case ECOMMANDTARGET_NONE:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_NONE);
			break;
		case ECOMMANDTARGET_DOLL_RANDOM:
			cmd.SetTarget(GetRandomDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case ECOMMANDTARGET_DOLL_ALL:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_DOLL_ALL);
			break;
		case ECOMMANDTARGET_ENEMY_RANDOM:
			cmd.SetTarget(GetRandomEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case ECOMMANDTARGET_ENEMY_ALL:
			cmd.SetTarget(NULL);
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ALL);
			break;
		case ECOMMANDTARGET_SELF:
			cmd.SetTarget(pEnemy);
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case ECOMMANDTARGET_DOLL_HP_MIN:
			cmd.SetTarget(GetMinHPDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case ECOMMANDTARGET_DOLL_HP_MIN2:
			cmd.SetTarget(GetMinHPRateDollPtr());
			cmd.SetTargetType(ACTIONTARGET_DOLL_ONE);
			break;
		case ECOMMANDTARGET_ENEMY_HP_MIN:
			cmd.SetTarget(GetMinHPEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case ECOMMANDTARGET_ENEMY_HP_MIN2:
			cmd.SetTarget(GetMinHPRateEnemyPtr());
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			break;
		case ECOMMANDTARGET_ENEMY_OTHER:
			cmd.SetTarget(GetRandomOtherEnemyPtr(pEnemy));
			cmd.SetTargetType(ACTIONTARGET_ENEMY_ONE);
			if(cmd.GetTarget() == NULL){
				cmd.SetEmpty();
			}
			break;
		}
		/*
		// �^�[�Q�b�g�����Ȃ��ꍇ��false��Ԃ�
		// ���Ƃ����̂͑S�̍U�����l����ƕs�\
		if(cmd.GetTarget() == NULL){
			cmd.SetEmpty();
		}
		*/
		break;
	case COMMANDTYPE_GUARD:
		cmd.SetActionType(COMMANDTYPE_GUARD);
		cmd.SetOwner(pEnemy);
		cmd.SetTarget(NULL);
		cmd.SetTargetType(ACTIONTARGET_NONE);
		break;
	}
	return cmd;
}

bool Scene_Battle::SortUnitCommands(){
	// �\�[�g���s��
	std::sort(commands, commands+MAX_UNITCOMMAND, Game_UnitCommand::SortBySpd);
	return true;
}

void Scene_Battle::ClearCommands(){
	for(int n=0; n<MAX_UNITCOMMAND; n++){
		commands[n].Reset();
	}
	commandIndex = 0;
}

BYTE Scene_Battle::CheckDamageAction(
	Game_BattleUnit* pActor, Game_BattleUnit* pTarget, int param){
		return 0;
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
			// �U���͂ɑ����␳��K�p����
			from	= pAttacker->GetAtk() 
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		= pOpponent->GetDef();
			rate	= 1.0f;
			break;
		case CALCDAMAGE_TECH:
			// �Z�I�ɑ����␳��K�p����
			from	= pAttacker->GetTec() 
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		= pOpponent->GetDef();
			rate	= 1.0f;
			break;
		case CALCDAMAGE_TECH_TECH:
			// �Z�I�̍��ɑ����␳��K�p����
			from	= (pAttacker->GetTec() * 2 - pOpponent->GetTec())
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		= pOpponent->GetDef();
			rate	= 1.0f;
			break;
		case CALCDAMAGE_TECH_NOGUARD:
			// �h����g�p���Ȃ�
			from	= pAttacker->GetTec()
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		= 0;
			rate	= 1.0f;
			break;
		case CALCDAMAGE_TECH_NOATTR:
			// �����␳���g�p���Ȃ�
			from	= pAttacker->GetTec();
			to		= pOpponent->GetDef();
			rate	= 1.0f;
			break;
		case CALCDAMAGE_MAGIC_MAGIC:
			// ���͂̍��ɑ����␳��K�p����
			from	= (pAttacker->GetMgc() * 2 - pOpponent->GetMgc())
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		=  pOpponent->GetDef();
			rate	= 1.0f;
			break;
		case CALCDAMAGE_ATTACK_DOUBLE:
			// �U����2�{���疂�͂��Z�I�̍�����������
			from	= (pAttacker->GetAtk() * 2 - max(pOpponent->GetMgc(), pOpponent->GetTec()))
				* GetAttrRate(pAttacker->GetAmendedAttr(), pOpponent->GetAmendedAttr());
			to		=  pOpponent->GetDef();
			rate	= 1.0f;
			break;
		}
		// �����̃X�e�[�g�ɂ��_���[�W�̕␳
		if(pOpponent->IsState(STATE_GUARD)){
			// �h��
			gRate *= 0.5;
		}

		damage = (int)(gRate*(rate*(from-to)+fix));
		if(canMinus){
			return min(DAMAGE_MAX, damage);
		}else{
			return min(DAMAGE_MAX, max(0, damage));
		}
}

int Scene_Battle::CalcHeal(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent,
	int param){
		int		base = 0;
		float	rate = 1.0;
		int		value = 0;

		switch(param){
		case CALCHEAL_HEAL1:
			// �񕜂̏p��1
			// �ő�HP��50%�̉�
			base = 0.5 * pOpponent->GetMaxHP();
			break;
		case CALCHEAL_MAGIC:
			// ���͂Ɠ��l��
			base = pAttacker->GetMgc();
			break;
		case CALCHEAL_MAGIC_DOUBLE:
			// ���͂�2�{�l��
			base = pAttacker->GetMgc()*2;
			break;
		}
		// �����̃X�e�[�g�ɂ��_���[�W�̕␳
		/*
		if(pOpponent->IsState(STATE_GUARD)){
			// �h��
			rate *= 0.5;
		}
		*/

		// �l�̌v�Z
		value = (int)(rate*base);

		// �񕜂�����ƍő�HP������ꍇ�͍ő�l���K��
		return min(value, pOpponent->GetMaxHP()-pOpponent->GetHP());

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

float Scene_Battle::GetMinimumHPRate(){
	Game_BattleEnemy* pTmpEnemy = NULL;
	float minRate = 1.0;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		pTmpEnemy = GetEnemyPtr(n, true);
		if(pTmpEnemy != NULL){
			minRate = min(minRate, (float)pTmpEnemy->GetHP()/pTmpEnemy->GetMaxHP());
		}
	}
	return max(0, minRate);
}

BYTE Scene_Battle::AddStateToUnit(
	Game_BattleUnit* pUnit, WORD stateRefID,
	bool showMessage, int level, bool morphSprite){
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
					pUnit->IsDoll() 
					? STATEMESSAGE_INDEX_DOLL_ADDED 
					: STATEMESSAGE_INDEX_ENEMY_ADDED,
					pUnit);
				// ���b�Z�[�W�ɒǉ�
				AddStockMessage(buf);
				// �X�v���C�g�A�N�V�����̒ǉ�
				if(pUnit->IsDoll()){
					SetDollSpriteMorphByState(
						(Game_BattleDoll*)pUnit, stateRefID);
				}else{
					SetEnemySpriteMorphByState(
						(Game_BattleEnemy*)pUnit, stateRefID);
				}
				break;
			}
		}
		return result;
}

void Scene_Battle::SetDollSpriteMorphByState(Game_BattleDoll* pUnit, WORD stateRefID){
	Sprite_BattleDoll* pSprite;
	pSprite = GetDollSprite(pUnit);
	if(pSprite == NULL) return;
	switch(stateRefID){
	case STATE_DEATH:
		// pSprite->SetMorphID(SPMORPH_DISAPPEAR, true, 60);
		break;
	}
}

void Scene_Battle::SetEnemySpriteMorphByState(Game_BattleEnemy* pUnit, WORD stateRefID){
	Sprite_BattleEnemy* pSprite;
	pSprite = GetEnemySprite(pUnit);
	if(pSprite == NULL) return;
	switch(stateRefID){
	case STATE_DEATH:
		pSprite->SetMorphID(SPMORPH_DISAPPEAR, true, 60);
		break;
	}
}


bool Scene_Battle::CheckStateTurn(){
	Game_BattleAction action;
	WORD removeStateID = 0;
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		if(dolls[n].GetIsUsed()){
			removeStateID = dolls[n].CheckStateTurn();
			if(removeStateID != 0){
				// �X�e�[�g�������������Ƃ������A�N�V�����X�^�b�N��ǉ�����
				action.Clear();
				action.SetActor((Game_BattleUnit*)&dolls[n]);
				action.SetOpponent(NULL);
				action.SetType(Game_BattleAction::TYPE_REMOVESTATE);
				action.SetParam(removeStateID);
				actionStack.Push(action);
				return true;
			}
		}
	}
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(enemies[n].GetIsUsed()){
			removeStateID = enemies[n].CheckStateTurn();
			if(removeStateID != 0){
				// �X�e�[�g�������������Ƃ������A�N�V�����X�^�b�N��ǉ�����
				action.Clear();
				action.SetActor((Game_BattleUnit*)&enemies[n]);
				action.SetOpponent(NULL);
				action.SetType(Game_BattleAction::TYPE_REMOVESTATE);
				action.SetParam(removeStateID);
				actionStack.Push(action);
				return true;
			}
		}
	}
	return false;
}

void Scene_Battle::UpdateUnitTurn(){
	// �G�̃^�[���o�ߔ���������ōs���B
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		if(enemies[n].GetIsUsed()){
			enemies[n].AddTurn();
			enemies[n].UpdateStateTurn();
		}
	}

}