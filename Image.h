#ifndef IMAGE_H
#define IMAGE_H

// 数字画像の大きさ
#define IMAGE_SIZE_NUMBER			13	// 数字画像の配列の大きさ
#define IMAGE_SIZE_COLUMN_NUMBER	4	// 数字画像の配列の横
#define IMAGE_SIZE_ROW_NUMBER		3	// 数字画像の配列の縦
#define NUMBER_I_WIDTH				16
#define NUMBER_I_HEIGHT				24

#include "WindowSkin.h"
#include "Static_AliceDoll.h"

//==================================================
// Imageクラス
// 
// 画像のハンドルをまとめて保持するグローバル変数。
// グローバル変数g_imageから参照される。
// 

// ウィンドウに関する画像を保持する。
typedef struct Image_Window{
	int image; // ウィンドウのダミー画像
	int simple[MAX_WNDIMGINDEX];
}IMAGE_WINDOW;

// 文字に関する画像を保持する。
typedef struct Image_Chars{
	int dummy_number_i;
	int number_i[IMAGE_SIZE_NUMBER];
}IMAGE_CHARS;

// イラストに関する画像を保持する。
typedef struct Image_Illust{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_ATTR_NUM];
}IMAGE_ILLUST;

// 敵キャラの画像を保持する。
typedef struct Image_Enemy{
	int	elf;
	Image_Enemy(){
		elf = -1;
	}
}IMAGE_ENEMY;


// 各種アイコン系の画像を保持する。
typedef struct Image_Icon{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_ATTR_NUM][DOLL_FACE_NUM];
	int attrstone_group;
	int attrstone[DOLL_GROUP_NUM][DOLL_ATTR_NUM];
}IMAGE_ICON_; // IMAGE_ICONだと組み込みの定数とかぶるので

// 各種背景系（画面全体）の画像を保持する。
typedef struct Image_BG{
}IMAGE_BG;

// エフェクト（パーティクル）の画像を保持する。
typedef struct Image_Effect{
}IMAGE_EFFECT;

class Image{
public: 
	IMAGE_WINDOW	window;
	IMAGE_CHARS		chars;
	IMAGE_ILLUST	illust;
	IMAGE_ENEMY		enemy;
	IMAGE_ICON_		icon;
	IMAGE_BG		bg;
	IMAGE_EFFECT	effect;
public:
	// コンストラクタ。
	// 全てのハンドルに-1を代入する。
	Image();

	// ロード。
	// 失敗したらfalseを返す。
	bool Load();

	// ウィンドウスキンのロード。
	bool Load_WndSkin();

	// 文字のロード。
	bool Load_Chars();

	// イラストのロード。
	bool Load_Illust();

	// 敵キャラのロード。
	bool Load_Enemy();

	// 背景画像のロード。
	bool Load_BG();

	// アイコンのロード。
	bool Load_Icon();

	// エフェクト画像のロード。
	bool Load_Effect();

	

};


#endif // IMAGE_H