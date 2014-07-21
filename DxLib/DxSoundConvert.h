// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�T�E���h�f�[�^�ϊ��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXSOUNDCONVERT_H__
#define __DXSOUNDCONVERT_H__

// �C���N���[�h ------------------------------------------------------------------

#include "DxCompileConfig.h"
#ifndef DX_NON_ACM
#ifndef DX_GCC_COMPILE
	#include <mmreg.h>
#endif	
	#include <msacm.h>
#endif
#include "DxLib.h"
#include "DxDirectX.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

// �\���̒�` --------------------------------------------------------------------

// RIFF�`�����N�f�[�^
struct ___RIFFCHUNK
{
	DWORD						fcc ;
	DWORD						 cb ;
} ;

// �����^�C�v
#define SOUND_METHODTYPE_NORMAL				(0)		// �ʏ�̏���(���ʂȏ����͋��܂Ȃ�)
#define SOUND_METHODTYPE_ACM				(1)		// �`�b�l���g�p
#define SOUND_METHODTYPE_OGG				(2)		// �n�f�f���g�p
#define SOUND_METHODTYPE_DSMP3				(3)		// �c�����������r���������g�p�����l�o�R�Đ�

// �v�`�u�d�f�[�^�ϊ��p�\����
struct SOUNDCONV_WAVE
{
	BYTE						*SrcBuffer ;		// �ϊ����̃f�[�^
	DWORD						SrcBufferSize ;		// �ϊ����o�b�t�@�̃f�[�^�T�C�Y
	DWORD						SrcSampleNum ;		// �ϊ����o�b�t�@�̃T���v����
	WAVEFORMATEX				SrcFormat ;			// �ϊ����o�b�t�@�̃t�H�[�}�b�g
} ;

#ifndef DX_NON_ACM

#ifdef DX_GCC_COMPILE
struct HACMSTREAM__ { int unused; }; typedef struct HACMSTREAM__ *HACMSTREAM ;
typedef HACMSTREAM *LPHACMSTREAM ;

struct HACMOBJ__ { int unused; }; typedef struct HACMOBJ__ *HACMOBJ ;
typedef HACMOBJ            *PHACMOBJ;
typedef HACMOBJ        FAR *LPHACMOBJ;

typedef struct wavefilter_tag {
    DWORD   cbStruct;           /* Size of the filter in bytes */
    DWORD   dwFilterTag;        /* filter type */
    DWORD   fdwFilter;          /* Flags for the filter (Universal Dfns) */
    DWORD   dwReserved[5];      /* Reserved for system use */
} WAVEFILTER;
typedef WAVEFILTER       *PWAVEFILTER;
typedef WAVEFILTER NEAR *NPWAVEFILTER;
typedef WAVEFILTER FAR  *LPWAVEFILTER;

#define MPEGLAYER3_WFX_EXTRA_BYTES   12
#define WAVE_FORMAT_MPEGLAYER3       0x0055 /* ISO/MPEG Layer3 Format Tag */

#define MPEGLAYER3_ID_UNKNOWN            0
#define MPEGLAYER3_ID_MPEG               1
#define MPEGLAYER3_ID_CONSTANTFRAMESIZE  2

typedef struct mpeglayer3waveformat_tag {
  WAVEFORMATEX  wfx;
  WORD          wID;
  DWORD         fdwFlags;
  WORD          nBlockSize;
  WORD          nFramesPerBlock;
  WORD          nCodecDelay;
} MPEGLAYER3WAVEFORMAT;

typedef MPEGLAYER3WAVEFORMAT          *PMPEGLAYER3WAVEFORMAT;
typedef MPEGLAYER3WAVEFORMAT NEAR    *NPMPEGLAYER3WAVEFORMAT;
typedef MPEGLAYER3WAVEFORMAT FAR     *LPMPEGLAYER3WAVEFORMAT;

#define ACM_STREAMSIZEF_SOURCE          0x00000000L
#define ACM_STREAMSIZEF_DESTINATION     0x00000001L
#define ACM_STREAMSIZEF_QUERYMASK       0x0000000FL

#define ACM_METRIC_MAX_SIZE_FORMAT          50

#define ACM_STREAMCONVERTF_BLOCKALIGN   0x00000004
#define ACM_STREAMCONVERTF_START        0x00000010
#define ACM_STREAMCONVERTF_END          0x00000020

#ifdef  _WIN64
#define _DRVRESERVED    15
#else
#define _DRVRESERVED    10
#endif  // _WIN64

