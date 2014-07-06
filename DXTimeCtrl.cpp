// DXTimeCtrl.cpp

#include "DXTimeCtrl.h"

DXTimeCtrl::DXTimeCtrl(){
	Reset();
	fSkipFrame = false;
	drawFlag = true;
}

DXTimeCtrl::~DXTimeCtrl(){
	Reset();
	fSkipFrame = false;
	drawFlag = true;
}

void DXTimeCtrl::Reset(){
	drawFlag = true;
	idealTime = (int)(1000.0f/FPS+0.5);
	frameTime = 0;
	curTime = 0;
	waitTime = 0;
	rateCounter = 0;
	rateTime = 0;
	lastFrameRate = FPS*10;
	skipNum = 0;
	delayPerFrame = 0;
}


void DXTimeCtrl::Regulate(){
	// ���݂̃J�E���g���擾����
	curTime = GetNowCount() ;
	
	// �R�}�����̎��͒x������߂����Ƃ���
	// ���������̎��̓K�^�K�^�ɂȂ�̂Œx�������Ă���
	if(fSkipFrame){ // �R�}����
		if(waitTime > 0){
			curTime += waitTime; // �x������߂����Ƃ���
			if(waitTime > idealTime){ // 1�t���[�����ȏ�x�ꂽ��R�}����
				
				drawFlag = false;
				skipNum ++;
			}else{
				drawFlag = true;
				skipNum = 0;
			}
			if(skipNum > 5){
				// 5�t���[���ȏ�A���Ŕ�΂��ꂽ�ꍇ��
				// �ǂ����Ȃ��Ɣ��f���ď��������ɂ���
				drawFlag = true;
				fSkipFrame = false;
			}
		}
	}else{ // �R�}�����Ȃ�
		// waitTime�͌v�Z���Ȃ�
		waitTime = 0;
	}
}

void DXTimeCtrl::Wait(){
	// FPS������̌o�ߎ��Ԃ�
	// �o�߂���܂ł����ő҂�
	frameTime = GetNowCount() - curTime;
	if(frameTime > idealTime){ // ���ۂ�莞�Ԃ��������Ă���
		waitTime += frameTime - idealTime;
		rateTime += frameTime;
	}else{ // ���ۂ�葁���s�Ȃ��Ă���
		if(idealTime - frameTime > 0){
			WaitTimer(idealTime - frameTime);
		}
		waitTime = 0;
		rateTime += idealTime;
	}	

	// �l�H�I�ȏ��������̏������s��
	if(delayPerFrame > 0){
		WaitTimer(delayPerFrame);
		rateTime -= delayPerFrame;
	}
	
	// �t���[�����[�g�̍X�V����
	rateCounter++;
	// �t���[�����[�g�l�̍X�V
	if(rateCounter >= FPS){
		// FPS�l��10�{�̒l���Z�o
		lastFrameRate = 10000*FPS/rateTime;
		rateCounter = 0; // �J�E���^��0��
		rateTime = 0;
	}
}

void DXTimeCtrl::DrawFPS(int x, int y, int size){
	char fps[6];
	// [0]��100�̈�
	// [1]��10�̈�
	// [2]��1�̈�
	// [3]�������_
	// [4]�������ȉ��̈�
	// [5]���I������
	int tmp, tmp2;
	tmp2 = lastFrameRate;
	tmp = tmp2 / 1000;
	fps[0] = '0'+tmp;
	tmp2 -= tmp*1000;
	tmp = tmp2 / 100;
	fps[1] = '0'+tmp;
	tmp2 -= tmp*100;
	tmp = tmp2 / 10;
	fps[2] = '0'+tmp;
	tmp2 -= tmp*10;
	fps[3] = '.';
	fps[4] = '0'+tmp2;
	fps[5] = '\0';
	// 100�̈ʂ������ꍇ�͏ȗ�
	if(fps[0] == '0'){
		fps[0] = ' ';
	}
	
	SetFontSize(size);
	DrawString(x+2, y+2, fps, GetColor(0,0,0));
	DrawString(x, y, fps, GetColor(255,255,255));
}

