#ifndef BWINDOW_ALICECOMMAND_H
#define BWINDOW_ALICECOMMAND_H

#include "Window_Selectable.h"

#define BWND_ALICECOMMAND_X		20
#define BWND_ALICECOMMAND_Y		380
#define BWND_ALICECOMMAND_W		240
#define BWND_ALICECOMMAND_H		200
#define BWND_ALICECOMMAND_PX	16
#define BWND_ALICECOMMAND_PY	16

class BWindow_AliceCommand : public Window_Selectable{
private:

public:
	BWindow_AliceCommand();

	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// 自動で閉じるかは場合によって変わる。
	virtual void CheckAutoClose(){ autoClose = true; };

	// 現在の項目がキャンセル可能であるかどうかの判定を行う
	// キャンセル可能かどうかは開く時に決まる。
	virtual void CheckCancelable(){ cancelable = false; };
};

#endif // BWINDOW_ALICECOMMAND_H
