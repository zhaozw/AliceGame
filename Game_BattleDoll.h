#ifndef GAME_BATTLEDOLL_H
#define GAME_BATTLEDOLL_H

#include "Static_AliceDoll.h"
#include "Game_BattleUnit.h"

// Game_BattleDollクラス
// 戦闘時の味方キャラ(人形)を扱うクラス。

class Game_AliceDoll_Essence;

class Game_BattleDoll : public Game_BattleUnit{
private:
	// 覚えているスキルの配列
	WORD skillID[DOLL_SKILL_MAX];
public: 
	Game_BattleDoll();

	// スキルIDをセットする。
	void SetSkillID(int index, WORD id){ skillID[index] = id; };

	// スキルIDを取得する。
	WORD GetSkillID(int index){ return skillID[index]; };

	// 人形への参照を指定すると、その人形のレベルを元にパラメータを作成する。
	// 現在のHPのコピー及びスキルのコピーも行う。
	// pDoll	:	コピーするパラメータへの参照
	// useHP	:	Game_AliceDoll_EssenceのHPの値を使用するか否か。
	//				falseの場合は最大HPをHPにコピーする。
	bool SetParamFromReference(Game_AliceDoll_Essence* pDoll, bool useHP=true);

	// 全てのパラメータをリセットする。
	virtual void Reset(int n=0);
};

#endif // GAME_BATTLEDOLL_H