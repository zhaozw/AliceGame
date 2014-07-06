// Selectable2D2D.cpp

#include "Selectable2D.h"
#include "Sound.h"
#include "KeyConfig.h"

extern DXInput g_input;
extern KeyConfig g_key;

Selectable2D::Selectable2D(int _column, int _row, int _iniRow, int _iniCol, 
		bool hWrap, bool vWrap, int c){
	row = _row;
	column = _column;
	index = lastIndex = _iniRow*_column+_iniCol;
	canHWrap = hWrap;
	canVWrap = vWrap;
	choiceWait = c;
	choiceDelay = 0;
	for(int i=0; i<SELECTABLE2D_MAX; i++){
		isActive[i] = true;
	}
	stayCount = 0;
}

int Selectable2D::Move(int hSnd){
	// 存在時間の増加
	stayCount++;

	// ディレイがある場合は何もしない
	if(choiceDelay > 0) choiceDelay -= 1;
	if(choiceDelay < 0) choiceDelay = 0;
	if(choiceDelay){ return SELECT2D_NONE; }

	int checkIndex = 0;
	int resultIndex = -1;

	if(g_input.digitalDir%3 == 0){
		// 右キーの判定
		for(int c=1; c<column; c++){
			checkIndex = index+c;
			// 右端に達したら戻る
			if(GetColumn(checkIndex) < GetColumn(index)){
				checkIndex -= column;
			}
			if(GetColumn(checkIndex) == 0 && !canHWrap){
				// 右端に達して折り返せない場合
				break;
			}
			if(isActive[checkIndex]){
				// 移動可能な選択肢に当たったらブレークする
				resultIndex = checkIndex;
				break;
			}
		}
	}else if(g_input.digitalDir%3 == 1){
		// 左キーの判定
		for(int c=1; c<column; c++){
			checkIndex = index-c;
			// 左端に達したら戻る
			if(GetColumn(checkIndex) > GetColumn(index) || checkIndex<0){
				checkIndex += column;
			}
			if(GetColumn(checkIndex) == (column-1) && !canHWrap){
				// 左端に達して折り返せない場合
				break;
			}
			if(isActive[checkIndex]){
				// 移動可能な選択肢に当たったらブレークする
				resultIndex = checkIndex;
				break;
			}
		}
	}else if(g_input.digitalDir <= 3){
		// 下キーの判定
		for(int r=1; r<row; r++){
			checkIndex = index+column*r;
			// 下端に達して折り返せない場合
			if(GetRow(checkIndex) >= row){
				// 下に同じものがついていると見なす
				checkIndex -= column*row;
			}
			if(GetRow(checkIndex) == 0 && !canVWrap){
				// 下端に達して折り返せない場合
				break;
			}
			if(isActive[checkIndex]){
				// 移動可能な選択肢に当たったらブレークする
				resultIndex = checkIndex;
				break;
			}
		}	
	}else if(g_input.digitalDir >= 7){
		// 上キーの判定
		for(int r=1; r<row; r++){
			checkIndex = index-column*r;
			// 下端に達して折り返せない場合
			if(checkIndex < 0){
				// 上に同じものがついていると見なす
				checkIndex += column*row;
			}
			if(GetRow(checkIndex) == row-1 && !canVWrap){
				// 上端に達して折り返せない場合
				break;
			}
			if(isActive[checkIndex]){
				// 移動可能な選択肢に当たったらブレークする
				resultIndex = checkIndex;
				break;
			}
		}	
	}

	// 行き先が見つかった
	if(resultIndex != -1){
		lastIndex = index;
		index = resultIndex;
	}

	// ボタン入力
	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]) return SELECT2D_CHOOSE;
	if(g_input.pushedKey & g_key.input[BTN_CANCEL]) return SELECT2D_CANCEL;

	return 0;
}
