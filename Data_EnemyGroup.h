#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"

// 敵グループ内の敵一体を表す構造体
typedef struct EnemyInGroup{
	WORD		refID;		// 敵ID。Data_EnemyParamクラスの参照IDを指定する。
	int			drawX;		// 描画位置の中心。
	int			drawY;		// 基本的にy座標の昇順でデータを記録する。
	EnemyInGroup(){
		refID = 0;
		drawX = 0;
		drawY = 0;
	}
} ENEMYINGROUP;

// 敵グループ一つを表すクラス。
// Data_EnemyGroupクラスにFlexListとして保持される。
class Data_EnemyGroup_Each{
private:
	// 敵グループID。マップなどから参照される。
	WORD		refID;		
	// 各敵キャラ。
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
public:
	// コンストラクタ
	Data_EnemyGroup_Each();
	void Refresh();
	// アクセサ
	void	SetRefID(WORD _refID){ refID = _refID; };
	WORD	GetRefID(){ return refID; };
	void	SetEnemyRefID(int index, WORD _refID){
		if(IsIndex(index)) enemy[index].refID = _refID;
	}
	WORD	GetEnemyRefID(int index){
		if(IsIndex(index)) return enemy[index].refID;
		return 0;
	}
	void	SetEnemyDrawX(int index, int _drawX){
		if(IsIndex(index)) enemy[index].drawX = _drawX;
	}
	WORD	GetEnemyDrawX(int index){
		if(IsIndex(index)) return enemy[index].drawX;
		return 0;
	}
	void	SetEnemyDrawY(int index, int _drawY){
		if(IsIndex(index)) enemy[index].drawY = _drawY;
	}
	WORD	GetEnemyDrawY(int index){
		if(IsIndex(index)) return enemy[index].drawY;
		return 0;
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
};

#endif // DATA_ENEMYGROUP_H