#ifndef FUNC_GRAPHICS_H
#define FUNC_GRAPHICS_H

#include <Windows.h>
#include <DxLib.h>

struct MYCOLOR3{
	MYCOLOR3(int r, int g, int b){
		R = r;
		G = g;
		B = b;
	}
	int R;
	int G;
	int B;
};


// int型の配列を渡すと指定した位置に数値の描画を行う。
// 戻り値 : 描画した幅。
int const DrawIntArray(int x, int y, int* image, int* nArray, int num, int wid,
	BYTE align=2, bool useComme=true, bool zerofill=false, float rate=1.0f);

// 得点を描画する。
void const DrawScore(int score, int score8dig, int x, int y, int* image,
	int wid, BYTE align=2, bool zerofill=false, bool useComme=true,
	int dig=10, float rate=1.0f);

// 数字を描画する。
void const DrawNum(int num, int x, int y, int* image,
	int wid, int dig, 
	BYTE align=2, bool zerofill=false, bool useComme=true,
	float rate=1.0f);

// A～Zの並びを持つ画像を用いて、DXライブラリで画像を描画する。
// 領域のチェックなどは行わないため、要注意。
void DrawStr(LPTSTR text, int x, int y, int wid, int* image);

// 読み込んだフォントを用いて、グラデーション付きの文字を描画する。
// 内部で描画範囲を指定した文字描画を複数回行うことにより実現する。
// 大雑把なグラデーションなので使用時は微調整を要する。
// また、使用後はSetDrawAreaが無効になる。
// (全体に描画するようになる)。
// そのため、
void DrawGradStrToHandle(const TCHAR* text, int hFont, int x, int y, int size, 
						 MYCOLOR3* upColor, MYCOLOR3* btmColor, int step,
						 int wndWid=800, int wndHei=600, int edgeColor=0);

// 虹色関数のうち一色。
// 虹色関数から呼び出される。
int GetRainbow(int i);
int GetRainbowR(int i);
int GetRainbowG(int i);
int GetRainbowB(int i);
#define RAINBOW_PARAM_CYCLE 1536

// 虹色関数
// 指定した値によって虹色に変化する色を返す。
int GetRainbowColor(int i);

// 画像を端からフェードさせる。
// hImg 画像のハンドル
// x, y 描画の左上の位置。
// width, height 画像の幅と高さ。
// grad ピクセルあたりの透明度の変化。
// zeropoint 透明度が0になる点。
// horizon 横方向にフェードか、縦方向にフェードか。
// reverse 通常は左側・上側が半透明だが、reverseがtrueだと右側・下側が半透明になる。
// blendmode 画像の合成モード。
void DrawFadeGraph(int hImg, int x, int y, int width, int height,
					float grad, int zeropoint, int blendmode,
					bool horizon=true, bool reverse=false);

// 画像を波状に描画する。
// count 波立たせる用のカウント。通常existTimeを使用。
// hImg 画像のハンドル。
// x, y 描画の左上の位置。
// height 画像の高さ。
// width 画像の幅。
// span 画像の揺れ幅。
// speed 画像が揺れる速度。
// pitch 画像の波立ち具合。
void DrawWaveGraph(int count, int hImg, int x, int y, int height, int width,
				   float span, float speed, float pitch);

// 画像を流れるようにフェードインさせる。
// 画像を高さ方向に切り分け、ある位置より上または下にある部分を
// 等加速度かつ透明にする。
// hImg : 画像のハンドル
// x, y : 画像の基準位置
// borderY : 画像の変形が始まる画像の位置。
//			 0だと完全に変形しない、widだと全ての領域について変形する。
// wid, hei : 画像のサイズ
// fromTop : 画像が上から（へ）フェードするか。
// deltaGrad : 画像の変形に使用する係数。
// alphaGrad : 画像の透明度の係数。
// alphaBase : 画像の透明度の基本値。
void DrawFlowGraph(int hImg, int x, int y, int borderY, int wid, int hei,
					 bool fromTop, float deltaGrad, float alphaGrad, int blendMode, float alphaBase=1.0f);

// 文字列を中央揃えしたい場合の、
// 左上からずらすべきx変位を求める。
// str		: 中央揃えする文字列
// strLen	: 文字列の長さ
// hFont	: フォントハンドル
// width	: 文字を入れる領域の幅
int GetRightAlignDX(LPTSTR str, int strLen, int hFont, int width);
int	GetCenteringDX(LPTSTR str, int strLen, int hFont, int width);



#endif // FUNC_GRAPHICS_H