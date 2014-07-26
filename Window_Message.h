#ifndef WINDOW_MESSAGE_H
#define WINDOW_MESSAGE_H

#include <Windows.h>
#include "Window_Text.h"

class Window_Message_DrawLine;
class Window_Message_DrawMsg;
class Window_Message_StockLine;
class Window_Message_StockMsg;
class Scene_Base;

// 各種定数の定義
#define WND_MSG_DRAWLINE		4		// 表示する行数
#define WND_MSG_DRAWLENGTH		48		// 表示時・一行あたりの文字数	
#define WND_MSG_STOCKLINE		8		// 内容をストックする行数
#define WND_MSG_STOCKLENGTH		128		// ストック時・一行あたりの「バイト数」

// メッセージ内の文字のフラグ
#define F_MSGCHAR_ENDMSG		0x0001	// 文章の終端を表す
#define F_MSGCHAR_ONE_BYTE		0x0002	// 1バイト文字である

// 文字送りなどのフラグ
#define F_READTYPE_QUICK		0x0001	// 文章の途中でも決定キーで瞬間表示
#define F_READTYPE_AUTOQUICK	0x0002	// キャンセルキーで決定キー押しっぱなし効果
#define F_READTYPE_DIRECTQUICK	0x0004	// 瞬間表示の際に次の行に進む
#define F_READTYPE_NOWAIT		0x0008	// 文章を瞬間的に表示する(messageSpeed値を無視)
#define F_READTYPE_PUSH			0x0010	// 次に表示する文章がある場合、自動で進める
#define F_READTYPE_FLOOD		0x0020	// 次に表示する文章があってもなくても進める
#define F_READTYPE_AUTOPLAY		0x0040	// 決定キーやキャンセルキーによる進行が出来ない。
										// （常に時間経過のみによって進行する）
#define F_READTYPE_BLANKLINE	0x0080	// ストックが空の時に決定キーを押すと
										// 空行を挿入して次の行に進む。
										// フラグを指定しない場合、
										// ストックがない場合ページ送りをしない。
										// 


// メッセージスピード
#define WND_MSG_DEFSPD			1.0


// バトルメッセージウィンドウで表示する一文字の情報を保持する構造体。
typedef struct Window_Message_DrawChar{
	TCHAR		character[3];	// 一文字
	WORD		flags;			// 文字装飾やタイミング調整に用いるフラグ
	bool		used;
	Window_Message_DrawChar(){
		for(int n=0; n<3; n++){
			character[n] = '\0';
		}
		flags = 0x0000;
		used = false;
	}
} WINDOW_MESSAGE_DRAWCHAR;

// バトルメッセージウィンドウで表示する一行の情報を保持する構造体。
// 描画位置はWindow_Messageクラス内で保持する。
class Window_Message_DrawLine{
public:
	WINDOW_MESSAGE_DRAWCHAR	chars[WND_MSG_DRAWLENGTH]; // 行内の各文字
	WORD					flags;	// 文字装飾やタイミング調整に用いるフラグ
public:
	// コンストラクタ
	Window_Message_DrawLine();
	// 内容をクリアする
	void Clear();
	// スタックから内容をインポートする。
	bool Import(LPTSTR buf, int strLen);
	// 現在の内容の文字数を取得する。
	int GetStrLength() const;
	// 自身の内容を描画する。
	// hFont	: 描画に用いるフォント
	// fontWidth: フォントの幅
	// x, y		: 描画位置(絶対座標)
	// count	: 描画する文字数。-1を指定すると全ての文字を描画。
	void DrawContent(int hFont, int fontWidth, int x, int y, int count=-1) const;
};

// バトルメッセージウィンドウで表示するメッセージ全体の情報を保持するクラス。
class Window_Message_DrawMsg{
private:
	Window_Message_DrawLine	lines[WND_MSG_DRAWLINE];	// 各行
	int						index; // 現在描画中の行のインデックス
public:
	// コンストラクタ
	Window_Message_DrawMsg();
	// 指定した行のクリア
	void ClearLine(int n);
	// 文章内容を全てクリア
	void ClearAll();
	// アクセサ
	int GetIndex() const{ return index; };
	// 現在の行の文字数を求める
	int GetLineLength(int historyCount=0) const;
	// 指定した行を描画する。
	void DrawLine(int hFont, int hFontWidth,
		int x, int y, int count=-1, int historyCount=0) const;
	// 空の行に描画する内容を追加する。
	// 行の長さについての確認は行わない。
	bool ImportLine(LPTSTR buf);
	// 空の行を挿入する。
	void BlankLine();
};

// バトルメッセージウィンドウで情報をストックする一行の情報を保持する構造体。
class Window_Message_StockLine{
public:
	TCHAR		chars[WND_MSG_STOCKLENGTH];
public:
	// コンストラクタ
	Window_Message_StockLine();
	// 内容のクリア
	void Clear();
	// 中身が空かどうかを返す
	bool IsEmpty();
	// 文字列のポインタを渡す
	TCHAR*		GetCharsPtr(){ return chars; };
};

// バトルメッセージウィンドウで情報をストックする全体の情報を保持するクラス。
class Window_Message_StockMsg{
private:
	Window_Message_StockLine		lines[WND_MSG_STOCKLINE]; // 各行
	int								index; // 次に処理する行のインデックス
	int								emptyIndex;	// 次に内容を追加する行のインデックス
												// 空かどうかの判定はAddMsg時に行う
public:
	// コンストラクタ
	Window_Message_StockMsg();

	// 指定した行の内容をクリア
	void ClearLine(int n);

	// 内容を全てクリア
	void ClearAll();

	// 空の行に指定したテキストの内容をコピーする
	bool AddMsg(LPTSTR str, int strlen);

