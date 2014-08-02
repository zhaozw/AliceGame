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

// スキルの説明画面で出る文章のバイト数。
#define SKILLACC_BYTES			64			

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

// 一つのスキルのデータ構造
// スキル名、ターゲット、消費MPなどを保持する構造体。
class Data_SkillInfo_Each{
protected:
	// スキル名。
	TCHAR		skillName[MAX_SKILL_BYTES];
	// スキルの説明。
	TCHAR		account[SKILLACC_BYTES];
	// スキル使用時のメッセージ。
	Data_SkillMessage_Each		assertMessage;
	// スキルで消費する魔力。
	int			costMP;
	// スキルの対象。
	BYTE		targetType;
public:
	// コンストラクタ
	Data_SkillInfo_Each();

	// データをセットする。
	void SetData(
		LPTSTR _skillName,
		LPTSTR _account,
		LPTSTR _assertMsg, BYTE _assertMsgType,
		int _costMP, BYTE _targetType);

	// アクセサ
	void	GetSkillName(LPTSTR buf);
	void	GetSkillAccount(LPTSTR buf);
	void	GetAssertMessage(LPTSTR buf, Game_BattleUnit* pUnit){
		assertMessage.GetSkillMessage(buf, pUnit); };
	int		GetCostMP(){ return costMP; };
	BYTE	GetTargetType(){ return targetType; };
};

//================================================
// スキルに関するデータベース。
// スキル名、及び、スキルの使用時などに流れるメッセージを記録する。
// 現時点ではファイルからの読み込みではなくベタ打ちである。

class Data_SkillInfo{
protected:
	Data_SkillInfo_Each			data[MAX_SKILL];
	/*
	// スキル名。
	TCHAR						skillName[MAX_SKILL][MAX_SKILL_BYTES];
	// スキルの対象。
	BYTE						targetType[MAX_SKILL];
	// スキルで消費する魔力。
	int							costMP[MAX_SKILL];

	// スキルを使用する際に流れるメッセージ。
	// スキルの数だけ存在する。
	Data_SkillMessage_Each		assertMessages[MAX_SKILL];

	// スキルの説明。
	// スキルの数だけ存在する。
	TCHAR						account[MAX_SKILL][SKILLACC_BYTES];
	*/

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

	// スキル名を取得する。
	bool GetSkillName(LPTSTR buf, WORD skillID);

	// スキルの説明を取得する。
	bool GetSkillAccount(LPTSTR buf, WORD skillID);

	// ターゲットのタイプを取得する。
	BYTE GetTargetType(WORD skillID);

	// 消費MPを取得する。
	int GetCostMP(WORD skillID);

	// メッセージを取得する
	bool GetAssertMessage(LPTSTR buf, WORD skillID, Game_BattleUnit* pUnit);

	// サブメッセージを取得する
	bool GetSubMessage(LPTSTR buf, WORD refID, Game_BattleUnit* pUnit);
};

#endif // DATA_SKILLMESSAGE_H