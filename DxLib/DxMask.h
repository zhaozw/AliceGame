// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�}�X�N�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXMASK_H__
#define __DXMASK_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_MASK

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxStatic.h"
#include "DxGraphicsAPI.h"
#include "DxMemImg.h"
#include "DxHandle.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �}�X�N�f�[�^�p�\����
struct MASKDATA
{
	HANDLEINFO				HandleInfo ;							// �n���h�����ʏ��

	BYTE					*SrcData ;								// �}�X�N�\�[�X�f�[�^
	int						SrcDataPitch ;							// �\�[�X�f�[�^�s�b�`
	int						MaskWidth, MaskHeight ;					// �}�X�N�̕��ƍ���
	int						ValidFlag ;								// �L���t���O
	int						TransMode ;								// ���ߐF�������[�h
} ;

// �}�X�N�f�[�^�Ǘ��p�\����
struct MASKMANAGEDATA
{
	int						InitializeFlag ;						// �������t���O

	BYTE					*MaskBuffer ;							// �}�X�N�f�[�^�o�b�t�@
	int						MaskBufferPitch ;						// �}�X�N�f�[�^�o�b�t�@�̃s�b�`

	int						MaskReverseEffectFlag ;					// �}�X�N�̐��l�ɑ΂�����ʂ��t�]������
	int						FullScreenMaskUpdateFlag ;				// �S��ʃ}�X�N�X�V���s���Ă��邩�̃t���O
	int						CreateMaskFlag ;						// �}�X�N�T�[�t�F�X���쐬����Ă��邩�A�̃t���O
	int						MaskUseFlag ;							// �}�X�N���g�p���邩�A�t���O
	int						MaskValidFlag ;							// MaskUseFlag �� CreateMaskFlag �� & ��������

	int						MaskBeginFunctionCount ;				// �}�X�N���g�p�����`��̑O�ɌĂԊ֐����Ă΂ꂽ��

	int						ValidMaskDrawMemImg ;					// MaskDrawMemImg ���L�����ǂ����A�̃t���O
	MEMIMG					MaskDrawMemImg ;						// �}�X�N�g�p���̕`���T�[�t�F�X�̑���� MEMIMG

	// DirectX �o�[�W�����ˑ���`
	int						MaskTextureSizeX, MaskTextureSizeY ;	// �}�X�N�e�N�X�`���̃T�C�Y
	DX_DIRECT3DTEXTURE9		*MaskImageTexture ;						// �}�X�N�C���[�W�e�N�X�`��
	DX_DIRECT3DTEXTURE9		*MaskScreenTexture ;					// �}�X�N�X�N���[���e�N�X�`��
	DX_DIRECT3DSURFACE9		*MaskScreenSurface ;					// �}�X�N�X�N���[���T�[�t�F�X

} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �}�X�N�֌W�̏��
extern MASKMANAGEDATA MaskManageData ;


// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// DxMask.cpp �֘A
extern	int			InitializeMask( void ) ;																				// �}�X�N�����̏�����
extern	int			TerminateMask( void ) ;																					// �}�X�N�����̌�n��

extern	int			ReleaseMaskSurface( void ) ;																			// �}�X�N�X�N���[�����ꎞ�폜����
extern	int			ReCreateMaskSurface( void ) ;																			// �}�X�N�X�N���[���𕜋�������
extern	int			CreateMaskScreenFunction( int MaskSurfaceFlag ) ;														// �}�X�N�X�N���[�����쐬����֐�
extern	int			SetGraphToMask( RECT MaskRect, DX_DIRECTDRAWSURFACE7 *SrcSurface, BASEIMAGE *SrcImage ) ;				// �}�X�N�f�[�^�T�[�t�F�X�ɃO���t�B�b�N�����[�h����
extern	int			OutGraphToMask( RECT MaskRect, DX_DIRECTDRAWSURFACE7 *DestSurface, BASEIMAGE *DestImage ) ;				// �}�X�L���O���s���Ďw��T�[�t�F�X�ɓ]��
extern	int			CreateMaskOn2D( int DrawPointX, int DrawPointY, int DestWidth, int DestHeight, void *DestBufP ,
								   int DestPitch, int DestBitDepth, int SrcWidth, int SrcHeight, void *SrcData ) ;			// �}�X�N�p�^�[���̍쐬

extern	int			CreateMaskSurface( BYTE **MaskBuffer, int *BufferPitch, int Width, int Height, int *TransModeP ) ;		// �}�X�N�T�[�t�F�X�̍쐬

extern	int			MaskDrawBeginFunction( RECT Rect ) ;																	// �}�X�N���g�p�����`��̑O�ɌĂԊ֐�
extern	int			MaskDrawAfterFunction( RECT Rect ) ;																	// �}�X�N���g�p�����`��̌�ɌĂԊ֐�

extern	int			InitializeMaskHandle( HANDLEINFO *HandleInfo ) ;														// �}�X�N�n���h���̏�����
extern	int			TerminateMaskHandle( HANDLEINFO *HandleInfo ) ;															// �}�X�N�n���h���̌�n��

extern	int			MakeMask_UseGParam( int Width, int Height, int ASyncLoadFlag = FALSE ) ;								// �}�X�N�f�[�^�̒ǉ�
extern	int			LoadMask_UseGParam( const TCHAR *FileName, int ASyncLoadFlag = FALSE ) ;								// �}�X�N�f�[�^�����[�h���� 
extern	int			LoadDivMask_UseGParam( const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int ASyncLoadFlag = FALSE ) ;	// �}�X�N���摜���番���ǂ݂���

}

#endif //	DX_NON_MASK

#endif // __DXMASK_H__
