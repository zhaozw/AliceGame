// MyFiles.h

#ifndef MYFILES_H
#define MYFILES_H

#include <Windows.h>
#include <tchar.h>

// 連結する最大のファイル数
#define MAX_FILES					32
#define MAX_FILEPATH				64 // 部分ファイルのファイル名

// ファイルのプロパティに関するフラグ
#define MYFILE_FLAG_USED 0x01			// MyFileInfoが使用されているか
#define MYFILE_FLAG_COPYED 0x02			// 独自でメモリを確保したものではなく、
										// あるオブジェクトのポインタをコピーしている
#define MYFILE_FLAG_PROTECTED 0x04		// 参照できない内容をポインタが指している
										// (通常立ってはいけないフラグ)

// その他
#define INDEX_ERROR (0xff)			// インデックスを取得する関数がエラーの場合に返す値
#define INDEX_ANY (0xfe)			// インデックスを特に制限しない場合

// ファイルヘッダを記述する構造体
// ロード後の情報保持も行う。
typedef struct MyFileInfo{
	TCHAR name[MAX_FILEPATH];			// ファイル名
	DWORD size; 						// ファイルサイズ
	void* pointer;						// ポインタ位置
	WORD flags;						// 使用されているか
	// コンストラクタ
	MyFileInfo(){
		for(int i=0; i<MAX_FILEPATH; i++){
			name[i] = _T('\0');
		}
		size = 0;
		pointer = NULL;
		flags = 0x00;
	};
}MYFILEINFO, *LPMYFILEINFO;


// 独自形式でファイルを読み込んだり扱ったりする。
// 最も基本的なファイル形式は、最初にファイルの数、次にファイルのサイズの列挙、
// そしてファイルの中身が連結されているだけというもの。
//
// DWORD 
class MyFiles{
private:
	// メンバ群
	bool fNeedToRelease;	// プログラム終了時にメモリを解放する必要がある
	// ファイルサイズ
	WORD fileNum;						// 有効な部分ファイルの数
	MyFileInfo fileInfo[MAX_FILES];		// 部分ファイルそれぞれの情報
										// (データを指すポインタもここに含まれる)
public:
	// コンストラクタ
	MyFiles();
	// デストラクタ
	~MyFiles();

	// 単純関数系

	// インデックスが参照可能なものかどうかを返す
	bool IndexEnabled(WORD index){ return(index>=0 && index<MAX_FILES); };

	// 使用されていない中で最も若いファイルのインデックスを返す
	// INDEX_ERRORならインデックスが存在しない
	WORD GetEmptyIndex();

	// 指定したファイルのインデックスが使用可能かを返す
	bool CheckIndexIsEmpty(WORD index);
	bool CheckIndexIsUsed(WORD index){ return !CheckIndexIsEmpty(index); };

	// 指定した名前のファイルを持つインデックスを返す。
	WORD GetNamedIndex(LPTSTR fileName, WORD fileNameLength=0);

	// 純粋なデータへのアクセサ
	LPVOID GetFilePointerByIndex(WORD index);
	LPVOID GetFilePointerByName(LPTSTR fileName, WORD fileNameLength=0){
		return GetFilePointerByIndex(GetNamedIndex(fileName, fileNameLength));
	};

	// ファイル名をセットする
	// 変な文字で埋められないように初期化を行う
	void SetFileName(int index, LPTSTR fileName);

	// フラグをセットする
	void ResetFileFlags(int index){ fileInfo[index].flags = 0x00; };
	void SetFileFlags(int index, WORD flag);

	// メモリ領域を確保し、pointerに割り当てる
	bool InitializePointer(int index, DWORD size);

	// 複雑関数系
	// テキストファイルに記述されたファイル群をMyFilesに読み込む
	// 追加読み込みは不可能（追加で読み込もうとした場合は前のファイル群を解放する）
	// fileName : ファイル名
	bool LoadFilesFromTxt(LPTSTR fileName);

	// 独自形式で保存されたファイル群をMyFilesに読み込む
	// 追加読み込みとしてこの関数を使用することは不可能
	// fileName : ファイル名
	bool LoadFilesFromDat(LPTSTR fileName);

