#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

// 主に戦闘画面のスプライトを表示するクラス。
 
#define		ANIME_NONE				0
#define		ANIME_TIME_NONE			9999
#define		ANIME_SKIPTIME_NONE		9999

class Sprite_Base{
public:
	enum SPRITESTATE{
		IDLE,				// 更新されていない状態
		ANIME_NOT_SKIP,		// アニメーション中、スキップ不可
		ANIME_SKIP,			// アニメーション中、スキップ可能
		UNDIFINED,			// エラー時
	};
protected:
	// 描画の基本位置
	float	ix, iy;
	// 一時的な描画位置のずれ
	float	dx, dy;
	// スプライトの大きさ
	int		width, height;
	// 描画角度
	float	angle; 
	// 描画倍率
	float	exRate;
	// 表示/非表示
	bool	visible;
	// アニメーションのID。
	int		animeID;
	// アニメーションの現在のフレーム数
	int		animeCount;
	// アニメーションが終了するフレーム数
	int		animeTime;
	// アニメーションがスキップ可能になるフレーム数
	int		animeSkipTime;
	// 現在の状態
	SPRITESTATE state;
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

	// 描画
	virtual void Draw() const{};

	// アクセサ
	float GetX() const{ return ix+dx; };
	float GetY() const{ return iy+dy; };
	float GetIX() const{ return ix; };
	float GetIY() const{ return iy; };
	float GetDX() const{ return dx; };
	float GetDY() const{ return dy; };
	int	GetWidth() const{ return width; };
	int	GetHeight() const{ return height; };
	void SetIX(float x){ ix = x; }; 
	void SetIY(float y){ ix = y; }; 
	void SetDX(float x){ dx = x; }; 
	void SetDY(float y){ dy = y; }; 
	bool GetVisible(){ return visible; };
	void SetVisible(bool v){ visible = v; };


};


#endif // SPRITE_BASE_H