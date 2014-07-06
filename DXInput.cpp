// Input.cpp

#include "DxLib.h"
#include "Config.h"
#include "DXInput.h"

extern Config g_cfg;

DXInput::DXInput(){
	key = 0;
	pushedKey = 0;
	analogX = analogY = 0;
	digitalDir = 5;
	pushed = false;
	pushed_time = 0;
}

void DXInput::getInput(bool is2P){
	// �A�i���O�ł̎擾
	int tmpKey = key;
	if(!is2P){
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1) ;
	}else{
		key = GetJoypadInputState(DX_INPUT_PAD2);
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD2) ;
	}
	pushedKey = key - (key&tmpKey);

	// �L�[�{�[�h���͂̃A�i���O�l�ւ̔��f
	if( key & PAD_INPUT_UP ) analogY -= 1000;
	if( key & PAD_INPUT_DOWN ) analogY += 1000;
	if( key & PAD_INPUT_LEFT ) analogX -= 1000;
	if( key & PAD_INPUT_RIGHT ) analogX += 1000;

	// �l�̃I�[�o�[��␳
	if(analogX < -1000) analogX = -1000;
	if(analogY < -1000) analogY = -1000;
	if(analogX > 1000) analogX = 1000;
	if(analogY > 1000) analogY = 1000;

	// �A�i���O���͂̍ő�l��127�ɕ␳�i�L�^�̂��߁j
	analogX = analogX*127/1000;
	analogX = min(max(-127, analogX), 127);
	analogY = analogY*127/1000;
	analogY = min(max(-127, analogY), 127);

	// �X�e�[�W�ł̓f�W�^���ł̎擾�͕s�v
	// �f�W�^���ł̎擾
	digitalDir = 5;
	// �\���L�[���A�����ĉ�����Ă��Ȃ��ꍇ�̂�
	if(!pushed){
		if(analogX > DEF_INPUT_MIN) digitalDir += 1;
		if(analogX < -DEF_INPUT_MIN) digitalDir -= 1;
		if(analogY > DEF_INPUT_MIN) digitalDir -= 3;
		if(analogY < -DEF_INPUT_MIN) digitalDir += 3;
	}

	// �f�W�^�����̓t���O�̐؂�ւ�
	if(abs(analogX) < DEF_INPUT_MIN &&
		abs(analogY) < DEF_INPUT_MIN){
		pushed = false;
		pushed_time = 0;
	}else{
		pushed = true;
		pushed_time += 1;
		// �^���c�c�^���^���^���^���̎���
		if(pushed_time >= DELAY_DIGDIR){
			pushed_time -= DELAY_DIGDIR2;
			pushed = false;
		}
	}
}

