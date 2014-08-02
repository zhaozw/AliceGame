#ifndef BWINDOW_BATTLEENEMYSTATUS_H
#define BWINDOW_BATTLEENEMYSTATUS_H

#include "Window_Info.h"
#include "Game_BattleEnemy.h"

class Scene_Battle;

#define WND_BATTLEENEMYSTATUS_W				216
#define WND_BATTLEENEMYSTATUS_H				240
#define WND_BATTLEENEMYSTATUS_POS_LEFT_X	0
#define WND_BATTLEENEMYSTATUS_POS_RIGHT_X	(WND_WIDTH-WND_BATTLEENEMYSTATUS_W)
#define WND_BATTLEENEMYSTATUS_POS_Y			80	

//===================================
// BWindow_BattleEnemyStatusクラス
// 
// 敵キャラのパラメータを表示するクラス。
// Scene_Battle内で使用される。

class BWindow_BattleEnemyStatus : public Window_Info{
protected:
	// シーン。
	Scene_Battle*			pScene;
	// 参照している人形。
	// 戦闘シーンであればpBattleDoll,
	// キャンプシーンであればpCampDollを使用する。
	Game_BattleEnemy*		pEnemy;

public:
	// コンストラクタ
	BWindow_BattleEnemyStatus();

	// セットアップ。
	// ウィンドウの大きさは描画パターンにより自動的に決まる。
	// ウィンドウの位置はウィンドウを開くときに決定する。
	void Setup(Scene_Battle* _pScene);

	// 参照する人形を指定して開く。
	// pos : ウィンドウの表示位置。
	void OpenWithEnemy(Game_BattleEnemy* pEnemy, BYTE pos);

	// 参照している人形を変更する。
	// 元の参照と異なる場合、表示を消してから再出現させる。
	bool ChangeRefEnemy(Game_BattleEnemy* pEnemy);

	// 更新。
	virtual void Update();

	// 開いた時に実行する関数。
	virtual void OnOpened();

	// 内容の描画。
	virtual void DrawContent() const;

	// アクセサ
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };
};

#endif // BWINDOW_BATTLEENEMYSTATUS_H
