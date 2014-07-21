// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�`��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXGRAPHICS_H__
#define __DXGRAPHICS_H__

// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxGraphicsBase.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxHandle.h"
#include "DxMemImg.h"
#include "DxGraphicsAPI.h"
#include "DxArchive_.h"
#include <stdarg.h>

#if !defined( __ANDROID )
#include "Windows/DxGraphicsWin.h"
#endif

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#define GRA2						GraphicsManage2
#define GRH							GraphicsManage2.Hard
#define GRS							GraphicsManage2.Soft

// DrawPreparation �֐��ɓn���t���O
#define DRAWPREP_TRANS				(0x00001)
#define DRAWPREP_VECTORINT			(0x00002)
#define DRAWPREP_GOURAUDSHADE		(0x00008)
#define DRAWPREP_PERSPECTIVE		(0x00010)
#define DRAWPREP_DIFFUSERGB			(0x00020)
#define DRAWPREP_DIFFUSEALPHA		(0x00040)
#define DRAWPREP_FOG				(0x00080)
#define DRAWPREP_NOBLENDSETTING		(0x00100)
#define DRAWPREP_LIGHTING			(0x00200)
#define DRAWPREP_SPECULAR			(0x00400)
#define DRAWPREP_3D					(0x00800)
#define DRAWPREP_TEXADDRESS			(0x01000)
#define DRAWPREP_NOTSHADERRESET		(0x02000)
#define DRAWPREP_CULLING			(0x04000)
#define DRAWPREP_TEXALPHACH			(0x08000)
#define DRAWPREP_TEXALPHATEST		(0x10000)
#define DRAWPREP_EDGEFONT			(0x20000)

// ���_�^�C�v
#define VERTEXTYPE_NOTEX			(0)				// �e�N�X�`�����g�p���Ȃ�
#define VERTEXTYPE_TEX				(1)				// �e�N�X�`������g�p����
#define VERTEXTYPE_BLENDTEX			(2)				// �u�����h�e�N�X�`�����g�p����
#define VERTEXTYPE_NUM				(3)

// �}�X�N��^����
#ifdef DX_NON_MASK
#define MASK_FULLSCREEN_MASKUPDATE
#else
#define MASK_FULLSCREEN_MASKUPDATE					\
	if( MASKD.FullScreenMaskUpdateFlag )			\
	{												\
		RECT MaskRect ;								\
		MaskRect.left   = GBASE.DrawArea.left ;		\
		MaskRect.right  = GBASE.DrawArea.right ;	\
		MaskRect.top    = GBASE.DrawArea.top ;		\
		MaskRect.bottom = GBASE.DrawArea.bottom ;	\
		MASK_END( MaskRect )						\
		MASKD.FullScreenMaskUpdateFlag = FALSE ;	\
	}
#endif

#ifdef DX_NON_MASK
#define MASK_BEGIN( RECT )
#else
#define MASK_BEGIN( RECT )		if( MASKD.MaskValidFlag ) MaskDrawBeginFunction( (RECT) ) ;
#endif

#ifdef DX_NON_MASK
#define MASK_END( RECT )
#else
#define MASK_END( RECT )		if( MASKD.MaskValidFlag ) MaskDrawAfterFunction( (RECT) ) ;
#endif


// �`���^����
#ifdef DX_NON_2DDRAW
	#ifdef DX_NON_MASK
		#define DRAW_DEF( FUNC3D, FUNC2D, SETRECT, RET, USE3DFLAG )\
			if( GBASE.BlendMode == DX_BLENDMODE_SUB && GRH.ValidDestBlendOp == FALSE )\
			{\
				RECT DrawRect ;\
				SETRECT\
				BlendModeSub_Pre( &DrawRect ) ;\
				RET = (FUNC3D) ;\
				BlendModeSub_Post( &DrawRect ) ;\
			}\
			else\
			{\
				RET = (FUNC3D) ;\
			}
	#else // DX_NON_MASK
		#define DRAW_DEF( FUNC3D, FUNC2D, SETRECT, RET, USE3DFLAG )\
			{\
				bool UseSubMode = GBASE.BlendMode == DX_BLENDMODE_SUB && GRH.ValidDestBlendOp == FALSE ;\
				if( UseSubMode || MASKD.MaskValidFlag )\
				{\
					RECT DrawRect ;\
					SETRECT\
					MASK_BEGIN( DrawRect ) ;\
					if( UseSubMode )\
					{\
						BlendModeSub_Pre( &DrawRect ) ;\
						RET = (FUNC3D) ;\
						BlendModeSub_Post( &DrawRect ) ;\
					}\
					else\
					{\
						RET = (FUNC3D) ;\
					}\
					\
					MASK_END( DrawRect ) ;\
				}\
				else\
				{\
					RET = (FUNC3D) ;\
				}\
			}
	#endif // DX_NON_MASK
#else // DX_NON_2DDRAW
	#ifdef DX_NON_MASK
		#define DRAW_DEF( FUNC3D, FUNC2D, SETRECT, RET, USE3DFLAG )\
			if( GBASE.BlendMode == DX_BLENDMODE_SUB && GRH.ValidDestBlendOp == FALSE && (USE3DFLAG) )\
			{\
				RECT DrawRect ;\
				SETRECT\
				BlendModeSub_Pre( &DrawRect ) ;\
				RET = (FUNC3D) ;\
				BlendModeSub_Post( &DrawRect ) ;\
			}\
			else\
			{\
				RET = (USE3DFLAG) ? (FUNC3D) : (FUNC2D) ;\
			}
	#else // DX_NON_MASK
		#define DRAW_DEF( FUNC3D, FUNC2D, SETRECT, RET, USE3DFLAG )\
			{\
				bool UseSubMode = GBASE.BlendMode == DX_BLENDMODE_SUB && GRH.ValidDestBlendOp == FALSE && (USE3DFLAG) ;\
				if( UseSubMode || MASKD.MaskValidFlag )\
				{\
					RECT DrawRect ;\
					SETRECT\
					MASK_BEGIN( DrawRect ) ;\
					if( UseSubMode )\
					{\
						BlendModeSub_Pre( &DrawRect ) ;\
						RET = (FUNC3D) ;\
						BlendModeSub_Post( &DrawRect ) ;\
					}\
					else\
					{\
						RET = (USE3DFLAG) ? (FUNC3D) : (FUNC2D) ;\
					}\
					\
					MASK_END( DrawRect ) ;\
				}\
				else\
				{\
					RET = (USE3DFLAG) ? (FUNC3D) : (FUNC2D) ;\
				}\
			}
	#endif // DX_NON_MASK
#endif // DX_NON_2DDRAW


// ���_�t�H�[�}�b�g
#define VERTEXFVF_NOTEX_2D			( D_D3DFVF_XYZRHW | D_D3DFVF_DIFFUSE )														// ���C���A�{�b�N�X�`��p���_�t�H�[�}�b�g
#define VERTEXFVF_2D				( D_D3DFVF_XYZRHW | D_D3DFVF_DIFFUSE | D_D3DFVF_TEX1 )										// �g�����X�t�H�[���ςݒ��_�t�H�[�}�b�g
#define VERTEXFVF_BLENDTEX_2D		( D_D3DFVF_XYZRHW | D_D3DFVF_DIFFUSE | D_D3DFVF_SPECULAR | D_D3DFVF_TEX2 )					// ���u�����h�e�N�X�`���t���g�����X�t�H�[���ςݒ��_�t�H�[�}�b�g
#define VERTEXFVF_SHADER_2D			( D_D3DFVF_XYZRHW | D_D3DFVF_DIFFUSE | D_D3DFVF_SPECULAR | D_D3DFVF_TEX2 )					// �V�F�[�_�[�`��p���_�t�H�[�}�b�g
#define VERTEXFVF_NOTEX_3D			( D_D3DFVF_XYZ | D_D3DFVF_DIFFUSE /*| D_D3DFVF_SPECULAR*/ )									// ���C���A�{�b�N�X�`��p���_�t�H�[�}�b�g�A�R�c�p( ���o�[�W�����p )
#define VERTEXFVF_3D				( D_D3DFVF_XYZ | D_D3DFVF_DIFFUSE /*| D_D3DFVF_SPECULAR*/ | D_D3DFVF_TEX1 )					// �O���t�B�b�N�X�`��p���_�t�H�[�}�b�g�A�R�c�p( ���o�[�W�����p )
#define VERTEXFVF_3D_LIGHT			( D_D3DFVF_XYZ | D_D3DFVF_NORMAL | D_D3DFVF_DIFFUSE | D_D3DFVF_SPECULAR | D_D3DFVF_TEX2 )	// �O���t�B�b�N�X�`��p���_�t�H�[�}�b�g
#define VERTEXFVF_SHADER_3D			( D_D3DFVF_XYZ | D_D3DFVF_NORMAL | D_D3DFVF_DIFFUSE | D_D3DFVF_SPECULAR | D_D3DFVF_TEX2 )	// �V�F�[�_�[�`��p���_�t�H�[�}�b�g

// ���_�o�b�t�@�̃T�C�Y
#define D3DDEV_NOTEX_VERTBUFFERSIZE		(63 * 1024)		// 63KB
#define D3DDEV_TEX_VERTBUFFERSIZE		(64 * 1024)		// 64KB
#define D3DDEV_BLENDTEX_VERTBUFFERSIZE	(64 * 1024)		// 64KB
#define D3DDEV_NOTEX_3D_VERTBUFFERSIZE	(64 * 1024)		// 64KB
#define D3DDEV_TEX_3D_VERTBUFFERSIZE	(64 * 1024)		// 64KB
#define D3DDEV_NOTEX_VERTMAXNUM			(D3DDEV_NOTEX_VERTBUFFERSIZE     / sizeof( VERTEX_NOTEX_2D    ))
#define D3DDEV_TEX_VERTMAXNUM			(D3DDEV_TEX_VERTBUFFERSIZE       / sizeof( VERTEX_2D          ))
#define D3DDEV_BLENDTEX_VERTMAXNUM		(D3DDEV_BLENDTEX_VERTBUFFERSIZE  / sizeof( VERTEX_BLENDTEX_2D ))
#define D3DDEV_NOTEX_3D_VERTMAXNUM		(D3DDEV_NOTEX_3D_VERTBUFFERSIZE  / sizeof( VERTEX_NOTEX_3D    ))
#define D3DDEV_TEX_3D_VERTMAXNUM		(D3DDEV_TEX_3D_VERTBUFFERSIZE    / sizeof( VERTEX_3D          ))

// ���_�C���f�b�N�X�o�b�t�@�̃T�C�Y
#define D3DDEV_INDEX_NUM			( D3DDEV_NOTEX_VERTMAXNUM / 4 * 6 )

// �t�B���^�[�^�C�v��`
#define DX_D3DTEXF_NONE				D_D3DTEXF_NONE
#define DX_D3DTEXF_POINT			D_D3DTEXF_POINT
#define DX_D3DTEXF_LINEAR			D_D3DTEXF_LINEAR
#define DX_D3DTEXF_ANISOTROPIC		D_D3DTEXF_ANISOTROPIC
#define DX_D3DTEXF_PYRAMIDALQUAD	D_D3DTEXF_PYRAMIDALQUAD
#define DX_D3DTEXF_GAUSSIANQUAD		D_D3DTEXF_GAUSSIANQUAD

// �t�B���^�[�^�[�Q�b�g��`
#define DX_D3DSAMP_MAGFILTER		D_D3DTSS_MAGFILTER
#define DX_D3DSAMP_MINFILTER		D_D3DTSS_MINFILTER
#define DX_D3DSAMP_MIPFILTER		D_D3DTSS_MIPFILTER

