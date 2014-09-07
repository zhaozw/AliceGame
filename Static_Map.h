#ifndef STATIC_MAP_H
#define STATIC_MAP_H

//======================================
// 全体マップに関する定数。
// CHOOSEMAPはWorldMapの略。

// エリア数とパス数の最大値。
#define CHOOSEMAP_AREA_MAX			16		// エリア数
#define CHOOSEMAP_POINT_MAX			24		// ポイント数（必ずしもポイントとエリアは一致しない）
#define CHOOSEMAP_PATH_MAX			32		// パス数
#define CHOOSEMAP_SPOT_MAX			8		// 特殊な施設数
#define CHOOSEMAP_STAGE_MAX			8		// 各エリアの最大ステージ数。

// パスの状態に関する定数
#define CHOOSEMAP_PATHSTATE_NONE	0		// 道が解放されていない
#define CHOOSEMAP_PATHSTATE_OPENED	1		// 道が解放された
#define CHOOSEMAP_PATHSTATE_CLOSED	2		// 何らかの理由で一時的に閉ざされている
#define CHOOSEMAP_PATHSTATE_HIDDEN	3		// 何らかの理由で一時的に閉ざされた上、見えない

// マップ上で用いる方向の定数。
// 北から時計回り。
#define MAP_NODIRECTION				0
#define MAP_NORTH					1
#define MAP_EAST					2
#define MAP_SOUTH					3
#define MAP_WEST					4

//======================================
// マップをグリッドによって指定する。

#define MAPGRID_INI_X			100
#define MAPGRID_DLT_X			120
#define MAPGRID_MAX_X			5		// 横最大数
#define MAPGRID_INI_Y			80
#define MAPGRID_DLT_Y			100
#define MAPGRID_MAX_Y			4		// 縦最大数


//======================================
// 各ポイントの属性。

#define MAPPOINT_TYPE_NONE		0		// 属性なし。通常使用されない。
#define MAPPOINT_TYPE_ENTRY		1		// スタート地点。
#define MAPPOINT_TYPE_BATTLE	2		// 戦闘ポイント。
#define MAPPOINT_TYPE_ITEM		3		// アイテム取得ポイント。
#define MAPPOINT_TYPE_BOSS		4		// ボスポイント。このポイントでの戦闘に勝利するとクリア。
#define MAPPOINT_TYPE_TERMINAL	5		// ボスではないがマップの出口であるポイント。
#define MAPPOINT_TYPE_PATH		6		// 道の誘導に使用する、擬似的なポイント。

//======================================
// 各ポイントの解放状態。

#define MAPPOINT_STATE_NONE			0		// 状態なし。スタート地点と道ポイントに使用する。
#define MAPPOINT_STATE_HIDDEN		1		// ポイントが隠れた状態。何も表示しない。
#define MAPPOINT_STATE_UNKNOWN		2		// ポイントが現れているが、属性が分からない状態。
#define MAPPOINT_STATE_UNTRACKED	3		// ポイントの素性は分かっているが、訪れていない。
											// クリア済みのマップはこの状態になる。
#define MAPPOINT_STATE_TRACKED		4		// 通過済みのポイント。


#endif // STATIC_MAP_H