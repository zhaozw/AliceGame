#ifndef WINDOW_SELECTABLE_H
#define WINDOW_SELECTABLE_H

#include "Window_Text.h"
#include "Selectable2D.h"
#include "Static_Game.h"
#include <Windows.h>
#include <string.h>

// 選択肢を表示するウィンドウ。
// 可変個数のリストを扱うのとは異なり、
// 単純に文字列を描画する。
// 内部に二次元のSelectable2Dを保持し、縦横の選択肢に対応する。
// また、項目数は最大で8個、各項目の文字サイズは32までに制限される。

#define WND_SELECTABLE_CONTENT		32
#define WND_SELECTABLE_STRLENGTH	32
#define WND_SELECTABLE_TITLELENGTH	32
#define WND_SELECTABLE_DEFPADDING	0
#define WND_SELECTABLE_DEFLINESPACE	4	// フォントに対する行の高さの差のデフォルト値。
										// ウィンドウサイズの計算に使用する。

#define WND_SELECTABLE_RESULT_NONE		-1	// まだ選択されていない
#define WND_SELECTABLE_RESULT_CANCEL	-2	// キャンセルボタンが押された

struct Window_Selectable_Content{
	TCHAR title[WND_SELECTABLE_TITLELENGTH];
	TCHAR data[WND_SELECTABLE_CONTENT][WND_SELECTABLE_STRLENGTH];
	Window_Selectable_Content(){
		strcpy_s(title, WND_SELECTABLE_TITLELENGTH-1, _T(""));
		for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
			strcpy_s(data[n], WND_SELECTABLE_STRLENGTH-1, _T(""));
		}
	};
};

class Window_Selectable : public Window_Text{
protected:
	Selectable2D select;
	Window_Selectable_Content content;
	// Setupで設定される項目
	// BYTE align;			// 文字の寄せ方。
	// int	lineHeight;		// 項目ごとの間隔。 
	// int hFont;			// フォントのハンドル
	bool useTitle;		// 選択肢にタイトルを表示するか否か。
	bool cancelable;	// キャンセル可能か否か
	// Setup時に自動で設定される項目
	int hTitleFont;		// タイトルに用いるフォント。
	int titleHeight;	// タイトルを描画するのに用いる高さ。
	int padding_bottom;	// 項目と枠下の間にある隙間。
						// ウィンドウサイズの設定に使用する。
	int row;			// 行の数
	int column;			// 列の数
	int result;			// 選択肢ウィンドウの結果
	int content_padding_x;		// 選択項目についてのパディング
	int content_margin_x;		// 列が複数ある場合の項目同士の幅
	int content_width;			// 項目の幅。自動計算される。
	// int color;
	bool autoClose;		// 選択肢を選んだ後、自動でウィンドウを閉じるか
public:
	// コンストラクタ。
	Window_Selectable();

	// 内容のセットアップを行う。
	void Setup(WindowSkin* _pSkin, int _x, int _y, 
		Window_Selectable_Content _content, int _column,
		int _hFont, int _fontHeight, int _lineHeight,
		bool _cancelable = false, bool _useTitle = false,
		BYTE _align = ALIGN_LEFT);

	// ウィンドウのタイトルを設定する。
	void SetTitle(LPTSTR title, int hTitleFont = 0);
	void GetTitle(LPTSTR str) const;
	// ウィンドウの内容を設定する。
	void SetContent(LPTSTR content, BYTE index);
	virtual void GetContent(LPTSTR str, BYTE index) const;
	// 結果を取得する。
	int GetResult() const { return result; };
	bool Choosed() const { return result != WND_SELECTABLE_RESULT_NONE; };
	// 省略時のパラメータを計算して代入する
	void SetAbbrParam();
	// デフォルトのウィンドウサイズなどの設定を適用する。
	void SetDefParam(bool autoSize=true);
	// インデックスの初期値を決める。
	void SetSelectIndex(WORD index){ select.index = index; };
	int GetSelectIndex(){ return select.index; };

	// 開かれた時の処理。
	// 選択された項目の初期化を行う。
	virtual void OnOpened();

	// 内容の更新を行う。
	virtual void Update();

	// 自動で閉じるかどうかの判定を行う
	virtual void CheckAutoClose(){};

	// 内容の描画を行う。
	// クラスごとに派生する。
	virtual void DrawContent() const;

};

#endif // WINDOW_SELECTABLE_H