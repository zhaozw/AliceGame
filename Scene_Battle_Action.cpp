// Scene_Battle_Action.cpp

#include "Scene_Battle.h"
#include <string.h>

bool Scene_Battle::InterpretAction(Game_BattleAction* pAction){
	if(pAction == NULL){ // アクションが不適切な場合
		return false;
	}
	switch(pAction->GetType()){
	case Game_BattleAction::TYPE_DAMAGE:
		Action_Damage(pAction);
		break;
	case Game_BattleAction::TYPE_CALLENEMYNAME:
		Action_CallEnemyName();
		break;
	case Game_BattleAction::TYPE_ASSERTATTACK:
		Action_AssertAttack(pAction);
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
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	// ダメージを適用する
	pAction->GetOpponent()->Damage(pAction->GetParam());
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
	return true;
}