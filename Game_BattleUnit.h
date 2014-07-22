#ifndef GAME_BATTLEUNIT_H
#define GAME_BATTLEUNIT_H

#include <Windows.h>
#include "Static_BattleUnit.h"

class Game_BattleState;

// �֐�AddState�̖߂�l�B
#define ADDSTATE_SUCCEED		0	// ���ʂɃX�e�[�g�ɂȂ���
#define ADDSTATE_ALREADY_ADDED	1	// ���ɂ��̃X�e�[�g������
#define ADDSTATE_MULTIPLIED		2	// �����˂����ɂȂ���
#define ADDSTATE_ERROR			99	// ������������

// �X�e�[�g��\���N���X�B
// �����o�ϐ��̓X�e�[�gID��݂̂����A
// ���בւ���K�v������N���X�ɂ��Ă���B

class Game_BattleState{
public:
	// �����o
	WORD	refID;
	// �^�[����
	int		turn;
	// �d�˂�����
	int		level;
	// �R���X�g���N�^
	Game_BattleState(){
		refID = 0;
		turn = 0;
		level = 0;
	}

	// ���בւ��p�̊֐�
	// �X�e�[�g�̕��בւ����s���֐��B
	// aLeft��aRight�����O�ɏo�������ꍇ��true��Ԃ��B

	// �����̏��Ԃŕ��בւ�
	static bool SortByCalc(const Game_BattleState& aLeft, const Game_BattleState& aRight);

	// �`��D��x�̏��Ԃŕ��בւ�
	static bool SortByDraw(const Game_BattleState& aLeft, const Game_BattleState& aRight);

};

// �퓬�L�����������N���X�B
// �G�������ɂ��̃N���X����h������B
class Game_BattleUnit{
protected:
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// ���O
	int			param[BATTLEUNIT_PARAM_NUM];	// �e�\�͒l
	BYTE		attr;							// ����
	bool		isFront;						// �O�ɏo�Ă��邩�ۂ�
	BYTE		position;						// �O��E���ɂ�����ʒu
	bool		isUsed;							// �g�p����Ă��邩

	// ���ݎ󂯂Ă���X�e�[�g�̃��X�g
	Game_BattleState	stateArray[BATTLEUNIT_STATE_MAX];
public:
	Game_BattleUnit();

	// ���O���Z�b�g����B
	bool SetName(LPTSTR name, int nameLength=-1);
	void GetName(LPTSTR buf, int bufSize);

	// �p�����[�^���Z�b�g����B
	void SetParam(int hp, int maxhp, int atk, int def, int spd, int mgc, int tec);
	void SetEachParam(int paramName, int n){
		param[paramName] = n;
	}
	void SetHP(int n){ param[BATTLEUNIT_PARAM_HP] = n; };
	void SetMaxHP(int n){ param[BATTLEUNIT_PARAM_MAXHP] = n; };
	void SetAtk(int n){ param[BATTLEUNIT_PARAM_ATK] = n; };
	void SetDef(int n){ param[BATTLEUNIT_PARAM_DEF] = n; };
	void SetSpd(int n){ param[BATTLEUNIT_PARAM_SPD] = n; };
	void SetMgc(int n){ param[BATTLEUNIT_PARAM_MGC] = n; };
	void SetTec(int n){ param[BATTLEUNIT_PARAM_TEC] = n; };
	void SetAttr(BYTE _attr){ attr = _attr; };
	void SetFront(bool _front){ isFront = _front; };
	void SetPosition(BYTE _position){ position = _position; };
	// �p�����[�^���擾����B
	int GetParam(int paramName){ 
		if(paramName < 0 || paramName >= BATTLEUNIT_PARAM_NUM){
			return BATTLEUNIT_PARAM_ERROR;
		}
		return param[paramName];
	};
	int GetHP(){ return param[BATTLEUNIT_PARAM_HP]; };
	int GetMaxHP(){ return param[BATTLEUNIT_PARAM_MAXHP]; };
	int GetAtk(){ return param[BATTLEUNIT_PARAM_ATK]; };
	int GetDef(){ return param[BATTLEUNIT_PARAM_DEF]; };
	int GetSpd(){ return param[BATTLEUNIT_PARAM_SPD]; };
	int GetMgc(){ return param[BATTLEUNIT_PARAM_MGC]; };
	int GetTec(){ return param[BATTLEUNIT_PARAM_TEC]; };
	BYTE GetAttr(){ return attr; };
	bool GetFront(){ return isFront; };
	BYTE GetPosition(){ return position; };
	void SetIsUsed(bool b){ isUsed = b; };
	bool IsUsed(){ return isUsed; };
	bool GetIsUsed(){ return IsUsed(); };

