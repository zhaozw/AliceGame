// Game_BattleDoll.cpp

#include "Game_BattleUnit.h"
#include "Game_BattleDoll.h"
#include "Game_AliceDoll.h"
#include "Data_DollParam.h"

// �l�`�̃p�����[�^�쐬�Ɏg�p����B
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
	// ���O�̃R�s�[
	

	// �l�`�̃^�C�v�̃R�s�[
	dollType = pDoll->GetType();

	// �e�p�����[�^�̃R�s�[
	for(BYTE n=0; n<DOLL_PARAM_MAX; n++){
		index = 1+((n>=DOLL_PARAM_SPD)?n+1:n);		// HP�A�h��͂Ɋւ��Ă����
		tmpParam = d_dollParam.GetParamFromLv(
			pDoll->GetType(), 
			n, pDoll->GetPotentialLevel(n));
		SetEachParam(index, tmpParam);
		/*
		SetEachParam(n, d_dollParam.GetParamFromLv(pDoll->GetPotentialLevel(n),
			pDoll->GetType(), n));
			*/
		
	}
	// HP�̃R�s�[
	if(useHP){
		SetHP(pDoll->GetHP());
	}else{
		SetHP(param[BATTLEUNIT_PARAM_MAXHP]);
	}
	// �����̃R�s�[
	SetAttr(pDoll->GetAttr());
	// �X�L���̃R�s�[
	for(int n=0; n<DOLL_SKILL_MAX; n++){
		SetSkillID(n, pDoll->GetSkillID(n));
	}
	return true;
}