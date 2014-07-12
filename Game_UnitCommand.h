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
	bool						isUsed;		// コマンドにデータが入っているか
public:
	// コンストラクタ
	Game_UnitCommand();

	// 内容の初期化を行う。
	void Reset();


	// ユニットの行動の並べ替えを行う関数。
	// 速度を比較して、降順にソートを行う。すなわち、速度が大きい方が
	// 昇順ソートする際に小さい値として見なされる。
	// aLeftをaRightよりも前に出したい場合にtrueを返す。
	static bool SortBySpd(const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight){
		// 空の要素は後ろに押しやる
		if(aLeft.IsEmpty()){
			return false;
		}else if(aRight.IsEmpty()){
			return true;
		}
		// ここまでで、どちらかの行動が空の場合はfalseかtrueを返した
		// 後は素早さ同士を比較
		return aLeft.pOwner->GetSpd() > aRight.pTarget->GetSpd();
	};

	// アクセサ
	void SetOwner(Game_BattleUnit* p){ pOwner = p; };
	void SetTarget(Game_BattleUnit* p){ pTarget = p; };
	void SetActionType(BYTE t){ actionType = t; };
	void SetTargetType(BYTE t){ targetType = t; };
	void SetUsed(){ isUsed = true; };

	bool IsEmpty() const{ return !isUsed; };

};

#endif GAME_UNITCOMMAND_H
