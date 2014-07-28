#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

#include "Window_Text.h"
#include "DXInput.h"

// ContentChangedが実行されてからopacityが元に戻るまでの時間
#define CONTENT_CHANGED_DELAY	12

//===============================================================
// 情報関連のウィンドウを作成する。
// 情報ウィンドウキーを押すと開いて内容を表示し、
// 決定キー・キャンセルキー・情報ウインドウキーのいずれかが押されると閉じる。
// このクラスは抽象クラスではないが、このクラス自体は機能を持たず、各クラスに派生する。
// 基本的に、派生クラスも含めて同じフォントを使用する。

class Window_Info : public Window_Text{
protected:
	// 表示するテキストの不透明度。
	// カーソル変更でテキストが変わった時に
	// 一旦透明度を下げて描画することにより
	// 対象が変わったことを見やすくする。
	int opacity;

	// ContentChangedが実行されてからの時間。
	int changedTime;
public:
	// コンストラクタ
	Window_Info();

	// 内容のセットアップ。
	// フォントはデフォルトのものを使用するため指定する必要がない。
	// ウィンドウのセットアップを行う。
	// この時既に内容はセットされていて、
	// column値及びrow値が決まっている。
	// ここでは大きさなどを決める。
	bool	Setup(
		WindowSkin* _pSkin,
		WINDOWAREA _frameArea,
		WINDOWAREA _contentArea
		);

	// このウィンドウが所属するシーンから呼び出される。
	// 情報ウィンドウ呼び出しキーが押されている場合、ウィンドウを開く。
	// 開いた場合はtrueを返す。この関数自体がOpenを行う。
	// 開いた時に動作が必要な場合はOnOpened関数を用いる。
	bool OpenIfCalled();

	// 各派生クラスで実行する。
	// 決定キーかキャンセルキーが押された時に閉じる。
	// trueの時閉じる。この関数自体はCloseは行わない。
	// (各クラスにより挙動が異なるため)
	bool CheckClose();

	// 十字キーの入力を四方向で取得する。
	// 値はDIGDIR_XXXで返す。
	// g_inputの関数を呼んでいるだけ。
	BYTE GetDigDir();

	// ウィンドウが開いたまま内容が変わった場合に実行する。
	// opacityの値を一旦0にし、少しかけて元に戻す。
	// 各クラスでSetDrawBlendMode関数を使用しないと意味がないので注意。
	void ContentChanged();

	// 内容の更新(開かれた後の動作及びCheckClose、
	// 内容が切り替わった際の不透明度の調整を行う)
	virtual void Update();

	// 内容の描画(内容なし)
	virtual void DrawContent() const{};


};

#endif // WINDOW_INFO_H