typedef struct tACMSTREAMHEADER
{
    DWORD           cbStruct;               // sizeof(ACMSTREAMHEADER)
    DWORD           fdwStatus;              // ACMSTREAMHEADER_STATUSF_*
    DWORD_PTR       dwUser;                 // user instance data for hdr
    LPBYTE          pbSrc;
    DWORD           cbSrcLength;
    DWORD           cbSrcLengthUsed;
    DWORD_PTR       dwSrcUser;              // user instance data for src
    LPBYTE          pbDst;
    DWORD           cbDstLength;
    DWORD           cbDstLengthUsed;
    DWORD_PTR       dwDstUser;              // user instance data for dst
    DWORD           dwReservedDriver[_DRVRESERVED];   // driver reserved work space

} ACMSTREAMHEADER, *PACMSTREAMHEADER, FAR *LPACMSTREAMHEADER;
#endif

// �`�b�l�f�[�^�ϊ��p�\����
struct SOUNDCONV_ACM
{
	WAVEFORMATEX				*Format ;				// �ϊ����̃t�H�[�}�b�g
	HACMSTREAM					AcmStreamHandle[2]	;	// ���k���ꂽ�f�[�^�������ۂɎg���`�b�l�̃n���h��

	void						*SrcData ;				// �ϊ����̃f�[�^���ꎞ�I�ɕۑ����Ă����������̈�
	int							SrcDataSize ;			// �ϊ����̃f�[�^���ꎞ�I�ɕۑ����Ă����������̈�̃T�C�Y
//	int							SrcDataValidSize ;		// �ϊ����̃f�[�^�̗L���ȃT�C�Y
	int							SrcDataPosition ;		// �ϊ����̃f�[�^�̕ϊ������������T�C�Y
	int							DestDataSampleNum ;		// �ϊ���̃f�[�^�̃T���v����( -1:�ȊO�̏ꍇ�̂ݗL�� )

	int							BeginSeekCompSrcSize ;	// �V�[�N�\��ʒu�܂ŃT�uACM�n���h���ŕϊ����Ă��������ŁA���ɕϊ����������Ă��鈳�k�f�[�^�̃T�C�Y
	int							BeginSeekPosition ;		// �V�[�N�\��ʒu�܂ŃT�uACM�n���h���ŕϊ����Ă��������ŁA���ɕϊ����������Ă���W�J��f�[�^�̃T�C�Y(�V�[�N�\��ʒu�� SOUNDCONV �֐��� SeekLockPosition �����o�[)
	void						*BeginSeekBuffer ;		// �V�[�N�\��ʒu�܂ŃT�uACM�n���h���ŕϊ����Ă��������Ŏg�p����o�b�t�@
} ;

#endif

#ifndef DX_NON_MOVIE
#ifndef DX_NON_DSHOW_MOVIE

// �c�����������r���������g�����l�o�R�f�[�^�ϊ������Ŏg�p����o�b�t�@�N���X
class SOUNDCONV_DSMP3_BUF : public D_ISampleGrabberCB
{
public :
	struct SOUNDCONV			*SoundConvData ;		// �����f�[�^�ϊ������p�\���̂ւ̃|�C���^

	ULONG __stdcall				AddRef() ;
	ULONG __stdcall				Release() ;

	HRESULT __stdcall			QueryInterface( REFIID riid, void ** ppv ) ;
	HRESULT __stdcall			SampleCB( double SampleTime, D_IMediaSample *pSample ) ;
	HRESULT __stdcall			BufferCB( double SampleTime, BYTE *pBuffer, long BufferLen ) ;
} ;

// �c�����������r���������g�����l�o�R�f�[�^�ϊ��p�\����
struct SOUNDCONV_DSMP3
{
	void						*PCMBuffer ;			// �o�b�l�ɕϊ����ꂽ�f�[�^���i�[���郁�����̈�
	DWORD						PCMBufferSize ;			// �o�b�l�o�b�t�@�̃T�C�Y
	DWORD						PCMValidDataSize ;		// �L���Ȃo�b�l�̃T�C�Y
	DWORD						PCMDestCopySize ;		// �{�o�b�t�@�ւ̃R�s�[�����������T�C�Y
} ;

#endif  // DX_NON_DSHOW_MOVIE
#endif	// DX_NON_MOVIE

// �����f�[�^�ϊ������p�\����
struct SOUNDCONV
{
	int							InitializeFlag ;		// ����������Ă���ꍇ�ɗ��t���O
	int							EndFlag ;				// �ϊ����I�������痧�t���O
	
