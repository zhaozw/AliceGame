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
// ファイル内に#newlineと書くと、それをページ送りの合図とみなす。
// これ以外にも、#が先頭にある行の場合、
// 最初の単語を命令の種類、それ以降をスペース区切りのパラメータとして
// 特殊な行と判断して処理を行う。
// ノベルゲームのスクリプタのすごく簡単なバージョン。
// 
// ④ファイルの終端に達したら、その時点での内容をstockMessageに送り、
// そのメッセージの処理が終わった時点でファイルを閉じる。
// ファイルの終端は#exitで表現する。
// また、ifstreamのファイル末端の検知によっても同様の処理を行う。

class Window_HintMessage : public Window_Message{
protected:
	TCHAR fileName[MAX_PATH];	// ファイルの名前
	std::streamoff filePos;		// 何度も開いたり閉じたりする関係上
								// ファイルの位置を保持しておく
								// このクラス自身はifstreamを保持せず、
								// 行を読み込むたびに関数内で宣言して使用する
	int			lineCount;		// 現在読み込んだ行数
	TCHAR		buffer[WND_MSG_STOCKLINE][WND_MSG_STOCKLENGTH];	
								// 現在読み込んでいるデータ。
								// Window_Messageで使用するサイズだけ確保している。
								// (バッファの中身を一度にウィンドウに送ったりする時用)
	int			linePos;		// 現在、bufferの何行目までデータが入っているか
								// (次に読み込む位置のインデックス)

public:
	// コンストラクタ
	Window_HintMessage();
	// 内容のリセット
	void Clear();

	// ファイルを読み込み、その中身を
	// メッセージとして表示し、終わると閉じる関数。
	// 全部この関数だけでいいんじゃないかな。
	bool OpenAndPlay(LPTSTR fileName, WORD wndType);

	// ファイル名を指定する
	// 試しにファイルを開いてみて、開けなかったらfalseを返す
	bool SetFileName(LPTSTR name);

	// ファイルの中身を一行読み込む。
	bool ReadLine();

	// 現在のbufferの内容をstockLineに転送する。
	bool FlushBuffer();

	// アクセサ
	int GetLineCount(){ return lineCount; };
};


#endif // WINDOW_HINTMESSAGE_H
