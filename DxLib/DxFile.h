// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		ファイルアクセスプログラムヘッダファイル
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXFILE_H__
#define __DXFILE_H__

// インクルード ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxHandle.h"

namespace DxLib
{

// マクロ定義 --------------------------------------------------------------------

// ライブラリ内部で使用するファイルアクセス用関数
#define FSYNC( handle )                             {while( FIDLECHK( handle ) == FALSE ) Thread_Sleep(0);}
#define FOPEN( path )								StreamOpen( (path), FALSE, TRUE, FALSE )
#define FOPEN_CACHE( path )							StreamOpen( (path),  TRUE, TRUE, FALSE )
#define FOPEN_ASYNC( path )							StreamOpen( (path), FALSE, TRUE,  TRUE )
#define FCLOSE( handle )							StreamClose( (int)(handle) )
#define FREAD( buf, length, num, handle )			StreamRead( (void *)(buf), (size_t)(length), (size_t)(num), (int)(handle) )
#define FSEEK( handle, pos, mode )					StreamSeek( (int)(handle), (long)(pos), (int)(mode) )
#define FTELL( handle )								StreamTell( (int)(handle) )
#define FEOF( handle )								StreamEof( (int)(handle) )
#define FIDLECHK( handle )							StreamIdleCheck( (int)(handle) )
#define FSETDIR( path )								StreamChDir( (path) )
#define FGETDIR( buffer )							StreamGetDir( (buffer) )
#define FFINDFIRST( path, buffer )					StreamFindFirst( (path), (FILEINFO *)(buffer) )
#define FFINDNEXT( handle, buffer )					StreamFindNext( (int)(handle), (FILEINFO *)(buffer) )
#define FFINDCLOSE( handle )						StreamFindClose( (int)(handle) )

// ファイルアクセス専用スレッドへの指令
#define FILEACCESSTHREAD_FUNCTION_OPEN		(0)				// ファイルを開け
#define FILEACCESSTHREAD_FUNCTION_CLOSE		(1)				// ファイルを閉じろ
#define FILEACCESSTHREAD_FUNCTION_READ		(2)				// ファイルを読み込め
#define FILEACCESSTHREAD_FUNCTION_SEEK		(3)				// ファイルポインタを移動しろ
#define FILEACCESSTHREAD_FUNCTION_EXIT		(4)				// 終了しろ

#define FILEACCESSTHREAD_DEFAULT_CACHESIZE	(128 * 1024)	// デフォルトのキャッシュサイズ


// 構造体定義 --------------------------------------------------------------------

// ファイルアクセスハンドル
struct FILEACCESSINFO
{
	HANDLEINFO				HandleInfo ;						// ハンドル共通データ
	DWORD_PTR				FilePointer ;						// ファイルポインタ
} ;

// 内部大域変数宣言 --------------------------------------------------------------

// デフォルトストリームファンクション
extern STREAMDATASHREDTYPE2 StreamFunction ;

// 関数プロトタイプ宣言-----------------------------------------------------------

// ファイルアクセス処理の初期化・終了関数
extern	int			InitializeFile( void ) ;														// ファイルアクセス処理の初期化
extern	int			TerminateFile( void ) ;															// ファイルアクセス処理の後始末



// ファイルアクセス関数
extern	DWORD_PTR	ReadOnlyFileAccessOpen( const TCHAR *Path, int UseCacheFlag, int BlockReadFlag, int UseASyncReadFlag  ) ;
extern	int			ReadOnlyFileAccessClose( DWORD_PTR Handle ) ;
extern	long		ReadOnlyFileAccessTell( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessSeek( DWORD_PTR Handle, long SeekPoint, int SeekType ) ;
extern	size_t		ReadOnlyFileAccessRead( void *Buffer, size_t BlockSize, size_t DataNum, DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessEof( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessIdleCheck( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessChDir( const TCHAR *Path ) ;
extern	int			ReadOnlyFileAccessGetDir( TCHAR *Buffer ) ;
extern	DWORD_PTR	ReadOnlyFileAccessFindFirst( const TCHAR *FilePath, FILEINFO *Buffer ) ;				// 戻り値: -1=エラー  -1以外=FindHandle
extern	int			ReadOnlyFileAccessFindNext( DWORD_PTR FindHandle, FILEINFO *Buffer ) ;					// 戻り値: -1=エラー  0=成功
extern	int			ReadOnlyFileAccessFindClose( DWORD_PTR FindHandle ) ;									// 戻り値: -1=エラー  0=成功

// ストリームデータアクセス関数
extern	DWORD_PTR	StreamOpen( const TCHAR *Path, int UseCacheFlag, int BlockFlag, int UseASyncReadFlag ) ;
extern	int			StreamClose( DWORD_PTR Handle ) ;
extern	long		StreamTell( DWORD_PTR Handle ) ;
extern	int			StreamSeek( DWORD_PTR Handle, int SeekPoint, int SeekType ) ;
extern	size_t		StreamRead( void *Buffer, size_t BlockSize, size_t DataNum, DWORD_PTR Handle ) ;
extern	int			StreamEof( DWORD_PTR Handle ) ;
extern	int			StreamIdleCheck( DWORD_PTR Handle ) ;
extern	int			StreamChDir( const TCHAR *Path ) ;
extern	int			StreamGetDir( TCHAR *Buffer ) ;
extern	DWORD_PTR	StreamFindFirst( const TCHAR *FilePath, FILEINFO *Buffer ) ;				// 戻り値: -1=エラー  -1以外=FindHandle
extern	int			StreamFindNext( DWORD_PTR FindHandle, FILEINFO *Buffer ) ;					// 戻り値: -1=エラー  0=成功
extern	int			StreamFindClose( DWORD_PTR FindHandle ) ;									// 戻り値: -1=エラー  0=成功
extern	const STREAMDATASHREDTYPE2 *StreamGetStruct( void ) ;

// ストリームデータアクセス用関数構造体関係
extern	STREAMDATASHRED *GetFileStreamDataShredStruct( void ) ;								// ストリームデータ読みこみ制御用関数ポインタ構造体のファイル用構造体を得る
extern	STREAMDATASHRED *GetMemStreamDataShredStruct( void ) ;								// ストリームデータ読みこみ制御用関数ポインタ構造体のﾒﾓﾘ用構造体を得る




// ファイルハンドル関数
extern	int			FileRead_open_UseGParam( const TCHAR *FilePath, int ASync, int ASyncLoadFlag = FALSE ) ;				// ファイルを開く
extern	int			FileRead_seek_UseGParam( int FileHandle, int Offset, int Origin, int ASyncLoadFlag = FALSE ) ;			// ファイルポインタの位置を変更する
extern	int			FileRead_read_UseGParam( int FileHandle, void *Buffer, int ReadSize, int ASyncLoadFlag = FALSE ) ;		// ファイルからデータを読み込む



// メモリに置かれたデータをファイルのデータに例えてつかうための関数
extern	void*		MemStreamOpen( void *DataBuffer, unsigned int DataSize ) ;
extern	int			MemStreamClose( void *StreamDataPoint ) ;



// ファイルパス関係

// フルパスではないパス文字列をフルパスに変換する
// ( CurrentDir はフルパスである必要がある(語尾に『\』があっても無くても良い) )
// ( CurrentDir が NULL の場合は現在のカレントディレクトリを使用する )
extern int			ConvertFullPath_( const char *Src, char *Dest, const char *CurrentDir = NULL ) ; 
extern int			ConvertFullPathW_( const wchar_t *Src, wchar_t *Dest, const wchar_t *CurrentDir = NULL ) ; 
extern int			ConvertFullPathT_( const TCHAR *Src, TCHAR *Dest, const TCHAR *CurrentDir = NULL ) ; 

// 指定のファイルパスを指定のフォルダパスから相対アクセスするための相対パスを作成する
// ( FilePath や StartFolderPath がフルパスではなかった場合は関数内でフルパス化されます )
// StartFolderPath の末端に / or \ があっても問題ありません
extern int			CreateRelativePath_( const char *FilePath, const char *StartFolderPath, char *Dest ) ;
extern int			CreateRelativePathW_( const wchar_t *FilePath, const wchar_t *StartFolderPath, wchar_t *Dest ) ;

// 特定のパス文字列から色々な情報を取得する
// ( CurrentDir はフルパスである必要がある(語尾に『\』があっても無くても良い) )
// ( CurrentDir が 0 の場合は実際のカレントディレクトリを使用する )
extern int			AnalyseFilePath_( const char *Src, // DirPath の終端には \ は付かない
										char *FullPath, char *DirPath, char *FileName, char *Name, char *ExeName, const char *CurrentDir = 0 );

// ファイル名も一緒になっていると分かっているパス中からファイル名とディレクトリパスを分割する
// フルパスである必要は無い、ファイル名だけでも良い
// DirPath の終端に ￥ マークは付かない
extern int			AnalysisFileNameAndDirPath_( const char *Src, char *FileName = 0, char *DirPath = 0 ) ;
extern int			AnalysisFileNameAndDirPathW_( const wchar_t *Src, wchar_t *FileName = 0, wchar_t *DirPath = 0 ) ;

// ファイルパスからファイル名と拡張子を取得する
extern int			AnalysisFileNameAndExeName_( const char *Src, char *Name = 0, char *ExeName = 0 ) ;
extern int			AnalysisFileNameAndExeNameW_( const wchar_t *Src, wchar_t *Name = 0, wchar_t *ExeName = 0 ) ;

// ファイルパスの拡張子を変えた文字列を得る
extern int			GetChangeExeNamePath_( const char *Src, char *Dest, const char *ExeName ) ;

extern void			SetEnMark_( char *PathBuf ) ;			// 語尾に『\』がついていない場合は付ける

// 渡された文字列をフルパス文字列として扱い、ドライブ名( :\ or :/ の前まで )
// 又はネットワークフォルダ名( \ or / の前まで )を取得する
// ネットワークフォルダだった場合は最初の \\ も含める
// 戻り値は取得した文字列の長さ( ネットワークフォルダの場合は \\ も文字列量に含まれます )
// Src はフルパスである必要があります、相対パスでは正常に動作しません
extern int			AnalysisDriveName_( const char *Src, char *Dest ) ;
extern int			AnalysisDriveNameW_( const wchar_t *Src, wchar_t *Dest ) ;

// 渡された文字列をフォルダパス文字列として扱い、フォルダ名( \ or / の前まで )を取得します
// 渡す文字列がフルパスで、最初にドライブ名が書かれていたら正常な結果が得られません
// ../ 等の下位フォルダに降りる文字列があった場合は .. 等が出力されます
// 戻り値は取得した文字列の長さです
extern int			AnalysisDirectoryName_( const char *Src, char *Dest ) ;
extern int			AnalysisDirectoryNameW_( const wchar_t *Src, wchar_t *Dest ) ;


}

#endif // __DXFILE_H__

