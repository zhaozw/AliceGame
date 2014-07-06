#ifndef DXTIMECTRL_H
#define DXTIMECTRL_H

#include "DxLib.h"
#include "Static_Game.h"

//////////////////////////////////////////////////
// DXTimeCtrlクラス
// DXライブラリにおいてフレームレート制御を行なう。
// Scene関連のクラスのメンバ。

class DXTimeCtrl{
	////////////////////////////////////
	// 内部で使用するパラメータ
	
	// 理想的な1フレームあたりの時間
	int idealTime; 
	// 実際の時間
	int frameTime;
	// 現在の時間を取得
	int curTime;
	// 遅れている時間
	int waitTime;
	// 連続で飛ばしたフレーム数
	int skipNum;
	// フレームレート計測用のカウンタ
	// (FPSの値になった時にフレームレート値を更新する)
	int rateCounter;
	// フレームあたりの時間の積算
	int rateTime;
	// 前回のフレームレート値(小数1桁までの値を10倍したもの)
	// 例として58.2fpsの時は582
	int lastFrameRate;
	// 処理落ちの演出
	int delayPerFrame;

	////////////////////////////////////
	// 外に見えるパラメータ
	
	// 遅れている時に描画を省略するかどうか
	bool fSkipFrame;
	// 描画するかどうか
	bool drawFlag;
	
public:
	// コンストラクタ
	DXTimeCtrl();

	// デストラクタ
	~DXTimeCtrl();
	
	// 時間の制御を行なう
	void Regulate();
	// 場合によって時間待ちを行なう
	void Wait();
	
	// 描画フラグがtrueかfalseか
	bool GetDrawFlag(){ return drawFlag; };
	// fSkipFrameに値をセットする
	void SetSkipFrame(bool b){ fSkipFrame = b; };
	// 値をリセット
	void Reset();
	// 処理落ちの演出を行う
	void SetArtificialDelay(int _delayPerFrame){ delayPerFrame = _delayPerFrame; };
	
	// FPS値を描画する
	// (DXライブラリの文字描画を利用、左上が(x,y)
	void DrawFPS(int x, int y, int size=24);
};

#endif