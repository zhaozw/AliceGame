#ifndef GAME_BATTLEACTION_H
#define GAME_BATTLEACTION_H

#include <Windows.h>

// Game_BattleActionクラス
// バトルにおいて発生する実際の動作を扱うクラス。
// 例として、誰かから誰かのダメージなどを表す。
// Scene_Battleからスタック構造で利用される。

// 参照を渡す。
class Game_BattleUnit;

class Game_BattleAction{
public:
	// 列挙子を記述する。
	enum ActionType{
		TYPE_NONE,			// スタックの0番目の要素が持つタイプ
		TYPE_DAMAGE,
		TYPE_CALLENEMYNAME,	// 戦闘開始時、敵の名前を列挙する。
		TYPE_UNDIFINED,
	};
private:
	// メンバ
	
	// 行動をするユニットへの参照
	Game_BattleUnit*	pActor;	
	// 行動をされるユニットへの参照
	Game_BattleUnit*	pOpponent;
	// 行動の種類
	ActionType			type;
	// 各種フラグ
	DWORD				flags;
	// 各種パラメータ。
	int					param;

public:
	// コンストラクタ
	Game_BattleAction();

	// 代入演算子
	// メンバを全てコピーする。
	Game_BattleAction &operator=(const Game_BattleAction &o);  // 代入演算子

	// 内容を初期化する。
	// スタックが取り出された時に実行する。
	void Clear();

	// アクセサ
	void SetActor(Game_BattleUnit* p){ pActor = p; };
	Game_BattleUnit* GetActor(){ return pActor; };
	void SetOpponent(Game_BattleUnit* p){ pOpponent = p; };
	Game_BattleUnit* GetOpponent(){ return pOpponent; };
	void SetType(enum ActionType t){ type = t; };
	enum ActionType GetType(){ return type; };
	void SetFlags(DWORD p){ flags = p; };
	DWORD GetFlags(){ return flags; };
	void SetFlag(DWORD flag){ flags |= flag; };
	void ResetFlag(DWORD flag){ flags |= ~flag; };
	bool GetFlag(DWORD flag){ return (flags &= flag) != 0; } ;
	void SetParam(int p){ param = p; };
	int GetParam(){ return param; };

	// 無効かどうかの判定
	bool IsEmpty(){ return type == TYPE_UNDIFINED; };

};

// Game_BattleActionクラスのスタックを扱うクラス。
// Scene_Battleクラスの変数actionStackとして保持される。
// 本当はメモリとか使った方がいいのだが、自分にはレベルが高いので
// 固定長の領域を確保しておいてスタックのふりをする。
// 0番目の要素には、エラーが起きたときに返す値を常に保持しておく。

// スタックの最大数。
#define MAX_BATTLEACTIONSTACK	32

class Game_BattleActionStack{
private:
	Game_BattleAction		data[MAX_BATTLEACTIONSTACK+1];
	int						cntIndex;	// 現在のスタックの位置。
public:
	// コンストラクタ
	Game_BattleActionStack();

	// 現在指しているデータを返す。
	// データの削除は行わない。
	Game_BattleAction GetCntData();

	// データを一つプッシュ（追加）し、インデックスをずらす。
	// 具体的には、Game_BattleActionクラスの実体を渡すと値を全てコピーして
	// 内容をスタックに追加する。
	// 成功したらtrue、失敗したらfalseを返す。
	bool Push(Game_BattleAction action);

	// データを一つポップ（取り出し）し、インデックスをずらす。
	// 具体的には、Game_BattleActionクラスの実体を返す。
	// データが無い場合やインデックスがおかしい場合には0番目の要素を返す。
	Game_BattleAction Pop();

	// データを一つ取り出すが、インデックスはずらさない。
	// データが無い場合やインデックスがおかしい場合には0番目の要素を返す。
	Game_BattleAction Pop_NoRemove();

	// データへのポインタを渡し、インデックスをずらす。
	// 戻り値は、成功したらtrue、失敗したらfalseになる。
	// 渡したポインタを絶対にdeleteしてはいけない。
	// データが無い場合やインデックスがおかしい場合には0番目の要素を返す。
	// bool PopPtr(Game_BattleAction* pAction);

	// 現在スタックされているデータの個数を返す。
	int	GetSize(){ return cntIndex; };

	// 全てのデータをクリアする。
	void ClearAll();
};

#endif // GAME_BATTLEACTION