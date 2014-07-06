#ifndef GAME_DOLLLIST_H
#define GAME_DOLLLIST_H

#include "FlexList.h"
#include "Game_AliceDoll.h"

// 所持している人形のリストを扱うクラス。
// グローバル変数g_dollListから参照される。

class Game_DollList{
private:
	FlexList<Game_AliceDoll_Essence>	list;
	
public:
	// コンストラクタ
	Game_DollList();
	// ドールリストなどポインタの解放を行う
	bool Release();
};

#endif // GAME_DOLLLIST_H