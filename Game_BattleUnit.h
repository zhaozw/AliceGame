#ifndef GAME_BATTLEUNIT_H
#define GAME_BATTLEUNIT_H

#include <Windows.h>
#include "Static_BattleUnit.h"

class Game_BattleState;

// 関数AddStateの戻り値。
#define ADDSTATE_SUCCEED		0	// 普通にステートになった
#define ADDSTATE_ALREADY_ADDED	1	// 既にそのステートだった
#define ADDSTATE_MULTIPLIED		2	// かさねがけになった
#define ADDSTATE_ERROR			99	// 何かおかしい

// ステートを表すクラス。
// メンバ変数はステートID一つのみだが、
// 並べ替える必要性からクラスにしている。

class Game_BattleState{
public:
	// メンバ
	WORD	refID;
	// ターン数
	int		turn;
	// 重ねがけ回数
	int		level;
	// コンストラクタ
	Game_BattleState(){
		refID = 0;
		turn = 0;
		level = 0;
	}

	// 並べ替え用の関数
	// ステートの並べ替えを行う関数。
	// aLeftをaRightよりも前に出したい場合にtrueを返す。

	// 処理の順番で並べ替え
	static bool SortByCalc(const Game_BattleState& aLeft, const Game_BattleState& aRight);

	// 描画優先度の順番で並べ替え
	static bool SortByDraw(const Game_BattleState& aLeft, const Game_BattleState& aRight);

};

// 戦闘キャラを扱うクラス。
// 敵味方共にこのクラスから派生する。
class Game_BattleUnit{
protected:
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// 名前
	int			param[BATTLEUNIT_PARAM_NUM];	// 各能力値
	BYTE		attr;							// 属性
	bool		isFront;						// 前に出ているか否か
	BYTE		position;						// 前列・後列における位置
	bool		isUsed;							// 使用されているか

	// 現在受けているステートのリスト
	Game_BattleState	stateArray[BATTLEUNIT_STATE_MAX];
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
	void SetIsUsed(bool b){ isUsed = b; };
	bool IsUsed(){ return isUsed; };
	bool GetIsUsed(){ return IsUsed(); };

	int GetRawParam(BYTE index);			// 補正なしのパラメータを取得する。
	int GetCalcParam(BYTE index);			// 補正ありのパラメータを取得する。

	// 現在のステートの数を返す。
	// 内部で、ステートを処理の優先度順に並べ替える。
	int GetStateNum();

	// ステートを優先度順に並べ替える。
	void SortStateByCalc();

	// ステートを描画順序順に並べ替える。
	void SortStateByDraw();

	// 参照番号のステートを追加する。
	// 戻り値 : ステート付加の結果。
	//			定数群ADDSTATE_xxxを参照。
	BYTE AddState(WORD refID, int level=1);
	
	// 参照番号のステートに罹患している場合、それを解除する。
	// sort : trueを指定するとステート解除後にソートを行う。
	void RemoveState(WORD refID, bool sort=true);

	// ステートのターン経過を処理する。
	// 一括してターン終了時に行う。
	void UpdateStateTurn();

	// 指定したrefIDのステートを保持しているかどうかを返す。
	// 見つかった場合は配列のインデックス、
	// 見つからなかった場合は-1を返す。
	int CheckIsState(WORD stateRefID);
	
	// 指定したrefIDのステートのレベルを返す。
	// そのステートになっていない場合は0を返す。
	int	CheckStateLevel(WORD stateRefID);
	bool IsState(WORD stateRefID){ return CheckIsState(stateRefID)!=-1; };

	// 全てのパラメータをリセットする。
	virtual void Reset(int n=0);

	// 戦闘中、このキャラがコマンドを選択可能かを返す。
	// 戦闘不能などの時はfalseを返す。
	bool CanAct();

	// 戦闘中、このキャラが攻撃のターゲットになるかどうかを返す。
	// 戦闘不能などの時はfalseを返す。
	bool CanTarget();

	// このキャラが戦闘不能の場合はtrueを返す。
	bool IsDead();

	// このキャラが人形である場合はtrueを返す。
	virtual bool IsDoll(){ return false; };

	// 指定したダメージを与える。
	// HPが負になったらfalseを返す。
	bool Damage(int damage);

	// 戦闘不能になるかどうかを判定する。
	// HPが0以下で、かつまだ戦闘不能ステートが適用されていない場合、
	// trueを返す。
	// trueを返した場合、Scene_Battleクラス経由で戦闘不能ステートが
	// 付加され、またメッセージでそのことが通知される。
	bool CheckDie();

	// 戦闘行動のソート時の素早さを取得する。
	// 素早さだけでなく、「先制」「後攻」ステートの素早さ補正も行う。
	int GetAmendedSpd();
};

#endif // GAME_BATTLEUNIT_H
