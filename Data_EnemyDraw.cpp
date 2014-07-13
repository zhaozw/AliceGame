// Data_EnemyDraw.cpp

#include "Data_EnemyDraw.h"
#include "CsvReader.h"
#include "Image.h"

#define MAX_ENEMYDRAWFILE		100

extern Image		g_image;

Data_EnemyDraw_Each::Data_EnemyDraw_Each(){
	Refresh();
}

void Data_EnemyDraw_Each::Refresh(){
}

Data_EnemyDraw::Data_EnemyDraw(){
	drawList.Release();
}


bool Data_EnemyDraw::Load(){
	return LoadDataFromCsv();
}

bool Data_EnemyDraw::LoadDataFromCsv(){
	// リストの解放
	drawList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// グループの内容を一時的に保持する変数
	Data_EnemyDraw_Each		tmpDraw;

	strcpy_s(fileName, MAX_PATH-1, _T("dat_enemy\\enemydraw.csv"));
	if(reader.Open(fileName)){
		// ダミー行
		reader.NextLine();
		// csvファイルを読み込んでグループに格納する
		for(int n=0; n<MAX_ENEMYDRAWFILE; n++){
			tmpDraw.Refresh();
			// レファレンス用IDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpDraw.SetRefID((WORD)reader.GetIntValue(1, 0));
			}
			// 画像サイズを取得
			tmpDraw.SetIWidth(reader.GetIntValue(2, 1));
			tmpDraw.SetIHeight(reader.GetIntValue(3, 1));
			// 描画基準位置を取得
			tmpDraw.SetCX(reader.GetFloatValue(4, 0));
			tmpDraw.SetCY(reader.GetFloatValue(5, 0));
			// 拡大倍率を取得
			tmpDraw.SetExRate(reader.GetFloatValue(6, 1.0));

			// 画像を取得
			tmpDraw.SetHImg(GetImgHandleByRefID(tmpDraw.GetRefID()));
			if(tmpDraw.GetHImg() == 0){
				continue;
			}
			// 
			// 取得したグループをデータベースにセットする
			drawList.AddData(tmpDraw);
		}
	}else{
		return false;
	}
	return true;
}

int Data_EnemyDraw::GetImgHandleByRefID(WORD refID){
	switch(refID){
	case ENEMYDRAW_ELF:
		return g_image.enemy.elf;
		break;
	case ENEMYDRAW_FIREELF:
		return g_image.enemy.elf;
		break;
	default:
		break;
	}
	return 0;
}

Data_EnemyDraw_Each* Data_EnemyDraw::GetEnemyDraw(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyDraw_Each* pResult = NULL;
	int maxSize = drawList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = drawList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// 欲しいIDと一致するものがあればそれを返す
				return pResult;
			}
		}
	}
	return NULL;
}
