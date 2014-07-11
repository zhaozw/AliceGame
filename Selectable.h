#ifndef SELECTABLE_H
#define SELECTABLE_H

#include "DxLib.h"
#include "DXInput.h"
#include "Config.h"

#define SELECTABLE_MAX 64

#define SELECT_CHOOSE 1
#define SELECT_CANCEL 2
#define SELECT_NONE 0
#define SELECTRESULT_CANCELED	-1

class Selectable{
public:
	int index;
	int maxSize;

	// それぞれの選択肢が選択可能か
	bool isActive[SELECTABLE_MAX];

	// 選択肢の移動
	// 決定キーが押された場合は1,
	// キャンセルキーが押された場合は2,
	// それ以外は0を返す。
	// hSnd : 移動時に鳴らす音のハンドル。
	int Move(int hSnd = 0);
	
	// 上下で選択するタイプならtrue,
	// 左右で選択するタイプならfalse。
	bool isVirtical;
	
	// 上と下がつながっていればtrue。
	bool canWrap;

	// 入力から次の入力可能までの時間。
	// デフォルトでは0。
	int choiceWait;
	int choiceDelay;	// 現在の待ち時間。

	// 移動前のインデックス。
	int lastIndex;

	// 現在の位置にとどまっている時間。
	int stayCount;

	// より詳細な指定。
	// 最大数、初期位置、方向、ラップ可能かを指定する。
	Selectable(int m, int ini=0, bool v=true, bool w=true, int c=0);

	// デフォルトコンストラクタ
	Selectable();
};


#endif // SELECTABLE_H