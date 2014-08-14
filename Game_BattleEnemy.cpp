//  Game_BattleEnemy.cpp

#include <DxLib.h>
#include "Game_BattleUnit.h"
#include "Game_BattleEnemy.h"
#include "Data_EnemyParam.h"

extern Data_EnemyParam	d_enemyParam;

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
}


void Game_BattleEnemy::LoadFromData(Data_EnemyParam_Each* pData){
	// �f�[�^ID�̎擾
	dataID = pData->data.refID;

	// ���O�̎擾
	SetName(pData->data.name);

	// �����E�o���l�̎擾
	SetAttr(pData->data.attr);
	SetExp(pData->data.exp);

	// �e�p�����[�^�l�̎擾
	for(int n=0; n<BATTLEUNIT_PARAM_NUM; n++){
		SetEachParam(n, pData->data.param[n]);
	}
}

ENEMYACTIONPATTERN*	Game_BattleEnemy::GetActionPatternPtr(int index){
	Data_EnemyParam_Each* pEnemyParam = NULL;
	pEnemyParam = d_enemyParam.GetEnemyParam(dataID);
	if(pEnemyParam != NULL){
		return pEnemyParam->GetActionPatternPtr(index);
	}
	return NULL;
}

