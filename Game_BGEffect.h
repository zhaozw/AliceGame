#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>

// typeIDの列挙。
#define GAME_BG_TYPE_NONE				0	// 背景なし。何も描画しない。
#define GAME_BG_TYPE_DUMMY				1	// ダミー背景。チェック画像を並べて表示。

//================================================
// Game_BGEffectクラス
// 
// エフェクトのかかった背景のクラス。
// 戦闘画面の背景、マップ画面の背景などで利用する。
// 

class Game_BGEffect{
private:
	// 背景のタイプID。
	WORD		typeID;

	// 同じタイプIDを使用しながら背景を微妙に変化させたい時の汎用パラメータ。
	// 使い方はtypeIDによって異なる。
	int			param;

	// 時間のパラメータ。
	// SetTypeIDを行う際に0になり、Updateが呼び出される度に増える。
	// 使うかどうか・使い方はtypeIDによって異なる。
	// 毎回エフェクトの基準時間を変えたい場合は、
	// SetRandTime関数を実行すると適当な値がtimeに代入される。
	int			time;

	// 変形の基準に使う座標。
	// これも汎用的なものであり、使い方はtypeIDによって異なる。
	// SetPosition関数で指定する。
	float		posX;
	float		posY;

	// 繰り返しに使用する値で、
	// 画像の幅と高さなどに使用する。
	// 使い方はtypeIDによって異なってもよい。
	float		loopWidth;
	float		loopHeight;


public:

	// コンストラクタ
	Game_BGEffect();

	// タイプIDを変更する。
	// タイプIDごとの初期化処理も含む。
	bool SetTypeID(WORD id);

	// タイプIDを取得する。
	WORD GetTypeID(){ return typeID; };

	// パラメータを変更する。
	void SetParam(int p){ param = p; };

	// パラメータを取得する。
	int GetParam(){ return param; };

	// タイプIDとパラメータをまとめてセットする。
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); };

	// 初期化を行う。
	// タイプIDごとの初期化はこの関数ではなくSetTypeID内で行う。
	bool Initialize();

	// 終了処理を行う。
	bool Terminate();

	// タイプIDごとの演算処理を行う。
	// このオブジェクトが属するクラスから毎フレーム実行される。
	void Update();

	// タイプIDごとの描画処理を行う。
	// このオブジェクトが属するクラスから毎フレーム実行される。
	void Draw() const;

	// 適当な時間を代入する。
	void SetRandTime();

	// 基準位置を代入する。
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; };


};

#endif // GAME_BGEFFECT_H