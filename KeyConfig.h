#ifndef KEYCONFIG_H
#define KEYCONFIG_H

// デフォルトのキー名を指定
#include <DxLib.h>

// 定数
#define MAX_BUTTON			4
// デフォルトのキー配置
#define DEF_INPUT_0		(PAD_INPUT_A) // ショットボタン
#define DEF_INPUT_1		(PAD_INPUT_B) // 低速ボタン
#define DEF_INPUT_2		(PAD_INPUT_C) // ボムボタン
#define DEF_INPUT_3		(PAD_INPUT_X) // Exショットボタン
#define DEF_INPUT_4		(PAD_INPUT_START) // 一時停止ボタン

//=========================================
// KeyConfigクラス
// ボタン操作に関するコンフィグの部分要素。

class KeyConfig{
public:
	int		input[MAX_BUTTON];		// キー割り当て。
									// 0: 決定ボタン
									// 1: キャンセルボタン
									// 2: 情報表示/非表示ボタン
									// 3: スクリーンショットを撮る

	// コンストラクタ
	KeyConfig();

	// 値を読み込む
	bool LoadKeyConfig();

	// 値を保存する
	bool SaveKeyConfig();

	// キー名と整数値の切り替え
	int KeyToInt(TCHAR i);
	TCHAR IntToKey(int i);

	// キー設定を初期に戻す。
	void ResetConfig();
};

#endif // KEYCONFIG_H