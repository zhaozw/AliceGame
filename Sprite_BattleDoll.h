#ifndef SPRITE_BATTLEDOLL_H
#define SPRITE_BATTLEDOLL_H

#include <Windows.h>

#include "Sprite_Base.h"
#include "Static_Game.h"
#include "Game_BattleDoll.h"

// スプライトの基準位置を決める定数

// スプライトの幅と高さ
#define	SPRITE_BATTLEDOLL_WIDTH		150
#define SPRITE_BATTLEDOLL_HEIGHT	200
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
public:
	// コンストラクタ
	Sprite_BattleDoll();
	// 位置のインデックスを渡す
	// この値は一度設定したら変わらない。
	void SetPosition(WORD i){
		position = i; 
		SetPos(
			SPRITE_BATTLEDOLL_IX + SPRITE_BATTLEDOLL_DX*i,
			SPRITE_BATTLEDOLL_IY + SPRITE_BATTLEDOLL_DY*i);
	};
	// 人形へのポインタを渡す
	void SetDollPtr(Game_BattleDoll* p){ pDoll = p; enabled = true; };
	// ポインタを外す
	void ResetDollPtr(){ pDoll = NULL; enabled = false; };

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw() const;

};


#endif // SPRITE_BATTLEDOLL_H

