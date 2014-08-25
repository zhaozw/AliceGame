#ifndef GAME_MAPPOINT_H
#define GAME_MAPPOINT_H

#include <Windows.h>
#include "Static_Map.h"

// マップ上のポイント一つを表すクラス。
// 戦闘ポイントやアイテムポイントなどの属性を持つ。
// Scene_Map内においてリストを作る。
// なお、マップ上には道も表示されるが、
// 道はポイントから自動計算される。
// どの方向キーを押したらどのポイント間を移動するのかを
// 決めるため、マップポイント同士は相互に参照する。

class Game_MapPoint{
	// ポイントのID。
	// リストの中から検索するのに必要。
	// 0は使用されていないことを示し、1から始まる。
	WORD			id;
	// マップ上のポイントの属性。
	// 定数MAPPOINT_XXXの値を取る。
	WORD			type;
	// ポイントの持つパラメータ。
	// 汎用的に用いる。
	int				param;
	// 各方向につながっているポイントのID。
	// 上(北)・右(東)・下(南)・左(西)の順。
	WORD			pointID[4];	
	// 各方向につながっている道のID。
	// 上(北)・右(東)・下(南)・左(西)の順。
	WORD			pathID[4];
	// マップ上の座標の位置。
	// そのまま画面上のポイントを表す。
	// 画面のスクロールは想定しない。
	int				posX;
	int				posY;
	// ポイントの開放状態。
	// 定数 MAPSTATE_XXXの値を取る。
	WORD			state;

public:
	// コンストラクタ
	Game_MapPoint();
	
	// アクセサ
	int				GetPosX(){ return posX; };
	int				GetPosY(){ return posY;	};
	void			SetPosX(int x){ posX = x; };
	void			SetPosY(int y){ posY = y; };
	void			SetPos(int x, int y){ SetPosX(x); SetPosY(y); };
	// 直接位置ではなくグリッドで指定
	// ポイントをきれいに並べたい時に
	void			SetGridX(int gridX){ posX = MAPGRID_INI_X + MAPGRID_DLT_X*gridX; };
	void			SetGridY(int gridY){ posY = MAPGRID_INI_Y + MAPGRID_DLT_Y*gridY; };
	void			SetGrid(int gridX, int gridY){ SetGridX(gridX); SetGridY(gridY); };


	// 各方向のポイントのIDを返す。
	// 0はつながっていないことを示す。
	WORD			GetNorthPoint(){ return pointID[0]; };
	WORD			GetEastPoint(){ return pointID[1]; };
	WORD			GetSouthPoint(){ return pointID[2]; };
	WORD			GetWestPoint(){ return pointID[3]; };

	// 各方向の道のIDを返す。
	// 0はつながっていないことを示す。
	WORD			GetNorthPath(){ return pathID[0]; };
	WORD			GetEastPath(){ return pathID[1]; };
	WORD			GetSouthPath(){ return pathID[2]; };
	WORD			GetWestPath(){ return pathID[3]; };

	// 座標を直接指定ではなくグリッドで指定する。
	// 

	// マップをクリアした時に実行される関数。
	void			Clear();

	// マップのポイントの描画を行う。
	void			Draw() const;

};

// マップ上の道一つを表すクラス。
// データとしては保存されないが、
// 便利のためScene_Map内でリストとして作成される。

class Game_MapPath{
protected:
	// 道のID
	int				id;

public:
	// コンストラクタ
	Game_MapPath();

	// マップのポイントの描画を行う。
	void			Draw() const;
};

#endif // GAME_MAPPOINT_H