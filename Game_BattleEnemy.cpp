//  Game_BattleEnemy.cpp

#include <DxLib.h>
#include "Game_BattleUnit.h"
#include "Game_BattleEnemy.h"
#include "Data_EnemyParam.h"

Game_BattleEnemy::Game_BattleEnemy() : Game_BattleUnit(){
	Reset();
}

void Game_BattleEnemy::SetSelfTurn(){
	selfTurn = GetRand(100);
}

void Game_BattleEnemy::Reset(int n){
	Game_BattleUnit::Reset(n);
	dataID = 0;
	selfTurn = 0;
	drawX = 0;
	drawY = 0;
	pActPattern = NULL;
}

void Game_BattleEnemy::LoadFromData(Data_EnemyParam_Each* pData){
	// データIDの取得
	dataID = pData->GetRefID();

	// 名前の取得
	SetName(pData->GetNamePtr());

	// 属性・経験値の取得
	SetAttr(pData->GetAttr());
	SetExp(pData->GetExp());

	// 各パラメータ値の取得
	for(int n=0; n<BATTLEUNIT_PARAM_NUM; n++){
		SetEachParam(n, pData->GetParam(n));
	}
}


bool Game_BattleEnemy::ChooseAction(){
	// 行動選択時は毎回データベースを参照する。
	return true;
}