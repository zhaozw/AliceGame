#ifndef GAME_UNITSUBCOMMAND_H
#define GAME_UNITSUBCOMMAND_H

#include "Game_UnitCommand.h"

// Game_UnitSubCommandクラス
// Game_UnitCommandクラスの内容をScene_Battleのコマンド実行部において
// 分解するために使用するクラス。
// 利便性のため、汎用パラメータparam及び結果を表すビット変数resultが追加されている。

// resultに入る値の列挙
#define COMMAND_RESULT_SUCCEED			0x0000	// 普通に成功した
#define COMMAND_RESULT_TARGET_CHANGED	0x0001	// 成功したがターゲットがずれた
#define COMMAND_RESULT_ZEROVALUE		0x0002	// ダメージや回復系のコマンドにおいて、
												// 与えた・回復したダメージが0だった

class Game_UnitSubCommand : public Game_UnitCommand{
protected:
	int				param;		// 汎用パラメータ。
								// 通常のコマンドとしては使用せず、
								// Game_BattleActionの解釈中に使用する。
	WORD			result;		// 行動の結果を表す。
								// 例として、「毒攻撃」においてダメージを与えるかを
								// 最初に判断し、次に毒ステートの付加の判断を行う際、
								// 最初の「ダメージ」が成功したかどうかの結果を入れる。
public:
	// コンストラクタ
	Game_UnitSubCommand();
	
	// アクセサ
	void	SetParam(int p){ param = p; };
	int		GetParam(){ return param; };
	void	ClearResult(){ result = COMMAND_RESULT_SUCCEED; };
	void	SetResult(BYTE r){ result |= r; };
	void	ResetResult(BYTE r){ result &= ~r; };
	WORD	GetResult(){ return result; };

};

#endif // GAME_UNITSUBCOMMAND_H