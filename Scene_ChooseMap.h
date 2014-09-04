// Scene_ChooseMap.h

// エリア内のマップを選択するシーン。

#pragma once

#include "Scene_Base.h"

class Scene_ChooseMap : public Scene_Base{
private:
	int			cntIndex;			// 現在選択中のポイント番号。
	int			lastIndex;		// 最後に選択していたポイント番号。
	bool		moving;			// 移動中フラグ。
public:
	// コンストラクタ
	Scene_ChooseMap();


	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;


};

