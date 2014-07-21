// ----------------------------------------------------------------------------
//
//		�c�w���C�u�����@�����g�p�֘A�p�w�b�_�t�@�C��
//
//				Ver 3.10c
//
// ----------------------------------------------------------------------------

// ���d�C���N���[�h�h�~�p�}�N��
#ifndef __DXSTATIC_H__
#define __DXSTATIC_H__

// �C���N���[�h --------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"

namespace DxLib
{

// �}�N����` ----------------------------------

#ifdef VISUALCPP_2005
#define RST  __restrict
#else
#define RST
#endif

// �\���̒�` --------------------------------------------------------------------

}

// �f�[�^��` --------------------------------------------

namespace DxLib
{


}

// �֐��錾 -----------------------------------------------

namespace DxLib
{

// ���C�u�����֐������Ăяo���ȗ����}�N�� -----------------


// DxSystem.cpp�֐��v���g�^�C�v�錾

#if defined( DX_THREAD_SAFE ) || defined( DX_THREAD_SAFE_NETWORK_ONLY )

// �������I���n�֐�
extern	int			NS_DxLib_Init( void ) ;													// ���C�u�����������֐�
extern	int			NS_DxLib_End( void ) ;														// ���C�u�����g�p�̏I���֐�

// ���b�Z�[�W�����֐�
extern	int			NS_ProcessMessage( void ) ;												// �E�C���h�E�Y�̃��b�Z�[�W���[�v�ɑ��鏈�����s��

#else

// �������I���n�֐�
#define NS_DxLib_Init	DxLib_Init
#define NS_DxLib_End	DxLib_End

// ���b�Z�[�W�����֐�
#define NS_ProcessMessage		ProcessMessage

#endif


#ifdef DX_THREAD_SAFE

extern	int			NS_DxLib_GlobalStructInitialize( void ) ;									// ���C�u�����̓����Ŏg�p���Ă���\���̂��[�����������āADxLib_Init �̑O�ɍs�����ݒ�𖳌�������( DxLib_Init �̑O�ł̂ݗL�� )
extern	int			NS_DxLib_IsInit( void ) ;													// ���C�u����������������Ă��邩�ǂ������擾����( �߂�l: TRUE=����������Ă���  FALSE=����Ă��Ȃ� )

#else

#define NS_DxLib_GlobalStructInitialize		DxLib_GlobalStructInitialize
#define NS_DxLib_IsInit						DxLib_IsInit

#endif







// DxNetwork.cpp�֐��v���g�^�C�v�錾

#ifdef DX_THREAD_SAFE

#ifndef DX_NON_NETWORK

// �ʐM�֌W
extern	int			NS_ProcessNetMessage(				int RunReleaseProcess = FALSE ) ;														// �ʐM���b�Z�[�W�̏���������֐�

extern	int			NS_GetHostIPbyName(				const TCHAR *HostName, IPDATA      *IPDataBuf ) ;										// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv4�� )
extern	int			NS_GetHostIPbyName_IPv6(			const TCHAR *HostName, IPDATA_IPv6 *IPDataBuf ) ;										// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����( IPv6�� )
extern	int			NS_ConnectNetWork(					IPDATA      IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv4�� )
extern	int			NS_ConnectNetWork_IPv6(			IPDATA_IPv6 IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv6�� )
extern	int			NS_ConnectNetWork_ASync(			IPDATA      IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv4�� )�A�񓯊���
extern	int			NS_ConnectNetWork_IPv6_ASync(		IPDATA_IPv6 IPData, int Port = -1 ) ;													// ���}�V���ɐڑ�����( IPv6�� )�A�񓯊���
extern	int			NS_PreparationListenNetWork(		int Port = -1 ) ;																		// �ڑ����󂯂����Ԃɂ���( IPv4�� )
extern	int			NS_PreparationListenNetWork_IPv6(	int Port = -1 ) ;																		// �ڑ����󂯂����Ԃɂ���( IPv6�� )
extern	int			NS_StopListenNetWork(				void ) ;																				// �ڑ����󂯂���Ԃ̉���
extern	int			NS_CloseNetWork(					int NetHandle ) ;																		// �ڑ����I������

extern	int			NS_GetNetWorkAcceptState(			int NetHandle ) ;																		// �ڑ���Ԃ��擾����
extern	int			NS_GetNetWorkDataLength(			int NetHandle ) ;																		// ��M�f�[�^�̗ʂ𓾂�
extern	int			NS_GetNetWorkSendDataLength(		int NetHandle ) ;																		// �����M�̃f�[�^�̗ʂ𓾂� 
extern	int			NS_GetNewAcceptNetWork(			void ) ;																				// �V���ɐڑ������ʐM����𓾂�
extern	int			NS_GetLostNetWork(					void ) ;																				// �ڑ���ؒf���ꂽ�ʐM����𓾂�
extern	int			NS_GetNetWorkIP(					int NetHandle, IPDATA      *IpBuf ) ;													// �ڑ���̂h�o�𓾂�( IPv4�� )
extern	int			NS_GetNetWorkIP_IPv6(				int NetHandle, IPDATA_IPv6 *IpBuf ) ;													// �ڑ���̂h�o�𓾂�( IPv6�� )
extern	int			NS_GetMyIPAddress(					IPDATA *IpBuf ) ;																		// �����̂h�o�𓾂�
extern	int			NS_SetConnectTimeOutWait(			int Time ) ;																			// �ڑ��̃^�C���A�E�g�܂ł̎��Ԃ�ݒ肷��
extern	int			NS_SetUseDXNetWorkProtocol(		int Flag ) ;																			// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������Z�b�g����
extern	int			NS_GetUseDXNetWorkProtocol(		void ) ; 																				// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������擾����
extern	int			NS_SetUseDXProtocol(				int Flag ) ;																			// SetUseDXNetWorkProtocol �̕ʖ�
extern	int			NS_GetUseDXProtocol(				void ) ; 																				// GetUseDXNetWorkProtocol �̕ʖ�
extern	int			NS_SetNetWorkCloseAfterLostFlag(	int Flag ) ;																			// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetNetWorkCloseAfterLostFlag(	void ) ;																				// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���擾����
//extern	int			NS_SetProxySetting( int UseFlag, const char *Address, int Port ) ;														// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���s��
//extern	int			NS_GetProxySetting( int *UseFlagBuffer, char *AddressBuffer, int *PortBuffer ) ;										// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���擾����
//extern	int			NS_SetIEProxySetting( void ) ;																							// �h�d�̃v���L�V�ݒ��K������

extern	int			NS_NetWorkRecv(			int NetHandle, void *Buffer, int Length ) ;														// ��M�����f�[�^��ǂݍ���
extern	int			NS_NetWorkRecvToPeek(		int NetHandle, void *Buffer, int Length ) ;														// ��M�����f�[�^��ǂݍ��ށA�ǂݍ��񂾃f�[�^�̓o�b�t�@����폜����Ȃ�
extern	int			NS_NetWorkRecvBufferClear(	int NetHandle ) ;																				// ��M�����f�[�^���N���A����
extern	int			NS_NetWorkSend(			int NetHandle, void *Buffer, int Length ) ;														// �f�[�^�𑗐M����

extern	int			NS_MakeUDPSocket(			int RecvPort = -1 ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����쐬����( RecvPort �� -1 �ɂ���Ƒ��M��p�̃\�P�b�g�n���h���ɂȂ�܂� )
extern	int			NS_MakeUDPSocket_IPv6(		int RecvPort = -1 ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����쐬����( RecvPort �� -1 �ɂ���Ƒ��M��p�̃\�P�b�g�n���h���ɂȂ�܂� )( IPv6�� )
extern	int			NS_DeleteUDPSocket(		int NetUDPHandle ) ;																			// UDP���g�p�����ʐM���s���\�P�b�g�n���h�����폜����
extern	int			NS_NetWorkSendUDP(			int NetUDPHandle, IPDATA       SendIP, int SendPort,  void *Buffer, int Length ) ;				// UDP���g�p�����ʐM�Ŏw��̂h�o�Ƀf�[�^�𑗐M����ALength �͍ő�65507�ASendPort �� -1 �ɂ���� MakeUDPSocket �� RecvPort �œn�����|�[�g���g�p����܂�( �߂�l  0�ȏ�;���M�ł����f�[�^�T�C�Y  -1:�G���[  -2:���M�f�[�^���傫������  -3:���M�������ł��Ă��Ȃ�  )
extern	int			NS_NetWorkSendUDP_IPv6(	int NetUDPHandle, IPDATA_IPv6  SendIP, int SendPort,  void *Buffer, int Length ) ;				// UDP���g�p�����ʐM�Ŏw��̂h�o�Ƀf�[�^�𑗐M����ALength �͍ő�65507�ASendPort �� -1 �ɂ���� MakeUDPSocket �� RecvPort �œn�����|�[�g���g�p����܂�( �߂�l  0�ȏ�;���M�ł����f�[�^�T�C�Y  -1:�G���[  -2:���M�f�[�^���傫������  -3:���M�������ł��Ă��Ȃ�  )( IPv6�� )
extern	int			NS_NetWorkRecvUDP(			int NetUDPHandle, IPDATA      *RecvIP, int *RecvPort, void *Buffer, int Length, int Peek ) ;	// UDP���g�p�����ʐM�Ńf�[�^����M����APeek �� TRUE ��n���Ǝ�M�ɐ������Ă��f�[�^����M�L���[����폜���܂���( �߂�l  0�ȏ�:��M�����f�[�^�̃T�C�Y  -1:�G���[  -2:�o�b�t�@�̃T�C�Y������Ȃ�  -3:��M�f�[�^���Ȃ� )
extern	int			NS_NetWorkRecvUDP_IPv6(	int NetUDPHandle, IPDATA_IPv6 *RecvIP, int *RecvPort, void *Buffer, int Length, int Peek ) ;	// UDP���g�p�����ʐM�Ńf�[�^����M����APeek �� TRUE ��n���Ǝ�M�ɐ������Ă��f�[�^����M�L���[����폜���܂���( �߂�l  0�ȏ�:��M�����f�[�^�̃T�C�Y  -1:�G���[  -2:�o�b�t�@�̃T�C�Y������Ȃ�  -3:��M�f�[�^���Ȃ� )( IPv6�� )
//extern int		NS_CheckNetWorkSendUDP(	int NetUDPHandle ) ;																			// UDP���g�p�����ʐM�Ńf�[�^�����M�ł����Ԃ��ǂ����𒲂ׂ�( �߂�l  -1:�G���[  TRUE:���M�\  FALSE:���M�s�\ )
extern	int			NS_CheckNetWorkRecvUDP(	int NetUDPHandle ) ;																			// UDP���g�p�����ʐM�ŐV���Ȏ�M�f�[�^�����݂��邩�ǂ����𒲂ׂ�( �߂�l  -1:�G���[  TRUE:��M�f�[�^����  FALSE:��M�f�[�^�Ȃ� )

/*	�g�p�s��
extern	int			NS_HTTP_FileDownload(			const char *FileURL, const char *SavePath = NULL , void **SaveBufferP = NULL , int *FileSize = NULL , char **ParamList = NULL ) ;						// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C�����_�E�����[�h����
extern	int			NS_HTTP_GetFileSize(			const char *FileURL ) ;																		// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂�

extern	int			NS_HTTP_StartFileDownload(		const char *FileURL, const char *SavePath, void **SaveBufferP = NULL , char **ParamList = NULL ) ;	// HTTP ���g�p�����l�b�g���[�N��̃t�@�C�����_�E�����[�h���鏈�����J�n����
extern	int			NS_HTTP_StartGetFileSize(		const char *FileURL ) ;																		// HTTP ���g�p�����l�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂鏈�����J�n����
extern	int			NS_HTTP_Close(					int HttpHandle ) ;																			// HTTP �̏������I�����A�n���h�����������
extern	int			NS_HTTP_CloseAll(				void ) ;																					// �S�Ẵn���h���ɑ΂��� HTTP_Close ���s��
extern	int			NS_HTTP_GetState(				int HttpHandle ) ;																			// HTTP �����̌��݂̏�Ԃ𓾂�( NET_RES_COMPLETE �� )
extern	int			NS_HTTP_GetError(				int HttpHandle ) ;																			// HTTP �����ŃG���[�����������ꍇ�A�G���[�̓��e�𓾂�( HTTP_ERR_NONE �� )
extern	int			NS_HTTP_GetDownloadFileSize(	int HttpHandle ) ;																			// HTTP �����őΏۂƂȂ��Ă���t�@�C���̃T�C�Y�𓾂�( �߂�l: -1 = �G���[�E�Ⴕ���͂܂��t�@�C���̃T�C�Y���擾���Ă��Ȃ�  0�ȏ� = �t�@�C���̃T�C�Y )
extern	int			NS_HTTP_GetDownloadedFileSize( int HttpHandle ) ;																			// HTTP �����Ŋ��Ƀ_�E�����[�h�����t�@�C���̃T�C�Y���擾����

extern	int			NS_fgetsForNetHandle(			int NetHandle, char *strbuffer ) ;															// fgets �̃l�b�g���[�N�n���h����( -1:�擾�ł��� 0:�擾�ł��� )
extern	int			NS_URLAnalys(					const char *URL, char *HostBuf = NULL , char *PathBuf = NULL , char *FileNameBuf = NULL , int *PortBuf = NULL ) ;	// �t�q�k����͂���
extern	int			NS_URLConvert(					char *URL, int ParamConvert = TRUE , int NonConvert = FALSE ) ;								// HTTP �ɓn���Ȃ��L�����g��ꂽ�������n����悤�ȕ�����ɕϊ�����( �߂�l: -1 = �G���[  0�ȏ� = �ϊ���̕�����̃T�C�Y )
extern	int			NS_URLParamAnalysis(			char **ParamList, char **ParamStringP ) ;													// HTTP �p�p�����[�^���X�g�����̃p�����[�^��������쐬����( �߂�l:  -1 = �G���[  0�ȏ� = �p�����[�^�̕�����̒��� )
*/

#endif	// DX_NON_NETWORK

#else	// DX_THREAD_SAFE

#ifndef DX_NON_NETWORK

// �ʐM�֌W
#define NS_ProcessNetMessage					ProcessNetMessage

#define NS_GetHostIPbyName						GetHostIPbyName
#define NS_GetHostIPbyName_IPv6					GetHostIPbyName_IPv6
#define NS_ConnectNetWork						ConnectNetWork
#define NS_ConnectNetWork_IPv6					ConnectNetWork_IPv6
#define NS_ConnectNetWork_ASync					ConnectNetWork_ASync
#define NS_ConnectNetWork_IPv6_ASync			ConnectNetWork_IPv6_ASync
#define NS_PreparationListenNetWork				PreparationListenNetWork
#define NS_PreparationListenNetWork_IPv6		PreparationListenNetWork_IPv6
#define NS_StopListenNetWork					StopListenNetWork
#define NS_CloseNetWork							CloseNetWork

#define NS_GetNetWorkAcceptState				GetNetWorkAcceptState
#define NS_GetNetWorkDataLength					GetNetWorkDataLength
#define NS_GetNetWorkSendDataLength				GetNetWorkSendDataLength
#define NS_GetNewAcceptNetWork					GetNewAcceptNetWork
#define NS_GetLostNetWork						GetLostNetWork
#define NS_GetNetWorkIP							GetNetWorkIP
#define NS_GetNetWorkIP_IPv6					GetNetWorkIP_IPv6
#define NS_GetMyIPAddress						GetMyIPAddress
#define NS_SetConnectTimeOutWait				SetConnectTimeOutWait
#define NS_SetUseDXNetWorkProtocol				SetUseDXNetWorkProtocol
#define NS_GetUseDXNetWorkProtocol				GetUseDXNetWorkProtocol
#define NS_SetUseDXProtocol						SetUseDXProtocol
#define NS_GetUseDXProtocol						GetUseDXProtocol
#define NS_SetNetWorkCloseAfterLostFlag			SetNetWorkCloseAfterLostFlag
#define NS_GetNetWorkCloseAfterLostFlag			GetNetWorkCloseAfterLostFlag
//#define NS_SetProxySetting					SetProxySetting
//#define NS_GetProxySetting					GetProxySetting
//#define NS_SetIEProxySetting					SetIEProxySetting

#define NS_NetWorkRecv							NetWorkRecv
#define NS_NetWorkRecvToPeek					NetWorkRecvToPeek
#define NS_NetWorkRecvBufferClear				NetWorkRecvBufferClear
#define NS_NetWorkSend							NetWorkSend

#define NS_MakeUDPSocket						MakeUDPSocket
#define NS_MakeUDPSocket_IPv6					MakeUDPSocket_IPv6
#define NS_DeleteUDPSocket						DeleteUDPSocket
#define NS_NetWorkSendUDP						NetWorkSendUDP
#define NS_NetWorkSendUDP_IPv6					NetWorkSendUDP_IPv6
#define NS_NetWorkRecvUDP						NetWorkRecvUDP
#define NS_NetWorkRecvUDP_IPv6					NetWorkRecvUDP_IPv6
#define NS_CheckNetWorkSendUDP					CheckNetWorkSendUDP
#define NS_CheckNetWorkRecvUDP					CheckNetWorkRecvUDP

/* �g�p�s��
#define NS_HTTP_FileDownload					HTTP_FileDownload
#define NS_HTTP_GetFileSize						HTTP_GetFileSize

#define NS_HTTP_StartFileDownload				HTTP_StartFileDownload
#define NS_HTTP_StartGetFileSize				HTTP_StartGetFileSize
#define NS_HTTP_Close							HTTP_Close
#define NS_HTTP_CloseAll						HTTP_CloseAll
#define NS_HTTP_GetState						HTTP_GetState
#define NS_HTTP_GetError						HTTP_GetError
#define NS_HTTP_GetDownloadFileSize				HTTP_GetDownloadFileSize
#define NS_HTTP_GetDownloadedFileSize			HTTP_GetDownloadedFileSize

#define NS_fgetsForNetHandle					fgetsForNetHandle
#define NS_URLAnalys							URLAnalys
#define NS_URLConvert							URLConvert
#define NS_URLParamAnalysis						URLParamAnalysis
*/

#endif	// DX_NON_NETWORK

#endif	// DX_THREAD_SAFE









#ifdef DX_THREAD_SAFE


// DxSystem.cpp�֐��v���g�^�C�v�錾

// �E�G�C�g�n�֐�
extern	int			NS_WaitTimer( int WaitTime ) ;												// �w��̎��Ԃ����������Ƃ߂�
#ifndef DX_NON_INPUT
extern	int			NS_WaitKey( void ) ;														// �L�[�̓��͑҂�
#endif // DX_NON_INPUT

// �J�E���^�y�ю����擾�n�֐�
extern	int			NS_GetNowCount(				int UseRDTSCFlag = FALSE ) ;				// �~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
extern	LONGLONG	NS_GetNowHiPerformanceCount(	int UseRDTSCFlag = FALSE ) ;				// GetNowCount�̍����x�o�[�W����
extern	int			NS_GetDateTime(				DATEDATA *DateBuf ) ;						// ���ݎ������擾���� 

// �����擾
extern	int			NS_GetRand( int RandMax ) ;												// �������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern	int			NS_SRand(	 int Seed ) ;													// �����̏����l��ݒ肷��
















// DxLog.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_LOG
// �G���[�����֐�
extern	int			NS_ErrorLogAdd(		 const TCHAR *ErrorStr ) ;							// �G���[�����������o��
extern 	int			NS_ErrorLogFmtAdd(		 const TCHAR *FormatString , ... ) ;				// �����t���G���[�����������o��
extern	int			NS_ErrorLogTabAdd(		 void ) ;											// �^�u���𑝂₷
extern	int			NS_ErrorLogTabSub(		 void ) ;											// �^�u�������炷
extern	int			NS_SetUseTimeStampFlag( int UseFlag ) ;									// �^�C���X�^���v�̗L����ݒ肷��
extern 	int			NS_AppLogAdd(			 const TCHAR *String , ... ) ;						// �����t�����O������������o��

#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�
extern	int			NS_SetLogDrawOutFlag(	 int DrawFlag ) ;									// ���O�o�̓t���O���Z�b�g����
extern 	int			NS_GetLogDrawFlag(		 void ) ;											// ���O�o�͂����邩�t���O�̎擾
extern	int			NS_SetLogFontSize(		 int Size ) ;										// printfDx �ŉ�ʂɏo�͂��郍�O�t�H���g�̃T�C�Y��ύX����

// �ȈՉ�ʏo�͊֐�
extern 	int			NS_printfDx(			 const TCHAR *FormatString , ... ) ;				// �ȈՉ�ʏo��
extern	int			NS_clsDx(				 void ) ;											// �ȈՉ�ʏo�͂��N���A����
#endif

#endif // DX_NON_LOG















#ifndef DX_NON_ASYNCLOAD

// DxASyncLoad.cpp�֐��v���g�^�C�v�錾

// �񓯊��ǂݍ��݊֌W
extern	int			NS_SetUseASyncLoadFlag(		int Flag ) ;								// �ǂݍ��ݏ����n�̊֐��Ŕ񓯊��ǂݍ��݂��s�����ǂ�����ݒ肷��( �񓯊��ǂݍ��݂ɑΉ����Ă���֐��̂ݗL�� )( TRUE:�񓯊��ǂݍ��݂��s��  FALSE:�񓯊��ǂݍ��݂��s��Ȃ�( �f�t�H���g ) )
extern	int			NS_CheckHandleASyncLoad(		int Handle ) ;								// �n���h���̔񓯊��ǂݍ��݂��������Ă��邩�ǂ������擾����( TRUE:�܂��������Ă��Ȃ�  FALSE:�������Ă���  -1:�G���[ )
extern	int			NS_GetHandleASyncLoadResult(	int Handle ) ;								// �n���h���̔񓯊��ǂݍ��ݏ����̖߂�l���擾����( �񓯊��ǂݍ��ݒ��̏ꍇ�͈�O�̔񓯊��ǂݍ��ݏ����̖߂�l���Ԃ��Ă��܂� )
extern	int			NS_GetASyncLoadNum(			void ) ;									// �񓯊��ǂݍ��ݒ��̏����̐����擾����

#endif // DX_NON_ASYNCLOAD













// DxHandle.cpp�֐��v���g�^�C�v�錾

extern	int			NS_SetDeleteHandleFlag(		int Handle, int *DeleteFlag ) ;					// �n���h�����폜���ꂽ�Ƃ��Ɂ|�P���ݒ肳���ϐ���o�^����














// DxWindow.cpp�֐��v���g�^�C�v�錾

#ifdef __WINDOWS__

// �֗��֐�
extern	int			NS_GetResourceInfo(		const TCHAR *ResourceName , const TCHAR *ResourceType , void **DataPointerP , int *DataSizeP ) ;		// �w��̃��\�[�X���擾����( -1:���s  0:���� )
extern	TCHAR*		NS_GetResourceIDString(	int ResourceID ) ;																						// ���\�[�X�h�c���烊�\�[�X�h�c������𓾂� 

// �E�C���h�E�֌W���擾�֐�
extern	int			NS_GetWindowCRect(					RECT *RectBuf ) ;										// �E�C���h�E�̃N���C�A���g�̈���擾����
extern	int			NS_GetWindowActiveFlag(			void ) ;												// �E�C���h�E�̃A�N�e�B�u�t���O���擾
extern	HWND		NS_GetMainWindowHandle(			void ) ;												// ���C���E�C���h�E�̃n���h�����擾����
extern	int			NS_GetWindowModeFlag(				void ) ;												// �E�C���h�E���[�h�ŋN�����Ă��邩�A�̃t���O���擾����
extern	int			NS_GetDefaultState(				int *SizeX , int *SizeY , int *ColorBitDepth ) ;		// �N�����̃f�X�N�g�b�v�̉�ʃ��[�h���擾����
extern	int			NS_GetActiveFlag(					void ) ;												// �\�t�g���A�N�e�B�u���ǂ������擾����
extern	int			NS_GetNoActiveState(				int ResetFlag = TRUE ) ;								// ��A�N�e�B�u�ɂȂ�A�������ꎞ��~���Ă������ǂ������擾����(���� ResetFlag=TRUE:��Ԃ����Z�b�g FALSE:��Ԃ����Z�b�g���Ȃ�    �߂�l: 0=�ꎞ��~�͂��Ă��Ȃ�  1=�ꎞ��~���Ă��� )
extern	int			NS_GetMouseDispFlag(				void ) ;												// �}�E�X��\�����邩�ǂ����̃t���O���擾����
extern	int			NS_GetAlwaysRunFlag(				void ) ;												// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���擾����
extern	int			NS__GetSystemInfo(					int *DxLibVer , int *DirectXVer , int *WindowsVer ) ;	// �c�w���C�u������ DirectX �̃o�[�W������ Windows �̃o�[�W�����𓾂�
extern	int			NS_GetPcInfo(						TCHAR *OSString , TCHAR *DirectXString , TCHAR *CPUString , int *CPUSpeed /* �P��MHz */ , double *FreeMemorySize /* �P��MByte */ , double *TotalMemorySize , TCHAR *VideoDriverFileName , TCHAR *VideoDriverString , double *FreeVideoMemorySize /* �P��MByte */ , double *TotalVideoMemorySize ) ;	// �o�b�̏��𓾂�
extern	int			NS_GetUseMMXFlag(					void ) ;												// �l�l�w���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetUseSSEFlag(					void ) ;												// �r�r�d���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetUseSSE2Flag(					void ) ;												// �r�r�d�Q���g���邩�ǂ����̏��𓾂�
extern	int			NS_GetWindowCloseFlag(				void ) ;												// �E�C���h�E����悤�Ƃ��Ă��邩�̏��𓾂�
extern	HINSTANCE	NS_GetTaskInstance(				void ) ;												// �\�t�g�̃C���X�^���X���擾����
extern	int			NS_GetUseWindowRgnFlag(			void ) ;												// ���[�W�������g���Ă��邩�ǂ������擾����
extern	int			NS_GetWindowSizeChangeEnableFlag(	int *FitScreen = NULL ) ;								// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���擾����
extern	double		NS_GetWindowSizeExtendRate(		double *ExRateX = NULL , double *ExRateY = NULL ) ;		// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦���擾����( �߂�l�� ExRateX �ɑ�������l�Ɠ����ł� )
extern	int			NS_GetWindowSize(					int *Width, int *Height ) ;								// �E�C���h�E���[�h�̃E�C���h�E�̂̃N���C�A���g�̈�̃T�C�Y���擾����
extern	int			NS_GetWindowPosition(				int *x, int *y ) ;										// �E�C���h�E���[�h�̃E�C���h�E�̈ʒu���擾����( �g���܂߂�������W )
extern	int			NS_GetWindowUserCloseFlag(			int StateResetFlag = FALSE ) ;							// �E�C���h�E�̕���{�^���������ꂽ���ǂ������擾����
extern	int			NS_GetNotDrawFlag(					void ) ;												// �`��@�\���g�����ǂ����̃t���O���擾����
extern	int			NS_GetPaintMessageFlag(			void ) ;												// WM_PAINT ���b�Z�[�W���������ǂ������擾����(�߂�l  TRUE:WM_PAINT���b�Z�[�W������(��x�擾����ƈȌ�A�Ă� WM_PAINT���b�Z�[�W������܂� FALSE ���Ԃ��Ă���悤�ɂȂ�)  FALSE:WM_PAINT ���b�Z�[�W�͗��Ă��Ȃ�)
extern	int			NS_GetValidHiPerformanceCounter(	void ) ;												// �p�t�H�[�}���X�J�E���^���L�����ǂ������擾����(�߂�l  TRUE:�L��  FALSE:����)

// �ݒ�n�֐�
extern	int			NS_ChangeWindowMode(						int Flag ) ;																		// �E�C���h�E���[�h��ύX����
extern	int			NS_SetUseCharSet(							int CharSet /* = DX_CHARSET_SHFTJIS �� */ ) ;										// �c�w���C�u�����̕����񏈗��őO��Ƃ��镶����Z�b�g��ݒ肷��
extern	int			NS_LoadPauseGraph(							const TCHAR *FileName ) ;															// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			NS_LoadPauseGraphFromMem(					void *MemImage , int MemImageSize ) ;												// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			NS_SetActiveStateChangeCallBackFunction(	int (* CallBackFunction )( int ActiveState , void *UserData ) , void *UserData ) ;	// �E�C���h�E�̃A�N�e�B�u��Ԃɕω����������Ƃ��ɌĂ΂��R�[���o�b�N�֐����Z�b�g����( NULL ���Z�b�g����ƌĂ΂�Ȃ��Ȃ� )
extern	int			NS_SetWindowText(							const TCHAR *WindowText ) ;															// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			NS_SetMainWindowText(						const TCHAR *WindowText ) ;															// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			NS_SetMainWindowClassName(					const TCHAR *ClassName ) ;															// ���C���E�C���h�E�̃N���X����ݒ肷��
#ifndef DX_NON_LOG
extern	int			NS_SetOutApplicationLogValidFlag(			int Flag ) ;																		// ���O�o�͂��s�����ۂ��̃Z�b�g
extern	int			NS_SetApplicationLogSaveDirectory(			const TCHAR *DirectoryPath ) ;														// ���O�t�@�C����ۑ�����f�B���N�g���p�X��ݒ肷��
extern	int			NS_SetUseDateNameLogFile(					int Flag ) ;																		// ���O�t�@�C�����ɓ��t�����邩�ǂ������Z�b�g����
#endif // DX_NON_LOG
extern	int			NS_SetAlwaysRunFlag(						int Flag ) ;																		// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���Z�b�g����
extern	int			NS_SetWindowIconID(						int ID ) ;																			// �g�p����A�C�R���̂h�c���Z�b�g����
extern	int			NS_SetWindowIconHandle(					HICON Icon ) ;																		// �g�p����A�C�R���̃n���h�����Z�b�g����
extern	int			NS_SetUseASyncChangeWindowModeFunction(	int Flag , void (* CallBackFunction )( void * ) , void *Data ) ;					// �ő剻�{�^����ALT+ENTER�L�[�ɂ��񓯊��ȃE�C���h�E���[�h�̕ύX�̋@�\�̐ݒ���s��
extern	int			NS_SetWindowStyleMode(						int Mode ) ;																		// �E�C���h�E�̃X�^�C����ύX����
extern	int			NS_SetWindowSizeChangeEnableFlag(			int Flag, int FitScreen = TRUE ) ;													// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���Z�b�g����( NotFitScreen:�E�C���h�E�̃N���C�A���g�̈�ɉ�ʂ��t�B�b�g������(�g�傳����)���ǂ���  TRUE:�t�B�b�g������  FALSE:�t�B�b�g�����Ȃ� )
extern	int			NS_SetWindowSizeExtendRate(				double ExRateX, double ExRateY = -1.0 ) ;											// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦��ݒ肷��( ExRateY ���}�C�i�X�̏ꍇ�� ExRateX �̒l�� ExRateY �ɂ��g�p����܂� )
extern	int			NS_SetWindowSize(							int Width, int Height ) ;															// �E�C���h�E���[�h���̃E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��
extern	int			NS_SetWindowPosition(						int x, int y ) ;																	// �E�C���h�E���[�h�̃E�C���h�E�̈ʒu��ݒ肷��( �g���܂߂�������W )
extern	int			NS_SetSysCommandOffFlag(					int Flag , const TCHAR *HookDllPath = NULL ) ;										// �^�X�N�X�C�b�`��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			NS_SetHookWinProc(							WNDPROC WinProc ) ;																	// ���b�Z�[�W���t�b�N����E�C���h�E�v���[�W����o�^����
extern	int			NS_SetUseHookWinProcReturnValue(			int UseFlag ) ;																		// SetHookWinProc �Őݒ肵���E�C���h�E�v���[�W���̖߂�l���g�p���邩�ǂ�����ݒ肷��ASetHookWinProc �Őݒ肵���E�C���h�E�v���[�W���̒��ł̂ݎg�p�\( UseFlag TRUE:�߂�l���g�p���āA�c�w���C�u�����̃E�C���h�E�v���[�W���̏����͍s��Ȃ�  FALSE:�߂�l�͎g�p�����A�E�C���h�E�v���[�W������o����A�c�w���C�u�����̃E�C���h�E�v���[�W���̏������s�� )
extern	int			NS_SetDoubleStartValidFlag(				int Flag ) ;																		// �Q�d�N�����������ǂ����̃t���O���Z�b�g����
extern	int			NS_AddMessageTakeOverWindow(				HWND Window ) ;																		// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E��ǉ�����
extern	int			NS_SubMessageTakeOverWindow(				HWND Window ) ;																		// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E�����炷

extern	int			NS_SetWindowInitPosition(					int x , int y ) ;																	// �E�C���h�E�̏����ʒu��ݒ肷��
extern	int			NS_SetNotWinFlag(							int Flag ) ;																		// �c�w���C�u�����̃E�C���h�E�֘A�̋@�\���g�p���Ȃ��t���O
extern	int			NS_SetNotDrawFlag(							int Flag ) ;																		// �`��@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetNotSoundFlag(						int Flag ) ;																		// �T�E���h�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetNotInputFlag(						int Flag ) ;																		// ���͏�Ԃ̎擾�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			NS_SetDialogBoxHandle(						HWND WindowHandle ) ;																// �c�w���C�u�����Ń��b�Z�[�W�������s���_�C�A���O�{�b�N�X��o�^����
extern	int			NS_SetWindowVisibleFlag(					int Flag ) ;																		// ���C���E�C���h�E��\�����邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetWindowMinimizeFlag(					int Flag ) ;																		// ���C���E�C���h�E���ŏ������邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetWindowUserCloseEnableFlag(			int Flag ) ;																		// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetDxLibEndPostQuitMessageFlag(			int Flag ) ;																		// �c�w���C�u�����I������ PostQuitMessage ���ĂԂ��ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUserWindow(							HWND WindowHandle ) ;																// �c�w���C�u�����Ŏg�p����E�C���h�E�̃n���h�����Z�b�g����(DxLib_Init �����s����ȑO�ł̂ݗL��)
extern	int			NS_SetUserChildWindow(						HWND WindowHandle ) ;																// �c�w���C�u�����Ŏg�p����\���p�̎q�E�C���h�E�̃n���h�����Z�b�g����(DxLib_Init �����s����ȑO�ł̂ݗL��)
extern	int			NS_SetUserWindowMessageProcessDXLibFlag(	int Flag ) ;																		// SetUseWindow �Őݒ肵���E�C���h�E�̃��b�Z�[�W���[�v�������c�w���C�u�����ōs�����ǂ����A�t���O���Z�b�g����
extern	int			NS_SetDXArchivePriority(					int Priority = 0 ) ;																// �c�w�A�[�J�C�u�t�@�C���ƒʏ�̃t�H���_�̂ǂ�������݂����ꍇ�A�ǂ����D�悳���邩��ݒ肷��( 1:�t�H���_��D�� 0:�c�w�A�[�J�C�u�t�@�C����D��(�f�t�H���g) )
extern	int			NS_SetDXArchiveExtension(					const TCHAR *Extension = NULL ) ;													// ��������c�w�A�[�J�C�u�t�@�C���̊g���q��ύX����
extern	int			NS_SetDXArchiveKeyString(					const TCHAR *KeyString = NULL ) ;													// �c�w�A�[�J�C�u�t�@�C���̌��������ݒ肷��
extern	int			NS_SetBackgroundColor(						int Red, int Green, int Blue ) ;													// ���C���E�C���h�E�̃o�b�N�O���E���h�J���[��ݒ肷��
extern	int			NS_SetUseFPUPreserveFlag(					int Flag ) ;																		// FPU�̐��x�𗎂Ƃ��Ȃ��ݒ���g�p���邩�ǂ�����ݒ肷��ADxLib_Init ���Ăяo���O�̂ݗL��( TRUE:�g�p����(���x�������Ȃ�)  FALSE:�g�p���Ȃ�(���x�𗎂Ƃ�(�f�t�H���g) )
extern	int			NS_SetValidMousePointerWindowOutClientAreaMoveFlag( int Flag ) ;																// �}�E�X�|�C���^���E�C���h�E�̃N���C�A���g�G���A�̊O�ɂ����邩�ǂ�����ݒ肷��( TRUE:������( �f�t�H���g�ݒ� )  FALSE:�����Ȃ� )
extern	int			NS_SetUseBackBufferTransColorFlag(			int Flag ) ;																		// �o�b�N�o�b�t�@�̓��ߐF�̕����𓧉߂����邩�ǂ�����ݒ肷��( TRUE:���߂�����  FALSE:���߂����Ȃ� )
extern	int			NS_SetResourceModule(						HMODULE ResourceModule ) ;															// ���\�[�X��ǂݍ��ލۂɎg�p���郂�W���[����ݒ肷��( NULL ���w�肷��Ə�����Ԃɖ߂�܂��A�f�t�H���g�ł� NULL )

// �N���b�v�{�[�h�֌W
extern	int			NS_GetClipboardText(			TCHAR *DestBuffer ) ;									// �N���b�v�{�[�h�Ɋi�[����Ă���e�L�X�g�f�[�^��ǂݏo���A-1 �̏ꍇ�̓N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�͖����Ƃ�������( DestBuffer �� NULL ��n���Ɗi�[�ɕK�v�ȃf�[�^�T�C�Y���Ԃ��Ă��� )
extern	int			NS_SetClipboardText(			const TCHAR *Text ) ;									// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^���i�[����

// �h���b�O���h���b�v���ꂽ�t�@�C���֌W
extern	int			NS_SetDragFileValidFlag(		int Flag ) ;											// �t�@�C���̃h���b�O���h���b�v�@�\��L���ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_DragFileInfoClear(			void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̏�������������
extern	int			NS_GetDragFilePath(			TCHAR *FilePathBuffer ) ;								// �h���b�O���h���b�v���ꂽ�t�@�C�������擾����( -1:�擾�ł��Ȃ�����  0:�擾�ł��� )
extern	int			NS_GetDragFileNum(				void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̐����擾����

// �E�C���h�E�`��̈�ݒ�n�֐�
extern	HRGN		NS_CreateRgnFromGraph(			int Width , int Height , void *MaskData , int Pitch , int Byte ) ;				// �C�ӂ̃O���t�B�b�N����RGN�n���h�����쐬����
extern	HRGN		NS_CreateRgnFromBaseImage(		BASEIMAGE *BaseImage, int TransColorR, int TransColorG, int TransColorB ) ;		// �C�ӂ̊�{�C���[�W�f�[�^�Ɠ��ߐF����RGN�n���h�����쐬����
extern	int			NS_SetWindowRgnGraph(			const TCHAR *FileName ) ;														// �C�ӂ̃O���t�B�b�N����q�f�m���Z�b�g����
extern	int			NS_UpdateTransColorWindowRgn(	void ) ;																		// �`���̉�ʂ̓��ߐF�̕����𓧉߂�����q�f�m���Z�b�g����

// �c�[���o�[�֌W
extern	int			NS_SetupToolBar(				const TCHAR *BitmapName , int DivNum , int ResourceID = -1 ) ;															// �c�[���o�[�̏���( BitmapName �� NULL, ResourceID �� -1 ���w�肷��ƃc�[���o�[�������AResourceID �� -1 �ȊO�� BitmapName �� NULL �̎��ɂ̂� ResourceID ���g�p����� )
extern	int			NS_AddToolBarButton(			int Type /* TOOLBUTTON_TYPE_NORMAL �� */ , int State /* TOOLBUTTON_STATE_ENABLE �� */ , int ImageIndex, int ID ) ;		// �c�[���o�[�Ƀ{�^����ǉ�
extern	int			NS_AddToolBarSep(				void ) ;																												// �c�[���o�[�Ɍ��Ԃ�ǉ�
extern	int			NS_GetToolBarButtonState(		int ID ) ;																												// �c�[���o�[�̃{�^���̏�Ԃ��擾( TRUE:������Ă��� or �����ꂽ  FALSE:������Ă��Ȃ� )
extern	int			NS_SetToolBarButtonState(		int ID , int State ) ;																									// �c�[���o�[�̃{�^���̏�Ԃ�ݒ�
extern	int			NS_DeleteAllToolBarButton(		void ) ;																												// �c�[���o�[�̃{�^����S�č폜

// ���j���[�֌W
extern	int			NS_SetUseMenuFlag(				int Flag ) ;																						// ���j���[��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			NS_SetUseKeyAccelFlag(			int Flag ) ;																						// �L�[�{�[�h�A�N�Z�����[�^�[���g�p���邩�ǂ�����ݒ肷��

extern	int			NS_AddKeyAccel(				const TCHAR *ItemName , int ItemID , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			NS_AddKeyAccel_Name(			const TCHAR *ItemName , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;				// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			NS_AddKeyAccel_ID(				int ItemID, int KeyCode, int CtrlFlag, int AltFlag, int ShiftFlag ) ;								// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			NS_ClearKeyAccel(				void ) ;																							// �V���[�g�J�b�g�L�[�̏�������������

extern	int			NS_AddMenuItem(				int AddType /* MENUITEM_ADD_CHILD�� */ , const TCHAR *ItemName, int ItemID, int SeparatorFlag, const TCHAR *NewItemName = NULL , int NewItemID = -1 ) ;	// ���j���[�ɍ��ڂ�ǉ�����
extern	int			NS_DeleteMenuItem(				const TCHAR *ItemName, int ItemID ) ;																// ���j���[����I�����ڂ��폜����
extern	int			NS_CheckMenuItemSelect(		const TCHAR *ItemName, int ItemID ) ;																// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_SetMenuItemEnable(			const TCHAR *ItemName, int ItemID, int EnableFlag ) ;												// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��
extern	int			NS_SetMenuItemMark(			const TCHAR *ItemName, int ItemID, int Mark ) ;														// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( MENUITEM_MARK_NONE �� )
extern	int			NS_CheckMenuItemSelectAll(		void ) ;																							// ���j���[�̍��ڂ��ǂꂩ�I�����ꂽ���ǂ������擾����( �߂�l  TRUE:�ǂꂩ�I�����ꂽ  FALSE:�I������Ă��Ȃ� )

extern	int			NS_AddMenuItem_Name(			const TCHAR *ParentItemName, const TCHAR *NewItemName ) ;											// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			NS_AddMenuLine_Name(			const TCHAR *ParentItemName ) ;																		// ���j���[�̃��X�g�ɋ�؂����ǉ�����
extern	int			NS_InsertMenuItem_Name(		const TCHAR *ItemName, const TCHAR *NewItemName ) ;													// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			NS_InsertMenuLine_Name(		const TCHAR *ItemName ) ;																			// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			NS_DeleteMenuItem_Name(		const TCHAR *ItemName ) ;																			// ���j���[����I�����ڂ��폜����
extern	int			NS_CheckMenuItemSelect_Name(	const TCHAR *ItemName ) ;																			// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_SetMenuItemEnable_Name(		const TCHAR *ItemName, int EnableFlag ) ;															// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( 1:�I���ł���  0:�I���ł��Ȃ� )
extern	int			NS_SetMenuItemMark_Name(		const TCHAR *ItemName, int Mark ) ;																	// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( MENUITEM_MARK_NONE �� )

extern	int			NS_AddMenuItem_ID(				int ParentItemID, const TCHAR *NewItemName, int NewItemID = -1 ) ;									// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			NS_AddMenuLine_ID(				int ParentItemID ) ;																				// ���j���[�̃��X�g�ɋ�؂����ǉ�����
extern	int			NS_InsertMenuItem_ID(			int ItemID, int NewItemID ) ;																		// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			NS_InsertMenuLine_ID(			int ItemID, int NewItemID ) ;																		// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			NS_DeleteMenuItem_ID(			int ItemID ) ;																						// ���j���[����I�����ڂ��폜����
extern	int			NS_CheckMenuItemSelect_ID(		int ItemID ) ;																						// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			NS_SetMenuItemEnable_ID(		int ItemID, int EnableFlag ) ;																		// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��
extern	int			NS_SetMenuItemMark_ID(			int ItemID, int Mark ) ;																			// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��( MENUITEM_MARK_NONE �� )

extern	int			NS_DeleteMenuItemAll(			void ) ;																							// ���j���[�̑S�Ă̑I�����ڂ��폜����
extern	int			NS_ClearMenuItemSelect(		void ) ;																							// ���j���[���I�����ꂽ���ǂ����̏���������
extern	int			NS_GetMenuItemID(				const TCHAR *ItemName ) ;																			// ���j���[�̍��ږ�����h�c���擾����
extern	int			NS_GetMenuItemName(			int ItemID, TCHAR *NameBuffer ) ;																	// ���j���[�̍��ږ�����h�c���擾����
extern	int			NS_LoadMenuResource(			int MenuResourceID ) ;																				// ���j���[�����\�[�X����ǂݍ���
extern	int			NS_SetMenuItemSelectCallBackFunction(		void (* CallBackFunction )( const TCHAR *ItemName, int ItemID ) ) ;						// ���j���[�̑I�����ڂ��I�����ꂽ�Ƃ��ɌĂ΂��R�[���o�b�N�֐���ݒ肷��

extern	int			NS_SetWindowMenu(				int MenuID, int (* MenuProc )( WORD ID ) ) ;														// (�Â��֐�)�E�C���h�E�Ƀ��j���[��ݒ肷��
extern	int			NS_SetDisplayMenuFlag(			int Flag ) ;																						// ���j���[��\�����邩�ǂ������Z�b�g����
extern	int			NS_GetDisplayMenuFlag(			void ) ;																							// ���j���[��\�����Ă��邩�ǂ������擾����
extern	int			NS_GetUseMenuFlag(				void ) ;																							// ���j���[���g�p���Ă��邩�ǂ����𓾂�
extern	int			NS_SetAutoMenuDisplayFlag(		int Flag ) ;																						// �t���X�N���[�����Ƀ��j���[�������ŕ\���������\���ɂ����肷�邩�ǂ����̃t���O���Z�b�g����

#endif // __WINDOWS__

// �}�E�X�֌W�֐�
extern	int			NS_SetMouseDispFlag(		int DispFlag ) ;												// �}�E�X�̕\���t���O�̃Z�b�g
extern	int			NS_GetMousePoint(			int *XBuf, int *YBuf ) ;										// �}�E�X�̈ʒu���擾����
extern	int			NS_SetMousePoint(			int PointX, int PointY ) ;										// �}�E�X�̈ʒu���Z�b�g����
#ifndef DX_NON_INPUT
extern	int			NS_GetMouseInput(			void ) ;														// �}�E�X�̃{�^���̏�Ԃ𓾂� 
extern	int			NS_GetMouseWheelRotVol(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ𓾂�
extern	int			NS_GetMouseHWheelRotVol(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ𓾂�
extern	float		NS_GetMouseWheelRotVolF(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
extern	float		NS_GetMouseHWheelRotVolF(	int CounterReset = TRUE ) ;										// �����}�E�X�z�C�[���̉�]�ʂ��擾����( �߂�l�� float �^ )
extern	int			NS_GetMouseInputLog(		int *Button, int *ClickX, int *ClickY, int LogDelete = TRUE ) ;	// �}�E�X�̃N���b�N�����擾����( �߂�l  -1:���O���������� )
#endif // DX_NON_INPUT



















// DxMemory.cpp�֐��v���g�^�C�v�錾

// �������m�یn�֐�
extern	void*		NS_DxAlloc(						size_t AllocSize , const char *File = NULL , int Line = -1 ) ;					// ���������m�ۂ���
extern	void*		NS_DxCalloc(						size_t AllocSize , const char *File = NULL , int Line = -1 ) ;					// ���������m�ۂ��ĂO�ŏ���������
extern	void*		NS_DxRealloc(						void *Memory , size_t AllocSize , const char *File = NULL , int Line = -1 ) ;	// �������̍Ċm�ۂ��s��
extern	void		NS_DxFree(							void *Memory ) ;																// ���������������
extern	size_t		NS_DxSetAllocSizeTrap(				size_t Size ) ;																	// �񋓑Ώۂɂ��郁�����̊m�ۗe�ʂ��Z�b�g����
extern	int			NS_DxSetAllocPrintFlag(			int Flag ) ;																	// �c�w���C�u�������Ń������m�ۂ��s���鎞�ɏ����o�͂��邩�ǂ������Z�b�g����
extern	size_t		NS_DxGetAllocSize(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁�����T�C�Y���擾����
extern	int			NS_DxGetAllocNum(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁�����̐����擾����
extern	void		NS_DxDumpAlloc(					void ) ;																		// DxAlloc �� DxCalloc �Ŋm�ۂ��Ă��郁������񋓂���
extern	int			NS_DxErrorCheckAlloc(				void ) ;																		// �m�ۂ�����������񂪔j�󂳂�Ă��Ȃ������ׂ�( -1:�j�󂠂�  0:�Ȃ� )
extern	int			NS_DxSetAllocSizeOutFlag(			int Flag ) ;																	// ���������m�ہA������s����x�Ɋm�ۂ��Ă��郁�����̗e�ʂ��o�͂��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_DxSetAllocMemoryErrorCheckFlag(	int Flag ) ;																	// �������̊m�ہA������s����x�Ɋm�ۂ��Ă��郁�����m�ۏ�񂪔j�����Ă��Ȃ������ׂ邩�ǂ����̃t���O���Z�b�g����














// DxInputString.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUTSTRING

// �����R�[�h�o�b�t�@����֌W
extern	int			NS_StockInputChar(		TCHAR CharCode ) ;								// �o�b�t�@�ɃR�[�h���X�g�b�N����
extern	int			NS_ClearInputCharBuf(	void ) ;										// �����R�[�h�o�b�t�@���N���A����
extern	TCHAR		NS_GetInputChar(		int DeleteFlag ) ;								// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^���當���R�[�h���擾����
extern	TCHAR		NS_GetInputCharWait(	int DeleteFlag ) ;								// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�o�C�g���擾����A�o�b�t�@�ɂȂɂ������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�

extern	int			NS_GetOneChar(			TCHAR *CharBuffer, int DeleteFlag ) ;			// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����
extern	int			NS_GetOneCharWait(		TCHAR *CharBuffer, int DeleteFlag ) ;			// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����A�o�b�t�@�ɉ��������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�
extern	int			NS_GetCtrlCodeCmp(		TCHAR Char ) ;									// �A�X�L�[�R���g���[���R�[�h�����ׂ�

#endif // DX_NON_INPUTSTRING

#ifndef DX_NON_KEYEX

extern	int			NS_DrawIMEInputString(				int x, int y, int SelectStringNum ) ;	// ��ʏ�ɓ��͒��̕������`�悷��
extern	int			NS_SetUseIMEFlag(					int UseFlag ) ;							// �h�l�d���g�p���邩�ǂ������Z�b�g����
extern	int			NS_SetInputStringMaxLengthIMESync(	int Flag ) ;							// �h�l�d�œ��͂ł���ő啶������ MakeKeyInput �̐ݒ�ɍ��킹�邩�ǂ������Z�b�g����( TRUE:���킹��  FALSE:���킹�Ȃ�(�f�t�H���g) )
extern	int			NS_SetIMEInputStringMaxLength(		int Length ) ;							// �h�l�d�ň�x�ɓ��͂ł���ő啶������ݒ肷��( 0:�����Ȃ�  1�ȏ�:�w��̕������Ő��� )

#endif

extern	int			NS_GetStringPoint(				const TCHAR *String, int Point ) ;			// �S�p�����A���p�������藐��钆����w��̕������ł̔��p�������𓾂�
extern	int			NS_GetStringPoint2(			const TCHAR *String, int Point ) ;			// �S�p�����A���p�������藐��钆����w��̕������ł̑S�p�������𓾂�

#ifndef DX_NON_FONT
extern	int			NS_DrawObtainsString(			int x, int y, int AddY, const TCHAR *String, int StrColor, int StrEdgeColor = 0 , int FontHandle = -1 , int SelectBackColor = -1 , int SelectStrColor = 0 , int SelectStrEdgeColor = -1 , int SelectStart = -1 , int SelectEnd = -1 ) ;		// �K��̈�Ɏ��߂��������ŕ������`��
#endif // DX_NON_FONT
extern	int			NS_DrawObtainsBox(				int x1, int y1, int x2, int y2, int AddY, int Color, int FillFlag ) ;																																										// �K��̈�Ɏ��߂��������ŋ�`��`�� 

#ifndef DX_NON_KEYEX

extern	int			NS_InputStringToCustom(		int x, int y, int BufLength, TCHAR *StrBuffer, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag, int DoubleCharOnlyFlag = FALSE ) ;		// ������̓��͎擾

extern	int			NS_KeyInputString(				int x, int y, int CharMaxLength, TCHAR *StrBuffer, int CancelValidFlag ) ;														// ������̓��͎擾
extern	int			NS_KeyInputSingleCharString(	int x, int y, int CharMaxLength, TCHAR *StrBuffer, int CancelValidFlag ) ;														// ���p������݂̂̓��͎擾
extern	int			NS_KeyInputNumber(				int x, int y, int MaxNum, int MinNum, int CancelValidFlag ) ;																	// ���l�̓���

extern	int			NS_GetIMEInputModeStr(			TCHAR *GetBuffer ) ;																											// IME�̓��̓��[�h������̎擾
extern	IMEINPUTDATA* NS_GetIMEInputData(			void ) ;																														// IME�œ��͒��̕�����̏����擾����
#if defined( DX_GCC_COMPILE ) || defined( __ANDROID )
extern	int			NS_SetKeyInputStringColor(		ULONGLONG NmlStr, ULONGLONG NmlCur, ULONGLONG IMEStr, ULONGLONG IMECur, ULONGLONG IMELine, ULONGLONG IMESelectStr, ULONGLONG IMEModeStr , ULONGLONG NmlStrE = 0 , ULONGLONG IMESelectStrE = 0 , ULONGLONG IMEModeStrE = 0 , ULONGLONG IMESelectWinE = 0xffffffffffffffffULL ,	ULONGLONG IMESelectWinF = 0xffffffffffffffffULL , ULONGLONG SelectStrBackColor = 0xffffffffffffffffULL , ULONGLONG SelectStrColor = 0xffffffffffffffffULL , ULONGLONG SelectStrEdgeColor = 0xffffffffffffffffULL ) ;	// InputString�֐��g�p���̕����̊e�F��ύX����
#else // defined( DX_GCC_COMPILE ) || defined( __ANDROID )
extern	int			NS_SetKeyInputStringColor(		ULONGLONG NmlStr, ULONGLONG NmlCur, ULONGLONG IMEStr, ULONGLONG IMECur, ULONGLONG IMELine, ULONGLONG IMESelectStr, ULONGLONG IMEModeStr , ULONGLONG NmlStrE = 0 , ULONGLONG IMESelectStrE = 0 , ULONGLONG IMEModeStrE = 0 , ULONGLONG IMESelectWinE = 0xffffffffffffffff ,	ULONGLONG IMESelectWinF = 0xffffffffffffffff , ULONGLONG SelectStrBackColor = 0xffffffffffffffff , ULONGLONG SelectStrColor = 0xffffffffffffffff , ULONGLONG SelectStrEdgeColor = 0xffffffffffffffff ) ;	// InputString�֐��g�p���̕����̊e�F��ύX����
#endif // defined( DX_GCC_COMPILE ) || defined( __ANDROID )
extern	int			NS_SetKeyInputStringFont(		int FontHandle ) ;																												// �L�[���͕�����`��֘A�Ŏg�p����t�H���g�̃n���h����ύX����(-1�Ńf�t�H���g�̃t�H���g�n���h��)
extern	int			NS_DrawKeyInputModeString(		int x, int y ) ;																												// ���̓��[�h�������`�悷��

extern	int			NS_InitKeyInput(				void ) ;																														// �L�[���̓f�[�^������
extern	int			NS_MakeKeyInput(				int MaxStrLength, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag, int DoubleCharOnlyFlag = FALSE ) ;			// �V�����L�[���̓f�[�^�̍쐬
extern	int			NS_DeleteKeyInput(				int InputHandle ) ;																												// �L�[���̓f�[�^�̍폜
extern	int			NS_SetActiveKeyInput(			int InputHandle ) ;																												// �w��̃L�[���͂��A�N�e�B�u�ɂ���( -1 ���w�肷��ƃA�N�e�B�u�ȃL�[���̓n���h����������ԂɂȂ�܂� )
extern	int			NS_GetActiveKeyInput(			void ) ;																														// ���݃A�N�e�B�u�ɂȂ��Ă���L�[���̓n���h�����擾����
extern	int			NS_CheckKeyInput(				int InputHandle ) ;																												// ���͂��I�����Ă��邩�擾����
extern	int			NS_ReStartKeyInput(			int InputHandle ) ;																												// ���͂����������L�[���͂��ēx�ҏW��Ԃɖ߂�
extern	int			NS_ProcessActKeyInput(			void ) ;																														// �L�[���͏����֐�
extern	int			NS_DrawKeyInputString(			int x, int y, int InputHandle ) ;																								// �L�[���͒��f�[�^�̕`��

extern	int			NS_SetKeyInputSelectArea(		int  SelectStart, int  SelectEnd, int InputHandle ) ;																			// �L�[���̓f�[�^�̎w��̗̈��I����Ԃɂ���( SelectStart �� SelectEnd �� -1 ���w�肷��ƑI����Ԃ���������܂� )
extern	int			NS_GetKeyInputSelectArea(		int *SelectStart, int *SelectEnd, int InputHandle ) ;																			// �L�[���̓f�[�^�̑I��̈���擾����
extern	int			NS_SetKeyInputDrawStartPos(	int DrawStartPos, int InputHandle ) ;																							// �L�[���͂̕`��J�n�����ʒu��ݒ肷��
extern	int			NS_GetKeyInputDrawStartPos(	int InputHandle ) ;																												// �L�[���͂̕`��J�n�����ʒu���擾����
extern	int			NS_SetKeyInputCursorBrinkTime(	int Time ) ;																													// �L�[���͎��̃J�[�\���̓_�ł��鑁�����Z�b�g����
extern	int			NS_SetKeyInputCursorBrinkFlag(	int Flag ) ;																													// �L�[���͎��̃J�[�\����_�ł����邩�ǂ������Z�b�g����
extern	int			NS_SetKeyInputString(			const TCHAR *String, int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̕�������Z�b�g����
extern	int			NS_SetKeyInputNumber(			int   Number,        int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̐��l�𕶎��ɒu�������ăZ�b�g����
extern	int			NS_SetKeyInputNumberToFloat(	float Number,        int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̕��������_�l�𕶎��ɒu�������ăZ�b�g����
extern	int			NS_GetKeyInputString(			TCHAR *StrBuffer,    int InputHandle ) ;																						// ���̓f�[�^�̕�������擾����
extern	int			NS_GetKeyInputNumber(			int InputHandle ) ;																												// ���̓f�[�^�̕�����𐮐��l�Ƃ��Ď擾����
extern	float		NS_GetKeyInputNumberToFloat(	int InputHandle ) ;																												// ���̓f�[�^�̕�����𕂓������_�l�Ƃ��Ď擾����
extern	int			NS_SetKeyInputCursorPosition(	int Position,        int InputHandle ) ;																						// �L�[���͂̌��݂̃J�[�\���ʒu��ݒ肷��
extern	int			NS_GetKeyInputCursorPosition(	int InputHandle ) ;																												// �L�[���͂̌��݂̃J�[�\���ʒu���擾����

#endif // DX_NON_KEYEX


















// DxFile.cpp�֐��v���g�^�C�v�錾

// �t�@�C���A�N�Z�X�֐�
extern	int			NS_FileRead_open(				const TCHAR *FilePath , int ASync = FALSE ) ;					// �t�@�C�����J��
extern	int			NS_FileRead_size(				const TCHAR *FilePath ) ;										// �t�@�C���̃T�C�Y�𓾂�
extern	int			NS_FileRead_close(				int FileHandle ) ;												// �t�@�C�������
extern	int			NS_FileRead_tell(				int FileHandle ) ;												// �t�@�C���|�C���^�̌��݈ʒu�𓾂�
extern	int			NS_FileRead_seek(				int FileHandle , int Offset , int Origin ) ;					// �t�@�C���|�C���^�̈ʒu��ύX����
extern	int			NS_FileRead_read(				void *Buffer , int ReadSize , int FileHandle ) ;				// �t�@�C������f�[�^��ǂݍ���
extern	int			NS_FileRead_idle_chk(			int FileHandle ) ;												// �t�@�C���ǂݍ��݂��������Ă��邩�ǂ������擾����
extern	int			NS_FileRead_eof(				int FileHandle ) ;												// �t�@�C���̏I�[���ǂ����𓾂�
extern	int			NS_FileRead_gets(				TCHAR *Buffer , int BufferSize , int FileHandle ) ;				// �t�@�C�����當�����ǂݏo��
extern	TCHAR		NS_FileRead_getc(				int FileHandle ) ;												// �t�@�C������ꕶ���ǂݏo��
extern	int			NS_FileRead_scanf(				int FileHandle , const TCHAR *Format , ... ) ;					// �t�@�C�����珑�������ꂽ�f�[�^��ǂݏo��

extern	DWORD_PTR	NS_FileRead_createInfo(		const TCHAR *ObjectPath ) ;										// �t�@�C�����n���h�����쐬����( �߂�l  -1:�G���[  -1�ȊO:�t�@�C�����n���h�� )
extern	int			NS_FileRead_getInfoNum(		DWORD_PTR FileInfoHandle ) ;									// �t�@�C�����n���h�����̃t�@�C���̐����擾����
extern	int			NS_FileRead_getInfo(			int Index , FILEINFO *Buffer , DWORD_PTR FileInfoHandle ) ;		// �t�@�C�����n���h�����̃t�@�C���̏����擾����
extern	int			NS_FileRead_deleteInfo(		DWORD_PTR FileInfoHandle ) ;									// �t�@�C�����n���h�����폜����

extern	DWORD_PTR	NS_FileRead_findFirst(			const TCHAR *FilePath, FILEINFO *Buffer ) ;						// �w��̃t�@�C�����̓t�H���_�̏����擾���A�t�@�C�������n���h�����쐬����( �߂�l: -1=�G���[  -1�ȊO=�t�@�C�������n���h�� )
extern	int			NS_FileRead_findNext(			DWORD_PTR FindHandle, FILEINFO *Buffer ) ;						// �����̍��v���鎟�̃t�@�C���̏����擾����( �߂�l: -1=�G���[  0=���� )
extern	int			NS_FileRead_findClose(			DWORD_PTR FindHandle ) ;										// �t�@�C�������n���h�������( �߂�l: -1=�G���[  0=���� )

// �ݒ�֌W�֐�
extern	int			NS_SetUseDXArchiveFlag(		int Flag ) ;													// �c�w�A�[�J�C�u�t�@�C���̓ǂݍ��݋@�\���g�����ǂ�����ݒ肷��( FALSE:�g�p���Ȃ�  TRUE:�g�p���� )
extern	int			NS_GetStreamFunctionDefault(	void ) ;														// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐����f�t�H���g�̂��̂����ׂ�( TRUE:�f�t�H���g  FALSE:�f�t�H���g�ł͂Ȃ� )
extern	int			NS_ChangeStreamFunction(		STREAMDATASHREDTYPE2 *StreamThread ) ;							// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐���ύX����
















// DxInput.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUT

// ���͏�Ԏ擾�֐�
extern	int			NS_CheckHitKey(							int KeyCode ) ;															// �L�[�{�[�h�̓��͏�Ԏ擾
extern	int			NS_CheckHitKeyAll(							int CheckType = DX_CHECKINPUT_ALL ) ;									// �S�L�[�̉�����Ԃ��擾
extern	int			NS_GetHitKeyStateAll(						DX_CHAR *KeyStateBuf ) ;												// ���ׂẴL�[�̉�����Ԃ��擾����
extern	int			NS_SetKeyExclusiveCooperativeLevelFlag(	int Flag ) ;															// �L�[�{�[�h�̋������x����r�����x���ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetJoypadNum(							void ) ;																// �W���C�p�b�h���ڑ�����Ă��鐔���擾����
extern	int			NS_GetJoypadInputState(					int InputType ) ;														// �W���C�o�b�h�̓��͏�Ԏ擾
extern	int			NS_GetJoypadAnalogInput(					int *XBuf, int *YBuf, int InputType ) ;									// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�
extern	int			NS_GetJoypadAnalogInputRight(				int *XBuf, int *YBuf, int InputType ) ;									// ( �g�p�񐄏� )�W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�(�E�X�e�B�b�N�p)
extern	int			NS_GetJoypadDirectInputState(				int InputType, DINPUT_JOYSTATE *DInputState ) ;							// DirectInput ���瓾����W���C�p�b�h�̐��̃f�[�^���擾����( DX_INPUT_KEY �� DX_INPUT_KEY_PAD1 �������ɓn���ƃG���[ )
extern	int			NS_KeyboradBufferProcess(					void ) ;																// �L�[�{�[�h�̃o�b�t�@����f�[�^���擾���鏈��
extern	int			NS_GetJoypadGUID(							int PadIndex, GUID *GuidBuffer ) ;										// �W���C�p�b�h�̂f�tI�c�𓾂�
extern	int			NS_ConvertKeyCodeToVirtualKey(				int KeyCode ) ;															// �c�w���C�u�����̃L�[�R�[�h���� Windows �̉��z�L�[�R�[�h���擾����
extern	int			NS_ConvertVirtualKeyToKeyCode(				int VirtualKey ) ;														//  Windows �̉��z�L�[�R�[�h( VK_LEFT �Ȃ� ) �ɑΉ�����c�w���C�u�����̃L�[�R�[�h( KEY_INPUT_A �Ȃ� )���擾����( VirtualKey:�ϊ�������Windows�̉��z�L�[�R�[�h�@�߂�l�F�c�w���C�u�����̃L�[�R�[�h )
extern	int			NS_SetJoypadInputToKeyInput(				int InputType, int PadInput, int KeyInput1, int KeyInput2 = -1 , int KeyInput3 = -1 , int KeyInput4 = -1  ) ; // �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓��͂�ݒ肷��
extern	int			NS_SetJoypadDeadZone(						int InputType, double Zone ) ;											// �W���C�p�b�h�̖����]�[���̐ݒ���s��
extern	int			NS_StartJoypadVibration(					int InputType, int Power, int Time ) ;									// �W���C�p�b�h�̐U�����J�n����
extern	int			NS_StopJoypadVibration(					int InputType ) ;														// �W���C�p�b�h�̐U�����~����
extern	int			NS_GetJoypadPOVState(						int InputType, int POVNumber ) ;										// �W���C�p�b�h�̂o�n�u���͂̏�Ԃ𓾂�( �P�ʂ͊p�x�̂P�O�O�{  ���S�ʒu�ɂ���ꍇ�� -1 ���Ԃ� )
extern	int			NS_GetJoypadName(							int InputType, TCHAR *InstanceNameBuffer, TCHAR *ProductNameBuffer ) ;	// �W���C�p�b�h�̃f�o�C�X�o�^���Ɛ��i�o�^�����擾����
extern	int			NS_ReSetupJoypad(							void ) ;																// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��( �V���ɐڑ����ꂽ�W���C�p�b�h������ꍇ�Ɍ��o����� )

extern	int			NS_SetKeyboardNotDirectInputFlag(			int Flag ) ;															// �L�[�{�[�h�̓��͏����� DirectInput ���g��Ȃ����A�t���O���Z�b�g����
extern	int			NS_SetUseDirectInputFlag(					int Flag ) ;															// ���͏����� DirectInput ���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseJoypadVibrationFlag(				int Flag ) ;															// �W���C�p�b�h�̐U���@�\���g�p���邩�ǂ����̃t���O���Z�b�g����

#endif // DX_NON_INPUT












#ifndef DX_NOTUSE_DRAWFUNCTION

// �摜�����n�֐��v���g�^�C�v�錾

// �O���t�B�b�N�n���h���쐬�֌W�֐�
extern	int			NS_MakeGraph(						int SizeX, int SizeY, int NotUse3DFlag = FALSE ) ;							// �O���t�B�b�N�n���h�����쐬����
extern	int			NS_MakeScreen(						int SizeX, int SizeY, int UseAlphaChannel = FALSE ) ;						// SetDrawScreen �ŕ`��Ώۂɂł���O���t�B�b�N�n���h�����쐬����
extern	int			NS_DerivationGraph(				int SrcX, int SrcY, int Width, int Height, int SrcGraphHandle ) ;			// �w��̃O���t�B�b�N�̎w�蕔�������𔲂��o���ĐV���ȃO���t�B�b�N�n���h�����쐬����
extern	int			NS_DeleteGraph(					int GrHandle, int LogOutFlag = FALSE ) ;									// �w��̃O���t�B�b�N�n���h�����폜����
extern	int			NS_DeleteSharingGraph(				int GrHandle ) ;															// �w��̃O���t�B�b�N�n���h���ƁA�����O���t�B�b�N�n���h������h�����Ă���O���t�B�b�N�n���h��( DerivationGraph �Ŕh�������n���h���ALoadDivGraph �ǂݍ���ō쐬���ꂽ�����̃n���h�� )����x�ɍ폜����
extern	int			NS_GetGraphNum(					void ) ;																	// �L���ȃO���t�B�b�N�n���h���̐����擾����
extern	int			NS_FillGraph(						int GrHandle, int Red, int Green, int Blue, int Alpha = 255 ) ;				// �O���t�B�b�N�n���h�������̐F�œh��Ԃ�
extern	int			NS_SetGraphLostFlag(				int GrHandle, int *LostFlag ) ;												// �O���t�B�b�N�n���h���폜���ɗ��Ă�t���O�̃A�h���X���Z�b�g����
extern	int			NS_InitGraph(						int LogOutFlag = FALSE ) ;													// ���ׂẴO���t�B�b�N�n���h�����폜����
extern	int			NS_ReloadFileGraphAll(				void ) ;																	// �t�@�C������ǂݍ��񂾉摜���O���t�B�b�N�n���h���ɍēx�ǂݍ���

// �O���t�B�b�N�n���h���ւ̉摜�]���֐�
extern	int			NS_BltBmpToGraph(					COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int CopyPointX, int CopyPointY,                                                                                 int GrHandle ) ;						// �a�l�o�̓��e���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpToDivGraph(				COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int AllNum, int XNum, int YNum, int Width, int Height,                                                          int *GrHandle, int ReverseFlag ) ;	// �a�l�o�̓��e�𕪊��쐬�����O���t�B�b�N�n���h�������ɓ]��
extern	int			NS_BltBmpOrGraphImageToGraph(		COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int CopyPointX, int CopyPointY,                        int GrHandle ) ;						// �a�l�o �� BASEIMAGE ���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpOrGraphImageToGraph2(		COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, RECT *SrcRect, int DestX, int DestY,                   int GrHandle ) ;						// �a�l�o �� BASEIMAGE �̎w��̗̈���O���t�B�b�N�n���h���ɓ]��
extern	int			NS_BltBmpOrGraphImageToDivGraph(	COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int Width, int Height, int *GrHandle, int ReverseFlag ) ;	// �a�l�o �� BASEIMAGE �𕪊��쐬�����O���t�B�b�N�n���h�������ɓ]��

// �摜����O���t�B�b�N�n���h�����쐬����֐�
extern	int			NS_LoadBmpToGraph(					const TCHAR *FileName, int TextureFlag, int ReverseFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL ) ;								// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraph(						const TCHAR *FileName, int NotUse3DFlag = FALSE ) ;																					// �摜�t�@�C������O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseGraph(				const TCHAR *FileName, int NotUse3DFlag = FALSE ) ;																					// �摜�t�@�C���𔽓]�������̂ŃO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraph(					const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int NotUse3DFlag = FALSE ) ;			// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivBmpToGraph(				const TCHAR *FileName, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag, int ReverseFlag ) ;	// �摜�t�@�C���𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadReverseDivGraph(			const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int NotUse3DFlag = FALSE ) ;			// �摜�t�@�C���𔽓]�������̂𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadBlendGraph(					const TCHAR *FileName ) ;																											// �摜�t�@�C������u�����h�p�O���t�B�b�N�n���h�����쐬����
#ifdef __WINDOWS__
extern	int			NS_LoadGraphToResource(			int ResourceID ) ;																													// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResource(			int ResourceID, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;											// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadGraphToResource(			const TCHAR *ResourceName, const TCHAR *ResourceType ) ;																			// �摜���\�[�X����O���t�B�b�N�n���h�����쐬����
extern	int			NS_LoadDivGraphToResource(			const TCHAR *ResourceName, const TCHAR *ResourceType, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;		// �摜���\�[�X�𕪊����ăO���t�B�b�N�n���h�����쐬����
#endif // __WINDOWS__

extern	int			NS_CreateGraphFromMem(				void *RGBFileImage, int RGBFileImageSize,               void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ,      int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// ��������̃O���t�B�b�N�C���[�W����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromMem(           void *RGBFileImage, int RGBFileImageSize, int GrHandle, void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ,      int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// ��������̃O���t�B�b�N�C���[�W��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromMem(          void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,         int TextureFlag = TRUE , int ReverseFlag = FALSE , void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;		// ��������̃O���t�B�b�N�C���[�W���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateDivGraphFromMem(        void *RGBFileImage, int RGBFileImageSize, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,         int TextureFlag = TRUE , int ReverseFlag = FALSE , void *AlphaFileImage = NULL , int AlphaFileImageSize = 0 ) ;		// ��������̃O���t�B�b�N�C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateGraphFromBmp(             BITMAPINFO *RGBBmpInfo, void *RGBBmpImage,               BITMAPINFO *AlphaBmpInfo = NULL , void *AlphaBmpImage = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// �r�b�g�}�b�v�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromBmp(           BITMAPINFO *RGBBmpInfo, void *RGBBmpImage, int GrHandle, BITMAPINFO *AlphaBmpInfo = NULL , void *AlphaBmpImage = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// �r�b�g�}�b�v�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromBmp(          BITMAPINFO *RGBBmpInfo, void *RGBBmpImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,        int TextureFlag = TRUE , int ReverseFlag = FALSE , BITMAPINFO *AlphaBmpInfo = NULL , void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateDivGraphFromBmp(        BITMAPINFO *RGBBmpInfo, void *RGBBmpImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,        int TextureFlag = TRUE , int ReverseFlag = FALSE , BITMAPINFO *AlphaBmpInfo = NULL , void *AlphaBmpImage = NULL ) ;	// �r�b�g�}�b�v�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDXGraph(					BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage,																				int TextureFlag ) ;																									// GraphImage �f�[�^����T�C�Y������o���A����ɍ������O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateGraphFromGraphImage(      BASEIMAGE *RGBImage,                                                                                                    int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateGraphFromGraphImage(      BASEIMAGE *RGBImage, BASEIMAGE *AlphaImage,                                                                             int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromGraphImage(    BASEIMAGE *RGBImage,                        int GrHandle,                                                               int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateGraphFromGraphImage(    BASEIMAGE *RGBImage, BASEIMAGE *AlphaImage, int GrHandle,                                                               int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateDivGraphFromGraphImage(   BASEIMAGE *RGBImage,                        int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,       int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraphFromGraphImage(   BASEIMAGE *RGBImage, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,       int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateDivGraphFromGraphImage( BASEIMAGE *RGBImage,                        int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,       int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_ReCreateDivGraphFromGraphImage( BASEIMAGE *RGBImage, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,       int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// GraphImage�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int			NS_CreateGraph(                    int Width, int Height, int Pitch, void *RGBImage, void *AlphaImage = NULL , int GrHandle = -1 ) ;																																			// ��������̃O���t�B�b�N�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateDivGraph(                 int Width, int Height, int Pitch, void *RGBImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, void *AlphaImage = NULL ) ;																							// ��������̃O���t�B�b�N�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraph(                  int Width, int Height, int Pitch, void *RGBImage, int GrHandle, void *AlphaImage = NULL ) ;																																					// ��������̃O���t�B�b�N�f�[�^����O���t�B�b�N�n���h�����č쐬����
#ifndef DX_NON_SOFTIMAGE
extern	int			NS_CreateBlendGraphFromSoftImage(  int SIHandle ) ;																													// �\�t�g�E�G�A�ň����C���[�W����u�����h�p�摜�O���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�u�����h�p�O���t�B�b�N�n���h�� )
extern	int			NS_CreateGraphFromSoftImage(       int SIHandle ) ;																													// �\�t�g�E�G�A�ň����C���[�W����O���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�O���t�B�b�N�n���h�� )
extern	int			NS_CreateGraphFromRectSoftImage(   int SIHandle, int x, int y, int SizeX, int SizeY ) ;																				// �\�t�g�E�G�A�ň����C���[�W�̎w��̗̈���g���ăO���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�O���t�B�b�N�n���h�� )
extern	int			NS_ReCreateGraphFromSoftImage(     int SIHandle, int GrHandle ) ;																										// �\�t�g�E�G�A�ň����C���[�W��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_ReCreateGraphFromRectSoftImage( int SIHandle, int x, int y, int SizeX, int SizeY, int GrHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_CreateDivGraphFromSoftImage(    int SIHandle, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf ) ;												// �\�t�g�E�G�A�ň����C���[�W���番���O���t�B�b�N�n���h�����쐬����
#endif // DX_NON_SOFTIMAGE
extern	int			NS_CreateGraphFromBaseImage(       BASEIMAGE *BaseImage ) ;																											// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int			NS_CreateGraphFromRectBaseImage(   BASEIMAGE *BaseImage, int x, int y, int SizeX, int SizeY ) ;																		// ��{�C���[�W�̎w��̗̈���g���ăO���t�B�b�N�n���h�����쐬����
extern	int			NS_ReCreateGraphFromBaseImage(     BASEIMAGE *BaseImage,                                     int GrHandle ) ;															// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_ReCreateGraphFromRectBaseImage( BASEIMAGE *BaseImage, int x, int y, int SizeX, int SizeY, int GrHandle ) ;															// ��{�C���[�W�̎w��̗̈���g���Ċ����̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int			NS_CreateDivGraphFromBaseImage(    BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf ) ;										// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int			NS_ReloadGraph(					const TCHAR *FileName, int GrHandle, int ReverseFlag = FALSE ) ;																	// �摜�ւ̉摜�f�[�^�̓ǂݍ���
extern	int			NS_ReloadDivGraph(					const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int ReverseFlag = FALSE ) ;			// �摜�ւ̉摜�f�[�^�̕����ǂݍ���
extern	int			NS_ReloadReverseGraph(				const TCHAR *FileName, int GrHandle ) ;																								// �摜�ւ̉摜�f�[�^�̓ǂݍ���
extern	int			NS_ReloadReverseDivGraph(			const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;										// �摜�ւ̉摜�f�[�^�̕����ǂݍ���

// �O���t�B�b�N�n���h���쐬���ݒ�W�֐�
extern	int			NS_SetGraphColorBitDepth(						int ColorBitDepth ) ;							// SetCreateGraphColorBitDepth �̋�����
extern	int			NS_GetGraphColorBitDepth(						void ) ;										// GetCreateGraphColorBitDepth �̋�����
extern	int			NS_SetCreateGraphColorBitDepth(				int BitDepth ) ;								// �쐬����O���t�B�b�N�̐F�[�x��ݒ肷��
extern	int			NS_GetCreateGraphColorBitDepth(				void ) ;										// �쐬����O���t�B�b�N�̐F�[�x���擾����
extern	int			NS_SetCreateGraphChannelBitDepth(				int BitDepth ) ;								// �쐬����O���t�B�b�N�̂P�`�����l���ӂ�̃r�b�g�[�x��ݒ肷��
extern	int			NS_GetCreateGraphChannelBitDepth(				void ) ;										// �쐬����O���t�B�b�N�̂P�`�����l���ӂ�̃r�b�g�[�x���擾����
extern	int			NS_SetDrawValidGraphCreateFlag(				int Flag ) ;									// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�`��\  FALSE:�`��s�\ )
extern	int			NS_GetDrawValidGraphCreateFlag(				void ) ;										// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidFlagOf3DGraph(					int Flag ) ;									// SetDrawValidGraphCreateFlag �̋�����
extern	int			NS_SetLeftUpColorIsTransColorFlag(				int Flag ) ;									// �摜����̐F�𓧉ߐF�ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseSystemMemGraphCreateFlag(				int Flag ) ;									// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			NS_GetUseSystemMemGraphCreateFlag(				void ) ;										// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			NS_SetUseBlendGraphCreateFlag(					int Flag ) ;									// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetUseBlendGraphCreateFlag(					void ) ;										// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseAlphaTestGraphCreateFlag(				int Flag ) ;									// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_GetUseAlphaTestGraphCreateFlag(				void ) ;										// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetUseAlphaTestFlag(						int Flag ) ;									// SetUseAlphaTestGraphCreateFlag �̋�����
extern	int			NS_GetUseAlphaTestFlag(						void ) ;										// GetUseAlphaTestGraphCreateFlag �̋�����
extern	int			NS_SetUseNoBlendModeParam(						int Flag ) ;									// SetDrawBlendMode �֐��̑������� DX_BLENDMODE_NOBLEND ���������ۂɁA�f�t�H���g�ł͑������͓����łQ�T�T���w�肵�����ƂɂȂ邪�A���̎����Q�T�T�������Ȃ����ǂ�����ݒ肷��( TRUE:���Ȃ�(�������̒l���g�p�����)   FALSE:����(�������̒l�͖�������� 255 ����Ɏg�p�����)(�f�t�H���g) )���`�����l���t���摜�ɑ΂��ĕ`����s���ꍇ�݈̂Ӗ�������֐�
extern	int			NS_SetDrawValidAlphaChannelGraphCreateFlag(	int Flag ) ;									// �`��\�ȃ��`�����l���t���摜���쐬���邩�ǂ����̃t���O���Z�b�g����,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ�( TRUE:���`�����l���t�� FALSE:���`�����l���Ȃ� )
extern	int			NS_GetDrawValidAlphaChannelGraphCreateFlag(	void ) ;										// �`��\�ȃ��`�����l���t���摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidFloatTypeGraphCreateFlag(		int Flag ) ;									// �`��\�ȕ��������_�^�̉摜���쐬���邩�ǂ����̃t���O���Z�b�g����,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ��A�f�o�t�� Float�^�̉摜�ɑΉ����Ă��Ȃ��ꍇ�͉摜�쐬�Ɏ��s����( TRUE:Float�^ FALSE:Int�^ )
extern	int			NS_GetDrawValidFloatTypeGraphCreateFlag(		void ) ;										// �`��\�ȕ��������_�^�̉摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			NS_SetDrawValidGraphCreateZBufferFlag(			int Flag ) ;									// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@���쐬���邩�ǂ�����ݒ肷��( �f�t�H���g�ł� TRUE( �쐬���� ) )
extern	int			NS_GetDrawValidGraphCreateZBufferFlag(			void ) ;										// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@���쐬���邩�ǂ������擾����
extern	int			NS_SetCreateDrawValidGraphChannelNum(			int ChannelNum ) ;								// �쐬����`��\�ȉ摜�̃`�����l������ݒ肷��,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ�
extern	int			NS_GetCreateDrawValidGraphChannelNum(			void ) ;										// �쐬����`��\�ȉ摜�̃`�����l�������擾����
extern	int			NS_SetDrawValidMultiSample(					int Samples, int Quality ) ;					// �`��\�ȉ摜�̃}���`�T���v�����O�ݒ���s��
extern	int			NS_GetMultiSampleQuality(						int Samples ) ;									// �w��̃}���`�T���v�����Ŏg�p�ł���ő�N�I���e�B�l���擾����( �߂�l���}�C�i�X�̏ꍇ�͈����̃T���v�������g�p�ł��Ȃ����Ƃ������܂� )
extern	int			NS_SetUseTransColor(							int Flag ) ;									// ���ߐF�@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetUseTransColorGraphCreateFlag(			int Flag ) ;									// ���ߐF�@�\���g�p���邱�Ƃ�O��Ƃ����摜�̓ǂݍ��ݏ������s�����ǂ�����ݒ肷��( TRUE �ɂ���� SetDrawMode( DX_DRAWMODE_BILINEAR ); ��������Ԃ� DrawGraphF ���̕��������_�^���W���󂯎��֐��ŏ����_�ȉ��̒l���w�肵���ꍇ�ɔ�������`�挋�ʂ̕s���R���ɘa������ʂ����� ( �f�t�H���g�� FALSE ) )
extern	int			NS_SetUseGraphAlphaChannel(					int Flag ) ;									// SetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			NS_GetUseGraphAlphaChannel(					void ) ;										// GetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			NS_SetUseAlphaChannelGraphCreateFlag(			int Flag ) ;									// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern	int			NS_GetUseAlphaChannelGraphCreateFlag(			void ) ;										// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern	int			NS_SetUseNotManageTextureFlag(					int Flag ) ;									// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���Z�b�g( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_GetUseNotManageTextureFlag(					void ) ;										// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���擾����( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			NS_SetTransColor(								int Red, int Green, int Blue ) ;				// �O���t�B�b�N�ɐݒ肷�铧�ߐF���Z�b�g����
extern	int			NS_GetTransColor(								int *Red, int *Green, int *Blue ) ;				// ���ߐF�𓾂�
extern	int			NS_SetUseDivGraphFlag(							int Flag ) ;									// �K�v�Ȃ�O���t�B�b�N�̕������s�����A�t���O�̃Z�b�g
extern	int			NS_SetUseMaxTextureSize(						int Size ) ;									// �g�p����e�N�X�`���[�̍ő�T�C�Y���Z�b�g(0�Ńf�t�H���g)
extern	int			NS_SetUseGraphBaseDataBackup(					int Flag ) ;									// �摜���쐬����ۂɎg�p�����摜�f�[�^�̃o�b�N�A�b�v�����ăf�o�C�X���X�g���Ɏg�p���邩�ǂ����̃t���O���Z�b�g����( TRUE:�o�b�N�A�b�v������( �f�t�H���g )  FALSE:�o�b�N�A�b�v�����Ȃ� )
extern	int			NS_GetUseGraphBaseDataBackup(					void ) ;										// �摜���쐬����ۂɎg�p�����摜�f�[�^�̃o�b�N�A�b�v�����ăf�o�C�X���X�g���Ɏg�p���邩�ǂ����̃t���O���擾����

// �摜���֌W�֐�
extern	DWORD*		NS_GetFullColorImage(				int GrHandle ) ;																		// �w��̉摜�̂`�q�f�a�W�̃t���J���[�C���[�W���擾����

extern	int			NS_GraphLock(						int GrHandle, int *PitchBuf, void **DataPointBuf, COLORDATA **ColorDataPP = NULL ) ;	// �O���t�B�b�N�������̈�̃��b�N
extern	int			NS_GraphUnLock(					int GrHandle ) ;																		// �O���t�B�b�N�������̈�̃��b�N����

extern	int			NS_SetUseGraphZBuffer(				int GrHandle, int UseFlag ) ;															// �O���t�B�b�N��p�̂y�o�b�t�@�������ǂ�����ݒ肷��( �`��\�摜�̂݉\ )
extern	int			NS_CopyGraphZBufferImage(			int DestGrHandle, int SrcGrHandle ) ;													// �O���t�B�b�N�̂y�o�b�t�@�̏�Ԃ�ʂ̃O���t�B�b�N�̂y�o�b�t�@�ɃR�s�[����( DestGrHandle �� SrcGrHandle ���y�o�b�t�@�������Ă���`��\�摜�ŁA�T�C�Y�������ł���A���A���`�G�C���A�X�摜�ł͂Ȃ����Ƃ����� )

extern	int			NS_GetGraphSize(					int GrHandle, int *SizeXBuf, int *SizeYBuf ) ;											// �O���t�B�b�N�̃T�C�Y�𓾂�
extern	int			NS_GetGraphTextureSize(			int GrHandle, int *SizeXBuf, int *SizeYBuf ) ;											// �O���t�B�b�N�Ɏg�p����Ă���e�N�X�`���[�̃T�C�Y�𓾂�
extern	int			NS_GetGraphMipmapCount(			int GrHandle ) ;																		// �O���t�B�b�N�����~�b�v�}�b�v���x���̐����擾����
extern	int			NS_GetGraphFilePath(				int GrHandle, TCHAR *FilePathBuffer ) ;													// �O���t�B�b�N�n���h�����摜�t�@�C������ǂݍ��܂�Ă����ꍇ�A���̉摜�̃t�@�C���p�X���擾����

extern	COLORDATA*	NS_GetTexColorData(				int AlphaCh, int AlphaTest, int ColorBitDepth, int DrawValid = FALSE ) ;				// �J���[�f�[�^�𓾂�
extern	COLORDATA*	NS_GetTexColorData(				IMAGEFORMATDESC *Format ) ;																// �t�H�[�}�b�g�Ɋ�Â����J���[�f�[�^�𓾂�
extern	COLORDATA*	NS_GetTexColorData(				int FormatIndex ) ;																		// �w��̃t�H�[�}�b�g�C���f�b�N�X�̃J���[�f�[�^�𓾂�
extern	int			NS_GetMaxGraphTextureSize(			int *SizeX, int *SizeY ) ;																// �O���t�B�b�N�Ɏg�p�����ő�e�N�X�`���T�C�Y���擾����
extern	int			NS_GetValidRestoreShredPoint(		void ) ;																				// �O���t�B�b�N�����֐��̗L�����擾																
extern	int			NS_GetCreateGraphColorData(		COLORDATA *ColorData, IMAGEFORMATDESC *Format ) ;										// ���ꂩ��V���ɃO���t�B�b�N���쐬����ꍇ�Ɏg�p����J���[�����擾����

// �摜�p���b�g����֌W�֐�( �\�t�g�E�G�A�摜�̂ݎg�p�\ )
extern	int			NS_GetGraphPalette(				int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ;						// ��������ɓǂݍ��񂾉摜�̃p���b�g���擾����(�t���J���[�摜�̏ꍇ�͖���)
extern	int			NS_GetGraphOriginalPalette(		int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ;						// ��������ɓǂݍ��񂾉摜�� SetGraphPalette �ŕύX����O�̃p���b�g���擾����
extern	int			NS_SetGraphPalette(				int GrHandle, int ColorIndex, int Color ) ;												// ��������ɓǂݍ��񂾉摜�̃p���b�g��ύX����(�t���J���[�摜�̏ꍇ�͖���)
extern	int			NS_ResetGraphPalette(				int GrHandle ) ;																		// SetGraphPalette �ŕύX�����p���b�g��S�Č��ɖ߂�

// �}�`�`��֐�
extern	int			NS_DrawLine(       int x1, int y1, int x2, int y2,                                 int Color, int Thickness = 1 ) ;									// ����`��
extern	int			NS_DrawBox(        int x1, int y1, int x2, int y2,                                 int Color, int FillFlag ) ;											// �l�p�`�̕`��
extern	int			NS_DrawFillBox(    int x1, int y1, int x2, int y2,                                 int Color ) ;														// ���g�̂���l�p��`��
extern	int			NS_DrawLineBox(    int x1, int y1, int x2, int y2,                                 int Color ) ;														// �l�p�`�̕`�� 
extern	int			NS_DrawCircle(     int x, int y, int r,                                            int Color, int FillFlag = TRUE ) ;									// �~��`��
extern	int			NS_DrawOval(       int x, int y, int rx, int ry,                                   int Color, int FillFlag ) ;											// �ȉ~��`��
extern	int			NS_DrawTriangle(   int x1, int y1, int x2, int y2, int x3, int y3,                 int Color, int FillFlag ) ;											// �O�p�`�̕`��
extern	int			NS_DrawQuadrangle( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int Color, int FillFlag ) ;											// �l�p�`�̕`��
extern	int			NS_DrawPixel(      int x, int y,                                                   int Color ) ;														// �_��`�悷��

extern	int			NS_Paint(			int x, int y, int FillColor, int BoundaryColor = -1 ) ;																				// �w��_���狫�E�F������Ƃ���܂œh��Ԃ�(���E�F�� -1 �ɂ���Ǝw��_�̐F�̗̈��h��Ԃ�)

extern	int			NS_DrawPixelSet(   POINTDATA *PointData, int Num ) ;																									// �_�̏W����`��
extern	int			NS_DrawLineSet(    LINEDATA *LineData,   int Num ) ;																									// ���̏W����`��

extern	int			NS_DrawPixel3D(    VECTOR Pos,                                                            int Color ) ;												// �R�c�̓_��`�悷��
extern	int			NS_DrawLine3D(     VECTOR Pos1, VECTOR Pos2,                                              int Color ) ;												// �R�c�̐�����`�悷��
extern	int			NS_DrawTriangle3D( VECTOR Pos1, VECTOR Pos2, VECTOR Pos3,                                 int Color, int FillFlag ) ;									// �R�c�̎O�p�`��`�悷��
extern	int			NS_DrawCube3D(     VECTOR Pos1, VECTOR Pos2,                             int DifColor, int SpcColor, int FillFlag ) ;									// �R�c�̗����̂�`�悷��
extern	int			NS_DrawSphere3D(   VECTOR CenterPos,                float r, int DivNum, int DifColor, int SpcColor, int FillFlag ) ;									// �R�c�̋��̂�`�悷��
extern	int			NS_DrawCapsule3D(  VECTOR Pos1, VECTOR Pos2,        float r, int DivNum, int DifColor, int SpcColor, int FillFlag ) ;									// �R�c�̃J�v�Z����`�悷��
extern	int			NS_DrawCone3D(     VECTOR TopPos, VECTOR BottomPos, float r, int DivNum, int DifColor, int SpcColor, int FillFlag ) ;									// �R�c�̉~����`�悷��

// �摜�`��֐�
extern	int			NS_LoadGraphScreen(          int x, int y, const TCHAR *GraphName, int TransFlag ) ;								// �a�l�o�t�@�C����ǂ݂���ŉ�ʂɕ`�悷��

extern	int			NS_DrawGraph(                int x, int y,                                                                 int GrHandle, int TransFlag ) ;										// �O���t�B�b�N�̕`��
extern	int			NS_DrawExtendGraph(          int x1, int y1, int x2, int y2,                                               int GrHandle, int TransFlag ) ;										// �O���t�B�b�N�̊g��k���`��
extern	int			NS_DrawRotaGraph(            int x, int y,                 double ExRate,                    double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;				// �O���t�B�b�N�̉�]�`��
extern	int			NS_DrawRotaGraph2(           int x, int y, int cx, int cy, double ExtRate,                   double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;				// �O���t�B�b�N�̉�]�`��Q
extern	int			NS_DrawRotaGraph3(           int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE ) ; 				// �O���t�B�b�N�̉�]�`��R
extern	int			NS_DrawModiGraph(            int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,               int GrHandle, int TransFlag ) ;										// �摜�̎��R�ό`�`��
extern	int			NS_DrawTurnGraph(            int x, int y,                                                                 int GrHandle, int TransFlag ) ;										// �摜�̍��E���]�`��

extern	int			NS_DrawGraphF(               float xf, float yf,                                                                       int GrHandle, int TransFlag ) ;							// �O���t�B�b�N�̕`��
extern	int			NS_DrawExtendGraphF(         float x1f, float y1f, float x2f, float y2,                                                int GrHandle, int TransFlag ) ;							// �O���t�B�b�N�̊g��k���`��
extern	int			NS_DrawRotaGraphF(           float xf, float yf,                       double ExRate,                    double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;	// �O���t�B�b�N�̉�]�`��
extern	int			NS_DrawRotaGraph2F(          float xf, float yf, float cxf, float cyf, double ExtRate,                   double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;	// �O���t�B�b�N�̉�]�`��Q
extern	int			NS_DrawRotaGraph3F(          float xf, float yf, float cxf, float cyf, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE ) ; 	// �O���t�B�b�N�̉�]�`��R
extern	int			NS_DrawModiGraphF(           float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,           int GrHandle, int TransFlag ) ;							// �摜�̎��R�ό`�`��( float �� )
extern	int			NS_DrawTurnGraphF(           float xf, float yf,                                                                       int GrHandle, int TransFlag ) ;							// �摜�̍��E���]�`��

extern	int			NS_DrawChipMap(              int Sx, int Sy, int XNum, int YNum, int *MapData, int ChipTypeNum, int MapDataPitch, int *ChipGrHandle, int TransFlag ) ;																											// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
extern	int			NS_DrawChipMap(              int MapWidth, int MapHeight,        int *MapData, int ChipTypeNum,                   int *ChipGrHandle, int TransFlag, int MapDrawPointX, int MapDrawPointY, int MapDrawWidth, int MapDrawHeight, int ScreenX, int ScreenY ) ;	// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
extern	int			NS_DrawTile(                 int x1, int y1, int x2, int y2, int Tx, int Ty, double ExtRate, double Angle, int GrHandle, int TransFlag ) ;																														// �O���t�B�b�N���w��̈�Ƀ^�C����ɕ`�悷��

extern	int			NS_DrawRectGraph(            int DestX,  int DestY,                          int SrcX, int SrcY, int    Width, int    Height,                         int GraphHandle, int TransFlag, int TurnFlag ) ;				// �O���t�B�b�N�̎w���`�����݂̂�`��
extern	int			NS_DrawRectExtendGraph(      int DestX1, int DestY1, int DestX2, int DestY2, int SrcX, int SrcY, int SrcWidth, int SrcHeight,                         int GraphHandle, int TransFlag ) ;							// �O���t�B�b�N�̎w���`�����݂̂��g��`��
extern	int			NS_DrawRectRotaGraph(        int x, int y, int SrcX, int SrcY, int Width, int Height, double ExtRate, double Angle,                                   int GraphHandle, int TransFlag, int TurnFlag ) ; 
extern	int			NS_DrawRectRotaGraph2(       int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, double ExtRate,  double Angle,                  int GraphHandle, int TransFlag, int TurnFlag ) ; 
extern	int			NS_DrawRectRotaGraph3(       int x, int y, int SrcX, int SrcY, int Width, int Height, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GraphHandle, int TransFlag, int TurnFlag ) ; 

extern	int			NS_DrawRectGraphF(           float DestX,  float DestY,                              int SrcX, int SrcY, int    Width, int    Height,                           int GraphHandle, int TransFlag, int TurnFlag ) ;	// �O���t�B�b�N�̎w���`�����݂̂�`��
extern	int			NS_DrawRectExtendGraphF(     float DestX1, float DestY1, float DestX2, float DestY2, int SrcX, int SrcY, int SrcWidth, int SrcHeight,                           int GraphHandle, int TransFlag ) ;					// �O���t�B�b�N�̎w���`�����݂̂��g��`��
extern	int			NS_DrawRectRotaGraphF(       float x, float y, int SrcX, int SrcY, int Width, int Height,                       double ExtRate,                   double Angle, int GraphHandle, int TransFlag, int TurnFlag ) ; 
extern	int			NS_DrawRectRotaGraph2F(      float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, double ExtRate,                   double Angle, int GraphHandle, int TransFlag, int TurnFlag ) ; 
extern	int			NS_DrawRectRotaGraph3F(      float x, float y, int SrcX, int SrcY, int Width, int Height, float cxf, float cyf, double ExtRateX, double ExtRateY, double Angle, int GraphHandle, int TransFlag, int TurnFlag ) ; 

extern	int			NS_DrawBlendGraph(           int x, int y, int GrHandle, int TransFlag,                 int BlendGraph, int BorderParam, int BorderRange ) ;									// �u�����h�摜�ƍ������ĉ摜��`�悷��
extern	int			NS_DrawBlendGraphPos(        int x, int y, int GrHandle, int TransFlag, int bx, int by, int BlendGraph, int BorderParam, int BorderRange ) ;									// �u�����h�摜�ƍ������ĉ摜��`�悷��( �u�����h�摜�̋N�_���W���w�肷��� )

extern	int			NS_DrawCircleGauge(          int CenterX, int CenterY, double Percent, int GrHandle ) ;																						// �~�O���t�I�ȕ`����s��( GrHandle �̉摜�̏㉺���E�̒[�͓��ߐF�ɂ��Ă����K�v������܂� )

extern	int			NS_DrawGraphToZBuffer(       int X, int Y,                                                                 int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̕`����s��
extern	int			NS_DrawTurnGraphToZBuffer(   int x, int y,                                                                 int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̍��E���]�`��
extern	int			NS_DrawExtendGraphToZBuffer( int x1, int y1, int x2, int y2,                                               int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̊g��k���`��
extern	int			NS_DrawRotaGraphToZBuffer(   int x, int y, double ExRate, double Angle,                                    int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int TurnFlag = FALSE ) ;		// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��
extern	int			NS_DrawRotaGraph2ToZBuffer(  int x, int y, int cx, int cy, double ExtRate,                   double Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int TurnFlag = FALSE ) ;		// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��Q
extern	int			NS_DrawRotaGraph3ToZBuffer(  int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int TurnFlag = FALSE ) ; 	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��R
extern	int			NS_DrawModiGraphToZBuffer(   int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,               int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ摜�̎��R�ό`�`��
extern	int			NS_DrawBoxToZBuffer(         int x1, int y1, int x2, int y2,                                               int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ċ�`�̕`����s��
extern	int			NS_DrawCircleToZBuffer(      int x, int y, int r,                                                          int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ĉ~�̕`����s��

extern	int			NS_DrawPolygon(                             VERTEX    *Vertex, int PolygonNum,                                                                                              int GrHandle, int TransFlag, int UVScaling = FALSE ) ;		// �Q�c�|���S����`�悷��( Vertex:�O�p�`���`�����钸�_�z��̐擪�A�h���X( ���_�̐��̓|���S���̐��~�R )  PolygonNum:�`�悷��|���S���̐�  GrHandle:�g�p����O���t�B�b�N�n���h��  TransFlag:���ߐF�������s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )  UVScaling:��{FALSE��OK )
extern	int			NS_DrawPolygon2D(                           VERTEX2D  *Vertex, int PolygonNum,                                                                                              int GrHandle, int TransFlag ) ;							// �Q�c�|���S����`�悷��
extern	int			NS_DrawPolygon3D(                           VERTEX3D  *Vertex, int PolygonNum,                                                                                              int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��
extern	int			NS_DrawPolygonIndexed2D(                    VERTEX2D  *Vertex, int VertexNum, unsigned short *Indices, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �Q�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygonIndexed3D(                    VERTEX3D  *Vertex, int VertexNum, unsigned short *Indices, int PolygonNum,                                                      int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )
extern	int			NS_DrawPolygonIndexed3DBase(                VERTEX_3D *Vertex, int VertexNum, unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���_�C���f�b�N�X���g�p )( ���o�[�W�����p )
extern	int			NS_DrawPolygon3DBase(                       VERTEX_3D *Vertex, int VertexNum,                                          int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���o�[�W�����p )
extern	int			NS_DrawPolygon3D(                           VERTEX_3D *Vertex, int PolygonNum,                                                                                              int GrHandle, int TransFlag ) ;							// �R�c�|���S����`�悷��( ���o�[�W�����p )

extern	int			NS_DrawPolygonBase(                         VERTEX    *Vertex, int VertexNum,                                          int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag, int UVScaling = FALSE ) ;		// �Q�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive2D(                         VERTEX2D  *Vertex, int VertexNum,                                          int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �Q�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3D(                         VERTEX3D  *Vertex, int VertexNum,                                          int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed2D(                  VERTEX2D  *Vertex, int VertexNum, unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �Q�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)
extern	int			NS_DrawPrimitiveIndexed3D(                  VERTEX3D  *Vertex, int VertexNum, unsigned short *Indices, int IndexNum,   int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int GrHandle, int TransFlag ) ;							// �R�c�v���~�e�B�u��`�悷��(���_�C���f�b�N�X�g�p)

extern	int			NS_DrawPolygon3D_UseVertexBuffer(           int VertexBufHandle,                                                                                                                                                               int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPrimitive3D_UseVertexBuffer(         int VertexBufHandle,                     int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                                                                                     int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3D_UseVertexBuffer2(        int VertexBufHandle,                     int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                 int StartVertex, int UseVertexNum,                                  int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPolygonIndexed3D_UseVertexBuffer(    int VertexBufHandle, int IndexBufHandle,                                                                                                                                           int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPrimitiveIndexed3D_UseVertexBuffer(  int VertexBufHandle, int IndexBufHandle, int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */,                                                                                     int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed3D_UseVertexBuffer2( int VertexBufHandle, int IndexBufHandle, int PrimitiveType  /* DX_PRIMTYPE_TRIANGLELIST �� */, int BaseVertex, int StartVertex, int UseVertexNum, int StartIndex, int UseIndexNum, int GrHandle, int TransFlag ) ;		// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���g�p���ĂR�c�v���~�e�B�u��`�悷��

extern	int			NS_DrawGraph3D(                             float x, float y, float z,                                                                     int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̂R�c�`��
extern	int			NS_DrawExtendGraph3D(                       float x, float y, float z, double ExRateX, double ExRateY,                                     int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̊g��R�c�`��
extern	int			NS_DrawRotaGraph3D(                         float x, float y, float z, double ExRate, double Angle,                                        int GrHandle, int TransFlag, int TurnFlag = FALSE ) ;		// �O���t�B�b�N�̉�]�R�c�`��
extern	int			NS_DrawRota2Graph3D(                        float x, float y, float z, float cx, float cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE ) ;		// �O���t�B�b�N�̉�]�R�c�`��(��]���S�w��^)
extern	int			NS_DrawModiBillboard3D(                     VECTOR Pos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,    int GrHandle, int TransFlag ) ;								// �O���t�B�b�N�̎��R�ό`�R�c�`��
extern	int			NS_DrawBillboard3D(                         VECTOR Pos, float cx, float cy, float Size, float Angle,                                       int GrHandle, int TransFlag, int TurnFlag = FALSE ) ;		// �R�c��ԏ�ɃO���t�B�b�N��`��


// �`��ݒ�֌W�֐�
extern	int			NS_SetDrawMode(						int DrawMode ) ;												// �`�惂�[�h���Z�b�g����
extern	int			NS_GetDrawMode(						void ) ;														// �`�惂�[�h���擾����
extern	int			NS_SetDrawBlendMode(					int BlendMode, int BlendParam ) ;								// �`��u�����h���[�h���Z�b�g����
extern	int			NS_GetDrawBlendMode(					int *BlendMode, int *BlendParam ) ;								// �`��u�����h���[�h���擾����
extern	int			NS_SetDrawAlphaTest(					int TestMode, int TestParam ) ;									// �`�掞�̃A���t�@�e�X�g�̐ݒ���s��( TestMode:DX_CMP_GREATER��( -1:�f�t�H���g����ɖ߂� )  TestParam:�`��A���t�@�l�Ƃ̔�r�Ɏg�p����l )
extern	int			NS_SetBlendGraph(						int BlendGraph, int BorderParam, int BorderRange ) ;			// ( SetBlendGraphParam �� BlendType = DX_BLENDGRAPHTYPE_WIPE �̏������s�����֐� )�`�揈�����ɕ`�悷��摜�ƃu�����h���郿�`�����l���t���摜���Z�b�g����( BlendGraph �� -1 �Ńu�����h�@�\�𖳌� )
extern	int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType, ... ) ;							// �`�揈�����ɕ`�悷��摜�ƃu�����h����摜�̃u�����h�ݒ���s���ABlendGraph �� -1 �ɂ���ΐݒ�������A���̏ꍇ BlendType �Ƃ��̌��̃p�����[�^�͖��������
//		int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType = DX_BLENDGRAPHTYPE_NORMAL, int Ratio = ( 0( �u�����h���O�� )�`255( �u�����h���P�O�O�� ) ) ) ;
//		int			NS_SetBlendGraphParam(					int BlendGraph, int BlendType = DX_BLENDGRAPHTYPE_WIPE, int BorderParam, int BorderRange ) ;
extern	int			NS_SetBlendGraphPosition(				int x, int y ) ;												// �u�����h�摜�̋N�_���W���Z�b�g����
extern	int			NS_SetDrawBright(						int RedBright, int GreenBright, int BlueBright ) ;				// �`��P�x���Z�b�g
extern	int			NS_GetDrawBright(						int *Red, int *Green, int *Blue ) ;								// �`��P�x���擾����
extern	int			NS_SetIgnoreDrawGraphColor(			int EnableFlag ) ;												// �`�悷��摜�̐F�����𖳎����邩�ǂ������w�肷��( EnableFlag:���̋@�\���g�����ǂ���( TRUE:�g��  FALSE:�g��Ȃ� ) )
extern	int			NS_SetMaxAnisotropy(					int MaxAnisotropy ) ;											// �ő�ٕ����̒l���Z�b�g����

extern	int			NS_SetUseZBufferFlag(					int Flag ) ;													// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetWriteZBufferFlag(				int Flag ) ;													// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetZBufferCmpType(					int CmpType /* DX_CMP_NEVER �� */ ) ;							// �y�l�̔�r���[�h���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetZBias(							int Bias ) ;													// �y�o�C�A�X���Z�b�g����( �Q�c�ƂR�c�`��ɉe�� )
extern	int			NS_SetUseZBuffer3D(					int Flag ) ;													// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetWriteZBuffer3D(					int Flag ) ;													// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetZBufferCmpType3D(				int CmpType /* DX_CMP_NEVER �� */ ) ;							// �y�l�̔�r���[�h���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetZBias3D(							int Bias ) ;													// �y�o�C�A�X���Z�b�g����( �R�c�}�`�`��݂̂ɉe�� )
extern	int			NS_SetDrawZ(							float Z ) ;														// �Q�c�`�掞�ɂy�o�b�t�@�ɏ������ނy�l��ύX����

extern	int			NS_SetDrawArea(						int x1, int y1, int x2, int y2 ) ;								// �`��\�̈�̃Z�b�g
extern	int			NS_GetDrawArea(						RECT *Rect ) ;													// �`��\�̈�𓾂�
extern	int			NS_SetDraw3DScale(						float Scale ) ;													// �R�c�`��̃X�P�[�����Z�b�g����
extern	int			NS_SetDrawAreaFull(					void ) ;														// �`��\�̈��`��Ώۉ�ʑS�̂ɂ���

extern	int			NS_SetRestoreShredPoint(				void (* ShredPoint )( void ) ) ;								// SetRestoreGraphCallback �̋���
extern	int			NS_SetRestoreGraphCallback(			void (* Callback )( void ) ) ;									// �O���t�B�b�N�n���h�������֐��̓o�^
extern	int			NS_RunRestoreShred(					void ) ;														// �O���t�B�b�N�����֐��̎��s
extern	int			NS_SetGraphicsDeviceRestoreCallbackFunction( void (* Callback )( void *Data ), void *CallbackData ) ;	// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A�����ۂɌĂ΂��R�[���o�b�N�֐���ݒ肷��
extern	int			NS_SetGraphicsDeviceLostCallbackFunction(    void (* Callback )( void *Data ), void *CallbackData ) ;	// �O���t�B�b�N�X�f�o�C�X�����X�g���畜�A����O�ɌĂ΂��R�[���o�b�N�֐���ݒ肷��

extern	int			NS_SetTransformToWorld(				MATRIX *Matrix ) ;												// ���[���h�ϊ��p�s����Z�b�g����
extern	int			NS_GetTransformToWorldMatrix(			MATRIX *MatBuf ) ;												// ���[���h�s����擾����
extern	int			NS_SetTransformToView(					MATRIX *Matrix ) ;												// �r���[�ϊ��p�s����Z�b�g����
extern	int			NS_GetTransformToViewMatrix(			MATRIX *MatBuf ) ;												// �r���[�s����擾����
extern	int			NS_SetTransformToProjection(			MATRIX *Matrix ) ;												// ���e�ϊ��p�s����Z�b�g����
extern	int			NS_GetTransformToProjectionMatrix(		MATRIX *MatBuf ) ;												// �ˉe�s����擾����
extern	int			NS_SetTransformToViewport(				MATRIX *Matrix ) ;												// �r���[�|�[�g�s����Z�b�g����
extern	int			NS_GetTransformToViewportMatrix(		MATRIX *MatBuf ) ;												// �r���[�|�[�g�s����擾����
extern	int			NS_GetTransformToAPIViewportMatrix(	MATRIX *MatBuf ) ;												// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����
extern	int			NS_SetDefTransformMatrix(				void ) ;														// �f�t�H���g�̕ϊ��s����Z�b�g����
extern	int			NS_GetTransformPosition(				VECTOR *LocalPos, float *x, float *y ) ;						// ���[�J�����W�����ʍ��W���擾����
extern	float		NS_GetBillboardPixelSize(				VECTOR WorldPos, float WorldSize ) ;							// ���[���h��ԏ�̃r���{�[�h�̃T�C�Y����X�N���[���ɓ��e�����ꍇ�̃s�N�Z���P�ʂ̃T�C�Y���擾����
extern	VECTOR		NS_ConvWorldPosToViewPos(				VECTOR WorldPos ) ;												// ���[���h���W���J�������W�ɕϊ�����
extern	VECTOR		NS_ConvWorldPosToScreenPos(			VECTOR WorldPos ) ;												// ���[���h���W���X�N���[�����W�ɕϊ�����
extern	FLOAT4		NS_ConvWorldPosToScreenPosPlusW(		VECTOR WorldPos ) ;												// ���[���h���W���X�N���[�����W�ɕϊ�����A�Ō�̂w�x�y���W���v�Ŋ���O�̒l�𓾂�
extern	VECTOR		NS_ConvScreenPosToWorldPos(			VECTOR ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����
extern	VECTOR		NS_ConvScreenPosToWorldPos_ZLinear(	VECTOR ScreenPos ) ;											// �X�N���[�����W�����[���h���W�ɕϊ�����( Z���W�����` )

extern	int			NS_SetUseCullingFlag(					int Flag ) ;													// SetUseBackCulling �̋�����
extern	int			NS_SetUseBackCulling(					int Flag /* DX_CULLING_LEFT �� */ ) ;							// �|���S���J�����O�̗L���A�������Z�b�g����

extern	int			NS_SetTextureAddressMode(				int Mode /* DX_TEXADDRESS_WRAP �� */ , int Stage = -1 ) ;		// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int			NS_SetTextureAddressModeUV(			int ModeU, int ModeV, int Stage = -1 ) ;						// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int			NS_SetTextureAddressTransform(			float TransU, float TransV, float ScaleU, float ScaleV, float RotCenterU, float RotCenterV, float Rotate ) ;	// �e�N�X�`�����W�ϊ��p�����[�^���Z�b�g����
extern	int			NS_SetTextureAddressTransformMatrix(	MATRIX Matrix ) ;												// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int			NS_ResetTextureAddressTransform(		void ) ;														// �e�N�X�`�����W�ϊ��p�����[�^�����Z�b�g����

extern	int			NS_SetFogEnable(						int Flag ) ;													// �t�H�O��L���ɂ��邩�ǂ�����ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int			NS_SetFogMode(							int Mode /* DX_FOGMODE_NONE �� */ ) ;							// �t�H�O���[�h��ݒ肷��
extern	int			NS_SetFogColor(						int r, int g, int b ) ;											// �t�H�O�J���[��ύX����
extern	int			NS_SetFogStartEnd(						float start, float end ) ;										// �t�H�O���n�܂鋗���ƏI�����鋗����ݒ肷��( 0.0f �` 1.0f )
extern	int			NS_SetFogDensity(						float density ) ;												// �t�H�O�̖��x��ݒ肷��( 0.0f �` 1.0f )


// ��ʊ֌W�֐�
extern	int				NS_GetPixel(									int x, int y ) ;																// �w����W�̐F���擾����
extern	int				NS_GetDrawScreenGraph(							                             int x1, int y1, int x2, int y2,                       int GrHandle, int UseClientFlag = TRUE ) ;	// �`���̉�ʂ���w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
extern	int				NS_BltDrawValidGraph(							int TargetDrawValidGrHandle, int x1, int y1, int x2, int y2, int DestX, int DestY, int DestGrHandle ) ;							// �`��\�O���t�B�b�N�n���h������w��̈�̉摜�����O���t�B�b�N�n���h���ɓ]������
extern	int				NS_ScreenFlip(									void ) ;																		// ����ʂƕ\��ʂ̓��e����������
extern 	int				NS_ScreenCopy(									void ) ;																		// ����ʂ̓��e��\��ʂɓ]������
extern	int				NS_WaitVSync(									int SyncNum ) ;																	// ���������M����҂�
extern	int				NS_ClearDrawScreen(					        RECT *ClearRect = NULL ) ;														// ��ʂ̏�Ԃ�����������
extern	int				NS_ClearDrawScreenZBuffer(						RECT *ClearRect = NULL ) ;														// ��ʂ̂y�o�b�t�@�̏�Ԃ�����������
extern	int				NS_ClsDrawScreen(								void ) ;																		// ��ʂ̏�Ԃ�����������(ClearDrawScreen�̋�����)
extern	int				NS_SetDrawScreen(								int DrawScreen ) ;																// �`����ʂ̃Z�b�g
extern	int				NS_GetDrawScreen(								void ) ;																		// �`����ʂ̎擾
extern	int				NS_GetActiveGraph(								void ) ;																		// GetDrawScreen �̋�����
extern	int				NS_SetDrawZBuffer(								int DrawScreen ) ;																// �`���y�o�b�t�@�̃Z�b�g( DrawScreen �t���̂y�o�b�t�@��`���y�o�b�t�@�ɂ���ADrawScreen �� -1 �ɂ���ƃf�t�H���g�̕`���y�o�b�t�@�ɖ߂� )
#ifdef __WINDOWS__
extern	int				NS_BltBackScreenToWindow(						HWND Window, int ClientX, int ClientY ) ;										// ����ʂ̓��e���w��̃E�C���h�E�ɓ]������
extern	int				NS_BltRectBackScreenToWindow(					HWND Window, RECT BackScreenRect, RECT WindowClientRect ) ;						// ����ʂ̎w��̗̈���E�C���h�E�̃N���C�A���g�̈�̎w��̗̈�ɓ]������
#endif // __WINDOWS__
extern	int				NS_SetGraphMode(								int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate = 60 ) ;	// ��ʃ��[�h��ݒ肷��
extern	int				NS_SetEmulation320x240(						int Flag ) ;																	// �U�S�O���S�W�O�̉�ʂłR�Q�O���Q�S�O�̉�ʉ𑜓x�ɂ��邩�ǂ����̃t���O���Z�b�g����A�U�S�O���S�W�O�ȊO�̉𑜓x�ł͖���( TRUE:�L��  FALSE:���� )
extern	int				NS_SetZBufferSize(								int ZBufferSizeX, int ZBufferSizeY ) ;											// ��ʗp�̂y�o�b�t�@�̃T�C�Y��ݒ肷��
extern	int				NS_SetWaitVSyncFlag(							int Flag ) ;																	// �u�r�x�m�b�҂������邩�̃t���O�Z�b�g
extern	int				NS_GetWaitVSyncFlag(							void ) ;																		// �u�r�x�m�b�҂�������ݒ�ɂȂ��Ă��邩�ǂ������擾����
extern	int				NS_SetFullSceneAntiAliasingMode(				int Samples, int Quality ) ;													// ��ʂ̃t���X�N���[���A���`�G�C���A�X���[�h�̐ݒ������( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int				NS_SetGraphDisplayArea(						int x1, int y1, int x2, int y2 ) ;												// ScreenFlip ���ɕ\��ʑS�̂ɓ]�����闠��ʂ̗̈��ݒ肷��( DxLib_Init �̑O�ł̂ݎg�p�\ )
extern	int				NS_SetChangeScreenModeGraphicsSystemResetFlag(	int Flag ) ;																	// ��ʃ��[�h�ύX��( �ƃE�C���h�E���[�h�ύX�� )�ɃO���t�B�b�N�X�V�X�e���̐ݒ��O���t�B�b�N�n���h�������Z�b�g���邩�ǂ�����ݒ肷��( TRUE:���Z�b�g����  FALSE:���Z�b�g���Ȃ� )
extern	int				NS_GetScreenState(								int *SizeX, int *SizeY, int *ColorBitDepth ) ;									// ���݂̉�ʂ̑傫���ƃJ���[�r�b�g���𓾂� 
extern	int				NS_GetDrawScreenSize(							int *XBuf, int *YBuf ) ;														// �`��T�C�Y���擾����
extern	int				NS_GetScreenBitDepth(							void ) ;																		// �g�p�F�r�b�g����Ԃ�
extern	int				NS_GetColorBitDepth(							void ) ;																		// ��ʂ̐F�r�b�g�[�x�𓾂�
extern	int				NS_GetChangeDisplayFlag(						void ) ;																		// ��ʃ��[�h���ύX����Ă��邩�ǂ����̃t���O���擾����
extern	int				NS_GetVideoMemorySize(							int *AllSize, int *FreeSize ) ;													// �r�f�I�������̗e�ʂ𓾂�
extern	int				NS_GetRefreshRate(								void ) ;																		// ���݂̉�ʂ̃��t���b�V�����[�g���擾����
extern	int				NS_GetDisplayModeNum(							void ) ;																		// �ύX�\�ȃf�B�X�v���C���[�h�̐����擾����
extern	DISPLAYMODEDATA	NS_GetDisplayMode(								int ModeIndex ) ;																// �ύX�\�ȃf�B�X�v���C���[�h�̏����擾����( ModeIndex �� 0 �` GetDisplayModeNum �̖߂�l-1 )
extern	COLORDATA*		NS_GetDispColorData(							void ) ;																		// �f�B�X�v���[�̃J���[�f�[�^�|�C���^�𓾂�
extern	int				NS_GetMultiDrawScreenNum(						void ) ;																		// �����ɕ`����s�����Ƃ��ł����ʂ̐����擾����
extern	int				NS_SetDisplayRefreshRate(						int RefreshRate ) ;																// ( ���݌��ʂȂ� )�t���X�N���[�����̉�ʂ̃��t���b�V�����[�g��ύX����

// ���̑��ݒ�֌W�֐�
extern	int			NS_SetUseNormalDrawShader(						int Flag ) ;									// �ʏ�`��Ƀv���O���}�u���V�F�[�_�[���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
extern	int			NS_SetUseSoftwareRenderModeFlag(				int Flag ) ;									// �\�t�g�E�G�A�����_�����O���[�h���g�p���邩�ǂ������Z�b�g����
extern	int			NS_SetNotUse3DFlag(							int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�R�c�@�\���g��Ȃ��t���O�̃Z�b�g�A���ʂ� SetUse3DFlag �Ɠ���
extern	int			NS_SetUse3DFlag(								int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�R�c�@�\���g�����A�̃t���O���Z�b�g
extern	int			NS_GetUse3DFlag(								void ) ;										// �`��ɂR�c�@�\���g�����t���O���擾
extern	int			NS_SetScreenMemToVramFlag(						int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )��ʃf�[�^���u�q�`�l�ɒu�����A�t���O
extern	int			NS_GetScreenMemToSystemMemFlag(				void ) ;										// ��ʃO���t�B�b�N�f�[�^���V�X�e���������ɑ��݂��邩�t���O�̎擾

extern	int			NS_SetUseBasicGraphDraw3DDeviceMethodFlag(		int Flag ) ;									// �P���}�`�̕`��ɂR�c�f�o�C�X�̋@�\���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetWindowDrawRect(							RECT *DrawRect ) ;								// �ʏ�g�p���Ȃ�
extern	int			NS_RestoreGraphSystem(							void ) ;										// �c�w���C�u�����̃O���t�B�b�N�֘A�̕��A�������s��
extern	int			NS_SetAeroDisableFlag(							int Flag ) ;									// Vista�ȍ~�� Windows Aero �𖳌��ɂ��邩�ǂ������Z�b�g����ATRUE:�����ɂ���  FALSE:�L���ɂ���( DxLib_Init �̑O�ɌĂԕK�v������܂� )
extern	int			NS_SetUseDirect3D9Ex(							int Flag ) ;									// Vista�ȍ~�̊��� Direct3D9Ex ���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )( DxLib_Init �̑O�ɌĂԕK�v������܂� )
extern	int			NS_SetUseHardwareVertexProcessing(				int Flag ) ;									// �n�[�h�E�G�A�̒��_���Z�����@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMultiThreadFlag(							int Flag ) ;									// DirectDraw �� Direct3D �̋������x�����}���`�X���b�h�Ή��ɂ��邩�ǂ������Z�b�g����
extern	int			NS_SetUseDirectDrawDeviceIndex(				int Index ) ;									// �g�p���� DirectDraw �f�o�C�X�̃C���f�b�N�X��ݒ肷��
extern	int			NS_SetUseOldDrawModiGraphCodeFlag(				int Flag ) ;									// �ȑO�� DrawModiGraph �֐��̃R�[�h���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			NS_SetUseVramFlag(								int Flag ) ;									// ( ���݌��ʂȂ� )�u�q�`�l���g�p���邩�̃t���O���Z�b�g����
extern	int			NS_GetUseVramFlag(								void ) ;										// ( ���݌��ʂȂ� )�Q�c�O���t�B�b�N�T�[�t�F�X�쐬���ɃV�X�e���������[���g�p���邩�̃t���O�擾
extern	int			NS_SetBasicBlendFlag(							int Flag ) ;									// ( ���݌��ʂȂ� )�ȗ����u�����h�������s�����ۂ��̃t���O���Z�b�g����
#ifdef __WINDOWS__
extern	int			NS_SetUseDirectDrawFlag(						int Flag ) ;									// ( �����ʂ�SetUseSoftwareRenderModeFlag ���g�p���ĉ����� )�c�����������c���������g�p���邩�ǂ������Z�b�g����
extern	int			NS_SetUseGDIFlag(								int Flag ) ;									// �f�c�h�`���K�v�Ƃ��邩�A��ύX����
extern	int			NS_SetDDrawUseGuid(							GUID *Guid ) ;									// �c�����������c���������g�p����f�t�c�h��ݒ肷��
extern	void*		NS_GetUseDDrawObj(								void ) ;										// ���ݎg�p���Ă���c�����������c�������I�u�W�F�N�g�̃A�h���X���擾����( �߂�l�� IDirectDraw7 * �ɃL���X�g���ĉ����� )
extern	GUID*		NS_GetDirectDrawDeviceGUID(					int Number ) ;									// �L���� DirectDraw �f�o�C�X�� GUID ���擾����
extern	int			NS_GetDirectDrawDeviceDescription(				int Number, char *StringBuffer ) ;				// �L���� DirectDraw �f�o�C�X�̖��O�𓾂�
extern	int			NS_GetDirectDrawDeviceNum(						void ) ;										// �L���� DirectDraw �f�o�C�X�̐����擾����
extern	int			NS_GetUseGDIFlag(								void ) ;										// �f�c�h�`���K�v�Ƃ��邩�̏�Ԃ��擾����
extern	DX_DIRECT3DDEVICE9* NS_GetUseDirect3DDevice9(				void ) ;										// �g�p���̂c�����������R�c�c�����������X�I�u�W�F�N�g�𓾂�
extern	DX_DIRECT3DSURFACE9 *NS_GetUseDirect3D9BackBufferSurface(	void ) ;										// �g�p���̃o�b�N�o�b�t�@��Direct3DSurface9�I�u�W�F�N�g���擾����
#endif // __WINDOWS__
extern	int			NS_RefreshDxLibDirect3DSetting(				void ) ;										// �c�w���C�u�����̂c�����������R�c�ݒ�����Ȃ���( ����p�r )
extern	int			NS_RenderVertex(								void ) ;										// ���_�o�b�t�@�ɗ��܂������_�f�[�^��f���o��( ����p�r )

#ifndef DX_NON_SAVEFUNCTION

// �`����ʕۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
extern	int			NS_SaveDrawScreen(       int x1, int y1, int x2, int y2, const TCHAR *FileName, int SaveType = DX_IMAGESAVETYPE_BMP , int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// ���ݕ`��ΏۂɂȂ��Ă����ʂ�ۑ�����
extern	int			NS_SaveDrawScreenToBMP(  int x1, int y1, int x2, int y2, const TCHAR *FileName ) ;																																	// ���ݕ`��ΏۂɂȂ��Ă����ʂ��a�l�o�`���ŕۑ�����
extern	int			NS_SaveDrawScreenToJPEG( int x1, int y1, int x2, int y2, const TCHAR *FileName, int Quality = 80 , int Sample2x1 = TRUE ) ;																						// ���ݕ`��ΏۂɂȂ��Ă����ʂ��i�o�d�f�`���ŕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
extern	int			NS_SaveDrawScreenToPNG(  int x1, int y1, int x2, int y2, const TCHAR *FileName, int CompressionLevel = -1 ) ;																										// ���ݕ`��ΏۂɂȂ��Ă����ʂ��o�m�f�`���ŕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9

#endif // DX_NON_SAVEFUNCTION

// ���_�o�b�t�@�֌W�֐�
extern	int			NS_CreateVertexBuffer(		int VertexNum, int VertexType /* DX_VERTEX_TYPE_NORMAL_3D �� */ ) ;						// ���_�o�b�t�@���쐬����( -1:�G���[  0�ȏ�:���_�o�b�t�@�n���h�� )
extern	int			NS_DeleteVertexBuffer(		int VertexBufHandle ) ;																	// ���_�o�b�t�@���폜����
extern	int			NS_InitVertexBuffer(		void ) ;																				// ���ׂĂ̒��_�o�b�t�@���폜����
extern	int			NS_SetVertexBufferData(	int SetIndex, void *VertexData, int VertexNum, int VertexBufHandle ) ;					// ���_�o�b�t�@�ɒ��_�f�[�^��]������
extern	int			NS_CreateIndexBuffer(		int IndexNum, int IndexType /* DX_INDEX_TYPE_16BIT �� */  ) ;							// �C���f�b�N�X�o�b�t�@���쐬����( -1:�G���[�@0�ȏ�F�C���f�b�N�X�o�b�t�@�n���h�� )
extern	int			NS_DeleteIndexBuffer(		int IndexBufHandle ) ;																	// �C���f�b�N�X�o�b�t�@���폜����
extern	int			NS_InitIndexBuffer(		void ) ;																				// ���ׂẴC���f�b�N�X�o�b�t�@���폜����
extern	int			NS_SetIndexBufferData(		int SetIndex, void *IndexData, int IndexNum, int IndexBufHandle ) ;						// �C���f�b�N�X�o�b�t�@�ɃC���f�b�N�X�f�[�^��]������

// �V�F�[�_�[�֌W�֐�
extern	int			NS_GetValidShaderVersion(		void ) ;												// �g�p�ł���V�F�[�_�[�̃o�[�W�������擾����( 0=�g���Ȃ�  200=�V�F�[�_�[���f���Q�D�O���g�p�\  300=�V�F�[�_�[���f���R�D�O���g�p�\ )

extern	int			NS_LoadVertexShader(			const TCHAR *FileName ) ;								// ���_�V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��ݒ��_�V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadPixelShader(			const TCHAR *FileName ) ;								// �s�N�Z���V�F�[�_�[�o�C�i�����t�@�C������ǂݍ��݃s�N�Z���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadVertexShaderFromMem(	void *ImageAddress, int ImageSize ) ;					// ��������ԏ�ɑ��݂��钸�_�V�F�[�_�[�o�C�i�����璸�_�V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_LoadPixelShaderFromMem(		void *ImageAddress, int ImageSize ) ;					// ��������ԏ�ɑ��݂���s�N�Z���V�F�[�_�[�o�C�i������s�N�Z���V�F�[�_�[�n���h�����쐬����( �߂�l -1:�G���[  -1�ȊO:�V�F�[�_�[�n���h�� )
extern	int			NS_DeleteShader(				int ShaderHandle ) ;									// �V�F�[�_�[�n���h���̍폜
extern	int			NS_InitShader(					void ) ;												// �V�F�[�_�[�n���h����S�č폜����

extern	int			NS_GetConstIndexToShader(           const TCHAR *ConstantName, int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̔ԍ����擾����
extern	int			NS_GetConstCountToShader(           const TCHAR *ConstantName, int ShaderHandle ) ;	// �w��̖��O�����萔���g�p����V�F�[�_�[�萔�̐����擾����
extern	const FLOAT4 *NS_GetConstDefaultParamFToShader( const TCHAR *ConstantName, int ShaderHandle ) ;	// �w��̖��O�������������_�萔�̃f�t�H���g�p�����[�^���i�[����Ă��郁�����A�h���X���擾����
extern	int			NS_SetVSConstSF(         int ConstantIndex, float  Param ) ;							// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetVSConstF(          int ConstantIndex, FLOAT4 Param ) ;							// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetVSConstFMtx(       int ConstantIndex, MATRIX Param ) ;							// ���_�V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��
extern	int			NS_SetVSConstFMtxT(      int ConstantIndex, MATRIX Param ) ;							// ���_�V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��
extern	int			NS_SetVSConstSI(         int ConstantIndex, int    Param ) ;							// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetVSConstI(          int ConstantIndex, INT4   Param ) ;							// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetVSConstB(          int ConstantIndex, BOOL   Param ) ;							// ���_�V�F�[�_�[�� BOOL �^�萔��ݒ肷��
extern	int			NS_SetVSConstSFArray(    int ConstantIndex, float  *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFArray(     int ConstantIndex, FLOAT4 *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFMtxArray(  int ConstantIndex, MATRIX *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstFMtxTArray( int ConstantIndex, MATRIX *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstSIArray(    int ConstantIndex, int    *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstIArray(     int ConstantIndex, INT4   *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� int �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetVSConstBArray(     int ConstantIndex, BOOL   *ParamArray, int ParamNum ) ;		// ���_�V�F�[�_�[�� BOOL �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_ResetVSConstF(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� float �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetVSConstI(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� int �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetVSConstB(        int ConstantIndex, int ParamNum ) ;							// ���_�V�F�[�_�[�� BOOL �^�萔�̐ݒ�����Z�b�g����

extern	int			NS_SetPSConstSF(         int ConstantIndex, float  Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetPSConstF(          int ConstantIndex, FLOAT4 Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��
extern	int			NS_SetPSConstFMtx(       int ConstantIndex, MATRIX Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��
extern	int			NS_SetPSConstFMtxT(      int ConstantIndex, MATRIX Param ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��
extern	int			NS_SetPSConstSI(         int ConstantIndex, int    Param ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetPSConstI(          int ConstantIndex, INT4   Param ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��
extern	int			NS_SetPSConstB(          int ConstantIndex, BOOL   Param ) ;							// �s�N�Z���V�F�[�_�[�� BOOL �^�萔��ݒ肷��
extern	int			NS_SetPSConstSFArray(    int ConstantIndex, float  *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFArray(     int ConstantIndex, FLOAT4 *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� float �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFMtxArray(  int ConstantIndex, MATRIX *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� float �^�萔�ɍs���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstFMtxTArray( int ConstantIndex, MATRIX *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� float �^�萔�ɓ]�u�����s���ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstSIArray(    int ConstantIndex, int    *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstIArray(     int ConstantIndex, INT4   *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� int �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_SetPSConstBArray(     int ConstantIndex, BOOL   *ParamArray, int ParamNum ) ;		// �s�N�Z���V�F�[�_�[�� BOOL �^�萔��ݒ肷��( �z����g���ĘA�ԃC���f�b�N�X�Ɉ�x�ɐݒ� )
extern	int			NS_ResetPSConstF(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� float �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetPSConstI(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� int �^�萔�̐ݒ�����Z�b�g����
extern	int			NS_ResetPSConstB(        int ConstantIndex, int ParamNum ) ;							// �s�N�Z���V�F�[�_�[�� BOOL �^�萔�̐ݒ�����Z�b�g����

extern	int			NS_SetRenderTargetToShader( int TargetIndex, int DrawScreen ) ;						// �V�F�[�_�[�`��ł̕`����ݒ肷��
extern	int			NS_SetUseTextureToShader(   int StageIndex, int GraphHandle ) ;						// �V�F�[�_�[�`��Ŏg�p����O���t�B�b�N��ݒ肷��
extern	int			NS_SetUseVertexShader(      int ShaderHandle ) ;										// �V�F�[�_�[�`��Ɏg�p���钸�_�V�F�[�_�[��ݒ肷��( -1��n���Ɖ��� )
extern	int			NS_SetUsePixelShader(       int ShaderHandle ) ;										// �V�F�[�_�[�`��Ɏg�p����s�N�Z���V�F�[�_�[��ݒ肷��( -1��n���Ɖ��� )

extern	int			NS_CalcPolygonBinormalAndTangentsToShader(        VERTEX3DSHADER *Vertex, int PolygonNum ) ;												// �|���S���̒��_�̐ڐ��Ə]�@�����t�u���W����v�Z���ăZ�b�g����
extern	int			NS_CalcPolygonIndexedBinormalAndTangentsToShader( VERTEX3DSHADER *Vertex, int VertexNum, unsigned short *Indices, int PolygonNum ) ;		// �|���S���̒��_�̐ڐ��Ə]�@�����t�u���W����v�Z���ăZ�b�g����(�C���f�b�N�X)

extern	int			NS_DrawPolygon2DToShader(          VERTEX2DSHADER *Vertex, int PolygonNum ) ;																												// �V�F�[�_�[���g���ĂQ�c�|���S����`�悷��
extern	int			NS_DrawPolygon3DToShader(          VERTEX3DSHADER *Vertex, int PolygonNum ) ;																												// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��
extern	int			NS_DrawPolygonIndexed2DToShader(   VERTEX2DSHADER *Vertex, int VertexNum, unsigned short *Indices, int PolygonNum ) ;																		// �V�F�[�_�[���g���ĂQ�c�|���S����`�悷��(�C���f�b�N�X)
extern	int			NS_DrawPolygonIndexed3DToShader(   VERTEX3DSHADER *Vertex, int VertexNum, unsigned short *Indices, int PolygonNum ) ;																		// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��(�C���f�b�N�X)
extern	int			NS_DrawPrimitive2DToShader(        VERTEX2DSHADER *Vertex, int VertexNum,                                        int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;					// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitive3DToShader(        VERTEX3DSHADER *Vertex, int VertexNum,                                        int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;					// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��
extern	int			NS_DrawPrimitiveIndexed2DToShader( VERTEX2DSHADER *Vertex, int VertexNum, unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;					// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��(�C���f�b�N�X)
extern	int			NS_DrawPrimitiveIndexed3DToShader( VERTEX3DSHADER *Vertex, int VertexNum, unsigned short *Indices, int IndexNum, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;					// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��(�C���f�b�N�X)
extern	int			NS_DrawPolygon3DToShader_UseVertexBuffer(           int VertexBufHandle ) ;																												// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPolygonIndexed3DToShader_UseVertexBuffer(    int VertexBufHandle, int IndexBufHandle ) ;																							// �V�F�[�_�[���g���ĂR�c�|���S����`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitive3DToShader_UseVertexBuffer(         int VertexBufHandle,                     int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;										// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitive3DToShader_UseVertexBuffer2(        int VertexBufHandle,                     int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int StartVertex, int UseVertexNum ) ;	// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer(  int VertexBufHandle, int IndexBufHandle, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */ ) ;										// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )
extern	int			NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer2( int VertexBufHandle, int IndexBufHandle, int PrimitiveType /* DX_PRIMTYPE_TRIANGLELIST �� */, int BaseVertex, int StartVertex, int UseVertexNum, int StartIndex, int UseIndexNum ) ;	// �V�F�[�_�[���g���ĂR�c�v���~�e�B�u��`�悷��( ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�g�p�� )

// �t�B���^�[�֌W�֐�
#ifndef DX_NON_FILTER
extern	int			NS_GraphFilter(        int    GrHandle,                                                                                     int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�Ƀt�B���^�[�������s��
extern	int			NS_GraphFilterBlt(     int SrcGrHandle, int DestGrHandle,                                                                   int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��
extern	int			NS_GraphFilterRectBlt( int SrcGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int DestX, int DestY, int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��( ��`�w�� )
extern	int			NS_GraphFilterRectBlt2( int SrcGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int DestX1, int DestY1, int DestX2, int DestY2, int FilterType /* DX_GRAPH_FILTER_GAUSS �� */ , ... ) ;		// �摜�̃t�B���^�[�t���]�����s��( ��`�w���R )
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_MONO, int Cb = �F��( -255 �` 255 ), int Cr = �ԐF��( -255 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_GAUSS, int PixelWidth = �g�p�s�N�Z����( 8 , 16 , 32 �̉��ꂩ ), int Param = �ڂ����p�����[�^( 100 �Ŗ�1�s�N�Z�����̕� ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_DOWN_SCALE, int DivNum = ���̃T�C�Y�̉����̂P���A�Ƃ����l( 2 , 4 , 8 �̉��ꂩ ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_BRIGHT_CLIP, int CmpType = �N���b�v�^�C�v( DX_CMP_LESS:CmpParam�ȉ����N���b�v  ����  DX_CMP_GREATER:CmpParam�ȏ���N���b�v ), int CmpParam = �N���b�v�p�����[�^( 0 �` 255 ), int ClipFillFlag = �N���b�v�����s�N�Z����h��Ԃ����ǂ���( TRUE:�h��Ԃ�  FALSE:�h��Ԃ��Ȃ� ), int ClipFillColor = �N���b�v�����s�N�Z���ɓh��F�l( GetColor �Ŏ擾���� )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ), int ClipFillAlpha = �N���b�v�����s�N�Z���ɓh�郿�l( 0 �` 255 )( ClipFillFlag �� FALSE �̏ꍇ�͎g�p���Ȃ� ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_HSB, int HueType = Hue �̈Ӗ�( 0:���Βl  1:��Βl ), int Hue = �F���p�����[�^( HueType �� 0 �̏ꍇ = �s�N�Z���̐F���ɑ΂��鑊�Βl( -180 �` 180 )   HueType �� 1 �̏ꍇ = �F���̐�Βl( 0 �` 360 ) ), int Saturation = �ʓx( -255 �` ), int Bright = �P�x( -255 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_INVERT ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_LEVEL, int Min = �ϊ����̉����l( 0 �` 255 ), int Max = �ϊ����̏���l( 0 �` 255 ), int Gamma = �K���}�l( 100 �ŃK���}�␳�����A0 �Ƃ���ȉ��̒l�͕s�� ), int AfterMin = �ϊ���̍Œ�l( 0 �` 255 ), int AfterMax = �ϊ���̍ő�l( 0 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_TWO_COLOR, int Threshold = 臒l( 0 �` 255 ), int LowColor = 臒l���l���Ⴉ�����s�N�Z���̕ϊ���̐F�l( GetColor �Ŏ擾���� ), int LowAlpha = 臒l���l���Ⴉ�����s�N�Z���̕ϊ���̃��l( 0 �` 255 ), int HighColor = 臒l���l�����������s�N�Z���̕ϊ���̐F�l( GetColor �Ŏ擾���� ), int HighAlpha = 臒l���l�����������s�N�Z���̕ϊ���̃��l( 0 �` 255 ) ) ;
//		int			GraphFilter( int GrHandle, int FilterType = DX_GRAPH_FILTER_GRADIENT_MAP, int MapGrHandle = �O���f�[�V�����}�b�v�̃O���t�B�b�N�n���h��( ���摜�̋P�x����O���f�[�V�����}�b�v�摜�� x ���W���Z�o���܂��̂ŏc����1dot�ł��n�j ), int Reverse = �O���f�[�V�����}�b�v���E���]�t���O( TRUE : �O���f�[�V�����}�b�v�����E���]���Ďg��  FALSE : ���E���]���Ȃ� ) ) ;

extern	int			NS_GraphBlend(        int    GrHandle, int BlendGrHandle,                                                                                                             int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h����
extern	int			NS_GraphBlendBlt(     int SrcGrHandle, int BlendGrHandle, int DestGrHandle,                                                                                           int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���
extern	int			NS_GraphBlendRectBlt( int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX, int BlendY, int DestX, int DestY, int BlendRatio /* �u�����h���ʂ̉e���x( 0:�O��  255:�P�O�O�� ) */ , int BlendType /* DX_GRAPH_BLEND_ADD �� */ , ... ) ;	// ��̉摜���u�����h���Č��ʂ��w��̉摜�ɏo�͂���( ��`�w�� )
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_NORMAL ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_RGBA_SELECT_MIX, int SelectR = ( �o�͂̐ԕ��ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectG = ( �o�̗͂ΐ����ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectB = ( �o�͂̐����ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ), int SelectA = ( �o�͂̃������ƂȂ鐬�� DX_RGBA_SELECT_SRC_R �� ) ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_MULTIPLE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DIFFERENCE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_ADD ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SCREEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_OVERLAY ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DODGE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_BURN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_DARKEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_LIGHTEN ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SOFTLIGHT ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_HARDLIGHT ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_EXCLUSION ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_HUE ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_SATURATION ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_COLOR ) ;
//		int			GraphBlend( int GrHandle, int BlendGrHandle, int BlendRatio, int BlendType = DX_GRAPH_BLEND_BRIGHT ) ;
#endif // DX_NON_FILTER

#ifndef DX_NON_MOVIE
// ���[�r�[�O���t�B�b�N�֌W�֐�
extern	int			NS_PlayMovie(						const TCHAR *FileName, int ExRate, int PlayType ) ;						// ����t�@�C���̍Đ�
extern	int			NS_OpenMovieToGraph(				const TCHAR *FileName, int FullColor = TRUE ) ;							// ���[�r�[���J��
extern	int			NS_PlayMovieToGraph(				int GraphHandle, int PlayType = DX_PLAYTYPE_BACK , int SysPlay = 0 ) ;	// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����J�n����
extern	int			NS_PauseMovieToGraph(				int GraphHandle, int SysPause = 0 ) ;									// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����X�g�b�v����
extern	int			NS_AddMovieFrameToGraph(			int GraphHandle, unsigned int FrameNum ) ;								// ���[�r�[�̃t���[����i�߂�A�߂����Ƃ͏o���Ȃ�( ���[�r�[����~��ԂŁA���� Ogg Theora �̂ݗL�� )
extern	int			NS_SeekMovieToGraph(				int GraphHandle, int Time ) ;											// ���[�r�[�̍Đ��ʒu��ݒ肷��(�~���b�P��)
extern	int			NS_GetMovieStateToGraph(			int GraphHandle ) ;														// ���[�r�[�̍Đ���Ԃ𓾂�
extern	int			NS_SetMovieVolumeToGraph(			int Volume, int GraphHandle ) ;											// ���[�r�[�̃{�����[�����Z�b�g����(0�`10000)
extern	int			NS_ChangeMovieVolumeToGraph(		int Volume, int GraphHandle ) ;											// ���[�r�[�̃{�����[�����Z�b�g����(0�`255)
extern	BASEIMAGE*	NS_GetMovieBaseImageToGraph(		int GraphHandle ) ;														// ���[�r�[�̊�{�C���[�W�f�[�^���擾����
extern	int			NS_GetMovieTotalFrameToGraph(		int GraphHandle ) ;														// ���[�r�[�̑��t���[�����𓾂�( Ogg Theora �ł̂ݗL�� )
extern	int			NS_TellMovieToGraph(				int GraphHandle ) ;														// ���[�r�[�̍Đ��ʒu���擾����(�~���b�P��)
extern	int			NS_TellMovieToGraphToFrame(		int GraphHandle ) ;														// ���[�r�[�̍Đ��ʒu���擾����(�t���[���P��)
extern	int			NS_SeekMovieToGraphToFrame(		int GraphHandle, int Frame ) ;											// ���[�r�[�̍Đ��ʒu��ݒ肷��(�t���[���P��)
extern	LONGLONG	NS_GetOneFrameTimeMovieToGraph(	int GraphHandle ) ;														// ���[�r�[�̂P�t���[��������̎��Ԃ𓾂�
extern	int			NS_GetLastUpdateTimeMovieToGraph(	int GraphHandle ) ;														// ���[�r�[�̃C���[�W���Ō�ɍX�V�������Ԃ𓾂�(�~���b�P��)
extern	int			NS_SetMovieRightImageAlphaFlag(	int Flag ) ;															// ����t�@�C���̉E�����̐Ԑ��������A���t�@���Ƃ��Ĉ������ǂ������Z�b�g����( TRUE:�A���t�@���Ƃ��Ĉ��� )
#endif

// �J�����֌W�֐�
extern	int			NS_SetCameraNearFar(					float Near, float Far ) ;											// �J������ Near�N���b�v�ʂ� Far�N���b�v�ʂ̋�����ݒ肷��
extern	int			NS_SetCameraPositionAndTarget_UpVecY(  VECTOR Position, VECTOR Target ) ;									// �J�����̐ݒ������A���_�A�����_�A�A�b�v�x�N�g���͂x����
extern	int			NS_SetCameraPositionAndTargetAndUpVec( VECTOR Position, VECTOR Target, VECTOR Up ) ;						// �J�����̐ݒ������A���_�A�����_�A�A�b�v�x�N�g���w���
extern	int			NS_SetCameraPositionAndAngle(			VECTOR Position, float VRotate, float HRotate, float TRotate ) ;	// �J�����̐ݒ������A������]�p�x�A������]�p�x�A�P���]�p�x�A���_�w���
extern	int			NS_SetCameraViewMatrix(				MATRIX ViewMatrix ) ;												// �r���[�s��𒼐ڐݒ肷��
extern	int			NS_SetCameraScreenCenter(				float x, float y ) ;												// ��ʏ�ɂ�����J���������Ă���f���̒��S�̍��W��ݒ肷��

extern	int			NS_SetupCamera_Perspective(			float Fov ) ;														// ���ߖ@�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_Ortho(					float Size ) ;														// ���ˉe�J�������Z�b�g�A�b�v����
extern	int			NS_SetupCamera_ProjectionMatrix(		MATRIX ProjectionMatrix ) ;											// �ˉe�s���ݒ肷��
extern	int			NS_SetCameraDotAspect(					float DotAspect ) ;													// �J�����̃h�b�g�A�X�y�N�g���ݒ肷��

extern	int			NS_CheckCameraViewClip(				VECTOR CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )
extern	int			NS_CheckCameraViewClip_Dir(			VECTOR CheckPos ) ;													// �w��̍��W���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��A�߂�l�ŊO��Ă���������m�邱�Ƃ��ł���( �߂�l 0:���E�ɓ����Ă���  0�ȊO:���E�ɓ����Ă��Ȃ�( DX_CAMERACLIP_LEFT �� DX_CAMERACLIP_RIGHT �� or ���Z�ō������ꂽ���́Aand ���Z�ŕ������m�F�ł��� ) )
extern	int			NS_CheckCameraViewClip_Box(			VECTOR BoxPos1, VECTOR BoxPos2 ) ;									// ��̍��W�ŕ\�����{�b�N�X���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )

extern	float		NS_GetCameraNear(						void ) ;															// �J������ Near �N���b�v�ʂ̋������擾����
extern	float		NS_GetCameraFar(						void ) ;															// �J������ Far �N���b�v�ʂ̋������擾����

extern	VECTOR		NS_GetCameraPosition(					void ) ;															// �J�����̈ʒu���擾����
extern	VECTOR		NS_GetCameraTarget(					void ) ;															// �J�����̒����_���擾����
extern	VECTOR		NS_GetCameraUpVector(					void ) ;															// �J�����̎����ɐ����ȏ�����̃x�N�g���𓾂�
extern	float		NS_GetCameraAngleHRotate(				void ) ;															// �J�����̐��������̌������擾����
extern	float		NS_GetCameraAngleVRotate(				void ) ;															// �J�����̐��������̌������擾����
extern	float		NS_GetCameraAngleTRotate(				void ) ;															// �J�����̌����̔P��p�x���擾����

extern	MATRIX		NS_GetCameraViewMatrix(				void ) ;															// �r���[�s����擾����
extern	MATRIX		NS_GetCameraBillboardMatrix(			void ) ;															// �r���{�[�h�s����擾����
extern	float		NS_GetCameraFov(						void ) ;															// �J�����̎���p���擾����
extern	float		NS_GetCameraSize(						void ) ;															// �J�����̎���T�C�Y���擾����
extern	MATRIX		NS_GetCameraProjectionMatrix(			void ) ;															// �ˉe�s����擾����
extern	float		NS_GetCameraDotAspect(					void ) ;															// �J�����̃h�b�g�A�X�y�N�g��𓾂�
extern	MATRIX		NS_GetCameraViewportMatrix(			void ) ;															// �r���[�|�[�g�s����擾����
extern	MATRIX		NS_GetCameraAPIViewportMatrix(			void ) ;															// Direct3D�Ŏ����K�p�����r���[�|�[�g�s����擾����

// ���C�g�֌W�֐�
extern	int			NS_SetUseLighting(				int Flag ) ;																// ���C�e�B���O�v�Z�@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialUseVertDifColor( int UseFlag ) ;																// �R�c�}�`�`��̃��C�e�B���O�v�Z�ɒ��_�J���[�̃f�B�t���[�Y�J���[���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialUseVertSpcColor( int UseFlag ) ;																// �R�c�}�`�`��̃��C�e�B���O�v�Z�ɒ��_�J���[�̃X�y�L�����J���[���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetMaterialParam(			MATERIALPARAM Material ) ;													// �R�c�}�`�`��̃��C�e�B���O�v�Z�Ɏg�p����}�e���A���p�����[�^��ݒ肷��
extern	int			NS_SetUseSpecular(				int UseFlag ) ;																// �R�c�}�`�`��ɃX�y�L�������g�p���邩�ǂ�����ݒ肷��
extern	int			NS_SetGlobalAmbientLight(		COLOR_F Color ) ;															// �O���[�o���A���r�G���g���C�g�J���[��ݒ肷��

extern	int			NS_ChangeLightTypeDir(			VECTOR Direction ) ;														// ���C�g�̃^�C�v���f�B���N�V���i�����C�g�ɂ���
extern	int			NS_ChangeLightTypeSpot(		VECTOR Position, VECTOR Direction, float OutAngle, float InAngle, float Range, float Atten0, float Atten1, float Atten2 ) ;	// ���C�g�̃^�C�v���X�|�b�g���C�g�ɂ���
extern	int			NS_ChangeLightTypePoint(		VECTOR Position, float Range, float Atten0, float Atten1, float Atten2 ) ;	// ���C�g�̃^�C�v���|�C���g���C�g�ɂ���
extern	int			NS_SetLightEnable(				int EnableFlag ) ;															// ���C�g�̗L���A�������Z�b�g����
extern	int			NS_SetLightDifColor(			COLOR_F Color ) ;															// ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
extern	int			NS_SetLightSpcColor(			COLOR_F Color ) ;															// ���C�g�̃X�y�L�����J���[��ݒ肷��
extern	int			NS_SetLightAmbColor(			COLOR_F Color ) ;															// ���C�g�̃A���r�G���g�J���[��ݒ肷��
extern	int			NS_SetLightDirection(			VECTOR Direction ) ;														// ���C�g�̕�����ݒ肷��
extern	int			NS_SetLightPosition(			VECTOR Position ) ;															// ���C�g�̈ʒu��ݒ肷��
extern	int			NS_SetLightRangeAtten(			float Range, float Atten0, float Atten1, float Atten2 ) ;					// ���C�g�̋��������p�����[�^��ݒ肷��( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_SetLightAngle(				float OutAngle, float InAngle ) ;											// ���C�g�̃X�|�b�g���C�g�̃p�����[�^��ݒ肷��( �O���R�[���p�x�A�����R�[���p�x )
extern	int			NS_GetLightType(				void ) ;																	// ���C�g�̃^�C�v���擾����( �߂�l�� DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_GetLightEnable(				void ) ;																	// ���C�g���ʂ̗L���A�������擾����( TRUE:�L��  FALSE:���� )
extern	COLOR_F		NS_GetLightDifColor(			void ) ;																	// ���C�g�̃f�B�t���[�Y�J���[���擾����
extern	COLOR_F		NS_GetLightSpcColor(			void ) ;																	// ���C�g�̃X�y�L�����J���[���擾����
extern	COLOR_F		NS_GetLightAmbColor(			void ) ;																	// ���C�g�̃A���r�G���g�J���[���擾����
extern	VECTOR		NS_GetLightDirection(			void ) ;																	// ���C�g�̕������擾����
extern	VECTOR		NS_GetLightPosition(			void ) ;																	// ���C�g�̈ʒu���擾����
extern	int			NS_GetLightRangeAtten(			float *Range, float *Atten0, float *Atten1, float *Atten2 )	;				// ���C�g�̋��������p�����[�^���擾����( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_GetLightAngle(				float *OutAngle, float *InAngle ) ;											// ���C�g�̃X�|�b�g���C�g�̃p�����[�^���擾����( �O���R�[���p�x�A�����R�[���p�x )

extern	int			NS_CreateDirLightHandle(       VECTOR Direction ) ;														// �f�B���N�V���i�����C�g�n���h�����쐬����
extern	int			NS_CreateSpotLightHandle(      VECTOR Position, VECTOR Direction, float OutAngle, float InAngle, float Range, float Atten0, float Atten1, float Atten2 ) ;	// �X�|�b�g���C�g�n���h�����쐬����
extern	int			NS_CreatePointLightHandle(     VECTOR Position, float Range, float Atten0, float Atten1, float Atten2 ) ;	// �|�C���g���C�g�n���h�����쐬����
extern	int			NS_DeleteLightHandle(          int LHandle ) ;																// ���C�g�n���h�����폜����
extern	int			NS_DeleteLightHandleAll(       void ) ;																	// ���C�g�n���h����S�č폜����
extern	int			NS_SetLightTypeHandle(         int LHandle, int LightType ) ;												// ���C�g�n���h���̃��C�g�̃^�C�v��ύX����( DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_SetLightEnableHandle(       int LHandle, int EnableFlag ) ;												// ���C�g�n���h���̃��C�g���ʂ̗L���A������ݒ肷��( TRUE:�L��  FALSE:���� )
extern	int			NS_SetLightDifColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃f�B�t���[�Y�J���[��ݒ肷��
extern	int			NS_SetLightSpcColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃X�y�L�����J���[��ݒ肷��
extern	int			NS_SetLightAmbColorHandle(     int LHandle, COLOR_F Color ) ;												// ���C�g�n���h���̃��C�g�̃A���r�G���g�J���[��ݒ肷��
extern	int			NS_SetLightDirectionHandle(    int LHandle, VECTOR Direction ) ;											// ���C�g�n���h���̃��C�g�̕�����ݒ肷��
extern	int			NS_SetLightPositionHandle(     int LHandle, VECTOR Position ) ;											// ���C�g�n���h���̃��C�g�̈ʒu��ݒ肷��
extern	int			NS_SetLightRangeAttenHandle(   int LHandle, float Range, float Atten0, float Atten1, float Atten2 ) ;		// ���C�g�n���h���̃��C�g�̋��������p�����[�^��ݒ肷��( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_SetLightAngleHandle(        int LHandle, float OutAngle, float InAngle ) ;								// ���C�g�n���h���̃��C�g�̃X�|�b�g���C�g�̃p�����[�^��ݒ肷��( �O���R�[���p�x�A�����R�[���p�x )
extern	int			NS_GetLightTypeHandle(         int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃^�C�v���擾����( �߂�l�� DX_LIGHTTYPE_DIRECTIONAL �� )
extern	int			NS_GetLightEnableHandle(       int LHandle ) ;																// ���C�g�n���h���̃��C�g���ʂ̗L���A�������擾����( TRUE:�L��  FALSE:���� )
extern	COLOR_F		NS_GetLightDifColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃f�B�t���[�Y�J���[���擾����
extern	COLOR_F		NS_GetLightSpcColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃X�y�L�����J���[���擾����
extern	COLOR_F		NS_GetLightAmbColorHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̃A���r�G���g�J���[���擾����
extern	VECTOR		NS_GetLightDirectionHandle(    int LHandle ) ;																// ���C�g�n���h���̃��C�g�̕������擾����
extern	VECTOR		NS_GetLightPositionHandle(     int LHandle ) ;																// ���C�g�n���h���̃��C�g�̈ʒu���擾����
extern	int			NS_GetLightRangeAttenHandle(   int LHandle, float *Range, float *Atten0, float *Atten1, float *Atten2 ) ;	// ���C�g�n���h���̃��C�g�̋��������p�����[�^���擾����( �L�������A���������W���O�A�P�A�Q )
extern	int			NS_GetLightAngleHandle(        int LHandle, float *OutAngle, float *InAngle ) ;							// ���C�g�n���h���̃��C�g�̃X�|�b�g���C�g�̃p�����[�^���擾����( �O���R�[���p�x�A�����R�[���p�x )

extern	int			NS_GetEnableLightHandleNum(	void ) ;																	// �L���ɂȂ��Ă��郉�C�g�n���h���̐����擾����
extern	int			NS_GetEnableLightHandle(		int Index ) ;																// �L���ɂȂ��Ă��郉�C�g�n���h�����擾����

// �F���擾�p�֐�
extern	int			NS_GetTexFormatIndex(			IMAGEFORMATDESC *Format ) ;																									// �e�N�X�`���t�H�[�}�b�g�̃C���f�b�N�X�𓾂�
extern	int			NS_ColorKaiseki(				void *PixelData, COLORDATA* ColorData ) ;																					// �F�r�b�g�����
#ifdef __WINDOWS__
extern	int			NS_CreatePixelFormat(			D_DDPIXELFORMAT *PixelFormatBuf, int ColorBitDepth, DWORD RedMask, DWORD GreenMask, DWORD BlueMask, DWORD AlphaMask ) ;		// DDPIXELFORMAT�f�[�^���쐬����
#endif // __WINDOWS__












// DxMask.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_MASK

// �}�X�N�֌W 
extern	int			NS_CreateMaskScreen(				void ) ;																						// �}�X�N�X�N���[�����쐬����
extern	int			NS_DeleteMaskScreen(				void ) ;																						// �}�X�N�X�N���[�����폜����
extern	int			NS_DrawMaskToDirectData(			int x, int y, int Width, int Height, void *MaskData , int TransMode ) ;							// �}�X�N�̃f�[�^�𒼐ڃZ�b�g
extern	int			NS_DrawFillMaskToDirectData(		int x1, int y1, int x2, int y2,  int Width, int Height, void *MaskData ) ;						// �}�X�N�̃f�[�^�𒼐ڃ}�X�N��ʑS�̂ɕ`�悷��

extern	int			NS_SetUseMaskScreenFlag(			int ValidFlag ) ;																				// �}�X�N�g�p���[�h��ύX
extern	int			NS_GetUseMaskScreenFlag(			void ) ;																						// �}�X�N�g�p���[�h�̎擾
extern	int			NS_FillMaskScreen(					int Flag ) ;																					// �}�X�N�X�N���[�����w��̐F�œh��Ԃ�

extern	int			NS_InitMask(						void ) ;																						// �}�X�N�f�[�^������������
extern	int			NS_MakeMask(						int Width, int Height ) ;																		// �}�X�N�f�[�^�̒ǉ�
extern	int			NS_GetMaskSize(					int *WidthBuf, int *HeightBuf, int MaskHandle ) ;												// �}�X�N�̑傫���𓾂� 
extern	int			NS_SetDataToMask(					int Width, int Height, void *MaskData, int MaskHandle ) ;										// �}�X�N�̃f�[�^���}�X�N�ɓ]������
extern	int			NS_DeleteMask(						int MaskHandle ) ;																				// �}�X�N�f�[�^���폜
extern	int			NS_BmpBltToMask(					HBITMAP Bmp, int BmpPointX, int BmpPointY, int MaskHandle ) ;									// �}�X�N�f�[�^�ɂa�l�o�f�[�^���}�X�N�f�[�^�ƌ����Ăē]��
extern	int			NS_LoadMask(						const TCHAR *FileName ) ;																		// �}�X�N�f�[�^�����[�h����
extern	int			NS_LoadDivMask(					const TCHAR *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;	// �}�X�N���摜���番���ǂ݂���
extern	int			NS_DrawMask(						int x, int y, int MaskHandle, int TransMode ) ;													// �}�X�N���Z�b�g����
#ifndef DX_NON_FONT
extern	int			NS_DrawFormatStringMask(			int x, int y, int Flag,                 const TCHAR *FormatString, ... ) ;						// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��
extern	int			NS_DrawFormatStringMaskToHandle(	int x, int y, int Flag, int FontHandle, const TCHAR *FormatString, ... ) ;						// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��(�t�H���g�n���h���w���)( SetFontCacheToTextureFlag( FALSE ) ; �ɂ��č쐬�����t�H���g�n���h���̂ݎg�p�\ )
extern	int			NS_DrawStringMask(					int x, int y, int Flag,                 const TCHAR *String ) ;									// ��������}�X�N�X�N���[���ɕ`�悷��
extern	int			NS_DrawStringMaskToHandle(			int x, int y, int Flag, int FontHandle, const TCHAR *String ) ;									// ��������}�X�N�X�N���[���ɕ`�悷��(�t�H���g�n���h���w���)( SetFontCacheToTextureFlag( FALSE ) ; �ɂ��č쐬�����t�H���g�n���h���̂ݎg�p�\ )
#endif // DX_NON_FONT
extern	int			NS_DrawFillMask(					int x1, int y1, int x2, int y2, int MaskHandle ) ;												// �w��̃}�X�N����ʂ����ς��ɓW�J����	
extern	int			NS_SetMaskReverseEffectFlag(		int ReverseFlag ) ;																				// �}�X�N�̐��l�ɑ΂�����ʂ��t�]������

extern	int			NS_GetMaskScreenData(				int x1, int y1, int x2, int y2, int MaskHandle ) ;												// �}�X�N��ʏ�̕`���Ԃ��擾����
extern	int			NS_GetMaskUseFlag(					void ) ;																						// �}�X�N�X�N���[�����g�p�����t���O�̎擾

#endif // DX_NON_MASK













// DxFont.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_FONT

// �t�H���g�A������`��֌W�֐�
extern	int			NS_EnumFontName(                           TCHAR *NameBuffer, int NameBufferNum, int JapanOnlyFlag = TRUE ) ;								// �g�p�\�ȃt�H���g�̖��O�����ׂė񋓂���( NameBuffer �� 64�o�C�g��؂�Ŗ��O���i�[����܂� )
extern	int			NS_EnumFontNameEx(                         TCHAR *NameBuffer, int NameBufferNum, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;			// �g�p�\�ȃt�H���g�̖��O�����ׂė񋓂���( NameBuffer �� 64�o�C�g��؂�Ŗ��O���i�[����܂� )
extern	int			NS_EnumFontNameEx2(						TCHAR *NameBuffer, int NameBufferNum, TCHAR *EnumFontName, int CharSet = -1 /* DX_CHARSET_DEFAULT �� */ ) ;	// �w��̃t�H���g���̃t�H���g��񋓂���
extern	int			NS_InitFontToHandle(                       void ) ;																						// �t�H���g�̃X�e�[�^�X���f�t�H���g�ɖ߂�

extern	int			NS_CreateFontToHandle(                     const TCHAR *FontName, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE , int Handle = -1 ) ;			// �V�����t�H���g�f�[�^���쐬
extern	int			NS_SetFontSpaceToHandle(                   int Point, int FontHandle ) ;																	// ���Ԃ�ύX����
extern	int			NS_SetDefaultFontState(                    const TCHAR *FontName, int Size, int Thick ) ;													// �f�t�H���g�t�H���g�̃X�e�[�^�X���ꊇ�ݒ肷��
extern	int			NS_DeleteFontToHandle(                     int FontHandle ) ;																				// �t�H���g�L���b�V���̐�����I������
extern	int			NS_SetFontLostFlag(                        int FontHandle, int *LostFlag ) ;																// ������� TRUE �ɂ���t���O�ւ̃|�C���^��ݒ肷��

extern	int			NS_SetFontSize(                            int FontSize ) ;																				// �`�悷��t�H���g�̃T�C�Y���Z�b�g����
extern	int			NS_SetFontThickness(                       int ThickPal ) ;																				// �t�H���g�̑������Z�b�g
extern	int			NS_SetFontSpace(                           int Point ) ;																					// ���Ԃ�ύX����

extern	int			NS_SetFontCacheToTextureFlag(              int Flag ) ;																					// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����
extern	int			NS_SetFontChacheToTextureFlag(             int Flag ) ;																					// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����(�뎚��)
extern	int			NS_SetFontCacheCharNum(                    int CharNum ) ;																					// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������w�肷��
extern	int			NS_ChangeFont(                             const TCHAR *FontName, int CharSet = -1 /* DX_CHARSET_SHFTJIS �� */ ) ;							// �t�H���g��ύX
extern	int			NS_ChangeFontType(                         int FontType ) ;																				// �t�H���g�^�C�v�̕ύX
// FontCacheStringDraw �� DrawString ���g���Ă�������
extern	int			NS_FontCacheStringDrawToHandle(            int x, int y, const TCHAR *StrData, int Color, int EdgeColor, BASEIMAGE *DestImage, RECT *ClipRect /* NULL �� */ , int FontHandle, int VerticalFlag = FALSE , SIZE *DrawSizeP = NULL ) ;
extern	int			NS_FontBaseImageBlt(                       int x, int y, const TCHAR *StrData, BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage,                 int VerticalFlag = FALSE ) ;															// ��{�C���[�W�ɕ�����C���[�W��]������
extern	int			NS_FontBaseImageBltToHandle(               int x, int y, const TCHAR *StrData, BASEIMAGE *DestImage, BASEIMAGE *DestEdgeImage, int FontHandle, int VerticalFlag = FALSE ) ;															// ��{�C���[�W�ɕ�����C���[�W��]������

extern	int			NS_GetFontMaxWidth(                        void ) ;																						// �����̍ő啝�𓾂�
extern	int			NS_GetFontMaxWidthToHandle(                int FontHandle ) ;																				// �����̍ő啝�𓾂�
extern	int			NS_GetFontCharInfo(                        int FontHandle, const TCHAR *Char, int *DrawX, int *DrawY, int *NextCharX, int *SizeX, int *SizeY ) ;		// �w��̕����̕`������擾����
extern	int			NS_GetDrawStringWidth(                     const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;									// ������̕��𓾂�
extern	int			NS_GetDrawFormatStringWidth(               const TCHAR *FormatString, ... ) ;																// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawStringWidthToHandle(             const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;					// ������̕��𓾂�
extern	int			NS_GetDrawFormatStringWidthToHandle(       int FontHandle, const TCHAR *FormatString, ... ) ;												// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawExtendStringWidth(               double ExRateX, const TCHAR *String, int StrLen, int VerticalFlag = FALSE ) ;					// ������̕��𓾂�
extern	int			NS_GetDrawExtendFormatStringWidth(         double ExRateX, const TCHAR *FormatString, ... ) ;												// �����t��������̕`�敝�𓾂�
extern	int			NS_GetDrawExtendStringWidthToHandle(       double ExRateX, const TCHAR *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;	// ������̕��𓾂�
extern	int			NS_GetDrawExtendFormatStringWidthToHandle( double ExRateX, int FontHandle, const TCHAR *FormatString, ... ) ;								// �����t��������̕`�敝�𓾂�

extern	int			NS_GetFontStateToHandle(                   TCHAR *FontName, int *Size, int *Thick, int FontHandle) ;										// �t�H���g�̏��𓾂�
extern	int			NS_GetDefaultFontHandle(                   void ) ;																						// �f�t�H���g�̃t�H���g�̃n���h���𓾂�
extern	int			NS_GetFontChacheToTextureFlag(             void ) ;																						// �t�H���g�Ƀe�N�X�`���L���b�V�����g�p���邩�ǂ������擾����(�뎚��)
extern	int			NS_SetFontCacheTextureColorBitDepth(		int ColorBitDepth ) ;																			// �t�H���g�̃L���b�V���Ƃ��Ďg�p����e�N�X�`���̃J���[�r�b�g�[�x��ݒ肷��( 16 ���� 32 �̂ݎw��\  �f�t�H���g�� 32 )
extern	int			NS_GetFontCacheTextureColorBitDepth(		void ) ;																						// �t�H���g�̃L���b�V���Ƃ��Ďg�p����e�N�X�`���̃J���[�r�b�g�[�x���擾����
extern	int			NS_GetFontCacheToTextureFlag(              void ) ;																						// �t�H���g�Ƀe�N�X�`���L���b�V�����g�p���邩�ǂ������擾����
extern	int			NS_CheckFontChacheToTextureFlag(           int FontHandle ) ;																				// �w��̃t�H���g���e�N�X�`���L���b�V�����g�p���Ă��邩�ǂ����𓾂�(�뎚��)
extern	int			NS_CheckFontCacheToTextureFlag(            int FontHandle ) ;																				// �w��̃t�H���g���e�N�X�`���L���b�V�����g�p���Ă��邩�ǂ����𓾂�
extern	int			NS_CheckFontHandleValid(                   int FontHandle ) ;																				// �w��̃t�H���g�n���h�����L�����ۂ����ׂ�
extern	int			NS_MultiByteCharCheck(                     const char *Buf, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;										// �Q�o�C�g���������ׂ�( TRUE:�Q�o�C�g����  FALSE:�P�o�C�g���� )
extern	int			NS_GetFontCacheCharNum(                    void ) ;																						// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������擾����( �߂�l  0:�f�t�H���g  1�ȏ�:�w�蕶���� )
extern	int			NS_GetFontSize(                            void ) ;																						// �t�H���g�̃T�C�Y�𓾂�
extern	int			NS_GetFontSizeToHandle(                    int FontHandle ) ;																				// �t�H���g�̃T�C�Y�𓾂�

// ������`��֐�
extern	int			NS_DrawString(                      int x, int y, const TCHAR *String, int Color,                 int EdgeColor = 0 ) ;																// ������̕`��
extern	int			NS_DrawVString(                     int x, int y, const TCHAR *String, int Color,                 int EdgeColor = 0 ) ;																// ������̕`��
extern	int			NS_DrawStringToHandle(              int x, int y, const TCHAR *String, int Color, int FontHandle, int EdgeColor = 0 , int VerticalFlag = FALSE ) ;										// �������`�悷��
extern	int			NS_DrawVStringToHandle(             int x, int y, const TCHAR *String, int Color, int FontHandle, int EdgeColor = 0 ) ;																// �������`�悷��
extern	int			NS_DrawFormatString(                int x, int y, int Color,                 const TCHAR *FormatString, ... ) ;																		// �����w�蕶�����`�悷��
extern	int			NS_DrawFormatVString(               int x, int y, int Color,                 const TCHAR *FormatString, ... ) ;																		// �����w�蕶�����`�悷��
extern	int			NS_DrawFormatStringToHandle(        int x, int y, int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																		// �����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToHandle(       int x, int y, int Color, int FontHandle, const TCHAR *FormatString, ... ) ;																		// �����w�蕶�����`�悷��
extern	int			NS_DrawExtendString(                int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int Color,                 int EdgeColor = 0 ) ;								// ������̊g��`��
extern	int			NS_DrawExtendVString(               int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int Color,                 int EdgeColor = 0 ) ;								// ������̊g��`��
extern	int			NS_DrawExtendStringToHandle(        int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int Color, int FontHandle, int EdgeColor = 0 , int VerticalFlag = FALSE ) ;		// ��������g��`�悷��
extern	int			NS_DrawExtendVStringToHandle(       int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int Color, int FontHandle, int EdgeColor = 0 ) ;								// ��������g��`�悷��
extern	int			NS_DrawExtendFormatString(          int x, int y, double ExRateX, double ExRateY, int Color,                 const TCHAR *FormatString, ... ) ;										// �����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVString(         int x, int y, double ExRateX, double ExRateY, int Color,                 const TCHAR *FormatString, ... ) ;										// �����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatStringToHandle(  int x, int y, double ExRateX, double ExRateY, int Color, int FontHandle, const TCHAR *FormatString, ... ) ;										// �����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToHandle( int x, int y, double ExRateX, double ExRateY, int Color, int FontHandle, const TCHAR *FormatString, ... ) ;										// �����w�蕶������g��`�悷��

extern	int			NS_DrawNumberToI(                   int x, int y,                          int    Num, int RisesNum, int Color, int EdgeColor = 0 ) ;													// �����^�̐��l��`�悷��
extern	int			NS_DrawNumberToF(                   int x, int y,                          double Num, int Length,   int Color, int EdgeColor = 0 ) ;													// ���������_�^�̐��l��`�悷��
extern	int			NS_DrawNumberPlusToI(               int x, int y, const TCHAR *NoteString, int    Num, int RisesNum, int Color, int EdgeColor = 0 ) ;													// �����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern 	int			NS_DrawNumberPlusToF(               int x, int y, const TCHAR *NoteString, double Num, int Length,   int Color, int EdgeColor = 0 ) ;													// ���������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

extern	int			NS_DrawNumberToIToHandle(           int x, int y,                          int    Num, int RisesNum, int Color, int FontHandle, int EdgeColor = 0 ) ;									// �����^�̐��l��`�悷��
extern	int			NS_DrawNumberToFToHandle(           int x, int y,                          double Num, int Length,   int Color, int FontHandle, int EdgeColor = 0 ) ;									// ���������_�^�̐��l��`�悷��
extern	int			NS_DrawNumberPlusToIToHandle(       int x, int y, const TCHAR *NoteString, int    Num, int RisesNum, int Color, int FontHandle, int EdgeColor = 0 ) ;									// �����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern	int			NS_DrawNumberPlusToFToHandle(       int x, int y, const TCHAR *NoteString, double Num, int Length,   int Color, int FontHandle, int EdgeColor = 0 ) ;									// ���������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

extern	int			NS_DrawStringToZBuffer(                      int x, int y, const TCHAR *String,                                                 int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ�����̕`��
extern	int			NS_DrawVStringToZBuffer(                     int x, int y, const TCHAR *String,                                                 int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ�����̕`��
extern	int			NS_DrawStringToHandleToZBuffer(              int x, int y, const TCHAR *String, int FontHandle,                                 int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;			// �y�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawVStringToHandleToZBuffer(             int x, int y, const TCHAR *String, int FontHandle,                                 int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ������`�悷��
extern	int			NS_DrawFormatStringToZBuffer(                int x, int y,                                                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToZBuffer(               int x, int y,                                                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatStringToHandleToZBuffer(        int x, int y, int FontHandle,                                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawFormatVStringToHandleToZBuffer(       int x, int y, int FontHandle,                                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶�����`�悷��
extern	int			NS_DrawExtendStringToZBuffer(                int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                 int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ�����̊g��`��
extern	int			NS_DrawExtendVStringToZBuffer(               int x, int y, double ExRateX, double ExRateY, const TCHAR *String,                 int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ�����̊g��`��
extern	int			NS_DrawExtendStringToHandleToZBuffer(        int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int VerticalFlag = FALSE ) ;			// �y�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendVStringToHandleToZBuffer(       int x, int y, double ExRateX, double ExRateY, const TCHAR *String, int FontHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĕ�������g��`�悷��
extern	int			NS_DrawExtendFormatStringToZBuffer(          int x, int y, double ExRateX, double ExRateY,                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToZBuffer(         int x, int y, double ExRateX, double ExRateY,                                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatStringToHandleToZBuffer(  int x, int y, double ExRateX, double ExRateY, int FontHandle,                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��
extern	int			NS_DrawExtendFormatVStringToHandleToZBuffer( int x, int y, double ExRateX, double ExRateY, int FontHandle,                      int WriteZMode /* DX_ZWRITE_MASK �� */, const TCHAR *FormatString, ... ) ;		// �y�o�b�t�@�ɑ΂��ď����w�蕶������g��`�悷��

#endif // DX_NON_FONT













// DxMath.cpp �֐��v���g�^�C�v�錾

// ���Z���C�u����
















// DxBaseImage.cpp �֐��v���g�^�C�v�錾

// ��{�C���[�W�f�[�^�̃��[�h�{�c�h�a�֌W
extern	int			NS_CreateGraphImageOrDIBGraph(    const TCHAR *FileName, void *DataImage, int DataImageSize, int DataImageType /* LOADIMAGE_TYPE_FILE �� */ , int BmpFlag, int ReverseFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ;				// �o�^����Ă���e��O���t�B�b�N���[�_�֐�����A�a�l�o�f�[�^�������� GraphImage�f�[�^���\�z����
extern	int			NS_CreateGraphImageType2(         STREAMDATA *Src, BASEIMAGE *Dest ) ;																																													// �ėp�ǂݍ��ݏ����ɂ��O���t�B�b�N�C���[�W�\�z�֐�( 0:����  -1:���s )
extern	int			NS_CreateBmpInfo(                 BITMAPINFO *BmpInfo, int Width, int Height, int Pitch, void *SrcGrData, void **DestGrData ) ;																														// �t���J���[�`����BITMAPINFO�\���̂��쐬����
extern	DWORD		NS_GetGraphImageFullColorCode(    BASEIMAGE *GraphImage, int x, int y ) ;																																												// BASEIMAGE �\���̂̉摜��񂩂�w��̍��W�̃t���J���[�R�[�h���擾����
extern	int			NS_CreateGraphImage_plus_Alpha(   const TCHAR *FileName, void *RgbImage, int RgbImageSize, int RgbImageType, void *AlphaImage, int AlphaImageSize, int AlphaImageType, BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag ) ;		// �e��O���t�B�b�N�f�[�^����O���t�B�b�N�C���[�W�f�[�^�ƃA���t�@�}�b�v�p�C���[�W�f�[�^���\�z����
extern	int			NS_ReverseGraphImage(             BASEIMAGE *GraphImage ) ;																																															// �w��� GraphImage �����E���]����
#ifdef __WINDOWS__
extern	HBITMAP		NS_CreateDIBGraph(                const TCHAR *FileName,                                                                                                                            int ReverseFlag,          COLORDATA *SrcColor) ;					// �c�h�a�O���t�B�b�N���쐬����
extern	HBITMAP		NS_CreateDIBGraphToMem(           BITMAPINFO *BmpInfo, void *GraphData,                                                                                                             int ReverseFlag,          COLORDATA *SrcColor ) ;					// �c�h�a�O���t�B�b�N���������C���[�W����쐬����
extern	int			NS_CreateDIBGraph_plus_Alpha(     const TCHAR *FileName, HBITMAP *RGBBmp, HBITMAP *AlphaBmp,                                                                                        int ReverseFlag = FALSE , COLORDATA *SrcColor = NULL ) ;			// �t�@�C������c�h�a�O���t�B�b�N�ƃ}�X�N�O���t�B�b�N���쐬����
extern	HBITMAP		NS_CreateDIBGraphVer2(            const TCHAR *FileName, void *MemImage, int MemImageSize,                                       int ImageType,                                     int ReverseFlag,          COLORDATA *SrcColor ) ;					// �c�h�a�O���t�B�b�N���쐬����(�o�[�W�����Q)
extern	int			NS_CreateDIBGraphVer2_plus_Alpha( const TCHAR *FileName, void *MemImage, int MemImageSize, void *AlphaImage, int AlphaImageSize, int ImageType, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag,          COLORDATA *SrcColor ) ;					// �c�h�a�O���t�B�b�N���쐬����
extern	int			NS_ConvBitmapToGraphImage(        BITMAPINFO *BmpInfo, void *GraphData, BASEIMAGE *GraphImage, int CopyFlag ) ;																																		// �a�l�o �� GraphImage �ɕϊ�����( Ret 0:����I��  1:�R�s�[���s����  -1:�G���[ )
extern	int			NS_ConvGraphImageToBitmap(        BASEIMAGE *GraphImage, BITMAPINFO *BmpInfo, void **GraphData, int CopyFlag, int FullColorConv = TRUE ) ;																												// GraphImage �� �a�l�o �ɕϊ�����(�A���t�@�f�[�^�͂����Ă����������)( Ret 0:����I��  1:�R�s�[���s����  -1:�G���[ )
#endif // __WINDOWS__

//extern int		NS_AddUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;																					// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^����
//extern int		NS_AddUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;												// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^����
//extern int		NS_AddUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver3��o�^����
extern	int			NS_AddUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *Image ) ) ; 																								// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver4��o�^����
//extern int		NS_SubUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;																					// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^���疕������
//extern int		NS_SubUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;												// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^���疕������
//extern int		NS_SubUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver3��o�^���疕������
extern	int			NS_SubUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *Image ) ) ; 																								// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver4��o�^���疕������

extern	int			NS_SetUseFastLoadFlag(            int Flag ) ;														// �����ǂݍ��݃��[�`�����g�����ۂ��̃t���O���Z�b�g����
extern	int			NS_GetGraphDataShavedMode(        void ) ;															// �O���t�B�b�N���F���̉摜�򉻊ɘa�������[�h�̎擾
extern	int			NS_SetGraphDataShavedMode(        int ShavedMode ) ;												// �O���t�B�b�N���F���̉摜�򉻊ɘa�������[�h�̕ύX

//��{�C���[�W�f�[�^�\���̊֌W
extern	int			NS_CreateBaseImage(               const TCHAR *FileName, void *FileImage, int FileImageSize, int DataType /*=LOADIMAGE_TYPE_FILE*/ , BASEIMAGE *BaseImage,  int ReverseFlag ) ;			// �e��O���t�B�b�N�f�[�^�����{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateGraphImage(              const TCHAR *FileName, void *DataImage, int DataImageSize, int DataImageType,                      BASEIMAGE *GraphImage, int ReverseFlag ) ;			// CreateBaseImage �̋�����
extern	int			NS_CreateBaseImageToFile(         const TCHAR *FileName,                                                                             BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;	// �摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateBaseImageToMem(                                 void *FileImage, int FileImageSize,                                         BASEIMAGE *BaseImage,  int ReverseFlag = FALSE ) ;	// ��������ɓW�J���ꂽ�摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int			NS_CreateARGB8ColorBaseImage(     int SizeX, int SizeY,                       BASEIMAGE *BaseImage ) ;																						// �`�q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateXRGB8ColorBaseImage(     int SizeX, int SizeY,                       BASEIMAGE *BaseImage ) ;																						// �w�q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateRGB8ColorBaseImage(      int SizeX, int SizeY,                       BASEIMAGE *BaseImage ) ;																						// �q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateARGB4ColorBaseImage(     int SizeX, int SizeY,                       BASEIMAGE *BaseImage ) ;																						// �`�q�f�a�S�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreatePAL8ColorBaseImage(      int SizeX, int SizeY,                       BASEIMAGE *BaseImage ) ;																						// �p���b�g�W�r�b�g�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_CreateColorDataBaseImage(      int SizeX, int SizeY, COLORDATA *ColorData, BASEIMAGE *BaseImage ) ;																						// �w��̃J���[�t�H�[�}�b�g�̊k�̊�{�C���[�W�f�[�^���쐬����
extern	int			NS_GetBaseImageGraphDataSize(     BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�̃C���[�W�T�C�Y���擾����( byte�P�� )

extern	int			NS_ReleaseBaseImage(              BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�̌�n�����s��
extern	int			NS_ReleaseGraphImage(             BASEIMAGE *GraphImage ) ;																																// ReleaseBaseImage �̋�����

extern	int			NS_ConvertNormalFormatBaseImage(  BASEIMAGE *BaseImage ) ;																																	// DX_BASEIMAGE_FORMAT_NORMAL �ȊO�̌`���̃C���[�W�f�[�^�� DX_BASEIMAGE_FORMAT_NORMAL �`���̃C���[�W�ɕϊ�����

extern	int			NS_GetDrawScreenBaseImage(        int x1, int y1, int x2, int y2, BASEIMAGE *BaseImage ) ;																									// �`��Ώۂ̉�ʂ���w��̈�̃O���t�B�b�N����{�C���[�W�f�[�^�ɓ]������
#ifdef __WINDOWS__
extern	int			NS_UpdateLayerdWindowForBaseImage(                   BASEIMAGE *BaseImage ) ;																												// ��{�C���[�W���g�p���� UpdateLayerdWindow ���s��
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaBaseImage( BASEIMAGE *BaseImage ) ;																												// ��Z�ς݃A���t�@�̊�{�C���[�W���g�p���� UpdateLayerdWindow ���s��
#endif // __WINDOWS__
extern	int			NS_FillBaseImage(                 BASEIMAGE *BaseImage, int r, int g, int b, int a ) ;																										// ��{�C���[�W�f�[�^���w��̐F�œh��Ԃ�
extern	int			NS_ClearRectBaseImage(            BASEIMAGE *BaseImage, int x, int y, int w, int h ) ;																										// ��{�C���[�W�f�[�^�̎w��̗̈���O�N���A����
extern	int			NS_GetPaletteBaseImage(           BASEIMAGE *BaseImage, int PaletteNo, int *r, int *g, int *b, int *a ) ;																					// ��{�C���[�W�f�[�^�̃p���b�g���擾����
extern	int			NS_SetPaletteBaseImage(           BASEIMAGE *BaseImage, int PaletteNo, int  r, int  g, int  b, int  a ) ;																					// ��{�C���[�W�f�[�^�̃p���b�g���Z�b�g����
extern	int			NS_SetPixelPalCodeBaseImage(      BASEIMAGE *BaseImage, int x, int y, int palNo ) ;																										// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h��ύX����(�p���b�g�摜�p)
extern	int			NS_GetPixelPalCodeBaseImage(      BASEIMAGE *BaseImage, int x, int y ) ;																													// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h���擾����(�p���b�g�摜�p)
extern	int			NS_SetPixelBaseImage(             BASEIMAGE *BaseImage, int x, int y, int  r, int  g, int  b, int  a ) ;																					// ��{�C���[�W�f�[�^�̎w��̍��W�̐F��ύX����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_GetPixelBaseImage(             BASEIMAGE *BaseImage, int x, int y, int *r, int *g, int *b, int *a ) ;																					// ��{�C���[�W�f�[�^�̎w��̍��W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawLineBaseImage(             BASEIMAGE *BaseImage, int x1, int y1, int x2, int y2, int r, int g, int b, int a ) ;																		// ��{�C���[�W�f�[�^�̎w��̍��W�ɐ���`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_BltBaseImage(                  int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;								// ��{�C���[�W�f�[�^��]������
extern	int			NS_BltBaseImage(                                                                  int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;								// ��{�C���[�W�f�[�^��]������
extern	int			NS_BltBaseImageWithTransColor(    int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage, int Tr, int Tg, int Tb, int Ta ) ;	// ��{�C���[�W�f�[�^�𓧉ߐF�����t���œ]������
extern	int			NS_BltBaseImageWithAlphaBlend(    int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage, int Opacity = 255 ) ;			// ��{�C���[�W�f�[�^���A���t�@�l�̃u�����h���l��������œ]������( Opacity �͓����x : 0( ���S���� ) �` 255( ���S�s���� ) )( �o�͐悪 ARGB8 �`���ȊO�̏ꍇ�̓G���[�ɂȂ�܂� )
extern	int			NS_ReverseBaseImageH(             BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�̍��E�𔽓]����
extern	int			NS_ReverseBaseImageV(             BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�̏㉺�𔽓]����
extern	int			NS_ReverseBaseImage(              BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�̏㉺���E�𔽓]����
extern	int			NS_CheckPixelAlphaBaseImage(      BASEIMAGE *BaseImage ) ;																																	// ��{�C���[�W�f�[�^�Ɋ܂܂��s�N�Z���̃A���t�@�l���`�F�b�N����( �߂�l   -1:�G���[  0:�摜�ɃA���t�@����������  1:�摜�ɃA���t�@����������A���ׂčő�(255)�l  2:�摜�ɃA���t�@����������A���݂���A���t�@�l�͍ŏ�(0)�ƍő�(255)�������͍ŏ�(0)�̂݁@3:�摜�ɃA���t�@����������A�ŏ��ƍő�ȊO�̒��Ԃ̒l������ )  

#ifndef DX_NON_SAVEFUNCTION

extern	int			NS_SaveBaseImageToBmp(            const TCHAR *FilePath, BASEIMAGE *BaseImage ) ;																											// ��{�摜�f�[�^���a�l�o�摜�Ƃ��ĕۑ�����
#ifndef DX_NON_PNGREAD
extern	int			NS_SaveBaseImageToPng(            const TCHAR *FilePath, BASEIMAGE *BaseImage, int CompressionLevel ) ;																					// ��{�摜�f�[�^���o�m�f�摜�Ƃ��ĕۑ�����
#endif
#ifndef DX_NON_JPEGREAD
extern	int			NS_SaveBaseImageToJpeg(           const TCHAR *FilePath, BASEIMAGE *BaseImage, int Quality, int Sample2x1 ) ;																				// ��{�摜�f�[�^���i�o�d�f�摜�Ƃ��ĕۑ�����
#endif

#endif // DX_NON_SAVEFUNCTION

// ��{�C���[�W�`��
extern	int			NS_DrawBaseImage(					int x, int y, BASEIMAGE *BaseImage ) ;																													// ��{�C���[�W�f�[�^��`�悷��

// �J���[�}�b�`���O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s�� Ver2
extern	int			NS_GraphColorMatchBltVer2( void *DestGraphData, int DestPitch,  COLORDATA *DestColorData,
											void *SrcGraphData,  int SrcPitch,   COLORDATA *SrcColorData,
											void *AlphaMask,     int AlphaPitch, COLORDATA *AlphaColorData,
											POINT DestPoint, RECT *SrcRect, int ReverseFlag,
											int TransColorAlphaTestFlag, unsigned int TransColor,
											int ImageShavedMode, int AlphaOnlyFlag = FALSE ,
											int RedIsAlphaFlag = FALSE , int TransColorNoMoveFlag = FALSE ,
											int Pal8ColorMatch = FALSE ) ;






// �F���擾�֌W
extern	COLOR_F		NS_GetColorF(              float Red, float Green, float Blue, float Alpha ) ;										// ���������_�^�̃J���[�l���쐬����
extern	COLOR_U8	NS_GetColorU8(             int Red, int Green, int Blue, int Alpha ) ;												// �����Ȃ������W�r�b�g�̃J���[�l���쐬����
extern	DWORD		NS_GetColor(               int Red, int Green, int Blue ) ;														// �R���F�l���猻�݂̉�ʃ��[�h�ɑΉ������F�f�[�^�l�𓾂�
extern	int			NS_GetColor2(              int Color, int *Red, int *Green, int *Blue ) ;											// ��ʃ��[�h�ɑΉ������F�f�[�^�l����X�̂R���F�f�[�^�𔲂��o��
extern	int			NS_GetColor3(              COLORDATA *ColorData, int Red, int Green, int Blue, int Alpha = 255 ) ;					// �R���F�l����w��̃s�N�Z���t�H�[�}�b�g�ɑΉ������F�f�[�^�l�𓾂�
extern	int			NS_GetColor4(              COLORDATA *DestColorData, COLORDATA* SrcColorData, int SrcColor ) ;						// �Q�̃J���[�t�H�[�}�b�g�Ԃ̃f�[�^�ϊ����s�������𓾂� 
extern	int			NS_GetColor5(              COLORDATA *ColorData, int Color, int *Red, int *Green, int *Blue, int *Alpha = NULL ) ;	// �w��J���[�t�H�[�}�b�g�ɑΉ������F�f�[�^�l����X�̂R���F�f�[�^�𔲂��o��
extern	int			NS_CreatePaletteColorData( COLORDATA *ColorDataBuf ) ;																// �p���b�g�J���[�̃J���[�����\�z����
extern	int			NS_CreateXRGB8ColorData(   COLORDATA *ColorDataBuf ) ;																// �w�q�f�a�W�J���[�̃J���[�����\�z����
extern	int			NS_CreateARGB8ColorData(   COLORDATA *ColorDataBuf ) ;																// �`�q�f�a�W�J���[�̃J���[�����\�z����
extern	int			NS_CreateARGB4ColorData(   COLORDATA *ColorDataBuf ) ;																// �`�q�f�a�S�J���[�̃J���[�����\�z����
extern	int			NS_CreateFullColorData(    COLORDATA *ColorDataBuf ) ;																// �t���J���[�c�h�a�̃J���[�����\�z����
extern	int			NS_CreateGrayColorData(    COLORDATA *ColorDataBuf ) ;																// �O���[�X�P�[���̃J���[�����\�z����
extern	int			NS_CreatePal8ColorData(    COLORDATA *ColorDataBuf ) ;																// �p���b�g�Q�T�U�F�̃J���[�����\�z����
extern	int			NS_CreateColorData(        COLORDATA *ColorDataBuf, int ColorBitDepth,
									        DWORD RedMask, DWORD GreenMask, DWORD BlueMask, DWORD AlphaMask,
									        int ChannelNum = 0, int ChannelBitDepth = 0, int FloatTypeFlag = FALSE ) ;				// �J���[�f�[�^���쐬����
extern	void		NS_SetColorDataNoneMask(   COLORDATA *ColorData ) ;																// NoneMask �ȊO�̗v�f�𖄂߂� COLORDATA �\���̂̏������� NoneMask ���Z�b�g����
extern	int			NS_CmpColorData(           COLORDATA *ColorData1, COLORDATA *ColorData2 ) ;										// ��̃J���[�f�[�^�����������ǂ������ׂ�( TRUE:������  FALSE:�������Ȃ� )

#endif // DX_NOTUSE_DRAWFUNCTION














// DxSoftImage.cpp�֐��v���g�^�C�v�錾
#ifndef DX_NON_SOFTIMAGE
extern	int			NS_InitSoftImage(                   void ) ;																			// �\�t�g�E�G�A�ň����C���[�W��S�ĉ������
extern	int			NS_LoadSoftImage(                   const TCHAR *FileName ) ;															// �\�t�g�E�G�A�ň����C���[�W�̓ǂݍ���( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_LoadSoftImageToMem(              void *FileImage, int FileImageSize ) ;												// �\�t�g�E�G�A�ň����C���[�W�̃���������̓ǂݍ���( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_MakeSoftImage(                   int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int			NS_MakeARGB8ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGBA8 �J���[ )
extern	int			NS_MakeXRGB8ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( XRGB8 �J���[ )
extern	int			NS_MakeARGB4ColorSoftImage(         int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( ARGB4 �J���[ )
extern	int			NS_MakeRGB8ColorSoftImage(          int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGB8 �J���[ )
extern	int			NS_MakePAL8ColorSoftImage(          int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( �p���b�g�Q�T�U�F �J���[ )

extern	int			NS_DeleteSoftImage(                 int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̉��

extern	int			NS_GetSoftImageSize(                int SIHandle, int *Width, int *Height ) ;											// �\�t�g�E�G�A�ň����C���[�W�̃T�C�Y���擾����
extern	int			NS_CheckPaletteSoftImage(           int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W���p���b�g�摜���ǂ������擾����( TRUE:�p���b�g�摜  FALSE:�p���b�g�摜����Ȃ� )
extern	int			NS_CheckAlphaSoftImage(             int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̃t�H�[�}�b�g�Ƀ��v�f�����邩�ǂ������擾����( TRUE:����  FALSE:�Ȃ� )
extern	int			NS_CheckPixelAlphaSoftImage(        int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�Ɋ܂܂��s�N�Z���̃A���t�@�l���`�F�b�N����( �߂�l   -1:�G���[  0:�摜�ɃA���t�@����������  1:�摜�ɃA���t�@����������A���ׂčő�(255)�l  2:�摜�ɃA���t�@����������A���݂���A���t�@�l�͍ŏ�(0)�ƍő�(255)�������͍ŏ�(0)�̂݁@3:�摜�ɃA���t�@����������A�ŏ��ƍő�ȊO�̒��Ԃ̒l������ )  

extern	int			NS_GetDrawScreenSoftImage(          int x1, int y1, int x2, int y2, int SIHandle ) ;									// �`��Ώۂ̉�ʂ���w��̈�̃O���t�B�b�N���\�t�g�E�G�A�ň����C���[�W�ɓ]������
#ifdef __WINDOWS__
extern	int			NS_UpdateLayerdWindowForSoftImage(                   int SIHandle ) ;													// �\�t�g�E�G�A�ň����C���[�W���g�p���� UpdateLayerdWindow ���s��( �C���[�W�̓E�C���h�E�̃N���C�A���g�̈�Ɠ����T�C�Y�ł���K�v������܂� )
extern	int			NS_UpdateLayerdWindowForPremultipliedAlphaSoftImage( int SIHandle ) ;													// ��Z�ς݃A���t�@�̃\�t�g�E�G�A�ň����C���[�W���g�p���� UpdateLayerdWindow ���s��( �C���[�W�̓E�C���h�E�̃N���C�A���g�̈�Ɠ����T�C�Y�ł���K�v������܂� )
#endif // __WINDOWS__
extern	int			NS_FillSoftImage(                   int SIHandle, int r, int g, int b, int a ) ;										// �\�t�g�E�G�A�ň����C���[�W���w��F�œh��Ԃ�(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_ClearRectSoftImage(              int SIHandle, int x, int y, int w, int h ) ;										// �\�t�g�E�G�A�ň����C���[�W�̎w��̗̈���O�N���A����
extern	int			NS_GetPaletteSoftImage(             int SIHandle, int PaletteNo, int *r, int *g, int *b, int *a ) ;					// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_SetPaletteSoftImage(             int SIHandle, int PaletteNo, int  r, int  g, int  b, int  a ) ;					// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���Z�b�g����(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_DrawPixelPalCodeSoftImage(       int SIHandle, int x, int y, int palNo ) ;											// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�p���b�g�摜�p�A�L���l�͂O�`�Q�T�T)
extern	int			NS_GetPixelPalCodeSoftImage(        int SIHandle, int x, int y ) ;														// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F�R�[�h���擾����(�p���b�g�摜�p�A�߂�l�͂O�`�Q�T�T)
extern	void		*NS_GetImageAddressSoftImage(       int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̎��C���[�W���i�[����Ă��郁�����̈�̐擪�A�h���X���擾����
extern	int			NS_DrawPixelSoftImage(              int SIHandle, int x, int y, int  r, int  g, int  b, int  a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	void		NS_DrawPixelSoftImage_Unsafe_XRGB8( int SIHandle, int x, int y, int  r, int  g, int  b ) ;								// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� ARGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	void		NS_DrawPixelSoftImage_Unsafe_ARGB8( int SIHandle, int x, int y, int  r, int  g, int  b, int  a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� XRGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	int			NS_GetPixelSoftImage(               int SIHandle, int x, int y, int *r, int *g, int *b, int *a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	void		NS_GetPixelSoftImage_Unsafe_XRGB8(  int SIHandle, int x, int y, int *r, int *g, int *b ) ;								// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� XRGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	void		NS_GetPixelSoftImage_Unsafe_ARGB8(  int SIHandle, int x, int y, int *r, int *g, int *b, int *a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)�A�G���[�`�F�b�N�����Ȃ�����ɍ����ł����A�͈͊O�̍��W�� ARGB8 �ȊO�̃t�H�[�}�b�g�̃\�t�g�n���h����n���ƕs���ȃ������A�N�Z�X�ŋ����I�����܂�
extern	int			NS_DrawLineSoftImage(               int SIHandle, int x1, int y1, int x2, int y2, int r, int g, int b, int a ) ;		// �\�t�g�E�G�A�ň����C���[�W�̎w����W�ɐ���`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int			NS_BltSoftImage(                    int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle ) ;									// �\�t�g�E�G�A�ň����C���[�W��ʂ̃C���[�W��ɓ]������
extern	int			NS_BltSoftImageWithTransColor(      int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle, int Tr, int Tg, int Tb, int Ta ) ;	// �\�t�g�E�G�A�ň����C���[�W�𓧉ߐF�����t���œ]������
extern	int			NS_BltSoftImageWithAlphaBlend(      int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle, int Opacity = 255 ) ;					// �\�t�g�E�G�A�ň����C���[�W���A���t�@�l�̃u�����h���l��������œ]������( Opacity �͓����x : 0( ���S���� ) �` 255( ���S�s���� ) )( �o�͐悪 ARGB8 �`���ȊO�̏ꍇ�̓G���[�ɂȂ�܂� )
extern	int			NS_ReverseSoftImageH(               int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̍��E�𔽓]����
extern	int			NS_ReverseSoftImageV(               int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̏㉺�𔽓]����
extern	int			NS_ReverseSoftImage(                int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W�̏㉺���E�𔽓]����

#ifndef DX_NON_FONT
extern	int			NS_BltStringSoftImage(              int x, int y, const TCHAR *StrData, int DestSIHandle, int DestEdgeSIHandle = -1 ,                                        int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�ň����C���[�W�ɕ�����C���[�W��]������
extern	int			NS_BltStringSoftImageToHandle(      int x, int y, const TCHAR *StrData, int DestSIHandle, int DestEdgeSIHandle /* �����K�v�Ȃ��ꍇ�� -1 */ , int FontHandle, int VerticalFlag = FALSE ) ;		// �\�t�g�E�G�A�ň����C���[�W�ɕ�����C���[�W��]������( �t�H���g�n���h���g�p�� )
#endif // DX_NON_FONT

extern	int			NS_DrawSoftImage(                   int x, int y, int SIHandle ) ;														// �\�t�g�E�G�A�ň����C���[�W����ʂɕ`�悷��

#ifndef DX_NON_SAVEFUNCTION

extern	int			NS_SaveSoftImageToBmp(              const TCHAR *FilePath, int SIHandle ) ;											// �\�t�g�E�G�A�ň����C���[�W���a�l�o�摜�t�@�C���Ƃ��ĕۑ�����
#ifndef DX_NON_PNGREAD
extern	int			NS_SaveSoftImageToPng(              const TCHAR *FilePath, int SIHandle, int CompressionLevel ) ;						// �\�t�g�E�G�A�ň����C���[�W���o�m�f�摜�t�@�C���Ƃ��ĕۑ����� CompressionLevel = ���k���A�l���傫���قǍ����k�������ׁA�O�͖����k,0�`9
#endif
#ifndef DX_NON_JPEGREAD
extern	int			NS_SaveSoftImageToJpeg(             const TCHAR *FilePath, int SIHandle, int Quality, int Sample2x1 ) ;				// �\�t�g�E�G�A�ň����C���[�W���i�o�d�f�摜�t�@�C���Ƃ��ĕۑ����� Quality = �掿�A�l���傫���قǒሳ�k���掿,0�`100 
#endif

#endif // DX_NON_SAVEFUNCTION

#endif // DX_NON_SOFTIMAGE















#ifndef DX_NON_SOUND

// DxSound.cpp�֐��v���g�^�C�v�錾

// �T�E���h�f�[�^�Ǘ��n�֐�
extern	int			NS_InitSoundMem(                        int LogOutFlag = FALSE ) ;																	// �������ɓǂ݂���WAVE�f�[�^���폜���A����������

extern	int			NS_AddSoundData(                        int Handle = -1 ) ;																										// �V�����T�E���h�f�[�^�̈���m�ۂ���
extern	int			NS_AddStreamSoundMem(                   STREAMDATA *Stream, int LoopNum,  int SoundHandle, int StreamDataType, int *CanStreamCloseFlag, int UnionHandle = -1 ) ;	// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int			NS_AddStreamSoundMemToMem(              void *FileImage, int FileImageSize, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;			// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int			NS_AddStreamSoundMemToFile(             const TCHAR *WaveFile, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;							// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int			NS_SetupStreamSoundMem(                 int SoundHandle ) ;																		// �X�g���[�����T�E���h�f�[�^�̍Đ��������s��
extern	int			NS_PlayStreamSoundMem(                  int SoundHandle, int PlayType = DX_PLAYTYPE_LOOP , int TopPositionFlag = TRUE ) ;			// �X�g���[�����T�E���h�f�[�^�̍Đ��J�n
extern	int			NS_CheckStreamSoundMem(                 int SoundHandle ) ;																		// �X�g���[�����T�E���h�f�[�^�̍Đ���Ԃ𓾂�
extern	int			NS_StopStreamSoundMem(                  int SoundHandle ) ;																		// �X�g���[�����T�E���h�f�[�^�̍Đ��I��
extern	int			NS_SetStreamSoundCurrentPosition(       int Byte, int SoundHandle ) ;																// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	int			NS_GetStreamSoundCurrentPosition(       int SoundHandle ) ;																		// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int			NS_SetStreamSoundCurrentTime(           int Time, int SoundHandle ) ;																// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	int			NS_GetStreamSoundCurrentTime(           int SoundHandle ) ;																		// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	int			NS_ProcessStreamSoundMem(               int SoundHandle ) ;																		// �X�g���[���T�E���h�̍Đ������֐�
extern	int			NS_ProcessStreamSoundMemAll(            void ) ;																					// �L���ȃX�g���[���T�E���h�̂��ׂčĐ������֐��ɂ�����


extern	int			NS_LoadSoundMem2(                       const TCHAR *FileName1, const TCHAR *FileName2 ) ;											// �O�t���ƃ��[�v���ɕ����ꂽ�T�E���h�f�[�^�̍쐬
extern	int			NS_LoadBGM(                             const TCHAR *FileName ) ;																	// ��ɂa�f�l��ǂݍ��ނ̂ɓK�����֐�

extern	int			NS_LoadSoundMemBase(                    const TCHAR *FileName, int BufferNum,      int UnionHandle = -1 ) ;						// �T�E���h�f�[�^��ǉ�����
extern	int			NS_LoadSoundMem(                        const TCHAR *FileName, int BufferNum = 3 , int UnionHandle = -1 ) ;						// �T�E���h�f�[�^��ǉ�����
extern	int			NS_LoadSoundMemToBufNumSitei(           const TCHAR *FileName, int BufferNum ) ;													// �����Đ����w��^�T�E���h�ǉ��֐�
extern	int			NS_LoadSoundMemByResource(              const TCHAR *ResourceName, const TCHAR *ResourceType, int BufferNum = 1 ) ;				// �T�E���h�����\�[�X����ǂݍ���
extern	int			NS_DuplicateSoundMem(                   int SrcSoundHandle, int BufferNum = 3 ) ;													// �����T�E���h�f�[�^���g�p����T�E���h�n���h�����쐬����( DX_SOUNDDATATYPE_MEMNOPRESS �^�C�v�̂� )

extern	int			NS_LoadSoundMemByMemImageBase(          void *FileImage, int FileImageSize, int BufferNum, int UnionHandle = -1 ) ;				// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����(�x�[�X�֐�)
extern	int			NS_LoadSoundMemByMemImage(              void *FileImage, int FileImageSize,                int UnionHandle = -1 ) ;				// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����(�o�b�t�@���w�肠��) 
extern	int			NS_LoadSoundMemByMemImage2(             void *WaveImage, int WaveImageSize, WAVEFORMATEX *WaveFormat, int WaveHeaderSize ) ;		// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����2
extern	int			NS_LoadSoundMemByMemImageToBufNumSitei( void *FileImage, int FileImageSize, int BufferNum ) ;										// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����
extern	int			NS_LoadSoundMem2ByMemImage(             void *FileImage1, int FileImageSize1, void *FileImage2, int FileImageSize2 ) ;				// ��������ɓW�J���ꂽ�t�@�C���C���[�W����O�t���ƃ��[�v���ɕ����ꂽ�n���h�����쐬����
extern	int			NS_LoadSoundMemFromSoftSound(           int SoftSoundHandle, int BufferNum = 3 ) ;													// �\�t�g�E�G�A�Ŕg�`�𐧌䂷��T�E���h�f�[�^����T�E���h�n���h�����쐬����

extern	int			NS_DeleteSoundMem(                      int SoundHandle, int LogOutFlag = FALSE ) ;												// �������ɓǂݍ���WAVE�f�[�^���폜����

extern	int			NS_PlaySoundMem(                        int SoundHandle, int PlayType, int TopPositionFlag = TRUE ) ;								// �������ɓǂ݂���WAVE�f�[�^���Đ�����
extern	int			NS_StopSoundMem(                                                     int SoundHandle ) ;											// �������ɓǂݍ���WAVE�f�[�^�̍Đ����~�߂�
extern	int			NS_CheckSoundMem(                                                    int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^���Đ��������ׂ�
extern	int			NS_SetPanSoundMem(                      int PanPal,                  int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀp����ݒ肷��
extern	int			NS_GetPanSoundMem(                                                   int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀp�����擾����
extern	int			NS_SetVolumeSoundMem(                   int VolumePal,               int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀ{�����[����ݒ肷��( 100����1�f�V�x���P�� )
extern	int			NS_ChangeVolumeSoundMem(                int VolumePal,               int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀ{�����[����ݒ肷��( �p�[�Z���g�w�� )
extern	int			NS_GetVolumeSoundMem(                                                int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̍Đ��̃{�����[�����擾����
extern	int			NS_SetFrequencySoundMem(                int FrequencyPal,            int SoundHandle ) ;											// �������ɓǂݍ���WAVE�f�[�^�̍Đ����g����ݒ肷��
extern	int			NS_GetFrequencySoundMem(                                             int SoundHandle ) ;											// �������ɓǂݍ���WAVE�f�[�^�̍Đ����g�����擾����
extern	int			NS_ResetFrequencySoundMem(                                           int SoundHandle ) ;											// �������ɓǂݍ���WAVE�f�[�^�̍Đ����g����ǂݍ��ݒ���̏�Ԃɖ߂�

extern	int			NS_SetNextPlayPanSoundMem(              int PanPal,                  int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̎��̍Đ��ɂ̂ݎg�p����p����ݒ肷��
extern	int			NS_SetNextPlayVolumeSoundMem(           int VolumePal,               int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̎��̍Đ��ɂ̂ݎg�p����{�����[����ݒ肷��( 100����1�f�V�x���P�� )
extern	int			NS_ChangeNextPlayVolumeSoundMem(        int VolumePal,               int SoundHandle ) ;											// �������ɓǂ݂���WAVE�f�[�^�̎��̍Đ��ɂ̂ݎg�p����{�����[����ݒ肷��( �p�[�Z���g�w�� )
extern	int			NS_SetNextPlayFrequencySoundMem(        int FrequencyPal,            int SoundHandle ) ;											// �������ɓǂݍ���WAVE�f�[�^�̎��̍Đ��ɂ̂ݎg�p����Đ����g����ݒ肷��

extern	int			NS_SetCurrentPositionSoundMem(          int SamplePosition,          int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���T���v���P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	int			NS_GetCurrentPositionSoundMem(                                       int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���T���v���P�ʂŎ擾����
extern	int			NS_SetSoundCurrentPosition(             int Byte,                    int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	int			NS_GetSoundCurrentPosition(                                          int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int			NS_SetSoundCurrentTime(                 int Time,                    int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	int			NS_GetSoundCurrentTime(                                              int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	int			NS_GetSoundTotalSample(                                              int SoundHandle ) ;											// �T�E���h�n���h���̉��̑����Ԃ��擾����(�P�ʂ̓T���v��)
extern	int			NS_GetSoundTotalTime(                                                int SoundHandle ) ;											// �T�E���h�n���h���̉��̑����Ԃ��擾����(�P�ʂ̓~���b)

extern	int			NS_SetLoopPosSoundMem(                  int LoopTime,                int SoundHandle ) ;											// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��
extern	int			NS_SetLoopTimePosSoundMem(              int LoopTime,                int SoundHandle ) ;											// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��
extern	int			NS_SetLoopSamplePosSoundMem(            int LoopSamplePosition,      int SoundHandle ) ;											// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��

extern	int			NS_SetLoopStartTimePosSoundMem(         int LoopStartTime,           int SoundHandle ) ;											// �T�E���h�n���h���Ƀ��[�v�J�n�ʒu��ݒ肷��
extern	int			NS_SetLoopStartSamplePosSoundMem(       int LoopStartSamplePosition, int SoundHandle ) ;											// �T�E���h�n���h���Ƀ��[�v�J�n�ʒu��ݒ肷��

extern	int			NS_Set3DPositionSoundMem(               VECTOR Position,                                int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̍Đ��ʒu��ݒ肷��
extern	int			NS_Set3DRadiusSoundMem(                 float Radius,                                   int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̉����������鋗����ݒ肷��
//extern	int			NS_Set3DInnerRadiusSoundMem(            float Radius,                                   int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̉��ʂP�O�O���ŕ������鋗����ݒ肷��
extern	int			NS_Set3DVelocitySoundMem(               VECTOR Velocity,                                int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̈ړ����x��ݒ肷��
//extern	int			NS_Set3DFrontPosition_UpVecYSoundMem(   VECTOR FrontPosition,                           int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̕��������肷�邽�߂̑O�����W��ݒ肷��( �����̏������Y���Œ� )
//extern	int			NS_Set3DFrontPositionSoundMem(          VECTOR FrontPosition, VECTOR UpVector,          int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̕��������肷�邽�߂̑O�����W�Ə������ݒ肷��
//extern	int			NS_Set3DConeAngleSoundMem(              float InnerAngle, float OuterAngle,             int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̕����̊p�x�͈͂�ݒ肷��
//extern	int			NS_Set3DConeVolumeSoundMem(             float InnerAngleVolume, float OuterAngleVolume, int SoundHandle ) ;						// �T�E���h�n���h���̂R�c�T�E���h�p�̕����̊p�x�͈͂̉��ʔ{����ݒ肷��

// �ݒ�֌W�֐�
extern	int			NS_SetCreateSoundDataType(              int SoundDataType ) ;																		// �쐬����T�E���h�̃f�[�^�`����ݒ肷��( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int			NS_GetCreateSoundDataType(              void ) ;																					// �쐬����T�E���h�̃f�[�^�`�����擾����( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int			NS_SetDisableReadSoundFunctionMask(     int Mask ) ;																				// �g�p���Ȃ��T�E���h�f�[�^�ǂݍ��ݏ����̃}�X�N��ݒ肷��( DX_READSOUNDFUNCTION_PCM �� )
extern	int			NS_GetDisableReadSoundFunctionMask(     void ) ;																					// �g�p���Ȃ��T�E���h�f�[�^�ǂݍ��ݏ����̃}�X�N���擾����( DX_READSOUNDFUNCTION_PCM �� )
extern	int			NS_SetEnableSoundCaptureFlag(           int Flag ) ;																				// �T�E���h�L���v�`����O��Ƃ�����������邩�ǂ�����ݒ肷��
extern	int			NS_SetUseSoftwareMixingSoundFlag(       int Flag ) ;																				// �T�E���h�̏������\�t�g�E�G�A�ōs�����ǂ�����ݒ肷��( TRUE:�\�t�g�E�G�A  FALSE:�n�[�h�E�G�A( �f�t�H���g ) )
extern	int			NS_SetEnableXAudioFlag(                 int Flag ) ;																				// �T�E���h�̍Đ���XAudio���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )

extern	int			NS_SetCreate3DSoundFlag(                    int Flag ) ;																			// ���ɍ쐬����T�E���h���R�c�T�E���h�p�ɂ��邩�ǂ�����ݒ肷��( TRUE:�R�c�T�E���h�p�ɂ���  FALSE:�R�c�T�E���h�p�ɂ��Ȃ�( �f�t�H���g ) )
extern	int			NS_Set3DSoundOneMetre(                      float Distance ) ;																		// �R�c��Ԃ̂P���[�g���ɓ��鋗����ݒ肷��( �f�t�H���g:1.0f )
extern	int			NS_Set3DSoundListenerPosAndFrontPos_UpVecY( VECTOR Position, VECTOR FrontPosition ) ;												// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu��ݒ肷��( ���X�i�[�̏�����ʒu�͂x���Œ� )
extern	int			NS_Set3DSoundListenerPosAndFrontPos(        VECTOR Position, VECTOR FrontPosition, VECTOR UpVector ) ;								// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu�ƃ��X�i�[�̏������ݒ肷��
extern	int			NS_Set3DSoundListenerVelocity(              VECTOR Velocity ) ;																		// �R�c�T�E���h�̃��X�i�[�̈ړ����x��ݒ肷��
extern	int			NS_Set3DSoundListenerConeAngle(             float InnerAngle, float OuterAngle ) ;													// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂�ݒ肷��
extern	int			NS_Set3DSoundListenerConeVolume(            float InnerAngleVolume, float OuterAngleVolume ) ;										// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂̉��ʔ{����ݒ肷��

// ���擾�n�֐�
extern	void*		NS_GetDSoundObj(                        void ) ;	/* �߂�l�� IDirectSound * �ɃL���X�g���ĉ����� */								// �c�w���C�u�������g�p���Ă��� DirectSound �I�u�W�F�N�g���擾����

#ifndef DX_NON_BEEP
// BEEP���Đ��p����
extern	int			NS_SetBeepFrequency(					int Freq ) ;																				// �r�[�v�����g���ݒ�֐�
extern	int			NS_PlayBeep(							void ) ;																					// �r�[�v�����Đ�����
extern	int			NS_StopBeep(							void ) ;																					// �r�[�v�����~�߂�
#endif

// ���b�p�[�֐�
extern	int			NS_PlaySoundFile(						const TCHAR *FileName, int PlayType ) ;														// WAVE�t�@�C�����Đ�����
extern	int			NS_PlaySound(							const TCHAR *FileName, int PlayType ) ;														// PlaySoundFile �̋�����
extern	int			NS_CheckSoundFile(						void ) ;																					// WAVE�t�@�C���̍Đ��������ׂ�
extern	int			NS_CheckSound(							void ) ;																					// CheckSoundFile �̋�����
extern	int			NS_StopSoundFile(						void ) ;																					// WAVE�t�@�C���̍Đ����~�߂�
extern	int			NS_StopSound(							void ) ;																					// StopSoundFile �̋�����
extern	int			NS_SetVolumeSoundFile(					int VolumePal ) ;																			// WAVE�t�@�C���̉��ʂ��Z�b�g����
extern	int			NS_SetVolumeSound(						int VolumePal ) ;																			// SetVolumeSound �̋�����

// �\�t�g�E�G�A����T�E���h�n�֐�
extern	int			NS_InitSoftSound(						void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�����ׂĉ������
extern	int			NS_LoadSoftSound(						const TCHAR *FileName ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^���t�@�C������쐬����
extern	int			NS_LoadSoftSoundFromMemImage(			const void *FileImage, int FileImageSize ) ;												// �\�t�g�E�G�A�ň����g�`�f�[�^����������ɓW�J���ꂽ�t�@�C���C���[�W����쐬����
extern	int			NS_MakeSoftSound(						int UseFormat_SoftSoundHandle, int SampleNum ) ;											// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �t�H�[�}�b�g�͈����̃\�t�g�E�G�A�T�E���h�n���h���Ɠ������̂ɂ��� )
extern	int			NS_MakeSoftSound2Ch16Bit44KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSound2Ch16Bit22KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound2Ch8Bit44KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:2 �ʎq���r�b�g��:8bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSound2Ch8Bit22KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:2 �ʎq���r�b�g��:8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound1Ch16Bit44KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSound1Ch16Bit22KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSound1Ch8Bit44KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:1 �ʎq���r�b�g��:8bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSound1Ch8Bit22KHz(			int SampleNum ) ;																			// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����( �`�����l����:1 �ʎq���r�b�g��:8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundCustom(				int ChannelNum, int BitsPerSample, int SamplesPerSec, int SampleNum );						// �\�t�g�E�G�A�ň�����̔g�`�f�[�^���쐬����
extern	int			NS_DeleteSoftSound(					int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^���������
#ifndef DX_NON_SAVEFUNCTION
extern	int			NS_SaveSoftSound(						int SoftSoundHandle, const TCHAR *FileName ) ;												// �\�t�g�E�G�A�ň����g�`�f�[�^�𖳈��kWav�`���ŕۑ�����
#endif // DX_NON_SAVEFUNCTION
extern	int			NS_GetSoftSoundSampleNum(				int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^�̃T���v�������擾����
extern	int			NS_GetSoftSoundFormat(					int SoftSoundHandle, int *Channels, int *BitsPerSample, int *SamplesPerSec ) ;				// �\�t�g�E�G�A�ň����g�`�f�[�^�̃t�H�[�}�b�g���擾����
extern	int			NS_ReadSoftSoundData(					int SoftSoundHandle, int SamplePosition, int *Channel1, int *Channel2 ) ;					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃T���v����ǂݎ��
extern	int			NS_WriteSoftSoundData(					int SoftSoundHandle, int SamplePosition, int Channel1, int Channel2 ) ;						// �\�t�g�E�G�A�ň����g�`�f�[�^�̃T���v������������
extern	void		*NS_GetSoftSoundDataImage(				int SoftSoundHandle ) ;																		// �\�t�g�E�G�A�ň����g�`�f�[�^�̔g�`�C���[�W���i�[����Ă��郁�����A�h���X���擾����

extern	int			NS_InitSoftSoundPlayer(				void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�����ׂĉ������
extern	int			NS_MakeSoftSoundPlayer(				int UseFormat_SoftSoundHandle ) ;															// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �t�H�[�}�b�g�͈����̃\�t�g�E�G�A�T�E���h�n���h���Ɠ������̂ɂ��� )
extern	int			NS_MakeSoftSoundPlayer2Ch16Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch16Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:2 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch8Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:2 �ʎq���r�b�g��:8bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSoundPlayer2Ch8Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:2 �ʎq���r�b�g��:8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch16Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch16Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:1 �ʎq���r�b�g��:16bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch8Bit44KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:1 �ʎq���r�b�g��:8bit �T���v�����O���g��:44KHz )
extern	int			NS_MakeSoftSoundPlayer1Ch8Bit22KHz(	void ) ;																					// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����( �`�����l����:1 �ʎq���r�b�g��:8bit �T���v�����O���g��:22KHz )
extern	int			NS_MakeSoftSoundPlayerCustom(			int ChannelNum, int BitsPerSample, int SamplesPerSec ) ;									// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���쐬����
extern	int			NS_DeleteSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[���폜����
extern	int			NS_AddDataSoftSoundPlayer(				int SSoundPlayerHandle, int SoftSoundHandle, int AddSamplePosition, int AddSampleNum ) ;	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�ɔg�`�f�[�^��ǉ�����( �t�H�[�}�b�g�������ł͂Ȃ��ꍇ�̓G���[ )
extern	int			NS_AddDirectDataSoftSoundPlayer(		int SSoundPlayerHandle, void *SoundData, int AddSampleNum ) ;								// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�Ƀv���C���[���Ή������t�H�[�}�b�g�̐��g�`�f�[�^��ǉ�����
extern	int			NS_AddOneDataSoftSoundPlayer(			int SSoundPlayerHandle, int Channel1, int Channel2 ) ;										// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�ɔg�`�f�[�^����ǉ�����
extern	int			NS_GetSoftSoundPlayerFormat(			int SSoundPlayerHandle, int *Channels, int *BitsPerSample, int *SamplesPerSec ) ;			// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�������f�[�^�t�H�[�}�b�g���擾����
extern	int			NS_StartSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̍Đ��������J�n����
extern	int			NS_CheckStartSoftSoundPlayer(			int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̍Đ��������J�n����Ă��邩�擾����( TRUE:�J�n���Ă���  FALSE:��~���Ă��� )
extern	int			NS_StopSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̍Đ��������~����
extern	int			NS_ResetSoftSoundPlayer(				int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�̏�Ԃ�������Ԃɖ߂�( �ǉ����ꂽ�g�`�f�[�^�͍폜����A�Đ���Ԃ������ꍇ�͒�~���� )
extern	int			NS_GetStockDataLengthSoftSoundPlayer(	int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�ɒǉ������g�`�f�[�^�ł܂��Đ��p�T�E���h�o�b�t�@�ɓ]������Ă��Ȃ��g�`�f�[�^�̃T���v�������擾����
extern	int			NS_CheckSoftSoundPlayerNoneData(		int SSoundPlayerHandle ) ;																	// �\�t�g�E�G�A�ň����g�`�f�[�^�̃v���C���[�ɍĐ��p�T�E���h�o�b�t�@�ɓ]�����Ă��Ȃ��g�`�f�[�^�������A�Đ��p�T�E���h�o�b�t�@�ɂ������f�[�^�ȊO�������ǂ������擾����( TRUE:�����f�[�^�ȊO����  FALSE:�L���f�[�^������ )




// �l�h�c�h����֐�
extern	int			NS_DeleteMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�n���h�����폜����
extern	int			NS_LoadMusicMem(						const TCHAR *FileName ) ;																	// �l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_LoadMusicMemByMemImage(				void *FileImage, int FileImageSize ) ;														// ��������ɓW�J���ꂽ�l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_LoadMusicMemByResource(				const TCHAR *ResourceName, const TCHAR *ResourceType ) ;									// ���\�[�X��̂l�h�c�h�t�@�C����ǂݍ���
extern	int			NS_PlayMusicMem(						int MusicHandle, int PlayType ) ;															// �ǂݍ��񂾂l�h�c�h�f�[�^�̉��t���J�n����
extern	int			NS_StopMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�f�[�^�̉��t���~����
extern	int			NS_CheckMusicMem(						int MusicHandle ) ;																			// �l�h�c�h�f�[�^�����t�����ǂ������擾����( TRUE:���t��  FALSE:��~�� )
extern	int			NS_SetVolumeMusicMem(					int Volume, int MusicHandle ) ;																// �l�h�c�h�f�[�^�̍Đ����ʂ��Z�b�g����
extern	int			NS_GetMusicMemPosition(				int MusicHandle ) ;																			// �l�h�c�h�f�[�^�̌��݂̍Đ��ʒu���擾����
extern	int			NS_InitMusicMem(						void ) ;																					// �l�h�c�h�f�[�^�n���h�������ׂč폜����
extern	int			NS_ProcessMusicMem(					void ) ;																					// �l�h�c�h�f�[�^�̎����I����

extern	int			NS_PlayMusic(							const TCHAR *FileName, int PlayType ) ;														// �l�h�c�h�t�@�C�������t����
extern	int			NS_PlayMusicByMemImage(				void *FileImage, int FileImageSize, int PlayType ) ;										// ��������ɓW�J����Ă���l�h�c�h�t�@�C�������t����
extern	int			NS_PlayMusicByResource(				const TCHAR *ResourceName, const TCHAR *ResourceType, int PlayType ) ;						// ���\�[�X����l�h�c�h�t�@�C����ǂݍ���ŉ��t����
extern	int			NS_SetVolumeMusic(						int Volume ) ;																				// �l�h�c�h�̍Đ����ʂ��Z�b�g����
extern	int			NS_StopMusic(							void ) ;																					// �l�h�c�h�t�@�C���̉��t��~
extern	int			NS_CheckMusic(							void ) ;																					// �l�h�c�h�t�@�C�������t�����ۂ������擾����
extern	int			NS_GetMusicPosition(					void ) ;																					// �l�h�c�h�̌��݂̍Đ��ʒu���擾����

extern	int			NS_SelectMidiMode(						int Mode ) ;																				// �l�h�c�h�̍Đ��`�����Z�b�g����

#endif // DX_NON_SOUND










// DxArchive_.cpp �֐� �v���g�^�C�v�錾
extern	int			NS_DXArchivePreLoad(	const TCHAR *FilePath , int ASync = FALSE ) ;					// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l: -1=�G���[  0=���� )
extern	int			NS_DXArchiveCheckIdle( const TCHAR *FilePath ) ;										// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l�F TRUE=�������� FALSE=�܂� )
extern	int			NS_DXArchiveRelease(	const TCHAR *FilePath ) ;										// �w��̂c�w�`�t�@�C��������������������
extern	int			NS_DXArchiveCheckFile( const TCHAR *FilePath, const TCHAR *TargetFilePath ) ;			// �c�w�`�t�@�C���̒��Ɏw��̃t�@�C�������݂��邩�ǂ����𒲂ׂ�ATargetFilePath �͂c�w�`�t�@�C�����J�����g�t�H���_�Ƃ����ꍇ�̃p�X( �߂�l:  -1=�G���[  0:����  1:���� )































#else  // DX_THREAD_SAFE


// DxSystem.cpp�֐��v���g�^�C�v�錾

// �E�G�C�g�n�֐�
#define NS_WaitTimer							WaitTimer
#ifndef DX_NON_INPUT
#define NS_WaitKey								WaitKey
#endif // DX_NON_INPUT

// �J�E���^�y�ю����擾�n�֐�
#define NS_GetNowCount							GetNowCount
#define NS_GetNowHiPerformanceCount				GetNowHiPerformanceCount
#define NS_GetDateTime							GetDateTime

// �����擾
#define NS_GetRand								GetRand
#define NS_SRand								SRand










// DxLog.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_LOG

// �G���[�����֐�
#define NS_ErrorLogAdd							ErrorLogAdd
#define NS_ErrorLogFmtAdd						ErrorLogFmtAdd
#define NS_ErrorLogTabAdd						ErrorLogTabAdd
#define NS_ErrorLogTabSub						ErrorLogTabSub
#define NS_SetUseTimeStampFlag					SetUseTimeStampFlag
#define NS_AppLogAdd							AppLogAdd

#ifndef DX_NON_PRINTF_DX

// ���O�o�͋@�\�֐�
#define NS_SetLogDrawOutFlag					SetLogDrawOutFlag
#define NS_GetLogDrawFlag						GetLogDrawFlag
#define NS_SetLogFontSize						SetLogFontSize

// �ȈՉ�ʏo�͊֐�
#define NS_printfDx								printfDx
#define NS_clsDx								clsDx
#endif

#endif // DX_NON_LOG













#ifndef DX_NON_ASYNCLOAD

// DxASyncLoad.cpp�֐��v���g�^�C�v�錾

// �񓯊��ǂݍ��݊֌W
#define NS_SetUseASyncLoadFlag					SetUseASyncLoadFlag
#define NS_CheckHandleASyncLoad					CheckHandleASyncLoad
#define NS_GetHandleASyncLoadResult				GetHandleASyncLoadResult
#define NS_GetASyncLoadNum						GetASyncLoadNum

#endif // DX_NON_ASYNCLOAD










// DxHandle.cpp�֐��v���g�^�C�v�錾

#define NS_SetDeleteHandleFlag					SetDeleteHandleFlag














// DxWindow.cpp�֐��v���g�^�C�v�錾

#ifdef __WINDOWS__

// �֗��֐�
#define NS_GetResourceInfo						GetResourceInfo
#define NS_GetResourceIDString					GetResourceIDString

// �E�C���h�E�֌W���擾�֐�
#define NS_GetWindowCRect						GetWindowCRect
#define NS_GetWindowActiveFlag					GetWindowActiveFlag
#define NS_GetMainWindowHandle					GetMainWindowHandle
#define NS_GetWindowModeFlag					GetWindowModeFlag
#define NS_GetDefaultState						GetDefaultState
#define NS_GetActiveFlag						GetActiveFlag
#define NS_GetNoActiveState						GetNoActiveState
#define NS_GetMouseDispFlag						GetMouseDispFlag
#define NS_GetAlwaysRunFlag						GetAlwaysRunFlag
#define NS__GetSystemInfo						_GetSystemInfo
#define NS_GetPcInfo							GetPcInfo
#define NS_GetUseMMXFlag						GetUseMMXFlag
#define NS_GetUseSSEFlag						GetUseSSEFlag
#define NS_GetUseSSE2Flag						GetUseSSE2Flag
#define NS_GetWindowCloseFlag					GetWindowCloseFlag
#define NS_GetTaskInstance						GetTaskInstance
#define NS_GetUseWindowRgnFlag					GetUseWindowRgnFlag
#define NS_GetWindowSizeChangeEnableFlag		GetWindowSizeChangeEnableFlag
#define NS_GetWindowSizeExtendRate				GetWindowSizeExtendRate
#define NS_GetWindowSize						GetWindowSize
#define NS_GetWindowPosition					GetWindowPosition
#define NS_GetWindowUserCloseFlag				GetWindowUserCloseFlag
#define NS_GetNotDrawFlag						GetNotDrawFlag
#define NS_GetPaintMessageFlag					GetPaintMessageFlag
#define NS_GetValidHiPerformanceCounter			GetValidHiPerformanceCounter

// �ݒ�n�֐�
#define NS_ChangeWindowMode						ChangeWindowMode
#define NS_SetUseCharSet						SetUseCharSet
#define NS_LoadPauseGraph						LoadPauseGraph
#define NS_LoadPauseGraphFromMem				LoadPauseGraphFromMem
#define NS_SetActiveStateChangeCallBackFunction	SetActiveStateChangeCallBackFunction
#define NS_SetWindowText						SetWindowText
#define NS_SetMainWindowText					SetMainWindowText
#define NS_SetMainWindowClassName				SetMainWindowClassName
#ifndef DX_NON_LOG
#define NS_SetOutApplicationLogValidFlag		SetOutApplicationLogValidFlag
#define NS_SetApplicationLogSaveDirectory		SetApplicationLogSaveDirectory
#define NS_SetUseDateNameLogFile				SetUseDateNameLogFile
#endif // DX_NON_LOG
#define NS_SetAlwaysRunFlag						SetAlwaysRunFlag
#define NS_SetWindowIconID						SetWindowIconID
#define NS_SetWindowIconHandle					SetWindowIconHandle
#define NS_SetUseASyncChangeWindowModeFunction	SetUseASyncChangeWindowModeFunction
#define NS_SetWindowStyleMode					SetWindowStyleMode
#define NS_SetWindowSizeChangeEnableFlag		SetWindowSizeChangeEnableFlag
#define NS_SetWindowSizeExtendRate				SetWindowSizeExtendRate
#define NS_SetWindowSize						SetWindowSize
#define NS_SetWindowPosition					SetWindowPosition
#define NS_SetSysCommandOffFlag					SetSysCommandOffFlag
#define NS_SetHookWinProc						SetHookWinProc
#define NS_SetUseHookWinProcReturnValue			SetUseHookWinProcReturnValue
#define NS_SetDoubleStartValidFlag				SetDoubleStartValidFlag
#define NS_AddMessageTakeOverWindow				AddMessageTakeOverWindow
#define NS_SubMessageTakeOverWindow				SubMessageTakeOverWindow

#define NS_SetWindowInitPosition				SetWindowInitPosition
#define NS_SetNotWinFlag						SetNotWinFlag
#define NS_SetNotDrawFlag						SetNotDrawFlag
#define NS_SetNotSoundFlag						SetNotSoundFlag
#define NS_SetNotInputFlag						SetNotInputFlag
#define NS_SetDialogBoxHandle					SetDialogBoxHandle
#define NS_SetWindowVisibleFlag					SetWindowVisibleFlag
#define NS_SetWindowMinimizeFlag				SetWindowMinimizeFlag
#define NS_SetWindowUserCloseEnableFlag			SetWindowUserCloseEnableFlag
#define NS_SetDxLibEndPostQuitMessageFlag		SetDxLibEndPostQuitMessageFlag
#define NS_SetUserWindow						SetUserWindow
#define NS_SetUserChildWindow					SetUserChildWindow
#define NS_SetUserWindowMessageProcessDXLibFlag	SetUserWindowMessageProcessDXLibFlag
#define NS_SetDXArchivePriority					SetDXArchivePriority
#define NS_SetDXArchiveExtension				SetDXArchiveExtension
#define NS_SetDXArchiveKeyString				SetDXArchiveKeyString
#define NS_SetBackgroundColor					SetBackgroundColor
#define NS_SetUseFPUPreserveFlag				SetUseFPUPreserveFlag
#define NS_SetValidMousePointerWindowOutClientAreaMoveFlag		SetValidMousePointerWindowOutClientAreaMoveFlag
#define NS_SetUseBackBufferTransColorFlag		SetUseBackBufferTransColorFlag
#define NS_SetResourceModule					SetResourceModule

// �N���b�v�{�[�h�֌W
#define NS_GetClipboardText						GetClipboardText
#define NS_SetClipboardText						SetClipboardText

// �h���b�O���h���b�v���ꂽ�t�@�C���֌W
#define NS_SetDragFileValidFlag					SetDragFileValidFlag
#define NS_DragFileInfoClear					DragFileInfoClear
#define NS_GetDragFilePath						GetDragFilePath
#define NS_GetDragFileNum						GetDragFileNum

// �E�C���h�E�`��̈�ݒ�n�֐�
#define NS_CreateRgnFromGraph					CreateRgnFromGraph
#define NS_CreateRgnFromBaseImage				CreateRgnFromBaseImage
#define NS_SetWindowRgnGraph					SetWindowRgnGraph
#define NS_UpdateTransColorWindowRgn			UpdateTransColorWindowRgn

// �c�[���o�[�֌W
#define NS_SetupToolBar							SetupToolBar
#define NS_AddToolBarButton						AddToolBarButton
#define NS_AddToolBarSep						AddToolBarSep
#define NS_GetToolBarButtonState				GetToolBarButtonState
#define NS_SetToolBarButtonState				SetToolBarButtonState
#define NS_DeleteAllToolBarButton				DeleteAllToolBarButton

// ���j���[�֌W
#define NS_SetUseMenuFlag						SetUseMenuFlag
#define NS_SetUseKeyAccelFlag					SetUseKeyAccelFlag

#define NS_AddKeyAccel							AddKeyAccel
#define NS_AddKeyAccel_Name						AddKeyAccel_Name
#define NS_AddKeyAccel_ID						AddKeyAccel_ID
#define NS_ClearKeyAccel						ClearKeyAccel

#define NS_AddMenuItem							AddMenuItem
#define NS_DeleteMenuItem						DeleteMenuItem
#define NS_CheckMenuItemSelect					CheckMenuItemSelect
#define NS_SetMenuItemEnable					SetMenuItemEnable
#define NS_SetMenuItemMark						SetMenuItemMark
#define NS_CheckMenuItemSelectAll				CheckMenuItemSelectAll

#define NS_AddMenuItem_Name						AddMenuItem_Name
#define NS_AddMenuLine_Name						AddMenuLine_Name
#define NS_InsertMenuItem_Name					InsertMenuItem_Name
#define NS_InsertMenuLine_Name					InsertMenuLine_Name
#define NS_DeleteMenuItem_Name					DeleteMenuItem_Name
#define NS_CheckMenuItemSelect_Name				CheckMenuItemSelect_Name
#define NS_SetMenuItemEnable_Name				SetMenuItemEnable_Name
#define NS_SetMenuItemMark_Name					SetMenuItemMark_Name

#define NS_AddMenuItem_ID						AddMenuItem_ID
#define NS_AddMenuLine_ID						AddMenuLine_ID
#define NS_InsertMenuItem_ID					InsertMenuItem_ID
#define NS_InsertMenuLine_ID					InsertMenuLine_ID
#define NS_DeleteMenuItem_ID					DeleteMenuItem_ID
#define NS_CheckMenuItemSelect_ID				CheckMenuItemSelect_ID
#define NS_SetMenuItemEnable_ID					SetMenuItemEnable_ID
#define NS_SetMenuItemMark_ID					SetMenuItemMark_ID

#define NS_DeleteMenuItemAll					DeleteMenuItemAll
#define NS_ClearMenuItemSelect					ClearMenuItemSelect
#define NS_GetMenuItemID						GetMenuItemID
#define NS_GetMenuItemName						GetMenuItemName
#define NS_LoadMenuResource						LoadMenuResource
#define NS_SetMenuItemSelectCallBackFunction	SetMenuItemSelectCallBackFunction

#define NS_SetWindowMenu						SetWindowMenu
#define NS_SetDisplayMenuFlag					SetDisplayMenuFlag
#define NS_GetDisplayMenuFlag					GetDisplayMenuFlag
#define NS_GetUseMenuFlag						GetUseMenuFlag
#define NS_SetAutoMenuDisplayFlag				SetAutoMenuDisplayFlag

#endif // __WINDOWS__

// �}�E�X�֌W�֐�
#define NS_SetMouseDispFlag						SetMouseDispFlag
#define NS_GetMousePoint						GetMousePoint
#define NS_SetMousePoint						SetMousePoint
#ifndef DX_NON_INPUT
#define NS_GetMouseInput						GetMouseInput
#define NS_GetMouseWheelRotVol					GetMouseWheelRotVol
#define NS_GetMouseHWheelRotVol					GetMouseHWheelRotVol
#define NS_GetMouseWheelRotVolF					GetMouseWheelRotVolF
#define NS_GetMouseHWheelRotVolF				GetMouseHWheelRotVolF
#define NS_GetMouseInputLog						GetMouseInputLog
#endif // DX_NON_INPUT












// DxMemory.cpp�֐��v���g�^�C�v�錾

// �������m�یn�֐�
#define NS_DxAlloc								DxAlloc
#define NS_DxCalloc								DxCalloc
#define NS_DxRealloc							DxRealloc
#define NS_DxFree								DxFree
#define NS_DxSetAllocSizeTrap					DxSetAllocSizeTrap
#define NS_DxSetAllocPrintFlag					DxSetAllocPrintFlag
#define NS_DxGetAllocSize						DxGetAllocSize
#define NS_DxGetAllocNum						DxGetAllocNum
#define NS_DxDumpAlloc							DxDumpAlloc
#define NS_DxErrorCheckAlloc					DxErrorCheckAlloc
#define NS_DxSetAllocSizeOutFlag				DxSetAllocSizeOutFlag
#define NS_DxSetAllocMemoryErrorCheckFlag		DxSetAllocMemoryErrorCheckFlag










// DxInputString.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUTSTRING

// �����R�[�h�o�b�t�@����֌W
#define NS_StockInputChar						StockInputChar
#define NS_ClearInputCharBuf					ClearInputCharBuf
#define NS_GetInputChar							GetInputChar
#define NS_GetInputCharWait						GetInputCharWait

#define NS_GetOneChar							GetOneChar
#define NS_GetOneCharWait						GetOneCharWait
#define NS_GetCtrlCodeCmp						GetCtrlCodeCmp

#ifndef DX_NON_KEYEX

#define NS_DrawIMEInputString					DrawIMEInputString
#define NS_SetUseIMEFlag						SetUseIMEFlag
#define NS_SetInputStringMaxLengthIMESync		SetInputStringMaxLengthIMESync
#define NS_SetIMEInputStringMaxLength			SetIMEInputStringMaxLength

#endif

#define NS_GetStringPoint						GetStringPoint
#define NS_GetStringPoint2						GetStringPoint2

#ifndef DX_NON_FONT
#define NS_DrawObtainsString					DrawObtainsString
#endif // DX_NON_FONT
#define NS_DrawObtainsBox						DrawObtainsBox

#ifndef DX_NON_KEYEX

#define NS_InputStringToCustom					InputStringToCustom

#define NS_KeyInputString						KeyInputString
#define NS_KeyInputSingleCharString				KeyInputSingleCharString
#define NS_KeyInputNumber						KeyInputNumber

#define NS_GetIMEInputModeStr					GetIMEInputModeStr
#define NS_GetIMEInputData						GetIMEInputData
#define NS_SetKeyInputStringColor				SetKeyInputStringColor
#define NS_SetKeyInputStringFont				SetKeyInputStringFont
#define NS_DrawKeyInputModeString				DrawKeyInputModeString

#define NS_InitKeyInput							InitKeyInput
#define NS_MakeKeyInput							MakeKeyInput
#define NS_DeleteKeyInput						DeleteKeyInput
#define NS_SetActiveKeyInput					SetActiveKeyInput
#define NS_GetActiveKeyInput					GetActiveKeyInput
#define NS_CheckKeyInput						CheckKeyInput
#define NS_ReStartKeyInput						ReStartKeyInput
#define NS_ProcessActKeyInput					ProcessActKeyInput
#define NS_DrawKeyInputString					DrawKeyInputString

#define NS_SetKeyInputSelectArea				SetKeyInputSelectArea
#define NS_GetKeyInputSelectArea				GetKeyInputSelectArea
#define NS_SetKeyInputDrawStartPos				SetKeyInputDrawStartPos
#define NS_GetKeyInputDrawStartPos				GetKeyInputDrawStartPos
#define NS_SetKeyInputCursorBrinkTime			SetKeyInputCursorBrinkTime
#define NS_SetKeyInputCursorBrinkFlag			SetKeyInputCursorBrinkFlag
#define NS_SetKeyInputString					SetKeyInputString
#define NS_SetKeyInputNumber					SetKeyInputNumber
#define NS_SetKeyInputNumberToFloat				SetKeyInputNumberToFloat
#define NS_GetKeyInputString					GetKeyInputString
#define NS_GetKeyInputNumber					GetKeyInputNumber
#define NS_GetKeyInputNumberToFloat				GetKeyInputNumberToFloat
#define NS_SetKeyInputCursorPosition			SetKeyInputCursorPosition
#define NS_GetKeyInputCursorPosition			GetKeyInputCursorPosition

#endif // DX_NON_KEYEX

#endif // DX_NON_INPUTSTRING












// DxFile.cpp�֐��v���g�^�C�v�錾

// �t�@�C���A�N�Z�X�֐�
#define NS_FileRead_open						FileRead_open
#define NS_FileRead_size						FileRead_size
#define NS_FileRead_close						FileRead_close
#define NS_FileRead_tell						FileRead_tell
#define NS_FileRead_seek						FileRead_seek
#define NS_FileRead_read						FileRead_read
#define NS_FileRead_idle_chk					FileRead_idle_chk
#define NS_FileRead_eof							FileRead_eof
#define NS_FileRead_gets						FileRead_gets
#define NS_FileRead_getc						FileRead_getc
#define NS_FileRead_scanf						FileRead_scanf

#define NS_FileRead_createInfo					FileRead_createInfo
#define NS_FileRead_getInfoNum					FileRead_getInfoNum
#define NS_FileRead_getInfo						FileRead_getInfo
#define NS_FileRead_deleteInfo					FileRead_deleteInfo

#define NS_FileRead_findFirst					FileRead_findFirst
#define NS_FileRead_findNext					FileRead_findNext
#define NS_FileRead_findClose					FileRead_findClose

// �ݒ�֌W�֐�
#define NS_SetUseDXArchiveFlag					SetUseDXArchiveFlag
#define NS_GetStreamFunctionDefault				GetStreamFunctionDefault
#define NS_ChangeStreamFunction					ChangeStreamFunction













// DxInput.cpp�֐��v���g�^�C�v�錾

#ifndef DX_NON_INPUT

// ���͏�Ԏ擾�֐�
#define NS_CheckHitKey							CheckHitKey
#define NS_CheckHitKeyAll						CheckHitKeyAll
#define NS_GetHitKeyStateAll					GetHitKeyStateAll
#define NS_SetKeyExclusiveCooperativeLevelFlag	SetKeyExclusiveCooperativeLevelFlag
#define NS_GetJoypadNum							GetJoypadNum
#define NS_GetJoypadInputState					GetJoypadInputState
#define NS_GetJoypadAnalogInput					GetJoypadAnalogInput
#define NS_GetJoypadAnalogInputRight			GetJoypadAnalogInputRight
#define NS_GetJoypadDirectInputState			GetJoypadDirectInputState
#define NS_KeyboradBufferProcess				KeyboradBufferProcess
#define NS_GetJoypadGUID						GetJoypadGUID
#define NS_ConvertKeyCodeToVirtualKey			ConvertKeyCodeToVirtualKey
#define NS_ConvertVirtualKeyToKeyCode			ConvertVirtualKeyToKeyCode
#define NS_SetJoypadInputToKeyInput				SetJoypadInputToKeyInput
#define NS_SetJoypadDeadZone					SetJoypadDeadZone
#define NS_StartJoypadVibration					StartJoypadVibration
#define NS_StopJoypadVibration					StopJoypadVibration
#define NS_GetJoypadPOVState					GetJoypadPOVState
#define NS_GetJoypadName						GetJoypadName
#define NS_ReSetupJoypad						ReSetupJoypad

#define NS_SetKeyboardNotDirectInputFlag		SetKeyboardNotDirectInputFlag
#define NS_SetUseDirectInputFlag				SetUseDirectInputFlag
#define NS_SetUseJoypadVibrationFlag			SetUseJoypadVibrationFlag

#endif // DX_NON_INPUT













#ifndef DX_NOTUSE_DRAWFUNCTION

// �O���t�B�b�N�n���h���쐬�֌W�֐�
#define NS_MakeGraph							MakeGraph
#define NS_MakeScreen							MakeScreen
#define NS_DerivationGraph						DerivationGraph
#define NS_DeleteGraph							DeleteGraph
#define NS_DeleteSharingGraph					DeleteSharingGraph
#define NS_GetGraphNum							GetGraphNum
#define NS_FillGraph							FillGraph
#define NS_SetGraphLostFlag						SetGraphLostFlag
#define NS_InitGraph							InitGraph
#define NS_ReloadFileGraphAll					ReloadFileGraphAll

// �O���t�B�b�N�n���h���ւ̉摜�]���֐�
#define NS_BltBmpToGraph						BltBmpToGraph
#define NS_BltBmpToDivGraph						BltBmpToDivGraph
#define NS_BltBmpOrGraphImageToGraph			BltBmpOrGraphImageToGraph
#define NS_BltBmpOrGraphImageToGraph2			BltBmpOrGraphImageToGraph2
#define NS_BltBmpOrGraphImageToDivGraph			BltBmpOrGraphImageToDivGraph

// �摜����O���t�B�b�N�n���h�����쐬����֐�
#define NS_LoadBmpToGraph						LoadBmpToGraph
#define NS_LoadGraph							LoadGraph
#define NS_LoadReverseGraph						LoadReverseGraph
#define NS_LoadDivGraph							LoadDivGraph
#define NS_LoadDivBmpToGraph					LoadDivBmpToGraph
#define NS_LoadReverseDivGraph					LoadReverseDivGraph
#define NS_LoadBlendGraph						LoadBlendGraph
#ifdef __WINDOWS__
#define NS_LoadGraphToResource					LoadGraphToResource
#define NS_LoadDivGraphToResource				LoadDivGraphToResource
#define NS_LoadGraphToResource					LoadGraphToResource
#define NS_LoadDivGraphToResource				LoadDivGraphToResource
#endif // __WINDOWS__

#define NS_CreateGraphFromMem					CreateGraphFromMem
#define NS_ReCreateGraphFromMem					ReCreateGraphFromMem
#define NS_CreateDivGraphFromMem				CreateDivGraphFromMem
#define NS_ReCreateDivGraphFromMem				ReCreateDivGraphFromMem
#define NS_CreateGraphFromBmp					CreateGraphFromBmp
#define NS_ReCreateGraphFromBmp					ReCreateGraphFromBmp
#define NS_CreateDivGraphFromBmp				CreateDivGraphFromBmp
#define NS_ReCreateDivGraphFromBmp				ReCreateDivGraphFromBmp
#define NS_CreateDXGraph						CreateDXGraph
#define NS_CreateGraphFromGraphImage			CreateGraphFromGraphImage
#define NS_CreateGraphFromGraphImage			CreateGraphFromGraphImage
#define NS_ReCreateGraphFromGraphImage			ReCreateGraphFromGraphImage
#define NS_ReCreateGraphFromGraphImage			ReCreateGraphFromGraphImage
#define NS_CreateDivGraphFromGraphImage			CreateDivGraphFromGraphImage
#define NS_CreateDivGraphFromGraphImage			CreateDivGraphFromGraphImage
#define NS_ReCreateDivGraphFromGraphImage		ReCreateDivGraphFromGraphImage
#define NS_ReCreateDivGraphFromGraphImage		ReCreateDivGraphFromGraphImage
#define NS_CreateGraph							CreateGraph
#define NS_CreateDivGraph						CreateDivGraph
#define NS_ReCreateGraph						ReCreateGraph
#ifndef DX_NON_SOFTIMAGE
#define NS_CreateBlendGraphFromSoftImage		CreateBlendGraphFromSoftImage
#define NS_CreateGraphFromSoftImage				CreateGraphFromSoftImage
#define NS_CreateGraphFromRectSoftImage			CreateGraphFromRectSoftImage
#define NS_ReCreateGraphFromSoftImage			ReCreateGraphFromSoftImage
#define NS_ReCreateGraphFromRectSoftImage		ReCreateGraphFromRectSoftImage
#define NS_CreateDivGraphFromSoftImage			CreateDivGraphFromSoftImage
#endif // DX_NON_SOFTIMAGE
#define NS_CreateGraphFromBaseImage				CreateGraphFromBaseImage
#define NS_CreateGraphFromRectBaseImage			CreateGraphFromRectBaseImage
#define NS_ReCreateGraphFromBaseImage			ReCreateGraphFromBaseImage
#define NS_ReCreateGraphFromRectBaseImage		ReCreateGraphFromRectBaseImage
#define NS_CreateDivGraphFromBaseImage			CreateDivGraphFromBaseImage
#define NS_ReloadGraph							ReloadGraph
#define NS_ReloadDivGraph						ReloadDivGraph
#define NS_ReloadReverseGraph					ReloadReverseGraph
#define NS_ReloadReverseDivGraph				ReloadReverseDivGraph

// �O���t�B�b�N�n���h���쐬���ݒ�W�֐�
#define NS_SetGraphColorBitDepth				SetGraphColorBitDepth
#define NS_GetGraphColorBitDepth				GetGraphColorBitDepth
#define NS_SetCreateGraphColorBitDepth			SetCreateGraphColorBitDepth
#define NS_GetCreateGraphColorBitDepth			GetCreateGraphColorBitDepth
#define NS_SetCreateGraphChannelBitDepth		SetCreateGraphChannelBitDepth
#define NS_GetCreateGraphChannelBitDepth		GetCreateGraphChannelBitDepth
#define NS_SetDrawValidGraphCreateFlag			SetDrawValidGraphCreateFlag
#define NS_GetDrawValidGraphCreateFlag			GetDrawValidGraphCreateFlag
#define NS_SetDrawValidFlagOf3DGraph			SetDrawValidFlagOf3DGraph
#define NS_SetLeftUpColorIsTransColorFlag		SetLeftUpColorIsTransColorFlag
#define NS_SetUseSystemMemGraphCreateFlag		SetUseSystemMemGraphCreateFlag
#define NS_GetUseSystemMemGraphCreateFlag		GetUseSystemMemGraphCreateFlag
#define NS_SetUseBlendGraphCreateFlag			SetUseBlendGraphCreateFlag
#define NS_GetUseBlendGraphCreateFlag			GetUseBlendGraphCreateFlag
#define NS_SetUseAlphaTestGraphCreateFlag		SetUseAlphaTestGraphCreateFlag
#define NS_GetUseAlphaTestGraphCreateFlag		GetUseAlphaTestGraphCreateFlag
#define NS_SetUseAlphaTestFlag					SetUseAlphaTestFlag
#define NS_GetUseAlphaTestFlag					GetUseAlphaTestFlag
#define NS_SetUseNoBlendModeParam				SetUseNoBlendModeParam
#define NS_SetDrawValidAlphaChannelGraphCreateFlag		SetDrawValidAlphaChannelGraphCreateFlag
#define NS_GetDrawValidAlphaChannelGraphCreateFlag		GetDrawValidAlphaChannelGraphCreateFlag
#define NS_SetDrawValidFloatTypeGraphCreateFlag			SetDrawValidFloatTypeGraphCreateFlag
#define NS_GetDrawValidFloatTypeGraphCreateFlag			GetDrawValidFloatTypeGraphCreateFlag
#define NS_SetDrawValidGraphCreateZBufferFlag			SetDrawValidGraphCreateZBufferFlag
#define NS_GetDrawValidGraphCreateZBufferFlag			GetDrawValidGraphCreateZBufferFlag
#define NS_SetCreateDrawValidGraphChannelNum	SetCreateDrawValidGraphChannelNum
#define NS_GetCreateDrawValidGraphChannelNum	GetCreateDrawValidGraphChannelNum
#define NS_SetDrawValidMultiSample				SetDrawValidMultiSample
#define NS_GetMultiSampleQuality				GetMultiSampleQuality
#define NS_SetUseTransColor						SetUseTransColor
#define NS_SetUseTransColorGraphCreateFlag		SetUseTransColorGraphCreateFlag
#define NS_SetUseGraphAlphaChannel				SetUseGraphAlphaChannel
#define NS_GetUseGraphAlphaChannel				GetUseGraphAlphaChannel
#define NS_SetUseAlphaChannelGraphCreateFlag	SetUseAlphaChannelGraphCreateFlag
#define NS_GetUseAlphaChannelGraphCreateFlag	GetUseAlphaChannelGraphCreateFlag
#define NS_SetUseNotManageTextureFlag			SetUseNotManageTextureFlag
#define NS_GetUseNotManageTextureFlag			GetUseNotManageTextureFlag
#define NS_SetTransColor						SetTransColor
#define NS_GetTransColor						GetTransColor
#define NS_SetUseDivGraphFlag					SetUseDivGraphFlag
#define NS_SetUseMaxTextureSize					SetUseMaxTextureSize
#define NS_SetUseGraphBaseDataBackup			SetUseGraphBaseDataBackup
#define NS_GetUseGraphBaseDataBackup			GetUseGraphBaseDataBackup

// �摜���֌W�֐�
#define NS_GetFullColorImage					GetFullColorImage

#define NS_GraphLock							GraphLock
#define NS_GraphUnLock							GraphUnLock

#define NS_SetUseGraphZBuffer					SetUseGraphZBuffer
#define NS_CopyGraphZBufferImage				CopyGraphZBufferImage

#define NS_GetGraphSize							GetGraphSize
#define NS_GetGraphTextureSize					GetGraphTextureSize
#define NS_GetGraphMipmapCount					GetGraphMipmapCount
#define NS_GetGraphFilePath						GetGraphFilePath

#define NS_GetTexColorData						GetTexColorData
#define NS_GetTexColorData						GetTexColorData
#define NS_GetTexColorData						GetTexColorData
#define NS_GetMaxGraphTextureSize				GetMaxGraphTextureSize
#define NS_GetValidRestoreShredPoint			GetValidRestoreShredPoint
#define NS_GetCreateGraphColorData				GetCreateGraphColorData

// �p���b�g����֌W�֐�
#define NS_GetGraphPalette						GetGraphPalette
#define NS_GetGraphOriginalPalette				GetGraphOriginalPalette
#define NS_SetGraphPalette						SetGraphPalette
#define NS_ResetGraphPalette					ResetGraphPalette

// �}�`�`��֐�
#define NS_DrawLine										DrawLine
#define NS_DrawBox										DrawBox
#define NS_DrawFillBox									DrawFillBox
#define NS_DrawLineBox									DrawLineBox
#define NS_DrawCircle									DrawCircle
#define NS_DrawOval										DrawOval
#define NS_DrawTriangle									DrawTriangle
#define NS_DrawQuadrangle								DrawQuadrangle
#define NS_DrawPixel									DrawPixel

#define NS_Paint										Paint

#define NS_DrawPixelSet									DrawPixelSet
#define NS_DrawLineSet									DrawLineSet

#define NS_DrawPixel3D									DrawPixel3D
#define NS_DrawLine3D									DrawLine3D
#define NS_DrawTriangle3D								DrawTriangle3D
#define NS_DrawCube3D									DrawCube3D
#define NS_DrawSphere3D									DrawSphere3D
#define NS_DrawCapsule3D								DrawCapsule3D
#define NS_DrawCone3D									DrawCone3D

// �摜�`��֐�
#define NS_LoadGraphScreen								LoadGraphScreen

#define NS_DrawGraph									DrawGraph
#define NS_DrawExtendGraph								DrawExtendGraph
#define NS_DrawRotaGraph								DrawRotaGraph
#define NS_DrawRotaGraph2								DrawRotaGraph2
#define NS_DrawRotaGraph3								DrawRotaGraph3
#define NS_DrawModiGraph								DrawModiGraph
#define NS_DrawTurnGraph								DrawTurnGraph

#define NS_DrawGraphF									DrawGraphF
#define NS_DrawExtendGraphF								DrawExtendGraphF
#define NS_DrawRotaGraphF								DrawRotaGraphF
#define NS_DrawRotaGraph2F								DrawRotaGraph2F
#define NS_DrawRotaGraph3F								DrawRotaGraph3F
#define NS_DrawModiGraphF								DrawModiGraphF
#define NS_DrawTurnGraphF								DrawTurnGraphF

#define NS_DrawChipMap									DrawChipMap
#define NS_DrawChipMap									DrawChipMap
#define NS_DrawTile										DrawTile

#define NS_DrawRectGraph								DrawRectGraph
#define NS_DrawRectExtendGraph							DrawRectExtendGraph
#define NS_DrawRectRotaGraph							DrawRectRotaGraph
#define NS_DrawRectRotaGraph2							DrawRectRotaGraph2
#define NS_DrawRectRotaGraph3							DrawRectRotaGraph3

#define NS_DrawRectGraphF								DrawRectGraphF
#define NS_DrawRectExtendGraphF							DrawRectExtendGraphF
#define NS_DrawRectRotaGraphF							DrawRectRotaGraphF
#define NS_DrawRectRotaGraph2F							DrawRectRotaGraph2F
#define NS_DrawRectRotaGraph3F							DrawRectRotaGraph3F

#define NS_DrawBlendGraph								DrawBlendGraph
#define NS_DrawBlendGraphPos							DrawBlendGraphPos

#define NS_DrawCircleGauge								DrawCircleGauge

#define NS_DrawGraphToZBuffer							DrawGraphToZBuffer
#define NS_DrawTurnGraphToZBuffer						DrawTurnGraphToZBuffer
#define NS_DrawExtendGraphToZBuffer						DrawExtendGraphToZBuffer
#define NS_DrawRotaGraphToZBuffer						DrawRotaGraphToZBuffer
#define NS_DrawRotaGraph2ToZBuffer						DrawRotaGraph2ToZBuffer
#define NS_DrawRotaGraph3ToZBuffer						DrawRotaGraph3ToZBuffer
#define NS_DrawModiGraphToZBuffer						DrawModiGraphToZBuffer
#define NS_DrawBoxToZBuffer								DrawBoxToZBuffer
#define NS_DrawCircleToZBuffer							DrawCircleToZBuffer

#define NS_DrawPolygon									DrawPolygon
#define NS_DrawPolygon2D								DrawPolygon2D
#define NS_DrawPolygon3D								DrawPolygon3D
#define NS_DrawPolygonIndexed2D							DrawPolygonIndexed2D
#define NS_DrawPolygonIndexed3D							DrawPolygonIndexed3D
#define NS_DrawPolygonIndexed3DBase						DrawPolygonIndexed3DBase
#define NS_DrawPolygon3DBase							DrawPolygon3DBase
#define NS_DrawPolygon3D								DrawPolygon3D

#define NS_DrawPolygonBase								DrawPolygonBase
#define NS_DrawPrimitive2D								DrawPrimitive2D
#define NS_DrawPrimitive3D								DrawPrimitive3D
#define NS_DrawPrimitiveIndexed2D						DrawPrimitiveIndexed2D
#define NS_DrawPrimitiveIndexed3D						DrawPrimitiveIndexed3D

#define NS_DrawPolygon3D_UseVertexBuffer				DrawPolygon3D_UseVertexBuffer
#define NS_DrawPrimitive3D_UseVertexBuffer				DrawPrimitive3D_UseVertexBuffer
#define NS_DrawPrimitive3D_UseVertexBuffer2				DrawPrimitive3D_UseVertexBuffer2
#define NS_DrawPolygonIndexed3D_UseVertexBuffer			DrawPolygonIndexed3D_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3D_UseVertexBuffer		DrawPrimitiveIndexed3D_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3D_UseVertexBuffer2		DrawPrimitiveIndexed3D_UseVertexBuffer2

#define NS_DrawGraph3D									DrawGraph3D
#define NS_DrawExtendGraph3D							DrawExtendGraph3D
#define NS_DrawRotaGraph3D								DrawRotaGraph3D
#define NS_DrawRota2Graph3D								DrawRota2Graph3D
#define NS_DrawModiBillboard3D							DrawModiBillboard3D
#define NS_DrawBillboard3D								DrawBillboard3D

// �`��ݒ�֌W�֐�
#define NS_SetDrawMode							SetDrawMode
#define NS_GetDrawMode							GetDrawMode
#define NS_SetDrawBlendMode						SetDrawBlendMode
#define NS_GetDrawBlendMode						GetDrawBlendMode
#define NS_SetDrawAlphaTest						SetDrawAlphaTest
#define NS_SetBlendGraph						SetBlendGraph
#define NS_SetBlendGraphParam					SetBlendGraphParam
#define NS_SetBlendGraphPosition				SetBlendGraphPosition
#define NS_SetDrawBright						SetDrawBright
// ######## 06/17 ########
#define NS_SetDrawBright2						SetDrawBright2
#define NS_GetDrawBright						GetDrawBright
#define NS_SetIgnoreDrawGraphColor				SetIgnoreDrawGraphColor
#define NS_SetMaxAnisotropy						SetMaxAnisotropy

#define NS_SetUseZBufferFlag					SetUseZBufferFlag
#define NS_SetWriteZBufferFlag					SetWriteZBufferFlag
#define NS_SetZBufferCmpType					SetZBufferCmpType
#define NS_SetZBias								SetZBias
#define NS_SetUseZBuffer3D						SetUseZBuffer3D
#define NS_SetWriteZBuffer3D					SetWriteZBuffer3D
#define NS_SetZBufferCmpType3D					SetZBufferCmpType3D
#define NS_SetZBias3D							SetZBias3D
#define NS_SetDrawZ								SetDrawZ

#define NS_SetDrawArea							SetDrawArea
#define NS_GetDrawArea							GetDrawArea
#define NS_SetDraw3DScale						SetDraw3DScale
#define NS_SetDrawAreaFull						SetDrawAreaFull

#define NS_SetRestoreShredPoint					SetRestoreShredPoint
#define NS_SetRestoreGraphCallback				SetRestoreGraphCallback
#define NS_RunRestoreShred						RunRestoreShred
#define NS_SetGraphicsDeviceRestoreCallbackFunction		SetGraphicsDeviceRestoreCallbackFunction
#define NS_SetGraphicsDeviceLostCallbackFunction		SetGraphicsDeviceLostCallbackFunction

#define NS_SetTransformToWorld					SetTransformToWorld
#define NS_GetTransformToWorldMatrix			GetTransformToWorldMatrix
#define NS_SetTransformToView					SetTransformToView
#define NS_GetTransformToViewMatrix				GetTransformToViewMatrix
#define NS_SetTransformToProjection				SetTransformToProjection
#define NS_GetTransformToProjectionMatrix		GetTransformToProjectionMatrix
#define NS_SetTransformToViewport				SetTransformToViewport
#define NS_GetTransformToViewportMatrix			GetTransformToViewportMatrix
#define NS_GetTransformToAPIViewportMatrix		GetTransformToAPIViewportMatrix
#define NS_SetDefTransformMatrix				SetDefTransformMatrix
#define NS_GetTransformPosition					GetTransformPosition
#define NS_GetBillboardPixelSize				GetBillboardPixelSize
#define	NS_ConvWorldPosToViewPos				ConvWorldPosToViewPos
#define NS_ConvWorldPosToScreenPos				ConvWorldPosToScreenPos
#define NS_ConvWorldPosToScreenPosPlusW			ConvWorldPosToScreenPosPlusW
#define NS_ConvScreenPosToWorldPos				ConvScreenPosToWorldPos
#define NS_ConvScreenPosToWorldPos_ZLinear		ConvScreenPosToWorldPos_ZLinear

#define NS_SetUseCullingFlag					SetUseCullingFlag
#define NS_SetUseBackCulling					SetUseBackCulling

#define NS_SetTextureAddressMode				SetTextureAddressMode
#define NS_SetTextureAddressModeUV				SetTextureAddressModeUV
#define NS_SetTextureAddressTransform			SetTextureAddressTransform
#define NS_SetTextureAddressTransformMatrix		SetTextureAddressTransformMatrix
#define NS_ResetTextureAddressTransform			ResetTextureAddressTransform

#define NS_SetFogEnable							SetFogEnable
#define NS_SetFogMode							SetFogMode
#define NS_SetFogColor							SetFogColor
#define NS_SetFogStartEnd						SetFogStartEnd
#define NS_SetFogDensity						SetFogDensity

// ��ʊ֌W�֐�
#define NS_GetPixel								GetPixel
#define NS_GetDrawScreenGraph					GetDrawScreenGraph
#define NS_BltDrawValidGraph					BltDrawValidGraph
#define NS_ScreenFlip							ScreenFlip
#define NS_ScreenCopy							ScreenCopy
#define NS_WaitVSync							WaitVSync
#define NS_ClearDrawScreen						ClearDrawScreen
#define NS_ClearDrawScreenZBuffer				ClearDrawScreenZBuffer
#define NS_ClsDrawScreen						ClsDrawScreen
#define NS_SetDrawScreen						SetDrawScreen
#define NS_GetDrawScreen						GetDrawScreen
#define NS_GetActiveGraph						GetActiveGraph
#define NS_SetDrawZBuffer						SetDrawZBuffer
#ifdef __WINDOWS__
#define NS_BltBackScreenToWindow				BltBackScreenToWindow
#define NS_BltRectBackScreenToWindow			BltRectBackScreenToWindow
#endif // __WINDOWS__
#define NS_SetGraphMode							SetGraphMode
#define NS_SetEmulation320x240					SetEmulation320x240
#define NS_SetZBufferSize						SetZBufferSize
#define NS_SetWaitVSyncFlag						SetWaitVSyncFlag
#define NS_GetWaitVSyncFlag						GetWaitVSyncFlag
#define NS_SetFullSceneAntiAliasingMode			SetFullSceneAntiAliasingMode
#define NS_SetGraphDisplayArea					SetGraphDisplayArea
#define NS_SetChangeScreenModeGraphicsSystemResetFlag	SetChangeScreenModeGraphicsSystemResetFlag
#define NS_GetScreenState						GetScreenState
#define NS_GetDrawScreenSize					GetDrawScreenSize
#define NS_GetScreenBitDepth					GetScreenBitDepth
#define NS_GetColorBitDepth						GetColorBitDepth
#define NS_GetChangeDisplayFlag					GetChangeDisplayFlag
#define NS_GetVideoMemorySize					GetVideoMemorySize
#define NS_GetRefreshRate						GetRefreshRate
#define NS_GetDisplayModeNum					GetDisplayModeNum
#define NS_GetDisplayMode						GetDisplayMode
#define NS_GetDispColorData						GetDispColorData
#define NS_SetDisplayRefreshRate				SetDisplayRefreshRate
#define NS_GetMultiDrawScreenNum				GetMultiDrawScreenNum

// ���̑��ݒ�֌W�֐�
#define NS_SetUseNormalDrawShader				SetUseNormalDrawShader
#define NS_SetUseSoftwareRenderModeFlag			SetUseSoftwareRenderModeFlag
#define NS_SetNotUse3DFlag						SetNotUse3DFlag
#define NS_SetUse3DFlag							SetUse3DFlag
#define NS_GetUse3DFlag							GetUse3DFlag
#define NS_SetScreenMemToVramFlag				SetScreenMemToVramFlag
#define NS_GetScreenMemToSystemMemFlag			GetScreenMemToSystemMemFlag

#define NS_SetUseBasicGraphDraw3DDeviceMethodFlag	SetUseBasicGraphDraw3DDeviceMethodFlag
#define NS_SetWindowDrawRect					SetWindowDrawRect
#define NS_RestoreGraphSystem					RestoreGraphSystem
#define NS_SetAeroDisableFlag					SetAeroDisableFlag
#define NS_SetUseDirect3D9Ex					SetUseDirect3D9Ex
#define NS_SetUseHardwareVertexProcessing		SetUseHardwareVertexProcessing
#define NS_SetMultiThreadFlag					SetMultiThreadFlag
#define NS_SetUseDirectDrawDeviceIndex			SetUseDirectDrawDeviceIndex
#define NS_SetUseOldDrawModiGraphCodeFlag		SetUseOldDrawModiGraphCodeFlag
#define NS_SetUseVramFlag						SetUseVramFlag
#define NS_GetUseVramFlag						GetUseVramFlag
#define NS_SetBasicBlendFlag					SetBasicBlendFlag
#ifdef __WINDOWS__
#define NS_SetUseDirectDrawFlag					SetUseDirectDrawFlag
#define NS_SetUseGDIFlag						SetUseGDIFlag
#define NS_SetDDrawUseGuid						SetDDrawUseGuid
#define NS_GetUseDDrawObj						GetUseDDrawObj
#define NS_GetDirectDrawDeviceGUID				GetDirectDrawDeviceGUID
#define NS_GetDirectDrawDeviceDescription		GetDirectDrawDeviceDescription
#define NS_GetDirectDrawDeviceNum				GetDirectDrawDeviceNum
#define NS_GetUseGDIFlag						GetUseGDIFlag
#define NS_GetUseDirect3DDevice9				GetUseDirect3DDevice9
#define NS_GetUseDirect3D9BackBufferSurface		GetUseDirect3D9BackBufferSurface
#endif // __WINDOWS__
#define NS_RefreshDxLibDirect3DSetting			RefreshDxLibDirect3DSetting
#define NS_RenderVertex							RenderVertex

#ifndef DX_NON_SAVEFUNCTION

// ��ʉ摜�ۑ��֐�
// Jpeg_Quality         = 0:��掿�`100:���掿
// Png_CompressionLevel = 0:�����k�`  9:�ō����k
#define NS_SaveDrawScreen						SaveDrawScreen
#define NS_SaveDrawScreenToBMP					SaveDrawScreenToBMP
#define NS_SaveDrawScreenToJPEG					SaveDrawScreenToJPEG
#define NS_SaveDrawScreenToPNG					SaveDrawScreenToPNG

#endif // DX_NON_SAVEFUNCTION

// ���_�o�b�t�@�֌W�֐�
#define NS_CreateVertexBuffer					CreateVertexBuffer
#define NS_DeleteVertexBuffer					DeleteVertexBuffer
#define NS_InitVertexBuffer						InitVertexBuffer
#define NS_SetVertexBufferData					SetVertexBufferData
#define NS_CreateIndexBuffer					CreateIndexBuffer
#define NS_DeleteIndexBuffer					DeleteIndexBuffer
#define NS_InitIndexBuffer						InitIndexBuffer
#define NS_SetIndexBufferData					SetIndexBufferData

// �V�F�[�_�[�֌W�֐�
#define NS_GetValidShaderVersion				GetValidShaderVersion

#define NS_LoadVertexShader						LoadVertexShader
#define NS_LoadPixelShader						LoadPixelShader
#define NS_LoadVertexShaderFromMem				LoadVertexShaderFromMem
#define NS_LoadPixelShaderFromMem				LoadPixelShaderFromMem
#define NS_DeleteShader							DeleteShader
#define NS_InitShader							InitShader

#define NS_GetConstIndexToShader				GetConstIndexToShader
#define NS_GetConstCountToShader				GetConstCountToShader
#define NS_GetConstDefaultParamFToShader		GetConstDefaultParamFToShader
#define NS_SetVSConstSF							SetVSConstSF
#define NS_SetVSConstF							SetVSConstF
#define NS_SetVSConstFMtx						SetVSConstFMtx
#define NS_SetVSConstFMtxT						SetVSConstFMtxT
#define NS_SetVSConstSI							SetVSConstSI
#define NS_SetVSConstI							SetVSConstI
#define NS_SetVSConstB							SetVSConstB
#define NS_SetVSConstSFArray					SetVSConstSFArray
#define NS_SetVSConstFArray						SetVSConstFArray
#define NS_SetVSConstFMtxArray					SetVSConstFMtxArray
#define NS_SetVSConstFMtxTArray					SetVSConstFMtxTArray
#define NS_SetVSConstSIArray					SetVSConstSIArray
#define NS_SetVSConstIArray						SetVSConstIArray
#define NS_SetVSConstBArray						SetVSConstBArray
#define NS_ResetVSConstF						ResetVSConstF
#define NS_ResetVSConstI						ResetVSConstI
#define NS_ResetVSConstB						ResetVSConstB

#define NS_SetPSConstSF							SetPSConstSF
#define NS_SetPSConstF							SetPSConstF
#define NS_SetPSConstFMtx						SetPSConstFMtx
#define NS_SetPSConstFMtxT						SetPSConstFMtxT
#define NS_SetPSConstSI							SetPSConstSI
#define NS_SetPSConstI							SetPSConstI
#define NS_SetPSConstB							SetPSConstB
#define NS_SetPSConstSFArray					SetPSConstSFArray
#define NS_SetPSConstFArray						SetPSConstFArray
#define NS_SetPSConstFMtxArray					SetPSConstFMtxArray
#define NS_SetPSConstFMtxTArray					SetPSConstFMtxTArray
#define NS_SetPSConstSIArray					SetPSConstSIArray
#define NS_SetPSConstIArray						SetPSConstIArray
#define NS_SetPSConstBArray						SetPSConstBArray
#define NS_ResetPSConstF						ResetPSConstF
#define NS_ResetPSConstI						ResetPSConstI
#define NS_ResetPSConstB						ResetPSConstB

#define NS_SetRenderTargetToShader				SetRenderTargetToShader
#define NS_SetUseTextureToShader				SetUseTextureToShader
#define NS_SetUseVertexShader					SetUseVertexShader
#define NS_SetUsePixelShader					SetUsePixelShader

#define NS_CalcPolygonBinormalAndTangentsToShader				CalcPolygonBinormalAndTangentsToShader
#define NS_CalcPolygonIndexedBinormalAndTangentsToShader		CalcPolygonIndexedBinormalAndTangentsToShader

#define NS_DrawPolygon2DToShader								DrawPolygon2DToShader
#define NS_DrawPolygon3DToShader								DrawPolygon3DToShader
#define NS_DrawPolygonIndexed2DToShader							DrawPolygonIndexed2DToShader
#define NS_DrawPolygonIndexed3DToShader							DrawPolygonIndexed3DToShader
#define NS_DrawPrimitive2DToShader								DrawPrimitive2DToShader
#define NS_DrawPrimitive3DToShader								DrawPrimitive3DToShader
#define NS_DrawPrimitiveIndexed2DToShader						DrawPrimitiveIndexed2DToShader
#define NS_DrawPrimitiveIndexed3DToShader						DrawPrimitiveIndexed3DToShader
#define NS_DrawPolygon3DToShader_UseVertexBuffer				DrawPolygon3DToShader_UseVertexBuffer
#define NS_DrawPolygonIndexed3DToShader_UseVertexBuffer			DrawPolygonIndexed3DToShader_UseVertexBuffer
#define NS_DrawPrimitive3DToShader_UseVertexBuffer				DrawPrimitive3DToShader_UseVertexBuffer
#define NS_DrawPrimitive3DToShader_UseVertexBuffer2				DrawPrimitive3DToShader_UseVertexBuffer2
#define NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer		DrawPrimitiveIndexed3DToShader_UseVertexBuffer
#define NS_DrawPrimitiveIndexed3DToShader_UseVertexBuffer2		DrawPrimitiveIndexed3DToShader_UseVertexBuffer2

// �t�B���^�[�֌W�֐�
#ifndef DX_NON_FILTER

#define NS_GraphFilter							GraphFilter
#define NS_GraphFilterBlt						GraphFilterBlt
#define NS_GraphFilterRectBlt					GraphFilterRectBlt
#define NS_GraphBlend							GraphBlend
#define NS_GraphBlendBlt						GraphBlendBlt
#define NS_GraphBlendRectBlt					GraphBlendRectBlt

#endif // DX_NON_FILTER


#ifndef DX_NON_MOVIE

// ���[�r�[�O���t�B�b�N�֌W�֐�
#define NS_PlayMovie							PlayMovie
#define NS_OpenMovieToGraph						OpenMovieToGraph
#define NS_PlayMovieToGraph						PlayMovieToGraph
#define NS_PauseMovieToGraph					PauseMovieToGraph
#define NS_AddMovieFrameToGraph					AddMovieFrameToGraph
#define NS_SeekMovieToGraph						SeekMovieToGraph
#define NS_GetMovieStateToGraph					GetMovieStateToGraph
#define NS_SetMovieVolumeToGraph				SetMovieVolumeToGraph
#define NS_ChangeMovieVolumeToGraph				ChangeMovieVolumeToGraph
#define NS_GetMovieBaseImageToGraph				GetMovieBaseImageToGraph
#define NS_GetMovieTotalFrameToGraph			GetMovieTotalFrameToGraph
#define NS_TellMovieToGraph						TellMovieToGraph
#define NS_TellMovieToGraphToFrame				TellMovieToGraphToFrame
#define NS_SeekMovieToGraphToFrame				SeekMovieToGraphToFrame
#define NS_GetOneFrameTimeMovieToGraph			GetOneFrameTimeMovieToGraph
#define NS_GetLastUpdateTimeMovieToGraph		GetLastUpdateTimeMovieToGraph
#define NS_SetMovieRightImageAlphaFlag			SetMovieRightImageAlphaFlag

#endif

// �J�����֌W�֐�
#define NS_SetCameraNearFar						SetCameraNearFar
#define NS_SetCameraPositionAndTarget_UpVecY	SetCameraPositionAndTarget_UpVecY
#define NS_SetCameraPositionAndTargetAndUpVec	SetCameraPositionAndTargetAndUpVec
#define NS_SetCameraPositionAndAngle			SetCameraPositionAndAngle
#define NS_SetCameraViewMatrix					SetCameraViewMatrix
#define NS_SetCameraScreenCenter				SetCameraScreenCenter

#define NS_SetupCamera_Perspective				SetupCamera_Perspective
#define NS_SetupCamera_Ortho					SetupCamera_Ortho
#define NS_SetupCamera_ProjectionMatrix			SetupCamera_ProjectionMatrix
#define NS_SetCameraDotAspect					SetCameraDotAspect

#define NS_CheckCameraViewClip					CheckCameraViewClip
#define NS_CheckCameraViewClip_Dir				CheckCameraViewClip_Dir
#define NS_CheckCameraViewClip_Box				CheckCameraViewClip_Box

#define NS_GetCameraNear						GetCameraNear
#define NS_GetCameraFar							GetCameraFar

#define NS_GetCameraPosition					GetCameraPosition
#define NS_GetCameraTarget						GetCameraTarget
#define NS_GetCameraUpVector					GetCameraUpVector
#define NS_GetCameraAngleHRotate				GetCameraAngleHRotate
#define NS_GetCameraAngleVRotate				GetCameraAngleVRotate
#define NS_GetCameraAngleTRotate				GetCameraAngleTRotate

#define NS_GetCameraViewMatrix					GetCameraViewMatrix
#define NS_GetCameraBillboardMatrix				GetCameraBillboardMatrix
#define NS_GetCameraFov							GetCameraFov
#define NS_GetCameraSize						GetCameraSize
#define NS_GetCameraProjectionMatrix			GetCameraProjectionMatrix
#define NS_GetCameraDotAspect					GetCameraDotAspect
#define NS_GetCameraViewportMatrix				GetCameraViewportMatrix
#define NS_GetCameraAPIViewportMatrix			GetCameraAPIViewportMatrix

// ���C�g�֌W�֐�
#define NS_SetUseLighting						SetUseLighting
#define NS_SetMaterialUseVertDifColor			SetMaterialUseVertDifColor
#define NS_SetMaterialUseVertSpcColor			SetMaterialUseVertSpcColor
#define NS_SetMaterialParam						SetMaterialParam
#define NS_SetUseSpecular						SetUseSpecular
#define NS_SetGlobalAmbientLight				SetGlobalAmbientLight

#define NS_ChangeLightTypeDir					ChangeLightTypeDir
#define NS_ChangeLightTypeSpot					ChangeLightTypeSpot
#define NS_ChangeLightTypePoint					ChangeLightTypePoint
#define NS_SetLightEnable						SetLightEnable
#define NS_SetLightDifColor						SetLightDifColor
#define NS_SetLightSpcColor						SetLightSpcColor
#define NS_SetLightAmbColor						SetLightAmbColor
#define NS_SetLightDirection					SetLightDirection
#define NS_SetLightPosition						SetLightPosition
#define NS_SetLightRangeAtten					SetLightRangeAtten
#define NS_SetLightAngle						SetLightAngle
#define NS_GetLightType							GetLightType
#define NS_GetLightEnable						GetLightEnable
#define NS_GetLightDifColor						GetLightDifColor
#define NS_GetLightSpcColor						GetLightSpcColor
#define NS_GetLightAmbColor						GetLightAmbColor
#define NS_GetLightDirection					GetLightDirection
#define NS_GetLightPosition						GetLightPosition
#define NS_GetLightRangeAtten					GetLightRangeAtten
#define NS_GetLightAngle						GetLightAngle

#define NS_CreateDirLightHandle					CreateDirLightHandle
#define NS_CreateSpotLightHandle				CreateSpotLightHandle
#define NS_CreatePointLightHandle				CreatePointLightHandle
#define NS_DeleteLightHandle					DeleteLightHandle
#define NS_DeleteLightHandleAll					DeleteLightHandleAll
#define NS_SetLightTypeHandle					SetLightTypeHandle
#define NS_SetLightEnableHandle					SetLightEnableHandle
#define NS_SetLightDifColorHandle				SetLightDifColorHandle
#define NS_SetLightSpcColorHandle				SetLightSpcColorHandle
#define NS_SetLightAmbColorHandle				SetLightAmbColorHandle
#define NS_SetLightDirectionHandle				SetLightDirectionHandle
#define NS_SetLightPositionHandle				SetLightPositionHandle
#define NS_SetLightRangeAttenHandle				SetLightRangeAttenHandle
#define NS_SetLightAngleHandle					SetLightAngleHandle
#define NS_GetLightTypeHandle					GetLightTypeHandle
#define NS_GetLightEnableHandle					GetLightEnableHandle
#define NS_GetLightDifColorHandle				GetLightDifColorHandle
#define NS_GetLightSpcColorHandle				GetLightSpcColorHandle
#define NS_GetLightAmbColorHandle				GetLightAmbColorHandle
#define NS_GetLightDirectionHandle				GetLightDirectionHandle
#define NS_GetLightPositionHandle				GetLightPositionHandle
#define NS_GetLightRangeAttenHandle				GetLightRangeAttenHandle
#define NS_GetLightAngleHandle					GetLightAngleHandle

#define NS_GetEnableLightHandleNum				GetEnableLightHandleNum
#define NS_GetEnableLightHandle					GetEnableLightHandle

// �F���擾�p�֐�
#define NS_GetTexFormatIndex					GetTexFormatIndex
#define NS_ColorKaiseki							ColorKaiseki
#ifdef __WINDOWS__
#define NS_CreatePixelFormat					CreatePixelFormat
#endif // __WINDOWS__


















// DxMask.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_MASK

// �}�X�N�֌W 
#define NS_CreateMaskScreen						CreateMaskScreen
#define NS_DeleteMaskScreen						DeleteMaskScreen
#define NS_DrawMaskToDirectData					DrawMaskToDirectData
#define NS_DrawFillMaskToDirectData				DrawFillMaskToDirectData

#define NS_SetUseMaskScreenFlag					SetUseMaskScreenFlag
#define NS_GetUseMaskScreenFlag					GetUseMaskScreenFlag
#define NS_FillMaskScreen						FillMaskScreen

#define NS_InitMask								InitMask
#define NS_MakeMask								MakeMask
#define NS_GetMaskSize							GetMaskSize
#define NS_SetDataToMask						SetDataToMask
#define NS_DeleteMask							DeleteMask
#define NS_BmpBltToMask							BmpBltToMask
#define NS_LoadMask								LoadMask
#define NS_LoadDivMask							LoadDivMask
#define NS_DrawMask								DrawMask
#ifndef DX_NON_FONT
#define NS_DrawFormatStringMask					DrawFormatStringMask
#define NS_DrawFormatStringMaskToHandle			DrawFormatStringMaskToHandle
#define NS_DrawStringMask						DrawStringMask
#define NS_DrawStringMaskToHandle				DrawStringMaskToHandle
#endif // DX_NON_FONT
#define NS_DrawFillMask							DrawFillMask
#define NS_SetMaskReverseEffectFlag				SetMaskReverseEffectFlag

#define NS_GetMaskScreenData					GetMaskScreenData
#define NS_GetMaskUseFlag						GetMaskUseFlag

#endif // DX_NON_MASK












// DxFont.cpp �֐��v���g�^�C�v�錾

#ifndef DX_NON_FONT

// �t�H���g�A������`��֌W�֐�
#define NS_EnumFontName								EnumFontName
#define NS_EnumFontNameEx							EnumFontNameEx
#define NS_EnumFontNameEx2							EnumFontNameEx2
#define NS_InitFontToHandle							InitFontToHandle

#define NS_CreateFontToHandle						CreateFontToHandle
#define NS_SetFontSpaceToHandle						SetFontSpaceToHandle
#define NS_SetDefaultFontState						SetDefaultFontState
#define NS_DeleteFontToHandle						DeleteFontToHandle
#define NS_SetFontLostFlag							SetFontLostFlag

#define NS_SetFontSize								SetFontSize
#define NS_SetFontThickness							SetFontThickness
#define NS_SetFontSpace								SetFontSpace

#define NS_SetFontCacheToTextureFlag				SetFontCacheToTextureFlag
#define NS_SetFontChacheToTextureFlag				SetFontChacheToTextureFlag
#define NS_SetFontCacheCharNum						SetFontCacheCharNum
#define NS_ChangeFont								ChangeFont
#define NS_ChangeFontType							ChangeFontType

#define NS_FontCacheStringDrawToHandle				FontCacheStringDrawToHandle
#define NS_FontBaseImageBlt							FontBaseImageBlt
#define NS_FontBaseImageBltToHandle					FontBaseImageBltToHandle

#define NS_GetFontMaxWidth							GetFontMaxWidth
#define NS_GetFontMaxWidthToHandle					GetFontMaxWidthToHandle
#define NS_GetFontCharInfo							GetFontCharInfo
#define NS_GetDrawStringWidth						GetDrawStringWidth
#define NS_GetDrawFormatStringWidth					GetDrawFormatStringWidth
#define NS_GetDrawStringWidthToHandle				GetDrawStringWidthToHandle
#define NS_GetDrawFormatStringWidthToHandle			GetDrawFormatStringWidthToHandle
#define NS_GetDrawExtendStringWidth					GetDrawExtendStringWidth
#define NS_GetDrawExtendFormatStringWidth			GetDrawExtendFormatStringWidth
#define NS_GetDrawExtendStringWidthToHandle			GetDrawExtendStringWidthToHandle
#define NS_GetDrawExtendFormatStringWidthToHandle	GetDrawExtendFormatStringWidthToHandle

#define NS_GetFontStateToHandle						GetFontStateToHandle
#define NS_GetDefaultFontHandle						GetDefaultFontHandle
#define NS_GetFontChacheToTextureFlag				GetFontChacheToTextureFlag
#define NS_SetFontCacheTextureColorBitDepth			SetFontCacheTextureColorBitDepth
#define NS_GetFontCacheTextureColorBitDepth			GetFontCacheTextureColorBitDepth
#define NS_GetFontCacheToTextureFlag				GetFontCacheToTextureFlag
#define NS_CheckFontChacheToTextureFlag				CheckFontChacheToTextureFlag
#define NS_CheckFontCacheToTextureFlag				CheckFontCacheToTextureFlag
#define NS_CheckFontHandleValid						CheckFontHandleValid
#define NS_MultiByteCharCheck						MultiByteCharCheck
#define NS_GetFontCacheCharNum						GetFontCacheCharNum
#define NS_GetFontSize								GetFontSize
#define NS_GetFontSizeToHandle						GetFontSizeToHandle

// ������`��֐�
#define NS_DrawString								DrawString
#define NS_DrawVString								DrawVString
#define NS_DrawStringToHandle						DrawStringToHandle
#define NS_DrawVStringToHandle						DrawVStringToHandle
#define NS_DrawFormatString							DrawFormatString
#define NS_DrawFormatVString						DrawFormatVString
#define NS_DrawFormatStringToHandle					DrawFormatStringToHandle
#define NS_DrawFormatVStringToHandle				DrawFormatVStringToHandle
#define NS_DrawExtendString							DrawExtendString
#define NS_DrawExtendVString						DrawExtendVString
#define NS_DrawExtendStringToHandle					DrawExtendStringToHandle
#define NS_DrawExtendVStringToHandle				DrawExtendVStringToHandle
#define NS_DrawExtendFormatString					DrawExtendFormatString
#define NS_DrawExtendFormatVString					DrawExtendFormatVString
#define NS_DrawExtendFormatStringToHandle			DrawExtendFormatStringToHandle
#define NS_DrawExtendFormatVStringToHandle			DrawExtendFormatVStringToHandle

#define NS_DrawNumberToI							DrawNumberToI
#define NS_DrawNumberToF							DrawNumberToF
#define NS_DrawNumberPlusToI						DrawNumberPlusToI
#define NS_DrawNumberPlusToF						DrawNumberPlusToF

#define NS_DrawNumberToIToHandle					DrawNumberToIToHandle
#define NS_DrawNumberToFToHandle					DrawNumberToFToHandle
#define NS_DrawNumberPlusToIToHandle				DrawNumberPlusToIToHandle
#define NS_DrawNumberPlusToFToHandle				DrawNumberPlusToFToHandle

#define NS_DrawStringToZBuffer						DrawStringToZBuffer
#define NS_DrawVStringToZBuffer						DrawVStringToZBuffer
#define NS_DrawStringToHandleToZBuffer				DrawStringToHandleToZBuffer
#define NS_DrawVStringToHandleToZBuffer				DrawVStringToHandleToZBuffer
#define NS_DrawFormatStringToZBuffer				DrawFormatStringToZBuffer
#define NS_DrawFormatVStringToZBuffer				DrawFormatVStringToZBuffer
#define NS_DrawFormatStringToHandleToZBuffer		DrawFormatStringToHandleToZBuffer
#define NS_DrawFormatVStringToHandleToZBuffer		DrawFormatVStringToHandleToZBuffer
#define NS_DrawExtendStringToZBuffer				DrawExtendStringToZBuffer
#define NS_DrawExtendVStringToZBuffer				DrawExtendVStringToZBuffer
#define NS_DrawExtendStringToHandleToZBuffer		DrawExtendStringToHandleToZBuffer
#define NS_DrawExtendVStringToHandleToZBuffer		DrawExtendVStringToHandleToZBuffer
#define NS_DrawExtendFormatStringToZBuffer			DrawExtendFormatStringToZBuffer
#define NS_DrawExtendFormatVStringToZBuffer			DrawExtendFormatVStringToZBuffer
#define NS_DrawExtendFormatStringToHandleToZBuffer	DrawExtendFormatStringToHandleToZBuffer
#define NS_DrawExtendFormatVStringToHandleToZBuffer	DrawExtendFormatVStringToHandleToZBuffer

#endif // DX_NON_FONT










// DxMath.cpp �֐��v���g�^�C�v�錾

// ���Z���C�u����









// DxBaseImage.cpp �֐��v���g�^�C�v�錾

// ��{�C���[�W�f�[�^�̃��[�h�{�c�h�a�֌W
#define NS_CreateGraphImageOrDIBGraph			CreateGraphImageOrDIBGraph
#define NS_CreateGraphImageType2				CreateGraphImageType2
#define NS_CreateBmpInfo						CreateBmpInfo
#define NS_GetGraphImageFullColorCode			GetGraphImageFullColorCode
#define NS_CreateGraphImage_plus_Alpha			CreateGraphImage_plus_Alpha
#define NS_ReverseGraphImage					ReverseGraphImage
#ifdef __WINDOWS__
#define NS_CreateDIBGraph						CreateDIBGraph
#define NS_CreateDIBGraphToMem					CreateDIBGraphToMem
#define NS_CreateDIBGraph_plus_Alpha			CreateDIBGraph_plus_Alpha
#define NS_CreateDIBGraphVer2					CreateDIBGraphVer2
#define NS_CreateDIBGraphVer2_plus_Alpha		CreateDIBGraphVer2_plus_Alpha
#define NS_ConvBitmapToGraphImage				ConvBitmapToGraphImage
#define NS_ConvGraphImageToBitmap				ConvGraphImageToBitmap
#endif // __WINDOWS__

//#define NS_AddUserGraphLoadFunction			S_AddUserGraphLoadFunction
//#define NS_AddUserGraphLoadFunction2			S_AddUserGraphLoadFunction2
//#define NS_AddUserGraphLoadFunction3			S_AddUserGraphLoadFunction3
#define NS_AddUserGraphLoadFunction4			AddUserGraphLoadFunction4
//#define NS_SubUserGraphLoadFunction			S_SubUserGraphLoadFunction
//#define NS_SubUserGraphLoadFunction2			S_SubUserGraphLoadFunction2
//#define NS_SubUserGraphLoadFunction3			S_SubUserGraphLoadFunction3
#define NS_SubUserGraphLoadFunction4			SubUserGraphLoadFunction4

#define NS_SetUseFastLoadFlag					SetUseFastLoadFlag
#define NS_GetGraphDataShavedMode				GetGraphDataShavedMode
#define NS_SetGraphDataShavedMode				SetGraphDataShavedMode

//��{�C���[�W�f�[�^�\���̊֌W
#define NS_CreateBaseImage						CreateBaseImage
#define NS_CreateGraphImage						CreateGraphImage
#define NS_CreateBaseImageToFile				CreateBaseImageToFile
#define NS_CreateBaseImageToMem					CreateBaseImageToMem
#define NS_CreateARGB8ColorBaseImage			CreateARGB8ColorBaseImage
#define NS_CreateXRGB8ColorBaseImage			CreateXRGB8ColorBaseImage
#define NS_CreateRGB8ColorBaseImage				CreateRGB8ColorBaseImage
#define NS_CreateARGB4ColorBaseImage			CreateARGB4ColorBaseImage
#define NS_CreatePAL8ColorBaseImage				CreatePAL8ColorBaseImage
#define NS_CreateColorDataBaseImage				CreateColorDataBaseImage
#define NS_GetBaseImageGraphDataSize			GetBaseImageGraphDataSize

#define NS_ReleaseBaseImage						ReleaseBaseImage
#define NS_ReleaseGraphImage					ReleaseGraphImage

#define NS_ConvertNormalFormatBaseImage			ConvertNormalFormatBaseImage

#define NS_GetDrawScreenBaseImage				GetDrawScreenBaseImage
#ifdef __WINDOWS__
#define NS_UpdateLayerdWindowForBaseImage		UpdateLayerdWindowForBaseImage
#define NS_UpdateLayerdWindowForPremultipliedAlphaBaseImage		UpdateLayerdWindowForPremultipliedAlphaBaseImage
#endif // __WINDOWS__
#define NS_FillBaseImage						FillBaseImage
#define NS_ClearRectBaseImage					ClearRectBaseImage
#define NS_GetPaletteBaseImage					GetPaletteBaseImage
#define NS_SetPaletteBaseImage					SetPaletteBaseImage
#define NS_SetPixelPalCodeBaseImage				SetPixelPalCodeBaseImage
#define NS_GetPixelPalCodeBaseImage				GetPixelPalCodeBaseImage
#define NS_SetPixelBaseImage					SetPixelBaseImage
#define NS_GetPixelBaseImage					GetPixelBaseImage
#define NS_DrawLineBaseImage					DrawLineBaseImage
#define NS_BltBaseImage							BltBaseImage
#define NS_BltBaseImage							BltBaseImage
#define NS_BltBaseImageWithTransColor			BltBaseImageWithTransColor
#define NS_BltBaseImageWithAlphaBlend			BltBaseImageWithAlphaBlend
#define NS_ReverseBaseImageH					ReverseBaseImageH
#define NS_ReverseBaseImageV					ReverseBaseImageV
#define NS_ReverseBaseImage						ReverseBaseImage
#define NS_CheckPixelAlphaBaseImage				CheckPixelAlphaBaseImage

#ifndef DX_NON_SAVEFUNCTION

#define NS_SaveBaseImageToBmp					SaveBaseImageToBmp
#ifndef DX_NON_PNGREAD
#define NS_SaveBaseImageToPng					SaveBaseImageToPng
#endif
#ifndef DX_NON_JPEGREAD
#define NS_SaveBaseImageToJpeg					SaveBaseImageToJpeg
#endif

#endif // DX_NON_SAVEFUNCTION

// ��{�C���[�W�`��
#define NS_DrawBaseImage						DrawBaseImage

// �J���[�}�b�`���O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s�� Ver2
#define NS_GraphColorMatchBltVer2				GraphColorMatchBltVer2







// �F���擾�֌W
#define NS_GetColorF							GetColorF
#define NS_GetColorU8							GetColorU8
#define NS_GetColor								GetColor
#define NS_GetColor2							GetColor2
#define NS_GetColor3							GetColor3
#define NS_GetColor4							GetColor4
#define NS_GetColor5							GetColor5
#define NS_CreatePaletteColorData				CreatePaletteColorData
#define NS_CreateXRGB8ColorData					CreateXRGB8ColorData
#define NS_CreateARGB8ColorData					CreateARGB8ColorData
#define NS_CreateARGB4ColorData					CreateARGB4ColorData
#define NS_CreateFullColorData					CreateFullColorData
#define NS_CreateGrayColorData					CreateGrayColorData
#define NS_CreatePal8ColorData					CreatePal8ColorData
#define NS_CreateColorData						CreateColorData
#define NS_SetColorDataNoneMask					SetColorDataNoneMask
#define NS_CmpColorData							CmpColorData

#endif // DX_NOTUSE_DRAWFUNCTION









// DxSoftImage.cpp�֐��v���g�^�C�v�錾
#ifndef DX_NON_SOFTIMAGE
#define NS_InitSoftImage						InitSoftImage
#define NS_LoadSoftImage						LoadSoftImage
#define NS_LoadSoftImageToMem					LoadSoftImageToMem
#define NS_MakeSoftImage						MakeSoftImage
#define NS_MakeARGB8ColorSoftImage				MakeARGB8ColorSoftImage
#define NS_MakeXRGB8ColorSoftImage				MakeXRGB8ColorSoftImage
#define NS_MakeARGB4ColorSoftImage				MakeARGB4ColorSoftImage
#define NS_MakeRGB8ColorSoftImage				MakeRGB8ColorSoftImage
#define NS_MakePAL8ColorSoftImage				MakePAL8ColorSoftImage

#define NS_DeleteSoftImage						DeleteSoftImage

#define NS_GetSoftImageSize						GetSoftImageSize
#define NS_CheckPaletteSoftImage				CheckPaletteSoftImage
#define NS_CheckAlphaSoftImage					CheckAlphaSoftImage
#define NS_CheckPixelAlphaSoftImage				CheckPixelAlphaSoftImage

#define NS_GetDrawScreenSoftImage				GetDrawScreenSoftImage
#ifdef __WINDOWS__
#define NS_UpdateLayerdWindowForSoftImage		UpdateLayerdWindowForSoftImage
#define NS_UpdateLayerdWindowForPremultipliedAlphaSoftImage		UpdateLayerdWindowForPremultipliedAlphaSoftImage
#endif // __WINDOWS__
#define NS_FillSoftImage						FillSoftImage
#define NS_ClearRectSoftImage					ClearRectSoftImage
#define NS_GetPaletteSoftImage					GetPaletteSoftImage
#define NS_SetPaletteSoftImage					SetPaletteSoftImage
#define NS_DrawPixelPalCodeSoftImage			DrawPixelPalCodeSoftImage
#define NS_GetPixelPalCodeSoftImage				GetPixelPalCodeSoftImage
#define NS_GetImageAddressSoftImage				GetImageAddressSoftImage
#define NS_DrawPixelSoftImage					DrawPixelSoftImage
#define NS_DrawPixelSoftImage_Unsafe_XRGB8		DrawPixelSoftImage_Unsafe_XRGB8
#define NS_DrawPixelSoftImage_Unsafe_ARGB8		DrawPixelSoftImage_Unsafe_ARGB8
#define NS_GetPixelSoftImage					GetPixelSoftImage
#define NS_GetPixelSoftImage_Unsafe_XRGB8		GetPixelSoftImage_Unsafe_XRGB8
#define NS_GetPixelSoftImage_Unsafe_ARGB8		GetPixelSoftImage_Unsafe_ARGB8
#define NS_DrawLineSoftImage					DrawLineSoftImage
#define NS_BltSoftImage							BltSoftImage
#define NS_BltSoftImageWithTransColor			BltSoftImageWithTransColor
#define NS_BltSoftImageWithAlphaBlend			BltSoftImageWithAlphaBlend
#define NS_ReverseSoftImageH					ReverseSoftImageH
#define NS_ReverseSoftImageV					ReverseSoftImageV
#define NS_ReverseSoftImage						ReverseSoftImage

#ifndef DX_NON_FONT
#define NS_BltStringSoftImage					BltStringSoftImage
#define NS_BltStringSoftImageToHandle			BltStringSoftImageToHandle
#endif  // DX_NON_FONT

#define NS_DrawSoftImage						DrawSoftImage

#ifndef DX_NON_SAVEFUNCTION

#define NS_SaveSoftImageToBmp					SaveSoftImageToBmp
#ifndef DX_NON_PNGREAD
#define NS_SaveSoftImageToPng					SaveSoftImageToPng
#endif
#ifndef DX_NON_JPEGREAD
#define NS_SaveSoftImageToJpeg					SaveSoftImageToJpeg
#endif

#endif // DX_NON_SAVEFUNCTION

#endif // DX_NON_SOFTIMAGE
















#ifndef DX_NON_SOUND

// DxSound.cpp�֐��v���g�^�C�v�錾

// �T�E���h�f�[�^�Ǘ��n�֐�
#define NS_InitSoundMem							InitSoundMem

#define NS_AddSoundData							AddSoundData
#define NS_AddStreamSoundMem					AddStreamSoundMem
#define NS_AddStreamSoundMemToMem				AddStreamSoundMemToMem
#define NS_AddStreamSoundMemToFile				AddStreamSoundMemToFile
#define NS_SetupStreamSoundMem					SetupStreamSoundMem
#define NS_PlayStreamSoundMem					PlayStreamSoundMem
#define NS_CheckStreamSoundMem					CheckStreamSoundMem
#define NS_StopStreamSoundMem					StopStreamSoundMem
#define NS_SetStreamSoundCurrentPosition		SetStreamSoundCurrentPosition
#define NS_GetStreamSoundCurrentPosition		GetStreamSoundCurrentPosition
#define NS_SetStreamSoundCurrentTime			SetStreamSoundCurrentTime
#define NS_GetStreamSoundCurrentTime			GetStreamSoundCurrentTime
#define NS_ProcessStreamSoundMem				ProcessStreamSoundMem
#define NS_ProcessStreamSoundMemAll				ProcessStreamSoundMemAll


#define NS_LoadSoundMem2						LoadSoundMem2
#define NS_LoadBGM								LoadBGM

#define NS_LoadSoundMemBase						LoadSoundMemBase
#define NS_LoadSoundMem							LoadSoundMem
#define NS_LoadSoundMemToBufNumSitei			LoadSoundMemToBufNumSitei
#define NS_LoadSoundMemByResource				LoadSoundMemByResource
#define NS_DuplicateSoundMem					DuplicateSoundMem

#define NS_LoadSoundMemByMemImageBase			LoadSoundMemByMemImageBase
#define NS_LoadSoundMemByMemImage				LoadSoundMemByMemImage
#define NS_LoadSoundMemByMemImage2				LoadSoundMemByMemImage2
#define NS_LoadSoundMemByMemImageToBufNumSitei	LoadSoundMemByMemImageToBufNumSitei
#define NS_LoadSoundMem2ByMemImage				LoadSoundMem2ByMemImage
#define NS_LoadSoundMemFromSoftSound			LoadSoundMemFromSoftSound

#define NS_DeleteSoundMem						DeleteSoundMem

#define NS_PlaySoundMem							PlaySoundMem
#define NS_StopSoundMem							StopSoundMem
#define NS_CheckSoundMem						CheckSoundMem
#define NS_SetPanSoundMem						SetPanSoundMem
#define NS_GetPanSoundMem						GetPanSoundMem
#define NS_SetVolumeSoundMem					SetVolumeSoundMem
#define NS_ChangeVolumeSoundMem					ChangeVolumeSoundMem
#define NS_GetVolumeSoundMem					GetVolumeSoundMem
#define NS_SetFrequencySoundMem					SetFrequencySoundMem
#define NS_GetFrequencySoundMem					GetFrequencySoundMem
#define NS_ResetFrequencySoundMem				ResetFrequencySoundMem

#define NS_SetNextPlayPanSoundMem				SetNextPlayPanSoundMem
#define NS_SetNextPlayVolumeSoundMem			SetNextPlayVolumeSoundMem
#define NS_ChangeNextPlayVolumeSoundMem			ChangeNextPlayVolumeSoundMem
#define NS_SetNextPlayFrequencySoundMem			SetNextPlayFrequencySoundMem

#define NS_SetCurrentPositionSoundMem			SetCurrentPositionSoundMem
#define NS_GetCurrentPositionSoundMem			GetCurrentPositionSoundMem
#define NS_SetSoundCurrentPosition				SetSoundCurrentPosition
#define NS_GetSoundCurrentPosition				GetSoundCurrentPosition
#define NS_SetSoundCurrentTime					SetSoundCurrentTime
#define NS_GetSoundCurrentTime					GetSoundCurrentTime
#define NS_GetSoundTotalSample					GetSoundTotalSample
#define NS_GetSoundTotalTime					GetSoundTotalTime

#define NS_SetLoopPosSoundMem					SetLoopPosSoundMem
#define NS_SetLoopTimePosSoundMem				SetLoopTimePosSoundMem
#define NS_SetLoopSamplePosSoundMem				SetLoopSamplePosSoundMem

#define NS_SetLoopStartTimePosSoundMem			SetLoopStartTimePosSoundMem
#define NS_SetLoopStartSamplePosSoundMem		SetLoopStartSamplePosSoundMem

#define NS_Set3DPositionSoundMem				Set3DPositionSoundMem
#define NS_Set3DRadiusSoundMem					Set3DRadiusSoundMem
//#define NS_Set3DInnerRadiusSoundMem			Set3DInnerRadiusSoundMem
#define NS_Set3DVelocitySoundMem				Set3DVelocitySoundMem
//#define NS_Set3DFrontPosition_UpVecYSoundMem	Set3DFrontPosition_UpVecYSoundMem
//#define NS_Set3DFrontPositionSoundMem			Set3DFrontPositionSoundMem
//#define NS_Set3DConeAngleSoundMem				Set3DConeAngleSoundMem
//#define NS_Set3DConeVolumeSoundMem			Set3DConeVolumeSoundMem

// �ݒ�֌W�֐�
#define NS_SetCreateSoundDataType				SetCreateSoundDataType
#define NS_GetCreateSoundDataType				GetCreateSoundDataType
#define NS_SetDisableReadSoundFunctionMask		SetDisableReadSoundFunctionMask
#define NS_GetDisableReadSoundFunctionMask		GetDisableReadSoundFunctionMask
#define NS_SetEnableSoundCaptureFlag			SetEnableSoundCaptureFlag
#define NS_SetUseSoftwareMixingSoundFlag		SetUseSoftwareMixingSoundFlag
#define NS_SetEnableXAudioFlag					SetEnableXAudioFlag

#define NS_SetCreate3DSoundFlag					SetCreate3DSoundFlag
#define NS_Set3DSoundOneMetre					Set3DSoundOneMetre
#define NS_Set3DSoundListenerPosAndFrontPos_UpVecY	Set3DSoundListenerPosAndFrontPos_UpVecY
#define NS_Set3DSoundListenerPosAndFrontPos		Set3DSoundListenerPosAndFrontPos
#define NS_Set3DSoundListenerVelocity			Set3DSoundListenerVelocity
#define NS_Set3DSoundListenerConeAngle			Set3DSoundListenerConeAngle
#define NS_Set3DSoundListenerConeVolume			Set3DSoundListenerConeVolume


// ���擾�n�֐�
#define NS_GetDSoundObj							GetDSoundObj

#ifndef DX_NON_BEEP
// BEEP���Đ��p����
#define NS_SetBeepFrequency						SetBeepFrequency
#define NS_PlayBeep								PlayBeep
#define NS_StopBeep								StopBeep
#endif

// ���b�p�[�֐�
#define NS_PlaySoundFile						PlaySoundFile
#define NS_PlaySound							PlaySound
#define NS_CheckSoundFile						CheckSoundFile
#define NS_CheckSound							CheckSound
#define NS_StopSoundFile						StopSoundFile
#define NS_StopSound							StopSound
#define NS_SetVolumeSoundFile					SetVolumeSoundFile
#define NS_SetVolumeSound						SetVolumeSound

// �\�t�g�E�G�A����T�E���h�n�֐�
#define NS_InitSoftSound						InitSoftSound
#define NS_LoadSoftSound						LoadSoftSound
#define NS_LoadSoftSoundFromMemImage			LoadSoftSoundFromMemImage
#define NS_MakeSoftSound						MakeSoftSound
#define NS_MakeSoftSound2Ch16Bit44KHz			MakeSoftSound2Ch16Bit44KHz
#define NS_MakeSoftSound2Ch16Bit22KHz			MakeSoftSound2Ch16Bit22KHz
#define NS_MakeSoftSound2Ch8Bit44KHz			MakeSoftSound2Ch8Bit44KHz
#define NS_MakeSoftSound2Ch8Bit22KHz			MakeSoftSound2Ch8Bit22KHz
#define NS_MakeSoftSound1Ch16Bit44KHz			MakeSoftSound1Ch16Bit44KHz
#define NS_MakeSoftSound1Ch16Bit22KHz			MakeSoftSound1Ch16Bit22KHz
#define NS_MakeSoftSound1Ch8Bit44KHz			MakeSoftSound1Ch8Bit44KHz
#define NS_MakeSoftSound1Ch8Bit22KHz			MakeSoftSound1Ch8Bit22KHz
#define NS_MakeSoftSoundCustom					MakeSoftSoundCustom
#define NS_DeleteSoftSound						DeleteSoftSound
#ifndef DX_NON_SAVEFUNCTION
#define NS_SaveSoftSound						SaveSoftSound
#endif // DX_NON_SAVEFUNCTION
#define NS_GetSoftSoundSampleNum				GetSoftSoundSampleNum
#define NS_GetSoftSoundFormat					GetSoftSoundFormat
#define NS_ReadSoftSoundData					ReadSoftSoundData
#define NS_WriteSoftSoundData					WriteSoftSoundData
#define NS_GetSoftSoundDataImage				GetSoftSoundDataImage

#define NS_InitSoftSoundPlayer					InitSoftSoundPlayer
#define NS_MakeSoftSoundPlayer					MakeSoftSoundPlayer
#define NS_MakeSoftSoundPlayer2Ch16Bit44KHz		MakeSoftSoundPlayer2Ch16Bit44KHz
#define NS_MakeSoftSoundPlayer2Ch16Bit22KHz		MakeSoftSoundPlayer2Ch16Bit22KHz
#define NS_MakeSoftSoundPlayer2Ch8Bit44KHz		MakeSoftSoundPlayer2Ch8Bit44KHz
#define NS_MakeSoftSoundPlayer2Ch8Bit22KHz		MakeSoftSoundPlayer2Ch8Bit22KHz
#define NS_MakeSoftSoundPlayer1Ch16Bit44KHz		MakeSoftSoundPlayer1Ch16Bit44KHz
#define NS_MakeSoftSoundPlayer1Ch16Bit22KHz		MakeSoftSoundPlayer1Ch16Bit22KHz
#define NS_MakeSoftSoundPlayer1Ch8Bit44KHz		MakeSoftSoundPlayer1Ch8Bit44KHz
#define NS_MakeSoftSoundPlayer1Ch8Bit22KHz		MakeSoftSoundPlayer1Ch8Bit22KHz
#define NS_MakeSoftSoundPlayerCustom			MakeSoftSoundPlayerCustom
#define NS_DeleteSoftSoundPlayer				DeleteSoftSoundPlayer
#define NS_AddDataSoftSoundPlayer				AddDataSoftSoundPlayer
#define NS_AddDirectDataSoftSoundPlayer			AddDirectDataSoftSoundPlayer
#define NS_AddOneDataSoftSoundPlayer			AddOneDataSoftSoundPlayer
#define NS_GetSoftSoundPlayerFormat				GetSoftSoundPlayerFormat
#define NS_StartSoftSoundPlayer					StartSoftSoundPlayer
#define NS_CheckStartSoftSoundPlayer			CheckStartSoftSoundPlayer
#define NS_StopSoftSoundPlayer					StopSoftSoundPlayer
#define NS_ResetSoftSoundPlayer					ResetSoftSoundPlayer
#define NS_GetStockDataLengthSoftSoundPlayer	GetStockDataLengthSoftSoundPlayer
#define NS_CheckSoftSoundPlayerNoneData			CheckSoftSoundPlayerNoneData


// �l�h�c�h����֐�
#define NS_DeleteMusicMem						DeleteMusicMem
#define NS_LoadMusicMem							LoadMusicMem
#define NS_LoadMusicMemByMemImage				LoadMusicMemByMemImage
#define NS_LoadMusicMemByResource				LoadMusicMemByResource
#define NS_PlayMusicMem							PlayMusicMem
#define NS_StopMusicMem							StopMusicMem
#define NS_CheckMusicMem						CheckMusicMem
#define NS_SetVolumeMusicMem					SetVolumeMusicMem
#define NS_GetMusicMemPosition					GetMusicMemPosition
#define NS_InitMusicMem							InitMusicMem
#define NS_ProcessMusicMem						ProcessMusicMem

#define NS_PlayMusic							PlayMusic
#define NS_PlayMusicByMemImage					PlayMusicByMemImage
#define NS_PlayMusicByResource					PlayMusicByResource
#define NS_SetVolumeMusic						SetVolumeMusic
#define NS_StopMusic							StopMusic
#define NS_CheckMusic							CheckMusic
#define NS_GetMusicPosition						GetMusicPosition

#define NS_SelectMidiMode						SelectMidiMode

#endif // DX_NON_SOUND










// DxArchive_.cpp �֐� �v���g�^�C�v�錾
#define NS_DXArchivePreLoad		DXArchivePreLoad
#define NS_DXArchiveCheckIdle	DXArchiveCheckIdle
#define NS_DXArchiveRelease		DXArchiveRelease
#define NS_DXArchiveCheckFile	DXArchiveCheckFile
















// DxModel.cpp �֐� �v���g�^�C�v�錾

#ifndef DX_NON_MODEL


#endif






#endif

}

#endif

