#ifndef FUNC_ALICEFILE_H
#define FUNC_ALICEFILE_H

#include <Windows.h>

// セーブ可能な最大数
#define MAX_SAVEFILE		32
// セーブファイル名を保持する文字列の長さ
#define SIZE_SAVEFILENAME	64

// 各セーブコンテンツを収納するためのインデックス値
#define SAVEFILE_INDEX_FILEHEADER		0
#define SAVEFILE_INDEX_ALICEINFO		1
#define SAVEFILE_INDEX_DOLLLIST			2


// 各セーブコンテンツを暗号化するための文字列
#define SAVEFILE_CODE_FILEHEADER		"7zgC6Hd"
#define SAVEFILE_CODE_ALICEINFO			"7zgD63a"
#define SAVEFILE_CODE_DOLLLIST			"9zgD6Hd"


// ポインタを扱うためのクラス宣言
class Game_FileHeader;

// インデックスを指定するとファイル名を返す。
// str : ファイル名を格納するTCHARの配列
// strLength : 確保した文字列のサイズ
// index : インデックス
// 戻り値 : インデックスが不正の場合はfalseを返す
bool GetSaveGameFileName(LPTSTR str, int strLength, BYTE index);

// ファイルが存在するか否かを返す。
// 戻り値 : 存在する場合はtrue
bool GetGameFileIsExist(BYTE index);

// ファイルのヘッダ情報を格納する。
// pHeader : 情報を格納するGame_FileHeaderクラスへのポインタ
// index : ファイルのインデックス
bool GetGameFileHeader(Game_FileHeader* pHeader, BYTE index);

// 現在の内容をインデックスを指定して保存する。
// 上書きなどの確認は行わない。
// 戻り値：成功した場合はtrue
bool SaveGame(BYTE index);

// 現在の内容をインデックスを指定して各グローバル変数に読み込む。
// 戻り値：成功した場合はtrue
bool LoadGame(BYTE index);

// 各グローバル変数を全てリセットする。
bool NewGame();

// 初期状態の人形をリストに加える。
void GenerateInitialDoll();



#endif // FUNC_ALICEFILE_H