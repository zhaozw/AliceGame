#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Static_Game.h"

#define TITLE_MENU_NEWGAME		0	// 最初から始める
#define TITLE_MENU_CONTINUE		1	// 続きから始める
#define TITLE_MENU_STOCKDOLLS	2	// 記憶の中の人形
#define TITLE_MENU_RECORDS		3	// トロフィー
#define TITLE_MENU_TESTBATTLE	4	// テストバトル画面に戻る
#define TITLE_MENU_OPTION		5	// オプション
#define TITLE_MENU_EXIT			6	// ゲームを終了する
#define MAX_TITLE_MENU			(TITLE_MENU_EXIT+1)	// メニューの総数

#define TITLE_PHAZE_START		0
#define TITLE_PHAZE_MAIN		1
#define TITLE_PHAZE_CHAPTER		2
#define TITLE_PHAZE_OPTION		3


class Scene_Title : public Scene_Base{
private:
	Selectable		s_main;		// メニューの選択画面
	Selectable		s_chapter;	// 「はじめから」のチャプターの選択
	WORD			phaze;		// フェイズ
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
	virtual void Draw() const;

};

#endif // SCENE_TITLE_H