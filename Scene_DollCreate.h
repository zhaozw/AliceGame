#ifndef SCENE_DOLLCREATE_H
#define SCENE_DOLLCREATE_H

#include "Scene_Base.h"
#include "Selectable2D.h"
#include "Selectable.h"
#include "Static_AliceDoll.h"
#include "Window_Yesno.h"


#define EACHGROUP_WIDTH			300
#define EACHGROUP_HEIGHT		120
#define EACHGROUP_MARGIN		10


// シーンのステート
#define SCNSTATE_DOLLCREATE_CHOOSETYPE		0	// どのタイプの人形かの選択
#define SCNSTATE_DOLLCREATE_CHOOSESTONE		1	// 属性の欠片の選択
#define SCNSTATE_DOLLCREATE_ASKCREATE		2	// 人形を作成するかどうかの確認

class Scene_DollCreate : public Scene_Base{
public:
	Window_Yesno		w_yesno;					// 作成条件の確認ウィンドウ
	Selectable			s_group;					// 人形のタイプを選択
	Selectable			s_type[DOLL_GROUP_NUM];		// 人形の種類を選択
	Selectable			s_attr;						// 人形の属性を選択
	// Selectable2D		s_test;
	BYTE				attrStones[DOLL_ATTRSTONE_CREATE];		// 属性の宝石
	BYTE				cntAttrStone;				// 現在の位置

private:
public:
	// コンストラクタ
	Scene_DollCreate();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw();


	// 各タイプについての情報を描画する。
	void DrawEachGroup(int x, int y, BYTE group, bool focused);

	// 各stateの説明を描画する。
	void DrawAccount();
	
	// 属性の宝石を描画する。
	void DrawAttrStones();

	// 宝石選択時の枠を描画する。
	void DrawAttrStoneFocus(int x, int y);

	// 属性の宝石のセットをリセットする。
	void ResetAttrStones();

	// 属性の宝石を指定した位置にセットする。
	void SetAttrStone(BYTE group, BYTE attr, int pos);

	// 指定した位置の属性の宝石を回収する。
	void ResetAttrStone(int pos);

	// 現在登録されている情報を元にTempDataに人形データを代入する。
	void RegisterNewDoll();
};

#endif // SCENE_DOLLCREATE_H