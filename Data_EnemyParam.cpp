// Data_EnemyParam.cpp

#include "Data_EnemyParam.h"

#include <fstream>

#include "Game_AliceDoll.h"
#include "CsvReader.h"
#include "Static_CompileMode.h"

#define MAX_ENEMYPARAMFILE		999

Data_EnemyParam_Each::Data_EnemyParam_Each(){
	data = DATA_ENEMYPARAM_EACH_DATA();
}

// アクセサ関連
void Data_EnemyParam_Each::SetActionPattern(int index, int paramIndex, int value){
	if(paramIndex < 0 || paramIndex >= ACTIONPATTERN_PARAMNUM){
		return;
	}
	switch(paramIndex){
	case ACTIONPATTERN_ACTIONTYPE:
		SetActionType(index, (WORD)value);
		break;
	case ACTIONPATTERN_SKILLID:
		SetActionSkillID(index, (WORD)value);
		break;
	case ACTIONPATTERN_ECOMMANDTARGET:
		SetActionTarget(index, (BYTE)value);
		break;
	case ACTIONPATTERN_PRIORITY:
		SetActionPriority(index, (WORD)value);
		break;
	}
}
int	Data_EnemyParam_Each::GetActionPattern(int index, int paramIndex){
	if(paramIndex < 0 || paramIndex >= ACTIONPATTERN_PARAMNUM){
		return -9999;
	}
	switch(paramIndex){
	case ACTIONPATTERN_ACTIONTYPE:
		(int)GetActionType(index);
		break;
	case ACTIONPATTERN_SKILLID:
		(int)GetActionSkillID(index);
		break;
	case ACTIONPATTERN_ECOMMANDTARGET:
		(int)GetActionTarget(index);
		break;
	case ACTIONPATTERN_PRIORITY:
		(int)GetActionPriority(index);
		break;
	}
	return 0;
}

ENEMYACTIONPATTERN* Data_EnemyParam_Each::GetActionPatternPtr(int index){
	if(index < 0 || index >= MAX_ACTIONPATTERN){
		return NULL;
	}
	if(data.actionPtn[index].priority == 0){
		return NULL;
	}
	return &data.actionPtn[index];
}

