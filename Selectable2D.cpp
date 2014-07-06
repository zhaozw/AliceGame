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
	// ���ݎ��Ԃ̑���
	stayCount++;

	// �f�B���C������ꍇ�͉������Ȃ�
	if(choiceDelay > 0) choiceDelay -= 1;
	if(choiceDelay < 0) choiceDelay = 0;
	if(choiceDelay){ return SELECT2D_NONE; }

	int checkIndex = 0;
	int resultIndex = -1;

	if(g_input.digitalDir%3 == 0){
		// �E�L�[�̔���
		for(int c=1; c<column; c++){
			checkIndex = index+c;
			// �E�[�ɒB������߂�
			if(GetColumn(checkIndex) < GetColumn(index)){
				checkIndex -= column;
			}
			if(GetColumn(checkIndex) == 0 && !canHWrap){
				// �E�[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
				break;
			}
			if(isActive[checkIndex]){
				// �ړ��\�ȑI�����ɓ���������u���[�N����
				resultIndex = checkIndex;
				break;
			}
		}
	}else if(g_input.digitalDir%3 == 1){
		// ���L�[�̔���
		for(int c=1; c<column; c++){
			checkIndex = index-c;
			// ���[�ɒB������߂�
			if(GetColumn(checkIndex) > GetColumn(index) || checkIndex<0){
				checkIndex += column;
			}
			if(GetColumn(checkIndex) == (column-1) && !canHWrap){
				// ���[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
				break;
			}
			if(isActive[checkIndex]){
				// �ړ��\�ȑI�����ɓ���������u���[�N����
				resultIndex = checkIndex;
				break;
			}
		}
	}else if(g_input.digitalDir <= 3){
		// ���L�[�̔���
		for(int r=1; r<row; r++){
			checkIndex = index+column*r;
			// ���[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
			if(GetRow(checkIndex) >= row){
				// ���ɓ������̂����Ă���ƌ��Ȃ�
				checkIndex -= column*row;
			}
			if(GetRow(checkIndex) == 0 && !canVWrap){
				// ���[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
				break;
			}
			if(isActive[checkIndex]){
				// �ړ��\�ȑI�����ɓ���������u���[�N����
				resultIndex = checkIndex;
				break;
			}
		}	
	}else if(g_input.digitalDir >= 7){
		// ��L�[�̔���
		for(int r=1; r<row; r++){
			checkIndex = index-column*r;
			// ���[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
			if(checkIndex < 0){
				// ��ɓ������̂����Ă���ƌ��Ȃ�
				checkIndex += column*row;
			}
			if(GetRow(checkIndex) == row-1 && !canVWrap){
				// ��[�ɒB���Đ܂�Ԃ��Ȃ��ꍇ
				break;
			}
			if(isActive[checkIndex]){
				// �ړ��\�ȑI�����ɓ���������u���[�N����
				resultIndex = checkIndex;
				break;
			}
		}	
	}

	// �s���悪��������
	if(resultIndex != -1){
		lastIndex = index;
		index = resultIndex;
	}

	// �{�^������
	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]) return SELECT2D_CHOOSE;
	if(g_input.pushedKey & g_key.input[BTN_CANCEL]) return SELECT2D_CANCEL;

	return 0;
}
