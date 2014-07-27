// Scene_Battle_Command.cpp

#include "Scene_Battle.h"
#include "Game_BattleAction.h"
#include "Data_BattleState.h"
#include "Static_Skill.h"
#include "Game_UnitSubCommand.h"

char Scene_Battle::InterpretCommand(Game_UnitCommand* pCmd, int phaze){
	if(pCmd == NULL) return -1;
	if(pCmd->IsEmpty()) return -1;
	switch(phaze){
	case COMMANDPHAZE_NOPHAZE:
		return InterpretCommand_NoPhaze(pCmd);
		break;
	case COMMANDPHAZE_BEFORE_SORT:
		return InterpretCommand_Before_Sort(pCmd);
		break;
	case COMMANDPHAZE_AFTER_SORT:
		return InterpretCommand_After_Sort(pCmd);
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

char Scene_Battle::InterpretCommand_Before_Sort(Game_UnitCommand* pCmd){
	// ��{�I�Ɏ����ɑ�����t������n�̃R�}���h
	Game_BattleAction action;
	if(pCmd == NULL) return false;
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		break;
	case ACTIONTYPE_GUARD:
		break;
	case ACTIONTYPE_SKILL:
		switch(pCmd->GetSkillID()){
		case SKILL_LOADOFF_ATTACK:
			// �搧�U���B
			AddStateToUnit(pCmd->GetOwner(), STATE_SUBSPD_UP, false, 1);
			break;
		}
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}
	return 0;
}


char Scene_Battle::InterpretCommand_After_Sort(Game_UnitCommand* pCmd){
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
// ���u���΂��v�̓A�N�V�����������ɕ␳���s���B

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
	case ACTIONTYPE_SKILL:
		switch(pCmd->GetSkillID()){
		case SKILL_LOADOFF_ATTACK:
			fixType = FIXTARGET_DIE_CHANGE;
			break;
		}
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}

	switch(fixType){
	case FIXTARGET_NOFIX:
		// �S�̍U���E������U���ȂǁA�^�[�Q�b�g�������̏ꍇ�͂����ɊY������B
		// ���̏ꍇ�A�^�[�Q�b�g�̕ύX�͌�ōs���B
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

#define MAX_SUBCOMMAND_PER_COMMAND		16

char Scene_Battle::InterpretCommand_Action(Game_UnitCommand* pCmd){
	// ���̃t�F�C�Y��InterpretCommand�͓���B
	// ���΂��Ȃǂ̏����𔭐�����A�N�V�������Ƃɍs���K�v�����邪�A
	// �֋X��A�����^�[�Q�b�g�̏ꍇ��pTarget = NULL�ƂȂ��Ă��邽��
	// ��U�A�{���̃R�}���h��Scene_Battle�N���X���ێ�����̂Ƃ͕ʂ�
	// Game_UnitCommand�̔z��subCommands��p�ӂ��A
	// �����Ń^�[�Q�b�g����̂Ɋm�肳����B
	// ���̃^�[�Q�b�g���m�肵��subCommands�ɑ΂���
	// ���ꂼ��R�}���h�̊m�F���s�������
	// ���ۂ̃A�N�V�����Ƃ��ēK�p����B
	// 
	Game_BattleAction action;
	Game_BattleUnit*		pDefOwner = pCmd->GetOwner();
	Game_BattleUnit*		pDefTarget = pCmd->GetTarget();
	Game_UnitSubCommand		subCommands[MAX_SUBCOMMAND_PER_COMMAND];
	int						subCommandIndex = 0;
	for(int n=0; n<MAX_SUBCOMMAND_PER_COMMAND; n++){
		subCommands[n].SetOwner(pDefOwner);
		subCommands[n].SetIsUsed(false);
		subCommands[n].SetEmpty();
	}


	if(pCmd == NULL) return -1;

	// �g�p�҂ƃ^�[�Q�b�g�ȊO�̏����N���A
	action.SetActor(pDefOwner);
	action.SetOpponent(pDefTarget);
	action.ClearWithoutUnit();

	// �{���̃R�}���h��subCommands�̔z��ɕϊ�����B
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		// �ʏ�U��
		if(CheckDamageAction(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK) == 0){
			subCommands[subCommandIndex].SetOwner(pDefOwner);
			subCommands[subCommandIndex].SetTarget(pDefTarget);
			subCommands[subCommandIndex].SetActionType(ACTIONTYPE_DAMAGE);
			subCommands[subCommandIndex].SetUsed();
			subCommandIndex++;
			/*
		action.SetType(Game_BattleAction::TYPE_DAMAGE);
		action.SetParam(CalcDamage(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK));
		actionStack.Push(action);
		*/
		}
		// return 1;
		break;
	case ACTIONTYPE_GUARD:
		// �錾�݂̂ŉ����s��Ȃ�
		break;
	case ACTIONTYPE_SKILL:
		switch(pCmd->GetSkillID()){
		case SKILL_LOADOFF_ATTACK:
			if(CheckDamageAction(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK) == 0){
				// �ʏ�U���Ɠ��l�̃_���[�W����
				action.SetType(Game_BattleAction::TYPE_DAMAGE);
				action.SetParam(CalcDamage(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK));
				actionStack.Push(action);
			}
			return 1;
			break;
		case SKILL_HEAL1:
			// HP����
			action.SetType(Game_BattleAction::TYPE_HEAL);
			action.SetParam(CalcHeal(pDefOwner, pDefTarget, CALCHEAL_HEAL1));
			actionStack.Push(action);
			return 1;
		}
		break;
	case ACTIONTYPE_ERROR:
		return -1;
		break;
	}

	// subCommands�̔z������߂���actionStack�ɒǉ�����B
	BYTE result = 0;
	for(int n=0; n<MAX_SUBCOMMAND_PER_COMMAND; n++){
		if(subCommands[n].IsEmpty()){
			break;
		}
		switch(subCommands[n].GetActionType()){
		case ACTIONTYPE_DAMAGE:
			// �_���[�W�֘A�Bparam:�_���[�W�̎�ށB
			// �u���΂��v�Ȃǂɂ��^�[�Q�b�g�ύX
			action.Clear();
			action.SetActor(subCommands[n].GetOwner());
			action.SetOpponent(subCommands[n].GetTarget());
			action.SetType(Game_BattleAction::TYPE_DAMAGE);
			action.ClearFlag();
			action.SetParam(CalcDamage(
				subCommands[n].GetOwner(), subCommands[n].GetTarget(),
				CALCDAMAGE_ATTACK));
			actionStack.Push(action);
			result = (result==0?1:result);
			break;
		case ACTIONTYPE_HEAL:
			// �񕜊֘A�Bparam:�񕜂̎�ށB
			break;
		case ACTIONTYPE_STATE_ATTACK:
			// �X�e�[�g�̕t���Bparam:�K�p����X�e�[�g��ID�B
			break;
		case ACTIONTYPE_STATE_PURE:
			// �X�e�[�g�̕t���Bparam:�K�p����X�e�[�g��ID�B
			break;
		case ACTIONTYPE_STATE_FIX:
			// �X�e�[�g�̕t���Bparam:�K�p����X�e�[�g��ID�B
			break;
		}
	}

	return result;
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


