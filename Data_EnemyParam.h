#ifndef DATA_ENEMYPARAM_H
#define DATA_ENEMYPARAM_H

#include <Windows.h>
#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

// 敵キャラの能力値のデータベースを扱うクラス。
//データはグローバル変数d_enemyParamから参照される。

// ファイル名
#define CSVFILE_ENEMYPARAM		"dat_enemy\\enemy%03d.csv"
#define DATFILE_ENEMYPARAM		"dat\\enemy%03d.dat"

// 定数
#define MAX_CONDITION			2	// 複数条件を指定可能
#define MAX_CONDITIONPARAM		3	// 条件あたりのパラメータの数
#define MAX_ACTIONPATTERN		16	// 攻撃パターンの数
#define MAX_INITIALSTATE		8	// 最初から持っているステートの最大数

// 行動パターンに関するパラメータをまとめて指定する用
#define ACTIONPATTERN_ACTIONTYPE			0
#define ACTIONPATTERN_SKILLID				1
#define ACTIONPATTERN_ECOMMANDTARGET		2
#define ACTIONPATTERN_PRIORITY				3
#define ACTIONPATTERN_PARAMNUM				4

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

typedef struct Data_EnemyParam_Each_Data{
	WORD		refID;							// 参照される時のID
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// 名前
	int			param[NUM_ENEMYPARAM_DATA];		// 各能力値(HPを除く)
	BYTE		attr;							// 属性
	DWORD		exp;							// 経験値
	// 行動パターンの配列
	ENEMYACTIONPATTERN		actionPtn[MAX_ACTIONPATTERN];
	// 初期状態で持っているステート及びパラメータの配列
	ENEMYINITIALSTATE		stateArray[MAX_INITIALSTATE];
	Data_EnemyParam_Each_Data(){
		refID = 0;
		attr = DOLL_ATTR_NONE;
		exp = 0;
		for(int n=0; n<BATTLEUNIT_PARAM_NUM-1; n++){
			param[n] = 0;
		}
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, "");
		// 各攻撃パターンのリセット
		for(int n=0; n<MAX_ACTIONPATTERN; n++){
			actionPtn[n].actionType = COMMANDTYPE_ERROR;
			actionPtn[n].skillID = 0;
			actionPtn[n].targetType = ACTIONTARGET_NONE;
			actionPtn[n].priority = 0;
			// 攻撃条件のリセット
			for(int i=0; i<MAX_CONDITION; i++){
				actionPtn[n].conditionType[i] = CONDITIONTYPE_ALWAYS;
				for(int j=0; j<MAX_CONDITIONPARAM; j++){
					actionPtn[n].conditionParam[i][j] = 0;
				}
			}
		}
	}
} DATA_ENEMYPARAM_EACH_DATA;

// Data_EnemyParam_Eachクラス。
// 敵一体についての情報を保持する。
// 実際には、このクラスの配列を持つFlexListが作成される。
class Data_EnemyParam_Each{
public:
	DATA_ENEMYPARAM_EACH_DATA	data;
public:
	// コンストラクタ
	Data_EnemyParam_Each();
	void	GetName(LPTSTR buf, int bufSize=-1){
		strcpy_s(buf, (bufSize!=-1?bufSize-1:BATTLEUNIT_NAME_BYTES-1), data.name); 
	}
	void	SetName(LPTSTR name){
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, data.name); 
	}
	// 各パラメータの参照
	void	SetHP(int value){	data.param[ENEMYPARAM_HP] = value; };
	void	SetAtk(int value){	data.param[ENEMYPARAM_ATK] = value; };
	void	SetDef(int value){	data.param[ENEMYPARAM_DEF] = value; };
	void	SetSpd(int value){	data.param[ENEMYPARAM_SPD] = value; };
	void	SetMgc(int value){	data.param[ENEMYPARAM_MGC] = value; };
	void	SetTec(int value){	data.param[ENEMYPARAM_TEC] = value; };
	int		GetHP(){	return data.param[ENEMYPARAM_HP]; };
	int		GetAtk(){	return data.param[ENEMYPARAM_ATK]; };
	int		GetDef(){	return data.param[ENEMYPARAM_DEF]; };
	int		GetSpd(){	return data.param[ENEMYPARAM_SPD]; };
	int		GetMgc(){	return data.param[ENEMYPARAM_MGC]; };
	int		GetTec(){	return data.param[ENEMYPARAM_TEC]; };

	void	SetInitialState(int index, WORD refID, int param, int param2){
		data.stateArray[index].refID = refID;
		data.stateArray[index].param = param;
		data.stateArray[index].param2 = param2;
	};
	WORD	GetInitialStateRefID(int index){ return data.stateArray[index].refID; };
	int		GetInitialStateParam(int index){ return data.stateArray[index].param; };
	int		GetInitialStateParam2(int index){ return data.stateArray[index].param2; };

	// 行動パターンをインデックスで指定
	void	SetActionPattern(int index, int paramIndex, int value);
	int		GetActionPattern(int index, int paramIndex);
	ENEMYACTIONPATTERN*	GetActionPatternPtr(int index);
	// 行動パターンを直接指定
	void	SetActionType(int index, WORD type){ data.actionPtn[index].actionType = type; };
	void	SetActionSkillID(int index, DWORD skillID){
		data.actionPtn[index].skillID = skillID; 
	};
	void	SetActionTarget(int index, BYTE type){ data.actionPtn[index].targetType = type; };
	void	SetActionPriority(int index, WORD p){ data.actionPtn[index].priority = p; };
	WORD	GetActionType(int index){ return data.actionPtn[index].actionType; };
	DWORD	GetActionSkillID(int index){ return data.actionPtn[index].skillID; };
	BYTE	GetActionTarget(int index){ return data.actionPtn[index].targetType; };
	WORD	GetActionPriority(int index){ return data.actionPtn[index].priority; };
	// 行動パターンの参照を返す
	ENEMYACTIONPATTERN* GetActPatternPtr(){ return data.actionPtn; };
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
	bool LoadDataFromDat();

	// 暗号化
	bool EncodeCsv();

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