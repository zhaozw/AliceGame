// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�T�E���h�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXSOUND_H__
#define __DXSOUND_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h ------------------------------------------------------------------
#include "DxLib.h"
#include "DxStatic.h"
#include "DxRingBuffer.h"
#include "DxSoundConvert.h"
#include "DxHandle.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#define MAX_SOUNDBUFFER_NUM			(10)				// DIRECTSOUNDBUFFER �o�b�t�@�̍ő吔
#define STS_SETSOUNDNUM				(4)					// �X�g���[�����T�E���h�Đ��ɓo�^�ł���T�E���h�̐�

#define D_X3DAUDIO_INPUTCHANNELS	(8)					// X3DAudio �̌v�Z�Ŏg�p����ő���̓`�����l����

// �\���̒�` --------------------------------------------------------------------

// �t�@�C������T�E���h�n���h�����쐬���鏈���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct LOADSOUND_GPARAM
{
	int						Create3DSoundFlag ;						// 3D�T�E���h���쐬���邩�ǂ����̃t���O( TRUE:�R�c�T�E���h���쐬����  FALSE:�R�c�T�E���h���쐬���Ȃ� )
	int						CreateSoundDataType ;					// �쐬����T�E���h�f�[�^�̃f�[�^�^�C�v
	int						DisableReadSoundFunctionMask ;			// �g�p���Ȃ��ǂݍ��ݏ����̃}�X�N
#ifndef DX_NON_OGGVORBIS
	int						OggVorbisBitDepth ;						// �n�����u�����������g�p���̃r�b�g�[�x(1:8bit 2:16bit)
	int						OggVorbisFromTheoraFile ;				// Ogg Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��邩�ǂ����̃t���O( TRUE:Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��� )
#endif
} ;

// �T�E���h�o�b�t�@�����b�N�����ۂɎg�p����f�[�^�^
struct SOUNDBUFFERLOCKDATA
{
	DWORD						StartOffst ;
	BYTE						*WriteP, *WriteP2 ;
	DWORD						Length, Length2 ;
	DWORD						Offset, Offset2 ;
	DWORD						Valid, Valid2 ;
} ;

// �g�`�f�[�^�\����
struct WAVEDATA
{
	void						*Buffer ;				// �g�`�f�[�^
	int							Bytes ;					// �T�C�Y
	int							RefCount ;				// �Q�Ɛ�
} ;

// XAudio2�p�R�[���o�b�N�����p�\����
struct SOUNDBUFFER_CALLBACK : public D_IXAudio2VoiceCallback
{
	virtual void    __stdcall OnVoiceProcessingPassStart( DWORD BytesRequired ) ;
	virtual void    __stdcall OnVoiceProcessingPassEnd	() ;
	virtual void    __stdcall OnStreamEnd				() ;
	virtual void    __stdcall OnBufferStart				( void* pBufferContext ) ;
	virtual void    __stdcall OnBufferEnd				( void* pBufferContext ) ;
	virtual void    __stdcall OnLoopEnd					( void* pBufferContext ) ;
	virtual void    __stdcall OnVoiceError				( void* pBufferContext, HRESULT Error ) ;

	struct SOUNDBUFFER			*Buffer ;
} ;

// �T�E���h�o�b�t�@�\����
struct SOUNDBUFFER
{
	int							Valid ;					// �f�[�^���L�����ۂ�(TRUE:�L�� FALSE:����)

	union
	{
		D_IDirectSoundBuffer 		*DSBuffer ;				// DirectSoundBuffer
		D_IXAudio2SourceVoice		*XA2SourceVoice ;		// XAudio2SourceVoice
		D_IXAudio2_8SourceVoice		*XA2_8SourceVoice ;		// XAudio2_8SourceVoice
	} ;
	union
	{
		D_IXAudio2SubmixVoice		*XA2SubmixVoice ;		// XAudio2SubmixVoice
		D_IXAudio2_8SubmixVoice		*XA2_8SubmixVoice ;		// XAudio2_8SubmixVoice
	} ;
	IUnknown					*XA2ReverbEffect ;		// ���o�[�u�G�t�F�N�g
	SOUNDBUFFER_CALLBACK		*XA2Callback ;			// XAudio2�p�̃R�[���o�b�N

