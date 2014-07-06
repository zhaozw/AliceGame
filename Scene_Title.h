#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene_Base.h"
#include "Selectable.h"

#define TITLE_MENU_NEWGAME		0	// 最初から始める
#define TITLE_MENU_CONTINUE		1	// 続きから始める
#define TITLE_MENU_EXIT			2	// ゲームを終了する
#define MAX_TITLE_MENU			(TITLE_MENU_EXIT+1)	// メニューの総数


class Scene_Title : public Scene_Base{
public:
	Selectable		s_main;	// メニューの選択画面

private:

public:
	// コンストラクタ
	Scene_Title();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw();

};

#endif // SCENE_TITLE_H