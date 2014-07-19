#ifndef DATA_SKILLTEXT_H
#define DATA_SKILLTEXT_H

#include <Windows.h>
#include <tchar.h>
#include "Game_BattleUnit.h"
#include "Static_Skill.h"

// メッセージの表示タイプ
#define SKILLMESSAGE_TYPE_NONE	0		// 何も表示しない
#define SKILLMESSAGE_TYPE_CONST	1		// ステートになるユニットの名前を使わない
#define SKILLMESSAGE_TYPE_UNIT	2		// ユニットの名前を使う

// スキルに伴うメッセージのバイト数。
#define SKILLMESSAGE_BYTES		48

// 一つのメッセージのデータ構造
// メッセージそのものと、表示タイプを保持する。
class Data_SkillMessage_Each{
private:
	BYTE		type;
	TCHAR		message[SKILLMESSAGE_BYTES];
public:
	// コンストラクタ
	Data_SkillMessage_Each(){
		type = SKILLMESSAGE_TYPE_NONE;
		strcpy_s(message, SKILLMESSAGE_BYTES-1, _T(""));
	}
	// 値をセットする
	void SetSkillMessage(BYTE type, LPTSTR str, int strLen=-1);
	// データを読み込む
	bool GetSkillMessage(LPTSTR buf, Game_BattleUnit* pUnit);
};

//================================================
// スキルに関するデータベース。
// スキル名、及び、スキルの使用時などに流れるメッセージを記録する。
// 現時点ではファイルからの読み込みではなくベタ打ちである。

class Data_SkillInfo{
protected:
	// スキル名。
	TCHAR						skillName[MAX_SKILL][MAX_SKILL_BYTES];
	// スキルの対象。
	BYTE						targetType[MAX_SKILL];

	// スキルを使用する際に流れるメッセージ。
	// スキルの数だけ存在する。
	Data_SkillMessage_Each		assertMessages[MAX_SKILL];

	// 使用時以外に、スキルに関連して流れるメッセージ。
	// スキルの数だけ存在するわけではない。
	Data_SkillMessage_Each		subMessages[MAX_SKILL_SUBMESSAGE];
public:

	// コンストラクタ
	Data_SkillInfo();

	// 内容をロードする。
	// （実際にはベタ打ち）
	bool Load();

	// ベタ打ち部分。
	bool SetSkillData();

	// メッセージを取得する
	bool GetAssertMessage(LPTSTR buf, WORD skillID, Game_BattleUnit* pUnit);

	// サブメッセージを取得する
	bool GetSubMessage(LPTSTR buf, WORD refID, Game_BattleUnit* pUnit);
};

#endif // DATA_SKILLMESSAGE_H