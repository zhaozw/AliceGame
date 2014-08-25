#ifndef SCENE_MAP_H
#define SCENE_MAP_H

#include "Scene_Base.h"
#include "Game_MapPoint.h"
#include "VectorList.h"

class Scene_Map : public Scene_Base{
protected:
	// マップID。
	// Game_Temp内に保持された値を
	// 初期化時に読み込み、
	// それを元にマップのロードなどを行う。
	int								id;

	// ポイントのリスト。
	// ファイルから読み込まれる。
	VectorList<Game_MapPoint>		pointList;

	// 道のリスト。
	// ポイントのリストを元に作成される。
	VectorList<Game_MapPath>		pathList;
public:
	// コンストラクタ
	Scene_Map();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;

	// ファイルからマップを読み込む。
	// ファイル名はid値から自動的に計算される。
	bool Load();
};


#endif // SCENE_MAP_H


