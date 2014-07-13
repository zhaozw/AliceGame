#ifndef BWINDOW_FOCUSEDENEMY_H
#define BWINDOW_FOCUSEDENEMY_H

#include "Window_Base.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Selectable.h"

#define		BWND_FOCUSEDENEMY_WIDTH			200
#define		BWND_FOCUSEDENEMY_HEIGHT		100

// フォーカスしている敵の情報を表示する。
// 内部的にはSelectableを持つウィンドウである。

class Scene_Battle;
class Game_BattleEnemy;

class BWindow_FocusedEnemy : public Window_Base{
protected:
	// 選択肢
	Selectable				s_enemy;
	// バトルシーンへの参照
	Scene_Battle*			pScene;
	// このウィンドウを保持している人形
	Game_BattleDoll*		pDoll;
	// 現在参照している敵キャラ
	Game_BattleEnemy*		pEnemy;
	// 敵全体にフォーカスした状態
	// (ウィンドウ一つで敵全体を表示する)
	bool					focusAll;
public:
	// コンストラクタ
	BWindow_FocusedEnemy();


	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup(Scene_Battle* _pScene);

	// 
	void SetDoll(Game_BattleDoll* _pDoll){
		pDoll = _pDoll;
	}

	// 開いた時の挙動
	virtual void OnOpened();

	// 選択肢の有効/無効を敵キャラに合わせて行う。
	void CheckEnemyEnabled();

	// インデックス値が変わったとき、
	// 位置及び表示内容の更新を行う。
	void OnIndexChanged();

	// 選択肢のインデックスを指定する。
	// 選択できる敵がいない場合、falseを返す。
	bool SetDefaultIndex();

	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 内容の描画を行う。
	virtual void DrawContent() const;

	// 指定した敵キャラについての描画を行う。
	virtual void DrawCntEnemy(Game_BattleEnemy*) const;

	// アクセサ
	int GetSelectIndex() const { return s_enemy.index; };
	bool GetFocusAll(){ return focusAll; };
	void SetFocusAll(bool b){ focusAll = b; };
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };

};



#endif // BWINDOW_FOCUSEDENEMY_H