	// 現在の行の内容を指定した領域に読み出す。
	// バッファサイズはチェックしない。
	// discard : 読み出した際、読み出した内容をストックから除外する。
	// エラーがあった場合、内容が空の場合はfalseを返す。
	bool ReadLine(LPTSTR buf, bool discard);

	// 現在の行が空かどうかをチェックする。
	bool IsEmpty(){ return lines[index].IsEmpty(); };

	// 現在の内容をストックから除外する。
	void DiscardLine();

};

// Window_Messageクラス
// 戦闘中に流れるメッセージを表示するクラス。

class Window_Message : public Window_Text{
public:
	enum SUBSTATE{
		WNDSUBSTATE_NOTEXT,		// テキストがない状態
		WNDSUBSTATE_READING,	// 行を読んでいる状態
		// WNDSUBSTATE_CLICKWAIT,	// クリック待ちの状態
		WNDSUBSTATE_UNDIFINED,
	};
protected:
	// 描画中のメッセージ
	Window_Message_DrawMsg	drawMsg;
	// 内容を保持しているメッセージ
	Window_Message_StockMsg	stockMsg;
	// サブステート
	enum SUBSTATE			subState;
	// 文字送りパターン
	WORD					readTypeFlag;
	// 描画中の行の現在の位置
	int						linePos;
	// 現在の行の表示が始まってからの時間
	int						lineCount;
	// 少なくともこのフレーム数経つまでは次の行に進まない
	int						lineCountMin;
	// クリック待ちを行っているフレーム数
	int						clickWaitCount;
	// クリック待ちを自動で飛ばすフレーム数
	int						clickWaitTime;
	// フォントの横幅
	int						fontWidth;
	// 1フレームあたりに勧める文字数
	float					messageSpeed;

public:
	// コンストラクタ
	Window_Message();

	// 内容のセットアップ
	void Setup(WindowSkin* pSkin, WINDOWAREA _frameArea, WINDOWAREA _contentArea,
		bool _visible);
	void Setup_FixPadding(WindowSkin* pSkin, WINDOWAREA _frameArea,
		int _px, int _py, bool _visible);
	void Setup_FixContentWidth(WindowSkin* pSkin, WINDOWAREA _frameArea,
		int _content_width, int _py, bool _visible);
	
	// 内容を全てクリア(Setup時、コンストラクタ時に使用)
	void ResetAll();

	// 描画時のフォントの幅を指定
	// (半角文字の場合は自動で半分の値が指定される)
	void SetFontWidth(int width){ fontWidth = width; };

	// stockMsgに内容を追加する。
	bool AddStockMsg(LPTSTR str, int strlen);

	// 現在描画中の行が空であるかどうかを返す。
	bool DrawMsgIsEmpty(int historyCount=0){
		return drawMsg.GetLineLength(historyCount) == 0; };

	// stockMsgが空かどうかを返す。
	bool StockIsEmpty(){ return stockMsg.IsEmpty(); };

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// Window_Messageクラスから派生するクラスのアップデート。
	// さらにクラスごとに派生する。Update関数内から実行される。
	virtual void ExUpdate();

	// Window_MessageクラスのウィンドウがIDLEになる条件を示す。
	virtual bool CheckIsIdle();

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// メッセージを改行する。
	// 具体的には、stockMsgの内容を1行分読み出し、
	// drawMsgの新しい行に対して読み出したstockMsgの内容を渡して文字列に変換する。
	// 
	// force : trueの場合、表示するべきメッセージがなくても改行する。
	// この場合、stockMsgの内容を読み出しはせず、
	// drawMsgには文字を含まない空行を渡す。
	void NewLine(bool force);

	// メッセージの更新の判定を行う。
	void UpdateLine();

	// メッセージの改行の判定を行う。
	// 実際の改行までこの関数内で行う。
	// chooseKey	: 決定キーが「この瞬間に」押されたかどうか
	// skipKey		: スキップキーが「押されっぱなし」かどうか
	// 戻り値		: 改行を行ったかどうか
	bool CheckNewLine(bool chooseKey, bool skipKey);

	// 次に表示するべき文章が存在するかどうかの判定を行う。
	bool CheckStockMsg();

	// 現在の行の文字数を取得する。
	int GetLineLength();
	int GetClickWaitCount(){ return clickWaitCount; };
	void SetClickWaitTime(int t){ clickWaitTime = t; };
	int GetClickWaitTime(){ return clickWaitTime; };

	// アクセサ
	void SetReadType(WORD flag){ readTypeFlag = flag; };
	WORD GetReadType(){ return readTypeFlag; };
	
	// 内容1行の描画を行う。
	// dx, dy : ウィンドウの左上に対する位置
	// historyCount :	0の場合、最新の行を描画。
	//					1以上の場合、それより指定した数だけ古い行を描画する。
	//					無効な数値の場合は描画しない。
	void DrawLine(int dx, int dy, int historyCount=0) const;
	void DrawCurrentLine(int dx, int dy) const;
	void DrawHistoryLine(int dx, int dy, int historyCount=1) const;

};

// StockMessageとDrawMessageの紛らわしいところの補足
// StockMessageに関しては、次に読み込むのは一番最初に追加されたストックである。
// そして、次に追加されるのは一番最後に追加されたストックの次のインデックスであり
// indexとemptyIndexを別のメンバとして持っていないと（もしくは毎回計算しないと）
// 次に追加すべきインデックスが分からない。
// 一方、DrawMessageはストックから読み込まれる行が次に表示する行であり、
// 既に内容が入っている行は全て履歴である。
// そのため、新しい行を読み込むときは、さきほどまで表示していた行の次の行に
// 常に内容を読み込めば良い。そのため、emptyIndexメンバは不要となる。

#endif // WINDOW_MESSAGE_H