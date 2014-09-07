// Data_ChooseMap.h

#pragma once

#include "Static_Map.h"
#include "Static_Game.h"
#include <Windows.h>

//==============================================
// Data_ChooseMapクラス
// エリア選択画面におけるデータを扱う。
// グローバル変数d_chooseMapから参照される。
//
// 道の移動に関しては、Data_ChooseMap_Path構造体が判定の主体となる。
// Data_ChooseMap_Path構造体のメンバであるData_ChooseMap_Path_Edge構造体は
// この道の両端のポイントのポイントIDと、そのポイントからどの方向キーを押した時に
// 移動する道であるかを保持している。
// プレイヤーがあるキーを押した時、現在プレイヤーが居るポイントのIDと方向キーによって
// 各Data_ChooseMap_Path構造体をスキャンし、
// 移動するようなパスがあれば、それに沿ってプレイヤーを移動させる。
// 
// 内容は章ごとに、一部重複し、一部異なっているが、
// 章ごとにd_chooseMapに別の値を読み込むことはせず、
// 全ての章の情報をまとめて読み込む。


// エリア選択マップにおける、道の両端の情報を保持する構造体。
typedef struct Data_ChooseMap_Path_Edge{
	// 道の端が何番のポイントに接続されているか
	WORD					pointID;
	// そのポイントからどちらの方向に接続されているか
	BYTE					direction;	
	Data_ChooseMap_Path_Edge(){
		pointID = 0;
		direction = 0;
	};
} DATA_CHOOSEMAP_PATH_EDGE;

// チャプターごとの、道の解放条件を保持する構造体。
#define CHOOSEMAP_PATH_CONDITION_AREA_MAX		3
#define CHOOSEMAP_PATH_CONDITION_DISABLED		(CHOOSEMAP_PATH_CONDITION_AREA_MAX+1)
typedef struct Data_ChooseMap_Path_Condition{
	BYTE	areaID[CHOOSEMAP_PATH_CONDITION_AREA_MAX];	// 道の解放に関連するエリア群。
	BYTE	num;						// 上記のエリア群のうち、クリアする必要の	
										// あるエリア数。ただし、areaIDが0の場合は除く。
										// 0にすると、最初から開かれている道。
	Data_ChooseMap_Path_Condition(){
		for(int n=0; n<CHOOSEMAP_PATH_CONDITION_AREA_MAX; n++){
			areaID[n] = 0;
		}
		num = CHOOSEMAP_PATH_CONDITION_DISABLED; // 使用しないをチェック。
	};
} DATA_CHOOSEMAP_PATH_CONDITION;

// エリア選択マップにおける道の情報を保持する構造体。
// パスIDの0番は使用しない。
typedef struct Data_ChooseMap_Path{
	DATA_CHOOSEMAP_PATH_EDGE				edge[2];
	DATA_CHOOSEMAP_PATH_CONDITION			condition[MAX_CHAPTER];
	Data_ChooseMap_Path() : edge(), condition(){
	};
} DATA_CHOOSEMAP_PATH;

// エリア選択マップにおけるポイントの情報を保持する構造体。
// ポイントIDの0番は使用しない。
typedef struct Data_ChooseMap_Point{
	BYTE					areaID;		// エリアのID。どこでもない場合は0。
	int						posX;
	int						posY;		// 座標。
	Data_ChooseMap_Point(){
		areaID = 0;
	}
}DATA_CHOOSEMAP_POINT;


// エリア選択マップにおけるスポット解放の情報を保持する構造体。
typedef struct Data_ChooseMap_Spot{
	bool					opened;		// スポットが解放されているか否か
	Data_ChooseMap_Spot(){
		opened = false;
	}
}DATA_CHOOSEMAP_SPOT;

// 各エリアのステージなどの情報を保持する構造体。
typedef struct Data_ChooseMap_Area{
	// マップのID。チャプターごとに派生。
	// 
	WORD				mapID[MAX_CHAPTER*CHOOSEMAP_STAGE_MAX];	
	Data_ChooseMap_Area(){
		for(int n=0; n<MAX_CHAPTER*CHOOSEMAP_STAGE_MAX; n++){
			mapID[n] = 0;
		}
	}
}DATA_CHOOSEMAP_AREA;


// エリア選択マップ全体の情報を保持するクラス。
class Data_ChooseMap{
protected:
	// ポイントの情報。
	DATA_CHOOSEMAP_POINT		point[CHOOSEMAP_POINT_MAX];
	// パスの情報。
	DATA_CHOOSEMAP_PATH			path[CHOOSEMAP_PATH_MAX];
	// スポットの情報。
	DATA_CHOOSEMAP_SPOT			spot[CHOOSEMAP_SPOT_MAX];
	// ステージの情報。
	DATA_CHOOSEMAP_AREA			area[CHOOSEMAP_AREA_MAX];

public:
	// コンストラクタ
	Data_ChooseMap();

	// データを読み込む。
	bool Load();
	bool LoadDataByHand();		// 手入力で入れる
	bool LoadDataFromCsv();
	bool LoadDataFromDat();
	bool EncodeCsv();

	// パスID、ポイント、方向を指定すると、そのパスをそのポイントと方向で
	// 移動するかを返す。
	// この関数では位置関係のみを判別し、
	// 実際に移動出来るかどうか(ゲームの進捗によって変わる)は判定しない。
	bool CheckPathMove(WORD pathID, WORD pointID, BYTE direction) const;

	// アクセサ系
	// ポイントの座標を取得する。
	int GetPointX(int index){
		if(index > 0 || index < CHOOSEMAP_POINT_MAX){
			return point[index].posX;
		}
		return 0;
	}
	int GetPointY(int index){
		if(index > 0 || index < CHOOSEMAP_POINT_MAX){
			return point[index].posY;
		}
		return 0;
	}

	// パスの両端のポイントのインデックスを取得する。
	// isRoot : パスの出発側(便宜上定めているだけで、意味はない)
	WORD	GetPathEdgeIndex(int index, bool isRoot){
		if(index > 0 || index < CHOOSEMAP_PATH_MAX){
			return path[index].edge[(isRoot?0:1)].pointID;
		}
		return 0;
	}

	// パスの解放に必要なエリアを設定する。
	bool	SetAreaToOpenPath(WORD pathID, WORD areaID, BYTE chapter);

	// 各エリアのステージ数を取得する。
	int	GetStageNum(int areaID, int chapter){
		for(int n=0; n<CHOOSEMAP_STAGE_MAX; n++){
			if(area[areaID].mapID[n+chapter*CHOOSEMAP_STAGE_MAX] == 0){
				// IDが0のマップは使用されない。
				// 従って、この時のnがエリアごとのステージ数。
				return n;
			}
		}
		return CHOOSEMAP_STAGE_MAX;
	}

	// パスの解放に必要なエリアを取得する。
	WORD	GetAreaToOpenPath(WORD pathID, int index, BYTE chapter){
		return path[pathID].condition[chapter].areaID[index];
	}
	BYTE	GetAreaNumToOpenPath(WORD pathID, BYTE chapter){
		return path[pathID].condition[chapter].num;
	}

	// エリアにマップIDをセットする。
	void SetMapID(WORD mapID, WORD chapter, WORD areaID, WORD mapIndex){
		area[areaID].mapID[mapIndex+chapter*CHOOSEMAP_STAGE_MAX] = mapID;
	}

	// エリアのマップIDを取得する。
	WORD GetMapID(WORD chapter, WORD areaID, WORD mapIndex){
		return area[areaID].mapID[mapIndex+chapter*CHOOSEMAP_STAGE_MAX];
	}




};