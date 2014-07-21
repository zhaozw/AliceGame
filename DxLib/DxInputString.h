// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		��������̓v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXINPUTSTRING_H__
#define __DXINPUTSTRING_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_INPUTSTRING

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#define CHARBUFFER_SIZE				(1024)				// �����R�[�h�o�b�t�@�e��

// �\���̒�` --------------------------------------------------------------------

#ifndef DX_NON_KEYEX

// ��������͒��f�[�^�\����
struct INPUTDATA
{
	int						UseFlag ;							// �g�p�����t���O

	int						ID ;								// �G���[�`�F�b�N�Ɏg�p����h�c

	int						EndFlag ;							// ���͂��I�����Ă��邩�t���O
	int						CancellFlag ;						// ���͂��L�����Z�����ꂽ���̃t���O

//	RECT					DrawRect ;							// �`��̈�

	int						StrLength ;							// ���͒�������̒���
	int						MaxStrLength ;						// ������̍ő咷
	int						SelectStart ;						// �I��͈͊J�n�ʒu
	int						SelectEnd ;							// �I��͈͏I���ʒu
	int						DrawStartPos ;						// �`����J�n����ʒu
	int						Point ;								// �J�[�\���̈ʒu
	TCHAR					*Buffer ;							// ���s���ɕҏW���镶����o�b�t�@
//	char					*DestBuffer ;						// ���͏I�����ɓ]�����镶����o�b�t�@�ւ̃|�C���^

	int						CancelValidFlag ;					// �L�����Z���L���t���O
	int						SingleCharOnlyFlag ;				// �_�u���o�C�g�����͈���Ȃ����t���O
	int						NumCharOnlyFlag ;					// ���p�p���������g��Ȃ����t���O
	int						DoubleCharOnlyFlag ;				// �_�u���o�C�g������������Ȃ����t���O
} ;

#endif // DX_NON_KEYEX

// �����R�[�h�o�b�t�@�\����
struct CHARBUFFER
{
	TCHAR					CharBuffer[ CHARBUFFER_SIZE + 1 ] ;	// ���͂��ꂽ������
	int						StPoint , EdPoint ;					// �����O�o�b�t�@�p�|�C���^

	TCHAR					SecondString[CHARBUFFER_SIZE + 1 ] ;
	int						IMEInputFlag ;						// ���͏��������A�t���O
	int						InputPoint ;						// ���͒��̕ҏW�������̈ʒu
	TCHAR					InputString[ CHARBUFFER_SIZE + 1 ] ;// �h�l�d�ɂ����͒��̕�����
	TCHAR					InputTempString[ CHARBUFFER_SIZE + 1 ] ;// �h�l�d�ɂ����͒��̕�����̃e���|�����o�b�t�@
	PCANDIDATELIST			CandidateList ;						// �ϊ����̃��X�g�f�[�^
	int						CandidateListSize ;					// �ϊ����̃��X�g�f�[�^�ɕK�v�ȃf�[�^�e��
	int						IMEUseFlag ;						// �h�l�d�̎g�p���
	int						IMESwitch ;							// �h�l�d�̋N�����
	int						IMEInputStringMaxLengthIMESync ;	// �h�l�d�œ��͂ł���ő啶������ MakeKeyInput �̍ő吔�ɓ��������邩�ǂ���( TRUE:����������  FALSE:�����Ȃ� )
	int						IMEInputMaxLength ;					// �h�l�d�ň�x�ɓ��͂ł��镶����( 0:���ɐ����Ȃ�  1�ȏ�:���������� )
	int						IMERefreshStep ;					// �h�l�d�̓��͕����񃊃t���b�V���p�X�e�b�v�ϐ�
	IMEINPUTDATA			*IMEInputData ;						// �h�l�d�̓��͒��̏��( ���[�U�[�p )

	int						IMEProcessNum ;						// �h�l�d�̕����擾�v���Z�X�ԍ�
	int						ClauseData[ 1024 ] ;				// ���߃f�[�^
	int						ClauseNum ;							// ���ߐ�
	BYTE					CharAttr[ 1024 ] ;					// �e�����̑������
	int						CharAttrNum ;						// �e�����̑������̗v�f��
	int						ChangeFlag ;						// �h�l�d���͂ɕω������������t���O

	int						StrColor1 ;							// ���͕�����̐F
	int						StrColor2 ;							// �h�l�d���g�p���̃J�[�\���̐F
	int						StrColor3 ;							// �h�l�d�g�p���̓��͕�����̐F
	int						StrColor4 ;							// �h�l�d�g�p���̃J�[�\���̐F
	int						StrColor5 ;							// �h�l�d�g�p���̕ϊ�������̉���
	int						StrColor6 ;							// �h�l�d�g�p���̑I��Ώۂ̕ϊ���╶����̐F
	int						StrColor7 ;							// �h�l�d�g�p���̓��̓��[�h������̐F(�u�S�p�Ђ炪�ȁv��)
	int						StrColor8 ;							// ���͕�����̉��̐F
	int						StrColor9 ;							// �h�l�d�g�p���̑I��Ώۂ̕ϊ���╶����̉��̐F
	int						StrColor10 ;						// �h�l�d�g�p���̓��̓��[�h������̉��̐F
	int						StrColor11 ;						// �h�l�d�g�p���̕ϊ����E�C���h�E�̉��̐F
	int						StrColor12 ;						// �h�l�d�g�p���̕ϊ����E�C���h�E�̉��n�̐F
	int						StrColor13 ;						// �I�����ꂽ���͕�����̔w�i�̐F
	int						StrColor14 ;						// �I�����ꂽ���͕�����̐F
	int						StrColor15 ;						// �I�����ꂽ���͕�����̉��̐F
	
	int						CBrinkFlag ;						// �J�[�\����_�ł����邩�A�t���O
	int						CBrinkCount ;						// �J�[�\����_�ł�����ꍇ�̃J�E���^
	int						CBrinkWait ;						// �J�[�\���̓_�ł̑��x
	int						CBrinkDrawFlag ;					// �J�[�\����`�悷�邩�ǂ����̃t���O

	int						ActiveInputHandle ;					// ���͂��A�N�e�B�u�ɂȂ��Ă�����̓n���h��
	int						UseFontHandle ;						// ������`��Ɏg�p����t�H���g�̃n���h��(-1�Ńf�t�H���g�̃n���h��)
#ifndef DX_NON_KEYEX
	INPUTDATA				InputData[ MAX_INPUT_NUM ] ;		// �C���v�b�g�f�[�^
	int						HandleID ;							// �n���h���Ɋ��蓖�Ă�h�c
#endif
} ;

// ���̓��[�h�\����
struct INPUTMODE
{
	DWORD					InputState ;						// ���̓��[�h�l
	TCHAR					InputName[ 16 ] ;					// ���̓��[�h�l�[��
} ;

// �e�[�u��-----------------------------------------------------------------------

// ���z�L�[�R�[�h���R���g���[�������R�[�h�ɕϊ����邽�߂̃e�[�u��
extern char CtrlCode[ 10 ][ 2 ] ;

// �������ϐ��錾 --------------------------------------------------------------

// ��������̓f�[�^
extern CHARBUFFER CharBuf ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �����R�[�h�o�b�t�@����֌W
extern	int			InitializeInputCharBuf( void ) ;										// �����R�[�h�o�b�t�@�֌W�̏�����
#ifndef DX_NON_KEYEX
extern	LRESULT		IMEProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) ;			// �h�l�d���b�Z�[�W�̃R�[���o�b�N�֐�
#endif

}

#endif // DX_NON_INPUTSTRING

#endif // __DXINPUTSTRING_H__
