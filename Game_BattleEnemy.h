#ifndef GAME_BATTLEENEMY_H
#define GAME_BATTLEENEMY_H

// Game_BattleEnemy�N���X
// �퓬�ɂ�����G��̂������N���X�B

#include "Data_EnemyParam.h"
#include "Game_BattleUnit.h"

class Data_EnemyParam_Each;

class Game_BattleEnemy : public Game_BattleUnit{
private:
	WORD		dataID;				// �f�[�^���Q�Ƃ���ۂ�ID�B
	DWORD		exp;				// �o���l
	int			selfTurn;			// �G���ɈقȂ�^�[�����B�퓬�s���̑I���Ɏg�p����B
	int			drawX;				// �`��ʒu
	int			drawY;
	ENEMYACTIONPATTERN*		pActPattern;	// �s���p�^�[���ւ̎Q��(�f�[�^�x�[�X)
public: 
	// �R���X�g���N�^
	Game_BattleEnemy();
	// �s����I�����A�s�����X�g�ɕt��������B
	bool ChooseAction();
	// �`��ʒu���Z�b�g����B
	void SetDrawPos(int x, int y){ drawX = x; drawY = y; };
	// �f�[�^�x�[�X�ł���Data_EnemyParam�N���X����f�[�^����荞�ށB
	void LoadFromData(Data_EnemyParam_Each* pData);
	// �A�N�Z�T
	DWORD	GetExp(){ return exp; }
	void	SetExp(DWORD n){ exp = n; };
	WORD	GetDataID(){ return dataID; };
	void	SetDataID(WORD _id){ dataID = _id; };
	int		GetDrawX(){ return drawX; };
	int		GetDrawY(){ return drawY; };
	int		GetSelfTurn(){ return selfTurn; };
	void	SetSelfTurn(int turn){ selfTurn = turn; };
	void	SetSelfTurn(); // selfTurn�l�������_���ɃZ�b�g����
	void	SetActPattern(ENEMYACTIONPATTERN* pPtn){ pActPattern = pPtn; };
	ENEMYACTIONPATTERN* GetActPattern(){ return pActPattern; };
	// ���̃L�������l�`�ł���ꍇ��true��Ԃ��B
	virtual bool IsDoll(){ return false; };

	// �S�Ẵp�����[�^�����Z�b�g����B
	virtual void Reset(int n=0);
};

#endif // GAME_BATTLEENEMY_H