// Data_EnemyParam.cpp

#include "Data_EnemyParam.h"
#include "Game_AliceDoll.h"
#include "CsvReader.h"

#define MAX_ENEMYPARAMFILE		999

Data_EnemyParam_Each::Data_EnemyParam_Each(){
	Refresh();
}

void Data_EnemyParam_Each::Refresh(){
	refID = 0;
	attr = DOLL_ATTR_NONE;
	exp = 0;
	for(int n=0; n<BATTLEUNIT_PARAM_NUM-1; n++){
		param[n] = 0;
	}
	strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, _T(""));
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
	if(actionPtn[index].priority == 0){
		return NULL;
	}
	return &actionPtn[index];
}

void Data_EnemyParam_Each::SetActConditionPattern(
	int index, int conditionIndex, int type){
	actionPtn[index].conditionType[conditionIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionPattern(
	int index, int conditionIndex){
	return actionPtn[index].conditionType[conditionIndex];
}

void Data_EnemyParam_Each::SetActConditionParam(
	int index, int conditionIndex, int paramIndex, int type){
	actionPtn[index].conditionParam[conditionIndex][paramIndex] = type;
}

int Data_EnemyParam_Each::GetActConditionParam(
	int index, int conditionIndex, int paramIndex){
	return actionPtn[index].conditionParam[conditionIndex][paramIndex];
}

Data_EnemyParam::Data_EnemyParam() : enemyList(){
}

bool Data_EnemyParam::Load(){
	return LoadDataFromCsv();
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
		sprintf_s(fileName, MAX_PATH-1, "dat_enemy\\enemy%03d.csv", n);
		// csvファイルを読み込んでグループに格納する
		if(reader.Open(fileName)){
			tmpEnemy.Refresh();
			nEmptyFile = 0; // 空ファイル数のリセット
			index = 0;
			// ダミー行
			reader.NextLine();
			// レファレンス用IDを取得する
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpEnemy.SetRefID((WORD)reader.GetIntValue(0, 0));
			}
			// ダミー行
			reader.NextLine();
			// 敵の名前と属性と経験値を取得する
			if(reader.Read() == CSV_READ_NOERROR){
				// バッファに直接値を入れる
				reader.GetValue(0, tmpEnemy.GetNamePtr(), BATTLEUNIT_NAME_BYTES-1);
				// 属性を読み取る
				tmpEnemy.SetAttr((BYTE)reader.GetIntValue(1, DOLL_ATTR_NONE));
				// 経験値を読み取る
				tmpEnemy.SetExp((DWORD)reader.GetIntValue(2, 0));
			}
			// ダミー行
			reader.NextLine();
			// 敵の各パラメータを取得する
			reader.Read();
			for(int i=0; i<NUM_ENEMYPARAM_DATA; i++){
				tmpEnemy.SetParam(i, reader.GetIntValue(i, 0));
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
		if(pResult->GetRefID() == _refID){
			// 欲しいIDと一致するものがあればそれを返す
			return pResult;
		}
	}
	return NULL;
}