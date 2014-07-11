#ifndef GAME_BATTLEUNIT_H
#define GAME_BATTLEUNIT_H

#include <Windows.h>
#include "Static_BattleUnit.h"

// �퓬�L�����������N���X�B
// �G�������ɂ��̃N���X����h������B

class Game_BattleUnit{
protected:
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// ���O
	int			param[BATTLEUNIT_PARAM_NUM];	// �e�\�͒l
	BYTE		attr;							// ����
	bool		isFront;						// �O�ɏo�Ă��邩�ۂ�
	BYTE		position;						// �O��E���ɂ�����ʒu
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

	

	int GetRawParam(BYTE index);			// �␳�Ȃ��̃p�����[�^���擾����B
	int GetCalcParam(BYTE index);			// �␳����̃p�����[�^���擾����B


	// �S�Ẵp�����[�^�����Z�b�g����B
	virtual void Reset(int n=0);

	// �퓬���A���̃L�������U���̃^�[�Q�b�g�ɂȂ邩�ǂ�����Ԃ��B
	// �퓬�s�\�Ȃǂ̎���false��Ԃ��B
	bool CanTarget();
};

#endif // GAME_BATTLEUNIT_H
