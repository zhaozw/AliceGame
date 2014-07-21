// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�t�H���g�����p�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXFONT_H__
#define __DXFONT_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_FONT

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxStatic.h"
#include "DxMemImg.h"
#include "DxHandle.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// CreateFontToHandle �Ŏg�p�����O���[�o���ϐ���Z�߂�����
struct CREATEFONTTOHANDLE_GPARAM
{
	int						NotTextureFlag ;					// �쐬����t�H���g�L���b�V�����e�N�X�`���ɂ��邩�A�t���O
	int						TextureCacheColorBitDepth16Flag ;	// �쐬����t�H���g�L���b�V���e�N�X�`���̃J���[�r�b�g����16�r�b�g�ɂ��邩�ǂ����̃t���O
	int						CacheCharNum ;						// �t�H���g�L���b�V���ŃL���b�V���ł��镶���̐�
} ;

// �t�H���g�P�����̃L���b�V�����
struct FONTDATA
{
	BYTE					ValidFlag ;			// �L���t���O
	BYTE					WCharaFlag ;		// ���C�h�����t���O
	short					DrawX, DrawY ;		// �����摜��`�悷�ׂ����W
	short					AddX ;				// ���̕�����`�悷�ׂ����΍��W
	int						GraphIndex ;		// �����f�[�^�̃C���f�b�N�X�i���o�[
	short					SizeX, SizeY ;		// �����̃T�C�Y
	struct FONTCODEDATA *	CodeData ;			// ���̃t�H���g���Ǘ����Ă���f�[�^�̃|�C���^
} ;

// �t�H���g�L���b�V�����݃t���O�\����
struct FONTCODEDATA
{
	int						ExistFlag ;			// �L���b�V���̑��݃t���O
	FONTDATA *				DataPoint ;			// �L���b�V���f�[�^�̑��݈ʒu
} ;

// �t�H���g�L���b�V���̊Ǘ��f�[�^
struct FONTMANAGE
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	int						*LostFlag ;							// ������� TRUE �ɂ���t���O�ւ̃|�C���^

	FONTDATA				FontData[ FONT_CACHE_MAXNUM + 1 ];	// �L���b�V���f�[�^
	FONTCODEDATA			FontCodeData[ 0x10000 ] ;			// ���݃f�[�^���܂ރf�[�^�z��
	unsigned int			Index ;								// ���f�[�^�ǉ����̔z��C���f�b�N�X�i���o�[
	int						MaxCacheCharNum ;					// �L���b�V���ł���ő吔
	unsigned char			*CacheMem ;							// �e�L�X�g�L���b�V��������
	int						CachePitch ;						// �e�L�X�g�L���b�V���������̃s�b�`	
	int						CacheDataBitNum ;					// �e�L�X�g�L���b�V����̂P�s�N�Z���̃r�b�g��

	TCHAR					FontName[ 256 ] ;					// �t�H���g�̖��O
	int						FontThickness ;						// �t�H���g�̑���
	int						FontSize ;							// �`�悷��t�H���g�̃T�C�Y
	int						FontHeight ;						// �`�悷��t�H���g�̍ő�c��
	int						FontAddHeight ;						// �T�C�Y�����ׂ̈ɑ���������
	int						Italic ;							// �C�^���b�N�t�H���g���ǂ���(TRUE:�C�^���b�N FALSE:��C�^���b�N)
	int						Space ;								// ���̕�����\��������W�ɉ��Z�h�b�g��
	int						MaxWidth ;							// �t�H���g�̍ő啝
	HFONT					FontObj ;							// �t�H���g�̃I�u�W�F�N�g�f�[�^

	int						FontType ;							// �t�H���g�̃^�C�v
	int						CharSet ;							// �L�����N�^�Z�b�g
	int						EdgeSize ;							// �G�b�W�̑���

	SIZE					SurfaceSize ;						// �e�L�X�g�T�[�t�F�X�̃T�C�Y 
	int						LengthCharNum ;						// �T�[�t�F�X�̏c�ɕ��ׂ��镶���̐�

	int						TextureCache ;						// �e�N�X�`���ɃL���b�V������ꍇ�̃e�N�X�`���O���t�B�b�N�n���h��
	int						TextureCacheSub ;					// �e�N�X�`���ɃL���b�V������ꍇ�̃e�N�X�`���O���t�B�b�N�n���h��(���p)
	int						TextureCacheLostFlag ;				// TextureCache �������ɂȂ����Ƃ��� TRUE �ɂȂ�ϐ�
