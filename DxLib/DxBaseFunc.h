// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�W���֐��̌݊��֐��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXBASEFUNC_H__
#define __DXBASEFUNC_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include <stdarg.h>

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#ifdef UNICODE
	#define _TMULT( strp, cset )					CheckUTF16H( (strp) )
#else
	#define _TMULT( strp, cset )					CheckMultiByteChar( (strp), (cset) )
#endif

#define DXWCHAR		WORD
#ifdef UNICODE
	#define _DXWTP( x )		( DXWCHAR * )( x )
	#define _DXWTR( x )		( DXWCHAR * )( _T( x ) )
#else
	#define _DXWTP( x )		x
	#define _DXWTR( x )		x
#endif

// �\���̒�` --------------------------------------------------------------------

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// TCHAR�p��`
#ifdef UNICODE
	#define _TSTRCAT								_WCSCAT
	#define _TSTRCPY								_WCSCPY
	#define _TSTRLEN								_WCSLEN
	#define _TSTRCMP								_WCSCMP
	#define _TSTRNCMP								_WCSNCMP
	#define _TSTRNCPY								_WCSNCPY
	#define _TSTRUPR								_WCSUPR
	#define _TSTRCHR								_WCSCHR
	#define _TSTRRCHR								_WCSRCHR
	#define _TVSPRINTF( buf, frm, vlst )			_VSWPRINTF( _DXWTP( buf ), _DXWTP( frm ), vlst )
	#define _TSPRINTF								_SWPRINTF
	#define _TTOF									_ATOFW
	#define _TTOI									_ATOIW
	#define _ITOT									_ITOAW
#else
	#define _TSTRCAT								_STRCAT
	#define _TSTRCPY								_STRCPY
	#define _TSTRLEN								_STRLEN
	#define _TSTRCMP								_STRCMP
	#define _TSTRNCMP								_STRNCMP
	#define _TSTRNCPY								_STRNCPY
	#define _TSTRUPR								_STRUPR
	#define _TSTRCHR								_STRCHR
	#define _TSTRRCHR								_STRRCHR
	#define _TVSPRINTF								_VSPRINTF
	#define _TSPRINTF								_SPRINTF
	#define _TTOF									_ATOF
	#define _TTOI									_ATOI
	#define _ITOT									_ITOA
#endif


// �����R�[�h�֘A
extern	void		_SET_CHARSET( int CharSet ) ;
extern	int			_GET_CHARSET( void ) ;

extern	void		_SET_CODEPAGE( int CodePage ) ;
extern	int			_GET_CODEPAGE( void ) ;

