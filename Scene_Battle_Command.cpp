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
	// 基本的に自分に属性を付加する系のコマンド
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
			// 先制攻撃。
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
	// 基本的に自分に属性を付加する系のコマンド
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

	// 行動不能になった場合は
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


// 下記fixTypeの値
// どんな場合でも補正を行わない
// 全体攻撃などがこれに該当する
#define FIXTARGET_NOFIX					0
// ターゲットが戦闘不能の場合、行動を行わない
// ※選択不可能であっても行動は行う
#define FIXTARGET_DIE_DISAPPEAR			1	
// ターゲットが選択不可能の場合、行動を行わない
#define FIXTARGET_TARGET_DISAPPEAR		2
// ターゲットが戦闘不可ではないが行動対象にはならない場合、行動を行わない
// 逃げた後だったり。
// ※現在のソースコードではいまいちうまくいかない。
#define FIXTARGET_TRANS_DISAPPEAR		3
// ターゲットが戦闘不能の場合、同じサイドの誰かにターゲットを移す
#define FIXTARGET_DIE_CHANGE			4
// ターゲットが選択不可能の場合、同じサイドの誰かにターゲットを移す
#define FIXTARGET_TARGET_CHANGE			5
// ターゲットが戦闘不可ではないが行動対象にはならない場合、行動を行わない
#define FIXTARGET_TRANS_CHANGE			6

// ※混乱してそもそも正しい行動が出来ない場合の補正はこれより前に行う。
// ※全体攻撃のターゲットはアクション発生時に補正を行う。
// ※「かばう」はアクション発生時に補正を行う。

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
		// 全体攻撃・複数回攻撃など、ターゲットが複数の場合はここに該当する。
		// その場合、ターゲットの変更は後で行う。
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
	// このフェイズのInterpretCommandは特殊。
	// かばうなどの処理を発生するアクションごとに行う必要があるが、
	// 便宜上、複数ターゲットの場合はpTarget = NULLとなっているため
	// 一旦、本来のコマンドをScene_Battleクラスが保持するのとは別の
	// Game_UnitCommandの配列subCommandsを用意し、
	// そこでターゲットを一体に確定させる。
	// そのターゲットが確定したsubCommandsに対して
	// それぞれコマンドの確認を行った上で
	// 実際のアクションとして適用する。
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

	// 使用者とターゲット以外の情報をクリア
	action.SetActor(pDefOwner);
	action.SetOpponent(pDefTarget);
	action.ClearWithoutUnit();

	// 本来のコマンドをsubCommandsの配列に変換する。
	switch(pCmd->GetActionType()){
	case ACTIONTYPE_NONE:
		break;
	case ACTIONTYPE_ATTACK:
		// 通常攻撃
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
		// 宣言のみで何も行わない
		break;
	case ACTIONTYPE_SKILL:
		switch(pCmd->GetSkillID()){
		case SKILL_LOADOFF_ATTACK:
			if(CheckDamageAction(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK) == 0){
				// 通常攻撃と同様のダメージ判定
				action.SetType(Game_BattleAction::TYPE_DAMAGE);
				action.SetParam(CalcDamage(pDefOwner, pDefTarget, CALCDAMAGE_ATTACK));
				actionStack.Push(action);
			}
			return 1;
			break;
		case SKILL_HEAL1:
			// HPを回復
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

	// subCommandsの配列を解釈してactionStackに追加する。
	BYTE result = 0;
	for(int n=0; n<MAX_SUBCOMMAND_PER_COMMAND; n++){
		if(subCommands[n].IsEmpty()){
			break;
		}
		switch(subCommands[n].GetActionType()){
		case ACTIONTYPE_DAMAGE:
			// ダメージ関連。param:ダメージの種類。
			// 「かばう」などによるターゲット変更
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
			// 回復関連。param:回復の種類。
			break;
		case ACTIONTYPE_STATE_ATTACK:
			// ステートの付加。param:適用するステートのID。
			break;
		case ACTIONTYPE_STATE_PURE:
			// ステートの付加。param:適用するステートのID。
			break;
		case ACTIONTYPE_STATE_FIX:
			// ステートの付加。param:適用するステートのID。
			break;
		}
	}

	return result;
}

char Scene_Battle::InterpretCommand_Check_Death(Game_UnitCommand* pCmd){
	Sprite_Base* pSprite = NULL;
	// 行動は何であれ、死亡したかどうかの判定を必ず行う
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


