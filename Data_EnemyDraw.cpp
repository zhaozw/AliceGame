// Data_EnemyDraw.cpp

#include "Data_EnemyDraw.h"

#include <fstream>

#include "CsvReader.h"
#include "Image.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYDRAWFILE		100

extern Image		g_image;

Data_EnemyDraw::Data_EnemyDraw(){
	drawList.Release();
}


bool Data_EnemyDraw::Load(){
#ifndef MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#endif // USE_ENCODED_CSV
}

bool Data_EnemyDraw::LoadDataFromCsv(){
	// リストの解放
	drawList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// グループの内容を一時的に保持する変数
	Data_EnemyDraw_Data		tmpDraw;

	strcpy_s(fileName, MAX_PATH-1, CSVFILE_ENEMYDRAW);
	if(reader.Open(fileName)){
		// ダミー行
		reader.NextLine();
		// csvファイルを読み込んでグループに格納する
		for(int n=0; n<MAX_ENEMYDRAWFILE; n++){
			tmpDraw = DATA_ENEMYDRAW_DATA();
			// レファレンス用IDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpDraw.refID = (WORD)reader.GetIntValue(1, 0);
				// 画像サイズを取得
				tmpDraw.iWidth = reader.GetIntValue(2, 1);
				tmpDraw.iHeight = reader.GetIntValue(3, 1);
				// 描画基準位置を取得
				tmpDraw.cx = reader.GetFloatValue(4, 0);
				tmpDraw.cy = reader.GetFloatValue(5, 0);
				// 拡大倍率を取得
				tmpDraw.baseExRate = reader.GetFloatValue(6, 1.0);

				// 取得したグループをデータベースにセットする
				drawList.AddData(tmpDraw);
			}
		}
	}else{
		return false;
	}
	return true;
}

bool Data_EnemyDraw::LoadDataFromDat(){
	// ファイルを開く
	std::basic_ifstream<TCHAR> fin;
	fin.open(DATFILE_ENEMYDRAW,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "読み込み用ファイルが開けませんでした。\n");
		return false;
	}

	DATA_ENEMYDRAW_DATA			copiedData;
	DWORD dataSize = 0;
	fin.read((char*)&dataSize, sizeof(DWORD));
	// データの数、またifstreamがおかしくない限りデータの読み込みを行う
	for(DWORD n=0; n<dataSize && !fin.eof() && fin; n++){
		fin.read((char*)&copiedData, sizeof(DATA_ENEMYDRAW_DATA));
		drawList.AddData(copiedData);
	}

	// 画像ハンドルの結びつけは毎回手動で行う必要がある
	DATA_ENEMYDRAW_DATA*		pData;
	for(int n=0; n<drawList.GetSize(); n++){
		pData = drawList.GetPointerByIndex(n);
		for(int i=0; i<DOLL_ATTR_NUM; i++){
			pData->hImg[i] = GetImgHandleByRefID(pData->refID, i);
		}
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

bool Data_EnemyDraw::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorListのデータ部分を書き出す
	// ファイルに書き出す
	// ファイルを開く
	std::basic_ofstream<TCHAR> fout;
	fout.open(DATFILE_ENEMYDRAW,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
		return false;
	}

	// 暗号化のためのコピーを行うバッファ
	// (2014年夏コミでは暗号化を行わない
	DATA_ENEMYDRAW_DATA			copiedData;
	DATA_ENEMYDRAW_DATA*		dataPtr;
	// 人形の数だけデータの書き出しを行う
	DWORD length = drawList.GetSize();
	// データの個数を最初に書き出す
	fout.write((char*)&length, sizeof(DWORD));
	for(DWORD n=0; n<length; n++){
		// 実体を返す
		dataPtr = drawList.GetPointerByIndex(n);
		copiedData = *dataPtr;
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYDRAW_DATA));
	}
	// 書き出し終了
	fout.close();
	return true;


	/*
	DWORD fileSize = 0;
	void* dataPtr = NULL;
	std::basic_ofstream<TCHAR> fout;
	// dataPtr = drawList.SaveToString(&fileSize);

	if(fileSize != 0){
		// ファイルを開く
		fout.open(DATFILE_ENEMYDRAW,
			std::ios::out|std::ios::binary|std::ios::trunc);
		if(!fout){
			_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
			return false;
		}
		// データを書き出す
		fout.write((char*)dataPtr, fileSize);
		// 書き出し終了
		fout.close();
		// 確保した領域の開放
		VirtualFree(dataPtr, fileSize, MEM_DECOMMIT);
	}
	return true;
	*/
}

int Data_EnemyDraw::GetImgHandleByRefID(WORD refID, BYTE attr){
	// 敵のID及び属性と画像の対応を決める。
	// 同じ画像を参照していてもかまわない。
	switch(refID){
	case ENEMYDRAW_SMALLFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_FAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_L_SNAIL:
		return g_image.enemy.snail[attr];
		break;
	case ENEMYDRAW_F_BUTTERFLY:
		return g_image.enemy.butterfly[attr];
		break;
	case ENEMYDRAW_SHIKABANE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_WINDCROW:
		return g_image.enemy.crow[attr];
		break;
	case ENEMYDRAW_HARPY:
		return g_image.enemy.harpy[attr];
		break;
	case ENEMYDRAW_HEALFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_INNOCENTBONE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_NECROMANCER:
		return g_image.enemy.cardinal;
		break;
	default:
		break;
	}
	return 0;
}

Data_EnemyDraw_Data* Data_EnemyDraw::GetEnemyDraw(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyDraw_Data* pResult = NULL;
	int maxSize = drawList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = drawList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->refID == _refID){
				// 欲しいIDと一致するものがあればそれを返す
				return pResult;
			}
		}
	}
	return NULL;
}
