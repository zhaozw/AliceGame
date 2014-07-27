#ifndef SCENE_TESTBATTLE_H
#define SCENE_TESTBATTLE_H

#include "Scene_Base.h"
#include "Selectable.h"

#define MAX_TESTBATTLE			10
#define MAX_TESTBATTLE_MENU		3
#define TESTBATTLE_SELECT_NUM	(MAX_TESTBATTLE+MAX_TESTBATTLE_MENU)

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
	virtual void Draw() const;


};


#endif // SCENE_TESTBATTLE_H