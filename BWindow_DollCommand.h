#ifndef BWINDOW_DOLLCOMMAND_H
#define BWINDOW_DOLLCOMMAND_H

#include "Window_Selectable.h"

#define BWND_DOLLCOMMAND_X		200
#define BWND_DOLLCOMMAND_Y		300
#define BWND_DOLLCOMMAND_W		300
#define BWND_DOLLCOMMAND_H		200
#define BWND_DOLLCOMMAND_PX	16
#define BWND_DOLLCOMMAND_PY	16

class BWindow_DollCommand : public Window_Selectable{
private:

public:
	BWindow_DollCommand();

	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 内容の描画を行う。
	virtual void DrawContent() const;

};


#endif // BWINDOW_DOLLCOMMAND_H