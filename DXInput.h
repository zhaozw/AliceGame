#ifndef DXINPUT_H
#define DXINPUT_H

#include <iostream>
#include <fstream>

///////////////////////////////////////////////////
// DXInputクラス
//
// 入力を管理するクラス。
// グローバル変数g_key、key2にそれぞれ
// 1P、2Pのキー入力状態を記録する。

#define DELAY_DIGDIR 30	// 十字キーの1回押し認識
#define DELAY_DIGDIR2 6	// 押しっぱなしのディレイ

// 十字キーの方向をint値で表す場合。
// DXライブラリの値とは対応していない。
#define DIGDIR_DOWN 2
#define DIGDIR_LEFT 4
#define DIGDIR_RIGHT 6
#define DIGDIR_UP 8

// アナログ入力の閾値を設定する。
#define DEF_INPUT_MIN		30
#define DEF_INPUT_MAX		90

class DXInput{

public: 
	int key;				// 押しているキー
	int pushedKey;			// 押されたキー
	int analogX, analogY;	// アナログの十字キー状態 
	int digitalDir;			// 十字キーの方向を8方向で入れる

	// 十字キーの1回押しを認識するための値
	// 一度入力が入るとtrueになり、入力offになるとfalseになる。
	// ただし、pushed_time以上押し続けると以降は
	// 押しっぱなしで断続的に1回押しを入力する
	bool pushed;
	int pushed_time;

	DXInput();
	void getInput(bool is2P);		// key, pushedKeyの取得。2Pの場合はis2P = true
};

#endif