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
public:
	// �R���X�g���N�^
	Game_UnitCommand();

	// ���e�̏��������s���B
	void Reset();


	// ���j�b�g�̍s���̕��בւ����s���֐��B
	// ���x���r���āA�~���Ƀ\�[�g���s���B���Ȃ킿�A���x���傫������
	// �����\�[�g����ۂɏ������l�Ƃ��Č��Ȃ����B
	// aLeft��aRight�����O�ɏo�������ꍇ��true��Ԃ��B
	static bool SortBySpd(const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
		// ��̗v�f�͌��ɉ������
		if(aLeft.IsEmpty()){
			return false;
		}else if(aRight.IsEmpty()){
			return true;
		}
		// �����܂łŁA�ǂ��炩�̍s������̏ꍇ��false��true��Ԃ���
		// ��͑f�������m���r
		return aLeft.pOwner->GetSpd() > aRight.pTarget->GetSpd();
	};

	// �A�N�Z�T
	void SetOwner(Game_BattleUnit* p){ pOwner = p; };
	void SetTarget(Game_BattleUnit* p){ pTarget = p; };
	void SetActionType(BYTE t){ actionType = t; };
	void SetTargetType(BYTE t){ targetType = t; };
	void SetUsed(){ isUsed = true; };

	bool IsEmpty() const{ return !isUsed; };

};

#endif GAME_UNITCOMMAND_H
