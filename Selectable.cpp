#include "Selectable.h"
#include "Sound.h"
#include "KeyConfig.h"

extern DXInput g_input;
extern KeyConfig g_key;

Selectable::Selectable(){
	maxSize = 1;
	index = lastIndex = 0;
	isVirtical = true;
	canWrap = true;
	choiceWait = 0;
	choiceDelay = 0;
	for(int i=0; i<SELECTABLE_MAX; i++){
		isActive[i] = true;
	}
	stayCount = 0;
}

Selectable::Selectable(int m, int ini, bool v, bool w, int c){
	maxSize = m;
	index = lastIndex = ini;
	isVirtical = v;
	canWrap = w;
	choiceWait = c;
	choiceDelay = 0;
	for(int i=0; i<SELECTABLE_MAX; i++){
		isActive[i] = true;
	}
	stayCount = 0;
}

int Selectable::Move(int hSnd){
	// 存在時間の増加
	stayCount++;

	// ディレイがある場合は何もしない
	if(choiceDelay > 0) choiceDelay -= 1;
	if(choiceDelay < 0) choiceDelay = 0;
	if(choiceDelay){ return SELECT_NONE; }

	int delta = 0;
	// index+1するとき1に、-1するときに-1になる。


	// 入力（delta値への代入）
	if(isVirtical){
		// 縦方向
		if(g_input.digitalDir <= 3){ 
			choiceDelay = choiceWait;
			delta = 1;
		}else if( g_input.digitalDir >= 7){
			choiceDelay = choiceWait;
			delta = -1;
		}
	}else{
		// 横方向
		if( g_input.digitalDir % 3 == 0 ){
			choiceDelay = choiceWait;
			delta = 1;
		}else if( g_input.digitalDir % 3 == 1){
			choiceDelay = choiceWait;
			delta = -1;
		}
	}

	// 実際の移動（delta値に基づく）
	bool isFirstTime = true;
	int lIndex = index;	// 失敗した場合戻る
							// （ラップ不可能で行き止まりの場合）
	bool isOK = false;
	if(delta == 1){
		// 前向きに進む
		while(!isOK){
			index += 1;
			if(index>=maxSize){
				if(canWrap){
					index-= maxSize;
				}else{
					index = lIndex;
					isOK = true;
				}
			}	
			if(isActive[index]){
				isOK=true;
			}
		}
	}else if(delta == -1){
		// 後ろ向きに進む
		while(!isOK){
			index -= 1;
			if(index<0){
				if(canWrap){
					index += maxSize;
				}else{
					index = lIndex;
					isOK = true;
				}
			}
			if(isActive[index]){
				isOK=true;
			}
		}
	}

	if(index!=lIndex){
		lastIndex = lIndex;
		stayCount = 0;
	}
	
	// ボタン入力
	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]) return SELECT_CHOOSE;
	if(g_input.pushedKey & g_key.input[BTN_CANCEL]) return SELECT_CANCEL;

	return 0;
}
