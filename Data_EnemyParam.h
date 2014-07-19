#ifndef DATA_ENEMYPARAM_H
#define DATA_ENEMYPARAM_H

#include <Windows.h>
#include "Static_BattleUnit.h"
#include "VectorList.h"

// 敵キャラの能力値のデータベースを扱うクラス。
//データはグローバル変数d_enemyParamから参照される。

// 定数
#define MAX_CONDITION			2	// 複数条件を指定可能
#define MAX_CONDITIONPARAM		3	// 条件あたりのパラメータの数
#define MAX_ACTIONPATTERN		16	// 攻撃パターンの数

/*
// この内容はStatic_BattleUnitに移行。
// 行動の種類に関する定数
#define ACTIONTYPE_NONE			0	// 何もしない
#define ACTIONTYPE_ATTACK		1	// 通常攻撃
#define ACTIONTYPE_GUARD		2	// 防御
#define ACTIONTYPE_SKILL		3	// 特技
*/

// 行動の対象に関する定数
#define TARGETTYPE_NONE				0	// 対象なし（もしくは場全体）
#define TARGETTYPE_DOLL_RANDOM		1	// 人形一体をランダムに
#define TARGETTYPE_DOLL_ALL			2	// 人形全体
#define TARGETTYPE_ENEMY_RANDOM		3	// 敵一体をランダムに
#define TARGETTYPE_ENEMY_ALL		4	// 敵全体
#define TARGETTYPE_SELF				5	// 自分
#define TARGETTYPE_DOLL_HP_MIN		6	// HPの最も少ない人形一体
#define TARGETTYPE_DOLL_HP_MIN2		7	// 最大HPに対するHPの比が最も少ない人形一体
#define TARGETTYPE_ENEMY_HP_MIN		8	// HPの最も少ない敵一体
#define TARGETTYPE_ENEMY_HP_MIN2	9	// 最大HPに対するHPの比が最も少ない敵一体

// 敵データのパラメータ数
#define NUM_ENEMYPARAM_DATA			(BATTLEUNIT_PARAM_NUM-1)
#define ENEMYPARAM_HP				0
#define ENEMYPARAM_ATK				1
#define ENEMYPARAM_DEF				2
#define ENEMYPARAM_SPD				3
#define ENEMYPARAM_MGC				4
#define ENEMYPARAM_TEC				5

// 行動パターンを取りうるか取らないかの条件。
// 条件に合う行動を、priorityに従って選択する。

// 常時行う。
// 漏れを防ぐため、必ずこの条件を持つ行動を1つ以上持っているべき。
#define CONDITIONTYPE_ALWAYS		0 
// 行動を行うHPの最大値を規定する。
// param[0] : HPが(x)%以上の時は行わない。
#define CONDITIONTYPE_MAX_HP_RATE		1
// 行動を行うHPの最大値を規定する。
// param[0] : HPが(x)%以下の時は行わない。
#define CONDITIONTYPE_MIN_HP_RATE		2

// ターンによる。
// [0][1] : 戦闘が始まってからのターン数を[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC	1

// ターンによるその2。
// [0][1] : 敵毎に異なるターン数selfTurnを[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC2	2

// HPが一定範囲の場合。
// [0] : HPが[0]%以下である場合であり、さらに
// [1] : HPが[1]%以上である場合は行動する。
#define CONDITIONTYPE_HP		3

// 行動パターンに関するパラメータをまとめて指定する用
#define ACTIONPATTERN_ACTIONTYPE	0
#define ACTIONPATTERN_SKILLID		1
#define ACTIONPATTERN_TARGETTYPE	2
#define ACTIONPATTERN_PRIORITY		3
#define ACTIONPATTERN_PARAMNUM		4

// 敵キャラの行動パターンの一つを扱う構造体。
typedef struct EnemyActionPattern{
	WORD		actionType;			// 行動の種類。
	DWORD		skillID;			// 行動が特技である場合、特技ID
	BYTE		targetType;			// 行動の対象の種類
	WORD		priority;			// 行動の優先度。これが0であるということは
									// 行動が指定されていないということも意味する。
	// その行動を選択する条件のタイプ
	WORD		conditionType[MAX_CONDITION];
	// 条件に関連するパラメータ
	int			conditionParam[MAX_CONDITION][MAX_CONDITIONPARAM];
	EnemyActionPattern(){
		actionType		= ACTIONTYPE_NONE;
		skillID			= 0;
		targetType		= TARGETTYPE_NONE;
		priority		= 0;
		for(int j=0; j<MAX_CONDITION; j++){
			conditionType[j] = CONDITIONTYPE_ALWAYS;
			for(int i=0; i<MAX_CONDITIONPARAM; i++){
				conditionParam[j][i] = 0;
			}
		}
	}
}ENEMYACTIONPATTERN;

