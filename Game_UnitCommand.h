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
	WORD						skillID;	// スキルのID。
	int							param;		// 汎用パラメータ。
											// 通常のコマンドとしては使用せず、
											// Game_BattleActionの解釈中に使用する。
public:
	// コンストラクタ
	Game_UnitCommand();

	// 内容の初期化を行う。
	void Reset();


	// ユニットの行動の並べ替えを行う関数。
	// 速度を比較して、降順にソートを行う。すなわち、速度が大きい方が
	// 昇順ソートする際に小さい値として見なされる。
	// aLeftをaRightよりも前に出したい場合にtrueを返す。
	static bool SortBySpd(const Game_UnitCommand& aLeft, const Game_UnitCommand& aRight);


	// アクセサ
	void SetOwner(Game_BattleUnit* p){ pOwner = p; };
	void SetTarget(Game_BattleUnit* p){ pTarget = p; };
	void SetActionType(BYTE t){ actionType = t; };
	void SetTargetType(BYTE t){ targetType = t; };
	void SetSkillID(WORD i){ skillID = i; };
	void SetUsed(){ isUsed = true; };
	void SetIsUsed(bool b){ isUsed = b; };
	void SetParam(int p){ param = p; };

	Game_BattleUnit* GetOwner(){ return pOwner; };
	Game_BattleUnit* GetTarget(){ return pTarget; };
	BYTE GetActionType(){ return actionType; };
	BYTE GetTargetType(){ return targetType; };
	WORD GetSkillID(){ return skillID; };
	int GetParam(){ return param; };

	bool IsEmpty() const{ return !isUsed; };

	// 「何もしない」コマンドにする。
	// ターゲットが消滅した場合など。
	void SetEmpty();

};

#endif GAME_UNITCOMMAND_H
