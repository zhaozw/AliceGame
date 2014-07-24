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

// 使用する方法としては、まずSetContentにより表示する内容を指定、
// 次にSetGridSizeまたはSetRowByContentSizeで選択肢の縦横の大きさを決め、
// 次にSetup、Setup_AutoMarginなどでウィンドウの位置や大きさを決める。
// 表示する度に内容が異なる場合は、毎回この順序を踏むが、
// ウィンドウサイズが固定の場合はSetup系関数は再度行う必要はない。
// Setup系関数からはWindow_Base::Setupが呼び出される。
// なお、文字がはみ出す場合などの救済措置はない（縮めて表示してくれたりはしない）。

#define WND_SELECTABLE_CONTENT		32
#define WND_SELECTABLE_STRLENGTH	32
#define WND_SELECTABLE_TITLELENGTH	32
#define WND_SELECTABLE_DEFPADDING	0
#define WND_SELECTABLE_DEFLINESPACE	4	// フォントに対する行の高さの差のデフォルト値。
										// ウィンドウサイズの計算に使用する。

#define WND_SELECTABLE_RESULT_NONE		-1	// まだ選択されていない
#define WND_SELECTABLE_RESULT_CANCEL	-2	// キャンセルボタンが押された

typedef struct Window_Selectable_Content{
	TCHAR	title[WND_SELECTABLE_TITLELENGTH];
	bool	useTitle;		// 選択肢にタイトルを表示するか否か。
	int		hTitleFont;		// タイトルに用いるフォント。
	int		titleHeight;	// タイトルを描画するのに用いる高さ。
	TCHAR	data[WND_SELECTABLE_CONTENT][WND_SELECTABLE_STRLENGTH];
	Window_Selectable_Content(){
		strcpy_s(title, WND_SELECTABLE_TITLELENGTH-1, _T(""));
		useTitle = false;
		hTitleFont = 0;
		titleHeight = 0;
		for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
			strcpy_s(data[n], WND_SELECTABLE_STRLENGTH-1, _T(""));
		}
	};
} WINDOW_SELECTABLE_CONTENT;

class Window_Selectable : public Window_Text{
protected:
	Selectable2D					select;
	WINDOW_SELECTABLE_CONTENT		content;
	// 内容のサイズに関して
	int		row;			// 行の数
	int		column;			// 列の数
	int		item_width;		// 項目の幅
							// マージンの大きさは項目の幅と内容の幅から自動的に決まる。

	// 関数の結果に関して
	int		result;			// 選択肢ウィンドウの結果
							// キャンセルの場合は-1を返す
	bool	cancelable;		// キャンセル可能か否か
							// CheckCancelable関数で
	bool	autoClose;		// 選択肢を選んだ後、自動でウィンドウを閉じるか
public:
	// コンストラクタ。
	Window_Selectable();

	// 内容を設定する。
	// 連動させて、その選択肢が選択可能かどうかも設定する。
	void	SetContent(WINDOW_SELECTABLE_CONTENT _content);	// 全部指定する場合
															// CheckActiveSelectを行う
	void	SetContent(
		LPTSTR _content, BYTE index, bool active=true);		// 一つずつ指定する場合
															// useTitleがtrueになる
	virtual void GetContent(LPTSTR str, BYTE index) const;

	// ウィンドウの内容を全てクリアする。
	// 文字をクリアするだけで、大きさなどは変更しない。
	void	ClearContent();	

	int		GetContentMaxDrawWidth() const;					// 項目の描画サイズのうち
															// 最も大きい値を取得
	// ウィンドウのタイトルを設定する。
	void	SetTitle(LPTSTR title, int hTitleFont = 0);
	void	GetTitle(LPTSTR str) const;
	
	// 選択肢の横の数と縦の数を設定する。
	void	SetGridSize(int _column, int _row){
		column = _column; row = _row;
		select.column = _column; select.row = _row;
	}

	// 選択肢の縦の数を現在の内容から決定する。
	void	SetRowByContentSize(int _column);

	// 内容の入っている選択肢をtrue、
	// 入っていない選択肢をfalseにする。
	// 内容が入っているけど選択出来ない、などは
	// 自分で設定する必要がある。
	void	CheckActiveSelect();

	// ウィンドウのセットアップを行う。
	// この時既に内容はセットされていて、
	// column値及びrow値が決まっている。
	// ここでは大きさなどを決める。
	void	Setup(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		WINDOWAREA _contentArea,
		WINDOWFONT _font,
		int itemWidth
		);

	void	Setup(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		int _px, int _py,
		WINDOWFONT _font,
		int itemWidth
		);
	
	// 内容のセットアップを行う。
	// 項目のサイズに応じて項目のサイズを自動で調整してくれる。
	void	Setup_AutoMargin(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		int _px, int _py,
		WINDOWFONT _font
		);

	// 内容のセットアップを行う。
	// 項目のサイズに応じてウィンドウの大きさを変えるという特殊なセットアップ。
	// 画面中央に出るウィンドウなどに使用する。
	// この関数を実行する前にSetGridSize関数を行う必要がある。
	/*
	void	Setup_FlexSize(WindowSkin* _pSkin, int _x, int _y, 
		Window_Selectable_Content _content, int _column,
		int _hFont, int _fontHeight, int _lineHeight,
		bool _cancelable = false, bool _useTitle = false,
		BYTE _align = ALIGN_LEFT);
		*/

	// 結果を取得する。
	int		GetResult() const { return result; };
	bool	Choosed() const { return result != WND_SELECTABLE_RESULT_NONE; };
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