	// DirectSound �ȊO�̏ꍇ�Ɏg�p
	WAVEDATA					*Wave ;					// �g�`�f�[�^�o�b�t�@
	int							State ;					// �Đ����( TRUE:�Đ���  FALSE:��~�� )
	int							Pos ;					// �Đ��ʒu
	int							CompPos ;				// �]�������������ʒu
	int							Loop ;					// ���[�v���邩�ǂ���( TRUE:���[�v����  FALSE:���[�v���Ȃ� )
	int							Pan ;					// �p��( 10000:��100%�E0%  0:���E100%  -100000:�E100% )
	int							Volume ;				// �{�����[��( 10000:100%  0:0% )
	int							Frequency ;				// �Đ����g��( -1:�f�t�H���g )
	int							SampleNum ;				// �T���v���̐�
	WAVEFORMATEX				Format ;				// �o�b�t�@�̃t�H�[�}�b�g
	int							CalcPan ;				// �L���v�`���p�Ɍv�Z������̃p��( 256:��100%�E0%  0:���E100%  -256:�E100% )
	int							CalcVolume ;			// �L���v�`���p�Ɍv�Z������̃{�����[��( 256:100%  0:0% )
} ;

// �X�g���[�����T�E���h�v���C�p�t�@�C���f�[�^
struct STREAMFILEDATA
{
	char						LoopNum ;					// ���[�v��( -1:�������[�v )
	int							DataType ;					// �f�[�^�̃^�C�v( DX_SOUNDDATATYPE_MEMNOPRESS �� )
	void						*FileImage ;				// ��������ɓW�J�����t�@�C���C���[�W( DX_SOUNDDATATYPE_FILE �ȊO�Ŏg�p )
	int							FileImageSize ;				// ��������ɓW�J�����t�@�C���C���[�W�̃T�C�Y( DX_SOUNDDATATYPE_FILE �ȊO�Ŏg�p )
	STREAMDATA					MemStream ;					// �������X�g���[�������p�f�[�^( DX_SOUNDDATATYPE_FILE �ȊO�Ŏg�p )
	int							LoopSamplePosition ;		// ���[�v��̍Đ��ʒu(�T���v���P�ʁAOGG �� �����kWAV �̂ݗL�� )
	int							LoopStartSamplePosition ;	// ���[�v���J�n����Đ��ʒu(�T���v���P�ʁAOGG �� �����kWAV �̂ݗL�� )
	
	SOUNDCONV					ConvData ;					// �t�H�[�}�b�g�ϊ������p�f�[�^
} ;

// �X�g���[�����T�E���h�v���C�p�f�[�^
struct STREAMPLAYDATA
{
	int							BufferBorrowSoundHandle ;								// DirectSoundBuffer ��݂�Ă���T�E���h�n���h��(-1:�؂�Ă��Ȃ�)
	int							BufferBorrowSoundHandleCount ;							// DirectSoundBuffer ��݂��Ă��鐔(0:�݂��Ă��Ȃ�)
	int							BufferUseSoundHandle ;									// DirectSoundBuffer �����ݎg�p���Ă���T�E���h�n���h��(-1:�N�����͎g���Ă��Ȃ�)
	int							DeleteWaitFlag ;										// DirectSoundBuffer ��݂��Ă��邩��폜�ł��Ȃ��ŋ���̂��A�t���O
	
	BYTE						*SoundBuffer ;											// �T�E���h�o�b�t�@( XAudio2�p )
	DWORD						SoundBufferSize ;										// DirectSoundBuffer �̃T�C�Y( �P�ʂ̓o�C�g )
	int							SoundBufferCompCopyOffset ;								// �O��̃T�E���h�f�[�^�R�s�[�œ]�������������T�E���h�f�[�^�̈�̖��[�I�t�Z�b�g
	int							SoundBufferCopyStartOffset ;							// �w�����܂ł����玟�̃T�E���h�f�[�^�R�s�[���J�n����x�Ƃ����f�[�^�I�t�Z�b�g

	STREAMFILEDATA				File[ STS_SETSOUNDNUM ] ;								// �X�g���[���t�@�C���f�[�^
	BYTE						FileLibraryLoadFlag[ STS_SETSOUNDNUM ] ;				// ���C�u���������[�h�����f�[�^���ǂ���
	int							FileNum ;												// �X�g���[���t�@�C���f�[�^�̐�
	int							FileActive ;											// �A�N�e�B�u�ȃX�g���[���t�@�C���f�[�^�ԍ�
	int							FileLoopCount ;											// ���݃A�N�e�B�u�ȃX�g���[���f�[�^�����[�v������
	int							FileCompCopyLength ;									// ���݃A�N�e�B�u�ȃX�g���[���f�[�^���̃T�E���h�o�b�t�@�ւ̓]�������������o�C�g��
	int							TotalSample ;											// �S�X�g���[���̃T���v������

