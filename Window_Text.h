#ifndef WINDOW_TEXT_H
#define WINDOW_TEXT_H

#include "Window_Base.h"

#define WINDOWFONT_DEFCOLOR		0x00ffffff
#define WINDOWFONT_DEFICOLOR	0x00909090
#define WINDOWFONT_DEFNCOLOR	0x00404060

typedef struct WindowFont{
	int		hFont;			// フォントのハンドル。
	int		fontSize;		// フォントサイズ。
	int		lineHeight;		// 一行の高さ。
	int		color;			// 通常文字の色。
	int		iColor;			// 非選択文字の色。
	int		nColor;			// 非アクティブ時の文字の色。
	BYTE	align;			// 文字の寄せ方。
	WindowFont(){
		hFont = 0;
		fontSize = 1;
		lineHeight = 1;
		color = WINDOWFONT_DEFCOLOR;
		iColor = WINDOWFONT_DEFICOLOR;
		nColor = WINDOWFONT_DEFNCOLOR;
		align = ALIGN_LEFT;
	}
	WindowFont(int _hFont, int _fontSize, int _lineHeight,
		int _color, int _iColor, int _nColor, BYTE _align = ALIGN_CENTER){
		hFont = _hFont;
		fontSize = _fontSize;
		lineHeight = _lineHeight;
		color = _color;
		iColor = _iColor;
		nColor = _nColor;
		align = _align;
	}
	WindowFont(int _hFont, int _fontSize, int _lineHeight, BYTE _align = ALIGN_CENTER){
		hFont = _hFont;
		fontSize = _fontSize;
		lineHeight = _lineHeight;
		color = WINDOWFONT_DEFCOLOR;
		iColor = WINDOWFONT_DEFICOLOR;
		nColor = WINDOWFONT_DEFNCOLOR;
		align = _align;
	}
} WINDOWFONT;

// 文字を描画するウィンドウのクラス。
// 特に描画する文字の形態や文字の描画の仕方は決まっておらず、
// 実際には派生したクラスを使用する。

class Window_Text : public Window_Base{
protected:
	WINDOWFONT	windowFont;			
public:
	// コンストラクタ
	Window_Text();

	// 文字色の設定
	// 色設定は、通常色、選択されていない、選択できないの順に指定する
	void SetColor(int _color, bool setAll=true){
		windowFont.color = _color; 
		if(setAll){
			windowFont.iColor = windowFont.nColor = _color;
		};
	};
	void SetIColor(int _color, bool setNColor=true){
		windowFont.iColor = _color;
		if(setNColor){
			windowFont.nColor = _color;
		};
	};
	void SetNColor(int _color){
		windowFont.nColor = _color;
	};
	void SetAllColor(int _color, int _iColor, int _nColor){
		windowFont.color = _color;
		windowFont.iColor = _iColor;
		windowFont.nColor = _nColor;
	}; 
		
	// フォントの指定
	void SetFont(int _hFont, int _fontSize, int _lineHeight){
		windowFont.hFont = _hFont;
		windowFont.fontSize = _fontSize;
		windowFont.lineHeight = _lineHeight;
	};

	// 内容の並びを揃える時の描画位置のずれの設定
	// content : 文字
	// strSize : 文字列の長さ（省略可）
	// _hFont : hFontと異なるフォントを使用する際のフォントのハンドル
	// なぜかDrawContent内で使用しようとするとErrorを吐くへっぽこ関数。
	// ※constにしておかないと派生クラスから使用した時にエラーが出る。
	//   メンバを変更されると困るとか何とか？
	int GetDrawDeltaX(TCHAR* content, int strSize = -1, int _hFont = 0) const;
};

#endif // WINDOW_TEXT_H