// Data_EnemyParam_Eachクラス。
// 敵一体についての情報を保持する。
// 実際には、このクラスの配列を持つFlexListが作成される。
class Data_EnemyParam_Each{
private:
	WORD		refID;							// 参照される時のID
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// 名前
	int			param[NUM_ENEMYPARAM_DATA];	// 各能力値(HPを除く)
	BYTE		attr;							// 属性
	DWORD		exp;							// 経験値
	// 行動パターンの配列
	ENEMYACTIONPATTERN		actionPtn[MAX_ACTIONPATTERN];
public:
	// コンストラクタ
	Data_EnemyParam_Each();
	void	Refresh();
	// アクセサ
	void	SetRefID(WORD _refID){ refID = _refID; };
	WORD	GetRefID(){ return refID; };
	LPTSTR	GetNamePtr(){ return name; }; // 直接ポインタを取得する。割と危険。
	void	GetName(LPTSTR buf, int bufSize=-1){
		strcpy_s(buf, (bufSize!=-1?bufSize-1:BATTLEUNIT_NAME_BYTES-1), name); 
	}
	void	SetName(LPTSTR name){
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, name); 
	}
	void	SetAttr(BYTE _attr){ attr = _attr; };
	BYTE	GetAttr(){ return attr; };
	void	SetExp(DWORD _exp){ exp = _exp; };
	DWORD	GetExp(){ return exp; };
	// パラメータ
	void	SetParam(int index, int value){
		if(index >= 0 && index < NUM_ENEMYPARAM_DATA){
			param[index] = value; 
		}
	};
	int		GetParam(int index){
		if(index >= 0 && index < NUM_ENEMYPARAM_DATA){
			return param[index]; 
		}
		return BATTLEUNIT_PARAM_ERROR;
	};
	// 各パラメータの参照
	void	SetHP(int value){ param[ENEMYPARAM_HP] = value; };
	void	SetAtk(int value){ param[ENEMYPARAM_ATK] = value; };
	void	SetDef(int value){ param[ENEMYPARAM_DEF] = value; };
	void	SetSpd(int value){ param[ENEMYPARAM_SPD] = value; };
	void	SetMgc(int value){ param[ENEMYPARAM_MGC] = value; };
	void	SetTec(int value){ param[ENEMYPARAM_TEC] = value; };
	int		GetHP(){ return param[ENEMYPARAM_HP]; };
	int		GetAtk(){ return param[ENEMYPARAM_ATK]; };
	int		GetDef(){ return param[ENEMYPARAM_DEF]; };
	int		GetSpd(){ return param[ENEMYPARAM_SPD]; };
	int		GetMgc(){ return param[ENEMYPARAM_MGC]; };
	int		GetTec(){ return param[ENEMYPARAM_TEC]; };



	// 行動パターンをインデックスで指定
	void	SetActionPattern(int index, int paramIndex, int value);
	int		GetActionPattern(int index, int paramIndex);
	ENEMYACTIONPATTERN*	GetActionPatternPtr(int index);
	// 行動パターンを直接指定
	void	SetActionType(int index, WORD type){ actionPtn[index].actionType = type; };
	void	SetActionSkillID(int index, DWORD skillID){
		actionPtn[index].skillID = skillID; 
	};
	void	SetActionTarget(int index, BYTE type){ actionPtn[index].targetType = type; };
	void	SetActionPriority(int index, WORD p){ actionPtn[index].priority = p; };
	WORD	GetActionType(int index){ return actionPtn[index].actionType; };
	DWORD	GetActionSkillID(int index){ return actionPtn[index].skillID; };
	BYTE	GetActionTarget(int index){ return actionPtn[index].targetType; };
	WORD	GetActionPriority(int index){ return actionPtn[index].priority; };
	// 行動パターンの参照を返す
	ENEMYACTIONPATTERN* GetActPatternPtr(){ return actionPtn; };
	// 行動パターンの条件
	void	SetActConditionPattern(int index, int conditionIndex, int type);
	int		GetActConditionPattern(int index, int conditionIndex);
	void	SetActConditionParam(
		int index, int conditionIndex, int paramIndex, int value);
	int		GetActConditionParam(
		int index, int conditionIndex, int paramIndex);
};

// Data_EnemyParamクラス。
// 全ての敵の情報を保持する。
// FlexListとしてData_EnemyParam_Eachクラスの配列を持つ。
class Data_EnemyParam{
private:
	VectorList<Data_EnemyParam_Each>		enemyList;
public:
	// コンストラクタ
	Data_EnemyParam();
	// 内容をファイルから読み込む
	bool Load();
	bool LoadDataFromCsv();

	// 敵パラメータへのポインタを取得する。
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyParam_Each* GetEnemyParam(WORD _refID);
};


#endif // DATA_ENEMYPARAM