	int 						MethodType ;			// �����^�C�v( SOUND_METHODTYPE_NORMAL �� )
	STREAMDATA 					Stream ;				// �f�[�^�ǂݍ��ݗp�X�g���[���f�[�^

	int							HeaderPos ;				// �w�b�_�̂���ʒu
	int							HeaderSize ;			// �w�b�_�̃T�C�Y
	int							DataPos ;				// ���f�[�^�̂���ʒu
	int							DataSize ;				// ���f�[�^�̃T�C�Y

	WAVEFORMATEX				OutFormat ;				// �ϊ���̃t�H�[�}�b�g

	char						ConvFunctionBuffer[ 1024 ] ;	// MethodType �ʃf�[�^�ۑ��p�o�b�t�@�̈�

	void						*DestData ;				// �ϊ���̃f�[�^���ꎞ�I�ɕۑ����郁�����̈�
	int							DestDataSize ;			// �ϊ���̃f�[�^���ꎞ�I�ɕۑ����郁�����̈�̃T�C�Y
	int							DestDataValidSize ;		// �ϊ���̃f�[�^�̗L���ȃT�C�Y
	int							DestDataCompSize ;		// �ϊ���̃f�[�^���ꎞ�I�ɕۑ����郁�����̈撆�̓]���ς݂̃T�C�Y
	int							DestDataCompSizeAll ;	// �ϊ��J�n���猻�݂Ɏ���܂łɓ]�������f�[�^�̃T�C�Y

	int							SeekLockPosition ;		// �\��V�[�N�ʒu(�`�b�l�^�C�v�Ń��[�v����ꍇ�ׂ̈̃f�[�^)
#ifndef DX_NON_OGGVORBIS
	int							OggVorbisBitDepth ;			// �n�����u�����������g�p���̃r�b�g�[�x(1:8bit 2:16bit)
	int							OggVorbisFromTheoraFile ;	// Ogg Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��邩�ǂ����̃t���O( TRUE:Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��� )
#endif
} ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �������E�I���֐�
extern	int InitializeSoundConvert( void ) ;														// �T�E���h�f�[�^�ϊ������̏��������s��
extern	int TerminateSoundConvert( void ) ;															// �T�E���h�f�[�^�ϊ������̏I���������s��

// �t�H�[�}�b�g�ϊ��p
extern	int SetupSoundConvert( SOUNDCONV *SoundConv, STREAMDATA *Stream, int DisableReadSoundFunctionMask = 0, int OggVorbisBitDepth = 2, int OggVorbisFromTheoraFile = FALSE ) ;	// �ϊ������̃Z�b�g�A�b�v( [��] -1:�G���[ )
//extern	int SetTimeSoundConvert(      SOUNDCONV *SoundConv, int Time ) ;						// �ϊ������̈ʒu��ύX����( �~���b�P�� )
extern	int SetSampleTimeSoundConvert(    SOUNDCONV *SoundConv, int SampleTime ) ;					// �ϊ������̈ʒu��ύX����( �T���v���P�� )
extern	int SetupSeekPosSoundConvert(     SOUNDCONV *SoundConv, int SeekPos ) ;						// �V�[�N�\��̈ʒu���Z�b�g���Ă���(�`�b�l�ׂ̈�)
extern	int RunSoundConvert(              SOUNDCONV *SoundConv, void *DestBuffer, int DestSize ) ;	// �w��̃T�C�Y��������������( [��] -1:�G���[  0�ȏ�:�ϊ������T�C�Y )
extern	int TerminateSoundConvert(        SOUNDCONV *SoundConv ) ;									// �ϊ������̌�n�����s��
extern	int GetOutSoundFormatInfo(        SOUNDCONV *SoundConv, WAVEFORMATEX *OutWaveFormat ) ;		// �ϊ���̉����`�����擾( [��] -1:�G���[  0�ȏ�:�ϊ���̃T�C�Y )
extern	int GetSoundConvertEndState(      SOUNDCONV *SoundConv ) ;									// �ϊ��������I�����Ă��邩�ǂ������擾����( [��] TRUE:�I������  FALSE:�܂��I�����Ă��Ȃ� )
extern	int GetSoundConvertDestSize_Fast( SOUNDCONV *SoundConv ) ;									// �ϊ���̑�}�̃f�[�^�T�C�Y�𓾂�
extern	int SoundConvertFast(             SOUNDCONV *SoundConv, WAVEFORMATEX *FormatP, void **DestBufferP, int *DestSizeP ) ;	// �����Ȉꊇ�ϊ�

}

#endif // __DXSOUNDCONVERT_H__
