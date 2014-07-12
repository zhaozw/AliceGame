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
#define MAX_UNITCOMMAND			(NUM_BATTLEDOLL_FRONT + MAX_BATTLEENEMY)


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
#define COMMANDPHAZE_PRE_ACTION		1	// 行動前に行う判定。
#define COMMANDPHAZE_ACTION			2	// 行動時に行う判定。
#define COMMANDPHAZE_POST_ACTION	3	// 行動後に行う判定。

#define COMMANDPHAZE_ERROR			-1	// エラー
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_PRE_ACTION)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)


#endif // STATIC_BATTLE