extern	int			CheckUTF16H( wchar_t c ) ;																					// �T���Q�[�g�y�A���ǂ����̔���( TRUE:�S�o�C�g�������  FALSE:�Q�o�C�g���� )
extern	int			CheckDoubleChar( const TCHAR *String, int CharPosition, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;			// �w��̕�����̎w��̈ʒu�̕����̃^�C�v��Ԃ�( 0:�P�L��������  1:�Q�L���������̂P�L������  2:�Q�L���������̂Q�L������ )
extern	int			CheckMultiByteChar( char CharCode, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;									// �Q�o�C�g���������ׂ�( TRUE:�Q�o�C�g����  FALSE:�P�o�C�g���� )
extern	int			CheckMultiByteString( const char *String, int BytePosition, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;		// �w��̕�����̎w��̈ʒu�̕����̃^�C�v��Ԃ�( 0:�P�o�C�g����  1:�Q�o�C�g�����̂P�o�C�g��  2:�Q�o�C�g�����̂Q�o�C�g�� )
extern	int			CheckUTF16HChar( const wchar_t *String, int CharPosition ) ;												// �w��̕�����̎w��̈ʒu�̕����̃^�C�v��Ԃ�( 0:��T���Q�[�g�y�A����  1:�T���Q�[�g�y�A�����̂P�L������  2:�T���Q�[�g�y�A�����̂Q�L������ )

// ���O�W���֐��n
extern	void		_STRCPY( char *Dest, const char *Src ) ;
extern	void		_WCSCPY( wchar_t *Dest, const wchar_t *Src ) ;
extern	void		_STRNCPY( char *Dest, const char *Src, int Num ) ;
extern	void		_WCSNCPY( wchar_t *Dest, const wchar_t *Src, int Num ) ;
extern	void		_STRCAT( char *Dest, const char *Src ) ;
extern	void		_WCSCAT( wchar_t *Dest, const wchar_t *Src ) ;
extern	char		*_STRSTR( const char *Str1, const char *Str2 ) ;
extern	int			_STRLEN( const char *Str ) ;
extern	int			_WCSLEN( const wchar_t *Str ) ;
extern	int			_STRCMP( const char *Str1, const char *Str2 ) ;
extern	int			_WCSCMP( const wchar_t *Str1, const wchar_t *Str2 ) ;
extern	int			_STRCMPI( const char *Str1, const char *Str2 ) ;
extern	int			_STRNCMP( const char *Str1, const char *Str2, int Size ) ;
extern	int			_WCSNCMP( const wchar_t *Str1, const wchar_t *Str2, int Size ) ;
extern	char		*_STRCHR( const char *Str1, char Char ) ;
extern	wchar_t		*_WCSCHR( const wchar_t *Str1, wchar_t Char ) ;
extern	char		*_STRRCHR( const char *Str1, char Char ) ;
extern	wchar_t		*_WCSRCHR( const wchar_t *Str1, wchar_t Char ) ;
extern	char		*_STRUPR( char *Str ) ;
extern	wchar_t		*_WCSUPR( wchar_t *Str ) ;
extern	int			_VSPRINTF( char *Buffer, const char *FormatString, va_list Arg ) ; // ���̂� DxUseCLib.cpp �̒�
extern	int			_VSWPRINTF( DXWCHAR *Buffer, const DXWCHAR *FormatString, va_list Arg ) ; // ���̂� DxUseCLib.cpp �̒�
extern	int			_SPRINTF( char *Buffer, const char *FormatString, ... ) ; // ���̂� DxUseCLib.cpp �̒�
extern	int			_SWPRINTF( DXWCHAR *Buffer, const DXWCHAR *WFormatString, ... ) ; // ���̂� DxUseCLib.cpp �̒�
extern	void		_MEMSET( void *Memory, unsigned char Char, size_t Size ) ;
extern	void		_MEMSETD( void *Memory, unsigned int Data, int Num ) ;
extern	int			_MEMCMP( const void *Buffer1, const void *Buffer2, int Size ) ;
extern	void		_MEMCPY( void *Buffer1, const void *Buffer2, size_t Size ) ;
extern	void		_MEMMOVE( void *Buffer1, const void *Buffer2, size_t Size ) ;

extern	void		_SINCOS( float Angle, float *DestSin, float *DestCos ) ;
extern	void		_SINCOS_DOUBLE( double Angle, double *DestSin, double *DestCos ) ;
extern	float		_POW( float x, float y ) ;
extern	float		_ATAN2( float y, float x ) ;
extern	float		_EXPF( float x ) ;
extern	float		_ASIN( float Real ) ;
extern	float		_ACOS( float Real ) ;
extern	double		_LOG10( double Real ) ;
extern	int			_ABS( int Number ) ;
extern	float		_FABS( float Real ) ;
extern	int			_FTOL( float Real ) ;
extern	int			_DTOL( double Real ) ;
extern	LONGLONG	_DTOL64( double Real ) ;
extern	void		_FTOL4( float *Real, int *Buffer4 ) ;
extern	void		_DTOL4( double *Real, int *Buffer4 ) ;
extern	float		_SQRT( float Real ) ;
extern	int			_ATOI( const char *String ) ;
extern	int			_ATOIW( const DXWCHAR *String ) ;
extern	double		_ATOF( const char *String ) ;
extern	double		_ATOFW( const DXWCHAR *String ) ;
extern	char 		*_ITOA( int Value, char *Buffer, int Radix ) ;
extern	wchar_t		*_ITOAW( int Value, wchar_t *Buffer, int Radix ) ;
extern	void		_SHR64( DWORD *Number64, int ShftNum ) ;
extern	void		_SHL64( DWORD *Number64, int ShftNum ) ;
extern	void		_MUL128_1( DWORD *Src64_1, DWORD *Src64_2, DWORD *Dest128 );
extern	void		_DIV128_1( DWORD *Src128,  DWORD *Div64,   DWORD *Dest64  );

}

#endif // __DXBASEFUNC_H__
