// Data_DollParam.cpp

#include "Data_DollParam.h"

#include <Windows.h>
#include <string.h>
#include <tchar.h>

#include "CsvReader.h"

//======================================================
// Data_DollParam_Eachクラス

Data_DollParam_Each::Data_DollParam_Each() : LvToP(), LvBonus(){
}

bool Data_DollParam_Each::Load(LPTSTR fileName){
	CsvReader reader;
	// ファイルを開く
	if(!reader.Open(fileName)){
		return false;
	}
	// 名前を読み込む
	reader.Read();
	reader.GetValue(0, typeName, DOLL_TYPENAME_BYTES);
	// 空行を読む
	reader.Read();
	// パラメータの上昇率を読み込む
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		// 一行読む
		reader.Read();
		// 係数3つを取得する
		// 見やすさのために0番目の要素は能力値名を使用。
		LvToP[n].a = reader.GetFloatValue(1);
		LvToP[n].b = reader.GetFloatValue(2);
		LvToP[n].c = reader.GetFloatValue(3);
	}
	// 空行を読む
	reader.Read();
	// レベルアップボーナスを読み込む
	for(int n=0; n<DOLL_LEVEL_MAX; n++){
		// 一行読む
		reader.Read();
		// 各パラメータを取得する
		for(int m=0; m<DOLL_PARAM_MAX; m++){
			LvBonus[n].growth[m] = reader.GetIntValue(m+1, 0);
		}
		LvBonus[n].skillID = reader.GetIntValue(DOLL_PARAM_MAX+1, 0);
	}
	return true;
}

int Data_DollParam_Each::GetParamFromLv(BYTE paramType, int lv){
	if(paramType >= DOLL_PARAM_MAX) return 0;
	return (int)(LvToP[paramType].a * lv*lv + LvToP[paramType].b * lv 
		+ LvToP[paramType].c); 
}

//======================================================
// Data_DollParamクラス

Data_DollParam::Data_DollParam() : dollList(){
}

bool Data_DollParam::Load(){
	TCHAR	fileName[MAX_PATH]; 
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		wsprintf(fileName, _T("dat_doll\\doll%02d.csv"), n+1);
		if(!dollList[n].Load(fileName)){
			return false;
		}
	}
	return true;
}

int Data_DollParam::GetParamFromLv(BYTE dollType, BYTE paramType, int lv){
	if(dollType <= 0 || dollType > DOLL_TYPE_MAX) return -9999;
	return dollList[dollType-1].GetParamFromLv(paramType, lv);
}
