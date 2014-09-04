// Scene_Records.h

// トロフィーを確認するシーン。

#pragma once

#include "Scene_Base.h"

class Scene_Records : public Scene_Base{
private:
public:
	// コンストラクタ
	Scene_Records();

	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;


};

