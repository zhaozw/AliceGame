// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�V�X�e���v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXSYSTEM_H__
#define __DXSYSTEM_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxBaseFunc.h"

#if !defined( __ANDROID )
#include "Windows/DxSystemWin.h"
#endif

#ifdef __ANDROID
#include "Android/DxSystemAndroid.h"
#endif

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------


// �\���̒�` --------------------------------------------------------------------

// �V�X�e���f�[�^�\����
struct DXSYSTEMDATA
{
	int						DxLib_InitializeFlag ;				// �c�w���C�u�����̏��������������Ă��邩�t���O
	int						DxLib_RunInitializeFlag ;			// �c�w���C�u�����̏����������A�t���O

	int						NotWinFlag ;						// �c�w���C�u�����̃E�C���h�E�֘A�@�\���g�p���Ȃ��t���O
	int						NotDrawFlag ;						// �`��@�\���g�p���Ȃ��t���O
	int						NotSoundFlag ;						// �T�E���h�@�\���g�p���Ȃ��t���O
	int						NotInputFlag ;						// ���͏�Ԏ擾�@�\���g�p���Ȃ��t���O

	int						EndRequestFlag ;					// �I�����N�G�X�g�t���O
	int						ASyncLoadFlag ;						// �񓯊��ǂݍ��݃t���O
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

extern DXSYSTEMDATA DxSysData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �������E�I���֌W
extern	int			DxLib_SysInit( void ) ;													// DxSysData �֌W�̏��������s��
extern	int			DxLib_EndRequest( void ) ;												// �I�����N�G�X�g���s��
extern	int			DxLib_GetEndRequest( void ) ;											// �I�����N�G�X�g�̏�Ԃ��擾����

// �G���[�����֐�
extern	int			DxLib_Error( const TCHAR *ErrorStr ) ;									// ���C�u�����̃G���[�������s��				
extern	int			DxLib_FmtError( const TCHAR *FormatString, ... ) ;						// �����t�����C�u�����̃G���[�������s��	

// �񓯊��ǂݍ��݊֌W
extern	int			GetASyncLoadFlag( void ) ;												// �񓯊��ǂݍ��݂��s�����ǂ������擾����

// ������ϊ�
extern	int			WCharToMBChar( int CodePage, const DXWCHAR *Src, char *Dest, int DestSize ) ;		// ���C�h��������}���`�o�C�g������ɕϊ�����
extern	int			MBCharToWChar( int CodePage, const char *Src, DXWCHAR *Dest, int DestSize ) ;		// �}���`�o�C�g����������C�h������ɕϊ�����

}

#endif // __DXSYSTEM_H__