	DWORD						CompPlayWaveLength ;									// �Đ����I������g�`�f�[�^�̒���
	DWORD						PrevCheckPlayPosition ;									// �O��`�F�b�N�����Đ��ʒu

	BYTE						StartSetupCompFlag ;									// �Đ����������t���O
	BYTE						EndWaitFlag ;											// �I���҂����t���O
	BYTE						LoopPositionValidFlag ;									// ���[�v�ʒu���L���t���O
	BYTE						AllPlayFlag ;											// �S�̂�ʂ��Ĉ�x�ł��Ō�ł��Đ��������t���O
	DWORD						LoopAfterCompPlayWaveLength ;							// ���[�v��� CompPlayWaveLength �ɉ��Z����l
	
	DWORD						EndOffset ;												// �I���I�t�Z�b�g
	DWORD						EndStartOffset ;										// �I�������J�n�I�t�Z�b�g
	DWORD						LoopPosition ;											// ���[�v�ʒu(�Đ��o�b�t�@���̃A�h���X)

	HANDLELIST					StreamSoundList ;										// �X�g���[���T�E���h���X�g�����p�\����
} ;

// �m�[�}���T�E���h�v���C�p�f�[�^
struct NORMALPLAYDATA
{
	int							WaveSize ;												// �g�`�f�[�^�̃T�C�Y
	void						*WaveData ;												// �g�`�f�[�^
	int							*WaveDataUseCount ;										// �g�`�f�[�^�Q�Ɛ�
	int							BufferDuplicateFlag[ MAX_SOUNDBUFFER_NUM ] ;			// �������ꂽ�T�E���h�o�b�t�@���ǂ����̃t���O
	int							ValidBufferNum ;										// �L���ȃo�b�t�@�̐�
	int							BackPlayBufferNo ;										// ��O�ɍĐ������T�E���h�o�b�t�@�̔ԍ�(�Đ��p�o�b�t�@����������ꍇ�p)
} ;

// �R�c�T�E���h�f�[�^�̊�{�I�ȏ��
struct _3DSOUNDINFO
{
	VECTOR						Position ;				// �ʒu
	VECTOR						FrontDirection ;		// �O������
	VECTOR						UpDirection ;			// �����
	VECTOR						Velocity ;				// �ړ����x
	float						InnerAngle ;			// �����p�x
	float						OuterAngle ;			// ���O�p�x
	float						InnerVolume ;			// �����p�x�ł̉��ʃX�P�[��
	float						OuterVolume ;			// ���O�p�x�ł̉��ʃX�P�[��
} ;

// �T�E���h�f�[�^
struct SOUND
{
	HANDLEINFO					HandleInfo ;											// �n���h�����ʏ��

	HANDLELIST					_3DSoundList ;											// �R�c�T�E���h���X�g�����p�\����
	int							Is3DSound ;												// �R�c�T�E���h���ǂ���( TRUE:�R�c�T�E���h  FALSE:��R�c�T�E���h )
	D_X3DAUDIO_EMITTER			X3DAudioEmitterData ;									// �R�c�T�E���h�p�������
	D_X3DAUDIO_CONE				X3DAudioEmitterConeData ;								// �R�c�T�E���h�p�������Ŏg�p����R�[�����
	float						X3DAudioEmitterChannelAzimuths[ D_X3DAUDIO_INPUTCHANNELS ] ;	// �R�c�T�E���h�p�������Ŏg�p����`�����l���ʒu�e�[�u��
	_3DSOUNDINFO				EmitterInfo ;											// �R�c�T�E���h�p�̏��
	float						EmitterRadius ;											// �R�c�T�E���h�p�����̉����͂�����
	int							EmitterDataChangeFlag ;									// �R�c�T�E���h�p������񂪕ύX���ꂽ���ǂ���( TRUE:�ύX���ꂽ  FALSE:�ύX����Ă��Ȃ� )

//	char						FilePath[ 256 ] ;										// �f�B���N�g��
//	char						SoundName[ 256 ] ;										// �T�E���h�t�@�C���l�[��

