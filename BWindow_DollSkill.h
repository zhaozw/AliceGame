#ifndef BWINDOW_DOLLSKILL_H
#define BWINDOW_DOLLSKILL_H

#include "Window_Selectable.h"
#include "Window_LineInfo.h"
#include "Static_AliceDoll.h"

#define BWND_DOLLSKILL_W		500
#define BWND_DOLLSKILL_H		150
#define BWND_DOLLSKILL_X		150
#define BWND_DOLLSKILL_Y		(WND_HEIGHT-WND_LINEINFO_HEIGHT-BWND_DOLLSKILL_H)
#define BWND_DOLLSKILL_PX		16
#define BWND_DOLLSKILL_PY		16

class Scene_Battle;
class Game_BattleDoll;
class Game_BattleUnit;

class BWindow_DollCommand;

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
	// コマンドウィンドウへのポインタ
	BWindow_DollCommand* pWndCommand;
	// コマンドの消費MPの配列
	int					costMP[DOLL_SKILL_MAX];
public:
	BWindow_DollSkill();

	// セットアップ
	// BWindow_DollCommandを渡すのは、情報ウィンドウにアクセスするため。
	void MySetup(Scene_Battle* _pScene, BWindow_DollCommand* _pWndCommand);

	// 人形へのハンドルを渡す。
	void SetDoll(Game_BattleDoll* p){ pOwner = p; };

	// 開いた時の挙動
	virtual void OnOpened();

	// 子が閉じた時の挙動
	virtual void OnChildIsClosed();

	// インデックスが変化した、または開いたときの挙動
	void OnIndexChanged();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 項目を選択後、自動で閉じるかどうかの判定を行う
	virtual void CheckAutoClose(){ autoClose = false; };

	// 現在の項目がキャンセル可能であるかどうかの判定を行う
	// スキルウィンドウは常にキャンセル可能。
	virtual void CheckCancelable(){ cancelable = true; };

	// ターゲットを取得する。
	Game_BattleUnit* GetTarget(){ return pTarget; };

	// 指定した項目の内容の描画を行う。
	// 他のクラスから実行されうるため、分けている。
	virtual void DrawContentItem(int index, BYTE fontColor) const;
};

#endif // BWINDOW_DOLLSKILL_H