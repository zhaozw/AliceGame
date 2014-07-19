// Scene_Battle_Command.cpp

#include "Scene_Battle.h"
#include "Game_BattleAction.h"
#include "Data_BattleState.h"

char Scene_Battle::InterpretCommand(Game_UnitCommand* pCmd, int phaze){
	if(pCmd == NULL) return -1;
	if(pCmd->IsEmpty()) return -1;
	switch(phaze){
	case COMMANDPHAZE_NOPHAZE:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_FIX_COMMAND:
		return InterpretCommand_Fix_Command(pCmd);
		break;
	case COMMANDPHAZE_FIX_TARGET:
		return InterpretCommand_Fix_Target(pCmd);
		break;
	case COMMANDPHAZE_ASSERT:
		return InterpretCommand_Assert(pCmd);
		break;
	case COMMANDPHAZE_PRE_ACTION:
		return InterpretCommand_Pre_Action(pCmd);
		break;
	case COMMANDPHAZE_ACTION:
		return InterpretCommand_Action(pCmd);
		break;
	case COMMANDPHAZE_CHECK_DEATH:
		return InterpretCommand_Check_Death(pCmd);
		break;
	case COMMANDPHAZE_POST_ACTION:
		return InterpretCommand_Post_Action(pCmd);
		break;
	case COMMANDPHAZE_START_TURN:
		return InterpretCommand_Start_Turn(pCmd);
		break;
	}
	return false;
}

char Scene_Battle::InterpretCommand_NoPhaze(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:

		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}

char Scene_Battle::InterpretCommand_Start_Turn(Game_UnitCommand* pCmd){
	// ��{�I�Ɏ����ɑ�����t������n�̃R�}���h
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_GUARD:
		AddStateToUnit(pCmd->GetOwner(), STATE_GUARD, false);
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}



char Scene_Battle::InterpretCommand_Fix_Command(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;

	// �s���s�\�ɂȂ����ꍇ��
	if(!pCmd->GetOwner()->CanAct()){
		pCmd->SetEmpty();
	}

	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}


// ���LfixType�̒l
// �ǂ�ȏꍇ�ł��␳���s��Ȃ�
// �S�̍U���Ȃǂ�����ɊY������
#define FIXTARGET_NOFIX					0
// �^�[�Q�b�g���퓬�s�\�̏ꍇ�A�s�����s��Ȃ�
// ���I��s�\�ł����Ă��s���͍s��
#define FIXTARGET_DIE_DISAPPEAR			1	
// �^�[�Q�b�g���I��s�\�̏ꍇ�A�s�����s��Ȃ�
#define FIXTARGET_TARGET_DISAPPEAR		2
// �^�[�Q�b�g���퓬�s�ł͂Ȃ����s���Ώۂɂ͂Ȃ�Ȃ��ꍇ�A�s�����s��Ȃ�
// �������ゾ������B
// �����݂̃\�[�X�R�[�h�ł͂��܂������܂������Ȃ��B
#define FIXTARGET_TRANS_DISAPPEAR		3
// �^�[�Q�b�g���퓬�s�\�̏ꍇ�A�����T�C�h�̒N���Ƀ^�[�Q�b�g���ڂ�
#define FIXTARGET_DIE_CHANGE			4
// �^�[�Q�b�g���I��s�\�̏ꍇ�A�����T�C�h�̒N���Ƀ^�[�Q�b�g���ڂ�
#define FIXTARGET_TARGET_CHANGE			5
// �^�[�Q�b�g���퓬�s�ł͂Ȃ����s���Ώۂɂ͂Ȃ�Ȃ��ꍇ�A�s�����s��Ȃ�
#define FIXTARGET_TRANS_CHANGE			6

// ���������Ă��������������s�����o���Ȃ��ꍇ�̕␳�͂�����O�ɍs���B
// ���S�̍U���̃^�[�Q�b�g�̓A�N�V�����������ɕ␳���s���B