	int							BufferPlayStateBackupFlagValid[ MAX_SOUNDBUFFER_NUM ] ;	// BufferPlayStateBackupFlag ���L�����ǂ����̃t���O( TRUE:�L��  FALSE:���� )
	int							BufferPlayStateBackupFlag[ MAX_SOUNDBUFFER_NUM ] ;		// �T�E���h�o�b�t�@���ꎞ��~����Ƃ��̍Đ���ԃt���O
	SOUNDBUFFER					Buffer[ MAX_SOUNDBUFFER_NUM ] ;							// �T�E���h�o�b�t�@
	WAVEFORMATEX				BufferFormat ;											// �T�E���h�o�b�t�@�̃t�H�[�}�b�g

	int							Type ;													// �T�E���h�̃^�C�v
	int							PlayType ;												// �Đ��^�C�v
	
	STREAMPLAYDATA				Stream ;												// �X�g���[�����T�E���h�v���C�p�f�[�^
	NORMALPLAYDATA				Normal ;												// �m�[�}���T�E���h�v���C�p�f�[�^

	int							BaseVolume ;											// ��{�{�����[��( -1:�f�t�H���g )
	int							BasePan ;												// ��{�p��( -1:�f�t�H���g )
	int							BaseFrequency ;											// ��{�Đ����g��( -1:�f�t�H���g )

	BYTE						ValidNextPlayVolume ;									// NextPlayVolume ���L�����ǂ���( 1:�L�� 0:���� )
	BYTE						ValidNextPlayPan ;										// NextPlayPan ���L�����ǂ���( 1:�L�� 0:���� )
	BYTE						ValidNextPlayFrequency ;								// NextPlayFrequency ���L�����ǂ���( 1:�L�� 0:���� )
	int							NextPlayVolume ;										// ���ɖ炷���̃{�����[��
	int							NextPlayPan ;											// ���ɖ炷���̃p��
	int							NextPlayFrequency ;										// ���ɖ炷���̎��g��
} ;

// �\�t�g�E�G�A�ň����g�`�f�[�^�̔g�`�f�[�^�\����
struct SOFTSOUND_WAVE
{
	int							BufferSampleNum ;										// �o�b�t�@�̃T�C�Y( �T���v���� )
	void						*Buffer ;												// �f�[�^�o�b�t�@
} ;

// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�\����
struct SOFTSOUND_PLAYER
{
	HANDLELIST					SoftSoundPlayerList ;									// �\�t�g�E�G�A�T�E���h�v���C���[���X�g�����p�\����

	int							StockSampleNum ;										// �X�g�b�N���Ă���T���v���̐�
	RINGBUF						StockSample ;											// �T���v���X�g�b�N�p�����O�o�b�t�@

	int							SoundBufferPlayStateBackupFlagValid ;					// SoundBufferPlayStateBackupFlag ���L�����ǂ����̃t���O( TRUE:�L��  FALSE:���� )
	int							SoundBufferPlayStateBackupFlag ;						// �T�E���h�o�b�t�@���ꎞ��~����Ƃ��̍Đ���ԃt���O
	SOUNDBUFFER					SoundBuffer ;											// �Đ��p�T�E���h�o�b�t�@
	int							SoundBufferSize ;										// �Đ��p�T�E���h�o�b�t�@�̃T�C�Y( �o�C�g�P�� )
//	int							BackCheckPlayOffset ;									// ��O�Ƀ`�F�b�N�����Đ��ʒu
	int							DataSetCompOffset ;										// �f�[�^�Z�b�g���ς�ł���T�E���h�o�b�t�@��̈ʒu( -1:�܂��Z�b�g���Ă��Ȃ� )

	int							NoneDataSetCompOffset ;									// �����f�[�^�̃Z�b�g���J�n�����T�E���h�o�b�t�@��̈ʒu( -1:�܂��Z�b�g���Ă��Ȃ� )
	int							NoneDataPlayCheckBackPlayOffset ;						// �����f�[�^�̍Đ����J�n�����������o���邽�߂̑O��`�F�b�N���̍Đ��ʒu
	int							NoneDataPlayStartFlag ;									// �����f�[�^�̍Đ����J�n���Ă��邩�ǂ����t���O( TRUE:���Ă���  FALSE:���Ă��Ȃ� )

	int							MaxDataSetSize ;										// �Đ��ʒu�ɐ�s���ăZ�b�g����ő�f�[�^�T�C�Y�A�o�C�g�P��( ��s���ăZ�b�g���Ă���f�[�^�̃T�C�Y�����̃T�C�Y�ȏ�ɂȂ�Ȃ��悤�ɂ��� )
	int							MinDataSetSize ;										// �Đ��ʒu�ɐ�s���ăZ�b�g����ŏ��f�[�^�T�C�Y�A�o�C�g�P��( ��s���ăZ�b�g���Ă���f�[�^�̃T�C�Y�����̃T�C�Y�ȉ��ɂȂ�Ȃ��悤�ɂ��� )

