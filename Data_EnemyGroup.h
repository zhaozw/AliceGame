#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

#define CSVFILE_ENEMYGROUP _T("dat_egroup\\group%03d.csv")
#define DATFILE_ENEMYGROUP _T("dat\\enemygroup.dat")

// 敵グループ内の敵一体を表す構造体
typedef struct EnemyInGroup{
	WORD		refID;		// 敵ID。Data_EnemyParamクラスの参照IDを指定する。
	int			drawX;		// 描画位置の中心。
	int			drawY;		// 基本的にy座標の昇順でデータを記録する。
	BYTE		attr;		// 属性。-1の場合はランダムで決まる。
	EnemyInGroup(){
		refID	= 0;
		drawX	= 0;
		drawY	= 0;
		attr	= DOLL_ATTR_RANDOM;
	}
} ENEMYINGROUP;

// 敵グループ一つを表す構造体。
typedef struct Data_EnemyGroup_Data{
	// 敵グループID。マップなどから参照される。
	WORD				refID;		
	// 各敵キャラ。
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
	Data_EnemyGroup_Data(){
		refID = 0;
		for(int n=0; n<MAX_BATTLEENEMY; n++){
			enemy[n] = ENEMYINGROUP();
		}
	}
} DATA_ENEMYGROUP_DATA;

// 敵グループのデータを保持するクラス。
// グローバル変数d_enemyGroupから参照される。
class Data_EnemyGroup{
private:
	// 敵グループの配列
	VectorList<Data_EnemyGroup_Data>		groupList;

public:
	// コンストラクタ
	Data_EnemyGroup();
	// ロード
	bool Load();
	bool LoadDataFromCsv();
	bool LoadDataFromDat();

	bool EncodeCsv();

	// Vectorリストを意図的に開放する
	void ReleaseList(){ groupList.Release(); };

	// 敵グループへのポインタを取得する。
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyGroup_Data* GetEnemyGroup(WORD _refID);


	// 大きさを返す。
	int GetSize(){ return groupList.GetSize(); };
};

#endif // DATA_ENEMYGROUP_H