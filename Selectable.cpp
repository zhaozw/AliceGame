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
	// ���ݎ��Ԃ̑���
	stayCount++;

	// �f�B���C������ꍇ�͉������Ȃ�
	if(choiceDelay > 0) choiceDelay -= 1;
	if(choiceDelay < 0) choiceDelay = 0;
	if(choiceDelay){ return SELECT_NONE; }

	int delta = 0;
	// index+1����Ƃ�1�ɁA-1����Ƃ���-1�ɂȂ�B


	// ���́idelta�l�ւ̑���j
	if(isVirtical){
		// �c����
		if(g_input.digitalDir <= 3){ 
			choiceDelay = choiceWait;
			delta = 1;
		}else if( g_input.digitalDir >= 7){
			choiceDelay = choiceWait;
			delta = -1;
		}
	}else{
		// ������
		if( g_input.digitalDir % 3 == 0 ){
			choiceDelay = choiceWait;
			delta = 1;
		}else if( g_input.digitalDir % 3 == 1){
			choiceDelay = choiceWait;
			delta = -1;
		}
	}

	// ���ۂ̈ړ��idelta�l�Ɋ�Â��j
	bool isFirstTime = true;
	int lIndex = index;	// ���s�����ꍇ�߂�
							// �i���b�v�s�\�ōs���~�܂�̏ꍇ�j
	bool isOK = false;
	if(delta == 1){
		// �O�����ɐi��
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
		// �������ɐi��
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
	
	// �{�^������
	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]) return SELECT_CHOOSE;
	if(g_input.pushedKey & g_key.input[BTN_CANCEL]) return SELECT_CANCEL;

	return 0;
}
