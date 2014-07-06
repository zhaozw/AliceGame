// Func_Graphics.cpp

#include "Func_Graphics.h"
#include <DxLib.h>
#include <math.h>

int const DrawNumArray(int x, int y, int* image, int* nArray, int digit, int wid,
	BYTE align, bool useComme, bool zerofill, float rate){
		// �`�悷��t���O
		bool isShow = zerofill;
		// �`�悷�ׂ����l�̌���
		int drawDigit;
		if(zerofill){
			drawDigit = digit;
		}else{
			for(int i=0; i<digit; i++){
				if(nArray[i] > 0 || i==digit-1){
					// �`�悷�ׂ������ł���
					drawDigit = digit-i;
					break;
				}
			}
		}
		// �`�悳��镝���擾
		int drawWid = drawDigit*wid;
		if(useComme){
			drawWid += (int)((drawDigit-1)/3)*wid/2;
		}
		// �{���ɍ��킹�Ē���
		drawWid = (int)(rate*drawWid);
		// �`��ʒu�𒲐�
		int drawX = x;
		switch(align){
		case 0:
			break;
		case 1:
			drawX -= drawWid/2;
			break;
		case 2:
			drawX -= drawWid;
			break;
		}
		// �R���}���g���ꍇ�A���Ԗڂ̐����̌�ɍŏ��ɃR���}�����邩���擾
		BYTE commePos = ((drawDigit+2)%3)+1;

		// ���ۂ̕`��
		for(int i=(digit-drawDigit); i<digit; i++){
			if(commePos<=0){
				// �R���}�̕`��
				DrawGraph(drawX, y, image[10], 1);
				commePos += 3;
				drawX += (int)(wid*rate/2);
			}
			// ���l�̕`��
			DrawGraph(drawX, y, image[nArray[i]], 1);
			// �`�悷�ׂ��ʒu�����炷
			drawX += (int)(wid*rate);
			commePos--;
		}
		return drawWid;
}

void const DrawScore(int score, int score8dig, int x, int y, int* image,
	int wid, BYTE align, bool zerofill, bool useComme, int dig, float rate){
		// ���̐����̔z��ɒl������
		int nArray[10];

		int tmpIndex = 0;
		int tmpNum, tmpDiv;
		if(score8dig = 0){
			for(int i=0; i<dig-8; i++){
				nArray[tmpIndex] = 0;
				tmpIndex++;
			}
		}else{
			// ���l���e���ɏ���������
			tmpNum = score8dig;
			if(tmpNum > LONG_MAX) tmpNum = LONG_MAX;
			// �����Ƃɑ������
			for(int i=0;i<dig;i++){
				tmpDiv = 1;
				for(int j=i+1;j<dig;j++){
					tmpDiv *= 10;
				}
				nArray[tmpIndex] = (tmpNum/tmpDiv)%10;
				tmpNum -= nArray[tmpIndex]*tmpDiv;
				tmpIndex++;
			}
		}
		
		tmpNum = score;
		// ���l���e���ɏ���������
		if(tmpNum > LONG_MAX) tmpNum = LONG_MAX;
		// �����Ƃɑ������
		for(int i=0;i<dig;i++){
			tmpDiv = 1;
			for(int j=i+1;j<dig;j++){
				tmpDiv *= 10;
			}
			nArray[i] = (tmpNum/tmpDiv)%10;
			tmpNum -= nArray[i]*tmpDiv;
		}

		// ���ۂ̕`��
		DrawNumArray(x, y, image, nArray, dig, wid, align, useComme, zerofill, rate);
}

void const DrawNum(int num, int x, int y, int* image,
	int wid, int dig, BYTE align, bool zerofill, bool useComme, float rate){
		// ���̐����̔z��ɒl������
		int nArray[9];

		// ���l���e���ɏ���������
		int tmpNum = num;
		if(tmpNum > LONG_MAX) tmpNum = LONG_MAX;
		int tmpDiv;
		// �����Ƃɑ������
		for(int i=0;i<dig;i++){
			tmpDiv = 1;
			for(int j=i+1;j<dig;j++){
				tmpDiv *= 10;
			}
			nArray[i] = (num/tmpDiv)%10;
			tmpNum -= nArray[i]*tmpDiv;
		}
		// ���ۂ̕`��
		DrawNumArray(x, y, image, nArray, dig, wid, align, useComme, zerofill, rate);
}

void DrawStr(LPTSTR text, int x, int y, int wid, int* image){
	int length = strlen(text);
	char cntText;
	for(int i=0; i<length; i++){
		cntText = text[i] - 'a' + 1;
		DrawGraph(x+i*wid, y, image[cntText], 1);
	}
}

