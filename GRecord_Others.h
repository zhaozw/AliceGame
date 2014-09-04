// GRecord_Others.h

#pragma once

#include <Windows.h>
#include "Static_Game.h"

#define FIRST_DOLL_ID			100

//==========================================
// GRecord_Othersクラス
// 
// ゲーム全体で共有するデータのうち、
// どのクラスにも属さないデータを保持する。

//==========================================
// Record_Global_Others_Data
// 保存するデータの構造体。

typedef struct GRecord_Others_Data{
	// アリスのID。乱数及び、コンピュータの名前で決まる。
	// 他のプレイヤーと人形を交換した時の認証などに用いる。
	// (交換制限がかかるわけではない)
	// この値と異なるaliceID値をデータとして持つ人形は
	// よそのアリスと交換した人形と見なされる。
	// 理論上は他のアリスとIDが被ることも考えられるが、
	// そこまではサポートしない。
	DWORD		aliceID;

	// 人形をシリアルナンバーで管理するためのID。
	// 人形が生成されるごとにこの値が割り当てられ、その後1増える。
	DWORD		nextDollID;
	
	// 章をクリアしているか否か。
	// 実際には要素の番号が1ずれる。
	// 例として、1章をクリアした場合は要素0番の値がtrueになる。
	bool isClearedChapter[MAX_CHAPTER+1];

	GRecord_Others_Data(){
		for(int n=0; n<MAX_CHAPTER+1; n++){
			isClearedChapter[n] = false;
		}
		aliceID = 0;
	}
} GRECORD_OTHERS_DATA;

class GRecord_Others{
private:
	// データ
	GRECORD_OTHERS_DATA		data;


public:
	// コンストラクタ
	GRecord_Others();
	
	// 全て初期化
	bool	Initialize();

	// 章をクリアした(要素番号が1ずれる)
	void	ClearChapter(int n){ data.isClearedChapter[n-1] = true; };
	
	// 章をクリアしているかの取得(要素番号が1ずれる)
	bool	GetChapterIsCleared(int n){ return data.isClearedChapter[n-1]; };

	// アリスのIDを生成し、代入する。
	void	GenerateAliceID();

	// アリスのIDを取得する。
	DWORD	GetAliceID(){ return data.aliceID; };

	// 人形のIDを取得し、IDを1増やす。
	DWORD	GetDollID();
};
