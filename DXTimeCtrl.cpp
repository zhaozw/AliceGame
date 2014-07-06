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
	// 現在のカウントを取得する
	curTime = GetNowCount() ;
	
	// コマ落ちの時は遅れを取り戻そうとする
	// 処理落ちの時はガタガタになるので遅れを放っておく
	if(fSkipFrame){ // コマ落ち
		if(waitTime > 0){
			curTime += waitTime; // 遅れを取り戻そうとする
			if(waitTime > idealTime){ // 1フレーム分以上遅れたらコマ落ち
				
				drawFlag = false;
				skipNum ++;
			}else{
				drawFlag = true;
				skipNum = 0;
			}
			if(skipNum > 5){
				// 5フレーム以上連続で飛ばされた場合は
				// 追いつけないと判断して処理落ちにする
				drawFlag = true;
				fSkipFrame = false;
			}
		}
	}else{ // コマ落ちない
		// waitTimeは計算しない
		waitTime = 0;
	}
}

void DXTimeCtrl::Wait(){
	// FPSあたりの経過時間が
	// 経過するまでここで待つ
	frameTime = GetNowCount() - curTime;
	if(frameTime > idealTime){ // 実際より時間がかかっている
		waitTime += frameTime - idealTime;
		rateTime += frameTime;
	}else{ // 実際より早く行なっている
		if(idealTime - frameTime > 0){
			WaitTimer(idealTime - frameTime);
		}
		waitTime = 0;
		rateTime += idealTime;
	}	

	// 人工的な処理落ちの処理を行う
	if(delayPerFrame > 0){
		WaitTimer(delayPerFrame);
		rateTime -= delayPerFrame;
	}
	
	// フレームレートの更新処理
	rateCounter++;
	// フレームレート値の更新
	if(rateCounter >= FPS){
		// FPS値の10倍の値を算出
		lastFrameRate = 10000*FPS/rateTime;
		rateCounter = 0; // カウンタを0に
		rateTime = 0;
	}
}

void DXTimeCtrl::DrawFPS(int x, int y, int size){
	char fps[6];
	// [0]→100の位
	// [1]→10の位
	// [2]→1の位
	// [3]→小数点
	// [4]→少数以下の位
	// [5]→終了文字
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
	// 100の位が無い場合は省略
	if(fps[0] == '0'){
		fps[0] = ' ';
	}
	
	SetFontSize(size);
	DrawString(x+2, y+2, fps, GetColor(0,0,0));
	DrawString(x, y, fps, GetColor(255,255,255));
}

