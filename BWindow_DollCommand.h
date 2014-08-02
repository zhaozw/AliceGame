#ifndef BWINDOW_DOLLCOMMAND_H
#define BWINDOW_DOLLCOMMAND_H

#include "Window_Selectable.h"
#include "Game_BattleDoll.h"

#define BWND_DOLLCOMMAND_X		60
#define BWND_DOLLCOMMAND_Y		380
#define BWND_DOLLCOMMAND_W		180
#define BWND_DOLLCOMMAND_H		200
#define BWND_DOLLCOMMAND_PX		24
#define BWND_DOLLCOMMAND_PY		24

#define BWND_DOLLCOMMAND_ATTACK		0
#define BWND_DOLLCOMMAND_SKILL		1
#define BWND_DOLLCOMMAND_GUARD		2

#define BWND_DOLLCOMMAND_PHAZE_NONE		0	// エラー
#define BWND_DOLLCOMMAND_PHAZE_MAIN		1	// コマンド選択中
#define BWND_DOLLCOMMAND_PHAZE_SKILL	2	// スキル選択中
#define BWND_DOLLCOMMAND_PHAZE_TARGET	3	// ターゲット選択中

class Scene_Battle;

class BWindow_DollCommand : public Window_Selectable{
private:
	// このウィンドウを保持するシーンへのポインタ。
	Scene_Battle*		pScene;
	// このウィンドウでコマンドを選択している人形へのポインタ。
	Game_BattleDoll*	pActor;
	// 結果をScene_Battleなどに渡すために保持しておくインデックス
	int			commandIndex;
	// サブコマンドの結果を受け取るインデックス
	int			subIndex;
	// 選択したターゲットのインデックスを保持する
	int			targetIndex;
	// キャンセル可能か否か
	bool		cancelable;
	// ウィンドウのフェイズ。
	BYTE		phaze;
public:
	// コンストラクタ
	BWindow_DollCommand();

	// 開く度にリフレッシュする
	void		Refresh();

	// アクセサ
	int			GetCommandIndex(){ return commandIndex; };
	int			GetSubIndex(){ return subIndex; };
	BYTE		GetPhaze(){ return phaze; };
	void		SetPhaze(BYTE p){ phaze = p; }; // 外部からアクセスする場合

	// 子ウィンドウが閉じた時の挙動
	virtual void OnChildIsClosed();

	// セットアップ
	void MySetup(Scene_Battle* _pScene);

	// 実行者を指定してウィンドウを開く
	void OpenWithActor(Game_BattleDoll* pDoll, bool cancelable);

	// コマンド選択の可否を指定
	virtual void OnOpened();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 自動で閉じるかは場合によって変わる。
	virtual void CheckAutoClose();

	// 現在の項目がキャンセル可能であるかどうかの判定を行う
	// キャンセル可能かどうかは開く時に決まる。
	virtual void CheckCancelable(){};

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// ウィンドウを閉じるとき、現在のコマンド内容を元に
	// Scene_Battleクラスのアクションスタックに内容を追加する。
	bool SetCommandAndClose();

	// ウィンドウを閉じる関数の上書き
	virtual BYTE Close(bool force=false, bool sudden=false);

	// 技のターゲットタイプをtargetTypeに変換する
	// (人形側から見た値に変換する)
	static BYTE ConvertSkillTargetToTarget(BYTE skillTarget);

};


#endif // BWINDOW_DOLLCOMMAND_H