#ifndef WINDOW_LINEINFO_H
#define WINDOW_LINEINFO_H

#include "Window_Text.h"
#include "DXFont.h"

// 一行の情報を保持するクラス。
// かなり簡略化されており、フォントやウィンドウサイズ（高さ）は固定。
// このクラスのまま使っても良いし、使いにくければ派生させても良い。

#define WND_LINEINFO_BYTES		128
#define WND_LINEINFO_HEIGHT		(FONTSIZE_INFO+32)

class Window_LineInfo : public Window_Text{
protected:
	TCHAR			text[WND_LINEINFO_BYTES];
public:
	// コンストラクタ
	Window_LineInfo();
	
	// セットアップ
	void Setup(int x, int y, int w, BYTE align);

	// 表示する文字を設定する
	void SetText(LPTSTR str, int length);

	// 描画
	virtual void DrawContent() const;

};


#endif // WINDOW_LINEINFO_H
