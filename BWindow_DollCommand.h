#ifndef BWINDOW_DOLLCOMMAND_H
#define BWINDOW_DOLLCOMMAND_H

#include "Window_Selectable.h"

#define BWND_DOLLCOMMAND_X		100
#define BWND_DOLLCOMMAND_Y		400
#define BWND_DOLLCOMMAND_W		300
#define BWND_DOLLCOMMAND_H		200
#define BWND_DOLLCOMMAND_PX	16
#define BWND_DOLLCOMMAND_PY	16

#define BWND_DOLLCOMMAND_ATTACK		0
#define BWND_DOLLCOMMAND_SKILL		1
#define BWND_DOLLCOMMAND_GUARD		2

class Scene_Battle;

class BWindow_DollCommand : public Window_Selectable{
private:
	// このウィンドウを保持するシーンへのポインタ。
	Scene_Battle*		pScene;
	// 結果をScene_Battleなどに渡すために保持しておくインデックス
	int			commandIndex;
	// サブコマンドの結果を受け取るインデックス
	int			subIndex;
	// 選択したターゲットのインデックスを保持する
	int			targetIndex;
public:
	// コンストラクタ
	BWindow_DollCommand();

	// 開く度にリフレッシュする
	void		Refresh();

	// アクセサ
	int			GetCommandIndex(){ return commandIndex; };
	int			GetSubIndex(){ return subIndex; };

	// セットアップ
	void MySetup(Scene_Battle* _pScene);

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	//
	virtual void CheckAutoClose();

	// 内容の描画を行う。
	virtual void DrawContent() const;

};


#endif // BWINDOW_DOLLCOMMAND_H