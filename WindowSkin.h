#ifndef WINDOWSKIN_H
#define WINDOWSKIN_H

#include <Windows.h>

#define DEF_FRAME_SIZE 16
#define NUM_WND_IMG_ARRAY 10

// WindowSkinクラス
// ウィンドウスキン（ウィンドウの見た目）についての情報を保持するクラス。
// WindowSkinsクラスのグローバル変数であるg_wndSkinsが宣言され、
// そのメンバ変数であるskinとしてWindowSkinを列挙する形で保持する。
// 各WindowSkinへの参照をウインドウが保持することで参照を行う。

#define MAX_WNDSKIN					3
#define WNDSKIN_SIMPLE				0
#define WNDSKIN_NONE				1
#define WNDSKIN_BALLOON				2

class Window_Base;
class WindowSkin;


// ウィンドウスキン
#define MAX_WNDIMGINDEX					9
#define WNDIMGINDEX_TOPLEFT				0
#define WNDIMGINDEX_TOP					1
#define WNDIMGINDEX_TOPRIGHT			2
#define WNDIMGINDEX_LEFT				3
#define WNDIMGINDEX_CENTER				4
#define WNDIMGINDEX_RIGHT				5
#define WNDIMGINDEX_BOTTOMLEFT			6
#define WNDIMGINDEX_BOTTOM				7
#define WNDIMGINDEX_BOTTOMRIGHT			8
#define WNDIMGINDEX_NOFRAME				0
#define WNDIMGINDEX_HEADER_CENTER		3

class WindowSkin{
public:
	enum FRAMETYPE{
		FT_NOIMAGE,		// 画像なし
		FT_EXTEND,		// 枠はそのまま描画、中身は引き伸ばし
		FT_NOFRAME,		// 枠なし、中心画像を引き伸ばす
		FT_HEADER,		// 上端のみ独立、メイン部分は引き伸ばしで表示
	}; 

	enum WNDOPENTYPE{
		OT_NONE,		// 完全に開いたときだけ描画、他は描画しない
		OT_FADE,		// その場にフェードイン
		OT_EXPAND_Y,	// 縦方向に開く
	};
private:
	// 決まった順番で並べられた画像の配列への参照。
	int *wndImgArray;
	// ウィンドウスキンのID。
	// 選択項目の描画などに使用する。
	BYTE wndSkinID;
	// 枠の太さ。
	int frameSize;
	// 画像の組み合わせ方のタイプ。
	enum FRAMETYPE frameType;
	// ウィンドウを開くときのアニメーションの仕方のタイプ。
	enum WNDOPENTYPE openType;
	// ウィンドウを開くのに要する時間。
	int openTime;
public:
	// コンストラクタ
	WindowSkin();
	// 画像を割り当てる
	bool AttachImage(int* _img, BYTE _wndSkinID, int _frameSize,
		FRAMETYPE _type, WNDOPENTYPE _oType, int _openTime);

	// 描画
	// 引数のポインタにconstをつけることにより
	// 値を変更できなくする。
	void Draw(int _x, int _y, int _w, int _h, int _openLevel) const;
	void Draw_FT_Extend(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;
	void Draw_FT_NoFrame(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;
	void Draw_FT_Header(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;

	// 選択されている項目のハイライトの描画
	void DrawFocus(int x, int y, int width, int height, int time) const;

	// アクセサ
	int GetFrameSize(){ return frameSize; };
	int GetOpenTime(){ return openTime; };

};

class WindowSkins{
public:
	WindowSkin skin[MAX_WNDSKIN];
	// ウィンドウスキンへの割り当てを行う。
	bool AttachImages();
};


#endif // WINDOWSKIN_H