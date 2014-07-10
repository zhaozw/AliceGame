#ifndef BWINDOW_SELECTENEMY_H
#define BWINDOW_SELECTENEMY_H

#include "Window_Selectable.h"

class Scene_Battle;

#define BWND_SELECTENEMY_X		0
#define BWND_SELECTENEMY_Y		400
#define BWND_SELECTENEMY_W		300
#define BWND_SELECTENEMY_H		200
#define BWND_SELECTENEMY_PX	16
#define BWND_SELECTENEMY_PY	16

class BWindow_SelectEnemy : public Window_Selectable{
private:
	// バトルシーンへの参照
	Scene_Battle*			pScene;
	// 敵の最大数
	int						enemyNum;
public:
	// コンストラクタ
	BWindow_SelectEnemy();


	// セットアップ
	// (名前ウィンドウの出し方は全てほぼ同じ)
	void MySetup(Scene_Battle* _pScene);


	// 内容のアップデートを行う。
	virtual void Update();			// クラスごとに派生するアップデート関数。

	// 開いた時に実行する関数。
	virtual void OnOpened();

	// 内容の描画を行う。
	virtual void DrawContent() const;

};



#endif // BWINDOW_SELECTENEMY_H