// �V�F�[�_�[�萔�Z�b�g
#define DX_SHADERCONSTANTSET_LIB		0
#define DX_SHADERCONSTANTSET_LIB_SUB	1
#define DX_SHADERCONSTANTSET_MV1		2
#define DX_SHADERCONSTANTSET_USER		3
#define DX_SHADERCONSTANTSET_NUM		4

// �V�F�[�_�[�萔�Z�b�g�}�X�N
#define DX_SHADERCONSTANTSET_MASK_LIB		0x0001
#define DX_SHADERCONSTANTSET_MASK_LIB_SUB	0x0002
#define DX_SHADERCONSTANTSET_MASK_MV1		0x0004
#define DX_SHADERCONSTANTSET_MASK_USER		0x0008

// �V�F�[�_�[�萔�^�C�v
#define DX_SHADERCONSTANTTYPE_VS_FLOAT		0
#define DX_SHADERCONSTANTTYPE_VS_INT		1
#define DX_SHADERCONSTANTTYPE_VS_BOOL		2
#define DX_SHADERCONSTANTTYPE_PS_FLOAT		3
#define DX_SHADERCONSTANTTYPE_PS_INT		4
#define DX_SHADERCONSTANTTYPE_PS_BOOL		5
#define DX_SHADERCONSTANTTYPE_NUM			6

// ���_�V�F�[�_�[�z��C���f�b�N�X�쐬�p�}�N��
#define VS_TOONOUTLINE( use )				( ( use )  * 2 * 3 * 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_LIGHTUSE( use )					( ( use )  * 3 * 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_SKINMESH( use )					( ( use )  * 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_PHONG( use )						( ( use )  * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_BUMPMAP( use )					( ( use )  * 4 * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_FOGMODE( mode )					( ( mode ) * 4 * 4 * 4 * 2 * 2 * 2 )
#define VS_LIGHT0TYPE( type )				( ( type ) * 4 * 4 * 2 * 2 * 2 )
#define VS_LIGHT1TYPE( type )				( ( type ) * 4 * 2 * 2 * 2 )
#define VS_LIGHT2TYPE( type )				( ( type ) * 2 * 2 * 2 )
#define VS_DIFCSOURCE( vert )				( ( vert ) * 2 * 2 )
#define VS_SPECSOURCE( vert )				( ( vert ) * 2 )
#define VS_SPECULAR( use )					( ( use ) )

// ���_�V�F�[�_�[�z��C���f�b�N�X����e�v�f���擾���邽�߂̃}�N��
#define VS_GET_TOONOUTLINE( index )			( ( index ) / ( 2 * 3 * 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 ) % 2 )
#define VS_GET_LIGHTUSE( index )			( ( index ) / ( 3 * 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 ) % 2 )
#define VS_GET_SKINMESH( index )			( ( index ) / ( 2 * 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 ) % 3 )
#define VS_GET_PHONG( index )				( ( index ) / ( 2 * 4 * 4 * 4 * 4 * 2 * 2 * 2 ) % 2 )
#define VS_GET_BUMPMAP( index )				( ( index ) / ( 4 * 4 * 4 * 4 * 2 * 2 * 2 ) % 2 )
#define VS_GET_FOGMODE( index )				( ( index ) / ( 4 * 4 * 4 * 2 * 2 * 2 ) % 4 )
#define VS_GET_LIGHT0TYPE( index )			( ( index ) / ( 4 * 4 * 2 * 2 * 2 ) % 4 )
#define VS_GET_LIGHT1TYPE( index )			( ( index ) / ( 4 * 2 * 2 * 2 ) % 4 )
#define VS_GET_LIGHT2TYPE( index )			( ( index ) / ( 2 * 2 * 2 ) % 4 )
#define VS_GET_DIFCSOURCE( index )			( ( index ) / ( 2 * 2 ) % 2 )
#define VS_GET_SPECSOURCE( index )			( ( index ) / ( 2 ) % 2 )
#define VS_GET_SPECULAR( index )			( ( index ) % 2 )

// �s�N�Z���V�F�[�_�[�z��C���f�b�N�X�쐬�p�}�N��
#define PS_TOON( use )						( ( use )  * 3 * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 * 2 )
#define PS_TOONSPHEREOP( type )				( ( type ) * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 * 2 )
#define PS_TOONDIFBLDOP( type )				( ( type ) * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 )
#define PS_TOONSPCBLDOP( type )				( ( type ) * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 )
#define PS_LIGHTUSE( use )					( ( use )  * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 )
#define PS_SPECULARMAP( use )				( ( use )  * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 )
#define PS_PHONG( use )						( ( use )  * 2 * 3 * 3 * 3 * 2 * 2 * 2 )
#define PS_BUMPMAP( use )					( ( use )  * 3 * 3 * 3 * 2 * 2 * 2 )
#define PS_LIGHT0TYPE( type )				( ( type ) * 3 * 3 * 2 * 2 * 2 )
#define PS_LIGHT1TYPE( type )				( ( type ) * 3 * 2 * 2 * 2 )
#define PS_LIGHT2TYPE( type )				( ( type ) * 2 * 2 * 2 )
#define PS_DIFCSOURCE( vert )				( ( vert ) * 2 * 2 )
#define PS_SPECSOURCE( vert )				( ( vert ) * 2 )
#define PS_SPECULAR( use )					( ( use ) )

// �s�N�Z���V�F�[�_�[�z��C���f�b�N�X����e�v�f���擾���邽�߂̃}�N��
#define PS_GET_TOON( index )				( ( index ) / ( 3 * 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 * 2 ) % 3 )
#define PS_GET_TOONSPHEREOP( index )		( ( index ) / ( 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 * 2 ) % 3 )
#define PS_GET_TOONDIFBLDOP( index )		( ( index ) / ( 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 * 2 ) % 2 )
#define PS_GET_TOONSPCBLDOP( index )		( ( index ) / ( 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 * 2 ) % 2 )
#define PS_GET_LIGHTUSE( index )			( ( index ) / ( 2 * 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 ) % 2 )
#define PS_GET_SPECULARMAP( index )			( ( index ) / ( 2 * 2 * 3 * 3 * 3 * 2 * 2 * 2 ) % 2 )
#define PS_GET_PHONG( index )				( ( index ) / ( 2 * 3 * 3 * 3 * 2 * 2 * 2 ) % 2 )
#define PS_GET_BUMPMAP( index )				( ( index ) / ( 3 * 3 * 3 * 2 * 2 * 2 ) % 2 )
#define PS_GET_LIGHT0TYPE( index )			( ( index ) / ( 3 * 3 * 2 * 2 * 2 ) % 3 )
#define PS_GET_LIGHT1TYPE( index )			( ( index ) / ( 3 * 2 * 2 * 2 ) % 3 )
#define PS_GET_LIGHT2TYPE( index )			( ( index ) / ( 2 * 2 * 2 ) % 3 )
#define PS_GET_DIFCSOURCE( index )			( ( index ) / ( 2 * 2 ) % 2 )
#define PS_GET_SPECSOURCE( index )			( ( index ) / ( 2 ) % 2 )
#define PS_GET_SPECULAR( index )			( ( index ) % 2 )

// �t�B���^�[�^�C�v��`
#define DX_D3DTEXFILTER_TYPE		D_D3DTEXTUREFILTERTYPE

// �e�f�[�^�ւ̃A�N�Z�X�L�q�ȗ����p�}�N��
#define GSYSTEM						DX_GraphicsSystemData

// �f�o�C�X�񋓂̍ő吔
#define MAX_DEVICE_LISTUP					(32)

// ��Ǘ��e�N�X�`���ւ̃f�[�^�]���p�V�X�e���������z�u�e�N�X�`���̐�
#define SYSMEMTEXTURE_NUM					(2048)


// �\���̒�` --------------------------------------------------------------------

// ���������_�^�F�\����
struct COLOR
{
	float					r, g, b, a ;
} ;

// �u�����h�摜�t���Q�c�摜�`��p���_�\����
struct VERTEX_BLENDTEX_2D
{
	VECTOR					pos ;
	float					rhw ;
	int						color ;
	unsigned int			specular ;
	float					u1, v1 ;
	float					u2, v2 ;
} ;

// �}�e���A���\����
struct MATERIAL
{
	COLOR					Diffuse ;		// �f�B�t���[�Y�F
	COLOR					Ambient ;		// �A���r�G���g�F
	COLOR					Specular ;		// �X�y�L�����[�F
	COLOR					Emissive ;		// �G�~�b�V�����F
	float					Power ;			// �p���[
} ;

// ���C�g�\����
struct LIGHT
{
	int						Type ;
	COLOR					Diffuse ;
	COLOR					Specular ;
	COLOR					Ambient ;
	VECTOR					Position ;
	VECTOR					Direction ;
	float					Range ;
	float					Falloff ;
	float					Attenuation0 ;
	float					Attenuation1 ;
	float					Attenuation2 ;
	float					Theta ;
	float					Phi ;
} ;


// �e�N�X�`���X�e�[�W�̏��
struct DIRECT3DTEXTURESTAGEINFO
{
	void					*Texture ;							// �X�e�[�W�ɃZ�b�g����Ă���e�N�X�`���T�[�t�F�X
	int						TextureCoordIndex ;					// �g�p����e�N�X�`�����W�C���f�b�N�X
	int						ResultTempARG ;						// �o�͐惌�W�X�^���e���|�����ɂ��邩�ǂ���
	short					AlphaARG1, AlphaARG2, AlphaOP ;		// Direct3DDevice �� D3DTSS_ALPHAOP �� D3DTSS_ALPHAARG1 �� D3DTSS_ALPHAARG2 �̐ݒ�l
	short					ColorARG1, ColorARG2, ColorOP ;		// Direct3DDevice �� D3DTSS_COLOROP �� D3DTSS_COLORARG1 �� D3DTSS_COLORARG2 �̐ݒ�l
} ;

// �c�����������R�c �̃u�����h�ݒ�Ɋւ�ݒ�̏��
struct DIRECT3DBLENDINFO
{
	int						AlphaTestEnable ;					// Direct3DDevice �� D3DRENDERSTATE_ALPHATESTENABLE �̐ݒ�l
	int						AlphaRef ;							// Direct3DDevice �� D3DRENDERSTATE_ALPHAREF �̐ݒ�l
	int						AlphaFunc ;							// Direct3DDevice �� D3DRENDERSTATE_ALPHAFUNC �̐ݒ�l
	int						AlphaBlendEnable ;					// Direct3DDevice �� D3DRENDERSTATE_ALPHABLENDENABLE �̐ݒ�l

	DWORD					FactorColor ;						// Direct3DDevice �� D3DRENDERSTATE_TEXTUREFACTOR �̐ݒ�l
	int						SrcBlend, DestBlend ;				// Direct3DDevice �� D3DRENDERSTATE_DESTBLEND �� D3DRENDERSTATE_SRCBLEND �̐ݒ�l
	int						BlendOp ;							// Direct3DDevice �� D3DRENDERSTATE_BLENDOP �̐ݒ�l
	int						UseTextureStageNum ;				// �g�p���Ă���e�N�X�`���X�e�[�W�̐�
	DIRECT3DTEXTURESTAGEINFO TextureStageInfo[USE_TEXTURESTAGE_NUM] ;	// Direct3DDevice �̃e�N�X�`���X�e�[�W�ݒ�l( Direct3DDevice �ɂ��ꂩ��K������\��̐ݒ�l )
} ;


// �\�t�g�E�G�A�����_�����O�p�I���W�i���摜���
struct IMAGEDATA2_ORIG_SOFT
{
	MEMIMG					MemImg ;						// MEMIMG
	MEMIMG					*ZBuffer ;						// ZBuffer
} ;

