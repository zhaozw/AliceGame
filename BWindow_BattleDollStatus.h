#ifndef BWINDOW_BATTLEDOLLSTATUS_H
#define BWINDOW_BATTLEDOLLSTATUS_H

#include "Window_SimpleDollStatus.h"

class Scene_Battle;

//==============================================================
// BWindow_BattleDollStatusクラス
// 
// 戦闘シーンで使用する、人形のステータスを表示するウィンドウ。
// Scene_Battleへのポインタを持つ。

class BWindow_BattleDollStatus : public Window_SimpleDollStatus{
protected:
	Scene_Battle* pScene;

public:
	// コンストラクタ
	BWindow_BattleDollStatus();

	// セットアップ
	void Setup(Scene_Battle* _pScene);

	// 内容の更新
	virtual void Update();
};


#endif // BWINDOW_BATTLEDOLLSTATUS_H