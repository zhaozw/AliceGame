#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

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
typedef struct Data_EnemyGroup_Each_Data{
	// 敵グループID。マップなどから参照される。
	WORD				refID;		
	// 各敵キャラ。
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
} DATA_ENEMYGROUP_EACH_DATA;

// 敵グループ一つを表すクラス。
// Data_EnemyGroupクラスにFlexListとして保持される。
class Data_EnemyGroup_Each{
private:
	DATA_ENEMYGROUP_EACH_DATA		data;
public:
	// コンストラクタ
	Data_EnemyGroup_Each();
	void Refresh();
	// アクセサ
	void	SetRefID(WORD _refID){ data.refID = _refID; };
	WORD	GetRefID(){ return data.refID; };
	void	SetEnemyRefID(int index, WORD _refID){
		if(IsIndex(index)) data.enemy[index].refID = _refID;
	}
	WORD	GetEnemyRefID(int index){
		if(IsIndex(index)) return data.enemy[index].refID;
		return 0;
	}
	void	SetEnemyDrawX(int index, int _drawX){
		if(IsIndex(index)) data.enemy[index].drawX = _drawX;
	}
	WORD	GetEnemyDrawX(int index){
		if(IsIndex(index)) return data.enemy[index].drawX;
		return 0;
	}
	void	SetEnemyDrawY(int index, int _drawY){
		if(IsIndex(index)) data.enemy[index].drawY = _drawY;
	}
	WORD	GetEnemyDrawY(int index){
		if(IsIndex(index)) return data.enemy[index].drawY;
		return 0;
	}
	void	SetEnemyAttr(int index, BYTE _attr){
		if(IsIndex(index)) data.enemy[index].attr = _attr;
	}
	BYTE	GetEnemyAttr(int index){
		if(IsIndex(index)) return data.enemy[index].attr;
		return DOLL_ATTR_NONE;
	}
	bool	IsIndex(int index){ return index >= 0 && index < MAX_BATTLEENEMY; };
};

// 敵グループのデータを保持するクラス。
// グローバル変数d_enemyGroupから参照される。
class Data_EnemyGroup{
private:
	// 敵グループの配列
	VectorList<Data_EnemyGroup_Each>		groupList;

public:
	// コンストラクタ
	Data_EnemyGroup();
	// ロード
	bool Load();
	bool LoadDataFromCsv();

	// Vectorリストを意図的に開放する
	void ReleaseList(){ groupList.Release(); };

	// 敵グループへのポインタを取得する。
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_EnemyGroup_Each* GetEnemyGroup(WORD _refID);


	// 大きさを返す。
	int GetSize(){ return groupList.GetSize(); };
};

#endif // DATA_ENEMYGROUP_H