#ifndef STATIC_BATTLE
#define STATIC_BATTLE

//=========================================
// ユニット数関連

// パーティに参加する人形の最大数
#define MAX_BATTLEDOLL			8
// 前列に出る人形の最大数
#define NUM_BATTLEDOLL_FRONT	3
// 敵の最大数
#define MAX_BATTLEENEMY			8
// 攻撃パターンの最大数
#define MAX_UNITCOMMAND			(MAX_BATTLEDOLL + MAX_BATTLEENEMY)

//=========================================
// ユニット名の最大文字数
#define BATTLEUNIT_NAME					10
// TCHARのバイト換算した時の最大バイト数
// 日本語は1文字2バイトのはずだが、
// 何かエラーが起きてもめんどくさいので多めにサイズを確保している
// #define BATTLEUNIT_NAME_BYTES			(BATTLEUNIT_NAME*2)
#define BATTLEUNIT_NAME_BYTES			32

//======================================
// ユニットのパラメータ関連
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

//========================================
// 敵データのパラメータ数
#define NUM_ENEMYPARAM_DATA			(BATTLEUNIT_PARAM_NUM-1)
#define ENEMYPARAM_HP				0
#define ENEMYPARAM_ATK				1
#define ENEMYPARAM_DEF				2
#define ENEMYPARAM_SPD				3
#define ENEMYPARAM_MGC				4
#define ENEMYPARAM_TEC				5



//=========================================
// アリスのコマンド群

#define ALICE_COMMAND_BATTLE		0	// 戦う
#define ALICE_COMMAND_UNITCHANGE	1	// ユニット交換
#define ALICE_COMMAND_SPECIAL		2	// 特技
#define ALICE_COMMAND_ESCAPE		3	// 逃げる

//==========================================
// コマンドの種類に関する定数
#define COMMANDTYPE_ERROR		0	// 読み込みエラー
#define COMMANDTYPE_NONE		1	// 何もしない
#define COMMANDTYPE_ATTACK		2	// 通常攻撃
#define COMMANDTYPE_GUARD		3	// 防御
#define COMMANDTYPE_SKILL		4	// 特技


//=========================================
// commandPhazeの配列

#define COMMANDPHAZE_NOPHAZE		0	// 戦闘行動以外で使用する。
										// actionPhazeを使用しない場合の値
#define COMMANDPHAZE_BEFORE_SORT	1	// コマンドを素早さ順に入れ替える前。
										// 基本的に、素早さを補正する以外の
										// 行為は行わない。
#define COMMANDPHAZE_AFTER_SORT		2	// 素早さ順に入れ替えた後に行う。
										// 自分へのステート付加など。
#define COMMANDPHAZE_NEXTCOMMAND	3	// 次のコマンドに移動する時に入れる値。
										// それ自身は特に意味はない。
#define COMMANDPHAZE_FIX_COMMAND	10	// 何より先に、正しく行動できるかを判定する
#define COMMANDPHAZE_FIX_TARGET		11	// 行動の宣言より前に、ターゲットの確定を行う
#define COMMANDPHAZE_ASSERT			12	// 行動宣言時に行う判定。
#define COMMANDPHAZE_PRE_ACTION		13	// 行動前に行う判定。
#define COMMANDPHAZE_ACTION			14	// 行動時に行う判定。
#define COMMANDPHAZE_CHECK_DEATH	15	// 行動後にはとりあえず死亡判定。
#define COMMANDPHAZE_POST_ACTION	16	// 行動後に行う判定。

#define COMMANDPHAZE_ERROR			-1	// エラー
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_FIX_COMMAND)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)

//=========================================
// ダメージの最大値。
#define DAMAGE_MAX			9999

//=========================================
// 属性攻撃の倍率
#define ATTRAFFINITY_EVEN	0	// ふつう
#define ATTRAFFINITY_STRONG	1	// 強い
#define ATTRAFFINITY_WEAK	2	// 弱い

#define ATTRRATE_STRONG		2.0		// 弱点をついた時に与えるダメージ
#define ATTRRATE_WEAK		0.5		// 相手が有利だったときに与えるダメージ

//=============================================
// 行動のターゲットに関する定数
#define ACTIONTARGET_NONE			0	// ターゲットなし
#define ACTIONTARGET_DOLL_ONE		1	// 人形一体
#define ACTIONTARGET_DOLL_ALL		2	// 人形全体
#define ACTIONTARGET_ENEMY_ONE		3	// 敵一体
#define ACTIONTARGET_ENEMY_ALL		4	// 敵全体
#define ACTIONTARGET_NO_MP			10	// 魔力が足りない時にフラグとして使用する特殊な値。

//=============================================
// スキルのターゲットとして利用する定数。
#define SKILLTARGET_NONE			0	// 対象なし(もしくは場全体)
#define SKILLTARGET_TEAM_ONE		1	// 味方一体(人形なら人形、敵なら敵)
#define SKILLTARGET_TEAM_ALL		2	// 味方全体
#define SKILLTARGET_OPPONENT_ONE	3	// 相手一体
#define SKILLTARGET_OPPONENT_ALL	4	// 相手全体
#define SKILLTARGET_SELF			5	// 自分

