// Record_ChooseMap.h

#pragma once

#include "Static_Map.h"
#include <Windows.h>

//=============================================
// エリア選択画面のクリア状態を表すデータ。
// どの道が開通しているかの判定と、
// 各エリアのクリアステージ数を保存する。
// また、お店の開放状態についても含める。

typedef struct Record_ChooseMap_Data{
	BYTE		stageOfArea[CHOOSEMAP_AREA_MAX];	// エリアごとに進めているステージの数。
													// 0だとそのエリアが現れていない、
													// 1だとエリアが現れた直後、
													// 2だとそのエリアのステージを1個クリアした状態。
	BYTE		pathState[CHOOSEMAP_PATH_MAX];		// 各道の状態。
	bool		spotOpened[CHOOSEMAP_SPOT_MAX];		// スポットが解放されているか否か。
	// コンストラクタ
	Record_ChooseMap_Data(){
		for(int n=0; n<CHOOSEMAP_AREA_MAX; n++){
			stageOfArea[n] = 0;
		}
		for(int n=0; n<CHOOSEMAP_PATH_MAX; n++){
			pathState[n] = CHOOSEMAP_PATHSTATE_NONE;
		}
		for(int n=0; n<CHOOSEMAP_SPOT_MAX; n++){
			spotOpened[n] = false;
		}
	}
} RECORD_CHOOSEMAP_DATA;

// グローバル変数 r_chooseAreaから参照される。
class Record_ChooseMap{
private:
	RECORD_CHOOSEMAP_DATA		data;
public:
	// コンストラクタ
	Record_ChooseMap();

	// 初期化
	// (エリア1のみプレイ可能にする)
	bool Initialize();

	// バイト列からデータに内容をコピーする
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);

	// pathStateを更新する。
	// 原則として、常に行われるのではなくシーンの先頭において
	// 実行され、パスが通行可能かどうかの判定を行う。
	// 新たに開かれたパスがある場合、
	// そのパスのpathStateの値を更新し、
	// 開かれたパスのpathIDを返す。
	WORD	CheckPathOpen(BYTE chapter);

	// アクセサ系

	// アリスが現在のポイントから特定の方向に移動出来るかを返す。
	bool		CheckAliceDirection(WORD pointID, BYTE direction) const;

	// 指定したパスが通行可能かどうかを返す。
	BYTE		GetPathState(WORD pathID) const{ return data.pathState[pathID]; };

	// エリアのステージ数の取得
	BYTE		GetStageOfArea(int index){
		if(index <= 0 || index >= CHOOSEMAP_AREA_MAX){
			return 0;
		}else{
			return data.stageOfArea[index];
		}
	};
	// エリアを開放する。
	// 具体的には、指定したインデックスのstageOfArea値を1にする。
	bool		OpenArea(int index){
		if(index <= 0 || index >= CHOOSEMAP_AREA_MAX){
			return false;
		}else if(data.stageOfArea[index] > 0){
			return false;
		}else{
			data.stageOfArea[index] = 1;
			return true;
		}
	};
	// エリアのステージクリア数を1増やす。
	// 既に全ステージ開放済みの時は解放しない。
	bool		AddStageOfArea(WORD chapter, int areaID);
	// エリアがクリア済みであるかどうかを取得する。
	bool		GetAreaIsCleared(WORD chapter, int areaID);

	// パスを開く。
	bool		OpenPath(int index){
		data.pathState[index] = CHOOSEMAP_PATHSTATE_OPENED;
		return true;
	}



	// データを取得する
	RECORD_CHOOSEMAP_DATA		GetData(){ return data; };
};