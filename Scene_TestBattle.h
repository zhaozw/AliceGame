#ifndef SCENE_TESTBATTLE_H
#define SCENE_TESTBATTLE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Window_HintMessage.h"
#include "Game_BGEffect.h"

#define MAX_TESTBATTLE			10
#define MAX_TESTBATTLE_MENU		3
#define TESTBATTLE_SELECT_NUM	(MAX_TESTBATTLE+MAX_TESTBATTLE_MENU)

class Scene_TestBattle : public Scene_Base{
protected:
	Selectable				s_main;	// メニューの選択画面
	Window_HintMessage		w_hint;	// シャンハイのヒントウィンドウ
	float					backX;	// 背景画像の描画位置の指標
	float 					backY;
	int						backDoll;	// 右下に人形を表示する
	Game_BGEffect			bg;			// エフェクトつきの背景

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
	
	// ヒントウィンドウを開く
	bool OpenHintWindow();


};


#endif // SCENE_TESTBATTLE_H