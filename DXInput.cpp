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
	// アナログでの取得
	int tmpKey = key;
	if(!is2P){
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1) ;
	}else{
		key = GetJoypadInputState(DX_INPUT_PAD2);
		GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD2) ;
	}
	pushedKey = key - (key&tmpKey);

	// キーボード入力のアナログ値への反映
	if( key & PAD_INPUT_UP ) analogY -= 1000;
	if( key & PAD_INPUT_DOWN ) analogY += 1000;
	if( key & PAD_INPUT_LEFT ) analogX -= 1000;
	if( key & PAD_INPUT_RIGHT ) analogX += 1000;

	// 値のオーバーを補正
	if(analogX < -1000) analogX = -1000;
	if(analogY < -1000) analogY = -1000;
	if(analogX > 1000) analogX = 1000;
	if(analogY > 1000) analogY = 1000;

	// アナログ入力の最大値を127に補正（記録のため）
	analogX = analogX*127/1000;
	analogX = min(max(-127, analogX), 127);
	analogY = analogY*127/1000;
	analogY = min(max(-127, analogY), 127);

	// ステージではデジタルでの取得は不要
	// デジタルでの取得
	digitalDir = 5;
	// 十字キーが連続して押されていない場合のみ
	if(!pushed){
		if(analogX > DEF_INPUT_MIN) digitalDir += 1;
		if(analogX < -DEF_INPUT_MIN) digitalDir -= 1;
		if(analogY > DEF_INPUT_MIN) digitalDir -= 3;
		if(analogY < -DEF_INPUT_MIN) digitalDir += 3;
	}

	// デジタル入力フラグの切り替え
	if(abs(analogX) < DEF_INPUT_MIN &&
		abs(analogY) < DEF_INPUT_MIN){
		pushed = false;
		pushed_time = 0;
	}else{
		pushed = true;
		pushed_time += 1;
		// タン……タンタンタンタンの実現
		if(pushed_time >= DELAY_DIGDIR){
			pushed_time -= DELAY_DIGDIR2;
			pushed = false;
		}
	}
}

