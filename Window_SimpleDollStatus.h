#ifndef WINDOW_SIMPLEDOLLINFO_H
#define WINDOW_SIMPLEDOLLINFO_H

#include "Window_Info.h"

class Game_BattleDoll;
class Game_AliceDoll;

#define DRAWPTN_ALLSTATUS		0	// 戦闘に関するすべてのステータスを表示。

//===================================
// Window_SimpleDollStatusクラス
// 
// 人形のパラメータをシンプルに表示するクラス。
// 複数のシーンから参照されることを想定し、
// 特定のシーンへのポインタは保持しない。
// Setup時に設定するdrawPatternの値により
// ウィンドウの大きさや描画内容が変わる。
// 位置の設定についてはSetPosition関数から行い、自動化は行わない。
// 実は、バトルシーンにおける人形のステータス表示と
// それ以外のシーンにおける人形のステータス表示（両者はクラスが異なる）を
// 共通して表示するアクロバティックなクラス。

class Window_SimpleDollStatus : public Window_Info{
private:
	// 参照している人形。
	// 戦闘シーンであればpBattleDoll,
	// キャンプシーンであればpCampDollを使用する。
	Game_BattleDoll*		pBattleDoll;
	Game_AliceDoll*			pCampDoll;
	// 描画パターン。
	// 表示する情報を微妙に変える場合に用いる。
	BYTE					drawPtn;
	// 戦闘シーンであればtrue。
	bool					isBattle;

public:
	// コンストラクタ
	Window_SimpleDollStatus();

	// セットアップ。
	// 描画パターンと使用するシーンをセットする。
	// ウィンドウの大きさは描画パターンにより自動的に決まる。
	// ウィンドウの位置はウィンドウを開くときに決定する。
	void Setup(BYTE _drawPtn, bool _isBattle);

	// 参照する人形を指定して開く。
	void OpenWithBattleDoll(Game_BattleDoll* pDoll, int _x, int _y);
	void OpenWithCampDoll(Game_AliceDoll* pDoll, int _x, int _y);

	// 参照している人形を変更する。
	// 元の参照と異なる場合、表示を消してから再出現させる。
	bool ChangeRefBattleDoll(Game_BattleDoll* pDoll);
	bool ChangeRefCampDoll(Game_AliceDoll* pDoll);

	// 更新。
	virtual void Update();

	// 内容の描画。
	virtual void DrawContent() const;

	// 内容の描画（戦闘シーンの場合）
	virtual void DrawContent_Battle() const;

	// 内容の描画（戦闘シーン以外の場合）
	virtual void DrawContent_Camp() const;


};


#endif // WINDOW_SIMPLEDOLLINFO

