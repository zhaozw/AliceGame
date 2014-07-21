// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���͏��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXINPUT_H__
#define __DXINPUT_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_INPUT

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxStatic.h"
#include "DxDirectX.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// �p�b�h�̏��
struct DINPUTPAD
{
	int						XInputDeviceNo ;					// XInput�ŃA�N�Z�X����f�o�C�X�̏ꍇ�͂O�ȏ�̒l������( DirectInput �ň����ꍇ�� -1 )
	D_XINPUT_STATE			XInputState ;						// XInput�ł̃p�b�h�̏��

	D_IDirectInputDevice7	*Device ;							// �p�b�h�f�o�C�X�I�u�W�F�N�g
	D_IDirectInputEffect	*LeftEffect ;						// �p�b�h�f�o�C�X�G�t�F�N�g�I�u�W�F�N�g
	D_IDirectInputEffect	*RightEffect ;						// �p�b�h�f�o�C�X�G�t�F�N�g�I�u�W�F�N�g
	HANDLE					Event ;								// �p�b�h�̃C�x���g�n���h��
	D_DIJOYSTATE			State ;								// ���
	int						RightStickFlag ;					// �E�X�e�B�b�N�����邩�ǂ���
	int						GetTime ;							// �擾����
	int						EffectPlayFlag ;					// �G�t�F�N�g���Đ������A�t���O
	int						EffectPower ;						// �G�t�F�N�g�̋���
	int						EffectTime ;						// �G�t�F�N�g�̒���
	int						EffectCompTime ;					// �G�t�F�N�g���J�n���Ă���o�߂�������
	int						EffectBackTime ;					// �G�t�F�N�g�̑O�񒲂ׂ�����
	int						EffectPlayStateLeft ;				// DirectInputEffect ��ł́A������̍Đ����(�\�t�g����A�N�e�B�u�ɂȂ�΍Đ���~�����)
	int						EffectPlayStateRight ;				// DirectInputEffect ��ł́A������̍Đ����(�\�t�g����A�N�e�B�u�ɂȂ�΍Đ���~�����)
	char					InstanceName[MAX_PATH];				// �f�o�C�X�̓o�^��
	char					ProductName[MAX_PATH];				// �f�o�C�X�̐��i�o�^��
	DWORD					DeadZone ;							// �����]�[��( 65536 = 100% )
} ;

// �c�����������h������������p�f�[�^�\���̌^
struct DINPUTDATA
{
	HMODULE					XInputDLL ;							// �w�h���������̂c�k�k

	DWORD					( WINAPI * XInputGetStateFunc )( DWORD dwUserIndex, D_XINPUT_STATE* pState ) ;
	DWORD					( WINAPI * XInputSetStateFunc )( DWORD dwUserIndex, D_XINPUT_VIBRATION* pVibration ) ;

	int						NoUseDirectInputFlag ;				// �c�����������h�����������g�p���Ȃ����ǂ����̃t���O
	int						NoUseVibrationFlag ;				// �c�����������h���������̐U���@�\���g�p���Ȃ����ǂ����̃t���O
	int						UseDirectInputFlag ;				// �c�����������h�����������g�p���邩�ǂ����̃t���O( NoUseDirectInputFlag ��⏕������� )
	int						UseDirectInput8Flag ;				// �c�����������h���������W���g�p���邩�ǂ����̃t���O
	D_IDirectInput7			*DirectInputObject ;				// �c�����������h���������I�u�W�F�N�g

	D_IDirectInputDevice7	*MouseDeviceObject ;				// �}�E�X�f�o�C�X�I�u�W�F�N�g
	D_IDirectInputDevice7	*KeyboardDeviceObject ;				// �L�[�{�[�h�f�o�C�X�I�u�W�F�N�g
	HANDLE					KeyEvent ;							// �L�[�{�[�h�̃C�x���g�n���h��
	int						KeyInputGetTime ;					// ��O�ɏ�Ԃ��擾��������
	unsigned char			KeyInputBuf[256] ;					// �L�[�{�[�h�̓��͏��
	int						KeyExclusiveCooperativeLevelFlag ;	// �L�[�{�[�h�̋������x�����r�����x���ɂȂ��Ă��邩�ǂ����t���O
	int						KeyToJoypadInputInitializeFlag ;	// KeyToJoypadInput ����x�ł��������������ǂ����̃t���O
	int						KeyToJoypadInput[ MAX_JOYPAD_NUM ][ 32 ][ 4 ] ;	// �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓���
	int						MouseInputBufValidFlag ;			// MouseInputBuf ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	BYTE					MouseInputBuf[ 4 ] ;				// �}�E�X�̓��͏��( 0:LEFT 1:RIGHT 2:MIDDLE )

	int						JoyPadNum ;							// �W���C�p�b�h�̐�
	DINPUTPAD				Joypad[ MAX_JOYPAD_NUM ] ;			// �p�b�h�f�o�C�X���

	int						KeyboardNotDirectInputFlag ;		// �L�[�{�[�h�f�o�C�X�̃A�N�Z�X�� DirectInput ���g�p���Ȃ����A�t���O
	int						EndFlag ;
	int						F10Flag ;							// F10 �������ꂽ���t���O
	int						F10InputTime ;						// F10 �������ꂽ����
	int						F12Flag ;							// F12 �������ꂽ���t���O
	int						F12InputTime ;						// F12 �������ꂽ����
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �c�����������h���������̏������A�I���֐�
extern	int InitializeDirectInput( void ) ;											// �c�����������h�������������������� 
extern	int TerminateDirectInput( void ) ;											// �c�����������h���������̎g�p���I������

extern	int SetF10Input( void ) ;													// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int ResetF10Input( void ) ;													// F10 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int SetF12Input( void ) ;													// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int ResetF12Input( void ) ;													// F12 �������ꂽ���Ƃɂ���t���O�𗧂Ă�
extern	int RefreshInputDeviceAcquireState( void ) ;								// �c�����������h���������f�o�C�X�̎擾��Ԃ��X�V����
extern	int JoypadEffectProcess( void ) ;											// �p�b�h�G�t�F�N�g�Ɋւ���t���[���������s��
extern	int RefreshEffectPlayState( void ) ;										// �p�b�h�G�t�F�N�g�̍Đ���Ԃ��X�V����(�\�t�g����A�N�e�B�u�ɂȂ邱�Ƃ����邽��)
extern	int UpdateKeyboardInputState( int UseProcessMessage = TRUE ) ;				// ���͏�Ԃ̍X�V
extern	int SetupJoypad( void ) ;													// �W���C�p�b�h�̃Z�b�g�A�b�v���s��
extern	int TerminateJoypad( void ) ;												// �W���C�p�b�h�̌�n�����s��

}

#endif // DX_NON_INPUT

#endif // __DXINPUT_H__
