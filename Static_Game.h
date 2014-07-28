#ifndef STATIC_GAME_H
#define STATIC_GAME_H

//===================================================
// ゲーム全体に関する定数を定義する。

// ゲームのタイトル
#define WND_TITLE "ゲームフォーマット"

// ベースとなるウィンドウの幅
// (描画する時の基準であり、実際の画面幅とは異なる場合がある)
#define WND_WIDTH	800
#define WND_HEIGHT	600

// 存在するシーンの羅列。
#define SCENE_NONE			0		// ダミーシーン。
#define SCENE_ERROR			-1		// 何かエラーが発生した時に代入する値。
#define SCENE_END			-2		// ゲームを終了する時に代入する値。
#define SCENE_SAMPLE		1		// サンプルシーン。削除してもよい。
#define SCENE_TITLE			2		// タイトル画面。
#define SCENE_FILE			3		// ファイルのセーブ・ロード画面。
#define SCENE_CAMP			4		// キャンプ画面。
#define SCENE_DOLLCREATE	5		// キャンプ画面。
#define SCENE_DOLLBIRTH		6		// キャンプ画面。
#define SCENE_BATTLE		7		// 戦闘画面。
#define SCENE_TESTBATTLE	8		// テストバトル選択。

// ボタンの名称の羅列。
// 作るゲームに合わせて覚えやすいように変える。
#define BTN_CHOOSE		0	// 決定ボタン
#define BTN_CANCEL		1	// キャンセルボタン
#define BTN_SHOWINFO	2	// 情報ウィンドウの表示・非表示切り替えボタン
#define BTN_SCREENSHOT	3	// スクリーンショットを撮るボタン
#define BTN_D 3		// キャラチェンジボタン・スキップボタン
#define BTN_E 4		// 一時停止ボタン

//===================================================
// ゲームで使用する機能について記述する定数。
// 使わない場合はコメントアウトする。

// フォントを使用するか否か。
#define MYGAME_USE_FONT

// 3Dを使用するか否か。
#define MYGAME_USE_3D

// FPS調節を使用するか否か。
#define MYGAME_USE_TIMECTRL

// コンフィグ(ウィンドウサイズ、SE、BGMの調整)を使用する(ファイルに書き出す)か
#define MYGAME_USE_CONFIG		

// キーコンフィグを使用する(ファイルに書き出す)か
#define MYGAME_USE_KEYCONFIG

// 2人プレイを使用するか否か
// #define MYGAME_USE_2P	

// キーボード入力とゲームパッド入力を同時に処理するか
#define MYGAME_USE_PAD_AND_KEY

// メモリチェックを使用するか否か
#define MYGAME_USE_CHECKMEMORY

// 基本的なエラーログを使用するか否か。
#define MYGAME_USE_CRT_LOG

// DXライブラリのログを使用するか否か。
#define MYGAME_USE_DXLIB_LOG

// 致命的なバグで終了する時にメッセージボックスを出すか否か。
#define MYGAME_USE_WARN_ERROR

// Luaを使用するか否か。
// #define MYGAME_USE_LUA

//===================================================
// ゲームの性質に合わせて変更する定数。

// ゲームにおける基準方向(角度0の方向)を決める。
// 以下のどれか一つのみのコメントを外すと。Func_Mathの内容が変化する。

// 下方向を角度0とし、時計回りが正方向。画像は進行方向を下にする。
// 縦スクロールSTGなどに便利な座標系。
// #define MYGAME_DEFDIR_Y_AXIS

// 右方向を角度0とし、時計回りが正方向(下方向がy軸正方向のため)。
// 画像は進行方向を右にする。
// 横スクロールアクションなどに便利な座標系。
#ifndef MYGAME_DEFDIR_Y_AXIS
#define MYGAME_DEFDIR_X_AXIS
#endif // MYGAME_DEFDIR_Y_AXIS

//===================================================
// 参照する外部ファイル名に関する定数を定義する。

#define FILE_CONFIG "config.ini"


#define ARCHIVE_EXTENSION "dxa"

//===================================================
// デバッグなどに関する記述。基本的に変更しない。

// doubleからfloatに変換する際の警告を無視する
#ifndef DISABLE_WARNING
#define DISABLE_WARNING
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#endif // DISABLE_WARNING

// 一回だけメモリリーク防止のファイルを読み込む
#ifndef _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#ifdef MYGAME_USE_LUA
#include <lua.hpp>
#endif // MYGAME_USE_LUA

// ロケールの設定
#include <locale.h>

//===================================================
// 通常は変更しない定数群。

// フレームレート
// 基本的に60。
#define FPS			60

// 円周率
// (MATH_PIの略)
#define M_PI 3.14159265

// 文字や内容の整列させ方。
#define ALIGN_LEFT		0	// 左寄せ
#define ALIGN_CENTER	1	// 中央揃え
#define ALIGN_RIGHT		2	// 右寄せ


#endif