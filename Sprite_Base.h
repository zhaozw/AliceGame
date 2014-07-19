#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include <Windows.h>

// 主に戦闘画面のスプライトを表示するクラス。
 
// morphIDに指定される定数群
// 動作なし。動き終わった後は自動的にこれになる。
#define		SPMORPH_NONE			0
// 消滅する。
// このアクションの終了後、visible値がfalseになる。
#define		SPMORPH_DISAPPEAR		1
// 選択された状態になる。
// SPMORPH_DISACTIVATEとセットで使う。
#define		SPMORPH_ACTIVATE		2
// 選択状態を解除する。
// SPMORPH_ACTIVATEの後で実行する。
#define		SPMORPH_DISACTIVATE		3
// 一度だけ点滅する。
// 正確には、この状態になった瞬間一回消え、その後また出てくる。
// param値 = 消えるフレーム数
#define		SPMORPH_BLINK			4
// 一度だけ点滅する。
// 正確には、この状態になった瞬間一回消え、その後また出てくる。
// param値 = 消えるフレーム数
#define		SPMORPH_DAMAGE_DOLL		5


// param.effectに指定される定数群
#define		SPEFFECT_NONE			0

// スプライトの考え方
// スプライト＝動いたり回転したりする画像の板。
// スプライトはSpriteParamという構造体を持っていて、
// そこに拡大倍率や回転角の情報が保持されている。
// ある瞬間ごとに、SpriteParamが持っているパラメータに従って
// 描画を行う。実際の描画は派生クラスによって異なる。
// 
// スプライトは、あるタイミングで「こういう動きをしろ」という
// 命令を与えると、時間経過に沿って勝手にそういう動きをする。
// すなわち、SpriteParamが更新され、それによって描画が変化する。

// スプライトの変形などの情報を表すパラメータ。
// 

typedef struct SpriteParam{
	// 本来の描画位置からの変位
	float	dx, dy;
	// 回転角
	float	angle;
	// 隠すか否か(trueだと表示しない。)
	// visibleがtrueかつhideがfalseの場合のみ描画を行う。
	// 両者の違いは、hideはmorphIDによって設定され、
	// visibleはそれ以外のプログラムから設定される。
	bool	hide;
	// 不透明度(0～255, 255で不透明)
	int		opacity;
	// 拡大倍率(x方向、y方向それぞれ)
	float	xScale, yScale;
	// アニメーションする場合のセル。使用しない場合は0。
	int		cell;
	// 特殊効果。白く光る、透明など。
	// 使用するものだけ対応させれば良い。
	BYTE	effect;
	// 汎用パラメータ。
	// この値だけは、morphIDによって変化せず、
	// SetMorphID内で適宜渡される。
	// 描画の際はこの値を使ってもよい。
	int		param;

	// デフォルト値
	SpriteParam(){
		dx = dy = 0;
		angle = 0;
		hide = false;
		opacity = 255;
		xScale = yScale = 1.0f;
		cell = 0;
		effect = SPEFFECT_NONE;
		param = 0;
	}
}SPRITEPARAM;

class Sprite_Base{
public:
protected:
	// 描画の基本位置
	float	ix, iy;
	// 現在のスプライトの大きさ。
	int		width, height;
	// 現在のスプライトの回転中心。
	float	cx, cy;
	// 描画に要するパラメータ
	SPRITEPARAM		param;	
	// スプライトが表示状態であるか否か
	bool			visible;
	// 現在設定されている変形方法のID
	// SPMORPH_xxの定数群で指定される。
	// SPMORPH_NONEの場合は時間の更新を行わない。
	// あるmorphの更新が終わった時はSPMORPH_NONEに自動的に戻る。
	BYTE			morphID;
	// 現在のmorphIDの経過時間。
	int				morphCount;
	// 現在のmorphIDの、変形が終了する時間
	// SetMorphID時に自動で入力される。
	int				morphTime;
	// 現在のmorphIDの、スキップされる時間。
	// SetMorphID時に自動で入力される。
	int				morphSkipTime;

public:
	// コンストラクタ
	Sprite_Base();
	Sprite_Base(float x, float y);
	Sprite_Base(float x, float y, int w, int h);

	// 位置の指定
	void SetPos(float x, float y){ ix = x; iy = y; };

	// 大きさの指定
	void SetSize(int w, int h){ width = w; height = h; };

	// 更新
	virtual void Update();
	// morphIDの値に応じてparamの値を更新する。
	// Update関数を分割したもの。
	// Sprite_Base_Morph.cppに内容を記述する。
	void UpdateMorph();

	// 描画
	// 各派生クラスによって異なる
	virtual void Draw() const{};

	// morphID値のセット
	// 必要ならパラメータも渡す。
	// Sprite_Base_Morph.cppに内容を記述する。
	// forceがtrueの場合、現在のmorphに対して上書きする。
	bool SetMorphID(BYTE morph, bool force=true, int param=0);

	// morphの解除。
	void ResetMorph();

	// 現在画像の変形中かどうかを返す。
	bool GetMorphing(){ return morphID != SPMORPH_NONE; };

	// スキップ可能な状態かを返す
	bool GetCanSkip(){ return ((!GetMorphing()) || morphCount >= morphSkipTime); };

	// アクセサ
	void SetIX(float x){ ix = x; }; 
	void SetIY(float y){ ix = y; }; 
	void SetCX(float x){ cx = x; }; 
	void SetCY(float y){ cx = y; }; 
	void SetWidth(int w){ width = w; };
	void SetHeight(int h){ height = h; };
	void SetVisible(bool b){ visible = b; };
	float GetIX() const{ return ix; };
	float GetIY() const{ return iy; };
	float GetCX() const{ return cx; };
	float GetCY() const{ return cy; };
	int	GetWidth() const{ return width; };
	int	GetHeight() const{ return height; };
	bool GetVisible() const{ return visible; };

protected:
	// パラメータは基本的に外部からアクセス出来ない
	float GetX() const{ return ix+param.dx; };
	float GetY() const{ return iy+param.dy; };
	float GetDX() const{ return param.dx; };
	float GetDY() const{ return param.dy; };
	float GetAngle() const{ return param.angle; };
	bool GetHide() const{ return param.hide; };
	int	GetMorphCount() const{ return morphCount; };
	int GetMorphTime() const{ return morphTime; };
	float GetMorphRate() const{ return (float)morphCount/morphTime; };
	float GetMorphRestRate() const{ return (1.0f - GetMorphRate()); };



};


#endif // SPRITE_BASE_H