// WindowSkin.cpp

#include <Windows.h>
#include <DxLib.h>
#include "WindowSkin.h"
#include "Window_Base.h"
#include "Image.h"
#include "Func_Math.h"
#include "Static_Game.h" // 4244�x��������

WindowSkin::WindowSkin(){
	wndImgArray = NULL;
	frameSize = DEF_FRAME_SIZE;
	frameType = FT_NOIMAGE;
	openType = OT_NONE;
	openTime = 9999; // div0��h������
}

bool WindowSkin::AttachImage(int* _img, BYTE _wndSkinID, int _frameSize, FRAMETYPE _type, WNDOPENTYPE _oType, int _openTime){
	// �e�p�����[�^�̊��蓖��
	wndImgArray = _img;
	frameSize = _frameSize;
	frameType = _type;
	openType = _oType;
	openTime = _openTime;
	if(wndImgArray == NULL){
		if(frameType != FT_NOIMAGE){
			return false;
		}
	}
	return true;
}

void WindowSkin::Draw(int _x, int _y, int _w, int _h, int _openLevel) const{
	// 0��100��int�ŕ\�������̂�int�^���g�p
	// 0 : ���S�ɕ��Ă���
	// 100 : ���S�ɊJ���Ă���
	int openRate = 100*_openLevel/openTime;
	
	// �J���Ă���Œ��Ɏg���p�����[�^�Q
	int alpha = 255;						// �����x(0�`255)
	float exRateX = 1.0f, exRateY = 1.0f;	// �g��{��
	int deltaX = 0, deltaY = 0;				// �`��ʒu�̂���

	switch(openType){
	case OT_NONE:
		if(openRate != 0){
			return;
		}else{
			// ���Ƀp�����[�^�̕ύX�Ȃ�
		}
		break;
	case OT_FADE:
		// �A���t�@�l�̂ݕύX
		alpha = PARAM(255*openRate/100);
		break;
	case OT_EXPAND_Y:
		// �c�����̊g�嗦��ύX
		exRateY = 1.0f*openRate/100;
		break;
	}

	// �ݒ肵���p�����[�^�����ɃE�B���h�E�g��`�悷��
	int cx=0, cy=0;
	
	// �j�A���X�g�l�C�o�[�@���g�p
	SetDrawMode(DX_DRAWMODE_NEAREST);
	// �����x�̎w��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// ���S���W�̎w��
	cx = _x + _w/2 + deltaX;
	cy = _y + _h/2 + deltaY;

	switch(frameType){
	case FT_NOIMAGE:
		// �摜�̊��蓖�Ă������ꍇ�͕`�悵�Ȃ�
		return;
		break;
	case FT_EXTEND:
		Draw_FT_Extend(cx, cy, _w, _h, exRateX, exRateY);
		break;
	case FT_NOFRAME:
		Draw_FT_NoFrame(cx, cy, _w, _h, exRateX, exRateY);
		break;
	case FT_HEADER:
		break;
	}
	// �o�C���j�A�@���g�p
	SetDrawMode(DX_DRAWMODE_BILINEAR);
}


void WindowSkin::Draw_FT_Extend(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // ����ƉE���̍��W
	for(int v=0; v<3; v++){ // Vertical�̗�
		switch(v){
		case 0:
			y1 = _cy - _exRateY*(int)(_h/2); // ��[
			y2 = y1 + _exRateY*frameSize; // ���[
			break;
		case 1:
			y1 = _cy - ((int)(_h/2)-frameSize)*_exRateY;
			y2 = _cy + ((int)(_h/2)-frameSize)*_exRateY;
			break;
		case 2:
			y2 = _cy + _exRateY*(int)(_h/2); // ���[
			y1 = y2 - _exRateY*frameSize; // ��[
			break;
		}
		for(int h=0; h<3; h++){ // Horizontal�̗�
			switch(h){
			case 0:
				x1 = _cx - _exRateX*(int)(_w/2); // ��[
				x2 = x1 + _exRateX*frameSize; // ���[
				break;
			case 1:
				x1 = _cx - ((int)(_w/2)-frameSize)*_exRateX;
				x2 = _cx + ((int)(_w/2)-frameSize)*_exRateX;
				break;
			case 2:
				x2 = _cx + _exRateX*(int)(_w/2); // ���[
				x1 = x2 - _exRateX*frameSize; // ��[
				break;
			}
			// �g�p�[�c�̕`��
			DrawExtendGraph(x1, y1, x2, y2, wndImgArray[v*3+h], 1);
		}
	}
}


void WindowSkin::Draw_FT_NoFrame(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // ����ƉE���̍��W
	// ���S�摜�݂̂��g�傷��
	x1 = _cx - _exRateX*_w/2; 
	y1 = _cy - _exRateY*_h/2; 
	x2 = _cx + _exRateX*_w/2; 
	y2 = _cy + _exRateY*_h/2;
	DrawExtendGraph(x1, y1, x2, y2, wndImgArray[WNDIMGINDEX_NOFRAME], 1);
}

void WindowSkin::Draw_FT_Header(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // ����ƉE���̍��W
	// ��[�����̕`��
	y1 = _cy - _exRateY*_h/2; // ��[
	y2 = y1 + _exRateY*frameSize; // ���[
	for(int h=0; h<3; h++){ // Horizontal�̗�
		switch(h){
		case 0:
			x1 = _cx - _exRateX*_w/2; // ��[
			x2 = x1 + _exRateX*frameSize; // ���[
			break;
		case 1:
			x1 = _cx - (_w/2-frameSize)*_exRateX;
			x2 = _cx + (_w/2-frameSize)*_exRateX;
			break;
		case 2:
			x2 = _cx + _exRateX*_w/2; // ���[
			x1 = x2 - _exRateX*frameSize; // ��[
			break;
		}
		// �g�p�[�c�̕`��
		DrawExtendGraph(x1, y1, x2, y2, wndImgArray[h], 1);
	}
	// �w�b�_�[�������̕`��
	x1 = _cx - _exRateX*_w/2; 
	y1 = _cy - (_h/2-frameSize)*_exRateY;
	x2 = _cx + _exRateX*_w/2; 
	y2 = _cy + _exRateY*_h/2;
	DrawExtendGraph(x1, y1, x2, y2, wndImgArray[WNDIMGINDEX_HEADER_CENTER], 1);
}
