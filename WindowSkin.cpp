// WindowSkin.cpp

#include <Windows.h>
#include <DxLib.h>
#include "WindowSkin.h"
#include "Window_Base.h"
#include "Image.h"
#include "Func_Math.h"
#include "Static_Game.h" // 4244警告無効化

WindowSkin::WindowSkin(){
	wndImgArray = NULL;
	frameSize = DEF_FRAME_SIZE;
	frameType = FT_NOIMAGE;
	openType = OT_NONE;
	openTime = 9999; // div0を防ぐため
}

bool WindowSkin::AttachImage(int* _img, BYTE _wndSkinID, int _frameSize, FRAMETYPE _type, WNDOPENTYPE _oType, int _openTime){
	// 各パラメータの割り当て
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
	// 0や100をintで表したいのでint型を使用
	// 0 : 完全に閉じている
	// 100 : 完全に開いている
	int openRate = 100*_openLevel/openTime;
	
	// 開いている最中に使うパラメータ群
	int alpha = 255;						// 透明度(0～255)
	float exRateX = 1.0f, exRateY = 1.0f;	// 拡大倍率
	int deltaX = 0, deltaY = 0;				// 描画位置のずれ

	switch(openType){
	case OT_NONE:
		if(openRate != 0){
			return;
		}else{
			// 特にパラメータの変更なし
		}
		break;
	case OT_FADE:
		// アルファ値のみ変更
		alpha = PARAM(255*openRate/100);
		break;
	case OT_EXPAND_Y:
		// 縦方向の拡大率を変更
		exRateY = 1.0f*openRate/100;
		break;
	}

	// 設定したパラメータを元にウィンドウ枠を描画する
	int cx=0, cy=0;
	
	// ニアレストネイバー法を使用
	SetDrawMode(DX_DRAWMODE_NEAREST);
	// 透明度の指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// 中心座標の指定
	cx = _x + _w/2 + deltaX;
	cy = _y + _h/2 + deltaY;

	switch(frameType){
	case FT_NOIMAGE:
		// 画像の割り当てが無い場合は描画しない
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
	// バイリニア法を使用
	SetDrawMode(DX_DRAWMODE_BILINEAR);
}


void WindowSkin::Draw_FT_Extend(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // 左上と右下の座標
	for(int v=0; v<3; v++){ // Verticalの略
		switch(v){
		case 0:
			y1 = _cy - _exRateY*(int)(_h/2); // 上端
			y2 = y1 + _exRateY*frameSize; // 下端
			break;
		case 1:
			y1 = _cy - ((int)(_h/2)-frameSize)*_exRateY;
			y2 = _cy + ((int)(_h/2)-frameSize)*_exRateY;
			break;
		case 2:
			y2 = _cy + _exRateY*(int)(_h/2); // 下端
			y1 = y2 - _exRateY*frameSize; // 上端
			break;
		}
		for(int h=0; h<3; h++){ // Horizontalの略
			switch(h){
			case 0:
				x1 = _cx - _exRateX*(int)(_w/2); // 上端
				x2 = x1 + _exRateX*frameSize; // 下端
				break;
			case 1:
				x1 = _cx - ((int)(_w/2)-frameSize)*_exRateX;
				x2 = _cx + ((int)(_w/2)-frameSize)*_exRateX;
				break;
			case 2:
				x2 = _cx + _exRateX*(int)(_w/2); // 下端
				x1 = x2 - _exRateX*frameSize; // 上端
				break;
			}
			// 枠パーツの描画
			DrawExtendGraph(x1, y1, x2, y2, wndImgArray[v*3+h], 1);
		}
	}
}


void WindowSkin::Draw_FT_NoFrame(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // 左上と右下の座標
	// 中心画像のみを拡大する
	x1 = _cx - _exRateX*_w/2; 
	y1 = _cy - _exRateY*_h/2; 
	x2 = _cx + _exRateX*_w/2; 
	y2 = _cy + _exRateY*_h/2;
	DrawExtendGraph(x1, y1, x2, y2, wndImgArray[WNDIMGINDEX_NOFRAME], 1);
}

void WindowSkin::Draw_FT_Header(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const{
	int x1=0, y1=0, x2=0, y2=0; // 左上と右下の座標
	// 上端部分の描画
	y1 = _cy - _exRateY*_h/2; // 上端
	y2 = y1 + _exRateY*frameSize; // 下端
	for(int h=0; h<3; h++){ // Horizontalの略
		switch(h){
		case 0:
			x1 = _cx - _exRateX*_w/2; // 上端
			x2 = x1 + _exRateX*frameSize; // 下端
			break;
		case 1:
			x1 = _cx - (_w/2-frameSize)*_exRateX;
			x2 = _cx + (_w/2-frameSize)*_exRateX;
			break;
		case 2:
			x2 = _cx + _exRateX*_w/2; // 下端
			x1 = x2 - _exRateX*frameSize; // 上端
			break;
		}
		// 枠パーツの描画
		DrawExtendGraph(x1, y1, x2, y2, wndImgArray[h], 1);
	}
	// ヘッダー下部分の描画
	x1 = _cx - _exRateX*_w/2; 
	y1 = _cy - (_h/2-frameSize)*_exRateY;
	x2 = _cx + _exRateX*_w/2; 
	y2 = _cy + _exRateY*_h/2;
	DrawExtendGraph(x1, y1, x2, y2, wndImgArray[WNDIMGINDEX_HEADER_CENTER], 1);
}
