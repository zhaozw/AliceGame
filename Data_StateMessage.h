#ifndef DATA_STATEMESSAGE_H
#define DATA_STATEMESSAGE_H

#include <Windows.h>
#include <tchar.h>
#include "Data_BattleState.h"

// メッセージがあるステートの数
#define STATEMESSAGE_STATENUM	8

// メッセージの最大文字数
#define STATEMESSAGE_BYTES		48

// メッセージの表示タイプ
#define STATEMESSAGE_TYPE_NONE	0		// 何も表示しない
#define STATEMESSAGE_TYPE_CONST	1		// ステートになるユニットの名前を使わない
#define STATEMESSAGE_TYPE_UNIT	2		// ユニットの名前を使う

// メッセージのインデックス
#define STATEMESSAGE_INDEX_DOLL_ADDED	0	// 味方がステートになった時
#define STATEMESSAGE_INDEX_ENEMY_ADDED	1	// 敵がステートになった時
#define STATEMESSAGE_INDEX_REMOVED		2	// ステートから回復した時
#define STATEMESSAGE_INDEX_KEEP			3	// ステート継続（ターン終了時）

#define STATEMESSAGE_INDEX_NUM			4	// インデックスの最大数

class Game_BattleUnit;

// 一つのメッセージのデータ構造
// メッセージそのものと、表示タイプを保持する。
typedef struct Data_StateMessage_DataUnit{
	BYTE		type;
	TCHAR		message[STATEMESSAGE_BYTES];
	Data_StateMessage_DataUnit(){
		type = STATEMESSAGE_TYPE_NONE;
		strcpy_s(message, STATEMESSAGE_BYTES-1, _T(""));
	}
}DATA_STATEMESSAGE_DATAUNIT;

// 一つのステートのメッセージの集合
class Data_StateMessage_Each{
protected:
	DATA_STATEMESSAGE_DATAUNIT		messages[STATEMESSAGE_INDEX_NUM];
public:
	// コンストラクタ
	Data_StateMessage_Each();

	// 値をセットする
	void SetMessage(int index, BYTE type, LPTSTR str, int strLen=-1);

	// 値を取得する
	bool GetStateMessage(LPTSTR buf, int index, Game_BattleUnit* pUnit);
};

// 全部のステートメッセージ
// グローバル変数d_stateMessageから参照される
// 通常のVectorListでデータを管理するクラスとは違い、
// このクラスにおいてはデータの長さは固定。
// ちなみに、0番目のインデックスは空データ。
class Data_StateMessage{
protected:
	// データ
	Data_StateMessage_Each		stateMessages[STATEMESSAGE_STATENUM];
public:
	// コンストラクタ
	Data_StateMessage();

	// ロード
	bool Load();

	// メッセージの設定(ベタ打ち)
	bool SetStateMessages();

	// メッセージを取得する
	// (ステートに関わるユニットを渡すとその名前を入れた文字列を返す)
	// 内容が存在しない場合はfalseを返す
	bool GetStateMessage(LPTSTR buf, WORD stateRefID, int index, Game_BattleUnit* pUnit);
};

#endif // DATA_STATEMESSAGE_H