	// ファイル名を指定してMyFilesに追加する
	// fileName : ファイル名
	// 戻り値 : 追加されたファイル位置。INDEX_ERRORはエラー
	// 
	WORD AddFileToFiles(LPTSTR fileName, LPTSTR newName,
		WORD index=INDEX_ANY, bool useNewName=true);

	// ファイル名を指定し、一部を抜きだしてMyFilesに追加する
	// fileName : ファイル名
	// offset : オフセット
	// length : 抜きだす長さ
	// 戻り値 : 追加されたファイル位置。INDEX_ERRORはエラー
	// 
	WORD AddFilePartToFiles(LPTSTR fileName, LPTSTR newName,
		DWORD offset, DWORD length, WORD index=INDEX_ANY, bool useNewName=true);

	// オブジェクトを指すアドレスを元にデータをMyFilesに追加する。
	// オブジェクトのサイズもちゃんと指定しなければならない。
	// ポインタの指すオブジェクトがアクセスできないものの場合はエラー。
	// 戻り値 : 追加されたファイル位置。INDEX_ERRORはエラー
	// データをコピーするのではなくオブジェクトの位置を指すだけなので、
	// オブジェクトの開放は別途行う必要がある。
	WORD AddObjectToFiles(LPVOID pointer, DWORD size, 
		LPTSTR objName, int index=INDEX_ANY);

	// 何らかの方法で作成したバイト列をMyFilesに追加する。
	// バイト列のサイズも指定しなければならない。
	// needToReleaseがtrueの時、MyFilesクラスによって解放される。
	// 非常に二重開放を起こしやすい部分であるので、注意。
	// 戻り値 : 追加されたファイル位置。INDEX_ERRORはエラー
	WORD AddBytesToFiles(void* pointer, DWORD size, 
		LPTSTR objName, bool needToRelease, int index=INDEX_ANY);

	// MyFilesの中身を暗号化されていない形式でバイナリファイルに書き出す
	// fileName :		ファイル名
	// hideName :		書き出し時にファイル名を隠すかどうか
	//					(単純に、ファイル名に相当するところにダミーの文字列を入れる)
	// sizeInBytes :	書き出したファイルのサイズを格納するポインタ。
	bool SaveFilesToRawFile(LPTSTR fileName, bool hideName, DWORD* sizeInBytes);

	// MyFilesの中身のうち指定されたインデックスのファイルをバイナリファイルとして書き出す
	// index : インデックス
	// outName : 書き出し時の名前
	// useRawName : trueならoutNameを無視してMyFilesの名前でファイルを書き出す
	bool SaveFileToRawFileByIndex(int index, LPTSTR outName, bool useRawName=true);

	// MyFilesの中身のうち指定された名前のファイルをバイナリファイルとして書き出す
	// searchName : 名前
	// outName : 書き出し時の名前
	// useRawName : trueならoutNameを無視してMyFilesの名前でファイルを書き出す
	bool SaveFileToRawFileByName(LPTSTR searchName, LPTSTR outName, bool useRawName=true);

	// MyFilesの中身を（メモリ上で）暗号化・複合化する（関数名はEncodeだが復号も出来る）
	// ファイルデータをそのまま排他的論理和で暗号化する
	// index : 暗号化する中身
	// code : 暗号化コード
	// codeLength : 暗号化コードの長さ
	bool EncodeFileXOR(WORD index, LPTSTR code, WORD cordLength);

	// ファイルの中身が一致するかどうか比較する。
	// アップデータなどを作成する際に。
	bool CompareFiles(WORD index, WORD index2);

	// ファイルのサイズを取得する。
	DWORD GetFileSize(WORD index){
		if(!IndexEnabled(index)) return 0;
		return fileInfo[index].size;
	}

	// 明示的にメモリを解放する(正常時)
	bool Release(int index);
	bool ReleaseAll();

	// 明示的にメモリを解放する(強制)
	// checkUsed : 使用されているかどうかのフラグを信用するか
	bool ForceRelease(int index, bool checkUsed=false);
	bool ForceReleaseAll(bool checkUsed=false);

};


#endif