#ifndef DXFONT_H
#define DXFONT_H

// フォントサイズの列挙
#define FONTSIZE_INFO		24
#define FONTSIZE_STR		24
#define FONTSIZE_STR_L		32
#define FONTSIZE_TINYINFO	16
#define FONTSIZE_TALK		28

// 関数名の短縮
#ifndef ABBR_GETDRAWSTRINGWIDTHTOHANDLE
#define ABBR_GETDRAWSTRINGWIDTHTOHANDLE
#define GetStrWidth GetDrawStringWidthToHandle
#endif // ABBR_GETDRAWSTRINGWIDTHTOHANDLE

#ifndef ABBR_DRAWSTRINGTOHANDLE
#define ABBR_DRAWSTRINGTOHANDLE
#define DrawStr DrawStringToHandle
#endif // ABBR_DRAWSTRINGTOHANDLE

//==================================================
// DXFontクラス
// 
// 画像のハンドルをまとめて保持するグローバル変数。
// グローバル変数g_imageから参照される。
// 

class DXFont{
public:
	// フォントのハンドルを列挙する。
	int hInfo;
	int hStr;		// 文字。名前の描画にも用いる。
	int hStrL;		// 大きいサイズの文字。名前の描画にも用いる。
	int hTinyInfo;	// 戦闘中のHP描画など。小さい文字。
	int hTalk;		// 会話文など。
public:
	// コンストラクタ。
	// 全てのハンドルに-1を代入する。
	DXFont();

	// ロード。
	// 失敗したらfalseを返す。
	bool Load();

	// フォントの解放。
	// 失敗したらfalseを返す。
	bool Release();
};

#endif // DXFONT_H