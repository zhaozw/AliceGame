#ifndef WINDOW_TEXT_H
#define WINDOW_TEXT_H

#include "Window_Base.h"

// 文字を描画するウィンドウのクラス。
// 特に描画する文字の形態や文字の描画の仕方は決まっておらず、
// 実際には派生したクラスを使用する。
class Window_Text : public Window_Base{
protected:
	BYTE align;			// 文字の寄せ方。
	int	lineHeight;		// 項目ごとの間隔。 
	int hFont;			// フォントのハンドル
	int fontSize;		// フォントの大きさ
	int color;			// フォントの色
	int iColor;			// 選択されていないテキストのフォントの色。
	int nColor;			// 選択できないテキストのフォントの色。
public:
	// コンストラクタ
	Window_Text();

	// 文字色の設定
	// 色設定は、通常色、選択されていない、選択できないの順に指定する
	void SetColor(int _color, bool setAll=true){
		color = _color; if(setAll){ iColor = nColor = _color; }; };
	void SetIColor(int _color, bool setNColor=true){
		iColor = _color; if(setNColor){ nColor = _color; }; };
	void SetNColor(int _color){ nColor = _color; }
	void SetAllColor(int _color, int _iColor, int _nColor){
		color = _color; iColor = _iColor; nColor = _nColor; }; 
		
	// フォントの指定
	void SetFont(int _hFont, int _fontSize, int _lineHeight){
		hFont = _hFont; fontSize = _fontSize; lineHeight = _lineHeight;
	};

	// 内容の並びを揃える時の描画位置のずれの設定
	// content : 文字
	// strSize : 文字列の長さ（省略可）
	// _hFont : hFontと異なるフォントを使用する際のフォントのハンドル
	// ※constにしておかないと派生クラスから使用した時にエラーが出る。
	//   メンバを変更されると困るとか何とか？
	int GetDrawDeltaX(LPTSTR content, int strSize = -1, int _hFont = 0) const;
};

#endif // WINDOW_TEXT_H