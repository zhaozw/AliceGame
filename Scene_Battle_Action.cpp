// Scene_Battle_Action.cpp

#include "Scene_Battle.h"
#include <string.h>
#include "MyTask_InfoEffect.h"
#include "Static_InfoEffect.h"
#include "Data_SkillInfo.h"
#include "Data_StateMessage.h"
#include "Game_AliceInfo.h"


extern Data_SkillInfo d_skillInfo;
extern Data_StateMessage d_stateMessage;
extern Game_AliceInfo g_aliceInfo;

extern MyGroup* gMyTask_InfoEffect;

bool Scene_Battle::InterpretAction(Game_BattleAction* pAction){
	if(pAction == NULL){ // アクションが不適切な場合
		return false;
	}
	switch(pAction->GetType()){
	case Game_BattleAction::TYPE_DAMAGE:
		Action_Damage(pAction);
		break;
	case Game_BattleAction::TYPE_HEAL:
		Action_Heal(pAction);
		break;
	case Game_BattleAction::TYPE_CALLENEMYNAME:
		Action_CallEnemyName();
		break;
	case Game_BattleAction::TYPE_CALLVICTORY:
		Action_CallVictory();
		break;
	case Game_BattleAction::TYPE_CALLLOSE:
		Action_CallLose();
		break;
	case Game_BattleAction::TYPE_ASSERTATTACK:
		Action_AssertAttack(pAction);
		break;
	case Game_BattleAction::TYPE_ASSERTSKILL:
		Action_AssertSkill(pAction);
		break;
	case Game_BattleAction::TYPE_ASSERTGUARD:
		Action_AssertGuard(pAction);
		break;
	case Game_BattleAction::TYPE_NO_MP:
		Action_No_MP(pAction);
		break;
	case Game_BattleAction::TYPE_ADDSTATE:
		Action_Add_State(pAction);
		break;
	case Game_BattleAction::TYPE_REMOVESTATE:
		Action_Remove_State(pAction);
		break;
	case Game_BattleAction::TYPE_NONE:
	case Game_BattleAction::TYPE_UNDIFINED:
	default:
		// タイプが適切でない場合
		return false;
		break;
	}
	return true;

}

bool Scene_Battle::Action_Damage(Game_BattleAction* pAction){
	Sprite_Base* pSprite = NULL;
	Sprite_BattleDoll* pDoll = NULL;
	MyTask* pTask = NULL;
	int x=0, y=0;
	// ダメージをメッセージウィンドウに表示する
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	TCHAR numBuf[4]; // 数字表示用
	// 名前を取得する
	pAction->GetOpponent()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// 数値を取得する
	wsprintf(numBuf, _T("%d"), pAction->GetParam());
	// 名前の体裁を整える
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("に"));
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, numBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("のダメージ！"));
	AddStockMessage(buf);
	// ダメージを適用する
	pAction->GetOpponent()->Damage(pAction->GetParam());
	// ダメージの数値を表示する
	if(pAction->GetOpponent()->IsDoll()){
		// 位置を取得
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pTask = gMyTask_InfoEffect->Call();
			pDoll = (Sprite_BattleDoll*)pSprite;
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pDoll->GetDollX(), pDoll->GetDollY()+40,
					INFO_DAMAGENUM_DOLL, pAction->GetParam(), 0);
			}
		}
	}else{
		// 位置を取得
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pTask = gMyTask_InfoEffect->Call();
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pSprite->GetIX(), pSprite->GetIY(),
					INFO_DAMAGENUM_ENEMY, pAction->GetParam(), 0);
			}
		}
	}
	// スプライトに対する処理を行う
	if(pAction->GetOpponent()->IsDoll()){
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_DAMAGE_DOLL, false, 8);
		}
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_BLINK, false, 8);
		}
	}

	
	return true;
}

bool Scene_Battle::Action_Heal(Game_BattleAction* pAction){
	Sprite_Base* pSprite = NULL;
	Sprite_BattleDoll* pDoll = NULL;
	MyTask* pTask = NULL;
	int x=0, y=0;
	// ダメージをメッセージウィンドウに表示する
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	TCHAR numBuf[4]; // 数字表示用
	// 名前を取得する
	pAction->GetOpponent()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// 数値を取得する
	wsprintf(numBuf, _T("%d"), pAction->GetParam());
	// 名前の体裁を整える
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("の体力が"));
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, numBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("回復した！"));
	AddStockMessage(buf);
	// ダメージを適用する
	pAction->GetOpponent()->Heal(pAction->GetParam());
	/*
	// ダメージの数値を表示する
	if(pAction->GetOpponent()->IsDoll()){
		// 位置を取得
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pTask = gMyTask_InfoEffect->Call();
			pDoll = (Sprite_BattleDoll*)pSprite;
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pDoll->GetDollX(), pDoll->GetDollY()+40,
					INFO_DAMAGENUM_DOLL, pAction->GetParam(), 0);
			}
		}
	}else{
		// 位置を取得
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pTask = gMyTask_InfoEffect->Call();
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pSprite->GetIX(), pSprite->GetIY(),
					INFO_DAMAGENUM_ENEMY, pAction->GetParam(), 0);
			}
		}
	}
	*/
	/*
	// スプライトに対する処理を行う
	if(pAction->GetOpponent()->IsDoll()){
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_DAMAGE_DOLL, false, 8);
		}
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_BLINK, false, 8);
		}
	}
	*/

	
	return true;
}


