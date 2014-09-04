// Scene_StockDolls.h

// アリスの記憶の中の人形を確認したり、
// そこから人形を生み出したりするクラス。

#pragma once

#include "Scene_Base.h"

class Scene_StockDolls : public Scene_Base{
private:
public:
	// コンストラクタ
	Scene_StockDolls();

	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;


};

