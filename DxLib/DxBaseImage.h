// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�a�������h���������v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXBASEIMAGE_H__
#define __DXBASEIMAGE_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxThread.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#define BASEIM						BaseImageManage

// �\���̒�` --------------------------------------------------------------------

// �ėp�摜�ǂݍ��݂ɕK�v�ȃO���[�o���f�[�^���W�߂��\����
struct CREATEBASEIMAGETYPE2_GPARAM
{
	int						( *UserImageLoadFunc4[ MAX_USERIMAGEREAD_FUNCNUM ] )( STREAMDATA *Src, BASEIMAGE *Image ) ;	// ���[�U�[�摜�ǂݍ��݊֐�Ver4
	int						UserImageLoadFuncNum4 ;																		// ���[�U�[�摜�ǂݍ��݊֐�Ver4�̐�
} ;

// �摜�̓ǂݍ��݂ɕK�v�ȃO���[�o���f�[�^��Z�߂��\����
struct LOADBASEIMAGE_GPARAM
{
	CREATEBASEIMAGETYPE2_GPARAM CreateGraphImageType2GParam ;		// CreateGraphImageType2_UseGParam �Ŏg�p����f�[�^

	STREAMDATASHREDTYPE2	StreamDataShred2 ;						// �X�g���[���f�[�^�A�N�Z�X�p�֐��Q
	STREAMDATASHRED			FileStreamDataShred ;					// �t�@�C���f�[�^�A�N�Z�X�p�֐�
	STREAMDATASHRED			MemStreamDataShred ;					// �������f�[�^�A�N�Z�X�p�֐�
} ;

// BASEIMAGE + DIB �֌W�̏��\����
struct BASEIMAGEMANAGE
{
	int						( *UserImageLoadFunc4[ MAX_USERIMAGEREAD_FUNCNUM ] )( STREAMDATA *Src, BASEIMAGE *Image ) ;																									// ���[�U�[�摜�ǂݍ��݊֐�Ver4
	int						UserImageLoadFuncNum4 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver4�̐�
/*
	int						( *UserImageLoadFunc3[ MAX_USERIMAGEREAD_FUNCNUM ] )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ;		// ���[�U�[�摜�ǂݍ��݊֐�Ver3
	int						UserImageLoadFuncNum3 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver3�̐�

	int						( *UserImageLoadFunc2[ MAX_USERIMAGEREAD_FUNCNUM ] )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ;													// ���[�U�[�摜�ǂݍ��݊֐�Ver2
	int						UserImageLoadFuncNum2 ;																																										// ���[�U�[�摜�ǂݍ��݊֐�Ver2�̐�

	int						( *UserImageLoadFunc[ MAX_USERIMAGEREAD_FUNCNUM ] )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ;																					// ���[�U�[�摜�ǂݍ��݊֐�
	int						UserImageLoadFuncNum ;																																										// ���[�U�[�摜�ǂݍ��݊֐��̐�
*/

	DX_CRITICAL_SECTION		CriticalProcessHandle ;					// �f�[�^�����Փˉ��p�N���e�B�J���Z�N�V����
	int						InitializeFlag ;						// �������t���O

	int						Bmp32AllZeroAlphaToXRGB8 ;				// 32bit bmp �摜�̂`���������ׂĂO��������`�����𖳎����邩�ǂ���
	int						LowLoadFlag ;							// �O���t�B�b�N�̒ᑬ�ǂݍ��݂��s�����t���O
	int						ImageShavedMode ;						// ���F���̊g�U�p�^�[��
} ;


// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// ��{�C���[�W�Ǘ��p�f�[�^
extern BASEIMAGEMANAGE BaseImageManage ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �������A��n��
extern	int		InitializeBaseImageManage( void ) ;															// ��{�C���[�W�Ǘ����̏�����
extern	int		TerminateBaseImageManage( void ) ;															// ��{�C���[�W�Ǘ����̌�n��

// �摜�ǂݍ��݊֐�
extern	int		SetBmp32AllZeroAlphaToXRGB8( int Flag ) ;															// 32bit bmp �摜�̂`���������ׂĂO��������`�����𖳎����邩�ǂ����̃t���O���Z�b�g����

extern	int		ScalingBltBaseImage(
					int SrcX1,  int SrcY1,  int SrcX2,  int SrcY2,  BASEIMAGE *SrcBaseImage,
					int DestX1, int DestY1, int DestX2, int DestY2, BASEIMAGE *DestBaseImage, int Bilinear = TRUE ) ;		// ��{�C���[�W�f�[�^���g��]������
extern	int		GraphHalfScaleBlt(	COLORDATA *ColorData,
										void *DestGraphData, int DestPitch,
										void *SrcGraphData, int SrcPitch,
										int DestX, int DestY, int SrcX, int SrcY, int SrcWidth, int SrcHeight ) ;	// �Q���̂P�X�P�[�����O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s���A���̂��ߊ�{���̓]����`�͎w��ł��Ȃ�
extern	int		NoneMaskFill( RECT *Rect, void *ImageData, int Pitch, COLORDATA *ColorData, unsigned int Fill = 0xff ) ;		// �g���Ă��Ȃ��r�b�g���w��̒l�Ŗ��߂�


extern	int		ConvertYV12ToXRGB32( void *YV12Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YV12 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertNV11ToXRGB32( void *NV11Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// NV11 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertNV12ToXRGB32( void *NV12Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// NV12 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertYUY2ToXRGB32( void *YUY2Image, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YUY2 �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertUYVYToXRGB32( void *UYVYImage, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// UYVY �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����
extern	int		ConvertYVYUToXRGB32( void *YVYUImage, int Width, int Height, BASEIMAGE *DestBaseImage ) ;				// YVYU �t�H�[�}�b�g�̃C���[�W�� XRGB32 �̃r�b�g�}�b�v�C���[�W�ɕϊ�����

extern	void	InitCreateBaseImageType2GParam( CREATEBASEIMAGETYPE2_GPARAM *GParam ) ;											// CREATEBASEIMAGETYPE2_GPARAM �̃f�[�^���Z�b�g����
extern	void	InitLoadBaseImageGParam( LOADBASEIMAGE_GPARAM *GParam ) ;														// LOADBASEIMAGE_GPARAM �̃f�[�^���Z�b�g����

extern	int		CreateGraphImageType2_UseGParam( CREATEBASEIMAGETYPE2_GPARAM *GParam, STREAMDATA *Src, BASEIMAGE *Dest ) ;																																													// CreateGraphImageType2 �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphImageOrDIBGraph_UseGParam( LOADBASEIMAGE_GPARAM *GParam, const TCHAR *FileName, void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, int ReverseFlag,
														BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ;																																														// CreateGraphImageOrDIBGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphImage_plus_Alpha_UseGParam( LOADBASEIMAGE_GPARAM *GParam, const TCHAR *FileName, void *RgbImage, int RgbImageSize, int RgbImageType,
													void *AlphaImage, int AlphaImageSize, int AlphaImageType,
													BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag ) ;																																												// CreateGraphImage_plus_Alpha �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

}

#endif // __DXBASEIMAGE_H__