// ��Ǘ��e�N�X�`���ւ̃f�[�^�]���p�V�X�e���������z�u�e�N�X�`���̏��
struct IMAGEDATA2_SYSMEMTEXTURE
{
	unsigned char			InitializeFlag ;				// �g�p�\�ȏ�Ԃ��ǂ����̃t���O
	unsigned char			UseFlag ;						// �g�p�����ǂ����̃t���O
	short					Width ;							// ��
	short					Height ;						// ����
	unsigned char			MipMapCount ;					// �~�b�v�}�b�v�̐�
	unsigned char			Format ;						// �t�H�[�}�b�g
	unsigned int			UseCount ;						// �g�p��
	DX_DIRECT3DTEXTURE9		*MemTexture ;					// �V�X�e���������e�N�X�`��
} ;

// �n�[�h�E�G�A�����_�����O�p�I���W�i���摜�e�N�X�`�����
struct IMAGEDATA2_ORIG_HARD_TEX
{
	DX_DIRECT3DTEXTURE9		*Texture ;						// �e�N�X�`��
	//DX_DIRECT3DTEXTURE9	*MemTexture ;					// D3DPOOL_MANAGED ���g�p�ł��Ȃ��摜�p�������e�N�X�`��
	DX_DIRECT3DSURFACE9		*Surface ;						// �T�[�t�F�X
	DX_DIRECT3DSURFACE9		*RenderTargetSurface ;			// �����_�����O�^�[�Q�b�g�T�[�t�F�X
	DX_DIRECT3DSURFACE9		*ZBuffer ;						// �y�o�b�t�@

	int						OrigPosX, OrigPosY ;			// ���摜�Ŏg�p���Ă���̈�̍�����W
	int						UseWidth, UseHeight ;			// ���摜�Ŏg�p���Ă���̈�̃T�C�Y
	int						TexWidth, TexHeight ;			// �e�N�X�`�����̂̕��ƍ���
} ;

// �n�[�h�E�G�A�����_�����O�p�I���W�i���摜���
struct IMAGEDATA2_ORIG_HARD
{
	int						MipMapCount ;					// �~�b�v�}�b�v�̐�
	int						TexNum ;						// �e�N�X�`���̐�
	IMAGEDATA2_ORIG_HARD_TEX Tex[ 4 ] ;						// �e�N�X�`�����X�g�ւ̃|�C���^
} ;

// �I���W�i���摜���\����
struct IMAGEDATA2_ORIG
{
	int						RefCount ;						// �Q�Ƃ���Ă��鐔
	int						ColorFormat ;					// �J���[�t�H�[�}�b�g( DX_GRAPHICSIMAGE_FORMAT_3D_RGB16 �� )
	IMAGEFORMATDESC			FormatDesc ;					// �t�H�[�}�b�g
	unsigned int			TransCode ;						// ���ߐF�R�[�h
	int						Width, Height ;					// �摜�̃T�C�Y
	int						ZBufferFlag ;					// �y�o�b�t�@�����邩�ǂ���( TRUE:����  FALSE:�Ȃ� )

	union
	{
		IMAGEDATA2_ORIG_SOFT	Soft ;						// �\�t�g�E�G�A�����_�����O�p���
		IMAGEDATA2_ORIG_HARD	Hard ;						// �n�[�h�E�G�A�����_�����O�p���
	} ;
} ;

// �\�t�g�E�G�A�����_�����O�ŃC���[�W�f�[�^�\����
struct IMAGEDATA2_SOFT
{
	MEMIMG					MemImg ;						// �`��p MEMIMG
} ;

// �n�[�h�E�G�A�����_�����O�ō��W���\����
struct IMAGEDATA2_HARD_VERT
{
	float					x, y ;							// �ʒu
	float					u, v ;							// �t�u�ʒu
} ;

// �n�[�h�E�G�A�����_�����O�ŕ`��p�\����
struct IMAGEDATA2_HARD_DRAW
{
	int						DrawPosX, DrawPosY ;			// �`�掞�Ɏw�肳�����W����̑��΍��W
	int						UsePosX, UsePosY ;				// �e�N�X�`�����Ŏg�p���Ă����`�̍�����W
	int						Width, Height ;					// �e�N�X�`�����Ŏg�p���Ă���T�C�Y

	IMAGEDATA2_HARD_VERT	Vertex[ 4 ] ;					// �e�N�X�`���̕`����W���
	unsigned char			VertType[ 4 ] ;					// ���_�^�C�v( TRUE=�O�p�̔�������@FALSE=�� )

	IMAGEDATA2_ORIG_HARD_TEX *Tex ;							// �g�p����e�N�X�`���ւ̃|�C���^
} ;

// �n�[�h�E�G�A�����_�����O�ŃC���[�W�f�[�^�\����
struct IMAGEDATA2_HARD
{
	int						DrawNum ;						// �`��p���̐�
	IMAGEDATA2_HARD_DRAW	Draw[ 4 ] ;						// �`��p���
} ;

// �C���[�W���f�[�^�\����
struct IMAGEDATA_READBASE
{
	int						Type ;							// �^�C�v( 0:�t�@�C�� 1:�������C���[�W 2:BaseImage )

	TCHAR					*FileName ;						// �t�@�C����
	BASEIMAGE				*BaseImage ;					// ��{�C���[�W�f�[�^
	BASEIMAGE				*AlphaBaseImage ;				// ���`�����l���p��{�C���[�W�f�[�^
	void					*MemImage ;						// �������C���[�W
	int						MemImageSize ;					// �������C���[�W�T�C�Y
	void					*AlphaMemImage ;				// ���`�����l���p�������C���[�W
	int						AlphaMemImageSize ;				// ���`�����l���p�������C���[�W�T�C�Y
	int						ReverseFlag ;					// ���]�ǂݍ��݂������ǂ���( TRUE:����  FALSE:���ĂȂ� )�A�ēǂݍ��݂̍ۂɓǂݍ��݌��𔽓]���邩�ǂ����Ŏg�p�����ABASEIMAGE �Ɋւ��Ă͓ǂݍ��݌��ۑ����ɔ��]���邽�߂��̃t���O�͖��������

	int						RefCount ;						// �Q�Ɛ�
} ;

// �C���[�W�f�[�^�\����
struct IMAGEDATA2
{
	HANDLEINFO				HandleInfo ;					// �n���h�����ʃf�[�^

	int						*LostFlag ;						// ������ɗ��Ă�t���O�̃|�C���^

#ifndef DX_NON_MOVIE
	int						MovieHandle ;					// ����n���h��
#endif

	IMAGEDATA_READBASE		*ReadBase ;						// ���f�[�^���
	int						UseBaseX, UseBaseY ;			// ���f�[�^���Ŏg�p���Ă���͈͂̍�����W

	IMAGEDATA2_ORIG			*Orig ;							// �I���W�i���摜���\���̂ւ̃|�C���^( �I���W�i���摜�ł͂Ȃ��ꍇ�� NULL )
	int						UseOrigX, UseOrigY ;			// �I���W�i���摜���̎g�p���Ă����`�̍�����W
	int						Width, Height ;					// �I���W�i���摜���̎g�p���Ă����`�̕��ƍ���

	DWORD					*FullColorImage ;				// �t���J���[�C���[�W

	int						LockFlag ;						// ���b�N���Ă��邩�ǂ����t���O
	BYTE					*LockImage ;					// ���b�N���ɍ쐬����e���|�����C���[�W
	DWORD					LockImagePitch ;				// ���b�N�C���[�W�̃s�b�`

	union
	{
		IMAGEDATA2_SOFT		Soft ;							// �\�t�g�E�G�A�����_�����O�p�\���̂ւ̃|�C���^
		IMAGEDATA2_HARD		Hard ;							// �n�[�h�E�G�A�����_�����O�p�\���̂ւ̃|�C���^
	} ;
} ;

// �V�F�[�_�[�n���h���Ŏg�p������̍\����
struct SHADERHANDLEDATA
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	int						IsVertexShader ;					// ���_�V�F�[�_�[���ǂ���( TRUE:���_�V�F�[�_�[  FALSE:�s�N�Z���V�F�[�_�[ )
	void					*FunctionCode ;						// �V�F�[�_�[���쐬����ۂɎg�p�������ԃR�[�h���i�[�����������̈�ւ̃|�C���^
	union
	{
		DX_DIRECT3DPIXELSHADER9		*PixelShader ;				// IDirect3DPixelShader9 �̃|�C���^
		DX_DIRECT3DVERTEXSHADER9	*VertexShader ;				// IDirect3DVertexShader9 �̃|�C���^
	} ;
	int						ConstantNum ;						// �萔�̐�
	D_D3DXSHADER_CONSTANTINFO	*ConstantInfo ;					// �萔���z��̐擪�A�h���X
} ;

// ���_�o�b�t�@�n���h���Ŏg�p������̍\����
struct VERTEXBUFFERHANDLEDATA
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	int						Type ;								// ���_�f�[�^�̃^�C�v( DX_VERTEXTYPE_NORMAL_3D �� )
	int						UnitSize ;							// ���_�f�[�^��ӂ�̃o�C�g��
	int						Num ;								// ���_�̐�
	void					*Buffer ;							// �V�X�e���������Ɋm�ۂ��ꂽ�o�b�t�@
	DX_DIRECT3DVERTEXBUFFER9	*Direct3DBuffer ;				// IDirect3DVertexBuffer9 �̃|�C���^
} ;

// �C���f�b�N�X�o�b�t�@�n���h���Ŏg�p������̍\����
struct INDEXBUFFERHANDLEDATA
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	int						Type ;								// �C���f�b�N�X�f�[�^�̃^�C�v( DX_INDEX_TYPE_NORMAL_3D �� )
	int						UnitSize ;							// �C���f�b�N�X�f�[�^��ӂ�̃o�C�g��
	int						Num ;								// �C���f�b�N�X�̐�
	void					*Buffer ;							// �V�X�e���������Ɋm�ۂ��ꂽ�o�b�t�@
	DX_DIRECT3DINDEXBUFFER9	*Direct3DBuffer ;					// IDirect3DIndexBuffer9 �̃|�C���^
} ;

#ifndef DX_NON_FILTER

// �V�F�[�_�[�R�[�h�n���h��
struct SHADERCODE_HANDLE
{
	int						Gauss_PS[ 3 ] ;							// �K�E�X�t�B���^�̃s�N�Z���V�F�[�_�[
	int						BrightClipPS[ 2 ][ 2 ] ;				// ���邳�ŃN���b�v����t�B���^�̃s�N�Z���V�F�[�_�[( [ 1:���ȏ�N���b�v  0:���ȉ��N���b�v ][ 1:�N���b�v�h��Ԃ����� 0:�h��Ԃ��Ȃ� ] )
	int						DownScalePS[ 3 ] ;						// �k���t�B���^�[( 0:X2 1:X4 2:X8 )
	int						HsbPS[ 3 ] ;							// �g�r�a�t�B���^�[( 0:RGB to HSI  1:HSI to RGB  2:HSB �� HLock )
	int						MonoPS ;								// ���m�g�[���t�B���^�[
	int						InvertPS ;								// �K�����]�t�B���^�[
	int						LevelPS ;								// ���x���␳�t�B���^�[
	int						GammaTex ;								// �K���}�␳�Ɏg�p����摜
	float					PrevGamma ;								// �O��̃K���}�t�B���^�̍ۂ̃K���}�l
	int						TwoColorPS ;							// �Q�l���t�B���^�[
	int						GradientMapPS[ 2 ] ;					// �O���f�[�V�����}�b�v�t�B���^�[
	int						PreMulAlphaPS ;							// ��Z�ς݃A���t�@�摜�쐬�p�t�B���^�[

	int						BasicBlendPS[ 14 ] ;					// ��{�I�ȃu�����h�t�B���^�[
	int						RgbaMixBasePS ;							// RGBAMix�u�����h��{
	int						RgbaMixSRGBB[ 4 ] ;						// RGBAMix�u�����h�� A ���� BRGBA �̂S��
	int						RgbaMixSRRRB[ 4 ][ 4 ] ;				// RGBAMix�u�����h�� SYYY BX �̂P�U�� [ Y ][ X ]
	int						RgbaMixS[ 4 ][ 4 ][ 4 ][ 4 ] ;			// RGBAMix�u�����h�� S �����̑g�ݍ��킹256��[ R ][ G ][ B ][ A ]
} ;