	int							IsPlayFlag ;											// �Đ������ǂ����̃t���O( TRUE:�Đ���   FALSE:��~�� )
} ;

// �\�t�g�E�G�A�ň����g�`�f�[�^
struct SOFTSOUND
{
	HANDLEINFO					HandleInfo ;											// �n���h�����ʏ��

	int							IsPlayer ;												// �v���C���[���ǂ����̃t���O( TRUE:�v���C���[  FALSE:�T�E���h�f�[�^ )
	WAVEFORMATEX				BufferFormat ;											// �T�E���h�̃t�H�[�}�b�g

	union
	{
		SOFTSOUND_WAVE			Wave ;													// �g�`�f�[�^
		SOFTSOUND_PLAYER		Player ;												// �v���C���[
	} ;
} ;


// �c�����������r���������f�[�^�\���̒�`
struct DIRECTSOUNDDATA
{
	int							InitializeFlag ;				// �������t���O

	D_IDirectMusicLoader8		*DirectMusicLoaderObject ;		// DirectMusicLoader8 �I�u�W�F�N�g
	D_IDirectMusicPerformance8	*DirectMusicPerformanceObject ;	// DirectMusicPerformance8 �I�u�W�F�N�g

	HMODULE						XAudio2_8DLL ;					// XAudio2_8.dll
	HRESULT						( WINAPI *XAudio2CreateFunc )( D_IXAudio2_8 ** ppXAudio2, DWORD Flags, D_XAUDIO2_PROCESSOR XAudio2Processor );
	HRESULT						( WINAPI *CreateAudioVolumeMeterFunc )( IUnknown** ppApo ) ;
	HRESULT						( WINAPI *CreateAudioReverbFunc )( IUnknown** ppApo ) ;

	HMODULE						X3DAudioDLL ;					// X3DAudio.dll
	void						( __cdecl *X3DAudioInitializeFunc )( DWORD SpeakerChannelMask, float SpeedOfSound, D_X3DAUDIO_HANDLE Instance ) ;
	void						( __cdecl *X3DAudioCalculateFunc )( const D_X3DAUDIO_HANDLE Instance, const D_X3DAUDIO_LISTENER* pListener, const D_X3DAUDIO_EMITTER* pEmitter, DWORD Flags, D_X3DAUDIO_DSP_SETTINGS* pDSPSettings ) ;

	union
	{
		D_IXAudio2				*XAudio2Object ;				// XAudio2�I�u�W�F�N�g
		D_IXAudio2_8			*XAudio2_8Object ;				// XAudio2_8�I�u�W�F�N�g
		D_IDirectSound			*DirectSoundObject ;			// �c�����������r���������I�u�W�F�N�g
	} ;

	D_XAUDIO2FX_REVERB_PARAMETERS    XAudio2ReverbParameters[ D_XAUDIO2FX_PRESET_NUM ] ;	// ���o�[�u�v�Z�p�p�����[�^
	D_XAUDIO2FX_REVERB_PARAMETERS2_8 XAudio2_8ReverbParameters[ D_XAUDIO2FX_PRESET_NUM ] ;	// ���o�[�u�v�Z�p�p�����[�^XAudio2.8�p
	D_IXAudio2MasteringVoice	*XAudio2MasteringVoiceObject ;	// XAudio2MasteringVoice�I�u�W�F�N�g
	D_IXAudio2_8MasteringVoice	*XAudio2_8MasteringVoiceObject ;// XAudio2_8MasteringVoice�I�u�W�F�N�g
	D_XAUDIO2_EFFECT_CHAIN		XAudio2MasteringEffectChain ;	// �}�X�^�[�{�C�X�p�̃G�t�F�N�g�`�F�C��

	DWORD						XAudio2OutputChannelMask ;		// �o�̓`�����l���}�X�N
	DWORD						OutputChannels ;				// �o�̓`�����l����
	DWORD						OutputSmaplesPerSec ;			// �o�̓T���v�����O���[�g

