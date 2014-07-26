#ifndef BWINDOW_FOCUSEDENEMY_H
#define BWINDOW_FOCUSEDENEMY_H

#include "Window_Base.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Selectable.h"

#define		BWND_FOCUSEDENEMY_WIDTH			200
#define		BWND_FOCUSEDENEMY_HEIGHT		100

#define		BWND_FOCUS_TARGET_NONE			0
#define		BWND_FOCUS_TARGET_ONE_ENEMY		1	// 敵一体
#define		BWND_FOCUS_TARGET_ALL_ENEMIES	2	// 敵全体
#define		BWND_FOCUS_TARGET_ONE_DOLL		3	// 味方一体
#define		BWND_FOCUS_TARGET_ALL_DOLLS		4	// 味方全体
#define		BWND_FOCUS_TARGET_ALL_UNITS		5	// 敵味方全体
#define		BWND_FOCUS_TARGET_FIXED_DOLL	6	// 味方一体（カーソル移動不可）
#define		BWND_FOCUS_TARGET_FIXED_ENEMY	7	// 敵一体（カーソル移動不可）

#define		BWND_FOCUS_TYPE_UNDIFINED		0
#define		BWND_FOCUS_TYPE_ATTACK			1	// 攻撃時
#define		BWND_FOCUS_TYPE_SKILL			2	// スキルの対象選択時

#define		BWND_FOCUS_FLAG_EXCLUDE_DEAD	0x01	// 戦闘不能のキャラクターを
													// 選択不可にし、かつ
													// 矢印を表示しない
#define		BWND_FOCUS_FLAG_EXCLUDE_ALIVE	0x02	// 戦闘可能なキャラクターを
													// 選択不可にし、かつ
													// 矢印を表示しない


// フォーカスしている敵の情報を表示する。
// 内部的にはSelectableを持つウィンドウである。

class Scene_Battle;
class Game_BattleEnemy;

class BWindow_FocusedUnit : public Window_Base{
protected:
	// 選択肢
	Selectable				s_target;
	// バトルシーンへの参照
	Scene_Battle*			pScene;
	// このウィンドウを保持している人形
	Game_BattleUnit*		pOwner;
	// 現在参照している敵キャラ
	// 複数の場合はNULLを使用する
	Game_BattleUnit*		pTarget;
	// 選択のタイプ
	BYTE					focusTarget;
	// どのタイミングで開かれたウィンドウか
	BYTE					focusType;
	// 選択に関するフラグ
	BYTE					flags;
public:
	// コンストラクタ
	BWindow_FocusedUnit();


	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup(Scene_Battle* _pScene);

	// 開いた時の挙動
	virtual void OnOpened();

	// 選択肢の有効/無効を敵キャラに合わせて行う。
	void CheckEnemyEnabled();

	// 選択肢の有効/無効を味方キャラに合わせて行う。
	void CheckDollEnabled();

	// インデックス値が変わったとき、
	// 位置及び表示内容の更新を行う。
	void OnIndexChanged();

	// 選択肢のインデックスを指定する。
	// 選択できる敵がいない場合、falseを返す。
	bool SetDefaultEnemyIndex();

	// 選択肢のインデックスを指定する。
	// 選択できる味方がいない場合、falseを返す。
	bool SetDefaultDollIndex();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// 指定した敵キャラについての描画を行う。
	virtual void DrawCntEnemy(Game_BattleEnemy* pTarget) const;

	// 指定した人形（場所ID）についての描画を行う。
	virtual void DrawCntDoll(BYTE index) const;

	// アクセサ
	int GetSelectIndex() const { return s_target.index; };
	/*
	bool GetFocusAll(){ return focusAll; };
	void SetFocusAll(bool b){ focusAll = b; };
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };

	*/

	// ターゲットの種類とタイミングを指定して開く。
	void OpenWithParam(Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
		BYTE _focusTarget, BYTE _focusType, BYTE _flags=0x00);

	// 開く動作を行う前後に別途パラメータの指定がある場合、
	// 各パラメータの指定を行う。
	void SetParam(Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
		BYTE _focusTarget, BYTE _focusType, BYTE _flags=0x00);

	Game_BattleUnit* GetOwner(){ return pOwner; };
	Game_BattleUnit* GetTarget(){ return pTarget; };
	Game_BattleUnit* GetTargetAsCommandTarget();	// Game_BattleCommandに渡す用。

	static BYTE ConvertTargetTypeToFocusType(BYTE targetType);
};



#endif // BWINDOW_FOCUSEDENEMY_H