	int GetRawParam(BYTE index);			// �␳�Ȃ��̃p�����[�^���擾����B
	int GetCalcParam(BYTE index);			// �␳����̃p�����[�^���擾����B

	// ���݂̃X�e�[�g�̐���Ԃ��B
	// �����ŁA�X�e�[�g�������̗D��x���ɕ��בւ���B
	int GetStateNum();

	// �X�e�[�g��D��x���ɕ��בւ���B
	void SortStateByCalc();

	// �X�e�[�g��`�揇�����ɕ��בւ���B
	void SortStateByDraw();

	// �Q�Ɣԍ��̃X�e�[�g��ǉ�����B
	// �߂�l : �X�e�[�g�t���̌��ʁB
	//			�萔�QADDSTATE_xxx���Q�ƁB
	BYTE AddState(WORD refID, int level=1);
	
	// �Q�Ɣԍ��̃X�e�[�g�ɜ늳���Ă���ꍇ�A�������������B
	// sort : true���w�肷��ƃX�e�[�g������Ƀ\�[�g���s���B
	void RemoveState(WORD refID, bool sort=true);

	// �X�e�[�g�̃^�[���o�߂���������B
	// �ꊇ���ă^�[���I�����ɍs���B
	void UpdateStateTurn();

	// �w�肵��refID�̃X�e�[�g��ێ����Ă��邩�ǂ�����Ԃ��B
	// ���������ꍇ�͔z��̃C���f�b�N�X�A
	// ������Ȃ������ꍇ��-1��Ԃ��B
	int CheckIsState(WORD stateRefID);
	
	// �w�肵��refID�̃X�e�[�g�̃��x����Ԃ��B
	// ���̃X�e�[�g�ɂȂ��Ă��Ȃ��ꍇ��0��Ԃ��B
	int	CheckStateLevel(WORD stateRefID);
	bool IsState(WORD stateRefID){ return CheckIsState(stateRefID)!=-1; };

	// �S�Ẵp�����[�^�����Z�b�g����B
	virtual void Reset(int n=0);

	// �퓬���A���̃L�������R�}���h��I���\����Ԃ��B
	// �퓬�s�\�Ȃǂ̎���false��Ԃ��B
	bool CanAct();

	// �퓬���A���̃L�������U���̃^�[�Q�b�g�ɂȂ邩�ǂ�����Ԃ��B
	// �퓬�s�\�Ȃǂ̎���false��Ԃ��B
	bool CanTarget();

	// ���̃L�������퓬�s�\�̏ꍇ��true��Ԃ��B
	bool IsDead();

	// ���̃L�������l�`�ł���ꍇ��true��Ԃ��B
	virtual bool IsDoll(){ return false; };

	// �w�肵���_���[�W��^����B
	// HP�����ɂȂ�����false��Ԃ��B
	bool Damage(int damage);

	// �퓬�s�\�ɂȂ邩�ǂ����𔻒肷��B
	// HP��0�ȉ��ŁA���܂��퓬�s�\�X�e�[�g���K�p����Ă��Ȃ��ꍇ�A
	// true��Ԃ��B
	// true��Ԃ����ꍇ�AScene_Battle�N���X�o�R�Ő퓬�s�\�X�e�[�g��
	// �t������A�܂����b�Z�[�W�ł��̂��Ƃ��ʒm�����B
	bool CheckDie();

	// �퓬�s���̃\�[�g���̑f�������擾����B
	// �f���������łȂ��A�u�搧�v�u��U�v�X�e�[�g�̑f�����␳���s���B
	int GetAmendedSpd();
};

#endif // GAME_BATTLEUNIT_H
