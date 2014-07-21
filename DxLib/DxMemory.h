// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�������֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXMEMORY_H__
#define __DXMEMORY_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxThread.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#ifdef _WIN64
#define ALLOCNAMELENGTH			(32)
#define DXALLOC_INFO_SIZE		(64)
#else
#define ALLOCNAMELENGTH			(16)
#define DXALLOC_INFO_SIZE		(32)
#endif

#define DXADDRESS	(DXALLOC_INFO_SIZE * 2)
#define DXADDSIZE	(DXALLOC_INFO_SIZE * 3)

// �������m�یn�֐�
//#ifdef DX_USE_DXLIB_MEM_DUMP
#ifdef _DEBUG
	#define DXALLOC( size )			NS_DxAlloc( (size), __FILE__, __LINE__ )
	#define DXCALLOC( size )		NS_DxCalloc( (size), __FILE__, __LINE__ )
	#define DXREALLOC( mem, size )	NS_DxRealloc( (mem), (size), __FILE__, __LINE__ )
	#define DXFREE( mem )			NS_DxFree( (mem) )
#else
	#define DXALLOC( size )			NS_DxAlloc( (size), "", 0 )
	#define DXCALLOC( size )		NS_DxCalloc( (size), "", 0 )
	#define DXREALLOC( mem, size )	NS_DxRealloc( (mem), (size), "", 0 )
	#define DXFREE( mem )			NS_DxFree( (mem) )
#endif

//#else
//	#define DXALLOC( size )			AllocWrap( (size) )
//	#define DXCALLOC( size )		CallocWrap( (size) )
//	#define DXREALLOC( mem, size )	ReallocWrap( (mem), (size) )
//	#define DXFREE( mem )			FreeWrap( (mem) )
//	#define DXALLOC( size )			malloc( (size) )
//	#define DXCALLOC( size )		calloc( 1, (size) )
//	#define DXREALLOC( mem, size )	realloc( (mem), (size) )
//	#define DXFREE( mem )			free( (mem) )
//#endif

// �\���̒�` --------------------------------------------------------------------

// �������m�ۂ̏��
#ifdef _WIN64
struct ALLOCMEM
{
	char					Name[ ALLOCNAMELENGTH ] ;			// �t�@�C���p�X
	int						ID ;								// �h�c
	int						Line ;								// �s�ԍ�
	size_t					Size ;								// �m�ۃT�C�Y
	struct ALLOCMEM			*Back, *Next ;						// ���ƑO�̊m�ۃ��������ւ̃|�C���^
} ;
#else
struct ALLOCMEM
{
	char					Name[ ALLOCNAMELENGTH ] ;			// �t�@�C���p�X
	unsigned short			ID ;								// �h�c
	unsigned short			Line ;								// �s�ԍ�
	size_t					Size ;								// �m�ۃT�C�Y
	struct ALLOCMEM			*Back, *Next ;						// ���ƑO�̊m�ۃ��������ւ̃|�C���^
} ;
#endif

// �������֌W�̏��\����
struct MEMORYDATA
{
	ALLOCMEM				AllocMemoryAnchor ;					// �������m�ۏ��̍Ō��
	char					AllocMemoryAnchorDummy[DXALLOC_INFO_SIZE * 2] ;
	ALLOCMEM				*AllocMemoryFirst ;					// �������m�ۏ��̐擪
	unsigned short			AllocMemoryID ;						// �m�ۂ����������Ɋ��蓖�Ă�h�c
	size_t					AllocMemorySize ;					// �m�ۂ��Ă��郁�����̑���
	int						AllocMemoryNum ;					// ���C�u�����Ŋm�ۂ����������̐�
	int						AllocMemoryPrintFlag ;				// �m�ۂ���鎞�ɏ����o�͂��邩�ǂ����̃t���O
	int						AllocMemorySizeOutFlag ;			// �m�ۂ������s����x�Ɋm�ۃ������̑��ʂ����O�ɏo�͂��邩�ǂ����̃t���O
	int						AllocMemoryErrorCheckFlag ;			// �m�ۂ������s����x�Ɋm�ۃ������̏�񂪔j�����Ă��Ȃ������`�F�b�N���邩�ǂ����̃t���O
	size_t					AllocTrapSize ;						// �񋓑Ώۂɂ���m�ۃT�C�Y

#if defined( DX_THREAD_SAFE ) || defined( DX_THREAD_SAFE_NETWORK_ONLY )
	int						InitMemoryAllocCriticalSection ;	// MemoryAllocCriticalSection �̏��������ς�ł��邩�ǂ����̃t���O
	DX_CRITICAL_SECTION		MemoryAllocCriticalSection ;		// �������m�ۏ����p�N���e�B�J���Z�N�V����
#endif
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

// �������֌W�̏��
extern MEMORYDATA MemData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern void			MemoryDump( void *buffer, int size ) ;
extern int			DxCheckAlloc( ALLOCMEM *Alloc ) ;										// �m�ۏ�񂪔j�󂳂�Ă��Ȃ������ׂ�

// ���b�p�[�֐�
extern	void 		*AllocWrap( size_t AllocSize ) ;										// ���������m�ۂ���
extern	void 		*CallocWrap( size_t AllocSize ) ;										// ���������m�ۂ��ĂO�ŏ���������
extern	void		*ReallocWrap( void *Memory, size_t AllocSize ) ;						// �������̍Ċm�ۂ��s��
extern	void		FreeWrap( void *Memory ) ;												// ���������������

}

#endif // __DXMEMORY_H__
