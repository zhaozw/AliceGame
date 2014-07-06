#ifndef GAME_UNITCOMMAND_H
#define GAME_UNITCOMMAND_H

#include "Static_BattleUnit.h"

#include "Game_BattleUnit.h"

// 戦闘におけるユニットの行動を表すクラス。
// ターンの最初にこのクラスの配列が作成され、
// 素早さ順に並べ替えられた後、順番に実行される。
class Game_UnitCommand{
private:
	Game_BattleUnit*			pOwner;		// 行動の主体への参照。
	Game_BattleUnit*			pTarget;	// 行動の対象への参照。
											// 味方全体などの場合はNULLを指定する。
	BYTE						actionType;	// 行動のタイプ。
											// Static_BattleUnit.hに記述される定数。
	BYTE						targetType;	// ターゲットのタイプ。
											// Static_BattleUnit.hに記述される定数。
public:
	Game_UnitCommand();

	void Reset();
	// ユニットの行動の並べ替えを行う関数。
	// 速度を比較して、降順にソートを行う。すなわち、速度が大きい方が
	// 昇順ソートする際に小さい値として見なされる。
	static bool SortBySpd(const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
		return aLeft.pOwner->GetSpd() > aRight.pTarget->GetSpd();
	};
};

#endif GAME_UNITCOMMAND_H
