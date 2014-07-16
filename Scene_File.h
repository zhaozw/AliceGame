#ifndef SCENE_FILE_H
#define SCENE_FILE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Game_FileHeader.h"
#include "Func_AliceFile.h"
#include "Window_Yesno.h"

#define DRAW_FILE_BASEY		60
#define	DRAW_FILE_WIDTH		350
#define	DRAW_FILE_HEIGHT	100
#define	DRAW_FILE_MARGINY	20
#define DRAW_FILE_WLH		(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)
#define	DRAW_SELECTED_WIDTH		350
#define	DRAW_SELECTED_HEIGHT	500
#define FILESELECT_SCROLL_TIME		(DELAY_DIGDIR2+1)
#define FILESELECT_FILE_PER_PAGE	4

#define SCNSTATE_FILE_CHOOSEFILE		0		// ファイルの選択中
#define SCNSTATE_FILE_ASKOVERWRITE		1		// ファイルを上書きするかを問う	

class Scene_File : public Scene_Base{
private:
	// 現在のモード。初期化時にGame_Tempからコピーする。
	int mode;
	// ファイル間を移動しているフラグ。
	// 0:停止中
	// 1:下降中
	// 2:上昇中
	BYTE moving;
	int movingTime;
	// 現在画面内に表示されているファイルの一番上のインデックス。
	// 初期状態では0。
	int drawIndex;
	// ファイルを選択する選択肢。
	Selectable		s_file;
	// 「はい」「いいえ」を表示するウィンドウ。
	Window_Yesno	w_yesno;
	// 各ファイルのファイルヘッダのコピー。
	Game_FileHeader header[MAX_SAVEFILE];
	// 各ファイルのデータが既に存在するか否か。
	bool isFile[MAX_SAVEFILE];
public: 
	// コンストラクタ
	Scene_File();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	// ウィンドウの初期化
	bool InitWindow();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;

	// 基準位置を指定してセーブファイルの内容を描画する
	void DrawSaveFile(int x, int y, BYTE index,
		bool isActive, bool canSelect) const;
	// 基準位置を指定してデータのないファイルの内容を描画する
	void DrawEmptyFile(int x, int y, BYTE index,
		bool isActive, bool canSelect) const;
	// 基準位置を指定して詳細なファイルの内容を描画する
	void DrawSelectedFile(int x, int y, BYTE index) const;

};

#endif // SCENE_FILE_H