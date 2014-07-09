#ifndef SELECTABLE2D_H
#define SELECTABLE2D_H

#include "DxLib.h"
#include "DXInput.h"
#include "Config.h"

#define SELECTABLE2D_MAX 128

#define SELECT2D_CHOOSE 1
#define SELECT2D_CANCEL 2
#define SELECT2D_NONE 0

class Selectable2D{
public:
	// 現在のインデックス。
	int index;
	// 移動前のインデックス。
	int lastIndex;
	int column;		// 列数
	int row;		// 行数

	// それぞれの選択肢が選択可能か
	bool isActive[SELECTABLE2D_MAX];

	// 選択肢の移動
	// 決定キーが押された場合は1,
	// キャンセルキーが押された場合は2,
	// それ以外は0を返す。
	// hSnd : 移動時に鳴らす音のハンドル。
	int Move(int hSnd = 0);
	int CheckKey(int hSnd = 0);
		
	// 左右の端がつながっていればtrue。
	bool canHWrap;
	// 上下の端が繋がっていればtrue
	bool canVWrap; 

	// 入力から次の入力可能までの時間。
	// デフォルトでは0。
	int choiceWait;
	int choiceDelay;	// 現在の待ち時間。


	// 現在の位置にとどまっている時間。
	int stayCount;

	// より詳細な指定。
	// 最大数、初期位置、方向、ラップ可能かを指定する。
	Selectable2D(int _column, int _row, int _iniRow=0, int _iniCol=0, 
		bool hWrap=true, bool vWrap=true, int c=0);

	// 現在のインデックスから行数・列数を取得。
	int GetRow(int _index) const{ return _index/column; };
	int GetColumn(int _index) const{ return _index%column; };
	
	// 縦の位置・横の位置からインデックスを取得。
	int GetIndex(int _col, int _row){ return _row*column+_col; };
};


#endif // SELECTABLE_H