void DrawGradStrToHandle(const TCHAR* text, int hFont, int x, int y, int size, 
						 MYCOLOR3* upColor, MYCOLOR3* btmColor, int step,
						 int wndWid, int wndHei, int edgeColor){
	// �ŏ��̐F�ƕ`�掞�ɃO���f�[�V�����ŕω�����X�e�b�v�l
	// �v���X�ƃ}�C�i�X���������Ă���Ƃ�₱�����̂ŕ�����
	int iniR, iniG, iniB;
	int stepR, stepG, stepB;
	iniR = upColor->R;
	iniG = upColor->G;
	iniB = upColor->B;
	stepR = (int)(btmColor->R - iniR)/step;
	stepG = (int)(btmColor->G - iniG)/step;
	stepB = (int)(btmColor->B - iniB)/step;

	// �ȉ��A���������肵�ĕ`��
	for(int i=0; i<step; i++){
		if(i == step-1){ // �Ō�̕`��̏ꍇ
			SetDrawArea(x, y+i*(size/step), wndWid, y+(i+1)*(size/step));
		}else{
			// �Ō�A�`�悵�Ȃ��̈�𔭐������Ȃ�����
			SetDrawArea(x, y+i*(size/step), wndWid, y+size);
		}
		DrawStringToHandle(x, y, text, 
			GetColor(iniR+i*stepR, iniG+i*stepG, iniB+i*stepB),
			hFont, edgeColor);
	}
	SetDrawArea(0, 0, wndWid, wndHei);
}


int GetRainbow(int i){
	int j= i%(256*6);
	if(j<256){
		return j;
	}else if(j<768){
		return 255;
	}else if(j<1024){
		return 1023-j;
	}else{
		return 0;
	}
	return 0;
}

int GetRainbowR(int i){
	return GetRainbow(i);
}

int GetRainbowG(int i){
	return GetRainbow(i+512);
}

int GetRainbowB(int i){
	return GetRainbow(i+1024);
}


int GetRainbowColor(int i){
	return 0xff000000+(0x00010000*GetRainbow(i))+
		(0x00000100*GetRainbow(i+512))+GetRainbow(i+1024);
}

void DrawFadeGraph(int hImg, int x, int y, int width, int height,
	float grad, int zeropoint, int blendmode, bool horizon, bool reverse){
	int param;
	for(int i=0; i<(horizon?width:height); i++){
		param = (int)(grad*(i-zeropoint)*(reverse?-1:1));
		param = max(0, min(255, param));
		SetDrawBlendMode(blendmode, param);
		DrawRectGraph(
			x+(horizon?i:0), y+(horizon?0:i),
			(horizon?i:0), (horizon?0:i),
			(horizon?1:width), (horizon?height:1),
			hImg, 1, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


void DrawWaveGraph(int count, int hImg, int x, int y, int height, int width,
				   float span, float speed, float pitch){
	for(int i=0; i<height; i++){
		int param = (int)(span*sin(speed*count)*sin(i*pitch));
		DrawRectGraph(x+param, y+i, 0, i, width, 1, hImg, 1, 0);
	}
}

void DrawFlowGraph(int hImg, int x, int y, int borderY, int wid, int hei,
				   bool fromTop, float deltaGrad, float alphaGrad, int blendMode, float alphaBase){
	int cntY; // ���摜�ɂ�����`��Ώۂ̈ʒu
	int cntDelta; // ���݂̉摜�̂���̑傫��
	float cntAlpha; // ���݂̕`��̓����x(0~1)

	// fromTop�̏ꍇ�͉�����`��A!fromTop�̏ꍇ�͏ォ��`��
	cntY = (fromTop?hei:0);
	if(borderY < 0){
		cntY += (fromTop?(-borderY):borderY);
	}

	// �ŏ���borderY�̕����܂ŕ��ʂɕ`�悷��
	if(borderY > 0){
		cntAlpha = alphaBase;
		SetDrawBlendMode(blendMode, (int)(cntAlpha*255.0f)); 
		if(fromTop){
			// ������borderY�����`��
			DrawRectGraph(x, y+cntY-borderY, 0, hei-borderY, wid, borderY, hImg, 1, 0);
			cntY -= borderY;
		}else{
			// �ォ��borderY�����`��
			DrawRectGraph(x, y, 0, 0, wid, borderY, hImg, 1, 0);
			cntY += borderY;
		}
	}
	// �Ȍ��1�s�N�Z�����`�悵�Ă���
	for(int i=0; i<hei-borderY; i++){
		cntAlpha = alphaBase*(1-alphaGrad*i);
		if(cntAlpha < 0) break; // �`�悵�Ȃ����A�ȉ��S�ĕ`�悵�Ȃ�
		cntDelta = (int)(deltaGrad*0.5*i*i); // ���ߑ��x�^��
		SetDrawBlendMode(blendMode, (int)(cntAlpha*255.0f)); 
		// ���摜��1�s�N�Z���������炵�ĕ`�悷��
		if(fromTop) cntY--;
		if(cntY >= 0 && cntY < hei){
			DrawRectGraph(x+cntDelta*(fromTop?1:(-1)), y+cntY, 0, cntY, wid, 1, hImg, 1, 0);
		}
		if(!fromTop) cntY++;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

int GetRightAlignDX(LPTSTR str, int strLen, int hFont, int width){
	return (width - GetDrawStringWidthToHandle(str, strLen, hFont, 0));
}

int	GetCenteringDX(LPTSTR str, int strLen, int hFont, int width){
	return GetRightAlignDX(str, strLen, hFont, width)/2;
}