//=======================================
// 敵の行動の対象に関する定数
// Data_EnemyParamにおいて使用する。
// この値を元に行動の対象を計算し、
// 実際のコマンドの対象として当てはめる。
#define ECOMMANDTARGET_NONE				0	// 対象なし（もしくは場全体）
#define ECOMMANDTARGET_DOLL_RANDOM		1	// 人形一体をランダムに
#define ECOMMANDTARGET_DOLL_ALL			2	// 人形全体
#define ECOMMANDTARGET_ENEMY_RANDOM		3	// 敵一体をランダムに
#define ECOMMANDTARGET_ENEMY_ALL		4	// 敵全体
#define ECOMMANDTARGET_SELF				5	// 自分
#define ECOMMANDTARGET_DOLL_HP_MIN		6	// HPの最も少ない人形一体
#define ECOMMANDTARGET_DOLL_HP_MIN2		7	// 最大HPに対するHPの比が最も少ない人形一体
#define ECOMMANDTARGET_ENEMY_HP_MIN		8	// HPの最も少ない敵一体
#define ECOMMANDTARGET_ENEMY_HP_MIN2	9	// 最大HPに対するHPの比が最も少ない敵一体
#define ECOMMANDTARGET_ENEMY_OTHER		10	// 自分以外の味方一体

//==============================================
// 行動パターンを取りうるか取らないかの条件。
// 条件に合う行動を、priorityに従って選択する。

// 常時行う。
// 漏れを防ぐため、必ずこの条件を持つ行動を1つ以上持っているべき。
#define CONDITIONTYPE_ALWAYS			0 
// 行動を行うHPの最大値を規定する。
// param[0] : HPが(x)%以上の時は行わない。
#define CONDITIONTYPE_MAX_HP_RATE		1
// 行動を行うHPの最大値を規定する。
// param[0] : HPが(x)%以下の時は行わない。
#define CONDITIONTYPE_MIN_HP_RATE		2
// ターンによる。
// [0][1] : 戦闘が始まってからのターン数を[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC			3
// ターンによるその2。
// [0][1] : 敵毎に異なるターン数selfTurnを[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC2			4
// HPが一定範囲の場合。
// [0] : HPが[0]%以下である場合であり、さらに
// [1] : HPが[1]%以上である場合は行動する。
#define CONDITIONTYPE_HP_RATE_RANGE		5
// 味方の誰かがHPが一定割合以下である時に行う。(Pはパーティの略)
// param[0] : HPが(x)%以上の時は行わない。
#define CONDITIONTYPE_MAX_HP_RATE_P		6
// 自分が特定の属性である時に使う。
// スキルなどで属性が変化している時に。
// param[0] : 無：0, 太陽：1, 月：2, 星：3。
#define CONDITIONTYPE_ATTR				7
// actionCountの数値による(二回行動などのため)。
// [0][1] : actionCountの値を[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC3			8

// [0][1] : selfTurnとactionCountの和を[0]で割った時の値が[1]であれば行う。
#define CONDITIONTYPE_PERIODIC4			9

//==========================================
// ユニットに対して適用するアクションに関する定数。
// ここでのアクションは演算の結果既に確定したものであり、
// かばうなどの行動は適用されない。
#define ACTIONTYPE_DAMAGE		0	// ダメージ。
#define ACTIONTYPE_HEAL			1	// 回復。
#define ACTIONTYPE_STATE		10	// ステート付加。パラメータは使用しない。
#define ACTIONTYPE_STATE_ATTR	11	// 属性関係のステート付加。
									// パラメータの1000の位がステートのターン数。
									// 1000の位以下が付加するステートのID。
#define ACTIONTYPE_ATTR			3	// 属性の永続的変更。
									// ステートによる一時的な変更とは異なる。
									// 基本的には味方には適用されない。
#define ACTIONTYPE_NO_MP		99	// MPが足りない。


//=========================================
// ダメージ計算のタイプ
#define	CALCDAMAGE_ATTACK			0
#define	CALCDAMAGE_TECH				1		// 技巧 - 相手の防御
#define	CALCDAMAGE_TECH_TECH		2		// 技巧×2 - 相手の技巧 - 相手の防御
#define	CALCDAMAGE_TECH_NOGUARD		3		// 技巧(防御無視)
#define	CALCDAMAGE_TECH_NOATTR		4		// 技巧-防御(属性無視)
#define	CALCDAMAGE_MAGIC_MAGIC		5		// 魔力×2 - 相手の魔力 - 相手の防御
#define	CALCDAMAGE_ATTACK_DOUBLE	6		// 攻撃力×2 - 相手の(技巧か魔力の高いほう) - 相手の防御

//=========================================
// 回復量計算のタイプ
#define CALCHEAL_UNDIFINED			0
#define	CALCHEAL_HEAL1				1		// 回復の術式1
#define	CALCHEAL_MAGIC				2		// 魔力値と同じ値
#define	CALCHEAL_MAGIC_DOUBLE		3		// 魔力の2倍

//=========================================
// 戦闘の結果
#define BATTLERESULT_NONE			0	// まだ勝敗が決していない
#define BATTLERESULT_VICTORY		1	// 勝った
#define BATTLERESULT_LOSE			2	// 全滅した
#define BATTLERESULT_ESCAPE			3	// 逃げた




#endif // STATIC_BATTLE