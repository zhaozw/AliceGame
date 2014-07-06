#ifndef WINDOW_BATTLEMESSAGE_H
#define WINDOW_BATTLEMESSAGE_H

#include "Window_Message.h"

// ウィンドウ表示関連の定数
#define WND_BATTLEMSG_X				0
#define WND_BATTLEMSG_Y				0
#define WND_BATTLEMSG_WIDTH			(WND_WIDTH)
#define WND_BATTLEMSG_HEIGHT		128
#define WND_BATTLEMSG_PX			16
#define WND_BATTLEMSG_PY			16

// テキスト移動のアニメーションに要する時間
#define WND_BATTLEMSG_MOVETIME		8

class Scene_Battle;

class Window_BattleMessage : public Window_Message{
private:
	// 親となるシーン
	Scene_Battle*	pParent;
public:
	// コンストラクタ
	Window_BattleMessage();
	// 初期化
	void Setup(Scene_Battle* _pParent);
	// 内容の描画を行う。
	// Window_Messageクラスからさらに派生、独自の描画を行う。
	virtual void DrawContent() const;
	// SceneBattleクラスの指定
	void SetParent(Scene_Battle* p){ pParent = p; };
	// クラス内独自のアップデート関数
	virtual void ExUpdate();
	// クラス内独自のIDLE状態判定関数
	virtual bool CheckIsIdle();
	// 次のメッセージを受け入れる準備が出来ているか
	bool IsReady();
};

#endif // WINDOW_BATTLEMESSAGE