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
// アリスのコマンド群

#define ALICE_COMMAND_BATTLE		0	// 戦う
#define ALICE_COMMAND_UNITCHANGE	1	// ユニット交換
#define ALICE_COMMAND_SPECIAL		2	// 特技
#define ALICE_COMMAND_ESCAPE		3	// 逃げる

//=========================================
// commandPhazeの配列

#define COMMANDPHAZE_NOPHAZE		0	// 戦闘行動以外で使用する。
										// actionPhazeを使用しない場合の値
#define COMMANDPHAZE_FIX_COMMAND	1	// 何より先に、正しく行動できるかを判定する
#define COMMANDPHAZE_FIX_TARGET		2	// 行動の宣言より前に、ターゲットの確定を行う
#define COMMANDPHAZE_ASSERT			3	// 行動宣言時に行う判定。
#define COMMANDPHAZE_PRE_ACTION		4	// 行動前に行う判定。
#define COMMANDPHAZE_ACTION			5	// 行動時に行う判定。
#define COMMANDPHAZE_CHECK_DEATH	6	// 行動後にはとりあえず死亡判定。
#define COMMANDPHAZE_POST_ACTION	7	// 行動後に行う判定。
#define COMMANDPHAZE_START_TURN		8	// ターンの最初に行う判定。

#define COMMANDPHAZE_ERROR			-1	// エラー
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_FIX_COMMAND)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)

//=========================================
// 
#define DAMAGE_MAX			9999

//=========================================
// 属性攻撃の倍率

#define ATTRAFFINITY_EVEN	0	// ふつう
#define ATTRAFFINITY_STRONG	1	// 強い
#define ATTRAFFINITY_WEAK	2	// 弱い

#define ATTRRATE_STRONG		2.0
#define ATTRRATE_WEAK		0.5

//=========================================
// ダメージ計算のタイプ

#define	CALCDAMAGE_ATTACK			0

//=========================================
// 戦闘の結果

#define BATTLERESULT_NONE			0	// まだ勝敗が決していない
#define BATTLERESULT_VICTORY		1	// 勝った
#define BATTLERESULT_LOSE			2	// 全滅した


#endif // STATIC_BATTLE