#endif // DX_NON_FILTER


// �V�F�[�_�[�萔�̈�̎g�p�̈���\����
struct SHADERCONST_ONE_USEAREA
{
	WORD					Start ;									// �g�p�̈�̊J�n�ԍ�
	WORD					EndPlusOne ;							// �g�p�̈�̏I���ԍ��{�P
} ;

// �V�F�[�_�[�萔�g�p�̈���\����
struct SHADERCONSTANT_USEAREA
{
	SHADERCONST_ONE_USEAREA	AreaInfo[ 256 ] ;						// �g�p�̈���
	int						AreaInfoNum ;							// �g�p�̈���̐�
	int						TotalSize ;								// �Ǘ�����̈�̃T�C�Y
} ;

// �V�F�[�_�[�萔���\����
struct SHADERCONSTANTINFO
{
	SHADERCONSTANT_USEAREA	UseArea ;								// ���[�U�[�p���_�V�F�[�_�[�萔�̎g�p�̈���
	int						UnitSize ;								// �f�[�^�������̃T�C�Y

	union
	{
		BYTE					Data[ 256 * 16 ] ;					// �T�C�Y�ۏؗp�f�[�^

		FLOAT4					Float4[ 256 ] ;						// ���[�U�[�p���_�V�F�[�_�[ float �^�萔
		INT4					Int4[ 16 ] ;						// ���[�U�[�p���_�V�F�[�_�[ int �^�萔
		BOOL					Bool[ 16 ] ;						// ���[�U�[�p���_�V�F�[�_�[ BOOL �^�萔
	} ;
} ;

// �V�F�[�_�[�萔���Z�b�g�\����
struct SHADERCONSTANTINFOSET
{
	int						IsApply[ DX_SHADERCONSTANTSET_NUM ] ;			// �萔����K�p���邩�ǂ���( TRUE:�K�p����  FALSE:�K�p���Ȃ� )
	int						ApplyMask ;										// �K�p�}�X�N( DX_SHADERCONSTANTSET_MASK_LIB | DX_SHADERCONSTANTSET_MASK_LIB_SUB �� )
	SHADERCONSTANTINFO		Info[ DX_SHADERCONSTANTTYPE_NUM ][ DX_SHADERCONSTANTSET_NUM ] ;				// �萔������
	BYTE					UseMap[ DX_SHADERCONSTANTTYPE_NUM ][ DX_SHADERCONSTANTSET_NUM ][ 256 ] ;	// �萔�g�p�}�b�v

	SHADERCONSTANTINFO		FixInfo[ DX_SHADERCONSTANTTYPE_NUM ] ;			// ���ۂɃV�F�[�_�[�ɓK�p����Ă���萔���

	BYTE					SetMap[ DX_SHADERCONSTANTTYPE_NUM ][ 256 ] ;	// �V�F�[�_�[�萔�̎g�p���Z�b�g�}�b�v( DX_SHADERCONSTANTSET_LIB ���A0xff ���g�p )
} ;

// ���[�U�[�̕`��ݒ���\����
struct USERRENDERINFO
{
	int						SetTextureGraphHandle[ 20 ] ;			// ���[�U�[�ݒ�̊e�X�e�[�W�̃e�N�X�`��
	int						SetRenderTargetGraphHandle[ 4 ] ;		// ���[�U�[�ݒ�̊e�����_�����O�^�[�Q�b�g

	int						SetVertexShaderHandle ;					// ���[�U�[�ݒ�Ŏg�p���钸�_�V�F�[�_�[
	int						SetPixelShaderHandle ;					// ���[�U�[�ݒ�Ŏg�p����s�N�Z���V�F�[�_�[
} ;


// �n�[�h�E�G�A�A�N�Z�����[�^���g�p����O���t�B�b�N�X�����Ŏg�p������̍\����
struct GRAPHICS_HARDDATA
{
	int						NotUseDirect3D9Ex ;						// Direct3D9Ex ���g�p���Ȃ����ǂ���
	int						UseMultiThread ;						// �}���`�X���b�h�Ή��t���O���g�����ǂ���
	int						ValidAdapterNumber ;					// UseAdapterNumber ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	int						UseAdapterNumber ;						// �g�p����f�o�C�X�A�_�v�^�ԍ�
	int						NonUseVertexHardwareProcess ;			// �����I�ɒ��_���Z���n�[�h�E�G�A�ŏ������Ȃ����ǂ���( TRUE:�������Ȃ�  FALSE:�������� )
	int						VertexHardwareProcess ;					// ���_���Z���n�[�h�E�G�A�ŏ������邩�ǂ���( TRUE:��������  FALSE:�������Ȃ� )
	int						ValidVertexShader ;						// ���_�V�F�[�_�[���g�p�\���ǂ���( TRUE:�g�p�\  FALSE:�s�\ )
	int						ValidPixelShader ;						// �s�N�Z���V�F�[�_�[���g�p�\���ǂ���( TRUE:�g�p�\  FALSE:�s�\ )
	int						DisableAeroFlag ;						// Aero �𖳌��ɂ��邩�ǂ����̃t���O( TRUE:�����ɂ���  FALSE:�����ɂ��Ȃ� )
	DWORD					NativeVertexShaderVersion ;				// �G�~�����[�V���������̒��_�V�F�[�_�[�̃o�[�W����

	int						UseBaseVertexShaderIndex ;				// �g�p���钸�_�V�F�[�_�[�̃��C�g�E�t�H�O�E�t�H���V�F�[�f�B���O�̗L���̂ݐݒ肵���l
	int						UseBasePixelShaderIndex ;				// �g�p����s�N�Z���V�F�[�_�[�̃��C�g�E�t�H���V�F�[�f�B���O�̗L���̂ݐݒ肵���l

	D_D3DMULTISAMPLE_TYPE	FSAAMultiSampleType ;					// FSAA�p�}���`�T���v�����O�^�C�v
	int						FSAAMultiSampleQuality ;				// FSAA�p�}���`�T���v�����O�N�I���e�B
	int						MipMapCount ;							// �����ō쐬����~�b�v�}�b�v�̐�( -1:�ő僌�x���܂ō쐬���� )
	int						FullScreenEmulation320x240 ;			// �t���X�N���[�����[�h�� 320x240 ���w�肳��Ă��邩�ǂ���( TRUE:�w�肳��Ă���  FALSE:�w�肳��Ă��Ȃ� )
	int						UseRenderTargetLock ;					// �`���T�[�t�F�X�̃��b�N���s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )

	int						ValidAdapterInfo ;						// �A�_�v�^�̏�񂪗L�����ǂ���( TRUE:�L��  FALSE:���� )
	int						AdapterInfoNum ;						// �A�_�v�^���̐�
	D_D3DADAPTER_IDENTIFIER9	AdapterInfo[ MAX_DEVICE_LISTUP ] ;	// �A�_�v�^�̏��

	D_D3DFORMAT				ScreenFormat ;										// ��ʃJ���[�t�H�[�}�b�g
	D_D3DFORMAT				TextureFormat[ DX_GRAPHICSIMAGE_FORMAT_3D_NUM ] ;	// �e�N�X�`���t�H�[�}�b�g
	D_D3DFORMAT				MaskColorFormat ;									// �}�X�N�J���[�o�b�t�@�p�t�H�[�}�b�g
	D_D3DFORMAT				MaskAlphaFormat ;									// �}�X�N�A���t�@�`�����l���p�t�H�[�}�b�g
	D_D3DFORMAT				ZBufferFormat ;										// �y�o�b�t�@�t�H�[�}�b�g

	IMAGEDATA2_SYSMEMTEXTURE SysMemTexture[ SYSMEMTEXTURE_NUM ] ;	// ��Ǘ��e�N�X�`���ւ̃f�[�^�]���p�V�X�e���������z�u�e�N�X�`��
	int						SysMemTextureInitNum ;					// �������ς݂̔�Ǘ��e�N�X�`���̐�

	int						UserMaxTextureSize ;					// ���[�U�[�w��̃e�N�X�`���ő�T�C�Y
	int						NotUseDivFlag ;							// �摜�������s��Ȃ����ǂ���( TRUE:�s��Ȃ�  FALSE:�s�� )
	int						UseOldDrawModiGraphCodeFlag ;			// �ȑO�� DrawModiGraph �֐��R�[�h���g�p���邩�ǂ����̃t���O

	int						FlipRunScanline[ 2 ] ;					// ScreenFlip �����s�����Ƃ��̃X�L�������C���l
	DWORD					FlipRunTime[ 2 ] ;						// ScreenFlip �����s�����Ƃ��� timeGetTime �̒l
	int						FlipSkipFlag ;							// Flip�X�L�b�v�����A�t���O( TRUE:�X�L�b�v��  FALSE:�X�L�b�v���ł͂Ȃ� )

	int						ValidTexTempRegFlag ;					// �e�N�X�`���X�e�[�W�̃e���|�������W�X�^���g�p�ł��邩�ǂ����̃t���O

	DX_DIRECT3DSURFACE9		*BackBufferSurface ;					// �f�o�C�X�����o�b�N�o�b�t�@�T�[�t�F�X
	DX_DIRECT3DSURFACE9		*SubBackBufferSurface ;					// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����`��\�T�[�t�F�X
	DX_DIRECT3DSURFACE9		*ZBufferSurface ;						// ���C���Ŏg�p����y�o�b�t�@
	int						ZBufferSizeX, ZBufferSizeY ;			// �y�o�b�t�@�T�[�t�F�X�̃T�C�Y
	int						UserZBufferSizeSet ;					// �O������y�o�b�t�@�T�C�Y�̎w�肪���������ǂ���

	IMAGEFORMATDESC			*DrawPrepFormat ;						// �O�� DrawPreparation �ɓ������Ƃ��� Format �p�����[�^
	DX_DIRECT3DTEXTURE9		*DrawPrepTexture ;						// �O�� DrawPreparation �ɓ������Ƃ��� Texture �p�����[�^
	int						DrawPrepParamFlag ;						// �O�� DrawPreparation �ɓ������Ƃ��� ParamFlag �p�����[�^
	int						DrawPrepAlwaysFlag ;					// �K�� DrawPreparation ���s�����ǂ����̃t���O

	D_D3DCAPS9				DeviceCaps ;							// �f�o�C�X���
	int						TextureSizePow2 ;						// �e�N�X�`���̃T�C�Y���Q�̂���ł���K�v�����邩�ǂ���
	int						TextureSizeNonPow2Conditional ;			// �����t�Ńe�N�X�`���̃T�C�Y���Q�̂���łȂ��Ă����v���ǂ���
	int						MaxTextureSize ;						// �ő�e�N�X�`���T�C�Y
	int						ValidDestBlendOp ;						// D3DBLENDOP_ADD �ȊO���g�p�\���ǂ���( TRUE:�g�p�\  FALSE:�g�p�s�\ )
	int						WhiteTexHandle ;						// 8x8�̔����e�N�X�`���̃n���h��
	int						MaxPrimitiveCount ;						// ��x�ɕ`��ł���v���~�e�B�u�̍ő吔

	DX_DIRECT3DSURFACE9		*TargetSurface[DX_RENDERTARGET_COUNT] ;	// �`��Ώۂ̃T�[�t�F�X
	int						RenderTargetNum ;						// �����ɐݒ�ł��郌���_�����O�^�[�Q�b�g�̐�

