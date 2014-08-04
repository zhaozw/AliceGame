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

class Window_HintMessage : public Window_Message{
protected:
	TCHAR fileName[MAX_PATH];		// ファイルの名前
	std::streamoff filePos;	// 何度も開いたり閉じたりする関係上ファイルの位置を保持しておく
					// このクラス自身はifstreamを保持しない

public:
	// コンストラクタ
	Window_HintMessage();
	// 内容のリセット
	void Clear();


};


#endif // WINDOW_HINTMESSAGE_H
