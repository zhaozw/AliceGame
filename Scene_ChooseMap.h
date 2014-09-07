// Scene_ChooseMap.h

// マップを選択するシーン。
// エリア選択とマップ選択の二段階に分けられる。
// マップを選択するとScene_Mapに移行する。

#pragma once

#include "Scene_Base.h"
#include "Static_Map.h"

class Scene_ChooseMap : public Scene_Base{
public:
	// phaze値
	enum CHOOSEMAP_PHAZE{
		PHAZE_ERROR		= -1,
		PHAZE_STANDBY,			// スタンバイ状態。移動出来る。
		PHAZE_EVENT,			// イベントの処理中。最も優先度が高い。
		PHAZE_MENU,				// メニューの処理中。
		PHAZE_CHOOSEMAP,		// エリア内のマップを選択中。
		PHAZE_OPENPATH,			// パスを開く処理中。
		PHAZE_OPENPOINT,		// ポイントを開く処理中。
		PHAZE_CHECK,			// イベント・パス・ポイントの処理がないかを検討する。

	};
private:
	int						cntIndex;		// 現在選択中のポイント番号。
	int						lastIndex;		// 最後に選択していたポイント番号。
	bool					moving;			// 移動中フラグ。
	enum CHOOSEMAP_PHAZE	phaze;			// フェイズ。
	int						phazeTime;		// 現在のフェイズの時間。
	// ポイントが開放状態にあるかどうかの判定。
	// 表示判定や演出のみに使用され、
	// 実際のプレイヤーの移動はパス基準で行われる。
	// なお、パスの状態はRecord_ChooseMapクラスに含まれている。
	// ポイントの状態はそこに含める必要がないのでシーンのメンバとしている。
	bool					pointIsOpened[CHOOSEMAP_POINT_MAX];	
	int						alicePosX, alicePosY; // アリスの位置
	int						openingIndex;	// PHAZE_OPENPATHまたはPHAZE_OPENPOINTにおいて
											// 解放されている最中の地点のインデックス。

public:
	// コンストラクタ
	Scene_ChooseMap();


	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();

	// 更新処理
	virtual int Update();

	// phaze値を変更すると共に、その準備処理を行う。
	bool SetPhaze(enum CHOOSEMAP_PHAZE phaze);

	// 発生するイベントがあるかどうかの判定を行う。
	// イベントがある場合はイベントIDを、
	// イベントがない場合は0を返す。
	WORD CheckEventHappen();

	// 新たに開かれるパスがあるかどうかの判定を行う。
	// イベントがある場合はパスIDを、
	// イベントがない場合は0を返す。
	WORD CheckPathOpen();

	// 新たに開かれるポイントがあるかどうかの判定を行う。
	// イベントがある場合はポイントIDを、
	// イベントがない場合は0を返す。
	// ポイントがあるかどうかの判定のみであり、pathIsOpened値の更新は行わない。
	WORD CheckPointOpen();
	
	// 指定したインデックスのポイントが解放状態になるかどうかを取得する。
	// CheckPointOpen()から参照される。
	// 解放状態の判定は、パス基準で行われる。
	// すなわち、現在開かれているパスのうち、
	// 一つでも指定したポイントと接続されているパスがあれば、
	// そのポイントは開放状態であると判定する。
	bool CheckOpenPoint(WORD index);

	// 全てのポイントに対してCheckOpenPointを行い、
	// ポイントを即座に開く。
	// シーンの最初で行う。
	void RefreshPoints();

	// アリスの位置(座標、足下基準)を更新する。
	// 移動中のカウンタの制御も行う。
	void UpdateAlicePos();

	// アリスを移動させるための入力処理を行う。
	bool CheckAliceMove();

	// 描画処理
	virtual void Draw() const;

	// 背景の描画を行う。
	void DrawBG() const;

	// マップの描画を行う。
	// パスの描画とポイントの描画を含む。
	void DrawMap() const;
	// インデックスで指定したパスの描画を行う。
	void DrawPath(int index) const;
	// 全てのパスの描画を行う。
	void DrawPaths() const;
	// インデックスで指定したポイントの描画を行う。
	void DrawPoint(int index) const;
	// 各ポイントの描画を行う。
	void DrawPoints() const;

	// キャラクターの描画を行う。
	void DrawCharacters() const;
	// アリスの描画を行う。
	void DrawAlice() const;

	// アリスの移動出来る方向を示す矢印を表示する。
	void DrawAliceDirection(int aliceX, int aliceY) const;
	void DrawDirection(int aliceX, int aliceY, BYTE direction) const;

	// コマンド表示中、コマンドの描画を行う。
	void DrawCommand() const;

};

