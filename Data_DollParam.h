#ifndef DATA_DOLLPARAM_H
#define DATA_DOLLPARAM_H

#include <Windows.h>
#include "Static_AliceDoll.h"

// 人形のレベルとパラメータの関係に関するデータを保持するクラス。
// グローバル変数g_dollParamから参照される。

#define DOLL_TYPENAME_BYTES		18
#define DATFILE_DOLLPARAM		"dat\\doll.dat"

// 内部レベルをパラメータに変換する際の数式の係数の構造体。
// レベルをxとして、パラメータはax^2+bx+cで表される。
typedef struct LevelToParam{
	float a;
	float b;
	float c;
	LevelToParam(){
		a = 0;
		b = 0;
		c = 0;
	}
} LEVELTOPARAM;

// レベルアップボーナスの1レベルあたりの値を保持する構造体。
typedef struct LevelUpBonus{
	int		growth[DOLL_PARAM_MAX];		// 成長レベルの上昇値。
	WORD	skillID;					// 覚えるスキル。0以外の値だと覚える。
	LevelUpBonus(){
		for(int n=0; n<DOLL_PARAM_MAX; n++){
			growth[n] = 0;
		}
		skillID = 0;
	}
} LEVELUPBONUS;

// 各人形のパラメータ。
class Data_DollParam_Each{
protected:
	// 人形のタイプ名。
	TCHAR			typeName[DOLL_TYPENAME_BYTES];
	// データ。
	// レベルをパラメータに換算する式。
	LEVELTOPARAM	LvToP[DOLL_PARAM_MAX];
	LEVELUPBONUS	LvBonus[DOLL_LEVEL_MAX];

public:
	// コンストラクタ
	Data_DollParam_Each();
	// データベースファイルからデータの読み込みを行う。
	bool Load(LPTSTR fileName);
	// 内部レベル、パラメータ種を指定すると
	// パラメータの数値を返す。
	int GetParamFromLv(BYTE paramType, int lv);

	// 構造体へのアクセサ
	LEVELTOPARAM	GetLvToP(int paramType){ return LvToP[paramType]; }; 
	LEVELUPBONUS	GetLvBonus(int lv){ return LvBonus[lv]; }; 
	void			SetLvToP(int paramType, LEVELTOPARAM p){ LvToP[paramType] = p; };
	void			SetLvBonus(int lv, LEVELUPBONUS p){ LvBonus[lv] = p; };
	// 名前を返す。
	void GetName(LPTSTR buf, int bufSize);
	// 名前をセットする。
	void SetName(LPTSTR name);

};

class Data_DollParam{
protected:
	Data_DollParam_Each		dollList[DOLL_TYPE_MAX];		//
public:
	// コンストラクタ
	Data_DollParam();

	// 人形の名前を返す。
	void GetTypeName(BYTE index, LPTSTR buf, int bufSize){
		dollList[index-1].GetName(buf, bufSize); };
	
	// 人形タイプID、内部レベル、パラメータ種を指定すると
	// パラメータの数値を返す。
	int GetParamFromLv(BYTE dollType, BYTE paramType, int lv);


	// ロード
	// 全人形のデータをロードする。
	bool Load();

	// csvファイルから読み込む場合
	bool LoadDataFromCsv();

	// datファイルから読み込む場合
	bool LoadDataFromDat();

	// Csvデータを暗号化してファイルに書き出す。
	bool EncodeCsv();

};

#endif // DATA_DOLLPARAM_H