	int							_3DSoundOneMetreEnable ;		// _3DSoundOneMetre ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	float						_3DSoundOneMetre ;				// �R�c�T�E���h�����p�̂P���[�g��
	D_X3DAUDIO_HANDLE			X3DAudioInstance ;				// �R�c�T�E���h�v�Z�p�C���X�^���X�n���h��
	D_X3DAUDIO_CONE				X3DAudioListenerConeData ;		// �R�c�T�E���h�̃��X�i�[���Ɏg�p����R�[�����
	D_X3DAUDIO_LISTENER			X3DAudioListenerData ;			// �R�c�T�E���h�̃��X�i�[���
	_3DSOUNDINFO				ListenerInfo ;					// �R�c�T�E���h�̃��X�i�[�̏��
	VECTOR						ListenerSideDirection ;			// �R�c�T�E���h�̃��X�i�[�̉�����

	D_IDirectSoundBuffer		*PrimarySoundBuffer ;			// �v���C�}���T�E���h�o�b�t�@
	D_IDirectSoundBuffer		*BeepSoundBuffer ;				// �r�[�v���p�o�b�t�@

	HANDLELIST					_3DSoundListFirst ;				// �R�c�T�E���h�n���h�����X�g�̐擪
	HANDLELIST					_3DSoundListLast ;				// �R�c�T�E���h�n���h�����X�g�̏I�[

	HANDLELIST					StreamSoundListFirst ;			// �X�g���[���T�E���h�n���h�����X�g�̐擪
	HANDLELIST					StreamSoundListLast ;			// �X�g���[���T�E���h�n���h�����X�g�̏I�[

	HANDLELIST					SoftSoundPlayerListFirst ;		// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̃n���h�����X�g�̐擪
	HANDLELIST					SoftSoundPlayerListLast ;		// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̃n���h�����X�g�̏I�[

	int							PlayWavSoundHandle ;			// PlayWav�֐��Ŗ炳��Ă���WAVE�f�[�^�̃n���h��
	D_IDirectSoundBuffer		*NoSoundBuffer ;				// �����o�b�t�@

	int							DisableXAudioFlag ;				// XAudio���g�p���Ȃ����ǂ����̃t���O( TRUE:�g�p���Ȃ�  FALSE:�g�p���� ) 
	int							Create3DSoundFlag ;				// 3D�T�E���h���쐬���邩�ǂ����̃t���O( TRUE:�R�c�T�E���h���쐬����  FALSE:�R�c�T�E���h���쐬���Ȃ� )
	int							SoundMode ;						// �Đ��`��

	int							MaxVolume ;						// �ő剹��
	int							UseSoftwareMixing ;				// �\�t�g�E�G�A�~�L�V���O���s�����ǂ����̃t���O( TRUE:�\�t�g�E�G�A  FALSE:�n�[�h�E�G�A )

	int							EnableSoundCaptureFlag ;		// �T�E���h�L���v�`����O��Ƃ������������
	int							SoundCaptureFlag ;				// �T�E���h�L���v�`�������s���Ă���Œ����ǂ����̃t���O(TRUE:�Œ� FASLE:�Ⴄ)
	int							SoundCaptureSample ;			// �L���v�`�������T���v���̐�(44.1KHz���Z)
	HANDLE						SoundCaptureFileHandle ;		// �L���v�`�������T�E���h��ۑ����Ă���t�@�C��

	int							CreateSoundDataType ;			// �쐬����T�E���h�f�[�^�̃f�[�^�^�C�v
	int							DisableReadSoundFunctionMask ;	// �g�p���Ȃ��ǂݍ��ݏ����̃}�X�N
#ifndef DX_NON_OGGVORBIS
	int							OggVorbisBitDepth ;				// �n�����u�����������g�p���̃r�b�g�[�x(1:8bit 2:16bit)
	int							OggVorbisFromTheoraFile ;		// Ogg Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��邩�ǂ����̃t���O( TRUE:Theora �t�@�C������ Vorbis �f�[�^���Q�Ƃ��� )
#endif

	HANDLE						StreamSoundThreadHandle ;		// �X�g���[���T�E���h���Đ����鏈�����s���X���b�h�̃n���h��
	DWORD						StreamSoundThreadID ;			// �X�g���[���T�E���h���Đ����鏈�����s���X���b�h�̂h�c
	DWORD						StreamSoundThreadEndFlag ;		// �X�g���[���T�E���h���Đ����鏈�����I�����邩�ǂ����̃t���O
} ;

// �l�h�c�h�f�[�^
struct MIDIHANDLEDATA
{
	HANDLEINFO					HandleInfo ;					// �n���h�����ʃf�[�^

	int							PlayFlag ;						// �Đ������A�t���O
	int							PlayStartFlag ;					// �Đ����J�n���ꂽ���A�t���O
	int							Volume ;						// ����

