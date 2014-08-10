#ifndef WINDOW_HINTMESSAGE_H
#define WINDOW_HINTMESSAGE_H

#include "Window_Message.h"
#include <tchar.h>
#include <streambuf>

// ヒントメッセージを表示するクラス。
// 所定の書式で書かれたファイルを読み込み、表示する。
// 基本的な使い方として、ゲーム画面の最前面に表示され、
// それが表示されている間は他のウィンドウやコマンドへの入力は受け付けず、
// 全てのメッセージを表示したところで内容を閉じる。
// CsvReaderクラスのように、ファイルポインタとファイル位置を保持している。
// 単独の機能として暗号化も実装する（予定）。
//
// 関数OpenAndPlayを行うと、ウィンドウが開き、ファイルの中身を読み込んで
// ウィンドウに表示し、決定ボタンによるページ送りを行いながら
// ファイルの中身を次々と読んでいき、
// 終端まで行くと閉じる。
// 基本的にこのクラスを利用する時はこの関数を利用する。
// 
// ①ファイルを開く
// OpenAndPlay関数を行うと、まずファイルがあるかどうかを確認し、ウィンドウを開く。
// 失敗したらこの時点でfalseを返す。
// これ以降、Windowのstate値は閉じられる時までWNDSTATE_UPDATEのまま。
// 
// ②ファイルの中身を読み込む
// ファイルを先頭から一行ずつ読んでいく。
// 読んだ行の中身はbufferにセットされていく。
// ファイルの中身が暗号化されたものであれば、この時、行単位で複号を行う。
//
// ③ページ送りまで達したら、Window_MessageのstockMessageに内容を送る
// ファイル内に#newpageと書くと、それをページ送りの合図とみなす。
// これ以外にも、#が先頭にある行の場合、
// 最初の単語を命令の種類、それ以降をスペース区切りのパラメータとして
// 特殊な行と判断して処理を行う。
// ノベルゲームのスクリプタのすごく簡単なバージョン。
// 
// ④ファイルの終端に達したら、その時点での内容をstockMessageに送り、
// そのメッセージの処理が終わった時点でファイルを閉じる。
// ファイルの終端は#exitで表現する。
// また、ifstreamのファイル末端の検知によっても同様の処理を行う。


// typeIDの値
#define WND_HINT_TYPE_UNDIFINED			0		// SetupByTypeIDが実行される前
#define WND_HINT_SHANGHAI				1		// シャンハイ人形のヒント
#define WND_HINT_ALICE					2		// アリスのヒント

// NewPageの戻り値
#define WND_HINT_NEWPAGE_OK				0		// 次に読み込む文章が見つかり、
												// 読み込みに成功した。
#define WND_HINT_NEWPAGE_OVERFLOW		1		// 文章は読み込んだが、
												// ページ区切りが見つからず
												// 適当な位置で区切った。
#define WND_HINT_NEWPAGE_END			2		// 文章の末端に達した。
#define WND_HINT_NEWPAGE_ERROR			3		// 読み込み時にエラーが発生した。

// CheckCommandの戻り値
#define WND_HINT_CHKCMD_NONE			0		// コマンドではない
												// (普通に内容をコピーする)
#define WND_HINT_CHKCMD_ERROR			1		// なんかおかしい
#define	WND_HINT_CHKCMD_NEWPAGE			10		// ページの末端
#define WND_HINT_CHKCMD_END				11		// 内容の末端

class Window_HintMessage : public Window_Message{
protected:
	WORD		typeID;			// ウィンドウの大きさ、背景、フォントなど
								// 一通りの情報を与えるためのID番号。
								// SetupByTypeIDで指定した値が代入される。
	TCHAR fileName[MAX_PATH];	// ファイルの名前
	std::streamoff filePos;		// 何度も開いたり閉じたりする関係上
								// ファイルの位置を保持しておく
								// このクラス自身はifstreamを保持せず、
								// 行を読み込むたびに関数内で宣言して使用する
	int			lineCount;		// 現在読み込んだ行数
	TCHAR		buffer[WND_MSG_DRAWLINE][WND_MSG_STOCKLENGTH];	
								// 現在読み込んでいるデータ。
								// Window_Messageで使用するサイズだけ確保している。
								// (バッファの中身を一度にウィンドウに送ったりする時用)
								// 描画における1ページ分を最大でストックするため、
								// バッファの大きさは描画行数×ストック長さとなる。
	bool		isError;		// 文書の読み込みでエラーが発生している状態。
	bool		isTerminated;	// 文書の最後まで読み込み終わり、
								// 現在の文を表示し終わったら閉じる状態。

public:
	// コンストラクタ
	Window_HintMessage();
	// 内容のリセット
	void Clear();

	// バッファのリセット
	void ClearBuffer();


	// ファイルを読み込み、その中身を
	// メッセージとして表示し、終わると閉じる関数。
	// 全部この関数だけでいいんじゃないかな。
	bool OpenAndPlay(LPTSTR fileName, WORD _typeID);

	// ウィンドウの種類に関するパラメータを指定し、
	// ウィンドウの位置や背景、文字色などを設定する。
	// 多くのウィンドウはシーンの最初にSetupを行うが、
	// Window_HintMessageは使用する直前にSetupを行う。
	// これは、一度に一個しかウィンドウが出ないが、
	// 同じシーンでも複数タイプのウィンドウを使う場合があることに関係する。
	// OpenAndPlayでwndType値に0以外を入れるとその値を引数として
	// この関数を実行するため、基本的に単独で実行する必要はない。
	bool SetupByTypeID(WORD _typeID, bool check);

	// ファイル名を指定する
	// 試しにファイルを開いてみて、開けなかったらfalseを返す
	bool SetFileName(LPTSTR name);

	// ウィンドウが開いた時やページが送られた時など、
	// ウィンドウの表示内容がなくなった時に実行される。
	// ファイルの中身を一ページ分（次に表示する分）だけ読み込み、
	// stockLineにデータを蓄積する。
	BYTE NewPage();

	// 現在のbufferの内容をstockLineに転送する。
	bool FlushBuffer();

	// コマンドを確認する
	WORD CheckCommand(LPTSTR buf);

	// アクセサ
	int GetLineCount(){ return lineCount; };

	// 内容を更新する
	virtual void ExUpdate();

	// IDLE状態になる条件
	virtual bool CheckIsIdle();

	// 描画
	virtual void DrawFrameBack() const;		// 背景の人形などの描画
	virtual void DrawContent() const;

};


#endif // WINDOW_HINTMESSAGE_H
