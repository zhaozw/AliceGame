#ifndef DATA_ENEMYDRAW_H
#define DATA_ENEMYDRAW_H

#include <Windows.h>
#include "VectorList.h"

// refIDがどの敵に対応するかの定数リスト
#define		ENEMYDRAW_ELF			1
#define		ENEMYDRAW_FIREELF		2


// 敵グラフィックの描画位置と描画ハンドルを保持するクラス。
// グローバル変数g_enemyDrawから参照される。

class Data_EnemyDraw_Each{
private:
	// 参照ID
	WORD	refID;
	// 描画の中心位置
	float	cx, cy;
	// 画像のサイズ
	int		iWidth, iHeight;
	// 基本的な描画の倍率
	float	baseExRate;
	// 画像のハンドル
	int		hImg;
public:
	// コンストラクタ
	Data_EnemyDraw_Each();
	// 初期化
	void Refresh();

	// アクセサ
	WORD	GetRefID(){ return refID; };
	void	SetRefID(WORD id){ refID = id; };
	float	GetCX(){ return cx; };
	float	GetCY(){ return cy; };
	void	SetCX(float x){ cx = x; };
	void	SetCY(float y){ cy = y; };
	int		GetHImg(){ return hImg; };
	void	SetHImg(int h){ hImg = h; };
	int		GetIWidth(){ return iWidth; };
	int		GetIHeight(){ return iHeight; };
	void	SetIWidth(int i){ iWidth = i; };
	void	SetIHeight(int i){ iHeight = i; };
	float	GetExRate(){ return baseExRate; };
	void	SetExRate(float r){ baseExRate = r; };



};

class Data_EnemyDraw{
private:
	VectorList<Data_EnemyDraw_Each>		drawList;
public:
	// コンストラクタ
	Data_EnemyDraw();
	
	// データの読み込み
	bool Load();
	bool LoadDataFromCsv();

	// リストを開放する
	void ReleaseList(){ drawList.Release(); };

	// Imageクラスとハンドルを結びつける。
	int	GetImgHandleByRefID(WORD refID);

	// ベクトルの中からrefIDが該当する値を返す。
	Data_EnemyDraw_Each* GetEnemyDraw(WORD refID);
};

#endif // DATA_ENEMYDRAW_H