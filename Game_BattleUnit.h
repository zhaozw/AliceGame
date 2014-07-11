#ifndef GAME_BATTLEUNIT_H
#define GAME_BATTLEUNIT_H

#include <Windows.h>
#include "Static_BattleUnit.h"

// 戦闘キャラを扱うクラス。
// 敵味方共にこのクラスから派生する。

class Game_BattleUnit{
protected:
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// 名前
	int			param[BATTLEUNIT_PARAM_NUM];	// 各能力値
	BYTE		attr;							// 属性
	bool		isFront;						// 前に出ているか否か
	BYTE		position;						// 前列・後列における位置
public:
	Game_BattleUnit();

	// 名前をセットする。
	bool SetName(LPTSTR name, int nameLength=-1);
	void GetName(LPTSTR buf, int bufSize);

	// パラメータをセットする。
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
	// パラメータを取得する。
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

	

	int GetRawParam(BYTE index);			// 補正なしのパラメータを取得する。
	int GetCalcParam(BYTE index);			// 補正ありのパラメータを取得する。


	// 全てのパラメータをリセットする。
	virtual void Reset(int n=0);

	// 戦闘中、このキャラが攻撃のターゲットになるかどうかを返す。
	// 戦闘不能などの時はfalseを返す。
	bool CanTarget();
};

#endif // GAME_BATTLEUNIT_H
