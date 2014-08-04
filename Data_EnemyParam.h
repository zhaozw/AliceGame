#ifndef DATA_ENEMYPARAM_H
#define DATA_ENEMYPARAM_H

#include <Windows.h>
#include "Static_Battle.h"
#include "VectorList.h"

// 敵キャラの能力値のデータベースを扱うクラス。
//データはグローバル変数d_enemyParamから参照される。

// 定数
#define MAX_CONDITION			2	// 複数条件を指定可能
#define MAX_CONDITIONPARAM		3	// 条件あたりのパラメータの数
#define MAX_ACTIONPATTERN		16	// 攻撃パターンの数
#define MAX_INITIALSTATE		8	// 最初から持っているステートの最大数

// 行動パターンに関するパラメータをまとめて指定する用
#define ACTIONPATTERN_ACTIONTYPE	0
#define ACTIONPATTERN_SKILLID		1
#define ACTIONPATTERN_ECOMMANDTARGET	2
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
		actionType		= COMMANDTYPE_NONE;
		skillID			= 0;
		targetType		= ECOMMANDTARGET_NONE;
		priority		= 0;
		for(int j=0; j<MAX_CONDITION; j++){
			conditionType[j] = CONDITIONTYPE_ALWAYS;
			for(int i=0; i<MAX_CONDITIONPARAM; i++){
				conditionParam[j][i] = 0;
			}
		}
	}
}ENEMYACTIONPATTERN;

typedef struct EnemyInitialState{
	WORD	refID;
	int		param;
	int		param2;
	EnemyInitialState(){
		refID = 0;
		param = 0;
		param2 = 0;
	}
} ENEMYINITIALSTATE;

// Data_EnemyParam_Eachクラス。
// 敵一体についての情報を保持する。
// 実際には、このクラスの配列を持つFlexListが作成される。
class Data_EnemyParam_Each{
private:
	WORD		refID;							// 参照される時のID
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// 名前
	int			param[NUM_ENEMYPARAM_DATA];		// 各能力値(HPを除く)
	BYTE		attr;							// 属性
	DWORD		exp;							// 経験値
	// 行動パターンの配列
	ENEMYACTIONPATTERN		actionPtn[MAX_ACTIONPATTERN];
	// 初期状態で持っているステート及びパラメータの配列
	ENEMYINITIALSTATE		stateArray[MAX_INITIALSTATE];
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

	void	SetInitialState(int index, WORD refID, int param, int param2){
		stateArray[index].refID = refID;
		stateArray[index].param = param;
		stateArray[index].param2 = param2;
	};

	WORD	GetInitialStateRefID(int index){ return stateArray[index].refID; };
	int		GetInitialStateParam(int index){ return stateArray[index].param; };
	int		GetInitialStateParam2(int index){ return stateArray[index].param2; };


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

	void ReleaseList(){ enemyList.Release(); };

	// 文字からアクションタイプに変換する。
	// A : 攻撃
	// S : 特技
	// G : 防御
	// W, エラー : 何もしない
	WORD GetActionTypeFromChar(TCHAR c);


	// 敵パラメータへのポインタを取得する。
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyParam_Each* GetEnemyParam(WORD _refID);


	// 大きさを返す。
	int GetSize(){ return enemyList.GetSize(); };
};


#endif // DATA_ENEMYPARAM