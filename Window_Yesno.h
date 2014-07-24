#ifndef WINDOW_YESNO_H
#define WINDOW_YESNO_H

#include "Window_Selectable.h"

#define WINDOW_YESNO_YES		0
#define WINDOW_YESNO_NO			1

// 「はい」「いいえ」を表示するウィンドウ。
// Window_Selectableを扱いやすいように限定的にしたもの。
// Update関数、DrawContent関数ともにWindow_Selectableを引き継ぐ。
class Window_Yesno : public Window_Selectable{
private:
public:
	// コンストラクタ
	Window_Yesno();

	// 内容のセットアップを行う。
	void Setup(
		WindowSkin* _pSkin,
		WINDOWAREA	_frameArea,
		WINDOWAREA	_contentArea,
		WINDOWFONT	_font,
		bool horizontal = true);

};

#endif // WINDOW_YESNO_H