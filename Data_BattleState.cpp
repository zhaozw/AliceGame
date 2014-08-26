// Data_BattleState.cpp

#include "Data_BattleState.h"
#include "CsvReader.h"

#include "Static_CompileMode.h"

#define MAX_BATTLESTATE			999

Data_BattleState_Each::Data_BattleState_Each(){
	Refresh();
}

void Data_BattleState_Each::Refresh(){
	refID = 0;
	calcOrder = 0;
	drawOrder = 0;
	iconIndex = 0;
	flags = 0x00000000;
	strcpy_s(stateName, STATENAME_LENGTH-1, _T(""));
}

void Data_BattleState_Each::SetStateName(LPTSTR name, int size){
	strcpy_s(stateName, STATENAME_LENGTH-1, name);
}

void Data_BattleState_Each::GetStateName(LPTSTR buf, int bufSize){
	strcpy_s(buf, bufSize-1, stateName);
}

Data_BattleState::Data_BattleState(){
}

bool Data_BattleState::Load(){
	stateList.Reserve(DATANUM_STATEINFO);
	return LoadDataFromCsv();
}



bool Data_BattleState::LoadDataFromCsv(){
	// リストの解放
	stateList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// ステート名を保持する
	TCHAR					stateName[STATENAME_LENGTH];
	// グループの内容を一時的に保持する変数
	Data_BattleState_Each	tmpState;

	strcpy_s(fileName, MAX_PATH-1, CSVFILE_STATEINFO);
	if(reader.Open(fileName)){
		// ダミー行
		reader.NextLine();
		// csvファイルを読み込んでグループに格納する
		for(int n=0; n<MAX_BATTLESTATE; n++){
			tmpState.Refresh();
			// レファレンス用IDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpState.SetRefID((WORD)reader.GetIntValue(1, 0));
			}
			// 名前を取得
			reader.GetValue(0, stateName, STATENAME_LENGTH);
			tmpState.SetStateName(stateName, STATENAME_LENGTH);
			// 処理順序を取得
			tmpState.SetCalcOrder(reader.GetIntValue(2, 1));
			// 描画順序を取得
			tmpState.SetDrawOrder(reader.GetIntValue(3, 0));
			// アイコンを取得
			tmpState.SetIconIndex(reader.GetIntValue(4, 0));
			// フラグをセットする
			tmpState.SetFlags(reader.GetIntValue(5, 0));
			// 取得したグループをデータベースにセットする
			stateList.AddData(tmpState);
		}
	}else{
		return false;
	}
	return true;
}

Data_BattleState_Each* Data_BattleState::GetBattleState(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_BattleState_Each* pResult = NULL;
	int maxSize = stateList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = stateList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// 欲しいIDと一致するものがあればそれを返す
				return pResult;
			}
		}
	}
	return NULL;
}

bool Data_BattleState::CheckFlagOfState(WORD _refID, DWORD _flag){
	Data_BattleState_Each* pResult = NULL;
	pResult = GetBattleState(_refID);
	if(pResult != NULL){
		if((pResult->GetFlags() & _flag) != 0){
			return true;
		}
	}
	return false;
}