//	BASEIMAGE				TextureTempCache ;					// �e�N�X�`���ɓ]������O�Ɉꎞ�I�ɃO���t�B�b�N�f�[�^��ۑ�����C���[�W�f�[�^
	BASEIMAGE				TextureCacheBaseImage ;				// TextureCache �ɓ]���������̂Ɠ������̂��i�[������{�C���[�W
	int						TextureCacheColorBitDepth ;			// �e�N�X�`���L���b�V���̃J���[�r�b�g��

	int						TextureCacheFlag ;					// �e�N�X�`���L���b�V�������Ă��邩�A�t���O
} ;

// �t�H���g�V�X�e���p�\����
struct FONTSYSTEM
{
	int						InitializeFlag ;					// �������t���O

	int						NotTextureFlag ;					// �쐬����t�H���g�L���b�V�����e�N�X�`���ɂ��邩�A�t���O
	int						TextureCacheColorBitDepth16Flag ;	// �쐬����t�H���g�L���b�V���e�N�X�`���̃J���[�r�b�g����16�r�b�g�ɂ��邩�ǂ����̃t���O
	int						CacheCharNum ;						// �t�H���g�L���b�V���ŃL���b�V���ł��镶���̐�
	BYTE					BitCountTable[ 256 ] ;				// �r�b�g�J�E���g�e�[�u��

	int						DefaultFontHandle ;					// �f�t�H���g�Ŏg�p����t�H���g�̃n���h��
	TCHAR					DefaultFontName[ 128 ] ;			// �f�t�H���g�Ŏg�p����t�H���g�̐ݒ�
	int						DefaultFontSize ;
	int						DefaultFontThick ;
	int						DefaultFontType ;
	int						DefaultFontCharSet ;
	int						DefaultFontEdgeSize ;
	int						DefaultFontItalic ;
	int						DefaultFontSpace ;
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int			InitFontManage( void ) ;																					// �t�H���g�V�X�e���̏�����
extern	int			TermFontManage( void ) ;																					// �t�H���g����̏I��
extern	int			InitCacheFontToHandle( void ) ;																				// �t�H���g�̃L���b�V����������������
extern	int			InitFontCacheToHandle( int FontHandle, int ASyncThread = FALSE ) ;											// ����̃t�H���g�̃L���b�V����������������

extern	int			InitializeFontHandle( HANDLEINFO *HandleInfo ) ;															// �t�H���g�n���h��������������
extern	int			TerminateFontHandle( HANDLEINFO *HandleInfo ) ;																// �t�H���g�n���h���̌�n��������

extern	int			RefreshFontDrawResourceToHandle( int FontHandle, int ASyncThread = FALSE ) ;								// �t�H���g�n���h�����g�p����`��o�b�t�@��e�N�X�`���L���b�V�����ď���������
extern	int			FontCacheStringDrawToHandleST(
							int DrawFlag, int x, int y, 
							bool ExRateValidFlag, double ExRateX, double ExRateY,
							const TCHAR *StrData,
							int Color, MEMIMG *DestMemImg, RECT *ClipRect,
							int TransFlag, int FontHandle, int EdgeColor,
							int StrLen, int VerticalFlag, SIZE *DrawSize ) ;
extern	int			RefreshDefaultFont( void ) ;																				// �f�t�H���g�t�H���g���č쐬����
extern	int			InitFontToHandleBase( int Terminate = FALSE ) ;																// InitFontToHandle �̓����֐�
/*
extern	int			FontCacheStringDrawToHandleST(  int DrawFlag, int x, int y, const char *StrData, int Color, void *DSuf,
													void *ASuf, int APitch, RECT *ClipRect, int ColorBitDepth ,
													int TransFlag, int FontHandle, int EdgeColor, int StrLen, int VerticalFlag,
													SIZE *DrawSize ) ;															// ������̕`��i�L���b�V���g�p�Łj
*/

extern	FONTMANAGE *GetFontManageDataToHandle( int FontHandle ) ;																// �t�H���g�Ǘ��f�[�^�̎擾

extern	void		InitCreateFontToHandleGParam( CREATEFONTTOHANDLE_GPARAM *GParam ) ;											// CREATEFONTTOHANDLE_GPARAM �̃f�[�^���Z�b�g����

extern	int			CreateFontToHandle_UseGParam( CREATEFONTTOHANDLE_GPARAM *GParam, const TCHAR *FontName, int Size, int Thick, int FontType, int CharSet, int EdgeSize, int Italic, int Handle, int ASyncLoadFlag = FALSE ) ;			// CreateFontToHandle �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

}

#endif // DX_NON_FONT

#endif // __DXFONT_H__
