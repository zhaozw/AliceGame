// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�W���b���C�u�����g�p�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXUSECLIB_H__
#define __DXUSECLIB_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"

#ifndef DX_NON_OGGTHEORA
#include "DxMovie.h"
#endif

#if !defined( DX_NON_OGGVORBIS ) || !defined( DX_NON_MOVIE )
#include "DxSoundConvert.h"
#endif

#include "DxFile.h"
#include "DxBaseFunc.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------


#ifndef DX_NON_PNGREAD
extern	int		LoadPngImage( STREAMDATA *Src, BASEIMAGE *Image ) ;											// �o�m�f�摜�̓ǂ݂���
#ifndef DX_NON_SAVEFUNCTION
extern	int		SaveBaseImageToPngBase( const DXWCHAR *FilePathW, const char *FilePathA, BASEIMAGE *BaseImage, int CompressionLevel ) ;																					// ��{�摜�f�[�^���o�m�f�摜�Ƃ��ĕۑ�����
#endif
#endif
#ifndef DX_NON_JPEGREAD
extern	int		LoadJpegImage( STREAMDATA *Src, BASEIMAGE *Image ) ;										// �i�o�d�f�摜�̓ǂ݂��� (���̂� DxUseCLib.cpp �̒�)
#ifndef DX_NON_SAVEFUNCTION
extern	int		SaveBaseImageToJpegBase( const DXWCHAR *FilePathW, const char *FilePathA, BASEIMAGE *BaseImage, int Quality, int Sample2x1 ) ;																			// ��{�摜�f�[�^���i�o�d�f�摜�Ƃ��ĕۑ�����
#endif
#endif



extern	int			FileRead_scanf_base( DWORD_PTR FileHandle, const char *Format, va_list Param ) ;		// �t�@�C�����珑�������ꂽ�f�[�^��ǂݏo��
extern	int			FileRead_scanf_baseW( DWORD_PTR FileHandle, const DXWCHAR *Format, va_list Param ) ;	// �t�@�C�����珑�������ꂽ�f�[�^��ǂݏo��



#ifndef DX_NON_MOVIE
#ifndef DX_NON_DSHOW_MOVIE
#ifndef DX_NON_DSHOW_MP3
extern	int SetupSoundConvert_DSMP3(            SOUNDCONV *SoundConv ) ;							// DirectShow���g����MP3�t�@�C�����R���o�[�g����Z�b�g�A�b�v�������s��( [��] -1:�G���[ )
#endif
#endif
#endif




#ifndef DX_NON_OGGVORBIS
extern	int SetupSoundConvert_OGG(            SOUNDCONV *SoundConv ) ;								// �n�f�f�t�@�C���̃Z�b�g�A�b�v�������s��( [��] -1:�G���[ )
extern	int TerminateSoundConvert_OGG(        SOUNDCONV *SoundConv ) ;								// �n�f�f�t�@�C���̌�n���������s��
extern	int ConvertProcessSoundConvert_OGG(   SOUNDCONV *SoundConv ) ;								// �ϊ���̃o�b�t�@�Ƀf�[�^���[����
//extern	int SetTimeSoundConvert_OGG(      SOUNDCONV *SoundConv, int Time ) ;					// �ϊ��������ʒu��ύX����( �~���b�P�� )
extern	int SetSampleTimeSoundConvert_OGG(    SOUNDCONV *SoundConv, int SampleTime ) ;				// �ϊ������̈ʒu��ύX����( �T���v���P�� )
extern	int GetSoundConvertDestSize_Fast_OGG( SOUNDCONV *SoundConv ) ;								// �ϊ���̑�}�̃f�[�^�T�C�Y�𓾂�
#endif




#ifndef DX_NON_OGGTHEORA

extern int	TheoraDecode_GrobalInitialize( void ) ;																					// �\�t�g�I�Ɉ�x�����ĂԂׂ��������֐�

extern DWORD_PTR  TheoraDecode_InitializeStream( STREAMDATASHREDTYPE2 *StreamShred, DWORD_PTR StreamData, int StockFrameNum = 10, int ASyncTrhead = FALSE ) ;	// Ogg Theora �ǂݍ��ݏ����̏������s��( �߂�l  0:���s  1�ȏ�:���������� )
extern int	TheoraDecode_Terminate( DWORD_PTR Handle ) ;																			// Ogg Theora �ǂݍ��ݏ����̌�n�����s��
extern int	TheoraDecode_SurfaceTerminate( DWORD_PTR Handle ) ;																		// Ogg Theora �Ŏg�p���Ă���T�[�t�F�X���������

extern int	TheoraDecode_GetInfo( DWORD_PTR Handle, THEORADECODE_INFO *Info ) ;														// ����̏����擾����
extern int	TheoraDecode_GetCurrentFrame( DWORD_PTR Handle ) ;																		// �J�����g�t���[�����擾����
	
extern int	TheoraDecode_IncToFrame( DWORD_PTR Handle, int AddNum = 1 ) ;															// �J�����g�t���[�����P�t���[�����i�߂�( �߂�l  0:�L�[�t���[������Ȃ�����  1:�L�[�t���[��  -1:�G���[ )
extern int	TheoraDecode_SeekToFrame( DWORD_PTR Handle, int Frame ) ;																// �J�����g�t���[�����w��̃t���[���Ɉړ�����
extern int	TheoraDecode_SeekToTime( DWORD_PTR Handle, LONGLONG Time ) ;															// �J�����g�t���[�����w��̍Đ����ԂɈړ�����( �P�ʂ̓}�C�N���b )

extern int	TheoraDecode_SetupImage( DWORD_PTR Handle, int BaseImage = 0, int YUVImage = 0, int ASyncThread = FALSE ) ;				// �J�����g�t���[����RGB�摜���쐬����( �߂�l  1:�쐬���ꂽ  0:����Ȃ����� )
extern const BASEIMAGE           *TheoraDecode_GetBaseImage( DWORD_PTR Handle ) ;													// �ꎞ�o�b�t�@�̃A�h���X���擾����
extern const DX_DIRECT3DSURFACE9 *TheoraDecode_GetYUVImage( DWORD_PTR Handle ) ;													// �ꎞ�o�b�t�@�� YUV �t�H�[�}�b�g�̃T�[�t�F�X�𓾂�

extern int	TheoraDecode_IsIdle( DWORD_PTR Handle ) ;																				// �f�R�[�h�X���b�h���A�C�h����Ԃ��ǂ����𒲂ׂ�( �߂�l  1:�A�C�h�����  0:�ғ��� )

#endif

}

#endif // __DXUSECLIB_H__
