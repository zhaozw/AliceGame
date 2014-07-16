#ifndef SCENE_CAMP_H
#define SCENE_CAMP_H

#define CAMP_MENU_START		0	// ダンジョンへ移動
#define CAMP_MENU_EDIT		1	// チーム編成
#define CAMP_MENU_CREATE	2	// 人形の作成
#define CAMP_MENU_SAVE		3	// データの保存
#define CAMP_MENU_EXIT		4	// ゲームをやめる
#define MAX_CAMP_MENU		(CAMP_MENU_EXIT+1)

// キャンプのステート
#define SCNSTATE_CAMP_CHOOSEMENU		0		// メニューの選択中
#define SCNSTATE_CAMP_ASKQUITGAME		1		// ゲームを終了するかどうかの確認

// GUIに使用する
// アニメ1 : 左にずれる、フォーカスを外すと戻る
// アニメ2 : 光る、フォーマスに関わらず一瞬のアニメ
#define CAMP_ANIME1_TIME	1000
#define CAMP_ANIME2_TIME	10
#define CAMP_INFO_TIME		120

// 画面下部に表示する情報のID
#define CAMP_INFO_NONE		0	// 何も表示されていない
#define CAMP_INFO_SAVE		1	// 「セーブしました」
#define CAMP_INFO_REST		2	// 「休憩して魔力を回復しました」
#define MAX_CAMP_INFO		2	// 情報の最大数。判定に用いる。NONEは含めない。

#include "Scene_Base.h"
#include "Selectable.h"
#include "Window_Yesno.h"

class Scene_Camp : public Scene_Base{
public:

private:
	Selectable		s_main;
	WORD			menu_anime1[MAX_CAMP_MENU];
	BYTE			menu_anime2[MAX_CAMP_MENU];
	// 画面下部に表示する情報のID。
	BYTE			infoIndex;
	// 画面下部に表示する情報がある場合、情報が出現してからの時間。
	BYTE			infoTime;
	// ゲーム終了の確認ウィンドウ
	Window_Yesno	w_yesno;

public:
	// コンストラクタ
	Scene_Camp();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	// ウィンドウの初期化
	bool InitWindow();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;

	// 画面下に情報を流す。
	void SetInfo(BYTE index){
		if(index <= MAX_CAMP_INFO){
			infoIndex = index;
			infoTime = 1;
		}
	}

};

#endif // SCENE_CAMP_H