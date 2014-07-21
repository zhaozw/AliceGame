// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�t�@�C���A�N�Z�X�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXFILE_H__
#define __DXFILE_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxHandle.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// ���C�u���������Ŏg�p����t�@�C���A�N�Z�X�p�֐�
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

// �t�@�C���A�N�Z�X��p�X���b�h�ւ̎w��
#define FILEACCESSTHREAD_FUNCTION_OPEN		(0)				// �t�@�C�����J��
#define FILEACCESSTHREAD_FUNCTION_CLOSE		(1)				// �t�@�C�������
#define FILEACCESSTHREAD_FUNCTION_READ		(2)				// �t�@�C����ǂݍ���
#define FILEACCESSTHREAD_FUNCTION_SEEK		(3)				// �t�@�C���|�C���^���ړ�����
#define FILEACCESSTHREAD_FUNCTION_EXIT		(4)				// �I������

#define FILEACCESSTHREAD_DEFAULT_CACHESIZE	(128 * 1024)	// �f�t�H���g�̃L���b�V���T�C�Y


// �\���̒�` --------------------------------------------------------------------

// �t�@�C���A�N�Z�X�n���h��
struct FILEACCESSINFO
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^
	DWORD_PTR				FilePointer ;						// �t�@�C���|�C���^
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �f�t�H���g�X�g���[���t�@���N�V����
extern STREAMDATASHREDTYPE2 StreamFunction ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �t�@�C���A�N�Z�X�����̏������E�I���֐�
extern	int			InitializeFile( void ) ;														// �t�@�C���A�N�Z�X�����̏�����
extern	int			TerminateFile( void ) ;															// �t�@�C���A�N�Z�X�����̌�n��



// �t�@�C���A�N�Z�X�֐�
extern	DWORD_PTR	ReadOnlyFileAccessOpen( const TCHAR *Path, int UseCacheFlag, int BlockReadFlag, int UseASyncReadFlag  ) ;
extern	int			ReadOnlyFileAccessClose( DWORD_PTR Handle ) ;
extern	long		ReadOnlyFileAccessTell( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessSeek( DWORD_PTR Handle, long SeekPoint, int SeekType ) ;
extern	size_t		ReadOnlyFileAccessRead( void *Buffer, size_t BlockSize, size_t DataNum, DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessEof( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessIdleCheck( DWORD_PTR Handle ) ;
extern	int			ReadOnlyFileAccessChDir( const TCHAR *Path ) ;
extern	int			ReadOnlyFileAccessGetDir( TCHAR *Buffer ) ;
extern	DWORD_PTR	ReadOnlyFileAccessFindFirst( const TCHAR *FilePath, FILEINFO *Buffer ) ;				// �߂�l: -1=�G���[  -1�ȊO=FindHandle
extern	int			ReadOnlyFileAccessFindNext( DWORD_PTR FindHandle, FILEINFO *Buffer ) ;					// �߂�l: -1=�G���[  0=����
extern	int			ReadOnlyFileAccessFindClose( DWORD_PTR FindHandle ) ;									// �߂�l: -1=�G���[  0=����

// �X�g���[���f�[�^�A�N�Z�X�֐�
extern	DWORD_PTR	StreamOpen( const TCHAR *Path, int UseCacheFlag, int BlockFlag, int UseASyncReadFlag ) ;
extern	int			StreamClose( DWORD_PTR Handle ) ;
extern	long		StreamTell( DWORD_PTR Handle ) ;
extern	int			StreamSeek( DWORD_PTR Handle, int SeekPoint, int SeekType ) ;
extern	size_t		StreamRead( void *Buffer, size_t BlockSize, size_t DataNum, DWORD_PTR Handle ) ;
extern	int			StreamEof( DWORD_PTR Handle ) ;
extern	int			StreamIdleCheck( DWORD_PTR Handle ) ;
extern	int			StreamChDir( const TCHAR *Path ) ;
extern	int			StreamGetDir( TCHAR *Buffer ) ;
extern	DWORD_PTR	StreamFindFirst( const TCHAR *FilePath, FILEINFO *Buffer ) ;				// �߂�l: -1=�G���[  -1�ȊO=FindHandle
extern	int			StreamFindNext( DWORD_PTR FindHandle, FILEINFO *Buffer ) ;					// �߂�l: -1=�G���[  0=����
extern	int			StreamFindClose( DWORD_PTR FindHandle ) ;									// �߂�l: -1=�G���[  0=����
extern	const STREAMDATASHREDTYPE2 *StreamGetStruct( void ) ;

// �X�g���[���f�[�^�A�N�Z�X�p�֐��\���̊֌W
extern	STREAMDATASHRED *GetFileStreamDataShredStruct( void ) ;								// �X�g���[���f�[�^�ǂ݂��ݐ���p�֐��|�C���^�\���̂̃t�@�C���p�\���̂𓾂�
extern	STREAMDATASHRED *GetMemStreamDataShredStruct( void ) ;								// �X�g���[���f�[�^�ǂ݂��ݐ���p�֐��|�C���^�\���̂���ؗp�\���̂𓾂�




// �t�@�C���n���h���֐�
extern	int			FileRead_open_UseGParam( const TCHAR *FilePath, int ASync, int ASyncLoadFlag = FALSE ) ;				// �t�@�C�����J��
extern	int			FileRead_seek_UseGParam( int FileHandle, int Offset, int Origin, int ASyncLoadFlag = FALSE ) ;			// �t�@�C���|�C���^�̈ʒu��ύX����
extern	int			FileRead_read_UseGParam( int FileHandle, void *Buffer, int ReadSize, int ASyncLoadFlag = FALSE ) ;		// �t�@�C������f�[�^��ǂݍ���



// �������ɒu���ꂽ�f�[�^���t�@�C���̃f�[�^�ɗႦ�Ă������߂̊֐�
extern	void*		MemStreamOpen( void *DataBuffer, unsigned int DataSize ) ;
extern	int			MemStreamClose( void *StreamDataPoint ) ;



// �t�@�C���p�X�֌W

// �t���p�X�ł͂Ȃ��p�X��������t���p�X�ɕϊ�����
// ( CurrentDir �̓t���p�X�ł���K�v������(����Ɂw\�x�������Ă������Ă��ǂ�) )
// ( CurrentDir �� NULL �̏ꍇ�͌��݂̃J�����g�f�B���N�g�����g�p���� )
extern int			ConvertFullPath_( const char *Src, char *Dest, const char *CurrentDir = NULL ) ; 
extern int			ConvertFullPathW_( const wchar_t *Src, wchar_t *Dest, const wchar_t *CurrentDir = NULL ) ; 
extern int			ConvertFullPathT_( const TCHAR *Src, TCHAR *Dest, const TCHAR *CurrentDir = NULL ) ; 

// �w��̃t�@�C���p�X���w��̃t�H���_�p�X���瑊�΃A�N�Z�X���邽�߂̑��΃p�X���쐬����
// ( FilePath �� StartFolderPath ���t���p�X�ł͂Ȃ������ꍇ�͊֐����Ńt���p�X������܂� )
// StartFolderPath �̖��[�� / or \ �������Ă���肠��܂���
extern int			CreateRelativePath_( const char *FilePath, const char *StartFolderPath, char *Dest ) ;
extern int			CreateRelativePathW_( const wchar_t *FilePath, const wchar_t *StartFolderPath, wchar_t *Dest ) ;

// ����̃p�X�����񂩂�F�X�ȏ����擾����
// ( CurrentDir �̓t���p�X�ł���K�v������(����Ɂw\�x�������Ă������Ă��ǂ�) )
// ( CurrentDir �� 0 �̏ꍇ�͎��ۂ̃J�����g�f�B���N�g�����g�p���� )
extern int			AnalyseFilePath_( const char *Src, // DirPath �̏I�[�ɂ� \ �͕t���Ȃ�
										char *FullPath, char *DirPath, char *FileName, char *Name, char *ExeName, const char *CurrentDir = 0 );

// �t�@�C�������ꏏ�ɂȂ��Ă���ƕ������Ă���p�X������t�@�C�����ƃf�B���N�g���p�X�𕪊�����
// �t���p�X�ł���K�v�͖����A�t�@�C���������ł��ǂ�
// DirPath �̏I�[�� �� �}�[�N�͕t���Ȃ�
extern int			AnalysisFileNameAndDirPath_( const char *Src, char *FileName = 0, char *DirPath = 0 ) ;
extern int			AnalysisFileNameAndDirPathW_( const wchar_t *Src, wchar_t *FileName = 0, wchar_t *DirPath = 0 ) ;

// �t�@�C���p�X����t�@�C�����Ɗg���q���擾����
extern int			AnalysisFileNameAndExeName_( const char *Src, char *Name = 0, char *ExeName = 0 ) ;
extern int			AnalysisFileNameAndExeNameW_( const wchar_t *Src, wchar_t *Name = 0, wchar_t *ExeName = 0 ) ;

// �t�@�C���p�X�̊g���q��ς���������𓾂�
extern int			GetChangeExeNamePath_( const char *Src, char *Dest, const char *ExeName ) ;

extern void			SetEnMark_( char *PathBuf ) ;			// ����Ɂw\�x�����Ă��Ȃ��ꍇ�͕t����

// �n���ꂽ��������t���p�X������Ƃ��Ĉ����A�h���C�u��( :\ or :/ �̑O�܂� )
// ���̓l�b�g���[�N�t�H���_��( \ or / �̑O�܂� )���擾����
// �l�b�g���[�N�t�H���_�������ꍇ�͍ŏ��� \\ ���܂߂�
// �߂�l�͎擾����������̒���( �l�b�g���[�N�t�H���_�̏ꍇ�� \\ ��������ʂɊ܂܂�܂� )
// Src �̓t���p�X�ł���K�v������܂��A���΃p�X�ł͐���ɓ��삵�܂���
extern int			AnalysisDriveName_( const char *Src, char *Dest ) ;
extern int			AnalysisDriveNameW_( const wchar_t *Src, wchar_t *Dest ) ;

// �n���ꂽ��������t�H���_�p�X������Ƃ��Ĉ����A�t�H���_��( \ or / �̑O�܂� )���擾���܂�
// �n�������񂪃t���p�X�ŁA�ŏ��Ƀh���C�u����������Ă����琳��Ȍ��ʂ������܂���
// ../ ���̉��ʃt�H���_�ɍ~��镶���񂪂������ꍇ�� .. �����o�͂���܂�
// �߂�l�͎擾����������̒����ł�
extern int			AnalysisDirectoryName_( const char *Src, char *Dest ) ;
extern int			AnalysisDirectoryNameW_( const wchar_t *Src, wchar_t *Dest ) ;


}

#endif // __DXFILE_H__

