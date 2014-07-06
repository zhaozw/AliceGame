#ifndef WINDOW_DOLLSTATUS_H
#define WINDOW_DOLLSTATUS_H

#include "Window_Text.h"
#include "Game_AliceDoll.h"

#define WND_DOLLSTATUS_WIDTH		300
#define WND_DOLLSTATUS_HEIGHT		500
#define WND_DOLLSTATUS_PX			32
#define WND_DOLLSTATUS_PY			32

class Window_DollStatus : public Window_Text{
private:
	// ステータスを表示する人形への参照。
	Game_AliceDoll_Essence*	pDoll;
public:
	// コンストラクタ
	Window_DollStatus();

	// ウィンドウのセットアップ
	bool Setup(int _x, int _y);
	// 人形のセット。表示に必要なパラメータなどの計算も行う。
	bool SetDoll(Game_AliceDoll_Essence* p);

	// 内容の更新を行う。
	virtual void Update();

	// 内容の描画を行う。
	// クラスごとに派生する。
	virtual void DrawContent() const;
};

#endif // WINDOW_DOLLSTATUS_H