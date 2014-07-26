#ifndef BWINDOW_DOLLSKILL_H
#define BWINDOW_DOLLSKILL_H

#include "Window_Selectable.h"

#define BWND_DOLLSKILL_X		150
#define BWND_DOLLSKILL_Y		400
#define BWND_DOLLSKILL_W		500
#define BWND_DOLLSKILL_H		150
#define BWND_DOLLSKILL_PX		16
#define BWND_DOLLSKILL_PY		16

class Scene_Battle;
class Game_BattleDoll;
class Game_BattleUnit;

// BWindow_DollSkillクラス
// 戦闘時に人形の特技一覧を表示するクラス。

class BWindow_DollSkill : public Window_Selectable{
private:
	// このウィンドウを保持するシーンへのポインタ。
	Scene_Battle*		pScene;
	// 参照している人形へのハンドル
	Game_BattleDoll*	pOwner;
	// ターゲット選択ウィンドウの選択値
	// 全体選択だったりした場合はNULLになる
	Game_BattleUnit*	pTarget;
public:
	BWindow_DollSkill();

	// セットアップ
	void MySetup(Scene_Battle* _pScene);

	// 人形へのハンドルを渡す。
	void SetDoll(Game_BattleDoll* p){ pOwner = p; };

	// 開いた時の挙動
	virtual void OnOpened();

	// 子が閉じた時の挙動
	virtual void OnChildIsClosed();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 項目を選択後、自動で閉じるかどうかの判定を行う
	virtual void CheckAutoClose(){ autoClose = false; };

	// 現在の項目がキャンセル可能であるかどうかの判定を行う
	// スキルウィンドウは常にキャンセル可能。
	virtual void CheckCancelable(){ cancelable = true; };

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// ターゲットを取得する。
	Game_BattleUnit* GetTarget(){ return pTarget; };

};

#endif // BWINDOW_DOLLSKILL_H