bool Scene_Battle::Action_CallEnemyName(){
	// それぞれの敵についてメッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	for(int n=0; n<enemiesNum; n++){
		// 名前を取得する
		enemies[n].GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
		// 名前の体裁を整える
		strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
		strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("が現れた！"));
		w_battleMsg.AddStockMsg(buf, strlen(buf));
		// w_battleMsg.SetText
	}
	return true;
}

bool Scene_Battle::Action_CallVictory(){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("勝利した！"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_CallLose(){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("全滅した…。"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_AssertAttack(Game_BattleAction* pAction){
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// 名前を取得する
	pAction->GetActor()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// 名前の体裁を整える
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("の攻撃！"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	// スプライトに対する処理を行う
	Sprite_Base* pSprite;
	if(pAction->GetActor()->IsDoll()){
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetActor());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_ENEMYATTACK, false);
		}
	}
	return true;
}

bool Scene_Battle::Action_AssertSkill(Game_BattleAction* pAction){
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T(""));
	d_skillInfo.GetAssertMessage(buf, pAction->GetParam(), pAction->GetActor());
	if(strlen(buf)>0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// スプライトに対する処理を行う
	Sprite_Base* pSprite;
	if(pAction->GetActor()->IsDoll()){
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetActor());
		if(pSprite != NULL){
			// タスクを発生させる
			pSprite->SetMorphID(SPMORPH_ENEMYATTACK, false);
		}
	}
	return true;
}

bool Scene_Battle::Action_AssertGuard(Game_BattleAction* pAction){
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// 名前を取得する
	pAction->GetActor()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// 名前の体裁を整える
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("は身を守っている！"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_No_MP(Game_BattleAction* pAction){
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("しかし、アリスの魔力が足りない！"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_Add_State(Game_BattleAction* pAction){
	Game_BattleUnit* pTarget = pAction->GetOpponent();
	if(pTarget == NULL) return false;
	// ステートの付加
	int param = 0, param2 = 0;
	// ステートごとに、paramとparam2の代入の仕方が異なる
	switch(pAction->GetParam()){
	case STATE_TMPATTR_NONE:
	case STATE_TMPATTR_SUN:
	case STATE_TMPATTR_MOON:
	case STATE_TMPATTR_STAR:
		param = (int)(pAction->GetFlags());
		break;
	default:
		// param値を使用しない
		break;
	}
	pTarget->AddState(pAction->GetParam(), param, param2);
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	if(!d_stateMessage.GetStateMessage(buf, pAction->GetParam(),
		pTarget->IsDoll() 
		? STATEMESSAGE_INDEX_DOLL_ADDED 
		: STATEMESSAGE_INDEX_ENEMY_ADDED,
		pTarget)){
			// メッセージが存在しない場合
			return true;
	}
	if(strlen(buf) > 0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// スプライトを更新する
	if(pTarget->IsDoll()){
		// GetDollSprite((Game_BattleDoll*)pTarget)->UpdateRefID();
	}else{
		GetEnemySprite((Game_BattleEnemy*)pTarget)->UpdateRefID();
	}
	return true;
}

bool Scene_Battle::Action_Remove_State(Game_BattleAction* pAction){
	Game_BattleUnit* pTarget = pAction->GetActor();
	if(pTarget == NULL) return false;
	// ステートの解除
	pAction->GetActor()->RemoveState(pAction->GetParam());
	// メッセージウィンドウに内容を送る
	TCHAR buf[WND_MSG_STOCKLENGTH];
	if(!d_stateMessage.GetStateMessage(buf, pAction->GetParam(),
		STATEMESSAGE_INDEX_REMOVED, pAction->GetActor())){
			// メッセージが存在しない場合
			return true;
	}
	if(strlen(buf) > 0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// スプライトを更新する
	if(pTarget->IsDoll()){
		// GetDollSprite((Game_BattleDoll*)pTarget)->UpdateRefID();
	}else{
		GetEnemySprite((Game_BattleEnemy*)pTarget)->UpdateRefID();
	}
	return true;
}