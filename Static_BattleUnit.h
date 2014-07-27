#ifndef STATIC_BATTLEUNIT_H
#define STATIC_BATTLEUNIT_H

// 名前の最大文字数
#define BATTLEUNIT_NAME					10
// TCHARのバイト換算した時の最大バイト数
// 日本語は1文字2バイトのはずだが、
// 何かエラーが起きてもめんどくさいので多めにサイズを確保している
// #define BATTLEUNIT_NAME_BYTES			(BATTLEUNIT_NAME*2)
#define BATTLEUNIT_NAME_BYTES			32

// パラメータ関連
#define BATTLEUNIT_PARAM_NUM			7		// パラメータの最大数。
												// 体力と最大体力は別パラメータ扱い。
#define BATTLEUNIT_PARAM_HP				0		// 体力
#define BATTLEUNIT_PARAM_MAXHP			1		// 最大HP
#define BATTLEUNIT_PARAM_ATK			2		// 攻撃
#define BATTLEUNIT_PARAM_DEF			3		// 防御力
#define BATTLEUNIT_PARAM_SPD			4		// 敏捷
#define BATTLEUNIT_PARAM_MGC			5		// 魔力
#define BATTLEUNIT_PARAM_TEC			6		// 技巧

#define BATTLEUNIT_PARAM_ERROR			-9999	// 変な値にアクセスした時の戻り値

// ステートに関して
#define BATTLEUNIT_STATE_MAX			16		// 同時にかかるステートの最大数

// 行動の種類に関する定数
#define ACTIONTYPE_ERROR		0	// 読み込みエラー
#define ACTIONTYPE_NONE			1	// 何もしない
#define ACTIONTYPE_ATTACK		2	// 通常攻撃
#define ACTIONTYPE_GUARD		3	// 防御
#define ACTIONTYPE_SKILL		4	// 特技
// ここから下はコマンドの解釈中においてのみ使用。
#define ACTIONTYPE_DAMAGE		0	// ダメージ。
#define ACTIONTYPE_HEAL			1	// 回復。
#define ACTIONTYPE_STATE		2	// ステート付加。
									// かばうことは出来ない。

// 行動のターゲットに関する定数
#define ACTIONTARGET_NONE			0	// ターゲットなし
#define ACTIONTARGET_DOLL_ONE		1	// 人形一体
#define ACTIONTARGET_DOLL_ALL		2	// 人形全体
#define ACTIONTARGET_ENEMY_ONE		3	// 敵一体
#define ACTIONTARGET_ENEMY_ALL		4	// 敵全体
#define ACTIONTARGET_TEAM_ONE		5	// 味方一体(人形なら人形、敵なら敵)
#define ACTIONTARGET_TEAM_ALL		6	// 味方全体
#define ACTIONTARGET_OPPONENT_ONE	7	// 相手一体
#define ACTIONTARGET_OPPONENT_ALL	8	// 相手全体
#define ACTIONTARGET_SELF			9	// 自分

#endif // STATIC_BATTLEUNIT_H