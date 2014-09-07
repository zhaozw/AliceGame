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
#define SAVEFILE_INDEX_CHOOSEMAP		2
#define SAVEFILE_INDEX_DOLLLIST			3


// 各セーブコンテンツを暗号化するための文字列
#define SAVEFILE_CODE_FILEHEADER		"7zgC6Hd"
#define SAVEFILE_CODE_ALICEINFO			"7zgD63a"
#define SAVEFILE_CODE_CHOOSEMAP			"bvgD53d"
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

// 2014年度夏コミのバージョンにおけるデータを保持するクラス。
// グローバル変数g_aliceFile140816から参照される。

#define ALICEFILE_140816_TUTORIAL			10
#define ALICEFILE_140816_FILENAME			"savedata\\Trial_ver140806.dat"
#define ALICEFILE_140816_XORCODE			"aZkw7QQn"
#define ALICEFILE_140816_XORCODE_LENGTH		8
#define ALICEFILE_140816_XORCODE2			"3kkNniHnkkN"
#define ALICEFILE_140816_XORCODE2_LENGTH	11

typedef struct AliceFile_140816_Data{
	bool	firstHint;				// 最初のヒントメッセージ。
								// 見ていればtrueで、次回以降は自動での表示を行わない。
	BYTE	tutorialBattle[ALICEFILE_140816_TUTORIAL];	
								// チュートリアルバトルをクリアしたか否か。
								// 未挑戦なら0(説明表示)、
								// 未クリアなら1(説明は表示しない)、
								// クリアしていれば2。
								// クリアしていればtrue。
	bool	tutorialHint;		// チュートリアルのヒントの表示。
								// trueなら毎回見る。falseなら初回のみ見る。
	int		forFuture[10];		// 将来的に使用できるデータ領域。
								// 使用されていない時はすべて0である。
}ALICEFILE_140816_DATA;

class AliceFile_140816{
public:
	// データ
	ALICEFILE_140816_DATA	data;
public:
	// コンストラクタ
	AliceFile_140816();

	// 内容を保存する。
	bool Save();

	// 内容を読み込む。
	bool Load();

	// 内容のリセット
	void Reset();
};


#endif // FUNC_ALICEFILE_H