void Data_EnemyParam_Each::SetActConditionPattern(
	int index, int conditionIndex, int type){
	data.actionPtn[index].conditionType[conditionIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionPattern(
	int index, int conditionIndex){
	return data.actionPtn[index].conditionType[conditionIndex];
}

void Data_EnemyParam_Each::SetActConditionParam(
	int index, int conditionIndex, int paramIndex, int type){
	data.actionPtn[index].conditionParam[conditionIndex][paramIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionParam(
	int index, int conditionIndex, int paramIndex){
	return data.actionPtn[index].conditionParam[conditionIndex][paramIndex];
}

Data_EnemyParam::Data_EnemyParam() : enemyList(){
}

bool Data_EnemyParam::Load(){
	enemyList.Reserve(DATANUM_ENEMYPARAM);
#ifdef MYGAME_USE_ENCODED_CSV
	return LoadDataFromDat();
#else // MYGAME_USE_ENCODED_CSV
	return LoadDataFromCsv();
#endif // MYGAME_USE_ENCODED_CSV
}

bool Data_EnemyParam::LoadDataFromCsv(){
	// リストの解放
	enemyList.Release();
	// Csvを読み込むクラス
	CsvReader				reader;
	// ファイル名を保持する
	TCHAR					fileName[MAX_PATH];
	// グループの内容を一時的に保持する変数
	Data_EnemyParam_Each	tmpEnemy;
	// ファイルが存在しない場合が何度か続いたらループを抜ける
	int						nEmptyFile = 0;
	// 何番目の敵インデックスまで埋まっているか
	int						index = 0;
	int						actionIndex = 0;

	for(int n=1; n<=MAX_ENEMYPARAMFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, CSVFILE_ENEMYPARAM, n);
		// csvファイルを読み込んでグループに格納する
		if(reader.Open(fileName)){
			tmpEnemy = Data_EnemyParam_Each();
			nEmptyFile = 0; // 空ファイル数のリセット
			index = 0;
			// ダミー行
			reader.NextLine();
			// レファレンス用IDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpEnemy.data.refID = (WORD)reader.GetIntValue(0, 0);
			}
			// ダミー行
			reader.NextLine();
			// 敵の名前と属性と経験値を取得する
			if(reader.Read() == CSV_READ_NOERROR){
				// バッファに直接値を入れる
				reader.GetValue(0, tmpEnemy.data.name, BATTLEUNIT_NAME_BYTES-1);
				// 属性を読み取る
				tmpEnemy.data.attr = (BYTE)reader.GetIntValue(1, DOLL_ATTR_NONE);
				// 経験値を読み取る
				tmpEnemy.data.exp = (DWORD)reader.GetIntValue(2, 0);
			}
			// ダミー行
			reader.NextLine();
			// 敵の各パラメータを取得する
			reader.Read();
			for(int i=0; i<NUM_ENEMYPARAM_DATA; i++){
				tmpEnemy.data.param[i] = reader.GetIntValue(i, 0);
			}
			reader.NextLine();
			// ステートの配列を取得する
			for(int i=0; i<MAX_INITIALSTATE; i++){
				reader.Read();
				tmpEnemy.SetInitialState(
					i,
					reader.GetIntValue(0, 0),
					reader.GetIntValue(1, 0),
					reader.GetIntValue(2, 0));
			}
			reader.NextLine();
			// 敵の攻撃パターンを取得する
			for(int i=0; i<MAX_ACTIONPATTERN; i++){
				// 各行動は三行に分けて記述する。
				// 一行目：攻撃パターン名、スキルID、ターゲットのタイプ、優先度
				// 二行目、三行目：条件、条件に関するパラメータ(3つ)
				reader.Read();
				// 一行目
				tmpEnemy.SetActionPattern(i, 0,
					GetActionTypeFromChar(reader.GetCharacter(0)));
				tmpEnemy.SetActionPattern(i, 1,
					(DWORD)reader.GetIntValue(1, 0));
				tmpEnemy.SetActionPattern(i, 2,
					(BYTE)reader.GetIntValue(2, 0));
				tmpEnemy.SetActionPattern(i, 3,
					(WORD)reader.GetIntValue(3, 0));
				// 二行目、三行目
				for(int j=0; j<MAX_CONDITION; j++){
					reader.Read();
					tmpEnemy.SetActConditionPattern(
						i, j, reader.GetIntValue(0, 0));
					for(int k=0; k<MAX_CONDITIONPARAM; k++){
						tmpEnemy.SetActConditionParam(
							i, j, k, reader.GetIntValue(1+k, 0));
					}
				}
				// ダミー行
				reader.NextLine();
			}
			// 取得したグループをデータベースにセットする
			enemyList.AddData(tmpEnemy);
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

bool Data_EnemyParam::LoadDataFromDat(){
	// ファイルを開く
	std::basic_ifstream<TCHAR>	fin;
	TCHAR						fileName[MAX_PATH];

	DATA_ENEMYPARAM_EACH_DATA		copiedData;
	Data_EnemyParam_Each			data;
	// データの数、またifstreamがおかしくない限りデータの読み込みを行う
	for(DWORD n=0; n<MAX_ENEMYPARAMFILE; n++){
		wsprintf(fileName, DATFILE_ENEMYPARAM, n);
		fin.open(fileName,
			std::ios::in|std::ios::binary);
		if(fin){
			fin.read((char*)&copiedData, sizeof(DATA_ENEMYPARAM_EACH_DATA));
			data.data = copiedData;
			enemyList.AddData(data);
		}else{
		}
		fin.close();
		fin.clear();
	}
	return true;
}

bool Data_EnemyParam::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	// VectorListのデータ部分を書き出す
	// ファイルに書き出す

	TCHAR						fileName[MAX_PATH];
	std::basic_ofstream<TCHAR>	fout;

	// 暗号化のためのコピーを行うバッファ
	// (2014年夏コミでは暗号化を行わない
	DATA_ENEMYPARAM_EACH_DATA			copiedData;
	Data_EnemyParam_Each*				dataPtr;
	// 人形の数だけデータの書き出しを行う
	DWORD length = enemyList.GetSize();
	// データの個数を最初に書き出す
	for(DWORD n=0; n<length; n++){
		// 実体を返す
		dataPtr = enemyList.GetPointerByIndex(n);
		copiedData = dataPtr->data;
		wsprintf(fileName, DATFILE_ENEMYPARAM, n);
		fout.open(fileName,
			std::ios::out|std::ios::binary|std::ios::trunc);
		if(!fout){
			_RPTF0(_CRT_WARN, "書き出し用ファイルが開けませんでした。\n");
			return false;
		}
		fout.write((char*)&copiedData, sizeof(DATA_ENEMYPARAM_EACH_DATA));
		fout.close();
		fout.clear();
	}
	return true;
}

WORD Data_EnemyParam::GetActionTypeFromChar(TCHAR c){
	switch(c){
	case 'A':
		return COMMANDTYPE_ATTACK;
		break;
	case 'S':
		return COMMANDTYPE_SKILL;
		break;
	case 'G':
		return COMMANDTYPE_GUARD;
		break;
	case 'W':
	default:
		return COMMANDTYPE_NONE;
		break;
	}
}


Data_EnemyParam_Each* Data_EnemyParam::GetEnemyParam(WORD _refID){
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyParam_Each* pResult;
	int maxSize = enemyList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = enemyList.GetPointerByIndex(n);
		if(pResult->data.refID == _refID){
			// 欲しいIDと一致するものがあればそれを返す
			return pResult;
		}
	}
	return NULL;
}