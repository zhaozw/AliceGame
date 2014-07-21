// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		����v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXMOVIE_H__
#define __DXMOVIE_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_MOVIE

// �C���N���[�h ------------------------------------------------------------------
#include "DxHandle.h"
#include "DxGraphics.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// Ogg Theora �̃f�R�[�h���̏��
struct THEORADECODE_INFO
{
	double						FrameRate ;						// �P�b�ԕӂ�̃R�}��
	int							TotalFrame ;					// ���t���[����
	int							Width, Height ;					// ���ƍ���
} ;

// ���[�r�[�O���t�B�b�N�f�[�^�^
struct MOVIEGRAPH
{
	HANDLEINFO				HandleInfo ;					// �n���h�����ʃf�[�^

	int						PlayType ;						// �Đ��^�C�v

#ifndef DX_NON_OGGTHEORA
	int						TheoraFlag ;					// Theora ���g�p���Ă��邩�ǂ����̃t���O( 1:�g�p���Ă���  0:�g�p���Ă��Ȃ� )
	DWORD_PTR				TheoraHandle ;					// Theora �t�@�C���n���h��
	LONGLONG				TheoraPlayTime ;				// �Đ��J�n����
	DWORD_PTR				TheoraStreamData ;				// �X�g���[�������p�f�[�^
#ifndef DX_NON_SOUND
	int						TheoraVorbisHandle ;			// Vorbis�p�n���h��
#endif // DX_NON_SOUND
#endif // DX_NON_OGGTHEORA

	RECT					SrcRect ;						// �u���b�N�]������̓]������`

#ifndef DX_NON_DSHOW_MOVIE
	D_IGraphBuilder			*pGraph ;						// �t�B���^�O���t�}�l�[�W��
	D_IMediaControl			*pMediaControl ;				// ���f�B�A�R���g���[��
	D_IMediaSeeking			*pMediaSeeking ;				// ���f�B�A�V�[�L���O
	D_IBasicAudio			*pBasicAudio ;					// BasicAudio �C���^�[�t�F�C�X

//	D_ISampleGrabber		*SampleGrabber ;				// �T���v���O���b�o�I�u�W�F�N�g

	D_CMovieRender			*pMovieImage ;					// ����̃C���[�W

	D_IBaseFilter			*pFilter ;						// BaseFilter �C���^�[�t�F�C�X
	D_IVMRSurfaceAllocator9	*pAllocator ;					// VMR9�T�[�t�F�X�A���P�[�^

	D_STREAM_TIME			FrameTime ;						// �P�t���[��������̎���
	D_STREAM_TIME			OldTime ;						// �O��`�掞�̎���
	D_STREAM_TIME			StartTime ;						// �Đ��J�n����

	D_STREAM_TIME			BackUpTime ;					// �Đ����~�߂�����
	int						UseTemporaryFile ;				// �e���|�����t�@�C�����g�p���Ă��邩�ǂ����A�t���O
	wchar_t					FileName[ MAX_PATH ] ;			// �t�@�C���l�[��
#endif // DX_NON_DSHOW_MOVIE
	LONGLONG				RefreshFrame ;					// �O��X�V�����t���[��
	int						RefreshTime ;					// �O��X�V��������

	LONGLONG				StopTime ;						// �I���^�C��
	int						SufIsSystemMemory ;				// �T�[�t�F�X���V�X�e����������ɂ���ꍇ�s�q�t�d
	int						Width, Height ;					// ���[�r�[�O���t�B�b�N�̃T�C�Y
	int						RightAlpha ;					// ���[�r�[�̉E�����A���t�@�`�����l���Ƃ��Ĉ�����(TRUE:����)
	int						PlayFlag ;						// �Đ����t���O
	int						SysPauseFlag ;					// �����ꎞ��~�t���O
	int						FirstUpdateFlag ;				// �ŏ��̃A�b�v�f�[�g���s��ꂽ���ǂ���( TRUE:�s��ꂽ  FALSE:�܂� )

	int						YUVFlag ;						// �x�t�u�`�����g�p���Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )
	int						SurfaceMode ;					// �g�p���Ă���T�[�t�F�X�^�C�v


	HANDLE					RefreshEvent ;					// �X�V�C�x���g
	int						RefreshEventFlag ;				// �X�V�C�x���g���������A�t���O

	BASEIMAGE				NowImage ;
	int						NowImageGraphOutAlloc ;			// NowImage �� GraphData ���O���Ŋm�ۂ��ꂽ�o�b�t�@���g�p���Ă��邩�ǂ���
	BASEIMAGE				*UseNowImage ;					// Theora ���� BASEIMAGE ���g�p���Ă���\��������̂ŊO���̃v���O�����͂�������g���ׂ�
	int						OverlayDestX, OverlayDestY ;	// �Ō�ɐݒ肳�ꂽ�I�[�o�[���C�T�[�t�F�X�̏o�͈ʒu
	int						OverlayDestExRate ;				// �Ō�ɐݒ肳�ꂽ�I�[�o�[���C�T�[�t�F�X�̏o�͔{��
	int						OverlayDispFlag ;				// �Ō�ɐݒ肳�ꂽ�I�[�o�[���C�T�[�t�F�X�̕\���t���O
	RECT					OverlaySrcRect, OverlayDestRect ;// �Ō�ɃZ�b�g���ꂽ�I�[�o�[���C�\�[�X��`�Əo�͋�`

