#ifndef GAME_BATTLEDOLL_H
#define GAME_BATTLEDOLL_H

#include "Static_AliceDoll.h"
#include "Game_BattleUnit.h"

// Game_BattleDoll�N���X
// �퓬���̖����L����(�l�`)�������N���X�B

class Game_AliceDoll_Essence;

class Game_BattleDoll : public Game_BattleUnit{
private:
	// �o���Ă���X�L���̔z��
	WORD skillID[DOLL_SKILL_MAX];
public: 
	Game_BattleDoll();

	// �X�L��ID���Z�b�g����B
	void SetSkillID(int index, WORD id){ skillID[index] = id; };

	// �X�L��ID���擾����B
	WORD GetSkillID(int index){ return skillID[index]; };

	// �l�`�ւ̎Q�Ƃ��w�肷��ƁA���̐l�`�̃��x�������Ƀp�����[�^���쐬����B
	// ���݂�HP�̃R�s�[�y�уX�L���̃R�s�[���s���B
	// pDoll	:	�R�s�[����p�����[�^�ւ̎Q��
	// useHP	:	Game_AliceDoll_Essence��HP�̒l���g�p���邩�ۂ��B
	//				false�̏ꍇ�͍ő�HP��HP�ɃR�s�[����B
	bool SetParamFromReference(Game_AliceDoll_Essence* pDoll, bool useHP=true);

	// �S�Ẵp�����[�^�����Z�b�g����B
	virtual void Reset(int n=0);
};

#endif // GAME_BATTLEDOLL_H