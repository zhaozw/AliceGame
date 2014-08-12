#ifndef IMAGE_H
#define IMAGE_H

// 数字画像の大きさ
#define IMAGE_SIZE_NUMBER			13	// 数字画像の配列の大きさ
#define IMAGE_SIZE_COLUMN_NUMBER	4	// 数字画像の配列の横
#define IMAGE_SIZE_ROW_NUMBER		3	// 数字画像の配列の縦
#define NUMBER_I_WIDTH				16
#define NUMBER_I_HEIGHT				24
#define NUM_HP_WIDTH				16
#define NUM_HP_HEIGHT				16
#define NUM_DAMAGE_S_WIDTH			24	
#define NUM_DAMAGE_S_HEIGHT			24	
#define NUM_DAMAGE_M_WIDTH			24	
#define NUM_DAMAGE_M_HEIGHT			24	
#define NUM_DAMAGE_L_WIDTH			36	
#define NUM_DAMAGE_L_HEIGHT			36	

#define IMAGE_SIZE_STATEICON		24

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
	int simple[MAX_WNDIMGINDEX];	// シンプル
	int balloon[1];					// 吹き出し
}IMAGE_WINDOW;

// 文字に関する画像を保持する。
typedef struct Image_Chars{
	int dummy_number_i;
	int number_i[IMAGE_SIZE_NUMBER];
	int num_damage;
	int num_hp[IMAGE_SIZE_NUMBER];			// HP表示用
	int num_damage_l[IMAGE_SIZE_NUMBER];	// ダメージ(弱点)表示用
	int num_damage_m[IMAGE_SIZE_NUMBER];	// ダメージ(通常)表示用
	int num_damage_s[IMAGE_SIZE_NUMBER];	// ダメージ(耐性)表示用
	int sign_damage[2];						// 弱点・抵抗表示用
	Image_Chars(){
		dummy_number_i = -1;
		num_damage = -1;
		for(int n=0; n<IMAGE_SIZE_NUMBER; n++){
			number_i[n] = -1;
			num_hp[n] = -1;
			num_damage_l[n] = -1;
			num_damage_m[n] = -1;
			num_damage_s[n] = -1;
		}
		for(int n=0; n<2; n++){
			sign_damage[n] = -1;
		}
	};
}IMAGE_CHARS;

// イラストに関する画像を保持する。
typedef struct Image_Illust{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_ATTR_NUM];
	int doll_dummy[2];
}IMAGE_ILLUST;

// 敵キャラの画像を保持する。
typedef struct Image_Enemy{
	int	elf;
	int fairy[DOLL_ATTR_NUM];
	int snail[DOLL_ATTR_NUM];
	int butterfly[DOLL_ATTR_NUM];
	int rat[DOLL_ATTR_NUM];
	int crow[DOLL_ATTR_NUM];
	int slime[DOLL_ATTR_NUM];
	int flower[DOLL_ATTR_NUM];
	int skeleton[DOLL_ATTR_NUM];
	int harpy[DOLL_ATTR_NUM];
	int bird[DOLL_ATTR_NUM];
	int parrot[DOLL_ATTR_NUM];
	int cardinal;
	Image_Enemy(){
		elf = -1;
		for(int n=0; n<DOLL_ATTR_NUM; n++){
			fairy[n] = -1;
			snail[n] = -1;
			butterfly[n] = -1;
			rat[n] = -1;
			crow[n] = -1;
			slime[n] = -1;
			flower[n] = -1;
			skeleton[n] = -1;
			harpy[n] = -1;
			bird[n] = -1;
			parrot[n] = -1;
		}
		cardinal = -1;
	}
}IMAGE_ENEMY;


// 各種アイコン系の画像を保持する。
typedef struct Image_Icon{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_FACE_NUM][DOLL_ATTR_NUM];
	int attrstone_group;
	int attrstone[DOLL_GROUP_NUM][DOLL_ATTR_NUM];
	int state_group;
	int cursor[2];
	int tile;
	int cleared;
	int	state[64];
	int attr_graph;
	Image_Icon(){};
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

	// 人形のタイプ・属性・表情を指定すると人形のアイコンのハンドルを返す。
	int GetDollIconHandle(WORD type, WORD face, WORD attr);

	

};


#endif // IMAGE_H