#ifndef FUNC_MYGRAPHIC_H
#define FUNC_MYGRAPHIC_H

#include <Windows.h>
#include "DXFont.h"

// Func_Graphicsに含まない、このゲーム特有の描画関数を記述する。

// 使用する文字の最大数。
#define MAX_NAMESTRING		255 // 17行×5文字×3面

// 文字のサイズ
#define SIZE_NAMESTR		(FONTSIZE_STR)
#define SIZE_NAMESTR_L		(FONTSIZE_STR_L)

// 宝石のかけらのデフォルトサイズ
#define SIZE_ATTRSTONE		48

// 属性アイコンのサイズ
#define SIZE_ATTRICON		24

// 人形のイラストの画像サイズ
#define WIDTH_DOLLILLUST	512
#define HEIGHT_DOLLILLUST	512

// 人形のアイコンの画像サイズ
#define WIDTH_DOLLICON		96
#define HEIGHT_DOLLICON		128

// ステータス画面用に人形の種類を描画する。
void DrawDollType(int x, int y, BYTE type, int color);

// 名前に使用できる文字を描画する。
// isLarge : 描画出来る文字のサイズは二種類。
void DrawNameChar(int x, int y, WORD index, bool isLarge);

// 属性アイコンを描画する。
void DrawAttrIcon(int x, int y, BYTE attr);

// 属性の宝石を描画する。
void DrawAttrStone(int cx, int cy, BYTE group, BYTE attr, float exRate=1.0, int time=0);

// 人形のタイプ名の文字を指定したフォントで描画する。
void DrawGroupName(int x, int y, BYTE group, int hFont);

// 人形イラストの描画を行う。
// 指定する座標は描画の中心。
// type : 人形の種類
// attr : 人形の属性
// exRate : 拡大率
// rot : 回転角
void DrawDollIllust(int cx, int cy, BYTE type, BYTE attr, float exRate, float rot);
void DrawDollIllust2(int cx, int cy, BYTE type, BYTE attr,
	float exRateX, float exRateY, float rot);

// 人形アイコンの描画を行う。
// いくつかの種類がある。
// 左上の座標を指定して通常描画。
void DrawDollIcon(int x, int y, BYTE type, BYTE attr, BYTE face);
// 左上と右下の座標を指定して拡大縮小描画。
void DrawDollIconExtend(int x1, int y1, int x2, int y2, BYTE type, BYTE attr, BYTE face);
// 中心の座標を指定して回転拡大描画
void DrawDollIconRot(int cx, int cy, 
	BYTE type, BYTE attr, BYTE face, float exRate, float rot); 

#endif // FUNC_MYGRAPHIC_H