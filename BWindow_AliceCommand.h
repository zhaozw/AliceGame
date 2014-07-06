#ifndef BWINDOW_ALICECOMMAND_H
#define BWINDOW_ALICECOMMAND_H

#include "Window_Selectable.h"

#define BWND_ALICECOMMAND_X		20
#define BWND_ALICECOMMAND_Y		400
#define BWND_ALICECOMMAND_W		300
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

};

#endif // BWINDOW_ALICECOMMAND_H
