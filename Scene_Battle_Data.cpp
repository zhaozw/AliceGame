// Scene_Battle_Data.cpp

#include "Scene_Battle.h"
#include "Data_EnemyGroup.h"
#include "Data_EnemyParam.h"
#include "Game_AliceDoll.h"
#include "CsvReader.h"

// データベース
extern Data_EnemyGroup d_enemyGroup;
extern Data_EnemyParam	d_enemyParam;

bool Scene_Battle::SetupDolls(){
	if(!LoadPresetDolls(1)){
		return false;
	}
	return true;
}

bool Scene_Battle::SetupEnemy(){
	// 敵グループIDからデータベースを読み込む。
	if(!LoadEnemyGroup()){
		return false;
	}
	return true;
}

bool Scene_Battle::LoadDefaultDolls(int defaultID){
	return true;
}

bool Scene_Battle::LoadPresetDolls(int defaultID){
	TCHAR		fileName[MAX_PATH];
	CsvReader	reader;
	Game_AliceDoll_Essence	tmpDoll;
	TCHAR		tmpName[BATTLEUNIT_NAME_BYTES];
	BYTE		tmpAttr = DOLL_ATTR_NONE;
	int			tmpInt = 0;
	wsprintf(fileName, _T("dat_battle\\preset_dolls%02d.csv"), defaultID);
	if(!reader.Open(fileName)){
		return false;
	}
	// 最初の二行は空行
	reader.Read();
	reader.Read();
	// 人形の成長レベルは全て0、全て内部レベルで強さを管理する
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		tmpDoll.SetGrowthLevel(n, 0);
	}
	// 人形の名前はデータベースから直接読み込む。
	strcpy_s(tmpName, BATTLEUNIT_NAME_BYTES, _T(""));

	// 各人形のデータを読み込む
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		reader.Read();
		// タイプIDが適切かどうかで判断
		tmpInt = reader.GetIntValue(0);
		if(tmpInt < 0 || tmpInt > DOLL_TYPE_MAX){
			break;
		}
		// タイプID
		tmpDoll.SetType((BYTE)tmpInt);
		// 名前
		reader.GetValue(1, tmpName, BATTLEUNIT_NAME_BYTES);
		// レベル
		tmpDoll.SetLevel((WORD)reader.GetIntValue(2));
		// 各パラメータ
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			tmpDoll.SetPotentialLevel(i, (DWORD)reader.GetIntValue(3+i));
		}
		// 属性
		// 全ての属性石を同じにする
		// 属性が0の場合は全ての石を2つずつにする
		tmpAttr = (BYTE)reader.GetIntValue(3+DOLL_PARAM_MAX);
		if(tmpAttr == DOLL_ATTR_NONE){
			for(int j=0; j<DOLL_ATTR_NUM-1; j++){
				for(int i=0; i<2; i++){
					tmpDoll.SetAttrStone(i+j*2, (BYTE)(j+1));
				}
			}
		}else{
			for(int i=0; i<DOLL_ATTRSTONE_NUM; i++){
				tmpDoll.SetAttrStone(i, tmpAttr);
			}
		}
		// 特技IDのセット
		reader.Read();
		for(int i=0; i<DOLL_SKILL_MAX; i++){
			tmpDoll.SetSkillID(i, (WORD)reader.GetIntValue(i));
		}
		// Game_AliceDoll_EssenceからGame_BattleDollに内容をインポート
		dolls[n].SetParamFromReference(&tmpDoll, false);

		// 名前だけは別でコピー
		dolls[n].SetName(tmpName, strlen(tmpName));

		// 使用されている
		dolls[n].SetIsUsed(true);

		// 人形の数を指定。
		dollsNum = n+1;
	}
	return true;
}

bool Scene_Battle::LoadEnemyGroup(){
	// 敵ユニットのIDであるenemyGroup(WORD)値を使用する。
	Data_EnemyGroup_Each* pEnemyGroup = NULL;
	WORD tmpRefID;
	pEnemyGroup = d_enemyGroup.GetEnemyGroup(enemyGroup);
	if(pEnemyGroup == NULL){
		// 該当するrefIDを持つ敵グループが存在しない(エラー)
		return false;
	}
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		tmpRefID = pEnemyGroup->GetEnemyRefID(n);
		if(tmpRefID != 0){
			// IDから敵を作成する
			LoadEnemyData(n, tmpRefID,
				pEnemyGroup->GetEnemyDrawX(n), pEnemyGroup->GetEnemyDrawY(n));
			// 敵の数を入力
			enemiesNum = n+1;
		}else{
			// 敵IDが空。データの取り込みを終了する
			break;
		}
	}
	return true;
}

bool Scene_Battle::LoadEnemyData(WORD index, WORD enemyID, int drawX, int drawY){
	TCHAR tmpName[BATTLEUNIT_NAME_BYTES];
	Data_EnemyParam_Each* pEnemyParam = NULL;
	// 敵の情報を取得
	pEnemyParam = d_enemyParam.GetEnemyParam(enemyID);
	if(pEnemyParam == NULL){
		// 存在しない敵を参照している(エラー)
		return false;
	}
	// ID
	enemies[index].SetDataID(enemyID);
	// 名前
	pEnemyParam->GetName(tmpName, BATTLEUNIT_NAME_BYTES); // 要検討
	enemies[index].SetName(tmpName, strlen(tmpName));
	// パラメータ
	enemies[index].SetParam(
		pEnemyParam->GetHP(), pEnemyParam->GetHP(),
		pEnemyParam->GetAtk(), pEnemyParam->GetDef(),
		pEnemyParam->GetSpd(), pEnemyParam->GetMgc(),
		pEnemyParam->GetTec());
	// 属性
	enemies[index].SetAttr(pEnemyParam->GetAttr());
	// 描画位置
	enemies[index].SetDrawPos(drawX, drawY);
	// 経験値
	enemies[index].SetExp(pEnemyParam->GetExp());
	// その他固定値
	enemies[index].SetFront(true);
	enemies[index].SetPosition(index);
	enemies[index].SetSelfTurn();
	enemies[index].SetIsUsed(true);
	return true;
}
