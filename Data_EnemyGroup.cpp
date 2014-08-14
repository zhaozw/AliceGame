// Data_EnemyGroup.cpp

#include "Data_EnemyGroup.h"

#include <fstream>

#include "CsvReader.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYGROUPFILE		999


Data_EnemyGroup::Data_EnemyGroup(){
}

bool Data_EnemyGroup::Load(){
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_EnemyGroup::LoadDataFromCsv(){
	// リストの解放
	groupList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// グループの内容を一時的に保持する変数
	Data_EnemyGroup_Data	tmpGroup;
	// ファイルが存在しない場合が何度か続いたらループを抜ける
	int						nEmptyFile = 0;
	// 何番目の敵インデックスまで埋まっているか
	int						index = 0;

	for(int n=1; n<=MAX_ENEMYGROUPFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, CSVFILE_ENEMYGROUP, n);
		// csvファイルを読み込んでグループに格納する
		if(reader.Open(fileName)){
			nEmptyFile = 0; // 空ファイル数のリセット
			index = 0;
			tmpGroup = DATA_ENEMYGROUP_DATA();
			// ダミー行
			reader.NextLine();
			// グループIDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpGroup.refID = ((WORD)reader.GetIntValue(0, 0));
			}
			// ダミー行
			reader.NextLine();
			// 敵のIDとその描画位置及び属性を取得する
			for(int i=0; i<MAX_BATTLEENEMY; i++){
				if(reader.Read() == CSV_READ_NOERROR){
					if(reader.GetIntValue(0, 0) != 0){
						tmpGroup.enemy[index].refID = (WORD)reader.GetIntValue(0, 0);
						tmpGroup.enemy[index].drawX = (WORD)reader.GetIntValue(1, 0);
						tmpGroup.enemy[index].drawY = (WORD)reader.GetIntValue(2, 0);
						tmpGroup.enemy[index].attr = (BYTE)reader.GetIntValue(3, 0);
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

bool Data_EnemyGroup::LoadDataFromDat(){
	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_ENEMYGROUP,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "読み込み用ファイルが開けませんでした。\n");
		return false;
	}

	DATA_ENEMYGROUP_DATA			copiedData;
	DWORD dataSize = 0;
	fin.read((char*)&dataSize, sizeof(DWORD));
	// データの数、またifstreamがおかしくない限りデータの読み込みを行う
	for(DWORD n=0; n<dataSize && !fin.eof() && fin; n++){
		fin.read((char*)&copiedData, sizeof(DATA_ENEMYGROUP_DATA));
		groupList.AddData(copiedData);
	}

	// エラーの確認
	if(!fin){
		fin.close();
		return false;
	}

	// 読み込み終了
	fin.close();

	return true;
}

bool Data_EnemyGroup::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorListのデータ部分を書き出す
	// ファイルに書き出す
	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_ENEMYGROUP,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
		return false;
	}

	// 暗号化のためのコピーを行うバッファ
	// (2014年夏コミでは暗号化を行わない
	DATA_ENEMYGROUP_DATA			copiedData;
	DATA_ENEMYGROUP_DATA*			dataPtr;
	// 人形の数だけデータの書き出しを行う
	DWORD length = groupList.GetSize();
	// データの個数を最初に書き出す
	fout.write((char*)&length, sizeof(DWORD));
	for(DWORD n=0; n<length; n++){
		// 実体を返す
		dataPtr = groupList.GetPointerByIndex(n);
		copiedData = *dataPtr;
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYGROUP_DATA));
	}
	// 書き出し終了
	fout.close();
	return true;
}

Data_EnemyGroup_Data* Data_EnemyGroup::GetEnemyGroup(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyGroup_Data* pResult = NULL;
	int maxSize = groupList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = groupList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->refID == _refID){
				// 欲しいIDと一致するものがあればそれを返す
				return pResult;
			}
		}
	}
	return NULL;
}

