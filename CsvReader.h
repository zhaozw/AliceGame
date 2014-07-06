// CsvReader.h

#ifndef CSVREADER_H
#define CSVREADER_H

#include <Windows.h>
#include <tchar.h>
#include <streambuf>

#define CSV_MAX_COLUMN		10			// 1行あたりの要素数
#define CSV_MAX_TEXT		64			// セルあたりの文字数

// Read関数の戻り値
#define CSV_READ_NOERROR	0
#define CSV_READ_GOOD		0
#define CSV_READ_END		1			// ファイルの末尾
#define CSV_READ_ERROR		2			// エラーが出た
#define CSV_READ_NODATA		3			// 空行

#define CSV_ERROR_VALUE		-1
#define CSV_ERROR_VALUE_FLOAT 0

// CSVファイルを読み込んで利用しやすい形で提供するクラス。
// 具体的には、ファイルを1行ずつ読んでいき、コンマ区切りのテキストに分解する。
// 文字列型から別の型に変更するのはGetValueを用いる。
class CsvReader{
private:
	TCHAR fileName[MAX_PATH];		// ファイルの名前
	std::streamoff filePos;	// 何度も開いたり閉じたりする関係上ファイルの位置を保持しておく
					// このクラス自身はifstreamを保持しない
	TCHAR value[CSV_MAX_COLUMN][CSV_MAX_TEXT];
	DWORD lineNum;		// 行番号
	WORD valueNum;		// 空でない文字列が入った値の数

public:
	// コンストラクタ
	CsvReader();
	CsvReader(LPTSTR fileName);

	// デストラクタ
	~CsvReader();

	// ファイルを開く
	// (実際には開かず、ファイル名をセットするだけ	
	bool Open(LPTSTR fileName);

	// ファイルの行数(空行除く)を調べる
	// エラーの場合は0を返す
	DWORD GetMaxLine();
	DWORD GetMaxLine(LPTSTR fileName){ if(!Open(fileName)) return 0; GetMaxLine(); };

	// ファイルから1行読み込み、値をセットする
	WORD Read();

	// 値をセットせずに次の行に移動する
	// v, strLenを指定した場合、strLen以内の長さで読み込んだ行の内容をコピーする。
	// その際、コンマで区切ったりせずそのまま取り込む。
	WORD NextLine(LPTSTR v=NULL, WORD strLen=0);

	// ファイルを閉じる
	// 自動でリセットを行う
	bool Close(){ Reset(); return true; };

	// 読み込みを全てリセットする
	void Reset();

	// 指定したインデックスが使用されているかどうかをチェックする
	bool Used(int i){ return (i<valueNum); };

	// 値を取得する
	void GetValue(WORD index, LPTSTR v, WORD strLen=CSV_MAX_TEXT);

	// 値を整数値として取得する
	int GetIntValue(WORD index, int errorValue=CSV_ERROR_VALUE);

	// 値を小数値として取得する
	float GetFloatValue(WORD index, float errorValue=CSV_ERROR_VALUE_FLOAT);

	// 値を文字として取得する
	TCHAR GetCharacter(WORD index, TCHAR errorValue=_T(' '), WORD charPos=0);
	
	// 値をchar型の変数として取得する
	char GetCharValue(WORD index, char errorValue=0);


	// 値をブール値として取得する(1以上ならtrue、それ以外ならfalse)
	bool GetBoolValue(WORD index){
		return (GetIntValue(index)>0); 
	};

	// ファイルの現在の位置から、
	// 特定の文字列を先頭に持つ行を検索しその行の次の行に移動する。
	// goNextLineがfalseだと文字列を先頭に持つ行そのままに移動する。
	// fromHeadを指定するとファイルの先頭から検索する。
	// 指定の行が見つからなかった場合はfalseを返す。
	// 見つからなかった場合は元の場所を維持する。
	bool Seek(LPTSTR word, WORD strlen, bool fromHead=false, bool goNextLine=true);

};

#endif // CSVREADER_H