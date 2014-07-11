#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H

#include <Windows.h>
#include "WindowSkin.h"
#include "Static_Game.h"

// 最も基本的なウィンドウを扱うクラス。
// 各ウィンドウクラスに派生するが、このクラス自体は何も内容を描画しない。
// 開閉や内容更新などの状態を持ち、状態に合わせてウィンドウ枠を描画する機能を持つ。

// Open関数の戻り値
#define WNDOPEN_SUCCEED		0	// 開くことに成功した
#define WNDOPEN_FAILED		1	// 開くことに失敗した
#define WNDOPEN_OPENED		2	// 既に開いていた

// Close関数の戻り値
#define WNDCLOSE_SUCCEED	0	// 閉じることに成功した
#define WNDCLOSE_FAILED		1	// 閉じることに失敗した
#define WNDCLOSE_CLOSED		2	// 既に閉じられていた

class Window_Base{
public:
	// ウィンドウの状態を表すenum型の変数。
	// アクティブかどうかなどを保持するが、表示/非表示についてはこれとは別に管理する。
	enum WINDOWSTATE{
		CLOSED,			// ウィンドウが閉じた状態。非表示。
		OPENING,		// ウインドウが開きかけている状態。
						// WindowSkinに定められた時間が経つと開いた状態になる。
		CLOSING,		// ウィンドウが閉じかけている状態。
		UPDATING,		// ウィンドウが開いているが、内容を更新している状態。
		IDLE,			// ウィンドウの内容を更新し終わった状態。外部からの入力待ち。
		SUSPENDED,		// ウィンドウが開き切った瞬間の状態。
						// WindowのクラスによってIDLEに移行するかUPDATINGに移行するかが変わる。
		UNKNOWN = -1,	// 何でもない状態。
	};
protected:
	// ウィンドウスキンへの参照
	WindowSkin* pSkin;
	// ウィンドウの状態
	WINDOWSTATE state;
	// 子ウィンドウ
	// このウィンドウから派生してさらにウィンドウが出ている時、
	// 派生ウィンドウのポインタを代入する。
	Window_Base*	pChildWindow;

	// 位置
	int x;
	int y;
	// サイズ
	int width;
	int height;
	// 内容のサイズ
	int content_width;
	int content_height; // height - padding_y*2。下のパディング＝上のパディングを仮定
	// パディング(内容のウィンドウ端からの距離)。
	// padding_xは左右のパディングを表し、
	// padding_yは上のパディングを表す。
	// 下のパディングについては判定しない。
	int padding_x;
	int padding_y;
	// ウィンドウが表示状態か非表示状態か
	bool visible;
	// ウィンドウが存在している時間の長さ
	// enabledになってからの時間
	int activeCount;
	// ウィンドウが子ウィンドウを持つか否か。
	// falseになると、UpdateA関数で更新処理は行われない。
	bool haveChild;
	// ウィンドウの開き具合
	// openLevelがWindowSkinのopenTimeと等しくなった時が開ききった状態。
	int openLevel;
	// ウィンドウがUpdate_Commonされた回数
	// (基本的にはウィンドウの所属するsceneTimeと一致)
	int count;

public:
	// コンストラクタ
	Window_Base();
	void Initialize();

	// ウィンドウのセットアップ（位置・スキン・サイズの設定）を行う
	bool Setup(WindowSkin* pSkin, int _x, int _y, int _w, int _h, int _px, int _py, bool _visible);

	// ウィンドウを開く。
	// force :	無理やり開く(閉じている最中などでも開く。)
	//			これをfalseにすると状態がCLOSEDの時のみ開くようにする。
	// sudden : アニメーションを用いずにいきなり開く。
	// 戻り値には結果を返す。
	BYTE Open(bool force=false, bool sudden=false);

	// ウィンドウを開いたときに実行する関数。
	// (厳密には開こうとした瞬間に実行するので、
	// ここで内容の書き換えなども可能)
	// 各クラスで派生する。
	virtual void OnOpened(){};

	// 子ウィンドウが閉じられた時に実行する関数。
	// 各クラスで派生する。
	virtual void OnChildIsClosed(){};

	// ウィンドウを閉じる。
	// force :	無理やり閉じる(開いている最中や内容の更新中でも閉じる)。
	//			これをfalseにすると状態がIDLEの時のみ閉じるようにする。
	// sudden :	アニメーションを用いずにいきなり閉じる。
	BYTE Close(bool force=false, bool sudden=false);

	// 内容のアップデートを行う。
	void UpdateA();			// 子ウィンドウがない場合のみアップデートする。
							// 基本的にUpdate関数はこちらを使用する。
	virtual void Update();	// クラスごとに派生するアップデート関数。
	bool Update_Common();	// 基本的に共通のアップデート関数。
							// Updateを行わない状態の時はfalseを返す。

	// 内容の描画を行う。
	// クラスごとに派生する。
	virtual void DrawContent() const;
	// ウィンドウスキンへの参照を利用して枠の描画を行う。
	// 基本的にクラスごとには派生しない。
	void DrawFrame() const;  
	// ウィンドウ全体の描画を行う。
	void Draw() const{ if(visible){ DrawFrame(); DrawContent(); }; };

	// アクセサ
	WINDOWSTATE GetState() const{ return state; } ; 
	void SetPosition(int _x, int _y){x = _x; y = _y; };
	int GetPositionX() const{ return x; };
	int GetPositionY() const{ return y; };
	void SetVisible(bool b){ visible = b; };
	bool GetVisible() const{ return visible; };
	bool GetActive() const; // activeCountを増加させる状態にあるか
	int GetOpenTime() const; // スキンのopenTimeを取得する。

	// スキンのセットを行う
	bool AttachSkin(WindowSkin* _pSkin){ pSkin = _pSkin; return true; };
	
	// ある位置に揃える
	void SetPositionH(int pos, BYTE align=ALIGN_CENTER);
	void SetPositionV(int pos, BYTE align=ALIGN_CENTER);

	// コンテンツ部分のサイズの取得
	void SetContentSize(){
		content_width = width-padding_x*2; 
		content_height = height-padding_y*2;
	};

	// 子ウィンドウのポインタを指定してウィンドウを開く。
	// ウィンドウを開くと自動的にisActiveがfalseとなり、
	// 閉じると自動的にtrueになる。
	// 戻り値：子ウィンドウを開いた結果
	BYTE OpenChildWindow(Window_Base* _pChild, bool sudden = false);
};

#endif // WINDOW_BASE_H