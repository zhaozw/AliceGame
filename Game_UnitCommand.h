#ifndef GAME_UNITCOMMAND_H
#define GAME_UNITCOMMAND_H

#include "Static_BattleUnit.h"

#include "Game_BattleUnit.h"

// �퓬�ɂ����郆�j�b�g�̍s����\���N���X�B
// �^�[���̍ŏ��ɂ��̃N���X�̔z�񂪍쐬����A
// �f�������ɕ��בւ���ꂽ��A���ԂɎ��s�����B
class Game_UnitCommand{
private:
	Game_BattleUnit*			pOwner;		// �s���̎�̂ւ̎Q�ƁB
	Game_BattleUnit*			pTarget;	// �s���̑Ώۂւ̎Q�ƁB
											// �����S�̂Ȃǂ̏ꍇ��NULL���w�肷��B
	BYTE						actionType;	// �s���̃^�C�v�B
											// Static_BattleUnit.h�ɋL�q�����萔�B
	BYTE						targetType;	// �^�[�Q�b�g�̃^�C�v�B
											// Static_BattleUnit.h�ɋL�q�����萔�B
	bool						isUsed;		// �R�}���h�Ƀf�[�^�������Ă��邩
	WORD						skillID;	// �X�L����ID�B
	int							param;		// �ėp�p�����[�^�B
											// �ʏ�̃R�}���h�Ƃ��Ă͎g�p�����A
											// Game_BattleAction�̉��ߒ��Ɏg�p����B
public:
	// �R���X�g���N�^
	Game_UnitCommand();

	// ���e�̏��������s���B
	void Reset();


	// ���j�b�g�̍s���̕��בւ����s���֐��B
	// ���x���r���āA�~���Ƀ\�[�g���s���B���Ȃ킿�A���x���傫������
	// �����\�[�g����ۂɏ������l�Ƃ��Č��Ȃ����B
	// aLeft��aRight�����O�ɏo�������ꍇ��true��Ԃ��B
	static bool SortBySpd(const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight);


	// �A�N�Z�T
	void SetOwner(Game_BattleUnit* p){ pOwner = p; };
	void SetTarget(Game_BattleUnit* p){ pTarget = p; };
	void SetActionType(BYTE t){ actionType = t; };
	void SetTargetType(BYTE t){ targetType = t; };
	void SetSkillID(WORD i){ skillID = i; };
	void SetUsed(){ isUsed = true; };
	void SetIsUsed(bool b){ isUsed = b; };
	void SetParam(int p){ param = p; };

	Game_BattleUnit* GetOwner(){ return pOwner; };
	Game_BattleUnit* GetTarget(){ return pTarget; };
	BYTE GetActionType(){ return actionType; };
	BYTE GetTargetType(){ return targetType; };
	WORD GetSkillID(){ return skillID; };
	int GetParam(){ return param; };

	bool IsEmpty() const{ return !isUsed; };

	// �u�������Ȃ��v�R�}���h�ɂ���B
	// �^�[�Q�b�g�����ł����ꍇ�ȂǁB
	void SetEmpty();

};

#endif GAME_UNITCOMMAND_H
