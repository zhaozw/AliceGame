#ifndef WINDOW_ENTERNAME_H
#define WINDOW_ENTERNAME_H

#include "Window_Base.h"
#include "Selectable2D.h"

// nameTypeに入る値
#define NAMETYPE_DOLLNAME		1	// 人形の名前の入力

// 文字盤の大きさ
#define WINDOW_NAME_COLUMN		11	// 5+5+1
#define WINDOW_NAME_ROW			9	// 5+3+1

// ウィンドウのサイズとパディング
#define WND_ENTERNAME_WIDTH		500
#define WND_ENTERNAME_HEIGHT	420
#define WND_ENTERNAME_PX		40
#define WND_ENTERNAME_PY		40

#define WND_ENTERNAME_PAGE_KATA			0 // カタカナ
#define WND_ENTERNAME_PAGE_HIRA			1 // ひらがな
#define WND_ENTERNAME_PAGE_ALPHABET		2 // アルファベット・数字

// 名前を入力するウィンドウのクラス。
// 入力した名前はグローバル変数g_tempに代入される。
// 入力できる名前の文字はカタカナ、ひらがな、英数記号の3ページで表示される。
// 内部的には各文字はBYTE型の配列で管理される。

class Window_EnterName : public Window_Base{
private:
	// 入力する名前のタイプ。
	WORD nameType;
	// 現在表示しているページ。
	BYTE page;
	// 選択肢
	Selectable2D s_chars;
public:
	// アクセサ
	void SetNameType(WORD t){ nameType = t; };

	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup(WORD _nameType);

	// コンストラクタ
	Window_EnterName();

	// カーソルの位置と文字のインデックスを対応させる。
	WORD GetNameIndex(int pos_x, int pos_y, BYTE page) const;
	// 描画すべき位置を取得する。
	int GetDrawX(int pos_x, int pos_y) const;
	int GetDrawY(int pos_x, int pos_y) const;

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// 名前ウィンドウの特殊文字を描画する。
	void DrawSpecialChar(int x, int y, BYTE index, bool isLarge) const;
};

#endif // WINDOW_ENTERNAME_H