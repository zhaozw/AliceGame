// Data_EnemyGroup.cpp

#include "Data_EnemyGroup.h"
#include "CsvReader.h"

#define MAX_ENEMYGROUPFILE		999

// グループの初期化
Data_EnemyGroup_Each::Data_EnemyGroup_Each(){
	Refresh();
}

void Data_EnemyGroup_Each::Refresh(){
	refID = 0;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		enemy[n].refID = 0;
		enemy[n].drawX = 0;
		enemy[n].drawY = 0;
	}
}


Data_EnemyGroup::Data_EnemyGroup(){
}

bool Data_EnemyGroup::Load(){
	return LoadDataFromCsv();
}

bool Data_EnemyGroup::LoadDataFromCsv(){
	// リストの解放
	groupList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// グループの内容を一時的に保持する変数
	Data_EnemyGroup_Each	tmpGroup;
	// ファイルが存在しない場合が何度か続いたらループを抜ける
	int						nEmptyFile = 0;
	// 何番目の敵インデックスまで埋まっているか
	int						index = 0;

	for(int n=1; n<=MAX_ENEMYGROUPFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, "dat_egroup\\group%03d.csv", n);
		// csvファイルを読み込んでグループに格納する
		if(reader.Open(fileName)){
			nEmptyFile = 0; // 空ファイル数のリセット
			index = 0;
			tmpGroup.Refresh();
			// ダミー行
			reader.NextLine();
			// グループIDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpGroup.SetRefID((WORD)reader.GetIntValue(0, 0));
			}
			// ダミー行
			reader.NextLine();
			// 敵のIDとその描画位置を取得する
			for(int i=0; i<MAX_BATTLEENEMY; i++){
				if(reader.Read() == CSV_READ_NOERROR){
					if(reader.GetIntValue(0, 0) != 0){
						tmpGroup.SetEnemyRefID(index, (WORD)reader.GetIntValue(0, 0));
						tmpGroup.SetEnemyDrawX(index, (WORD)reader.GetIntValue(1, 0));
						tmpGroup.SetEnemyDrawY(index, (WORD)reader.GetIntValue(2, 0));
						index++;
					}
				}
			}
			// 取得したグループをデータベースにセットする
			groupList.AddData(tmpGroup);
		}else{
			nEmptyFile++;
			if(nEmptyFile > 100){
				// 空ファイルが続いた場合、ループを抜ける
				break;
			}
		}
	}
	return true;
}

Data_EnemyGroup_Each* Data_EnemyGroup::GetEnemyGroup(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyGroup_Each* pResult = NULL;
	int maxSize = groupList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = groupList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// 欲しいIDと一致するものがあればそれを返す
				return pResult;
			}
		}
	}
	return NULL;
}

