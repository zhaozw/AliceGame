#ifndef SCENE_TESTBATTLE_H
#define SCENE_TESTBATTLE_H

#include "Scene_Base.h"
#include "Selectable.h"

#define MAX_TESTBATTLE		10

class Scene_TestBattle : public Scene_Base{
public:
	Selectable		s_main;	// メニューの選択画面

private:

public:
	// コンストラクタ
	Scene_TestBattle();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw();


};


#endif // SCENE_TESTBATTLE_H