	D_D3DVIEWPORT9			Viewport ;								// �r���[�|�[�g���
	RECT					ScissorRect ;							// �V�U�[��`
	int						ScissorTestEnable ;						// �V�U�[��`�̗L���A����( TRUE:�L�� FALSE:���� )

	BYTE					*VertexBufferPoint[2][3] ;				// �e���_�o�b�t�@�ւ̃|�C���^( [ �R�c���_���ǂ��� ][ ���_�^�C�v ] )
	int						Use3DVertex ;							// �R�c���_���g�p���Ă��邩�ǂ���( 1:�g�p���Ă���  0:�g�p���Ă��Ȃ� )
	int						VertexNum ; 							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�̐�
	int						VertexType ;							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�f�[�^( 0:�e�N�X�`���Ȃ�  1:�e�N�X�`������  2:�u�����h�e�N�X�`������ )
	D_D3DPRIMITIVETYPE		PrimitiveType ;							// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�f�[�^�̃v���~�e�B�u�^�C�v

	float					BlendTextureWidth ;						// �u�����h�e�N�X�`���̕�
	float					BlendTextureHeight ;					// �u�����h�e�N�X�`���̍���
	float					InvBlendTextureWidth ;					// �u�����h�e�N�X�`���̕��̋t��
	float					InvBlendTextureHeight ;					// �u�����h�e�N�X�`���̍����̋t��
	DWORD					DiffuseColor ;							// �f�B�t���[�Y�J���[

	int						GaussPass1_VS ;							// �K�E�X�t�B���^�V�F�[�_�[�̂P�p�X�ڂ̒��_�V�F�[�_�[
	int						GaussPass1_PS ;							// �K�E�X�t�B���^�V�F�[�_�[�̂P�p�X�ڂ̃s�N�Z���V�F�[�_�[
	int						GaussPass2_VS ;							// �K�E�X�t�B���^�V�F�[�_�[�̂Q�p�X�ڂ̒��_�V�F�[�_�[
	int						GaussPass2_PS ;							// �K�E�X�t�B���^�V�F�[�_�[�̂Q�p�X�ڂ̃s�N�Z���V�F�[�_�[

	BYTE					*VertexBufferNextAddress ;				// ���̃f�[�^���i�[���ׂ����_�o�b�t�@���̃A�h���X
	BYTE					NoTexVertexBuffer[     D3DDEV_NOTEX_VERTBUFFERSIZE     ] ;	// �e�N�X�`�����g�p���Ȃ����_�o�b�t�@
	BYTE					TexVertexBuffer[       D3DDEV_TEX_VERTBUFFERSIZE       ] ;	// �e�N�X�`�����g�p���钸�_�o�b�t�@
	BYTE					BlendTexVertexBuffer[  D3DDEV_BLENDTEX_VERTBUFFERSIZE  ] ;	// �u�����h�e�N�X�`�����g�p���钸�_�o�b�t�@
	BYTE					Vertex3DBuffer[	       D3DDEV_NOTEX_3D_VERTBUFFERSIZE  ] ;	// �R�c�p���_�o�b�t�@

	DX_DIRECT3DTEXTURE9		*RenderTexture ;					// �`�掞�Ɏg�p����e�N�X�`���[
	DX_DIRECT3DTEXTURE9		*BlendTexture ;						// �`�掞�ɕ`��e�N�X�`���[�ƃu�����h���郿�`�����l���e�N�X�`���[
#ifndef DX_NON_MODEL
	DX_DIRECT3DVOLUMETEXTURE9	*RGBtoVMaxRGBVolumeTexture ;	// RGB�J���[���P�x���ő�ɂ���RGB�l�ɕϊ����邽�߂̃{�����[���e�N�X�`��
#endif // DX_NON_MODEL

	DIRECT3DBLENDINFO		BlendInfo ;							// Direct3DDevice �̃u�����h�Ɋ֌W����ݒ�l
	float					FactorColorPSConstantF[ 4 ] ;		// �s�N�Z���V�F�[�_�[���g�����c�w���C�u�����W�������p�� FactorColor �̒l
	DIRECT3DBLENDINFO		UserBlendInfo ;						// Direct3D �Ǘ��v���O�����O����ݒ肳���u�����h�Ɋ֌W����ݒ�l
	int						UserBlendInfoFlag ;					// UserBlendInfo ���L�����ǂ����t���O( TRUE:�L��  FALSE:���� )
	int						UserBlendInfoTextureStageIsTextureAndTextureCoordOnlyFlag ;	// UserBlendInfo.TextureStageInfo �̒��ŗL���ȃp�����[�^�� Texture �� TextureCoordIndex �������ǂ���( TRUE:���̒ʂ�  FALSE:�Ⴄ )

	int						DrawMode ;							// �`�惂�[�h
	int						MaxAnisotropy ;						// �ő�ٕ���
	int						MaxAnisotropyDim[ 8 ] ;				// �e�T���v���̍ő�ٕ���
	DX_D3DTEXFILTER_TYPE	MagFilter[ 8 ] ;					// �e�T���v���̊g��t�B���^
	DX_D3DTEXFILTER_TYPE	MinFilter[ 8 ] ;					// �e�T���v���̏k���t�B���^
	DX_D3DTEXFILTER_TYPE	MipFilter[ 8 ] ;					// �e�T���v���̃~�b�v�}�b�v�t�B���^
	int						EnableZBufferFlag ;					// �y�o�b�t�@�̗L���t���O
	int						WriteZBufferFlag ;					// �y�o�b�t�@�̍X�V���s�����A�t���O
	int						ZBufferCmpType ;					// �y�l�̔�r���[�h
	int						ZBias ;								// �y�o�C�A�X
	int						TextureTransformUse[ 8 ] ;				// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	MATRIX					TextureTransformMatrix[ 8 ] ;			// �e�N�X�`�����W�ϊ��s��
	int						TextureTransformMatrixDirectChange ;	// �e�N�X�`�����W�ϊ��s��𒼐ڕύX���ꂽ���ǂ���( TRUE:���ꂽ  FALSE:����ĂȂ� )

	int						NormalizeNormals ;					// �@���������K�����s�����ǂ���
	int						ShadeMode ;							// �V�F�[�f�B���O���[�h
	int						FillMode ;							// �t�B�����[�h
	int						CullMode ;							// �J�����O���[�h
	int						TexAddressModeU[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�t
	int						TexAddressModeV[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�u
	int						TexAddressModeW[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�v
	int						FogEnable ;							// �t�H�O���L�����ǂ���( TRUE:�L��  FALSE:���� )
	int						FogMode ;							// �t�H�O���[�h
	DWORD					FogColor ;							// �t�H�O�J���[
	float					FogStart, FogEnd ;					// �t�H�O�J�n�A�h���X�ƏI���A�h���X
	float					FogDensity ;						// �t�H�O���x
	int						PerspectiveFlag ;					// �p�[�X�y�N�e�B�u�␳�L���t���O

	int						LightFlag ;							// ���C�g���g�p���邩�t���O
	int						LightEnableMaxIndex ;				// �L���ȃ��C�g�̍ő�C���f�b�N�X
	int						LightEnableFlag[ 256 ] ;			// ���C�g���L�����ǂ����t���O( TRUE:�L��  FALSE:���� )
	LIGHT					LightParam[ 256 ] ;					// ���C�g�̃p�����[�^

	COLOR					GlobalAmbientLightColor ;			// �O���[�o���A���r�G���g���C�g�J���[
	MATERIAL				Material ;							// �f�o�C�X�ɃZ�b�g����Ă���}�e���A��
	int						MaterialUseVertexDiffuseColor ;		// ���_�̃f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�Ƃ��Ďg�p���邩�ǂ���
	int						MaterialUseVertexSpecularColor ;	// ���_�̃X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ���
	int						UseSpecular ;						// �X�y�L�������g�p���邩�ǂ���

	int						UseDiffuseRGBColor ;				// �f�B�t���[�Y�J���[�̂q�f�a�l���g�p���邩�A�t���O
	int						UseDiffuseAlphaColor ;				// �f�B�t���[�Y�J���[�̃��l���g�p���邩�A�t���O
	int						BeginSceneFlag ;					// BeginScene �����s���Ă��邩�ǂ���

	int						IgnoreGraphColorFlag ;				// �`�悷��摜�̐F�����𖳎����邩�ǂ����̃t���O

	int						BlendMode ;							// �u�����h���[�h
	int						BlendGraphType ;					// �u�����h�摜�^�C�v
	int						BlendGraphFadeRatio ;				// �u�����h�摜�̃t�F�[�h�p�����[�^
	int						BlendGraphBorderParam ;				// �u�����h�摜�̋��E�p�����[�^(�O(�u�����h�摜�̉e���O)�@���@(�u�����h�摜�̉e�����Ȃ�)�@���@�P�Q�W(�u�����h�摜�̉e���P�O�O��)�@���@(�u�����h�摜�̉e���𒴂��Ĕ�`�敔����������)�@���Q�T�T(�S���`�悳��Ȃ�) )
	int						BlendGraphBorderRange ;				// �u�����h�摜�̋��E��(�O�`�Q�T�T�@�����`�L���@�������S�i�K)
	int						AlphaChannelValidFlag ;				// ���`�����l���L���t���O

	int						AlphaTestMode ;						// �A���t�@�e�X�g���[�h
	int						AlphaTestParam ;					// �A���t�@�e�X�g�p�����[�^

	int						AlphaTestValidFlag ;				// ���e�X�g�L���t���O( Func �͕K�� D_D3DCMP_GREATEREQUAL )
	int						ChangeBlendParamFlag ;				// �u�����h�ݒ�Ɋւ�镔���̕ύX�����������A�t���O
	int						ChangeTextureFlag ;					// �e�N�X�`�����ύX���ꂽ���A�t���O
	int						BlendMaxNotDrawFlag ;				// �u�����h�l���ő�ł��邱�Ƃɂ��`����s��Ȃ����ǂ����A�t���O
	int						EdgeFontDrawFlag ;					// ���t���t�H���g��`�悷�邩�ǂ����̃t���O


	int						DrawScreenBufferLockFlag ;			// �o�b�N�o�b�t�@�����b�N���Ă��邩�ǂ����t���O
	DX_DIRECT3DSURFACE9		*DrawScreenBufferLockSMSurface ;	// �o�b�N�o�b�t�@�����b�N�����ۂɒ��ڃ��b�N�ł��Ȃ��ꍇ�Ɏg�p����T�[�t�F�X�̃|�C���^
	DX_DIRECT3DSURFACE9		*DrawScreenBufferLockSurface ;		// ���b�N�����o�b�N�o�b�t�@

	void					(*DeviceRestoreCallbackFunction)( void *Data ) ;	// �f�o�C�X���X�g���畜�A�����Ƃ��ɌĂԊ֐�
	void					*DeviceRestoreCallbackData ;		// �f�o�C�X���X�g���畜�A�����Ƃ��ɌĂԊ֐��ɓn���|�C���^

	void					(*DeviceLostCallbackFunction)( void *Data ) ;	// �f�o�C�X���X�g���畜�A����O�ɌĂԊ֐�
	void					*DeviceLostCallbackData ;			// �f�o�C�X���X�g���畜�A����O�ɌĂԊ֐��ɓn���|�C���^

	int						UseShader ;							// �v���O���}�u���V�F�[�_�[���g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	int						NormalDraw_NotUseShader ;			// �ʏ�`��ɃV�F�[�_�[���g�p���Ȃ����ǂ���( TRUE:�g�p���Ȃ�  FALSE:�g�p���� )
#ifndef DX_NON_FILTER
	int						ValidRenderTargetInputTexture ;		// �`������̓e�N�X�`���Ƃ��Ďg�p�ł��邩�ǂ���( TRUE:�g�p�ł���  FALSE:�g�p�ł��Ȃ� )
#endif // DX_NON_FILTER

	DX_DIRECT3DVERTEXSHADER9		*SetVS ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă��钸�_�V�F�[�_�[
	DX_DIRECT3DPIXELSHADER9			*SetPS ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă���s�N�Z���V�F�[�_�[
	int								NormalPS ;					// �ʏ�`��p�s�N�Z���V�F�[�_�[���Z�b�g����Ă��邩�ǂ���
	DX_DIRECT3DVERTEXDECLARATION9	*SetVD ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă��钸�_�V�F�[�_�錾
	DWORD							SetFVF ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă��� FVF �R�[�h
	DX_DIRECT3DVERTEXBUFFER9		*SetVB ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă��钸�_�o�b�t�@
	DX_DIRECT3DINDEXBUFFER9			*SetIB ;					// ���� Direct3DDevice9 �ɃZ�b�g���Ă���C���f�b�N�X�o�b�t�@

	// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`���Ȃ� )
	// [ �������( 0:�Ȃ�  1:��Z�u�����h�p  2:RGB���]  3:RGB�S�{ ) ]
	DX_DIRECT3DPIXELSHADER9          *BaseNoneTexPixelShader[ 4 ] ;

	// �Œ�@�\�p�C�v���C���݊��̃V�F�[�_�[( �e�N�X�`������ )
	// [ �u�����h�摜�Ƃ̃u�����h�^�C�v( 0:�Ȃ�  1:DX_BLENDGRAPHTYPE_NORMAL  2:DX_BLENDGRAPHTYPE_WIPE  3:DX_BLENDGRAPHTYPE_ALPHA ) ]
	// [ �������( 0:�Ȃ�  1:��Z�u�����h�p  2:RGB���]  3:RGB�S�{ ) ]
	// [ �e�N�X�`��RGB����( 0:�������Ȃ�  1:�������� ) ]
	// [ �e�N�X�`��Alpha����( 0:�������Ȃ�  1:�������� ) ]
	DX_DIRECT3DPIXELSHADER9          *BaseUseTexPixelShader[ 4 ][ 4 ][ 2 ][ 2 ] ;

	// �}�X�N�����p�̃V�F�[�_�[
	DX_DIRECT3DPIXELSHADER9          *MaskEffectPixelShader ;

#ifndef DX_NON_MODEL

	// ���_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O�̗֊s���̕`�悩�ǂ���( 0:�ʏ�`��  1:�֊s���̕`�� ) ]
	// [ ���C�e�B���O�v�Z�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �t�H���V�F�[�f�B���O�̗L��( 0:���� 1:�L�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	// [ ���C�g0�^�C�v ]
	// [ ���C�g1�^�C�v ]
	// [ ���C�g2�^�C�v ]
	// [ �f�B�t���[�Y�J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]
	DX_DIRECT3DVERTEXSHADER9         *DefaultVertexShader[ 2 ][ 2 ][ 3 ][ 2 ][ 2 ][ 4 ][ 4 ][ 4 ][ 4 ][ 2 ][ 2 ][ 2 ] ;

	// �s�N�Z���V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O���ǂ���( 0:�g�D�[�������_�����O�ł͂Ȃ�  1:�g�D�[�������_�����O  2:�g�D�[�������_�����O Type 2 ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖��� or �g�D�[�������_�����O�ł͂Ȃ�   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ ���C�e�B���O�v�Z�̗L��( 0:���� 1:�L�� ) ]
	// [ �X�y�L�����}�b�v ( 0:���� 1:���� ) ]
	// [ �t�H���V�F�[�f�B���O( 0:���� 1:�L�� ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g0�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ ���C�g1�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ ���C�g2�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ �f�B�t���[�Y�J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]
	DX_DIRECT3DPIXELSHADER9          *DefaultPixelShader[ 3 ][ 3 ][ 2 ][ 2 ][ 2 ][ 2 ][ 2 ][ 2 ][ 3 ][ 3 ][ 3 ][ 2 ][ 2 ][ 2 ] ;

	// ���_�V�F�[�_�錾( ���X�g�͔z��̍����� )
	// [ �o���v�}�b�v���t�����ǂ���( 1:�o���v�}�b�v�t�� 0:�t���ĂȂ� ) ]
	// [ �X�L�j���O���b�V�����ǂ���( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V�� 2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ UV�̐� ]
	DX_DIRECT3DVERTEXDECLARATION9 *DefaultVertexDeclaration[ 2 ][ 3 ][ 9 ] ;

#endif // DX_NON_MODEL

	int						InitializeFlag ;					// ���̃t���O�������Ă��鎞�͌��݂̃X�e�[�^�X�ƕύX
																// �w��̃X�e�[�^�X�������ł��K�����s�����
	int						DisplayModeNum ;					// �ύX�\�ȃf�B�X�v���C���[�h�̐�
	DISPLAYMODEDATA			*DisplayMode ;						// �f�B�X�v���C���[�h���X�g

	SHADERCONSTANTINFOSET	ShaderConstantInfo ;				// �V�F�[�_�[�̒萔���

	DX_DIRECT3DVERTEXDECLARATION9	*UserShaderDeclaration[ DX_VERTEX_TYPE_NUM ] ;	// ���[�U�[�V�F�[�_���[�h�Ŏg�p���钸�_�f�[�^�t�H�[�}�b�g

	USERRENDERINFO			UserShaderRenderInfo ;				// SetUseTextureToShader �Őݒ肳�ꂽ�e�X�e�[�W�̃e�N�X�`������A���[�U�[�ݒ�̃V�F�[�_�[�萔���Ȃ�

#ifndef DX_NON_FILTER
	int						WorkDrawValidGrHandle[ 16 ][ 2 ] ;	// �t�B���^�[������Ɨp�`��\�e�N�X�`��[ �Q�̂��� ][ ��Ɨp�Q�� ]
	SHADERCODE_HANDLE		ShaderCode ;						// ���C�u�������p�ӂ���V�F�[�_�[�R�[�h
#endif // DX_NON_FILTER
} ;

// �\�t�g�E�G�A�����_�����O�Ŏg�p������̍\����
struct GRAPHICS_SOFTDATA
{
	MEMIMG					MainBufferMemImg ;					// ���C����ʗp MEMIMG
	MEMIMG					FontScreenMemImgNormal ;			// �������`��Ȃǂ̎��Ɏg���t�H���g�p MEMIMG ( �A���t�@�Ȃ� )
	MEMIMG					FontScreenMemImgAlpha ;				// �������`��Ȃǂ̎��Ɏg���t�H���g�p MEMIMG ( �A���t�@�� )
	MEMIMG					*TargetMemImg ;						// �`��Ώۂ� MEMIMG
	MEMIMG					*BlendMemImg ;						// �u�����h�`��p MEMIMG
} ;

// �O���t�B�b�N�����Ǘ��f�[�^�\����
struct GRAPHICSMANAGE2
{
	int						InitializeFlag ;						// �������t���O

	int						MainScreenSizeX, MainScreenSizeY ;		// ���C����ʂ̃T�C�Y
	int						MainScreenSizeX_Result, MainScreenSizeY_Result ;	// GetDrawScreenSize �̕Ԃ�l�ɂȂ�T�C�Y
	int						MainScreenColorBitDepth ;				// ���C����ʂ̃J���[�r�b�g�[�x
	int						MainScreenRefreshRate ;					// ���C����ʂ̃��t���b�V�����[�g
	RECT					OriginalDrawRect ;						// �E�C���h�E�̈ʒu�ɂ���ĉ��ς����O�̎g�p�҂��Ӑ}���鐳�����`���`

	int						ValidGraphDisplayArea ;					// GraphDisplayArea �ɗL���Ȓl�������Ă��邩�ǂ���
	RECT					GraphDisplayArea ;						// �\��ʂɓ]�����闠��ʂ̗̈�
	RECT					LastCopySrcRect ;						// �Ō�Ƀt�B�b�g�]�������Ƃ��̃R�s�[����`
	RECT					LastCopyDestRect ;						// �Ō�Ƀt�B�b�g�]�������Ƃ��̃R�s�[���`
	int						EnableBackgroundColor;					// �o�b�N�O���E���h�h��ׂ��p�J���[���L�����ǂ����̃t���O
	int						BackgroundRed, BackgroundGreen, BackgroundBlue;	// �o�b�N�O���E���h�h��ׂ��p�J���[

	LONGLONG				VSyncWaitTime ;							// �O��u�r�x�m�b�҂������Ă��玟�Ƀ`�F�b�N����܂łɑ҂���
	LONGLONG				VSyncTime ;								// �O��u�r�x�m�b�҂�����������

	int						ValidHardWare ;							// �n�[�h�E�G�A�`�悪�\���ǂ���( TRUE:�\  FALSE:�s�\ )
	int						NotUseHardWare ;						// �n�[�h�E�G�A�`��̋@�\���g�p���Ȃ����ǂ���( TRUE:�g�p���Ȃ�  FALSE:�g�p���� )
	int						ChangeScreenModeNotGraphicsSystemFlag ;	// ��ʃ��[�h�̕ύX���ɉ摜�n���h�����폜���Ȃ����ǂ���( TRUE:���Ȃ�  FALSE:���� )


	int						ShaderInitializeFlag ;					// �V�F�[�_�[�o�C�i���̃Z�b�g�A�b�v���������Ă��邩�ǂ����̃t���O( TRUE:�������Ă���  FALSE:�������Ă��Ȃ� )

	DXARC					BaseShaderBinDxa ;						// ��{�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�\����
	void					*BaseShaderBinDxaImage ;				// ��{�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�̃o�C�i���C���[�W

#ifndef DX_NON_FILTER
	DXARC					FilterShaderBinDxa ;					// �t�B���^�[�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�\����
	void					*FilterShaderBinDxaImage ;				// �t�B���^�[�V�F�[�_�[�I�u�W�F�N�g�t�@�C���c�w�`�̃o�C�i���C���[�W

	void					*RGBAMixS_ShaderPackImage ;				// RGBAMix �� S �����̑g�ݍ��킹�Q�T�U�̃V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// RGBAMix �� S �����̑g�ݍ��킹�Q�T�U�̃V�F�[�_�[[ R ][ G ][ B ][ A ]
	void					*RGBAMixS_ShaderAddress[ 4 ][ 4 ][ 4 ][ 4 ] ;
	short					RGBAMixS_ShaderSize[ 4 ][ 4 ][ 4 ][ 4 ] ;
#endif // DX_NON_FILTER


#ifndef DX_NON_MODEL
	void					*ModelShaderPackImage ;					// �R�c���f���p�V�F�[�_�[�p�b�P�[�W�o�C�i���C���[�W

	// ���_�V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O�̗֊s���̕`�悩�ǂ���( 0:�ʏ�`��  1:�֊s���̕`�� ) ]
	// [ ���C�e�B���O�v�Z�̗L��( 0:���� 1:�L�� ) ]
	// [ ���b�V���^�C�v( 0:���̃��b�V�� 1:4�{�[�����X�L�j���O���b�V��  2:8�{�[�����X�L�j���O���b�V�� ) ]
	// [ �t�H���V�F�[�f�B���O�̗L��( 0:���� 1:�L�� ) ]
	// [ �o���v�}�b�v�̗L��( 0:���� 1:�L�� ) ]
	// [ �t�H�O�^�C�v ]
	// [ ���C�g0�^�C�v ]
	// [ ���C�g1�^�C�v ]
	// [ ���C�g2�^�C�v ]
	// [ �f�B�t���[�Y�J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]
	void					  *DefaultVertexShaderAddress[ 2 ][ 2 ][ 3 ][ 2 ][ 2 ][ 4 ][ 4 ][ 4 ][ 4 ][ 2 ][ 2 ][ 2 ] ;

	// �s�N�Z���V�F�[�_�[( ���X�g�͔z��̍����� )
	// [ �g�D�[�������_�����O���ǂ���( 0:�g�D�[�������_�����O�ł͂Ȃ�  1:�g�D�[�������_�����O  2:�g�D�[�������_�����O type 2 ) ]
	// [ �g�D�[�������_�����O�̃X�t�B�A�}�b�v�̗L���ƃu�����h�^�C�v( 0:�X�t�B�A�}�b�v�͖��� or �g�D�[�������_�����O�ł͂Ȃ�   1:MV1_LAYERBLEND_TYPE_MODULATE  2:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ �g�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_MODULATE ) ]
	// [ �g�D�[�������_�����O�̃X�y�L�����O���f�[�V�����̃u�����h�^�C�v( 0:MV1_LAYERBLEND_TYPE_TRANSLUCENT or �g�D�[�������_�����O�ł͂Ȃ�  1:MV1_LAYERBLEND_TYPE_ADDITIVE ) ]
	// [ ���C�e�B���O�v�Z�̗L��( 0:���� 1:�L�� ) ]
	// [ �X�y�L�����}�b�v ( 0:���� 1:���� ) ]
	// [ �t�H���V�F�[�f�B���O( 0:���� 1:�L�� ) ]
	// [ �o���v�}�b�v ( 0:�Ȃ� 1:���� ) ]
	// [ ���C�g0�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ ���C�g1�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ ���C�g2�^�C�v ( 0:�Ȃ� 1:���� 2:����Ńf�B���N�V���i�� ) ]
	// [ �f�B�t���[�Y�J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����J���[�\�[�X( 0:�}�e���A�� 1:���_ ) ]
	// [ �X�y�L�����̗L��( 0:���� 1:�L�� ) ]
	void					*DefaultPixelShaderAddress[ 3 ][ 3 ][ 2 ][ 2 ][ 2 ][ 2 ][ 2 ][ 2 ][ 3 ][ 3 ][ 3 ][ 2 ][ 2 ][ 2 ] ;

#endif // DX_NON_MODEL

	GRAPHICS_HARDDATA		Hard ;									// �n�[�h�E�F�A�A�N�Z�����[�^���g�p���鏈���ɕK�v�ȏ��
	GRAPHICS_SOFTDATA		Soft ;									// �\�t�g�E�G�A�����_�����O���g�p����ۂɕK�v�ȏ��
} ;

// �������ϐ��錾---------------------------------------------------------------

// �O���t�B�b�N�X�Ǘ��f�[�^�\����
extern GRAPHICSMANAGE2 GraphicsManage2 ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �O���t�B�b�N�֘A�̏������ƌ�n��
extern	int		InitializeGraphics2( void ) ;
extern	int		TerminateGraphics2( void ) ;

extern	void	SetMainScreenSize( int SizeX, int SizeY ) ;									// ���C����ʂ̃T�C�Y�l��ύX����
extern	void	ReleaseDirectXObject( void ) ;												// DirectX �̃I�u�W�F�N�g���������
extern	void	BeginScene( void ) ;														// �r�M���V�[�����s��	
extern	void	EndScene( void ) ;															// �G���h�V�[�����s��	
extern	int		RenderVertexHardware( int ASyncThread = FALSE ) ;							// ���_�o�b�t�@�ɗ��܂������_�f�[�^�������_�����O����
extern	int		SetRenderTargetHardware( DX_DIRECT3DSURFACE9 *TargetSurface, int TargetIndex = 0 ) ;	// �`��Ώۂ̕ύX
extern	int		SetViewportHardwareEasy( int x1, int y1, int x2, int y2 ) ;					// �r���[�|�[�g���Z�b�g����( �ȈՔ� )
extern	int		SetupUseZBuffer( void ) ;													// �ݒ�Ɋ�Â��Ďg�p����y�o�b�t�@���Z�b�g����
extern	int		CreateSubBackBufferSurface( void ) ;										// ScreenCopy �� GetDrawScreen ���������邽�߂Ɏg�p����e���|�����o�b�t�@�̍쐬( 0:����  -1:���s )
extern COLORDATA *GetD3DFormatColorData( D_D3DFORMAT Format ) ;								// D3DFORMAT �̃t�H�[�}�b�g�ɍ��킹���J���[�t�H�[�}�b�g�����擾����
extern	void FASTCALL SetDrawBrightToOneParam( DWORD Bright ) ;								// SetDrawBright �̈��������
extern	void FASTCALL BlendModeSub_Pre( RECT *DrawRect ) ;
extern	void FASTCALL BlendModeSub_Post( RECT *DrawRect ) ;
extern	int		SetUseAutoMipMap( int UseFlag, int MaxLevel = -1 ) ;
extern	int		ChangeGraphMode( int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int ChangeWindowFlag, int RefreshRate ) ;				// ��ʃ��[�h�̕ύX�Q
extern	int		SetD3DDialogBoxMode( int Flag ) ;
#ifndef DX_NON_MODEL
extern	int		SetupVertexShader( int VertexShaderIndex ) ;																// �w��̒��_�V�F�[�_�[���Z�b�g�A�b�v����( TRUE:����  FALSE:���s )
extern	int		SetupPixelShader( int PixelShaderIndex ) ;																	// �w��̃s�N�Z���V�F�[�_�[���Z�b�g�A�b�v����( TRUE:����  FALSE:���s )
extern	int		SetupVertexDeclaration( int BumpMap, int SkinMesh, int UVNum ) ;											// �w��̒��_�f�[�^��`���Z�b�g�A�b�v
#endif // DX_NON_MODEL
extern	int		SetDeviceVertexShaderToHandle( int ShaderHandle ) ;															// �w��̒��_�V�F�[�_�[���f�o�C�X�ɃZ�b�g����
extern	int		SetDevicePixelShaderToHandle( int ShaderHandle ) ;															// �w��̃s�N�Z���V�F�[�_�[���f�o�C�X�ɃZ�b�g����
extern	int		LockDrawScreenBuffer( RECT *LockRect, BASEIMAGE *BaseImage, int TargetScreen = -1, int ReadOnly = TRUE, int TargetScreenTextureNo = 0 ) ;	// �`���o�b�t�@�����b�N����
extern	int		UnlockDrawScreenBuffer( void ) ;																			// �`���o�b�t�@���A�����b�N����
extern	int		SetBlendGraphParamBase( int BlendGraph, int BlendType, va_list ParamList ) ;								// SetBlendGraphParam �̉ϒ������p�����[�^�t��
extern	int		GraphFilterRectBltBase( int IsBlend, int SrcGrHandle, int BlendGrHandle, int DestGrHandle, int BlendRatio, int FilterOrBlendType, int SrcX1, int SrcY1, int SrcX2, int SrcY2, int BlendX, int BlendY, int BlendPosEnable, int DestX, int DestY, va_list ParamList ) ;		// �摜�̃t�B���^�[�t���]�����s��( �ψ������t�� )

extern	int		CreateShaderHandle( void ) ;																				// �V�F�[�_�[�n���h�����쐬����
extern	int		CreateShader_UseGParam( int IsVertexShader, void *Image, int ImageSize, int ImageAfterFree, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;		// �V�F�[�_�[�n���h�����쐬����
extern	int		LoadShader_UseGParam( int IsVertexShader, const TCHAR *FileName, int ASyncLoadFlag = FALSE ) ;				// �V�F�[�_�[�o�C�i�����t�@�C������ǂݍ���

extern	int		InitializeShaderHandle( HANDLEINFO *HandleInfo ) ;															// �V�F�[�_�[�n���h���̏�����
extern	int		TerminateShaderHandle( HANDLEINFO *HandleInfo ) ;															// �V�F�[�_�[�n���h���̌�n��

extern	int		SetupVertexBufferHandle( int VertexBufHandle, int VertexNum, int VertexType /* DX_VERTEX_TYPE_NORMAL_3D �� */ ) ;	// ���_�o�b�t�@�n���h���̃Z�b�g�A�b�v���s��
extern	int		InitializeVertexBufferHandle( HANDLEINFO *HandleInfo ) ;													// ���_�o�b�t�@�n���h���̏�����
extern	int		TerminateVertexBufferHandle( HANDLEINFO *HandleInfo ) ;														// ���_�o�b�t�@�n���h���̌�n��

extern	int		SetupIndexBufferHandle( int IndexBufHandle, int IndexNum, int IndexType /* DX_INDEX_TYPE_16BIT �� */ ) ;	// �C���f�b�N�X�o�b�t�@�n���h���̃Z�b�g�A�b�v���s��
extern	int		InitializeIndexBufferHandle( HANDLEINFO *HandleInfo ) ;														// �C���f�b�N�X�o�b�t�@�n���h���̏�����
extern	int		TerminateIndexBufferHandle( HANDLEINFO *HandleInfo ) ;														// �C���f�b�N�X�o�b�t�@�n���h���̌�n��


// DirectX �֘A�֐�
extern	int		InitializeDirectX() ;									// DirectX �֘A�̏�����( 0:����  -1:���s )
extern	int		TerminateDirectX() ;									// DirectX �֘A�̌�n��

extern	int		CreateDirect3D9DeviceObject() ;							// Direct3DDevice9 �I�u�W�F�N�g�̍쐬( 0:����  -1:���s )

extern	int		SetupDirect3D9Shader() ;								// Direct3D9 �̃V�F�[�_�[�̃Z�b�g�A�b�v���s��( 0:����  -1:���s )
extern	int		TerminateDirect3D9Shader() ;							// Direct3D9 �̃V�F�[�_�[�̌�n��������( 0:����  -1:���s )

extern	int		CreateDirect3D9VertexDeclaration() ;					// Direct3DVertexDeclaration9 �I�u�W�F�N�g�̍쐬( 0:����  -1:���s )
extern	int		TerminateDirect3D9VertexDeclaration() ;					// Direct3DVertexDeclaration9 �I�u�W�F�N�g�̍폜( 0:����  -1:���s )

#ifndef DX_NON_MODEL
extern	int		CreateRGBtoVMaxRGBVolumeTexture() ;						// RGB�J���[���P�x���ő�ɂ���RGB�l�ɕϊ����邽�߂̃{�����[���e�N�X�`�����쐬����( 0:����  -1:���s )
#endif // DX_NON_MODEL

extern	int		CreateDirect3D9ZBufferObject() ;						// �y�o�b�t�@�I�u�W�F�N�g�̍쐬( 0:����  -1:���s )


// �n�[�h�E�G�A�ݒ�֌W�֐�
extern	void	ApplyLibMatrixToHardware( void ) ;						// ��{�f�[�^�ɐݒ肳��Ă���s����n�[�h�E�G�A�ɔ��f����
extern	void	ApplyLigFogToHardware( void ) ;							// ��{�f�[�^�ɐݒ肳��Ă���t�H�O�����n�[�h�E�G�A�ɔ��f����

extern	int		D_SetVertexBlend( int WeightNum ) ;					// �s��u�����h�̐���ݒ肷��( DrawGraph �Ȃǂ��ĂԑO�� 0 �������ɂ��ČĂяo���Ȃ��Ƃ��̌�̕`�悪����ɍs���Ȃ��Ȃ�܂� )
extern	int		D_DrawIndexedPrimitive( void *VertexBuffer9, DWORD VertexStride, DWORD FVFFlag, void *IndexBuffer9, int PrimitiveType, int BaseVertexIndex, DWORD MinIndex, DWORD NumVertices, DWORD StartIndex, DWORD PrimitiveCount ) ;						// Direct3DDevice9->DrawIndexedPrimitive �̃��b�s���O�֐�
extern	int		D_DrawIndexedPrimitiveUP( DWORD FVFFlag, int PrimitiveType, DWORD MinVertexIndex, DWORD NumVertexIndices, DWORD PrimitiveCount, void *pIndexData, D_D3DFORMAT IndexDataFormat, void *pVertexStreamZeroData, DWORD VertexStreamZeroStride ) ;		// Direct3DDevice9->DrawIndexedPrimitiveUP �̃��b�s���O�֐�
extern	int		D_SetLightEnable( int Flag ) ;											// ���C�g��L���ɂ��邩�ǂ������Z�b�g����
extern	int		D_SetLightParam( int No, int EnableFlag, LIGHTPARAM *Param = NULL ) ;	// ���C�g�̃p�����[�^���Z�b�g����
extern	int		D_SetAmbientLight( int r, int g, int b ) ;								// �A���r�G���g���C�g��ݒ肷��
extern	int		D_SetUseSpecular( int UseFlag ) ;										// �X�y�L�������g�p���邩�ǂ�����ݒ肷��
extern	int		D_SetMaterial( MATERIALPARAM *Param ) ;									// �}�e���A���p�����[�^���Z�b�g����
extern	int		D_SetMaterialUseVertexDiffuseColor( int UseFlag ) ;						// ���_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern	int		D_SetMaterialUseVertexSpecularColor( int UseFlag ) ;						// ���_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�Ƃ��Ďg�p���邩�ǂ�����ݒ肷��
extern	int		D_SetShadeMode( int ShadeMode ) ;										// �V�F�[�h���[�h���Z�b�g����
extern	int		D_GetShadeMode( void ) ;													// �V�F�[�h���[�h���擾����
extern	int		D_SetMaxAnisotropy( int TexStage, int MaxAnisotropy ) ;					// �ő�ٕ������Z�b�g����
extern	int		D_SetUseCullingFlag( int Flag ) ;										// �|���S���J�����O�̗L���A�������Z�b�g����
extern	int		D_SetupZBuffer3D( void ) ;												// �R�c�`��p�̂y�o�b�t�@�ݒ���n�[�h�ɔ��f����
extern	int		D_SetupUseVertColor( void ) ;											// ���_�J���[���g�p���邩�ǂ����̐ݒ���n�[�h�ɔ��f����
extern	int		D_SetUseZBufferFlag( int Flag ) ;										// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����
extern	int		D_SetWriteZBufferFlag( int Flag ) ;										// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����
extern	int		D_SetDrawAlphaTest( int TestMode, int TestParam ) ;						// �`�掞�̃A���t�@�e�X�g�̃��[�h���Z�b�g����
extern	int		D_SetZBufferCmpType( int CmpType /* DX_CMP_NEVER �� */ )	;				// �y�l�̔�r���[�h���Z�b�g����
extern	int		D_SetZBias( int Bias ) ;													// �y�o�C�A�X���Z�b�g����
extern	int		D_SetFillMode( int FillMode ) ;												// �t�B�����[�h���Z�b�g����
extern	int		D_SetTextureAddressMode( int Mode /* DX_TEXADDRESS_WRAP �� */, int Stage = -1 ) ;	// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int		D_SetTextureAddressModeUVW( int ModeU, int ModeV, int ModeW, int Stage ) ;			// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int		D_SetTextureAddressTransformMatrix( int Use, MATRIX *Matrix, int Stage = -1 ) ;		// �e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int		D_SetTransformToWorld( MATRIX *Matrix ) ;								// ���[�J�������[���h�s���ύX����
extern	int		D_SetTransformToView( MATRIX *Matrix ) ;									// �r���[�ϊ��p�s����Z�b�g����
extern	int		D_SetTransformToProjection( MATRIX *Matrix ) ;							// ���e�ϊ��p�s����Z�b�g����
extern	int		D_ResetTextureCoord( void ) ;											// �e�X�e�[�W���g�p����e�N�X�`���A�h���X���X�e�[�W�ԍ��Ɠ����ɂ���
extern	int		_SetTransformToProjection( MATRIX *Matrix ) ;								// ���e�ϊ��p�s����Z�b�g����
//extern	int		RenderVertexBuffer( void ) ;							// ���_�o�b�t�@�ɗ��܂������_�f�[�^��f���o��
extern	void	_DrawPreparation( int GrHandle = -1 , int ParamFlag = 0 ) ;										// �`�揀�����s��( ParamFlag �� DRAWPREP_TRANS �� )



extern	int		AddGraphHandle( void ) ;																						// �V�����O���t�B�b�N�n���h�����m�ۂ���
extern	int		SetupGraphHandle_UseGParam( SETUP_GRAPHHANDLE_GPARAM *GParam, int GrHandle, int Width, int Height, int TextureFlag, int AlphaValidFlag, int UsePaletteFlag, int BaseFormat = DX_BASEIMAGE_FORMAT_NORMAL, int MipMapCount = -1, int ASyncThread = FALSE ) ;										// SetupGraphHandle �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		InitializeGraphHandle( HANDLEINFO *HandleInfo ) ;																// �O���t�B�b�N�n���h���̏�����
extern	int		TerminateGraphHandle( HANDLEINFO *HandleInfo ) ;																// �O���t�B�b�N�n���h���̌�n��


extern	int		CreateDXGraph_UseGParam( SETUP_GRAPHHANDLE_GPARAM *GParam, int GrHandle, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int TextureFlag, int ASyncThread = FALSE ) ;																															// CreateDXGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		DerivationGraph_UseGParam( int SrcX, int SrcY, int Width, int Height, int SrcGraphHandle, int ASyncThread = FALSE ) ;																																												// DerivationGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
#ifndef DX_NON_MOVIE
extern	int		LoadBmpToGraph_OpenMovie_UseGParam( LOADGRAPH_GPARAM *GParam, int GrHandle, const TCHAR *GraphName, int TextureFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL, int ASyncThread = FALSE ) ;
#endif

extern	int		DerivationGraphBase( int GrHandle, int SrcX, int SrcY, int Width, int Height, int SrcGraphHandle, int ASyncThread = FALSE ) ;																																								// �O���t�B�b�N�n���h�����쐬���Ȃ� DerivationGraph
extern	int		SetGraphBaseInfo_UseGParam( SETGRAPHBASEINFO_GPARAM *GParam, int GrHandle, const TCHAR *FileName, COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, void *MemImage, int MemImageSize,
										   void *AlphaMemImage, int AlphaMemImageSize, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int ReverseFlag, int UnionGrHandle, int ASyncThread ) ;																														// SetGraphBaseInfo �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		SetGraphName_UseGParam( SETGRAPHBASEINFO_GPARAM *GParam, int Handle, const TCHAR *GraphName, int ReverseFlag, int UnionGrHandle, int ASyncThread ) ;																																		// SetGraphName �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		FillGraph_UseGParam( int GrHandle, int Red, int Green, int Blue, int Alpha, int ASyncThread ) ;																																																// FillGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		SetGraphName( int Handle, const TCHAR *GraphName, int ReverseFlag, int UnionGrHandle, int ASyncThread ) ;	// ����̃t�@�C������摜��ǂݍ��񂾏ꍇ�̃t�@�C���p�X���Z�b�g����
extern	int		IsValidGraphHandle( int GrHandle ) ;															// �O���t�B�b�N�n���h�����L�����ǂ����𒲂ׂ�( TRUE:�L��  FALSE:���� )


extern	int		ScreenFlipBase( RECT *CopyRect ) ;											// ScreenFlip �̃x�[�X�֐�
extern	int		SetGraphBaseInfo( int GrHandle, const TCHAR *FileName, COLORDATA *BmpColorData, HBITMAP RgbBmp, HBITMAP AlphaBmp, void *MemImage, int MemImageSize, void *AlphaMemImage, int AlphaMemImageSize, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int ReverseFlag, int UnionGrHandle, int ASyncThread ) ;		// �摜�̌��f�[�^�̏���ۑ�����

extern	int		BltBmpOrGraphImageToGraphBase( COLORDATA *SrcColorData, HBITMAP Bmp, HBITMAP AlphaMask, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int CopyPointX, int CopyPointY, int GrHandle, int UseTransColorConvAlpha = TRUE, int ASyncThread = FALSE ) ;											// BltBmpOrGraphImageToGraph �̓����֐�
extern	int		BltBmpOrGraphImageToGraph2Base( COLORDATA *SrcColorData, HBITMAP Bmp, HBITMAP AlphaMask, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, RECT *SrcRect, int DestX, int DestY, int GrHandle ) ;																							// BltBmpOrGraphImageToGraph2 �̓����֐�
extern	int		BltBmpOrGraphImageToDivGraphBase( COLORDATA *SrcColor, HBITMAP Bmp, HBITMAP AlphaMask, int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int Width, int Height, int *GrHandle, int ReverseFlag, int UseTransColorConvAlpha = TRUE, int ASyncThread = FALSE ) ;	// BltBmpOrGraphImageToDivGraph �̓����֐�

extern	int		SetUserBlendInfo( DIRECT3DBLENDINFO *BlendInfo, int TextureStageIsTextureAndTextureCoordOnlyFlag = FALSE ) ;	// �e�N�X�`���X�e�[�W�X�e�[�g�𒼐ڎw�肷��( NULL �Ŗ��� )
extern	int		D_SetSampleFilterMode( int TexStage, int SetTarget, DX_D3DTEXFILTER_TYPE FilterType ) ;	// �e�N�X�`���t�B���^�����O���[�h��ݒ肷��
extern	DX_D3DTEXFILTER_TYPE D_GetSampleFilterMode( int TexStage, int SetTarget ) ;		// �e�N�X�`���t�B���^�����O���[�h���擾����
extern	int		D_SetUserBlendInfo( DIRECT3DBLENDINFO *BlendInfo, int TextureStageIsTextureAndTextureCoordOnlyFlag, int TextureIsGraphHandleFlag = TRUE ) ;	// ���[�U�[�̃u�����h�C���t�H��K������
extern IMAGEDATA2 *GetGraphData2( int GrHandle, int ASyncThread = FALSE ) ;					// �O���t�B�b�N�̃f�[�^���C���f�b�N�X�l������o��
extern	D_D3DXSHADER_CONSTANTINFO *GetShaderConstInfo( SHADERHANDLEDATA *Shader, const TCHAR *ConstantName ) ;				// �V�F�[�_�[�̒萔���𓾂�

extern	int		InitializeShaderConstantUseArea( SHADERCONSTANT_USEAREA *UseArea, int TotalSize ) ;							// �V�F�[�_�[�萔�g�p�̈��������������
extern	int		SetShaderConstantUseArea( SHADERCONSTANT_USEAREA *UseArea, int IsUse, int Index, int Num ) ;				// �V�F�[�_�[�萔�g�p�̈����ύX����
extern	int		CreateUseAreaMap( SHADERCONSTANT_USEAREA *UseArea, BYTE *Map, BYTE SetNumber ) ;							// �V�F�[�_�[�萔�g�p�̈��񂩂�g�p�}�b�v���쐬����

extern	int		InitializeShaderConstantInfoSet( SHADERCONSTANTINFOSET *ConstInfoSet ) ;																	// �V�F�[�_�[�萔���̏�����
extern	int		SetUseShaderContantInfoState( SHADERCONSTANTINFOSET *ConstInfoSet, int ApplyMask ) ;														// �w��̃V�F�[�_�[�萔�Z�b�g��K�p���邩�ǂ�����ݒ肷�� DX_SHADERCONSTANTSET_MASK_LIB | DX_SHADERCONSTANTSET_MASK_LIB_SUB ��
extern	int		SetShaderConstantSet( SHADERCONSTANTINFOSET *ConstInfoSet, int TypeIndex, int SetIndex, int ConstantIndex, void *Param, int ParamNum, int UpdateUseArea ) ;	// �V�F�[�_�[�萔����ݒ肷��
extern	int		ResetShaderConstantSet( SHADERCONSTANTINFOSET *ConstInfoSet, int TypeIndex, int SetIndex, int ConstantIndex, int ParamNum ) ;				// �w��̈�̃V�F�[�_�[�萔�������Z�b�g����


}

#endif // __DXGRAPHICS_H__


