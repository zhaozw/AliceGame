#ifndef SPRITE_BATTLEENEMY_H
#define SPRITE_BATTLEENEMY_H

#include "Sprite_Base.h"
#include "Game_BattleEnemy.h"

class Sprite_BattleEnemy : public Sprite_Base{
private:
	// 敵キャラへの参照
	Game_BattleEnemy*		pEnemy;
	WORD	refID;		// 敵のID。
	// 画像内での中心の位置
	// 敵キャラは左上基準ではなく、画像のある一点を指定して基準とする
	// width, heightの値は実際には使用しない。
	float	cx, cy;	
	float	baseExRate;	// 基本的な表示倍率
	int		hImg;		// 画像のハンドル
public:
	// コンストラクタ
	Sprite_BattleEnemy();

	// 敵の情報を元に割り当て
	bool	AttachBattleEnemy(Game_BattleEnemy* _pEnemy);

	// 敵のrefIDが変わった時に描画を変更する。
	// Update内から自動で呼び出される。
	void	UpdateRefID();
	// 
	// 更新
	virtual void Update();

	// 描画
	virtual void Draw() const;

	// HPゲージの描画
	// x, yは中心位置
	virtual void DrawHPGauge(int x, int y) const;
};


#endif // SPRITE_BATTLEENEMY_H