// Data_DollParam.cpp

#include "Data_DollParam.h"

#include <Windows.h>
#include <string.h>
#include <tchar.h>
#include <fstream>

#include "CsvReader.h"
#include "Static_CompileMode.h"

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

void Data_DollParam_Each::GetName(LPTSTR buf, int bufSize){
	strcpy_s(buf, bufSize-1, typeName);
}

void Data_DollParam_Each::SetName(LPTSTR name){
	strcpy_s(typeName, DOLL_TYPENAME_BYTES-1, name);
}


//======================================================
// Data_DollParamクラス

Data_DollParam::Data_DollParam() : dollList(){
}

bool Data_DollParam::Load(){
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_DollParam::LoadDataFromCsv(){
	TCHAR	fileName[MAX_PATH]; 
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		wsprintf(fileName, _T("dat_doll\\doll%02d.csv"), n+1);
		if(!dollList[n].Load(fileName)){
			return false;
		}
	}
	return true;
}

bool Data_DollParam::LoadDataFromDat(){
	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_DOLLPARAM,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "読み込み用ファイルが開けませんでした。\n");
		return false;
	}

	TCHAR			copiedTypeName[DOLL_TYPENAME_BYTES];
	LEVELTOPARAM	copiedLTP;
	LEVELUPBONUS	copiedBonus;
	// 人形の数だけデータの書き出しを行う
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		fin.read((char*)copiedTypeName, sizeof(TCHAR)*DOLL_TYPENAME_BYTES);
		dollList[n].SetName(copiedTypeName);
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			fin.read((char*)&copiedLTP, sizeof(LEVELTOPARAM));
			dollList[n].SetLvToP(i, copiedLTP);
		}
		for(int i=0; i<DOLL_LEVEL_MAX; i++){
			fin.read((char*)&copiedBonus, sizeof(LEVELUPBONUS));
			dollList[n].SetLvBonus(i, copiedBonus);
		}
	}

	// 読み込み終了
	fin.close();
	return true;
}

bool Data_DollParam::EncodeCsv(){
	// データを読み込む
	if(!LoadDataFromCsv()) return false;
	// ファイルに書き出す
	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_DOLLPARAM,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
		return false;
	}

	// 暗号化のためのコピーを行うバッファ
	// (2014年夏コミでは暗号化を行わない
	TCHAR		 copiedTypeName[DOLL_TYPENAME_BYTES];
	LEVELTOPARAM copiedLTP;
	LEVELUPBONUS copiedBonus;
	// 人形の数だけデータの書き出しを行う
	for(int n=0; n<DOLL_TYPE_MAX; n++){
		dollList[n].GetName(copiedTypeName, DOLL_TYPENAME_BYTES);
		fout.write((char*)copiedTypeName, sizeof(TCHAR)*DOLL_TYPENAME_BYTES);
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			copiedLTP = dollList[n].GetLvToP(i);
			fout.write((char*)&copiedLTP, sizeof(LEVELTOPARAM));
		}
		for(int i=0; i<DOLL_LEVEL_MAX; i++){
			copiedBonus = dollList[n].GetLvBonus(i);
			fout.write((char*)&copiedBonus, sizeof(LEVELUPBONUS));
		}
	}
	// 書き出し終了
	fout.close();
	return true;

}



int Data_DollParam::GetParamFromLv(BYTE dollType, BYTE paramType, int lv){
	if(dollType <= 0 || dollType > DOLL_TYPE_MAX) return -9999;
	return dollList[dollType-1].GetParamFromLv(paramType, lv);
}
