#ifndef SPRITE_BATTLEDOLL_H
#define SPRITE_BATTLEDOLL_H

#include <Windows.h>

#include "Sprite_Base.h"
#include "Static_Game.h"
#include "Game_BattleDoll.h"
#include "Func_MyGraphic.h"

// スプライトの基準位置を決める定数

// スプライトの幅と高さ
#define	SPRITE_BATTLEDOLL_WIDTH		150
#define SPRITE_BATTLEDOLL_HEIGHT	200
// 描画スクリーンの余白の大きさ
#define SPRITE_BATTLEDOLL_MARGIN	50
// 描画スクリーンの幅と高さ
#define	SPRITE_BATTLEDOLL_SCREENWIDTH	(WIDTH_DOLLILLUST+SPRITE_BATTLEDOLL_MARGIN*2)
#define SPRITE_BATTLEDOLL_SCREENHEIGHT	(HEIGHT_DOLLILLUST+SPRITE_BATTLEDOLL_MARGIN*2)
// 描画時の拡大倍率
#define SPRITE_BATTLEDOLL_DRAWWIDTH		240
// 略称
#define SP_B_DW	SPRITE_BATTLEDOLL_DRAWWIDTH
#define SP_B_SW	SPRITE_BATTLEDOLL_SCREENWIDTH
#define SP_B_SH	SPRITE_BATTLEDOLL_SCREENHEIGHT
// 描画時の拡大倍率
#define SPRITE_BATTLEDOLL_DRAWHEIGHT	(SP_B_DW*SP_B_SH/SP_B_SW)
// 0番目のスプライトの位置
#define SPRITE_BATTLEDOLL_IX		300
#define SPRITE_BATTLEDOLL_IY		(WND_HEIGHT - SPRITE_BATTLEDOLL_HEIGHT - 20)
// 1番目以降のスプライトの位置のずれ
#define SPRITE_BATTLEDOLL_DX		160
#define SPRITE_BATTLEDOLL_DY		0

// バトルシーンにおいて人形一体を表示するスプライト。
// 戦闘シーンにおいて人形一体を参照する。
// 特定の人形を常に参照するわけではなく、
// 戦闘における隊列に基づいて入れ替えがある度に参照を変える。
class Sprite_BattleDoll : public Sprite_Base{
protected:
	// 位置のインデックス。
	WORD						position;
	// 人形への参照。
	Game_BattleDoll*			pDoll;
	// 人形への参照が行われているか。
	// (人形が3体以下の場合は参照しないこともありうる)
	bool						enabled;
	// 描画用のスクリーンのハンドル。
	int							drawScreen;
public:
	// コンストラクタ
	Sprite_BattleDoll();
	// 
	// 位置のインデックスを渡す
	// この値は一度設定したら変わらない。
	void SetPosition(WORD i){
		position = i; 
		SetPos(
			SPRITE_BATTLEDOLL_IX + SPRITE_BATTLEDOLL_DX*i,
			SPRITE_BATTLEDOLL_IY + SPRITE_BATTLEDOLL_DY*i);
	};
	// 人形へのポインタを渡す
	void SetDollPtr(Game_BattleDoll* p){ pDoll = p; enabled = (p!=NULL); };
	// 人形へのポインタを返す
	Game_BattleDoll*  GetDollPtr(){ return (enabled ? pDoll : NULL); };
	// ポインタを外す
	void ResetDollPtr(){ pDoll = NULL; enabled = false; };
	// 描画用スクリーンを作成する。
	bool SetupDrawScreen();
	// 更新
	virtual void Update();

	// 描画
	virtual void Draw() const;
	void DrawFrame() const;
	void DrawDoll() const;
	void DrawInfo() const;

	// アクセサ
	int	GetDollX() const{ return (GetX()+SPRITE_BATTLEDOLL_WIDTH/2); };
	int	GetDollY() const{ return (GetY()+SPRITE_BATTLEDOLL_HEIGHT/2+20); };
	
	// 他のクラスからスプライトの位置を知りたい場合
	static int GetSpriteX(int n){ return SPRITE_BATTLEDOLL_IX+n*SPRITE_BATTLEDOLL_DX; };

};


#endif // SPRITE_BATTLEDOLL_H

