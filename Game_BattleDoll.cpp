// Game_BattleDoll.cpp

#include "Game_BattleUnit.h"
#include "Game_BattleDoll.h"
#include "Game_AliceDoll.h"
#include "Data_DollParam.h"

// 人形のパラメータ作成に使用する。
extern Data_DollParam			d_dollParam;

Game_BattleDoll::Game_BattleDoll() : Game_BattleUnit(){
	Reset();
}

void Game_BattleDoll::Reset(int n){
	Game_BattleUnit::Reset(n);
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		skillID[n] = 0;
	}
	dollType = 0;
}

bool Game_BattleDoll::SetParamFromReference(Game_AliceDoll_Essence* pDoll, bool useHP){
	if(pDoll == NULL) return false;
	int index = 0;
	int tmpParam = 0;
	// 名前のコピー
	

	// 人形のタイプのコピー
	dollType = pDoll->GetType();

	// 各パラメータのコピー
	for(BYTE n=0; n<DOLL_PARAM_MAX; n++){
		index = 1+((n>=DOLL_PARAM_SPD)?n+1:n);		// HP、防御力に関してずれる
		tmpParam = d_dollParam.GetParamFromLv(
			pDoll->GetType(), 
			n, pDoll->GetPotentialLevel(n));
		SetEachParam(index, tmpParam);
		/*
		SetEachParam(n, d_dollParam.GetParamFromLv(pDoll->GetPotentialLevel(n),
			pDoll->GetType(), n));
			*/
		
	}
	// HPのコピー
	if(useHP){
		SetHP(pDoll->GetHP());
	}else{
		SetHP(param[BATTLEUNIT_PARAM_MAXHP]);
	}
	// 属性のコピー
	SetAttr(pDoll->GetAttr());
	// スキルのコピー
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		SetSkillID(n, pDoll->GetSkillID(n));
	}
	return true;
}