	void					( *UpdateFunction )( struct MOVIEGRAPH *Movie, void *Data ) ;		// ����X�V���ɌĂԃR�[���o�b�N�֐�
	void					*UpdateFunctionData ;												// �R�[���o�b�N�֐��ɓn���|�C���^
} ;

// ���[�r�[�f�[�^�Ǘ��\����
struct MOVIEGRAPHMANAGE
{
	int						InitializeFlag ;				// �������t���O

	int						RightAlphaFlag;					// ���摜�̉E�����A���t�@�Ƃ݂Ȃ�����n���h�����쐬���邩(TRUE:�쐬����)
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int		InitializeMovieManage( void ) ;																		// ���[�r�[�֘A�̊Ǘ������̏�����
extern	int		TerminateMovieManage( void ) ;																		// ���[�r�[�֘A�̊Ǘ������̌�n��

extern	int		OpenMovie_UseGParam( OPENMOVIE_GPARAM *GParam, const TCHAR *FileName, int *Width, int *Height, int SurfaceMode, int ASyncThread = FALSE ) ;	// OpenMovie �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		OpenMovie( const TCHAR *FileName, int *Width, int *Height, int SurfaceMode ) ;						// ���[�r�[���J��
extern	int		CloseMovie( int MovieHandle ) ;																		// ���[�r�[�����
extern 	int		PlayMovie_( int MovieHandle, int PlayType = DX_PLAYTYPE_BACK, int SysPlay = 0 ) ;					// ���[�r�[�̍Đ����J�n����
extern 	int		PauseMovie( int MovieHandle, int SysPause = 0 ) ;													// ���[�r�[�̍Đ����X�g�b�v����
extern	int		AddMovieFrame( int MovieHandle, unsigned int FrameNum ) ;											// ���[�r�[�̃t���[����i�߂�A�߂����Ƃ͏o���Ȃ�( ���[�r�[����~��ԂŁA���� Ogg Theora �̂ݗL�� )
extern	int		SeekMovie( int MovieHandle, int Time ) ;															// ���[�r�[�̍Đ��ʒu��ݒ肷��(�~���b�P��)
extern 	int		GetMovieState( int MovieHandle ) ;																	// ���[�r�[�̍Đ���Ԃ𓾂�
extern	int		SetMovieVolume( int Volume, int MovieHandle ) ;														// ���[�r�[�̃{�����[�����Z�b�g����(0�`10000)
extern	BASEIMAGE *GetMovieBaseImage( int MovieHandle ) ;															// ���[�r�[�̊�{�C���[�W�f�[�^���擾����
extern	int		GetMovieTotalFrame( int MovieHandle ) ;																// ���[�r�[�̑��t���[�����𓾂�( Ogg Theora �ł̂ݗL�� )
extern	int		TellMovie( int MovieHandle ) ;																		// ���[�r�[�̍Đ��ʒu���擾����(�~���b�P��)
extern	int		TellMovieToFrame( int MovieHandle ) ;																// ���[�r�[�̍Đ��ʒu���擾����(�t���[���P��)
extern	int		SeekMovieToFrame( int MovieHandle, int Frame ) ;													// ���[�r�[�̍Đ��ʒu��ݒ肷��(�t���[���P��)
extern	LONGLONG GetOneFrameTimeMovie( int MovieHandle ) ;															// ���[�r�[�̂P�t���[��������̎��Ԃ𓾂�
extern	MOVIEGRAPH *GetMovieData( int MovieHandle ) ;																// ���[�r�[�O���t�B�b�N�̃f�[�^���擾����

extern	int		SetCallbackMovie( int MovieHandle, void ( *Callback )( MOVIEGRAPH *Movie, void *Data ), void *Data );	// ���[�r�[�̍X�V���ɌĂяo���R�[���o�b�N�֐���o�^����
extern	int		UpdateMovie( int MovieHandle, int AlwaysFlag = FALSE ) ;											// ���[�r�[�̍X�V���s��
extern	int		ReleaseMovieSurface( int MovieHandle ) ;															// ���[�r�[�Ŏg�p���Ă���T�[�t�F�X�̉�����s��

extern	int		DisableMovieAll( void ) ;																			// ���[�r�[�̍Đ���Ԃ��~����
extern	int		RestoreMovieAll( void ) ;																			// ���[�r�[�̍Đ���Ԃ��Đ�����

extern 	int		PlayMovieAll( void ) ;																				// ���ׂẴ��[�r�[�O���t�B�b�N���X�^�[�g
extern 	int		PauseMovieAll( void ) ;																				// ���ׂẴ��[�r�[�O���t�B�b�N���X�g�b�v

extern	int		InitializeMovieHandle( HANDLEINFO *HandleInfo ) ;													// ���[�r�[�n���h����������������֐�
extern	int		TerminateMovieHandle( HANDLEINFO *HandleInfo ) ;													// ���[�r�[�n���h���̌�n�����s���֐�

#ifndef DX_NON_DSHOW_MOVIE
extern	D_CMovieRender *New_D_CMovieRender( IUnknown * pUnk, HRESULT *phr ) ;
#endif 

}

#endif // DX_NON_MOVIE

#endif // __DXMOVIE_H__