char Scene_Battle::InterpretCommand_Fix_Target(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	BYTE fixType = FIXTARGET_NOFIX;
	Game_BattleUnit* pNewTarget;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		fixType = FIXTARGET_DIE_CHANGE;
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}

	switch(fixType){
	case FIXTARGET_NOFIX:
		break;
	case FIXTARGET_DIE_DISAPPEAR:
		if(pCmd->GetTarget()->IsDead()){
			pCmd->SetEmpty();
		}
		break;
	case FIXTARGET_TARGET_DISAPPEAR:
		if(!pCmd->GetTarget()->CanTarget()){
			pCmd->SetEmpty();
		}
		break;
	case FIXTARGET_TRANS_DISAPPEAR:
		if(!pCmd->GetTarget()->CanTarget()){
			pCmd->SetEmpty();
		}
		break;
	case FIXTARGET_DIE_CHANGE:
		if(pCmd->GetTarget()->IsDead()){
			if(pCmd->GetTarget()->IsDoll()){
				pNewTarget = GetRandomDollPtr();
			}else{
				pNewTarget = GetRandomEnemyPtr();
			}
			if(pNewTarget != NULL){
				pCmd->SetTarget(pNewTarget);
			}else{
				pCmd->SetEmpty();
			}
		}
		break;
	case FIXTARGET_TARGET_CHANGE:
		if(!pCmd->GetTarget()->CanTarget()){
			if(pCmd->GetTarget()->IsDoll()){
				pNewTarget = GetRandomDollPtr();
			}else{
				pNewTarget = GetRandomEnemyPtr();
			}
			if(pNewTarget != NULL){
				pCmd->SetTarget(pNewTarget);
			}else{
				pCmd->SetEmpty();
			}
		}
		break;
	case FIXTARGET_TRANS_CHANGE:
		if(!pCmd->GetTarget()->CanTarget()){
			if(pCmd->GetTarget()->IsDoll()){
				pNewTarget = GetRandomDollPtr();
			}else{
				pNewTarget = GetRandomEnemyPtr();
			}
			if(pNewTarget != NULL){
				pCmd->SetTarget(pNewTarget);
			}else{
				pCmd->SetEmpty();
			}
		}
		break;
	}
	return 0;
}


char Scene_Battle::InterpretCommand_Assert(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return -1;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		action.Clear();
		action.SetActor(pCmd->GetOwner());
		action.SetOpponent(pCmd->GetTarget());
		action.SetType(Game_BattleAction::TYPE_ASSERTATTACK);
		actionStack.Push(action);
		return 1;
		break;
	case ACTIONTYPE_SKILL:
		action.Clear();
		action.SetActor(pCmd->GetOwner());
		action.SetOpponent(pCmd->GetTarget());
		action.SetParam(pCmd->GetSkillID());
		action.SetType(Game_BattleAction::TYPE_ASSERTSKILL);
		actionStack.Push(action);
		return 1;
		break;
	case ACTIONTYPE_GUARD:
		action.Clear();
		action.SetActor(pCmd->GetOwner());
		action.SetOpponent(NULL);
		action.SetType(Game_BattleAction::TYPE_ASSERTGUARD);
		actionStack.Push(action);
		return 1;
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}


char Scene_Battle::InterpretCommand_Pre_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_GUARD:
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}

char Scene_Battle::InterpretCommand_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	Game_BattleUnit*		pOwner = pCmd->GetOwner();
	Game_BattleUnit*		pTarget = pCmd->GetTarget();
	if(pCmd == NULL) return -1;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		// �ʏ�U��
		action.Clear();
		action.SetActor(pOwner);
		action.SetOpponent(pTarget);
		action.SetType(Game_BattleAction::TYPE_DAMAGE);
		action.ClearFlag();
		action.SetParam(CalcDamage(pOwner, pTarget, CALCDAMAGE_ATTACK));
		actionStack.Push(action);
		return 1;
		break;
	case ACTIONTYPE_GUARD:
		// �錾�݂̂ŉ����s��Ȃ�
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}

char Scene_Battle::InterpretCommand_Check_Death(Game_UnitCommand* pCmd){
	Sprite_Base* pSprite = NULL;
	// �s���͉��ł���A���S�������ǂ����̔����K���s��
	Game_BattleAction action;
	for(int n=0; n<dollsNum; n++){
		if(dolls[n].CheckDie()){
			if(AddStateToUnit(&dolls[n], STATE_DEATH, true) == ADDSTATE_SUCCEED){
				pSprite = GetDollSprite(&dolls[n]);
				if(pSprite != NULL){
					// pSprite->SetMorphID(SPMORPH_DISAPPEAR, true, 60);
				}
			}
			return 1;
		}
	}
	for(int n=0; n<enemiesNum; n++){
		if(enemies[n].CheckDie()){
			if(AddStateToUnit(&enemies[n], STATE_DEATH, true) == ADDSTATE_SUCCEED){
				pSprite = GetEnemySprite(&enemies[n]);
				if(pSprite != NULL){
					pSprite->SetMorphID(SPMORPH_DISAPPEAR, true, 60);
				}
			}
			return 1;
		}
	}
	return 0;
}

char Scene_Battle::InterpretCommand_Post_Action(Game_UnitCommand* pCmd){
	Game_BattleAction action;
	if(pCmd == NULL) return -1;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_GUARD:
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}


