#ifndef STATIC_BATTLE
#define STATIC_BATTLE

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


#endif // STATIC_BATTLE