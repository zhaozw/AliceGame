#ifndef DATA_BATTLESTATE_H
#define DATA_BATTLESTATE_H

#include <Windows.h>
#include "VectorList.h"

#define STATENAME_LENGTH	32

//==================================================
// 各ステート。

// 戦闘不能になった時に付加されるステート。
#define STATE_DEATH				1

// 防御を選択した時に付加されるステート。
// 受けるダメージに0.5倍の補正をかける。
#define STATE_GUARD				2

// 素早さ補正を行う際に付加されるステート。
// 素早さ判定時にパラメータ×1000の素早さを増加させる。
#define STATE_SUBSPD_UP			3

// 素早さのマイナス補正を行う際に付加されるステート。
// 素早さ判定時にパラメータ×1000の素早さを減少させる。
#define STATE_SUBSPD_DOWN		4

// 一時的に属性を無属性に変えるステート。
// パラメータ：解除までのターン数
// 以下、属性変更系ステートは互いに両立不可。
// 別のものがかけられた時点で元のステートは解除される。
#define STATE_TMPATTR_NONE		5

// 一時的に属性を太陽属性に変えるステート。
// パラメータ：解除までのターン数
#define STATE_TMPATTR_SUN		6

// 一時的に属性を月属性に変えるステート。
// パラメータ：解除までのターン数
#define STATE_TMPATTR_MOON		7

// 一時的に属性を星属性に変えるステート。
// パラメータ：解除までのターン数
#define STATE_TMPATTR_STAR		8

//=============================================
// フラグ関連

// ターンの終わりに解除する
// 具体的には、Game_BattleUnit内のUpdateStateTurnから解除される。
#define STATE_FLAG_REMOVE_AT_TURNEND		0x00000001
// 行動不能になる
// 具体的には、ターンの最初にコマンドが出ない
#define STATE_FLAG_CANNOT_ACT				0x00000002
// 重ねがけ可能か
// 具体的には、既に同じステートになっているとき、
// このフラグが設定されていないと、すでにステートになっていて
// 無効とコメントが出るが、
// フラグを設定しておくとGame_BattleUnitのステートのレベルが1上がる
#define STATE_FLAG_CAN_MULTIPLE				0x00000004
// このステートが付加されているユニットは
// 攻撃対象にならない
// 具体的には、人形のコマンド選択時に選択出来ず、
// また、敵のターゲット選択において対象から外れる。
#define STATE_FLAG_CANNOT_TARGET			0x00000008

// ステート一つを表すクラス。
// Data_BattleStateクラスにVectorListとして保持される。
class Data_BattleState_Each{
private:
	// ステートID。
	WORD		refID;		
	// ステート名
	// 実際に使うかどうかは不明。
	// csvファイルの可視性のためでもある。
	TCHAR		stateName[STATENAME_LENGTH];
	// 処理順序(これに合わせて並べ替えを行う)
	// 最大30、最小1。
	WORD		calcOrder;
	// 描画優先度(優先度の高いものからアイコンを表示する。)
	// 描画優先度が0のものはアイコンを描画しない。
	// 最大10、最小0。
	WORD		drawOrder;
	// アイコンを描画するステートの場合、
	// Imageクラスのアイコンの配列から画像を表示する。
	// その表示画像のインデックス。
	WORD		iconIndex;
	// フラグ。
	// 内容は未定。
	DWORD		flags;
public:
	// コンストラクタ
	Data_BattleState_Each();
	void Refresh();
	// アクセサ
	void		SetStateName(LPTSTR name, int size);
	void		GetStateName(LPTSTR buf, int bufSize);
	void		SetRefID(WORD id){ refID = id; };
	WORD		GetRefID(){ return refID; };
	void		SetCalcOrder(WORD _order){ calcOrder = _order; };
	WORD		GetCalcOrder(){ return calcOrder; };
	void		SetDrawOrder(WORD _order){ drawOrder = _order; };
	WORD		GetDrawOrder(){ return drawOrder; };
	void		SetIconIndex(WORD _icon){ iconIndex = _icon; };
	WORD		GetIconIndex(){ return iconIndex; };
	void		SetFlags(DWORD flag){ flags |= flag; };
	void		ResetFlags(DWORD flag){ flags &= !flag; };
	DWORD		GetFlags(){ return flags; };
};

// 敵グループのデータを保持するクラス。
// グローバル変数d_enemyGroupから参照される。
class Data_BattleState{
private:
	// 敵グループの配列
	VectorList<Data_BattleState_Each>		stateList;

public:
	// コンストラクタ
	Data_BattleState();
	// ロード
	bool Load();
	bool LoadDataFromCsv();

	// ステートの配列をリリースする。
	void ReleaseList(){ stateList.Release(); };


	// ステートへのポインタを取得する。
	// データベースを参照し、指定するrefIDを持っているものを返す。
	// 該当するものがない場合はNULLを返す。
	Data_BattleState_Each* GetBattleState(WORD _refID);

	// 指定したIDのステートが指定したフラグを持っているかどうかを返す。
	bool CheckFlagOfState(WORD _refID, DWORD flag);

	// 大きさを返す。
	int GetSize(){ return stateList.GetSize(); };
};

#endif // DATA_BATTLESTATE_H