	void						*DataImage ;					// �l�h�c�h�t�@�C���̃f�[�^���i�[����Ă���A�h���X( DSOUND.SoundMode �� DX_MIDIMODE_MCI �̎��̂ݗL�� )
	int							DataSize ;						// �l�h�c�h�t�@�C���̃f�[�^�T�C�Y( DSOUND.SoundMode �� DX_MIDIMODE_MCI �̎��̂ݗL�� )

	D_IDirectMusicSegment8		*DirectMusicSegmentObject ;		// DirectMusicSegment8 �I�u�W�F�N�g
	int							StartTime ;						// �Đ��J�n����
} ;

// �l�h�c�h�Ǘ��f�[�^�^
struct MIDIDATA
{
	int							PlayFlag ;						// ���t���t���O
	int							PlayHandle ;					// ���t���̃n���h��

	TCHAR						FileName[ MAX_PATH ] ;			// �t�@�C���l�[��

	UINT						MidiID ;						// �l�h�c�h���t���̂h�c
	int							LoopFlag ;						// ���[�v���t���A�t���O

	D_IDirectMusicSegment8		*DirectMusicSegmentObject ;		// DirectMusicSegment8 �I�u�W�F�N�g
	int							StartTime ;						// �Đ��J�n����

	int							MemImagePlayFlag ;				// ��������̃C���[�W���g�p���čĐ����Ă��邩�A�t���O( TRUE:�������C���[�W  FALSE:�t�@�C�� )

