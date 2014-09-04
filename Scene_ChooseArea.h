// Scene_ChooseArea.h

// エリアを選択するシーン。
// エリアの選択はSelectableクラスではなく、
// より複雑な移動を伴って行う。

#pragma once

#include "Scene_Base.h"

class Scene_ChooseArea : public Scene_Base{
private:
	int			cntIndex;		// 現在選択中のエリア。
	int			lastIndex;		// 選択していたエリア。
	bool		moving;			// エリア間を移動中であるというフラグ。
public:
	// コンストラクタ
	Scene_ChooseArea();

	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;


};

