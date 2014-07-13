#ifndef GAME_BATTLEENEMY_H
#define GAME_BATTLEENEMY_H

// Game_BattleEnemyクラス
// 戦闘における敵一体を示すクラス。

#include "Data_EnemyParam.h"
#include "Game_BattleUnit.h"

class Data_EnemyParam_Each;

class Game_BattleEnemy : public Game_BattleUnit{
private:
	WORD		dataID;				// データを参照する際のID。
	DWORD		exp;				// 経験値
	int			selfTurn;			// 敵毎に異なるターン数。戦闘行動の選択に使用する。
	int			drawX;				// 描画位置
	int			drawY;
	ENEMYACTIONPATTERN*		pActPattern;	// 行動パターンへの参照(データベース)
public: 
	// コンストラクタ
	Game_BattleEnemy();
	// 行動を選択し、行動リストに付け加える。
	bool ChooseAction();
	// 描画位置をセットする。
	void SetDrawPos(int x, int y){ drawX = x; drawY = y; };
	// データベースであるData_EnemyParamクラスからデータを取り込む。
	void LoadFromData(Data_EnemyParam_Each* pData);
	// アクセサ
	DWORD	GetExp(){ return exp; }
	void	SetExp(DWORD n){ exp = n; };
	WORD	GetDataID(){ return dataID; };
	void	SetDataID(WORD _id){ dataID = _id; };
	int		GetDrawX(){ return drawX; };
	int		GetDrawY(){ return drawY; };
	int		GetSelfTurn(){ return selfTurn; };
	void	SetSelfTurn(int turn){ selfTurn = turn; };
	void	SetSelfTurn(); // selfTurn値をランダムにセットする
	void	SetActPattern(ENEMYACTIONPATTERN* pPtn){ pActPattern = pPtn; };
	ENEMYACTIONPATTERN* GetActPattern(){ return pActPattern; };
	// このキャラが人形である場合はtrueを返す。
	virtual bool IsDoll(){ return false; };

	// 全てのパラメータをリセットする。
	virtual void Reset(int n=0);
};

#endif // GAME_BATTLEENEMY_H