	int							DefaultHandle ;					// �W���̍Đ��֐��Ŏg�p����MIDI�n���h��
	int							DefaultHandleToSoundHandleFlag ;	// �W���̍Đ��֐��ōĐ����Ă���n���h���͉����n���h�����A�t���O
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �c�����������r���������f�[�^
extern DIRECTSOUNDDATA DX_DirectSoundData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int		InitializeDirectSound( void ) ;																			// �c�����������r��������������������
extern	int		TerminateDirectSound( void ) ;																			// �c�����������r���������̎g�p���I������

extern	int		RefreshStreamSoundPlayCompLength( int SoundHandle, int CurrentPosition = -1, int ASyncThread = FALSE ) ;	// �T�E���h�n���h���̍Đ��������Ԃ��X�V����
extern	int		ST_SoftSoundPlayerProcessAll( void ) ;																	// �\�t�g�E�G�A�Ő��䂷��S�ẴT�E���h�f�[�^�v���C���[�̒���������s��

extern	int		MidiCallBackProcess( void ) ;																			// �l�h�c�h���t�I�����Ă΂��R�[���o�b�N�֐�

extern	int		StartSoundCapture( const char *SaveFilePath ) ;															// �T�E���h�L���v�`���̊J�n
extern	int		SoundCaptureProcess( int CaptureSample ) ;																// �T�E���h�L���v�`���̎����I����
extern	int		EndSoundCapture( void ) ;																				// �T�E���h�L���v�`���̏I��

extern	void	InitLoadSoundGParam( LOADSOUND_GPARAM *GParam ) ;														// LOADSOUND_GPARAM �̃f�[�^���Z�b�g����

extern	int		InitializeSoundHandle( HANDLEINFO *HandleInfo ) ;														// �T�E���h�n���h���̏�����
extern	int		TerminateSoundHandle( HANDLEINFO *HandleInfo ) ;														// �T�E���h�n���h���̌�n��

extern	int		LoadSoundMemBase_UseGParam( LOADSOUND_GPARAM *GParam, const TCHAR *WaveName, int BufferNum, int UnionHandle, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;																					// LoadSoundMemBase �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadSoundMemByMemImageBase_UseGParam( LOADSOUND_GPARAM *GParam, int CreateSoundHandle, int SoundHandle, void *FileImageBuffer, int ImageSize, int BufferNum, int UnionHandle = -1, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;		// LoadSoundMemByMemImageBase �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadSoundMem2_UseGParam( LOADSOUND_GPARAM *GParam, const TCHAR *WaveName1 , const TCHAR *WaveName2, int ASyncLoadFlag = FALSE ) ;																													// LoadSoundMem2 �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadSoundMem2ByMemImage_UseGParam( LOADSOUND_GPARAM *GParam, void *FileImageBuffer1, int ImageSize1, void *FileImageBuffer2, int ImageSize2, int ASyncLoadFlag = FALSE ) ;																			// LoadSoundMem2ByMemImage �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		AddStreamSoundMem_UseGParam( LOADSOUND_GPARAM *GParam, STREAMDATA *Stream, int LoopNum,  int SoundHandle, int StreamDataType, int *CanStreamCloseFlag, int UnionHandle = -1, int ASyncThread = FALSE ) ;											// AddStreamSoundMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		AddStreamSoundMemToFile_UseGParam( LOADSOUND_GPARAM *GParam, const TCHAR *WaveFile, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1, int ASyncThread = FALSE ) ;															// AddStreamSoundMemToFile �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		AddStreamSoundMemToMem_UseGParam( LOADSOUND_GPARAM *GParam, void *FileImageBuffer, int ImageSize, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1, int ASyncThread = FALSE ) ;												// AddStreamSoundMemToMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		SetupStreamSoundMem_UseGParam( int SoundHandle, int ASyncThread = FALSE ) ;																																											// SetupStreamSoundMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		ProcessStreamSoundMem_UseGParam( int SoundHandle, int ASyncThread = FALSE ) ;																																										// ProcessStreamSoundMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		Refresh3DSoundParam( int SoundHandle, int AlwaysFlag = FALSE ) ;										// �R�c�T�E���h�̃p�����[�^���X�V����
extern	int		Refresh3DSoundParamAll() ;																				// �Đ����̂��ׂĂ̂R�c�T�E���h�̃p�����[�^���X�V����

extern	int		SetupSoftSoundHandle( int SoftSoundHandle, int IsPlayer, int Channels, int BitsPerSample, int SamplesPerSec, int SampleNum ) ;	// �\�t�g�T�E���h�n���h�����Z�b�g�A�b�v

extern	int		InitializeSoftSoundHandle( HANDLEINFO *HandleInfo ) ;													// �\�t�g�T�E���h�n���h���̏�����
extern	int		TerminateSoftSoundHandle( HANDLEINFO *HandleInfo ) ;													// �\�t�g�T�E���h�n���h���̌�n��

extern	int		DeleteCancelCheckSoftSoundFunction( HANDLEINFO *HandleInfo ) ;											// �\�t�g�T�E���h�n���h�����폜���邩�ǂ������`�F�b�N����֐�
extern	int		DeleteCancelCheckSoftSoundPlayerFunction( HANDLEINFO *HandleInfo ) ;									// �\�t�g�T�E���h�v���[���[�n���h�����폜���邩�ǂ������`�F�b�N����֐�

extern	int		LoadSoftSoundBase_UseGParam( LOADSOUND_GPARAM *GParam, const TCHAR *FileName, const void *FileImage, int FileImageSize, int ASyncLoadFlag = FALSE ) ;		// �\�t�g�E�G�A�ň����g�`�f�[�^���t�@�C���܂��̓�������ɓW�J���ꂽ�t�@�C���C���[�W����쐬����
extern	int		MakeSoftSoundBase_UseGParam( int IsPlayer, int Channels, int BitsPerSample, int SamplesPerSec, int SampleNum, int UseFormat_SoftSoundHandle = -1, int ASyncLoadFlag = FALSE ) ;	// �\�t�g�E�G�A�Ő��䂷��T�E���h�f�[�^�n���h���̍쐬

extern	int		AddMusicData( void ) ;																					// �V�����l�h�c�h�n���h�����擾����

extern	int		InitializeMidiHandle( HANDLEINFO *HandleInfo ) ;														// �l�h�c�h�n���h����������������֐�
extern	int		TerminateMidiHandle( HANDLEINFO *HandleInfo ) ;															// �l�h�c�h�n���h���̌�n�����s���֐�

extern	int		LoadMusicMemByMemImage_UseGParam( void *FileImage, int FileImageSize, int ASyncLoadFlag = FALSE ) ;		// LoadMusicMemByMemImage �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadMusicMem_UseGParam( const TCHAR *FileName, int ASyncLoadFlag = FALSE ) ;							// LoadMusicMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadMusicMemByResource_UseGParam( const TCHAR *ResourceName, const TCHAR *ResourceType, int ASyncLoadFlag = FALSE ) ;	// LoadMusicMemByResource �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		PauseSoundMemAll( int PauseFlag ) ;																		// �S�Ẳ��̈ꎞ��~��Ԃ�ύX����
extern	int		PauseSoftSoundAll( int PauseFlag ) ;																	// �S�Ẵ\�t�g�E�G�A�T�E���h�̈ꎞ��~��Ԃ�ύX����

}

#endif // DX_NON_SOUND

#endif // __DXSOUND_H__
