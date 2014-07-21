// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���f���f�[�^����v���O����
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXMODEL_H__
#define __DXMODEL_H__

#include "DxCompileConfig.h"

#ifndef DX_NON_MODEL

// �C���N���[�h ---------------------------------
#include "DxLib.h"
#include "DxStatic.h"
#include "DxBaseFunc.h"
#include "DxGraphicsBase.h"
#include "DxUseCLib.h"
#include "DxMemory.h"
#include "DxVertexShader.h"
#include "DxGraphicsAPI.h"

namespace DxLib
{

// �}�N����` -----------------------------------

#define MV1_ANIMSET_NUM_UNIT				(4)					// �A�j���[�V�����Z�b�g�A�h���X�ǉ��P��
#define MV1_ANIM_NUM_UNIT					(4)					// �A�j���[�V�����A�h���X�ǉ��P��
#define MV1_TRIANGLE_MAX_INDEX				(65500)				// �P�g���C�A���O�����X�g�ӂ�̍ő�C���f�b�N�X��

#define MV1_VERTEXBUFFER_MAX_VERTNUM		(65536 * 6)			// ��̒��_�o�b�t�@�Ɋi�[����ő咸�_��
#define MV1_INDEXBUFFER_MAX_IDXNUM			(65536 * 12)		// ��̒��_�o�b�t�@�Ɋi�[����ő�C���f�b�N�X��

#define MV1_ADD_LOAD_FUNC_MAXNUM			(128)				// �ǉ��ł��郍�[�h�֐��̍ő吔

#define MV1_LOADCALC_PHYSICS_GRAVITY_NUM	(256)				// �ǂݍ��ݎ��ɓK�p�ł���d�͂̎�ސ�

#define MV1_SINTABLE_DIV					(65536)				// �T�C���e�[�u���̐��x

// �t���[���̃t���O
#define MV1_FRAMEFLAG_VISIBLE				(0x00000001)		// �\���t���O( 1:�\��  0:��\�� )
#define MV1_FRAMEFLAG_IGNOREPARENTTRANS		(0x00000002)		// �e�̍��W�ϊ��𖳎����邩�ǂ���( 1:�������� 0:�������Ȃ� )
#define MV1_FRAMEFLAG_PREROTATE				(0x00000004)		// �O��]���L�����ǂ���( 1:�L��  0:���� )
#define MV1_FRAMEFLAG_POSTROTATE			(0x00000008)		// ���]���L�����ǂ���( 1:�L��  0:���� )

// ���C�g�̃^�C�v
#define MV1_LIGHT_TYPE_POINT				(0)					// �|�C���g���C�g
#define MV1_LIGHT_TYPE_SPOT					(1)					// �X�|�b�g���C�g
#define MV1_LIGHT_TYPE_DIRECTIONAL			(2)					// �f�B���N�V���i�����C�g

// ���_�^�C�v
#define MV1_VERTEX_TYPE_NORMAL				(0)					// ���̃��b�V���p
#define MV1_VERTEX_TYPE_SKIN_4BONE			(1)					// �P�`�S�{�[���̃X�L�j���O���b�V���p
#define MV1_VERTEX_TYPE_SKIN_8BONE			(2)					// �T�`�W�{�[���̃X�L�j���O���b�V���p
#define MV1_VERTEX_TYPE_SKIN_FREEBONE		(3)					// �{�[�����������̃X�L�j���O���b�V���p
#define MV1_VERTEX_TYPE_NUM					(4)					// ���_�^�C�v�̐�

// ��]�^�C�v
#define MV1_ROTATE_TYPE_XYZROT				(0)					// X,Y,Z����]
#define MV1_ROTATE_TYPE_QUATERNION			(1)					// �N�H�[�^�j�I��
#define MV1_ROTATE_TYPE_MATRIX				(2)					// �s��
#define MV1_ROTATE_TYPE_ZAXIS				(3)					// �y������+������x�N�g��+�P���]�w��

// �w�x�y��]�I�[�_�[
#define MV1_ROTATE_ORDER_XYZ				(0)					// XYZ
#define MV1_ROTATE_ORDER_XZY				(1)					// XZY
#define MV1_ROTATE_ORDER_YZX				(2)					// YZX
#define MV1_ROTATE_ORDER_YXZ				(3)					// YXZ
#define MV1_ROTATE_ORDER_ZXY				(4)					// ZXY
#define MV1_ROTATE_ORDER_ZYX				(5)					// ZYX

// �A�j���[�V�����v�f�̃t���O
#define MV1_ANIMVALUE_TRANSLATE				(0x01)				// ���s�ړ�
#define MV1_ANIMVALUE_SCALE					(0x02)				// �g��
#define MV1_ANIMVALUE_ROTATE				(0x04)				// ��]
#define MV1_ANIMVALUE_QUATERNION_X			(0x08)				// ��]( X�t�@�C���^�C�v�N�H�[�^�j�I�� )
#define MV1_ANIMVALUE_MATRIX				(0x10)				// �s��
#define MV1_ANIMVALUE_QUATERNION_VMD		(0x20)				// ��]( VMD�^�C�v�N�H�[�^�j�I�� )

// �L�[�^�C�v
//#define MV1_KEY_TYPE_STEP					(0)					// �萔
//#define MV1_KEY_TYPE_LINEAR				(1)					// ���`���
//#define MV1_KEY_TYPE_SPLINE				(2)					// �X�v���C��
//#define MV1_KEY_TYPE_FLAT					(3)					// �X�v���C��(�X���O)

// ���C���[�u�����h�p�����[�^
#define MV1_LAYERBLEND_TYPE_TRANSLUCENT		(0)					// �A���t�@����
#define MV1_LAYERBLEND_TYPE_ADDITIVE		(1)					// ���Z
#define MV1_LAYERBLEND_TYPE_MODULATE		(2)					// ��Z
#define MV1_LAYERBLEND_TYPE_MODULATE2		(3)					// ��Z�~�Q

// �f�[�^�T�C�Y�w�莯�ʎq
#define MV1_DATASIZE_VERTEX					(1)					// ���_�f�[�^
#define MV1_DATASIZE_STRING					(2)					// ������f�[�^
#define MV1_DATASIZE_ANIM					(3)					// �A�j���[�V�����f�[�^
//#define MV1_DATASIZE_OTHER				(4)					// ���̑�

/*
// �e�N�X�`���̃A�h���X���[�h
#define MV1_TEXTURE_ADDRESS_MODE_WRAP		(0)					// �P���J��Ԃ�
#define MV1_TEXTURE_ADDRESS_MODE_MIRROR		(1)					// �~���[�����O
#define MV1_TEXTURE_ADDRESS_MODE_CLAMP 		(2)					// �[�̃s�N�Z��������

// �e�N�X�`���̃t�B���^�����O�^�C�v
#define MV1_TEXTURE_FILTER_MODE_POINT		(0)					// �ŋߓ_�T���v�����O
#define MV1_TEXTURE_FILTER_MODE_LINEAR		(1)					// �o�C���j�A�t�B���^�����O
#define MV1_TEXTURE_FILTER_MODE_ANISOTROPIC	(2)					// �ٕ����t�B���^�����O
*/

// �`�F�b�N�p�h�c
#define MV1_FRAME_CHECK_ID					(0x5F4D5246)		// �t���[���̃`�F�b�N�p�h�c

#ifdef _DEBUG
	#define ADDMEMAREA( size, mem )				AddMemArea( (size), (mem), __FILE__, __LINE__ )
	#define SUBMEMAREA( mem, buffer )			SubMemArea( (mem), (buffer) )
	#define MDALLOCMEM( size )					NS_DxAlloc( (size),        __FILE__, __LINE__ )
#else
	#define ADDMEMAREA( size, mem )				AddMemArea( (size), (mem) )
	#define SUBMEMAREA( mem, buffer )			SubMemArea( (mem), (buffer) )
	#define MDALLOCMEM( size )					NS_DxAlloc( (size) )
#endif
//#define MDFREEMEM( mem )						MDFreeMem( (mem) )
#define MDFREEMEM( mem )						NS_DxFree( (mem) )

// �\���̒�` -----------------------------------

// �g���C�A���O�����X�g�\�z�����_�`�F�b�N�p�\����
struct MV1_MAKEVERTINDEXINFO
{
	union
	{
		int						VertexIndex ;					// �g���C�A���O�����X�g�ł̒��_�C���f�b�N�X
		void					*Face ;							// ���_���Q�Ƃ��Ă����
	} ;
	int							TriangleListIndex ;				// ������g���C�A���O�����X�g�̃C���f�b�N�X
	void						*Mesh ;							// �ʂ������b�V��
	struct MV1_MAKEVERTINDEXINFO *Next ;						// ���̃f�[�^�ւ̃|�C���^
} ;


// �f�[�^��v�����p�\����
struct DATACMPINFO
{
	DWORD					Size ;								// �f�[�^�̃T�C�Y
	DWORD					Data[ 8 ] ;							// �`�F�b�N�p�f�[�^
} ;

// �������A�h���X�ۑ��f�[�^�^
struct MEMINFO
{
	void					*Data ;								// �f�[�^�A�h���X
	struct MEMINFO			*PrevInfo ;							// �O�̃������A�h���X�ۑ��f�[�^�ւ̃|�C���^
	struct MEMINFO			*NextInfo ;							// ���̃������A�h���X�ۑ��f�[�^�ւ̃|�C���^
	int						TotalSize ;
} ;

// �r�b�g�f�[�^���X�g
struct BITLIST
{
	int						DataNum ;							// �L���ȃf�[�^�̐�
	int						MaxDataNum ;						// �m�ۂ���Ă���o�b�t�@�̐�
	int						BitDepth ;							// �r�b�g�[�x
	int						UnitSize ;							// �f�[�^��ӂ�̃o�C�g�T�C�Y
	void					*Data ;								// �f�[�^�{��( �e�f�[�^�̍ŏI�o�C�g�� Press ���ꂽ�f�[�^���ɂ���ĕω�( ��Press( �g�p�����ǂ���( 1:�g�p�� 0:���g�p ) ) Press( �����Ă���r�b�g�̐� ) )
	int						*PressData ;						// ��Press:�v�f�𒊏o�����ۂ̒��o��̎�ޔԍ����X�g  Press:�Ή�����f�[�^�̏o����
} ;

// 4x4�\���̂�4��ڂ�(0,0,0,1)���ߑł��̍s��
// �X�ɕ��ʂ� MATRIX �Ƃ͔z��̗v�f�̈Ӗ����ꎟ���ڂƓ񎟌��ڂ��t
// MATRIX.m[ �s ][ �� ],  MATRIX_4X4CT.m[ �� ][ �s ]
struct MATRIX_4X4CT
{
	float					m[ 3 ][ 4 ] ;
} ;

// �R���W�����p�|���S�����\����
struct MV1_COLL_POLYGON
{
	MV1_REF_POLYGON			*Polygon ;							// �Q�Ɨp�|���S���ւ̃|�C���^
	struct MV1_COLL_POLYGON	*Next ;								// ���̃R���W�����p�|���S�����ւ̃|�C���^
} ;

// �R���W�����p�|���S�������i�[����o�b�t�@�\����
struct MV1_COLL_POLY_BUFFER
{
	int						BufferSize ;						// �o�b�t�@�̃T�C�Y
	int						UseSize ;							// �g�p���Ă��鐔
	MV1_COLL_POLYGON		*Buffer ;							// �o�b�t�@
	struct MV1_COLL_POLY_BUFFER	*Next ;								// ���̃o�b�t�@�\���̂ւ̃|�C���^
} ;

// �R���W�������\����
struct MV1_COLLISION
{
	int						XDivNum, YDivNum, ZDivNum ;			// �e���̕�����
	VECTOR					MinPosition ;						// �d���͈͂̍ŏ��l
	VECTOR					MaxPosition ;						// �d���͈͂̍ő�l
	VECTOR					Size ;								// �d���͈͂̃T�C�Y
	VECTOR					UnitSize ;							// �i�q�������̑傫��
	VECTOR					UnitSizeRev ;						// UnitSize �̋t��
	MV1_COLL_POLYGON		**Polygon ;							// �R���W�����p�|���S�����ւ̃|�C���^�z��A�X�y�[�X�Ɉ���|���S�����Ȃ��ꍇ�� NULL�A�C���f�b�N�X�Z�o�@�� [ X + Y * XDivNum + Z * ( XDivNum * YDivNum ) ]
	MV1_COLL_POLY_BUFFER	*FirstBuffer ;						// �R���W�����p�|���S�����i�[�p�o�b�t�@�̐�[
	MV1_COLL_POLY_BUFFER	*LastBuffer ;						// �R���W�����p�|���S�����i�[�p�o�b�t�@�̖��[
} ;

// ��]���\����
struct MV1_ROTATE
{
	int						Type ;								// ��]�^�C�v( MV1_ROTATE_TYPE_XYZROT �� )
	union
	{
		struct
		{
			VECTOR			Z ;									// �y���̌���
			VECTOR			Up ;								// ������̌���
			float			Twist ;								// �P���]�p�x
		} ZAxis ;												// �y�������{�P��p�x�p
		VECTOR				XYZRot ;							// X����]��Y����]��Z����]�p
		FLOAT4				Qt ;								// �N�H�[�^�j�I����]�p
		MATRIX_4X4CT		Mat ;								// �s���]�p
	} ;
} ;

// �e�N�X�`����f�[�^�\����
struct MV1_TEXTURE_BASE
{
	int						NameAllocMem ;						// �e�N�X�`���̖��O��ۑ����郁�������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )
	char					*Name ;								// �e�N�X�`���̖��O
	wchar_t					*NameW ;							// �e�N�X�`���̖��O

	int						AlphaImageFilePathAllocMem ;		// �A���t�@�`�����l���p�摜�̃t�@�C���p�X�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )
	char					*AlphaFilePath ;					// �A���t�@�`�����l���p�摜�̃t�@�C���p�X
	wchar_t					*AlphaFilePathW ;
	void					*AlphaImage ;						// �A���t�@�`�����l���摜�̃t�@�C���C���[�W�ւ̃|�C���^
	int						AlphaImageSize ;					// �A���t�@�`�����l���摜�̃t�@�C���C���[�W�̃T�C�Y

	int						ColorImageFilePathAllocMem ;		// �A���t�@�`�����l���p�摜�̃t�@�C���p�X�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )
	char					*ColorFilePath ;					// �J���[�`�����l���p�摜�̃t�@�C���p�X
	wchar_t					*ColorFilePathW ;
	void					*ColorImage ;						// �J���[�`�����l���p�摜�̃t�@�C���C���[�W�ւ̃|�C���^
	int						ColorImageSize ;					// �J���[�`�����l���p�摜�̃t�@�C���C���[�W�̃T�C�Y

	int						Width, Height ;						// ���A����
	int						SemiTransFlag ;						// �������v�f�����邩�ǂ���( TRUE:����  FALSE:�Ȃ� )
	int						BumpImageFlag ;						// �����o���v�}�b�v�摜��( TRUE:�o���v�}�b�v  FALSE:�Ⴄ )
	float					BumpImageNextPixelLength ;			// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋���

	int						GraphHandle ;						// �O���t�B�b�N�n���h��

	int						UseUserGraphHandle ;				// UserGraphHandle ���g�p���Ă��邩�ǂ���	int						UseGraphHandle ;					// GraphHandle ���g�p���Ă��邩�ǂ���( TRUE:�g�p���Ă���  FALSE:���Ă��Ȃ� )
	int						UserGraphHandle ;					// ���[�U�[�O���t�B�b�N�n���h��
	int						UserGraphWidth, UserGraphHeight ;	// ���A����
	int						UserGraphHandleSemiTransFlag ;		// ���[�U�[�O���t�B�b�N�n���h���ɔ������v�f�����邩�ǂ���

	int						AddressModeU ;						// �A�h���X���[�h( DX_TEXADDRESS_WRAP �� )
	int						AddressModeV ;						// �A�h���X���[�h( DX_TEXADDRESS_WRAP �� )
	int						FilterMode ;						// �t�B���^�����O���[�h( DX_DRAWMODE_BILINEAR �� )

	int						ReverseFlag ;						// �摜�𔽓]���邩�ǂ���( 1:���]����  0:���]���Ȃ� )
	int						Bmp32AllZeroAlphaToXRGB8Flag ;		// �R�Q�r�b�g�a�l�o�̃A���t�@�l���S���O�������� XRGB8 �Ƃ��Ĉ������ǂ����̃t���O

	DWORD					UserData[ 2 ] ;						// �O����`�̏��
} ;

// �}�e���A�����C���[�\����
struct MV1_MATERIAL_LAYER
{
	int						IsGraphHandleAlpha ;				// GraphHandle ��1.0f�ȊO�̃��l���܂܂�Ă��邩�ǂ���( TRUE:�܂܂�Ă���  FALSE:�܂܂�Ă��Ȃ� )
	int						GraphHandle ;						// Texture �̑���Ɏg�p����O���t�B�b�N�n���h���A0�̏ꍇ�͖���
	int						Texture ;							// ���f���e�N�X�`���C���f�b�N�X( MV1_MODEL_BASE.Textue �z��̃C���f�b�N�X )
	int						BlendType ;							// �u�����h�^�C�v( MV1_LAYERBLEND_TYPE_ADDITIVE �� )
} ;

// �}�e���A����f�[�^�\����
struct MV1_MATERIAL_BASE
{
	char					*Name ;								// ���O
	wchar_t					*NameW ;

	int						Type ;								// �}�e���A���^�C�v( DX_MATERIAL_TYPE_NORMAL �Ȃ� )

	COLOR_F					Diffuse ;							// �f�B�t���[�Y�F
	COLOR_F					Ambient ;							// �A���r�G���g�F
	COLOR_F					Specular ;							// �X�y�L�����[�F
	COLOR_F					Emissive ;							// �G�~�b�V�u�F
	float					Power ;								// �X�y�L�����n�C���C�g�̃p���[

	int						DiffuseLayerNum ;					// �f�B�t���[�Y�J���[�̃��C���[��
	MV1_MATERIAL_LAYER		DiffuseLayer[ 8 ] ;					// �f�B�t���[�Y�J���[�̃��C���[���( �O���C���[�� BlendType �͖�������� )
	int						SpecularLayerNum ;					// �X�y�L�����}�b�v�̃��C���[��
	MV1_MATERIAL_LAYER		SpecularLayer[ 8 ] ;				// �X�y�L�����}�b�v�̃��C���[���( �O���C���[�� BlendType �͖�������� )
	int						NormalLayerNum ;					// �@���}�b�v�̃��C���[��
	MV1_MATERIAL_LAYER		NormalLayer[ 8 ] ;					// �@���}�b�v�̃��C���[���( �O���C���[�� BlendType �͖�������� )

	int						DiffuseGradTexture ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`���C���f�b�N�X�A�������Ă��郉�C�g�̃f�B�t���[�Y�J���[�łt�l�����܂���́A�f�t�H���g�e�N�X�`���̏ꍇ�� -1 or -2�A0�ȏ�̏ꍇ�� MV1_MODEL_BASE.Textue �z��̃C���f�b�N�X
	int						SpecularGradTexture ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�y�L�����J���[�O���f�[�V�����e�N�X�`���C���f�b�N�X�A�������Ă��郉�C�g�̃X�y�L�����J���[�łt�l�����܂���́A�f�t�H���g�e�N�X�`���̏ꍇ�� -1 or -2�A0�ȏ�̏ꍇ�� MV1_MODEL_BASE.Textue �z��̃C���f�b�N�X
	int						SphereMapTexture ;					// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�t�B�A�}�b�v�e�N�X�`���C���f�b�N�X
	int						DiffuseGradBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�f�B�t���[�Y�O���f�[�V�����e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_TRANSLUCENT �Ȃ� )
	int						SpecularGradBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�y�L�����O���f�[�V�����e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
	int						SphereMapBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�t�B�A�}�b�v�e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
	float					OutLineWidth ;						// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̕�
	float					OutLineDotWidth ;					// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̃h�b�g�P�ʂł̕�
	COLOR_F					OutLineColor ;						// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̐F

	int						UseAlphaTest ;						// �A���t�@�e�X�g���g�p���邩�ǂ���
	int						AlphaFunc ;							// �A���t�@�e�X�g���[�h( ���̂Ƃ��떢�g�p )
	int						AlphaRef ;							// �A���t�@�e�X�g��臒l

	int						DrawBlendMode ;						// �o�͎��̃u�����h���[�h( DX_BLENDMODE_NOBLEND �� )
	int						DrawBlendParam ;					// �o�͎��̃u�����h�p�����[�^

	DWORD					UserData[ 4 ] ;						// �O����`�̏��
} ;

// ���C�g�\����
struct MV1_LIGHT
{
	char					*Name ;								// ���O
	int						Index ;								// �C���f�b�N�X

	int						FrameIndex ;						// ���C�g�������Ă���t���[���̃C���f�b�N�X
	int						Type ;								// ���C�g�^�C�v( MV1_LIGHT_TYPE_POINT �� )
	COLOR_F					Diffuse ;							// �f�B�t���[�Y�J���[
	COLOR_F					Specular ;							// �X�y�L�����J���[
	COLOR_F					Ambient ;							// �A���r�G���g�J���[
	float					Range ;								// �X�|�b�g���C�g�̗L������
	float					Falloff ;							// �t�H�[���I�t
	float					Attenuation0 ;						// ���C�g�p�����[�^�O
	float					Attenuation1 ;						// ���C�g�p�����[�^�P
	float					Attenuation2 ;						// ���C�g�p�����[�^�Q
	float					Theta ;								// �X�|�b�g���C�g�̓����R�[���̊p�x�͈�
	float					Phi ;								// �X�|�b�g���C�g�̊O���R�[���̊p�x�͈�

	DWORD					UserData[ 2 ] ;						// �O����`�̏��
} ;



// 16bit�f�[�^�^�C�v�p�⏕���\����
struct MV1_ANIM_KEY_16BIT
{
	BYTE					Min ;								// �ŏ��l( bit7:�O���ǂ���( 0:0�ȊO 1:0 )  bit6:����(0:+ 1:-)  bit5:�搔����(0:+ 1:-) bit4�`0:�搔(�ő�10��15��) ) 
	BYTE					Unit ;								// 16bit�l�P�ӂ�̒l( bit7:�搔����(0:+ 1:-) bit6�`4:�搔(�ő�10��7��) bit3�`0:��Z�����l( 0�`15 ) )
} ;

// 16bit�f�[�^�^�C�v�p�⏕���\����( float�� )
struct MV1_ANIM_KEY_16BIT_F
{
	float					Min ;								// �ŏ��l
	float					Unit ;								// 16bit�l�P�ӂ�̒l
} ;

// �A�j���[�V�����L�[(�S�~�S�s��̂S��ڂ�(0,0,0,1)�Œ�̍s��^�C�v)�f�[�^�\����
struct MV1_ANIM_KEY_MATRIX4X4C
{
	float					Matrix[ 4 ][ 3 ] ;					// �s��
} ;

// �A�j���[�V�����L�[(�R�~�R�s��^�C�v)�f�[�^�\����
struct MV1_ANIM_KEY_MATRIX3X3
{
	float					Matrix[ 3 ][ 3 ] ;					// �s��
} ;

// �A�j���[�V�����L�[���X�g��f�[�^�\����
struct MV1_ANIM_KEYSET_BASE
{
	char								Type ;					// �L�[�^�C�v( MV1_ANIMKEY_TYPE_QUATERNION�� )
	char								DataType ;				// �f�[�^�^�C�v( MV1_ANIMKEY_DATATYPE_ROTATE�� )
	char								TimeType ;				// ���ԃ^�C�v( MV1_ANIMKEY_TIME_TYPE_KEY �� )
	int									TargetShapeIndex ;		// �Ώۂ̃V�F�C�v�C���f�b�N�X( DataType �� MV1_ANIMKEY_DATATYPE_SHAPE �̏ꍇ�̂ݗL�� )

	int									Num ;					// �L�[�̐�
	float								UnitTime ;				// �P�ʎ���( TimeType �� MV1_ANIMKEY_TIME_TYPE_ONE �̏ꍇ�̂ݗL�� )
	union
	{
		float							*KeyTime ;				// �L�[���Ԕz��ւ̃|�C���^( TimeType �� MV1_ANIMKEY_TIME_TYPE_KEY �̏ꍇ�̂ݗL�� )
		float							StartTime ;				// �J�n����( TimeType �� MV1_ANIMKEY_TIME_TYPE_ONE �̏ꍇ�̂ݗL�� )
	} ;

	union
	{
		FLOAT4							*KeyFloat4 ;			// float4�L�[�z��ւ̃|�C���^
		VECTOR							*KeyVector ;			// �x�N�^�[�L�[�z��ւ̃|�C���^
		MV1_ANIM_KEY_MATRIX4X4C			*KeyMatrix4x4C ;		// �S��ڏȗ��S�~�S�s��L�[�z��ւ̃|�C���^
		MV1_ANIM_KEY_MATRIX3X3			*KeyMatrix3x3 ;			// �R���R�s��L�[�z��ւ̃|�C���^
		float							*KeyFlat ;				// �t���b�g�L�[�z��ւ̃|�C���^
		float							*KeyLinear ;			// ���`��ԃL�[�z��ւ̃|�C���^
	} ;

	DWORD								UserData[ 1 ] ;			// �O����`�̏��

} ;

// �A�j���[�V������f�[�^�\����
struct MV1_ANIM_BASE
{
	struct MV1_ANIMSET_BASE	*Container ;						// ���̃A�j���[�V�����������Ă���A�j���[�V�����Z�b�g�ւ̃|�C���^

	struct MV1_FRAME_BASE	*TargetFrame ;						// �ΏۂƂȂ�t���[��
//	char					*TargetFrameName ;					// �ΏۂƂȂ�t���[���̖��O
	int						TargetFrameIndex ;					// �ΏۂƂȂ�t���[���̃C���f�b�N�X
	float					MaxTime ;							// �e�L�[�Z�b�g�̒��ň�Ԓ����L�[�Z�b�g�̎��Ԓl
	int						RotateOrder ;						// ��]�I�[�_�[( MV1_ROTATE_ORDER_XYZ �� )

	int						KeySetNum ;							// �L�[�Z�b�g�̐�
	MV1_ANIM_KEYSET_BASE	*KeySet ;							// �L�[�Z�b�g�z��ւ̃|�C���^

	DWORD					UserData[ 2 ] ;						// �O����`�̏��
} ;

// �A�j���[�V�����Z�b�g��f�[�^�\����
struct MV1_ANIMSET_BASE
{
	int						NameAllocMem ;						// �A�j���[�V�����̖��O��ۑ����郁�������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )
	char					*Name ;								// �A�j���[�V�����Z�b�g��
	wchar_t					*NameW ;

	DWORD					KeyDataSize ;						// �A�j���[�V�����L�[�f�[�^�T�C�Y
	int						Index ;								// �C���f�b�N�X
	float					MaxTime ;							// �e�A�j���[�V�����̒��ň�Ԓ����A�j���[�V�����̎��Ԓl
	int						AnimNum ;							// �A�j���[�V�����̐�
	MV1_ANIM_BASE			*Anim ;								// �A�j���[�V�������X�g
	int						IsAddAnim ;							// ���Z�A�j���[�V�������ǂ���( 1:���Z�A�j���[�V����  0:��Βl�A�j���[�V���� )
	int						IsMatrixLinearBlend ;				// �e�L�[�̕�Ԃ��s��P�ʂŐ��`��Ԃ����邩�ǂ����̃t���O( 1:�s��Ő��`���  0:�v�f�P�ʂŕ�� )

	DWORD					UserData[ 4 ] ;						// �O����`�̏��
} ;

// ���̃��b�V���^�C�v���_�\����
struct MV1_VERTEX_SIMPLE
{
	VECTOR					Position ;							// ���W
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 3 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// ���̃��b�V���^�C�v�֊s���p���_�\����
struct MV1_VERTEX_SIMPLE_TOL
{
	VECTOR					Position ;							// ���W
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
} ;

// ���̃��b�V���^�C�v�o���v�}�b�v�p���_�\����
struct MV1_VERTEX_SIMPLE_BUMP
{
	VECTOR					Position ;							// ���W
	VECTOR					Tangent ;							// ���_�̐ڐ�
	VECTOR					Binormal ;							// ���_�̏]�@��
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 1 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// �X�L�����b�V���^�C�v���_�\����(�֘A�{�[���S�ȓ�)
struct MV1_VERTEX_SKIN_B4
{
	VECTOR					Position ;							// ���W
	unsigned char			MatrixIndex[ 4 ] ;					// �s��C���f�b�N�X( �s��ԍ��~�S )
	float					MatrixWeight[ 4 ] ;					// �s��E�G�C�g
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 1 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// �X�L�����b�V���^�C�v�o���v�}�b�v�p���_�\����(�֘A�{�[���S�ȓ�)
struct MV1_VERTEX_SKIN_B4_BUMP
{
	VECTOR					Position ;							// ���W
	unsigned char			MatrixIndex[ 4 ] ;					// �s��C���f�b�N�X( �s��ԍ��~�S )
	float					MatrixWeight[ 4 ] ;					// �s��E�G�C�g
	VECTOR					Tangent ;							// ���_�̐ڐ�
	VECTOR					Binormal ;							// ���_�̏]�@��
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 1 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// �X�L�����b�V���^�C�v���_�\����(�֘A�{�[���W�ȓ�)
struct MV1_VERTEX_SKIN_B8
{
	VECTOR					Position ;							// ���W
	unsigned char			MatrixIndex[ 8 ] ;					// �s��C���f�b�N�X( �s��ԍ��~�S )
	float					MatrixWeight[ 8 ] ;					// �s��E�G�C�g
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 1 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// �X�L�����b�V���^�C�v�o���v�}�b�v�p���_�\����(�֘A�{�[���W�ȓ�)
struct MV1_VERTEX_SKIN_B8_BUMP
{
	VECTOR					Position ;							// ���W
	unsigned char			MatrixIndex[ 8 ] ;					// �s��C���f�b�N�X( �s��ԍ��~�W )
	float					MatrixWeight[ 8 ] ;					// �s��E�G�C�g
	VECTOR					Tangent ;							// ���_�̐ڐ�
	VECTOR					Binormal ;							// ���_�̏]�@��
	VECTOR					Normal ;							// �@��
	COLOR_U8				DiffuseColor ;						// �f�B�t���[�Y�F
	COLOR_U8				SpecularColor ;						// �X�y�L�����[�F
	float					UVs[ 1 ][ 4 ] ;						// �e�N�X�`�����W
} ;

// �{�[�����������X�L�����b�V���p�u�����h���
struct MV1_SKINBONE_BLEND
{
	int						Index ;								// �g�p����{�[���̃C���f�b�N�X�A-1�ŏI�[( Model->SkinBone �z��̃C���f�b�N�X )
	float					W ;									// ���̃{�[���̃u�����h��
} ;

// �{�[����񖳂����W�f�[�^( 16�o�C�g )
struct MV1_TLIST_NORMAL_POS
{
	FLOAT4					Position ;							// �ʒu
	FLOAT4					Normal ;							// �@��
} ;

// �S�{�[���X�L�j���O�p���W�f�[�^( 48�o�C�g )
struct MV1_TLIST_SKIN_POS_4B
{
	float					MatrixWeight[ 4 ] ;					// 0  �s��E�G�C�g
	FLOAT4					Position ;							// 16 �ʒu
	VECTOR					Normal ;							// 32 �@��
	BYTE					MatrixIndex[ 4 ] ;					// 44 �s��C���f�b�N�X
} ;

// �W�{�[���X�L�j���O�p���W�f�[�^( 64�o�C�g )
struct MV1_TLIST_SKIN_POS_8B
{
	float					MatrixWeight[ 8 ] ;					// 0  �s��E�G�C�g
	VECTOR					Normal ;							// 32 �@��
	BYTE					MatrixIndex1[ 4 ] ;					// 44 �s��C���f�b�N�X
	VECTOR					Position ;							// 48 �ʒu
	BYTE					MatrixIndex2[ 4 ] ;					// 60 �s��C���f�b�N�X
} ;

// �X�{�[���ȏ�X�L�j���O�p���W�f�[�^
struct MV1_TLIST_SKIN_POS_FREEB
{
	FLOAT4					Position ;							// ���W
	FLOAT4					Normal ;							// �@��
	MV1_SKINBONE_BLEND		MatrixWeight[ 4 ] ;					// �s��E�G�C�g( �S�ȏ�̏ꍇ�͂��̌��ɂ����� )
} ;

// �g���C�A���O�����X�g��f�[�^�\����
struct MV1_TRIANGLE_LIST_BASE
{
	struct MV1_MESH_BASE	*Container ;						// ���̃g���C�A���O�����X�g�������Ă��郁�b�V���ւ̃|�C���^
	unsigned short			VertexType ;						// ���_�^�C�v( MV1_VERTEX_TYPE_NORMAL �Ȃ� )
	unsigned short			PosUnitSize ;						// ���_���W����ӂ�̃f�[�^�T�C�Y
	unsigned short			TempUnitSize ;						// �e���|�������_�o�b�t�@�̂P���_�ӂ�̃T�C�Y
	int						VertexNum ;							// ���_�̐�
	int						MaxBoneNum ;						// �ւ��{�[���̍ő吔( MV1_VERTEX_TYPE_SKIN_4OVERBONE �̍ۂɎg�p )
	int						UseBoneNum ;						// �g�p���Ă���{�[���̐�( MV1_VERTEX_TYPE_SKIN_2_4BONE �̍ۂɎg�p )
	int						UseBone[ DX_VS_CONSTF_WORLD_MAT_NUM ] ;	// �g�p����{�[���̔z��A-1�̏ꍇ�͎g�p���Ȃ��Ƃ�������( MV1_FRAME.UseSkinBone �z��̃C���f�b�N�X )( MV1_VERTEX_TYPE_SKIN_4BONE, MV1_VERTEX_TYPE_SKIN_8BONE, MV1_VERTEX_TYPE_SKIN_FREE �̍ۂɎg�p )

	DWORD					*MeshVertexIndex ;					// ���W���_�f�[�^�̑f�ƂȂ��Ă��郁�b�V���̒��_�f�[�^�C���f�b�N�X�̔z��( MV1_MESH_BASE.Vertex �̃C���f�b�N�X�AVertexNum �̐��������݂��� )
	int						MeshVertexIndexAllocMem ;			// MeshVertexIndex �p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )

	MV1_VERTEX_SIMPLE		*TempSimpleVertex ;					// �V�F�[�_�[���g�p�����ɕ`�悷��ꍇ�̒��_�f�[�^
	MV1_VERTEX_SIMPLE_TOL	*TempToonOutLineSimpleVertex ;		// �V�F�[�_�[���g�p�����ɕ`�悷��ꍇ�̃g�D�[���̗֊s���`��p���_�f�[�^
	union
	{
		MV1_TLIST_NORMAL_POS     *NormalPosition ;				// �{�[����񖳂����_���W�f�[�^
		MV1_TLIST_SKIN_POS_4B    *SkinPosition4B ;				// �S�{�[���X�L�j���O�����p���_���W�f�[�^
		MV1_TLIST_SKIN_POS_8B    *SkinPosition8B ;				// �W�{�[���X�L�j���O�����p���_���W�f�[�^
		MV1_TLIST_SKIN_POS_FREEB *SkinPositionFREEB ;			// �X�{�[���ȏ�̃X�L�j���O�����p���_���W�f�[�^
	} ;
	int						PositionAllocMem ;					// ���W�f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:�m�ۂ��Ă���  FALSE:���Ă��Ȃ� )

	unsigned short			IndexNum ;							// ���_�C���f�b�N�X�̐�
	unsigned short			*Index ;							// ���_�C���f�b�N�X

	unsigned short			ToonOutLineIndexNum ;				// �g�D�[���֊s���p���_�C���f�b�N�X�̐�
	unsigned short			*ToonOutLineIndex ;					// �g�D�[���֊s���p���_�C���f�b�N�X

	struct MV1_VERTEXBUFFER	*VertexBuffer ;						// �g�p���钸�_�o�b�t�@
	int						VBStartVertex ;						// �o�[�e�b�N�X�o�b�t�@��Ŏg�p���Ă��钸�_�̊J�n�ԍ�
	int						VBStartIndex ;						// �o�[�e�b�N�X�o�b�t�@��Ŏg�p���Ă���C���f�b�N�X�̊J�n�ԍ�
	int						ObjectDuplicateNum ;				// �o�[�e�b�N�X�o�b�t�@�Ɋi�[����Ă���R�s�[�̐�
} ;

// �X�L�����b�V���p�{�[�����g�p����t���[���̏��
struct MV1_SKIN_BONE_USE_FRAME
{
	int						Index ;								// �{�[�����g�p���Ă���t���[���̃C���f�b�N�X
	int						MatrixIndex ;						// ���̃{�[�����Z�b�g����Ă���t���[�����C���f�b�N�X( MV1_FRAME_BASE.UseSkinBone �̃C���f�b�N�X )
} ;

// �X�L�����b�V���p�{�[�����
struct MV1_SKIN_BONE
{
	MATRIX_4X4CT			ModelLocalMatrix ;					// ���f�����W����{�[���̃��[�J�����W�ɕϊ����邽�߂̍s��
	int						ModelLocalMatrixIsTranslateOnly ;	// ���f�����W����{�[���̃��[�J�����W�ɕϊ����邽�߂̍s�񂪕��s�ړ��݂̂��ǂ���( 1:���s�ړ��̂�  0:��]���܂� )
	int						BoneFrame ;							// �{�[���Ƃ��Ďg�p����t���[��
	int						UseFrameNum ;						// ���̃{�[�����g�p����t���[���̐�
	MV1_SKIN_BONE_USE_FRAME	*UseFrame ;							// ���̃{�[�����g�p����t���[���̏��
} ;

// ��ԕύX�Ǘ��p��{���\����
struct MV1_CHANGE_BASE
{
	DWORD					Target ;							// ��ԕω������������ۂɘ_���a����ׂ��Ώۂ̊J�n�������A�h���X�ւ̃I�t�Z�b�g( �S�o�C�g�P�� )
	DWORD					*Fill ;								// ��ԕω������������ۂɘ_���a����t���O�f�[�^�ANULL�̏ꍇ�� CheckBit �� Fill �̑���
	DWORD					Size ;								// ��ԕω������������ۂɘ_���a����t���O�f�[�^�̃T�C�Y( �S�o�C�g�P�� )�AFill �� NULL �̏ꍇ�͂O
	DWORD					CheckBit ;							// �����̃t���O�r�b�g���������r�b�g���
} ;

// ���b�V���\���̗p���_�f�[�^
struct MV1_MESH_POSITION
{
	VECTOR					Position ;							// ���W
	MV1_SKINBONE_BLEND		BoneWeight[ 4 ] ;					// ���_�u�����h�̏��( �X�L�j���O���b�V���̂Ƃ��̂ݗL���A�u�S�v�Ƃ��Ă���͉̂��ŁA���ۂ� MV1_MESH_BASE.MaxBoneBlendNum �̐��������݂��� )
} ;

// ���b�V���\���̗p�@���f�[�^
struct MV1_MESH_NORMAL
{
	VECTOR					Normal ;							// �@��
	VECTOR					Tangent ;							// �ڐ�
	VECTOR					Binormal ;							// �]�@��
} ;

// ���b�V���\���̗p���_�f�[�^
struct MV1_MESH_VERTEX
{
	DWORD					PositionIndex ;						// �g�p���钸�_
	DWORD					NormalIndex ;						// �g�p����@��
	COLOR_U8				DiffuseColor ;						// ���_�f�B�t���[�Y�J���[
	COLOR_U8				SpecularColor ;						// ���_�X�y�L�����J���[
	float					ToonOutLineScale ;					// �g�D�[���̗֊s���̕\���{��
	float					UVs[ 1 ][ 2 ] ;						// �e�N�X�`�����W( �t�u�Z�b�g����ł͂Ȃ�������A�t�u�Z�b�g��ӂ�̗v�f�����Q�ł͂Ȃ��ꍇ�͓Y���̒l���ω�����A�����ɏ�����Ă���̂͂����܂ł��� )
} ;

// ���b�V���\���̗p�ʃf�[�^
struct MV1_MESH_FACE
{
	WORD					VertexType ;						// ���_�^�C�v( MV1_VERTEX_TYPE_NORMAL �Ȃ� )
	WORD					TriangleListIndex ;					// ��������g���C�A���O�����X�g�ԍ�
	DWORD					VertexIndex[ 3 ] ;					// �ʂ��\�����钸�_�C���f�b�N�X
} ;

// ���b�V����f�[�^�\����
struct MV1_MESH_BASE
{
	struct MV1_FRAME_BASE	*Container ;						// ���̃��b�V���������Ă���t���[���ւ̃|�C���^
	MV1_MATERIAL_BASE		*Material ;							// �g�p����}�e���A���ւ̃|�C���^

	MV1_CHANGE_BASE			ChangeInfo ;						// ��ԕω��Ǘ��p��{���

	int						UseVertexDiffuseColor ;				// ���_�̃f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	int						UseVertexSpecularColor ;			// ���_�̃X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	int						RenderRef ;							// �`��p�Q�ƃJ�E���g
	int						NotOneDiffuseAlpha ;				// �f�B�t���[�Y�J���[�̃A���t�@�l�� 100% �ȊO�̂��̂����邩�ǂ���( 1:����  0:�Ȃ� )

	VECTOR					MaxPosition ;						// ���̃��b�V���Ɋ܂܂�钸�_���W�̍ő�l( ���b�V�����[�J�����W )
	VECTOR					MinPosition ;						// ���̃��b�V���Ɋ܂܂�钸�_���W�̍ŏ��l( ���b�V�����[�J�����W )

	int						TriangleListNum ;					// �g���C�A���O�����X�g�̐�
	MV1_TRIANGLE_LIST_BASE	*TriangleList ;						// �g���C�A���O�����X�g�̃��X�g�ւ̃|�C���^

	BYTE					Visible ;							// �\���t���O( 1:�\������  0:�\�����Ȃ� )
	BYTE					BackCulling ;						// �o�b�N�J�����O�����邩�ǂ���( 1:����  0:���Ȃ� )
	BYTE					Shape ;								// �V�F�C�v���b�V�����ǂ���( 1:�V�F�C�v���b�V��  0:�ʏ탁�b�V�� )

	int						UVSetUnitNum ;						// ��̍��W�f�[�^�Ɋ܂܂��e�N�X�`�����W�Z�b�g�̐�
	int						UVUnitNum ;							// ��̍��W�f�[�^�Ɋ܂܂��e�N�X�`�����W�̐�

	int						VertexNum ;							// ���_�̐�
	int						VertUnitSize ;						// ���_��ӂ�̃f�[�^�T�C�Y
	MV1_MESH_VERTEX			*Vertex ;							// ���_
	int						VertexAllocMem ;					// ���_�f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )

	int						FaceNum ;							// �ʂ̐�
	MV1_MESH_FACE			*Face ;								// ��

	DWORD					UserData[ 4 ] ;						// �O����`�̏��
} ;

// �V�F�C�v���_��f�[�^�\����
struct MV1_SHAPE_VERTEX_BASE
{
	DWORD					TargetMeshVertex ;					// �ΏۂƂȂ钸�_�ԍ�( MV1_MESH_BASE.Vertex �ɑ΂���C���f�b�N�X )
	VECTOR					Position ;							// ���W( ���̍��W�ɑ΂��鍷�� )
	VECTOR					Normal ;							// �@��
} ;

// �V�F�C�v���b�V����f�[�^�\����
struct MV1_SHAPE_MESH_BASE
{
	MV1_MESH_BASE			*TargetMesh ;						// �ΏۂƂȂ郁�b�V��

	DWORD					VertexNum ;							// ���_�f�[�^�̐�
	MV1_SHAPE_VERTEX_BASE	*Vertex ;							// ���_�f�[�^�z��ւ̃|�C���^
	int						VertexAllocMem ;					// ���_�f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )
} ;

// �V�F�C�v��f�[�^�\����
struct MV1_SHAPE_BASE
{
	struct MV1_FRAME_BASE	*Container ;						// ���̃V�F�C�v�������Ă���t���[���̃|�C���^

	char					*Name ;								// ���O

	int						MeshNum ;							// �V�F�C�v���b�V���̐�
	MV1_SHAPE_MESH_BASE		*Mesh ;								// �V�F�C�v���b�V���z��ւ̃|�C���^
} ;

// �������Z�p���̃f�[�^�\����
struct MV1_PHYSICS_RIGIDBODY_BASE
{
	int						Index ;								// �C���f�b�N�X
	char					*Name ;								// ���O

	struct MV1_FRAME_BASE	*TargetFrame ;						// �ΏۂƂȂ�t���[��

	int						RigidBodyGroupIndex ;				// ���̃O���[�v�ԍ�
	DWORD					RigidBodyGroupTarget ;				// ���̃O���[�v�Ώ�
	int						ShapeType ;							// �`��( 0:��  1:��  2:�J�v�Z�� )
	float					ShapeW ;							// ��
	float					ShapeH ;							// ����
	float					ShapeD ;							// ���s
	VECTOR					Position ;							// �ʒu
	VECTOR					Rotation ;							// ��]( ���W�A�� )
	float					RigidBodyWeight ;					// ����
	float					RigidBodyPosDim ;					// �ړ���
	float					RigidBodyRotDim ;					// ��]��
	float					RigidBodyRecoil ;					// ������
	float					RigidBodyFriction ;					// ���C��
	int						RigidBodyType ;						// ���̃^�C�v( 0:Bone�Ǐ]  1:�������Z  2:�������Z(Bone�ʒu���킹) )
	int						NoCopyToBone ;						// �{�[���̍s��𕨗��ɓK�p���Ȃ����ǂ���
} ;

// �������Z�p���̃W���C���g�f�[�^�\����
struct MV1_PHYSICS_JOINT_BASE
{
	int						Index ;								// �C���f�b�N�X
	char					*Name ;								// ���O

	MV1_PHYSICS_RIGIDBODY_BASE	*RigidBodyA ;					// �ڑ��捄�̂`
	MV1_PHYSICS_RIGIDBODY_BASE	*RigidBodyB ;					// �ڑ��捄�̂a
	VECTOR					Position ;							// �ʒu
	VECTOR					Rotation ;							// ��]( ���W�A�� )
	VECTOR					ConstrainPosition1 ;				// �ړ������l�P
	VECTOR					ConstrainPosition2 ;				// �ړ������l�Q
	VECTOR					ConstrainRotation1 ;				// ��]�����l�P
	VECTOR					ConstrainRotation2 ;				// ��]�����l�Q
	VECTOR					SpringPosition ;					// �΂ˈړ��l
	VECTOR					SpringRotation ;					// �΂ˉ�]�l
} ;

// ���f���K�w��f�[�^�\����
struct MV1_FRAME_BASE
{
	struct MV1_MODEL_BASE	*Container ;						// ���̃t���[���������Ă��郂�f���̃|�C���^

	int						CheckID ;							// �`�F�b�N�h�c
	int						CheckNo ;							// �`�F�b�N�ԍ�

	char					*Name ;								// ���O
	wchar_t					*NameW ;
	int						Index ;								// �C���f�b�N�X

	MV1_CHANGE_BASE			ChangeDrawMaterialInfo ;			// �`��p�}�e���A����ԕω��Ǘ��p��{���
	MV1_CHANGE_BASE			ChangeMatrixInfo ;					// �s���ԕω��Ǘ��p��{���

	int						TotalMeshNum ;						// �����̉��w�ɂ��郁�b�V���̑���
	int						TotalChildNum ;						// �����̉��w�ɂ���t���[���̐�
	MV1_FRAME_BASE			*Parent ;							// �e�K�w�ւ̃|�C���^
	MV1_FRAME_BASE			*FirstChild ;						// �q�K�w�ւ̃|�C���^(��[)
	MV1_FRAME_BASE			*LastChild ;						// �q�K�w�ւ̃|�C���^(���[)
	MV1_FRAME_BASE			*Prev ;								// �Z�K�w�ւ̃|�C���^
	MV1_FRAME_BASE			*Next ;								// ��K�w�ւ̃|�C���^

	int						TransformMatrixType ;				// �ϊ��s��̃^�C�v( 0:�P�ʍs��  1:���s�ړ��̂� 2:����ȊO )
	MATRIX_4X4CT			TransformMatrix ;					// ������Ԃ̃��[�J�������[���h�s��
	MATRIX_4X4CT			InverseTransformMatrix ;			// ������Ԃ̃��[�J�������[���h�s��̋t�s��

	int						LocalTransformMatrixType ;			// �ϊ��s��̃^�C�v( 0:�P�ʍs��  1:���s�ړ��̂� 2:����ȊO )
	MATRIX_4X4CT			LocalTransformMatrix ;				// �ϊ��s��

	VECTOR					Translate ;							// ���s�ړ�
	VECTOR					Scale ;								// �X�P�[��
	int						RotateOrder ;						// ��]�I�[�_�[( MV1_ROTATE_ORDER_XYZ �� )
	VECTOR					Rotate ;							// ��](�R��)
	FLOAT4					Quaternion ;						// ��]( �N�H�[�^�j�I�� )
	int						IgnoreParentTransform ;				// �e�̍��W�ϊ��𖳎����邩�ǂ���( 1:��������  0:�������Ȃ� )

	VECTOR					PreRotate ;							// �O��]
	VECTOR					PostRotate ;						// ���]

	VECTOR					MaxPosition ;						// ���̃m�[�h�Ɋ܂܂�郁�b�V���̒��_���W�̍ő�l( ���b�V�����[�J�����W )
	VECTOR					MinPosition ;						// ���̃m�[�h�Ɋ܂܂�郁�b�V���̒��_���W�̍ŏ��l( ���b�V�����[�J�����W )
	int						ValidMaxMinPosition ;				// MaxPosition, MinPosition ���L�����ǂ���( 1:�L��  0:���� )

	DWORD					Flag ;								// �e��t���O( MV1_FRAMEFLAG_VISIBLE �Ȃ� )

	int						IsSkinMesh ;						// ���̃t���[���Ɋ܂܂�郁�b�V���̒��ɃX�L�����b�V�����܂܂�邩�ǂ���( TRUE:�܂܂��  FALSE:�܂܂�Ȃ� )
	int						TriangleNum ;						// ���̃t���[���Ɋ܂܂��|���S���̐�
	int						VertexNum ;							// ���̃t���[���Ɋ܂܂�钸�_�f�[�^�̐�
	int						MeshNum ;							// ���b�V���̐�
	MV1_MESH_BASE			*Mesh ;								// ���b�V�����X�g�ւ̃|�C���^

	int						IsCombineMesh ;						// �������܂ߎq�̃t���[���Ɋ܂܂�郁�b�V�����Z�߂Ĉ�ɍ����������b�V�������݂��邩�ǂ���( TRUE:���݂���  FALSE:���݂��Ȃ� )
	MV1_MESH_BASE			*CombineMesh ;						// �������܂ߎq�̃t���[���Ɋ܂܂�郁�b�V�����Z�߂Ĉ�ɍ����������b�V���ւ̃|�C���^

	int						SkinBoneNum ;						// ���̃t���[�����^�[�Q�b�g�Ƃ���{�[���̐�
	MV1_SKIN_BONE			*SkinBone ;							// ���̃t���[�����^�[�Q�b�g�Ƃ���ŏ��̃{�[���ւ̃|�C���^

	int						UseSkinBoneNum ;					// ���̃t���[�����g�p���Ă���{�[���̐�
	MV1_SKIN_BONE			**UseSkinBone ;						// ���̃t���[�����g�p���Ă���{�[���ւ̃|�C���^�̔z��

	MV1_LIGHT				*Light ;							// ���C�g���ւ̃|�C���^

	int						MaxBoneBlendNum ;					// ��̍��W�f�[�^�Ŏg�p����{�[���E�G�C�g���̍ő吔
	float					SmoothingAngle ;					// �����@���v�Z�̏ꍇ�̃X���[�W���O���s�����ǂ�����臒l( �P�ʂ̓��W�A�� )
	int						AutoCreateNormal ;					// �@���̎����������g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )

	int						PositionNum ;						// ���W�̐�
	int						PosUnitSize ;						// ���W�f�[�^��ӂ�̃T�C�Y
	MV1_MESH_POSITION		*Position ;							// ���W

	int						NormalNum ;							// �@���̐�
	MV1_MESH_NORMAL			*Normal ;							// �@��
	int						NormalAllocMem ;					// �@���f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )

	int						ShapeNum ;							// �V�F�C�v�f�[�^�̐�
	MV1_SHAPE_BASE			*Shape ;							// �V�F�C�v�z��ւ̃|�C���^

	MV1_PHYSICS_RIGIDBODY_BASE *PhysicsRigidBody ;				// ���̏��

	DWORD					UserData[ 4 ] ;						// �O����`�̏��
} ;


// ���_�o�b�t�@���
struct MV1_VERTEXBUFFER
{
	DX_DIRECT3DVERTEXBUFFER9	*VertexBuffer ;					// ���_�o�b�t�@
	DX_DIRECT3DINDEXBUFFER9		*IndexBuffer ;					// �C���f�b�N�X�o�b�t�@
	int						VertexCount ;						// ���_��
	int						IndexCount ;						// �C���f�b�N�X��
	void					*VertexBufferL ;					// ���_�o�b�t�@���b�N���ɃA�h���X���i�[����|�C���^
	void					*IndexBufferL ;						// �C���f�b�N�X�o�b�t�@���b�N���ɃA�h���X���i�[����|�C���^
	DWORD					FVF ;								// ���_�o�b�t�@�쐬���Ɏg�p�����e�u�e
	DWORD					UnitSize ;							// ���_�f�[�^��ӂ�̃T�C�Y

	struct MV1_VERTEXBUFFER	*DataNext ;							// ���̒��_�f�[�^�ւ̃|�C���^
	struct MV1_VERTEXBUFFER	*DataPrev ;							// �O�̒��_�f�[�^�ւ̃|�C���^
} ;

// ���f����f�[�^�\����
struct MV1_MODEL_BASE
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	void					*DataBuffer ;						// �t���[����}�e���A����A�j���[�V�����Ȃǂ��i�[����o�b�t�@�ւ̃|�C���^

	DWORD_PTR				AllocMemorySize ;					// �������m�ۂɎg�p�����T�C�Y

	int						UseNum ;							// ���̊�f�[�^���g�p���Ă��郂�f���f�[�^�̐�
	struct MV1_MODEL		*UseFirst, *UseLast ;				// ���̊�f�[�^���g�p���Ă��郂�f���f�[�^�̐�[�ƏI�[�ւ̃|�C���^

	int						RightHandType ;						// �E����W�n���ǂ���( TRUE:�E����W�n  FALSE:������W�n )
	int						Ignore32bitBmpAlpha ;				// 32bit�a�l�o�̃A���t�@�����𖳎����邩�ǂ���( TRUE:�������� FALSE:�A���t�@�����Ƃ��Ĉ��� )

	TCHAR					*Name ;								// ���f���̖��O
	TCHAR					*FilePath ;							// ���f���̃t�@�C���p�X
	TCHAR					*DirectoryPath ;					// ���f���̃t�@�C�������݂���f�B���N�g���p�X( ���[�� \ �t�� )
	int						RefCount ;							// �Q�ƃJ�E���g

	int						ChangeDrawMaterialTableSize ;		// �`��}�e���A���̕ύX���Ǘ��p�ɕK�v�ȃf�[�^�̑��e��
	int						ChangeMatrixTableSize ;				// �s��̕ύX���Ǘ��p�ɕK�v�ȃf�[�^�̑��e��
	DWORD					*ChangeDrawMaterialTable ;			// �`��p�}�e���A���ύX�m�F�p�r�b�g�f�[�^
	DWORD					*ChangeMatrixTable ;				// �s��ύX�m�F�p�r�b�g�f�[�^

	int						FrameNum ;							// �K�w�f�[�^�̐�
	MV1_FRAME_BASE			*Frame ;							// �K�w�f�[�^�z��ւ̃|�C���^
	int						TopFrameNum ;						// �ŏ�ʊK�w�̃t���[���̐�
	MV1_FRAME_BASE			*FirstTopFrame ;					// �ŏ�ʊK�w�̍ŏ��̃t���[���ւ̃|�C���^
	MV1_FRAME_BASE			*LastTopFrame ;						// �ŏ�ʊK�w�̍Ō�̃t���[���ւ̃|�C���^
	int						FrameUseSkinBoneNum ;				// �t���[�����g�p���Ă���{�[���̑���
	MV1_SKIN_BONE			**FrameUseSkinBone ;				// �t���[�����g�p���Ă���{�[���ւ̃|�C���^

	int						MaterialNum ;						// �}�e���A���f�[�^�̐�
	MV1_MATERIAL_BASE		*Material ;							// �}�e���A���f�[�^�z��ւ̃|�C���^

	int						TextureNum ;						// �e�N�X�`���̐�
	MV1_TEXTURE_BASE		*Texture ;							// �e�N�X�`���f�[�^�z��ւ̃|�C���^
	int						TextureAllocMem ;					// �e�N�X�`���f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )

	int						MeshNum ;							// ���b�V���f�[�^�̐�
	MV1_MESH_BASE			*Mesh ;								// ���b�V���f�[�^�z��ւ̃|�C���^

	int						LightNum ;							// ���C�g�̐�
	MV1_LIGHT				*Light ;							// ���C�g�f�[�^�z��ւ̃|�C���^

	VECTOR					MaxPosition ;						// �f�t�H���g�|�[�Y�̒��_���W�̍ő�l( ���f�����[�J�����W )
	VECTOR					MinPosition ;						// �f�t�H���g�|�[�Y�̒��_���W�̍ŏ��l( ���f�����[�J�����W )
	int						ValidMaxMinPosition ;				// MaxPosition, MinPosition ���L�����ǂ���( 1:�L��  0:���� )

	int						SkinBoneNum ;						// �X�L�j���O���b�V���̃{�[���Ƃ��Ďg�p����t���[���̏��̐�
	MV1_SKIN_BONE			*SkinBone ;							// �X�L�j���O���b�V���̃{�[���Ƃ��Ďg�p����t���[���̏��
	int						SkinBoneUseFrameNum ;				// �X�L�j���O���b�V���̃{�[�����g�p����t���[���̐�
	MV1_SKIN_BONE_USE_FRAME	*SkinBoneUseFrame ;					// �X�L�j���O���b�V���̃{�[�����g�p����t���[��

	int						ShapeNum ;							// �V�F�C�v�f�[�^�̐�
	MV1_SHAPE_BASE			*Shape ;							// �V�F�C�v�f�[�^�z��ւ̃|�C���^
	int						ShapeMeshNum ;						// �V�F�C�v���b�V���f�[�^�̐�
	MV1_SHAPE_MESH_BASE		*ShapeMesh ;						// �V�F�C�v���b�V���f�[�^�z��ւ̃|�C���^
	int						ShapeVertexNum ;					// �V�F�C�v���_�f�[�^�̐�
	MV1_SHAPE_VERTEX_BASE	*ShapeVertex ;						// �V�F�C�v���_�f�[�^�z��ւ̃|�C���^
	int						ShapeTargetMeshVertexNum ;			// �V�F�C�v�Ώۂ̃��b�V���̒��_�̑���

	int						ShapeNormalPositionNum ;			// �V�F�C�v�p�g���C�A���O�����X�g�̃{�[����񖳂����W�f�[�^�̐�
	int						ShapeSkinPosition4BNum ;			// �V�F�C�v�p�g���C�A���O�����X�g�̂S�{�[���X�L�j���O���b�V�����W�f�[�^�̐�
	int						ShapeSkinPosition8BNum ;			// �V�F�C�v�p�g���C�A���O�����X�g�̂W�{�[���X�L�j���O���b�V�����W�f�[�^�̐�
	int						ShapeSkinPositionFREEBSize ;		// �V�F�C�v�p�g���C�A���O�����X�g�̂X�{�[���ȏ�X�L�j���O���b�V�����W�f�[�^�̃T�C�Y

	int						PhysicsRigidBodyNum ;				// �������Z�p���̃f�[�^�̐�
	MV1_PHYSICS_RIGIDBODY_BASE *PhysicsRigidBody ;				// �������Z�p���̃f�[�^�z��ւ̃|�C���^
	int						PhysicsJointNum ;					// �������Z�p�W���C���g�f�[�^�̐�
	MV1_PHYSICS_JOINT_BASE	*PhysicsJoint ;						// �������Z�p�W���C���g�f�[�^�z��ւ̃|�C���^

	int						TriangleListNum ;					// �g���C�A���O�����X�g�̐�
	MV1_TRIANGLE_LIST_BASE	*TriangleList ;						// �g���C�A���O�����X�g�f�[�^�z��ւ̃|�C���^

	int						TriangleListNormalPositionNum ;		// �g���C�A���O�����X�g�̃{�[����񖳂����W�f�[�^�̐�
	int						TriangleListSkinPosition4BNum ;		// �g���C�A���O�����X�g�̂S�{�[���X�L�j���O���b�V�����W�f�[�^�̐�
	int						TriangleListSkinPosition8BNum ;		// �g���C�A���O�����X�g�̂W�{�[���X�L�j���O���b�V�����W�f�[�^�̐�
	int						TriangleListSkinPositionFREEBSize ;	// �g���C�A���O�����X�g�̂X�{�[���ȏ�X�L�j���O���b�V�����W�f�[�^�̃T�C�Y
	int						MeshPositionSize ;					// ���b�V�����W�̃f�[�^�T�C�Y
	int						MeshNormalNum ;						// ���b�V���@���̐�
	int						MeshVertexSize ;					// ���b�V�����_���̃f�[�^�T�C�Y
	int						MeshFaceNum ;						// ���b�V���ʏ��̐�
	int						MeshVertexIndexNum ;				// ���_�C���f�b�N�X�f�[�^�̑���
	void					*VertexData ;						// ���_�f�[�^���i�[���郁�����̈�
	DWORD					VertexDataSize ;					// ���_�f�[�^�̃T�C�Y
	MV1_TLIST_NORMAL_POS	*TriangleListNormalPosition ;		// �g���C�A���O�����X�g�̃{�[����񖳂����W�f�[�^
	MV1_TLIST_SKIN_POS_4B	*TriangleListSkinPosition4B ;		// �g���C�A���O�����X�g�̂S�{�[���X�L�j���O���b�V�����W�f�[�^
	MV1_TLIST_SKIN_POS_8B	*TriangleListSkinPosition8B ;		// �g���C�A���O�����X�g�̂W�{�[���X�L�j���O���b�V�����W�f�[�^
	MV1_TLIST_SKIN_POS_FREEB *TriangleListSkinPositionFREEB ;	// �g���C�A���O�����X�g�̂X�{�[���ȏ�X�L�j���O���b�V�����W�f�[�^
	MV1_MESH_POSITION		*MeshPosition ;						// ���b�V�����W�f�[�^
	MV1_MESH_NORMAL			*MeshNormal ;						// ���b�V���@���f�[�^
	MV1_MESH_VERTEX			*MeshVertex ;						// ���b�V�����_�f�[�^
	MV1_MESH_FACE			*MeshFace ;							// ���b�V���ʃf�[�^
	DWORD					*MeshVertexIndex ;					// ���b�V���p���_�C���f�b�N�X�f�[�^

	float					PhysicsGravity ;					// �������Z�Ŏg�p����d�̓p�����[�^

	int						TriangleListIndexNum ;				// �g���C�A���O�����X�g�̒��_�C���f�b�N�X�f�[�^�̑���
	WORD					*TriangleListIndex ;				// �g���C�A���O�����X�g�̒��_�C���f�b�N�X�ւ̃|�C���^

	int						TriangleNum ;						// �O�p�`�̐�
	int						TriangleListVertexNum ;				// �g���C�A���O�����X�g�̒��_�f�[�^�̐�

	int						StringSize ;						// �������ۑ�����o�b�t�@�̃T�C�Y
	char					*StringBuffer ;						// �������ۑ�����o�b�t�@�ւ̃|�C���^

	int						AnimKeyDataSize ;					// �A�j���[�V�����L�[�f�[�^�̃T�C�Y
	void					*AnimKeyData ;						// �A�j���[�V�����L�[�f�[�^�̃o�b�t�@

	int						AnimKeySetNum ;						// �A�j���[�V�����L�[�Z�b�g�̐�
	MV1_ANIM_KEYSET_BASE	*AnimKeySet ;						// �A�j���[�V�����L�[�Z�b�g�f�[�^�z��ւ̃|�C���^

	int						AnimNum ;							// �A�j���[�V�����̐�
	MV1_ANIM_BASE			*Anim ;								// �A�j���[�V�����f�[�^�z��ւ̃|�C���^

	int						AnimSetNum ;						// �A�j���[�V�����Z�b�g�̐�
	MV1_ANIMSET_BASE		*AnimSet ;							// �A�j���[�V�����Z�b�g�f�[�^�z��ւ̃|�C���^

	MV1_ANIM_BASE			**AnimTargetFrameTable ;			// �t���[���̐��~�A�j���[�V�����Z�b�g�̐��������݂���t���[���ƃA�j���[�V�����̑Ή��e�[�u��

	int						TotalVertexBufferNum ;				// ���_�o�b�t�@�̑���
	int						SetupVertexBuffer ;					// ���_�o�b�t�@�̃Z�b�g�A�b�v���������Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )
	int						VertexBufferNum[ 3 ][ 2 ][ 9 ] ;	// �e���_�o�b�t�@�̐�
	MV1_VERTEXBUFFER		*VertexBufferFirst[ 3 ][ 2 ][ 9 ] ;	// �ŏ��̒��_�o�b�t�@�ւ̃|�C���^[ 0:�P�{�[���p  1:�S�{�[���p  2:�W�{�[���p ][ 0:�o���v�}�b�v����  1:�o���v�}�b�v�L�� ][ UV �̐� ]
	MV1_VERTEXBUFFER		*VertexBufferLast[ 3 ][ 2 ][ 9 ] ;	// ���[�̒��_�o�b�t�@�̃|�C���^[   0:�P�{�[���p  1:�S�{�[���p  2:�W�{�[���p ][ 0:�o���v�}�b�v����  1:�o���v�}�b�v�L�� ][ UV �̐� ]
	int						ObjectDuplicateNum ;				// ��]����I�u�W�F�N�g�R�s�[�̐�

	MEMINFO					*AddFirstMem ;						// ���e�ύX��������ꍇ�ɐV���Ɋm�ۂ������������L�����Ă������߂̃��m

	DWORD					UserData[ 4 ] ;						// �O����`�̏��
} ;





// �A�j���[�V�����L�[�Z�b�g���s�p�\����
struct MV1_ANIM_KEYSET
{
	MV1_ANIM_KEYSET_BASE	*BaseData ;							// �L�[�Z�b�g��{�f�[�^�ւ̃|�C���^

	int						ShapeTargetIndex ;					// �Ώۂ̃V�F�C�v�C���f�b�N�X
	float					ShapeKeyFactor ;					// �V�F�C�v�̃u�����h��
	int						NowKey ;							// ���ݏ������Ă���L�[�̃C���f�b�N�X
} ;

// �A�j���[�V�������s�p�\����
struct MV1_ANIM
{
	MV1_ANIM_BASE			*BaseData ;							// �A�j���[�V������{�f�[�^�ւ̃|�C���^
	struct MV1_FRAME		*Frame ;							// �A�j���[�V�������S�����Ă���t���[��

	int						ValidFlag ;							// �L���ȗv�f�̃r�b�g�������Ă���t���O�ϐ�( MV1_ANIMVALUE_TRANSLATE �� )
	VECTOR					Scale ;								// �g��l
	VECTOR					Translate ;							// ���s�ړ��l
	int						RotateOrder ;						// ��]�I�[�_�[( MV1_ROTATE_ORDER_XYZ �� )
	VECTOR					Rotate ;							// ��]�l
	FLOAT4					Quaternion ;						// ��]�l( �N�H�[�^�j�I�� )
	MATRIX_4X4CT			Matrix ;							// �s��
	float					*ShapeRate ;						// �V�F�C�v�̃u�����h��

	MATRIX_4X4CT			BlendMatrix ;						// �L�[�Z�b�g�̏�Ԃ𔽉f�����s��
	MV1_ANIM_KEYSET			*KeySet ;							// �L�[�Z�b�g�z��ւ̃|�C���^
} ;

// �A�j���[�V�����Z�b�g���s�p�\����
struct MV1_ANIMSET
{
	MV1_ANIMSET_BASE		*BaseData ;							// �A�j���[�V�����Z�b�g��{�f�[�^�ւ̃|�C���^

	bool					ParamSetup ;						// �p�����[�^�̃Z�b�g�A�b�v���ς�ł��邩�ǂ���( true:�ς�ł���  false:�ς�ł��Ȃ� )
	float					NowTime ;							// �A�j���[�V�����̌��݂̍Đ�����
	MV1_ANIM				*Anim ;								// �A�j���[�V�����z��ւ̃|�C���^
} ;

// ��ԕύX�Ǘ����\����
struct MV1_CHANGE
{
	MV1_CHANGE_BASE			*BaseData ;							// ��ԕύX�Ǘ����̊�{�f�[�^�ւ̃|�C���^
	DWORD					*Target ;							// ��ԕω������������ۂɘ_���a����ׂ��Ώۂ̊J�n�������A�h���X
} ;

// �`��p�}�e���A�����\����
struct MV1_DRAW_MATERIAL
{
	BYTE					Visible ;							// �\���t���O( 1:�\������  0:�\�����Ȃ� )

	bool					UseColorScale ;						// Scale�n�p�����[�^�Ŏg�p���Ă��鍀�ڂ����邩�ǂ���( true:���� false:�Ȃ� )
	COLOR_F					DiffuseScale ;						// �f�B�t���[�Y�F�ɏ�Z����l( �����l�͑S�v�f 1.0f )
	COLOR_F					AmbientScale ;						// �A���r�G���g�F�ɏ�Z����l( �����l�͑S�v�f 1.0f )
	COLOR_F					SpecularScale ;						// �X�y�L�����F�ɏ�Z����l( �����l�͑S�v�f 1.0f )
	COLOR_F					EmissiveScale ;						// �G�~�b�V�u�F�ɏ�Z����l( �����l�͑S�v�f 1.0f )

	float					OpacityRate ;						// �s������( �����l�� 1.0f )
} ;

// �e�N�X�`���\����
struct MV1_TEXTURE
{
	MV1_TEXTURE_BASE		*BaseData ;							// �e�N�X�`���̊�{�f�[�^�ւ̃|�C���^

	char					*AlphaFilePath ;					// �A���t�@�`�����l���p�摜�̃t�@�C���p�X
	wchar_t					*AlphaFilePathW ;
	void					*AlphaImage ;						// �A���t�@�`�����l���摜�̃t�@�C���C���[�W�ւ̃|�C���^
	int						AlphaImageSize ;					// �A���t�@�`�����l���摜�̃t�@�C���C���[�W�̃T�C�Y

	char					*ColorFilePath ;					// �J���[�`�����l���p�摜�̃t�@�C���p�X
	wchar_t					*ColorFilePathW ;
	void					*ColorImage ;						// �J���[�`�����l���p�摜�̃t�@�C���C���[�W�ւ̃|�C���^
	int						ColorImageSize ;					// �J���[�`�����l���p�摜�̃t�@�C���C���[�W�̃T�C�Y

	int						Width, Height ;						// ���A����
	int						SemiTransFlag ;						// �������v�f�����邩�ǂ���( TRUE:����  FALSE:�Ȃ� )
	int						BumpImageFlag ;						// �����o���v�}�b�v�摜��( TRUE:�o���v�}�b�v  FALSE:�Ⴄ )
	float					BumpImageNextPixelLength ;			// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋���

	int						UseGraphHandle ;					// GraphHandle ���g�p���Ă��邩�ǂ���( TRUE:�g�p���Ă���  FALSE:���Ă��Ȃ� )
	int						GraphHandle ;						// �O���t�B�b�N�n���h��

	int						UseUserGraphHandle ;				// UserGraphHandle ���g�p���Ă��邩�ǂ���( TRUE:�g�p���Ă���  FALSE:���Ă��Ȃ� )
	int						UserGraphHandle ;					// ���[�U�[�O���t�B�b�N�n���h��
	int						UserGraphWidth, UserGraphHeight ;	// ���A����
	int						UserGraphHandleSemiTransFlag ;		// ���[�U�[�O���t�B�b�N�n���h���ɔ������v�f�����邩�ǂ���

	int						AddressModeU ;						// �A�h���X���[�h( DX_TEXADDRESS_WRAP �� )
	int						AddressModeV ;						// �A�h���X���[�h( DX_TEXADDRESS_WRAP �� )
	int						FilterMode ;						// �t�B���^�����O���[�h( DX_DRAWMODE_BILINEAR �� )

	int						ReverseFlag ;						// �摜�𔽓]���邩�ǂ���( 1:���]����  0:���]���Ȃ� )
	int						Bmp32AllZeroAlphaToXRGB8Flag ;		// �R�Q�r�b�g�a�l�o�̃A���t�@�l���S���O�������� XRGB8 �Ƃ��Ĉ������ǂ����̃t���O
} ;

// �}�e���A���f�[�^�\����
struct MV1_MATERIAL
{
	MV1_MATERIAL_BASE		*BaseData ;							// �}�e���A���̊�f�[�^�ւ̃|�C���^

	COLOR_F					Diffuse ;							// �f�B�t���[�Y�F
	COLOR_F					Ambient ;							// �A���r�G���g�F
	COLOR_F					Specular ;							// �X�y�L�����[�F
	COLOR_F					Emissive ;							// �G�~�b�V�u�F
	float					Power ;								// �X�y�L�����n�C���C�g�̃p���[

	int						DiffuseLayerNum ;					// �f�B�t���[�Y�J���[�̃��C���[��
	MV1_MATERIAL_LAYER		DiffuseLayer[ 8 ] ;					// �f�B�t���[�Y�J���[�̃��C���[���( �O���C���[�� BlendType �͖�������� )
	int						SpecularLayerNum ;					// �X�y�L�����}�b�v�̃��C���[��
	MV1_MATERIAL_LAYER		SpecularLayer[ 8 ] ;				// �X�y�L�����}�b�v�̃��C���[���( �O���C���[�� BlendType �͖�������� )

	int						DiffuseGradTexture ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�f�B�t���[�Y�J���[�O���f�[�V�����e�N�X�`���C���f�b�N�X�A�������Ă��郉�C�g�̃f�B�t���[�Y�J���[�łt�l�����܂����( MV1_MODEL_BASE.Textue �z��̃C���f�b�N�X )
	int						SpecularGradTexture ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�y�L�����J���[�O���f�[�V�����e�N�X�`���C���f�b�N�X�A�������Ă��郉�C�g�̃X�y�L�����J���[�łt�l�����܂���́A�����̏ꍇ�́|�P( MV1_MODEL_BASE.Textue �z��̃C���f�b�N�X )
	int						SphereMapTexture ;					// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�t�B�A�}�b�v�e�N�X�`���C���f�b�N�X
	int						DiffuseGradBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�f�B�t���[�Y�O���f�[�V�����e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_TRANSLUCENT �Ȃ� )
	int						SpecularGradBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�y�L�����O���f�[�V�����e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
	int						SphereMapBlendType ;				// ( �g�D�[�������_�����O�ł̂ݎg�p )�X�t�B�A�}�b�v�e�N�X�`���̃u�����h�^�C�v( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
	float					OutLineWidth ;						// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̕�( 0.0f �` 1.0f )
	float					OutLineDotWidth ;					// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̃h�b�g�P�ʂł̕�
	COLOR_F					OutLineColor ;						// ( �g�D�[�������_�����O�ł̂ݎg�p )�֊s���̐F

	int						UseAlphaTest ;						// �A���t�@�e�X�g���g�p���邩�ǂ���
	int						AlphaFunc ;							// �A���t�@�e�X�g���[�h( ���̂Ƃ��떢�g�p )
	int						AlphaRef ;							// �A���t�@�e�X�g��臒l

	int						DrawBlendMode ;						// �o�͎��̃u�����h���[�h( DX_BLENDMODE_NOBLEND �� )
	int						DrawBlendParam ;					// �o�͎��̃u�����h�p�����[�^
} ;

// �g���C�A���O�����X�g�\����
struct MV1_TRIANGLE_LIST
{
	struct MV1_MESH				*Container ;					// ���̃g���C�A���O�����X�g�������Ă��郁�b�V���ւ̃|�C���^
	MV1_TRIANGLE_LIST_BASE		*BaseData ;						// ��f�[�^�ւ̃|�C���^

	union
	{
		MV1_TLIST_NORMAL_POS     *NormalPosition ;				// �{�[����񖳂����_���W�f�[�^
		MV1_TLIST_SKIN_POS_4B    *SkinPosition4B ;				// �S�{�[���X�L�j���O�����p���_���W�f�[�^
		MV1_TLIST_SKIN_POS_8B    *SkinPosition8B ;				// �W�{�[���X�L�j���O�����p���_���W�f�[�^
		MV1_TLIST_SKIN_POS_FREEB *SkinPositionFREEB ;			// �X�{�[���ȏ�̃X�L�j���O�����p���_���W�f�[�^
	} ;
	DX_DIRECT3DVERTEXBUFFER9	*VertexBuffer ;					// ���_�o�b�t�@
} ;

// �V�F�C�v���_�f�[�^�\����
struct MV1_SHAPE_VERTEX
{
	VECTOR					Position ;							// ���W
	VECTOR					Normal ;							// �@��
} ;

// �������Z�p���̃f�[�^�\����
struct MV1_PHYSICS_RIGIDBODY
{
	MV1_PHYSICS_RIGIDBODY_BASE *BaseData ;						// ��f�[�^�ւ̃|�C���^
	struct MV1_FRAME		*TargetFrame ;						// �ΏۂƂȂ�t���[��

	DWORD					BulletInfo[ 160 ] ;					// BULLET_RIGIDBODY_INFO ���i�[����o�b�t�@
} ;

// �������Z�p���̃W���C���g�f�[�^�\����
struct MV1_PHYSICS_JOINT
{
	MV1_PHYSICS_JOINT_BASE	*BaseData ;							// ��f�[�^�ւ̃|�C���^

	DWORD					BulletInfo[ 16 ] ;					// BULLET_JOINT_INFO ���i�[����o�b�t�@
} ;

// ���b�V���f�[�^�\����
struct MV1_MESH
{
	struct MV1_FRAME		*Container ;						// ���̃��b�V���������Ă���t���[���ւ̃|�C���^
	MV1_MESH_BASE			*BaseData ;							// ��f�[�^�ւ̃|�C���^

	MV1_MATERIAL			*Material ;							// �}�e���A���ւ̃|�C���^
	MV1_CHANGE				DrawMaterialChange ;				// ��ԕω��`�F�b�N�p���
	MV1_DRAW_MATERIAL		DrawMaterial ;						// �`��p�}�e���A�����
	MV1_DRAW_MATERIAL		SetupDrawMaterial ;					// ��ʃt���[���̏����l�������`��p�}�e���A�����
	bool					SemiTransStateSetupFlag ;			// SemiTransState �̃Z�b�g�A�b�v���ς�ł��邩( true:�ς�ł���  false:�ς�ł��Ȃ� )
	bool					SemiTransState ;					// ���̃��b�V���ɔ������v�f�����邩�ǂ���( true:����  false:�Ȃ� )

	MV1_SHAPE_VERTEX		*ShapeVertex ;						// �V�F�C�v�����������_�f�[�^( BaseData->Shape �� 1 �̏ꍇ�̂ݎg�p )
	MV1_TRIANGLE_LIST		*TriangleList ;						// �g���C�A���O�����X�g�ւ̃|�C���^

	int						DrawBlendMode ;						// �`��u�����h���[�h( -1:�̏ꍇ�̓}�e���A���̃f�t�H���g�l )
	int						DrawBlendParam ;					// �`��u�����h�p�����[�^
} ;

// ���f���K�w�\����
struct MV1_FRAME
{
	int						CheckID ;							// �`�F�b�N�h�c( "MFRM" )

	int						ModelHandle ;						// ���̃t���[���������Ă��郂�f���̃n���h��
	struct MV1_MODEL		*Container ;						// ���̃t���[���������Ă��郂�f���ւ̃|�C���^

	int						ChildIndex ;						// �e�̉��Ԗڂ̎q��
	MV1_FRAME_BASE			*BaseData ;							// �K�w�̊�{�f�[�^�ւ̃|�C���^

	struct MV1_FRAME		*Parent ;							// �e�K�w�ւ̃|�C���^
	struct MV1_FRAME		*Child ;							// �q�K�w�ւ̃|�C���^
	struct MV1_FRAME		*Prev ;								// �Z�K�w�ւ̃|�C���^
	struct MV1_FRAME		*Next ;								// ��K�w�ւ̃|�C���^
	int						ChildNum ;							// �q�̐�
	struct MV1_FRAME		**ChildList ;						// �q���X�g�ւ̃|�C���^

	bool					ValidUserLocalTransformMatrix ;		// �O���w��̍s�񂪗L�����ǂ���( true:�L��  false:���� )
	MATRIX_4X4CT			UserLocalTransformMatrix ;			// �O���w��̍s��
	MV1_CHANGE				LocalWorldMatrixChange ;			// �s��̏�ԕω��`�F�b�N�p���
	MATRIX_4X4CT			LocalWorldMatrix ;					// ���[�J�������[���h�s��
	bool					ValidLocalWorldMatrixNM ;			// LocalWorldMatrixNM ���L�����ǂ���( true:�L��  false:���� )
	MATRIX					LocalWorldMatrixNM ;				// ���[�J�������[���h�s��( �Œ�@�\�V�F�[�_�[�p )

	int						TextureAddressTransformUse ;		// �e�N�X�`�����W�ϊ��s����g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	MATRIX					TextureAddressTransformMatrix ;		// �e�N�X�`�����W�ϊ��s��

	MATRIX_4X4CT			**UseSkinBoneMatrix ;				// �g�p���Ă���{�[���̍s��ւ̃|�C���^�̔z��

	bool					SetupTransformPolygon ;				// ���_�ϊ�����|���S�����X�g�̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	bool					SetupNonTransformPolygon ;			// ���_�ϊ��Ȃ��|���S�����X�g�̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	MV1_REF_POLYGONLIST		*TransformPolygon ;					// ���_�ϊ�����|���S�����X�g
	MV1_REF_POLYGONLIST		*NonTransformPolygon ;				// ���_�ϊ��Ȃ��|���S�����X�g

	bool					SetupCollision ;					// �R���W�������̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	MV1_COLLISION			*Collision ;						// �R���W�������

	MV1_MESH				*Mesh ;								// ���̃t���[���ɑ����郁�b�V���ւ̃|�C���^( ���b�V���̐��� BaseData->MeshNum )

	bool					ShapeChangeFlag ;					// �V�F�C�v�̏�񂪕ω��������A�t���O( true:�ω�����  false:�ω����Ă��Ȃ� )

	MV1_PHYSICS_RIGIDBODY	*PhysicsRigidBody ;					// ���̏��

	MV1_CHANGE				DrawMaterialChange ;				// �`��p�}�e���A���̏�ԕω��`�F�b�N�p���
	MV1_DRAW_MATERIAL		DrawMaterial ;						// �`��p�}�e���A�����
	MV1_DRAW_MATERIAL		SetupDrawMaterial ;					// ��ʃt���[���̏����l�������`��p�}�e���A�����
	bool					SemiTransStateSetupFlag ;			// SemiTransState �̃Z�b�g�A�b�v���ς�ł��邩( true:�ς�ł���  false:�ς�ł��Ȃ� )
	bool					SemiTransState ;					// ���̃t���[���ɔ������v�f�����邩�ǂ���( true:����  false:�Ȃ� )
} ;

// ���f���A�j���[�V�������\����
struct MV1_MODEL_ANIM
{
	bool					Use ;								// ���̍\���̂��L�����ǂ���( true :�L��  false:���� )
	float					BlendRate ;							// �u�����h��
	MV1_ANIM				*Anim ;								// �A�j���[�V�������ւ̃|�C���^
} ;

// ���f���A�j���[�V�����Z�b�g���\����
struct MV1_MODEL_ANIMSET
{
	bool					Use ;								// ���̍\���̂��L�����ǂ���( true :�L��  false:���� )
	bool					DisableShapeFlag ;					// �V�F�C�v�A�j���[�V�����𖳌��ɂ��邩�ǂ���
	int						BaseDataHandle ;					// ���f����{�f�[�^�n���h��
	int						BaseDataAnimIndex ;					// ���f����{�f�[�^���̃A�j���[�V�����f�[�^�̃C���f�b�N�X
	int						UseAnimNum ;						// �K�����Ă���A�j���[�V�����̐�
	MV1_ANIMSET				*AnimSet ;							// �A�j���[�V�����Z�b�g���ւ̃|�C���^
} ;

// ���f�����s�p�\����
struct MV1_MODEL
{
	HANDLEINFO				HandleInfo ;						// �n���h�����ʃf�[�^

	void					*DataBuffer ;						// �t���[����}�e���A����A�j���[�V�����Ȃǂ��i�[����o�b�t�@�ւ̃|�C���^

	MV1_MODEL				*UseBaseDataNext ;					// �������f����{�f�[�^���g�p���Ă��鎟�̃��f���f�[�^�ւ̃|�C���^
	MV1_MODEL				*UseBaseDataPrev ;					// �������f����{�f�[�^���g�p���Ă���O�̃��f���f�[�^�ւ̃|�C���^

	int						BaseDataHandle ;					// ���f���̊�{�f�[�^�̃n���h��
	MV1_MODEL_BASE			*BaseData ;							// ���f����{�f�[�^�ւ̃|�C���^

	DWORD					*ChangeDrawMaterialFlag ;			// �`��p�}�e���A���ύX�m�F�p�r�b�g�f�[�^
	DWORD					*ChangeMatrixFlag ;					// �s��ύX�m�F�p�r�b�g�f�[�^
	DWORD					ChangeDrawMaterialFlagSize ;		// �`��p�}�e���A���ύX�m�F�p�r�b�g�f�[�^�̃T�C�Y( �o�C�g�P�� )
	DWORD					ChangeMatrixFlagSize ;				// �s��ύX�m�F�p�r�b�g�f�[�^�̃T�C�Y( �o�C�g�P�� )

	VECTOR					Translation ;						// ���s�ړ��l
	MV1_ROTATE				Rotation ;							// ��]�l
	VECTOR					Scale ;								// �g��l
	MATRIX_4X4CT			Matrix ;							// �s��
	bool					ValidMatrix ;						// �s��ɗL���Ȓl�������Ă��邩( true:�����Ă���  false:�����Ă��Ȃ� )

	bool					LocalWorldMatrixSetupFlag ;			// ���f���ƃ��f�����̃t���[���̍s��̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:���Ă��Ȃ� )
	MATRIX_4X4CT			LocalWorldMatrix ;					// ���[�J�������[���h�s��

	MV1_FRAME				*Frame ;							// �t���[�����ւ̃|�C���^
	int						TopFrameNum ;						// �ŏ�ʃt���[���̐�
	MV1_FRAME				**TopFrameList ;					// �ŏ�ʃt���[�����X�g�ւ̃|�C���^
	MATRIX_4X4CT			**SkinBoneUseFrameMatrix ;			// �X�L�j���O���b�V�����g�p���Ă���{�[���̍s��ւ̃|�C���^�̔z��

	MATRIX_4X4CT			*SkinBoneMatrix ;					// BaseData->SkinBone->ModelLocalMatrix �� BaseData->SkinBone->Frame �������t���[���� LocalWorldMatrix ����Z�������̂̔z��

	MV1_SHAPE_VERTEX		*ShapeVertex ;						// �V�F�C�v���_���ւ̃|�C���^
	bool					ShapeChangeFlag ;					// �V�F�C�v�̏�񂪕ω��������A�t���O( true:�ω�����  false:�ω����Ă��Ȃ� )
	bool					ShapeDisableFlag ;					// �V�F�C�v���g�p���Ȃ����ǂ����̃t���O( true:�g�p���Ȃ�  false:�g�p���� )

	MV1_PHYSICS_RIGIDBODY	*PhysicsRigidBody ;					// ���̏��ւ̃|�C���^
	MV1_PHYSICS_JOINT		*PhysicsJoint ;						// �W���C���g���ւ̃|�C���^
	int						PhysicsResetRequestFlag ;			// ���Z�b�g���N�G�X�g�t���O

	MV1_TRIANGLE_LIST		*TriangleList ;						// �g���C�A���O�����X�g���ւ̃|�C���^
	MV1_MESH				*Mesh ;								// ���b�V�����ւ̃|�C���^
	MV1_MATERIAL			*Material ;							// �}�e���A�����ւ̃|�C���^
	MV1_TEXTURE				*Texture ;							// �e�N�X�`�����ւ̃|�C���^
	int						TextureAllocMem ;					// �e�N�X�`���f�[�^�p�Ƀ��������m�ۂ��Ă��邩�ǂ���( TRUE:���Ă���  FALSE:���Ă��Ȃ� )

	MV1_TLIST_NORMAL_POS	*ShapeNormalPosition ;				// �V�F�C�v�p�g���C�A���O�����X�g�̃{�[����񖳂����W�f�[�^
	MV1_TLIST_SKIN_POS_4B	*ShapeSkinPosition4B ;				// �V�F�C�v�p�g���C�A���O�����X�g�̂S�{�[���X�L�j���O���b�V�����W�f�[�^
	MV1_TLIST_SKIN_POS_8B	*ShapeSkinPosition8B ;				// �V�F�C�v�p�g���C�A���O�����X�g�̂W�{�[���X�L�j���O���b�V�����W�f�[�^
	MV1_TLIST_SKIN_POS_FREEB *ShapeSkinPositionFREEB ;			// �V�F�C�v�p�g���C�A���O�����X�g�̂X�{�[���ȏ�X�L�j���O���b�V�����W�f�[�^

	bool					SetupTransformPolygon ;				// ���_�ϊ�����|���S�����X�g�̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	bool					SetupNonTransformPolygon ;			// ���_�ϊ��Ȃ��|���S�����X�g�̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	MV1_REF_POLYGONLIST		*TransformPolygon ;					// ���_�ϊ�����|���S�����X�g
	MV1_REF_POLYGONLIST		*NonTransformPolygon ;				// ���_�ϊ��Ȃ��|���S�����X�g

	bool					SetupCollision ;					// �R���W�������̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )
	MV1_COLLISION			*Collision ;						// �R���W�������

	int						AnimSetNum ;						// �Z�b�g����Ă���A�j���[�V�����Z�b�g�̐�
	int						AnimSetMaxNum ;						// ���݃Z�b�g�ł���A�j���[�V�����Z�b�g�̍ő吔
	MV1_MODEL_ANIMSET		*AnimSet ;							// �A�j���[�V�����Z�b�g���ւ̃|�C���^�z��
	MV1_MODEL_ANIM			*Anim ;								// �A�j���[�V�������ւ̃|�C���^�z��
	bool					AnimSetupFlag ;						// �A�j���[�V�����̃p�����[�^�����ɂ����s��̃Z�b�g�A�b�v���������Ă��邩�ǂ���( true:�������Ă���  false:�������Ă��Ȃ� )

	MV1_DRAW_MATERIAL		DrawMaterial ;						// �`��p�}�e���A�����
	bool					SemiTransStateSetupFlag ;			// SemiTransState �̃Z�b�g�A�b�v���ς�ł��邩( true:�ς�ł���  false:�ς�ł��Ȃ� )
	bool					SemiTransState ;					// ���̃��f���ɔ������v�f�����邩�ǂ���( true:����  false:�Ȃ� )

	int						MeshCategoryHide[ DX_MV1_MESHCATEGORY_NUM ] ;	// �J�e�S���ʂ̃��b�V����\���t���O
	int						EnableZBufferFlag ;					// �y�o�b�t�@�̗L���t���O
	int						WriteZBufferFlag ;					// �y�o�b�t�@�̍X�V���s�����A�t���O
	int						ZBufferCmpType ;					// �y�l�̔�r���[�h
	int						ZBias ;								// �y�o�C�A�X

	bool					WireFrame ;							// ���C���[�t���[���`������邩�ǂ����̃t���O

	int						MaxAnisotropy ;						// �ٕ����t�B���^�����O�̍ő原��

	float					PhysicsGravity ;					// �������Z�Ŏg�p����d�̓p�����[�^
	DWORD					BulletPhysicsDataBuffer[ 32 ] ;		// BULLET_PHYSICS ���i�[����o�b�t�@
} ;







// ���f���f�[�^�Ǘ��p�\����
struct MV1_MODEL_MANAGE
{
	bool					Initialize ;						// �������ς݂��A�t���O( true:�������ς�  false:�������� )

	int						UseOrigShaderFlag ;					// ���f���̕`��� SetUseVertexShader, SetUsePixelShader �Ŏw�肵���V�F�[�_�[���g�p���邩�ǂ���( TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ) )

	int						LoadModelToReMakeNormal ;			// ���f���̓ǂݍ��ݏ����Ŗ@���̍Čv�Z���s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )
	float					LoadModelToReMakeNormalSmoothingAngle ;		// ���f���̓ǂݍ��ݏ������ɍs���@��̍Čv�Z�Ŏg�p����X���[�W���O�p�x( �P�ʂ̓��W�A�� )
	int						LoadModelToPositionOptimize ;		// ���f���̓ǂݍ��ݏ����ō��W�̍œK���������s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )
	int						LoadModelToUsePhysicsMode ;			// �ǂݍ��ރ��f���̕������Z���[�h��ݒ肷��( DX_LOADMODEL_PHYSICS_LOADCALC �� )
	int						LoadModelToWorldGravityInitialize ;	// �ǂݍ��ރ��f���̕������Z�ɓK�p����d�̓p�����[�^�����������ꂽ���ǂ���
	float					LoadModelToWorldGravity ;			// �ǂݍ��ރ��f���̕������Z�ɓK�p����d�̓p�����[�^
	VECTOR					LoadCalcPhysicsWorldGravity[ MV1_LOADCALC_PHYSICS_GRAVITY_NUM ] ;	// �ǂݍ��ރ��f���̎��O�v�Z�Ɏg�p����d��

	int						AnimFilePathValid ;					// AnimFilePath ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	TCHAR					AnimFileName[ 512 ] ;				// �A�j���[�V�����t�@�C���̖��O
	TCHAR					AnimFileDirPath[ 512 ] ;			// �A�j���[�V�����t�@�C���̃f�B���N�g���p�X

	float					SinTable[ MV1_SINTABLE_DIV ] ;		// �T�C���e�[�u��

	int						ModelBaseNum ;						// ���f����{�f�[�^��
	int						ModelBaseMaxNum ;					// ���f����{�f�[�^�̌��݂̍ő吔
	int						ModelBaseNextIndex ;				// ���̃��f����{�f�[�^�̊i�[�����݂�C���f�b�N�X
	MV1_MODEL_BASE			**ModelBase ;						// ���f����{�f�[�^�|�C���^�̔z��ւ̃|�C���^

	int						ModelNum ;							// ���f���̃f�[����
	int						ModelMaxNum ;						// ���f���̌��݂̍ő吔
	int						ModelNextIndex ;					// ���̃��f���f�[�^�̊i�[�����݂�C���f�b�N�X
	int						ModelNextCheckNumber ;				// ���̃��f���f�[�^�ɐU��ԍ�
	MV1_MODEL				**Model ;							// ���f���|�C���^�̔z��ւ̃|�C���^

	int						( *AddLoadFunc[ MV1_ADD_LOAD_FUNC_MAXNUM ] )( const struct MV1_MODEL_LOAD_PARAM *LoadParam ) ;		// �ǉ����f�����[�h�֐�
	int						AddLoadFuncNum ;					// �ǉ����f�����[�h�֐��̐�

	MV1_MESH				**DrawMeshList ;					// �`�悷�郁�b�V���̃A�h���X�z����i�[���郁�����̈�
	int						DrawMeshListSize ;					// �`�悷�郁�b�V���̃A�h���X�z����i�[���郁�����̈�̃T�C�Y( ���P�� )

	int						TexNoneHandle ;						// �e�N�X�`�����������f���ɒ���e�N�X�`��
	int						ToonDefaultGradTexHandle[ 2 ] ;		// �g�D�[���p�O���f�[�V�����e�N�X�`�����������f���ɒ���e�N�X�`��

	int						WorldMatrixIsIdentity ;				// ���[���h�s��ɒP�ʍs�񂪃Z�b�g����Ă��邩�ǂ���( TRUE:����Ă���  FALSE:����Ă��Ȃ� )
//	MATRIX					OrigLocalWorldMatrix ;				// ���Ƃ��Ɛݒ肳��Ă����k�v�s��

	// �e�X�g�p�V�F�[�_�[
	DX_DIRECT3DPIXELSHADER9  *PS_Test ;
	DX_DIRECT3DVERTEXSHADER9 *VS_Test ;

//	int						UseBaseVertexShaderIndex ;			// �g�p���钸�_�V�F�[�_�[�̃��C�g�E�t�H�O�E�t�H���V�F�[�f�B���O�̗L���̂ݐݒ肵���l
//	int						UseBasePixelShaderIndex ;			// �g�p����s�N�Z���V�F�[�_�[�̃��C�g�E�t�H���V�F�[�f�B���O�̗L���̂ݐݒ肵���l

//	MV1_MATERIAL			*SetMaterial ;						// �Z�b�g����Ă���}�e���A��
} ;

// �Ǝ��t�@�C���ǂݍ��݊֐��̕ϐ����܂Ƃ߂��\����
struct MV1_FILE_READ_FUNC
{
	int						( *Read )( const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData ) ;	// �Ǝ��t�@�C���ǂݍ��݊֐�
	int						( *Release )( void *FileImageAddr, void *FileReadFuncData ) ;										// �Ǝ��t�@�C������֐�
	void					*Data ;								// �Ǝ��t�@�C���ǂݍ��݊֐��ɓn���f�[�^
} ;

// �t�@�C�����烂�f���n���h�����쐬���鏈���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct MV1LOADMODEL_GPARAM
{
	LOADGRAPH_GPARAM		LoadGraphGParam ;

	int						LoadModelToReMakeNormal ;			// ���f���̓ǂݍ��ݏ����Ŗ@���̍Čv�Z���s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )
	float					LoadModelToReMakeNormalSmoothingAngle ;		// ���f���̓ǂݍ��ݏ������ɍs���@��̍Čv�Z�Ŏg�p����X���[�W���O�p�x( �P�ʂ̓��W�A�� )
	int						LoadModelToPositionOptimize ;		// ���f���̓ǂݍ��ݏ����ō��W�̍œK���������s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )
	int						LoadModelToUsePhysicsMode ;			// �ǂݍ��ރ��f���̕������Z���[�h��ݒ肷��( DX_LOADMODEL_PHYSICS_LOADCALC �� )
	int						LoadModelToWorldGravityInitialize ;	// �ǂݍ��ރ��f���̕������Z�ɓK�p����d�̓p�����[�^�����������ꂽ���ǂ���
	float					LoadModelToWorldGravity ;			// �ǂݍ��ރ��f���̕������Z�ɓK�p����d�̓p�����[�^
	VECTOR					LoadCalcPhysicsWorldGravity[ MV1_LOADCALC_PHYSICS_GRAVITY_NUM ] ;	// �ǂݍ��ރ��f���̎��O�v�Z�Ɏg�p����d��

	int						AnimFilePathValid ;					// AnimFilePath ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	TCHAR					AnimFileName[ 512 ] ;				// �A�j���[�V�����t�@�C���̖��O
	TCHAR					AnimFileDirPath[ 512 ] ;			// �A�j���[�V�����t�@�C���̃f�B���N�g���p�X
} ;

// ���f���f�[�^�ǂݍ��ݏ����֐��̈������܂Ƃ߂��\����
struct MV1_MODEL_LOAD_PARAM
{
	MV1LOADMODEL_GPARAM		GParam ;							// �O���[�o���p�����[�^

	void					*DataBuffer ;						// ���f���t�@�C���C���[�W
	int						DataSize ;							// ���f���t�@�C���T�C�Y
	const TCHAR				*FilePath ;							// �t�@�C���p�X
	const TCHAR				*Name ;								// ���f����
	const TCHAR				*CurrentDir ;						// �J�����g�f�B���N�g��

	MV1_FILE_READ_FUNC		*FileReadFunc ;						// �Ǝ��t�@�C���ǂݍ��݊֐��̕ϐ����܂Ƃ߂��\���̂ւ̃|�C���^
	int						ASyncThread ;						// �񓯊��ǂݍ��݃X���b�h�ł̓ǂݍ��݂��ǂ���( TRUE:�񓯊��ǂݍ��݃X���b�h�ł̓ǂݍ��ݏ���  FALSE:�����ǂݍ��� )
} ;

// �f�[�^�錾 -----------------------------------

extern MV1_MODEL_MANAGE MV1Man ;

// �֐��v���g�^�C�v�錾 -------------------------

// �������Ǘ��n
#ifdef _DEBUG
	extern	void		*AddMemArea( int Size, MEMINFO **FirstMem, const char *FileName = NULL, int Line = 0 ) ;// �������̈�̊m��
#else
	extern	void		*AddMemArea( int Size, MEMINFO **FirstMem ) ;											// �������̈�̊m��
#endif
extern	int				SubMemArea( MEMINFO **FirstMem, void *Buffer ) ;										// �������̈�̉��
extern	int				ClearMemArea( MEMINFO **FirstMem ) ;													// �S�Ẵ������̈�̉��


// �r�b�g�f�[�^�֌W
extern	int				InitBitList( BITLIST *BitList, int BitDepth, int DataNum, MEMINFO **FirstMem ) ;			// �r�b�g�f�[�^���X�g������������( -1:���s  0:���� )
extern	int				SetBitList( BITLIST *BitList, int Index, int SetBitIndex ) ;								// �r�b�g�f�[�^���X�g���̎w��̗v�f�̃r�b�g�𗧂Ă�
extern	int				PressBitList( BITLIST *BitListDest, BITLIST *BitListSrc, MEMINFO **FirstMem ) ;				// �r�b�g�f�[�^���X�g���̒l�̎�ނ𒊏o����( �o�͑��͏���������Ă���K�v�͖��� )( -1:���s  0:���� )
extern	int				SearchBitList( BITLIST *BitListTarget, void *Buffer ) ;										// �w��̃r�b�g�f�[�^�Ɉ�v����^�[�Q�b�g���̃f�[�^�C���f�b�N�X�𓾂�( -1:�G���[�A���͖�������  -1�ȊO:�f�[�^�C���f�b�N�X )
extern	int				SearchBitList( BITLIST *BitListTarget, BITLIST *BitListSrc, int SrcIndex ) ;				// �\�[�X���̎w��̃r�b�g�f�[�^�Ɉ�v����^�[�Q�b�g���̃f�[�^�C���f�b�N�X�𓾂�( -1:�G���[�A���͖�������  -1�ȊO:�f�[�^�C���f�b�N�X )
extern	int				CmpBitList( BITLIST *BitList1, int Index1, BITLIST *BitList2, int Index2 ) ;				// ��̗v�f����v���Ă��邩�ǂ������擾����( 0:��v���Ă���  0:��v���Ă��Ȃ� )
extern	int				GetBitList( BITLIST *BitList, int Index, void *Buffer ) ;									// �r�b�g�f�[�^���X�g����w��ԍ��̃f�[�^���擾����
extern	int				CopyBitList( BITLIST *BitListDest, int Index, void *Buffer ) ;								// �w��̃r�b�g�f�[�^���w��̃C���f�b�N�X�ɃR�s�[����
extern	int				OrBitList( BITLIST *BitList, int Index, void *Buffer ) ;									// �C�ӂ̃r�b�g�f�[�^�ƃr�b�g�f�[�^���X�g���̎w��̃f�[�^�� Or ���Z����
extern	int				GetBitCount( void *Buffer, int UnitSize ) ;													// �w��̃r�b�g�f�[�^���A���r�b�g�����Ă��邩���ׂ�
extern	int				AddBitList( BITLIST *BitListDest, void *Buffer, int RefCount = 1 ) ;						// �w��̃r�b�g�f�[�^���A�^�[�Q�b�g���̃r�b�g�f�[�^�ɉ�����
extern	int				AddBitList( BITLIST *BitListDest, BITLIST *BitListSrc, int SrcIndex, int RefCount=1 ) ;		// �\�[�X���̎w��̃r�b�g�f�[�^���A�^�[�Q�b�g���̃r�b�g�f�[�^�ɉ�����
extern	int				GetBitListNumber( BITLIST *BitList, int Index, WORD *Buffer ) ;								// �w��̃r�b�g�f�[�^���ŗ����Ă���r�b�g�̃��X�g���擾����( �߂�l  -1:�G���[  0�ȏ�:�����Ă���r�b�g�̐� )

// 16bit�⏕���֌W
extern	BYTE			MV1AnimKey16BitMinFtoB( float Min ) ;													// float�^�̒l���� MV1_ANIM_KEY_16BIT�\���̂� Min �ϐ��p�̒l���쐬����
extern	BYTE			MV1AnimKey16BitUnitFtoB( float Unit ) ;													// float�^�̒l���� MV1_ANIM_KEY_16BIT�\���̂� Unit �ϐ��p�̒l���쐬����
extern	float			MV1AnimKey16BitMinBtoF( BYTE Min ) ;													// MV1_ANIM_KEY_16BIT�\���̂� Min �ϐ��̒l���� float�^�̒l���쐬����
extern	float			MV1AnimKey16BitUnitBtoF( BYTE Unit ) ;													// MV1_ANIM_KEY_16BIT�\���̂� Unit �ϐ��̒l���� float�^�̒l���쐬����

// �⏕���Z�֌W
extern	void			ConvertMatrixToMatrix4x4c( MATRIX_4X4CT *Out, MATRIX *In ) ;							// MATRIX �\���̂� MATRIX_4X4CT �\���̂ɕϊ�����
extern	void			ConvertMatrix4x4cToMatrix( MATRIX *Out, MATRIX_4X4CT *In ) ;							// MATRIX_4X4CT �\���̂� MATRIX �\���̂ɕϊ�����

// �f�[�^��v�����n
extern	void			MakeDataCmpInfo( DATACMPINFO *CmpInfo, void *Image, int Size ) ;						// �o�C�i���C���[�W����f�[�^��v�����f�[�^���쐬����
extern	int				CheckDataCmpInfo( DATACMPINFO *CmpInfo1, DATACMPINFO *CmpInfo2 ) ;						// ��̃`�F�b�N�f�[�^����v���Ă��邩�ǂ������擾����( 1:��v���Ă���  0:��v���Ă��Ȃ� )

// �X�V���o���\�z�p�֐�
extern	void			MV1ChangeInfoSetup( MV1_CHANGE_BASE *ChangeB, void *FillTable, int BitAddress, int FillBitNum ) ;	// ��ԕω��Ǘ��p�\���̂̃Z�b�g�A�b�v���s��

// ���f���ǂݍ��ݕ⏕�n
extern	int				AddVertexInfo( MV1_MAKEVERTINDEXINFO **InfoTable, MV1_MAKEVERTINDEXINFO *InfoBuffer, int *InfoNum, void *DataBuffer, int DataUnitSize, int DataNum, int AddDataIndex, void *AddData ) ;		// MV1_MAKEVERTINDEXINFO �𗘗p������������f�[�^������⏕����֐�
extern	int				MV1MakeMeshBinormalsAndTangents( MV1_MESH_BASE *Mesh ) ;								// ���b�V���̏]�@���Ɛڐ����v�Z����
extern	int				MV1SetupTriangleListPositionAndNormal( MV1_TRIANGLE_LIST_BASE *List ) ;					// �g���C�A���O�����X�g�̍��W�Ɩ@�����̃Z�b�g�A�b�v���s��
extern	int				MV1SetupShapeTriangleListPositionAndNormal( MV1_TRIANGLE_LIST *TList ) ;				// �V�F�C�v�p�g���C�A���O�����X�g�̍��W�Ɩ@�����̃Z�b�g�A�b�v���s��


// �O���[�o���ȏ������ƌ�n��
extern	int				MV1Initialize() ;																		// ���f���@�\�̏�����
extern	int				MV1Terminate() ;																		// ���f���@�\�̌�n��

// �e�N�X�`���̒ǉ�
extern	int				__MV1LoadTexture(
							  void **ColorImage, int *ColorImageSize,
							  void **AlphaImage, int *AlphaImageSize,
							  int *GraphHandle,
							  int *SemiTransFlag,
							  char **ColorFilePathMem, char **AlphaFilePathMem,
							  const wchar_t *ColorFilePath, const wchar_t *AlphaFilePath, const wchar_t *StartFolderPath,
							  int BumpImageFlag, float BumpImageNextPixelLength,
							  int ReverseFlag,
							  int IgnoreBmp32Alpha,
							  const MV1_FILE_READ_FUNC *FileReadFunc,
							  bool ValidImageAddr,
							  int ASyncThread ) ;
extern	int				MV1CreateTextureColorBaseImage(
										BASEIMAGE *DestColorBaseImage,
										BASEIMAGE *DestAlphaBaseImage,
										void *ColorFileImage, int ColorFileSize,
										void *AlphaFileImage, int AlphaFileSize,
										int BumpImageFlag = FALSE, float BumpImageNextPixelLength = 0.1f,
										int ReverseFlag = FALSE ) ;												// ���f���p�e�N�X�`���̃J���[�C���[�W���쐬����
extern	int				MV1ReloadTexture( void ) ;																// �e�N�X�`���̍ēǂݍ���

// �ǉ����[�h�֐��֌W
extern	int				MV1AddLoadFunc( int ( *AddLoadFunc )( const MV1_MODEL_LOAD_PARAM *LoadParam ) ) ;		// ���f���ǂݍ��݊֐���ǉ�����
extern	int				MV1SubLoadFunc( int ( *AddLoadFunc )( const MV1_MODEL_LOAD_PARAM *LoadParam ) ) ;		// ���f���ǂݍ��݊֐����폜����

// ���f����{�f�[�^�n���h���̒ǉ��E�폜
extern	int				MV1InitModelBase( void ) ;																// �L���ȃ��f����{�f�[�^�����ׂč폜����
extern	int				MV1AddModelBase( void ) ;																// ���f����{�f�[�^��ǉ�����( -1:�G���[  0�ȏ�:���f����{�f�[�^�n���h�� )
extern	int				MV1SubModelBase( int MBHandle ) ;														// ���f����{�f�[�^���폜����
extern	int				MV1CreateCloneModelBase( int SrcMBHandle ) ;											// ���f����{�f�[�^�𕡐�����

extern	int				InitializeModelBaseHandle( HANDLEINFO *HandleInfo ) ;									// ���f����{�f�[�^�n���h���̏�����
extern	int				TerminateModelBaseHandle( HANDLEINFO *HandleInfo ) ;									// ���f����{�f�[�^�n���h���̌�n��

// �����Z�b�g�A�b�v�n
extern	void			MV1SetupInitializeMatrixBase( MV1_MODEL_BASE *ModelBase ) ;								// ������Ԃ̕ϊ��s����Z�b�g�A�b�v����
extern	void			MV1SetupToonOutLineTriangleList( MV1_TRIANGLE_LIST_BASE *MBTList ) ;					// �g�D�[���֊s���p�̃��b�V�����쐬����

// �@���Čv�Z�E���W�œK��
extern	int				MV1ReMakeNormalBase( int MBHandle, float SmoothingAngle = 89.5f * DX_PI_F / 180.0f, int ASyncThread = FALSE ) ;	// ���f���S�̖̂@�����Čv�Z����
extern	int				MV1ReMakeNormalFrameBase( int MBHandle, int FrameIndex, float SmoothingAngle = 89.5f * DX_PI_F / 180.0f ) ;	// �w��t���[���������b�V���̖@�����Čv�Z����
extern	int				MV1PositionOptimizeBase( int MBHandle ) ;												// ���f���S�̂̍��W�����œK������
extern	int				MV1PositionOptimizeFrameBase( int MBHandle, int FrameIndex ) ;							// �w��t���[���������b�V���̍��W�����œK������

// ��{�f�[�^���}�e���A��
extern	int				MV1GetMaterialNumBase( int MBHandle ) ;													// ���f���Ŏg�p���Ă���}�e���A���̐����擾����
extern	const char *	MV1GetMaterialNameBase( int MBHandle, int MaterialIndex ) ;								// �w��̃}�e���A���̖��O���擾����
extern	const wchar_t *	MV1GetMaterialNameBaseW( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̖��O���擾����
extern	int				MV1SetMaterialTypeBase( int MBHandle, int MaterialIndex, int Type ) ;					// �w��̃}�e���A���̃^�C�v��ύX����( Type : DX_MATERIAL_TYPE_NORMAL �Ȃ� )
extern	int				MV1GetMaterialTypeBase( int MBHandle, int MaterialIndex ) ;								// �w��̃}�e���A���̃^�C�v���擾����( �߂�l : DX_MATERIAL_TYPE_NORMAL �Ȃ� )
extern	COLOR_F			MV1GetMaterialDifColorBase( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃f�B�t���[�Y�J���[���擾����
extern	COLOR_F			MV1GetMaterialSpcColorBase( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃X�y�L�����J���[���擾����
extern	COLOR_F			MV1GetMaterialEmiColorBase( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃G�~�b�V�u�J���[���擾����
extern	COLOR_F			MV1GetMaterialAmbColorBase( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃A���r�G���g�J���[���擾����
extern	float			MV1GetMaterialSpcPowerBase( int MBHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃X�y�L�����̋������擾����
extern	int				MV1SetMaterialDifMapTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���Ńf�B�t���[�Y�}�b�v�Ƃ��Ďg�p����e�N�X�`�����w�肷��
extern	int				MV1GetMaterialDifMapTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ńf�B�t���[�Y�}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
extern	int				MV1SetMaterialSpcMapTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���ŃX�y�L�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����w�肷��
extern	int				MV1GetMaterialSpcMapTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���ŃX�y�L�����}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
extern	int				MV1SetMaterialNormalMapTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;	// �w��̃}�e���A���Ŗ@���}�b�v�Ƃ��Ďg�p����e�N�X�`�����w�肷��
extern	int				MV1GetMaterialNormalMapTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ŗ@���}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
extern	int				MV1SetMaterialDifColorBase( int MBHandle, int MaterialIndex, COLOR_F Color ) ;			// �w��̃}�e���A���̃f�B�t���[�Y�J���[��ݒ肷��
extern	int				MV1SetMaterialSpcColorBase( int MBHandle, int MaterialIndex, COLOR_F Color ) ;			// �w��̃}�e���A���̃X�y�L�����J���[��ݒ肷��
extern	int				MV1SetMaterialEmiColorBase( int MBHandle, int MaterialIndex, COLOR_F Color ) ;			// �w��̃}�e���A���̃G�~�b�V�u�J���[��ݒ肷��
extern	int				MV1SetMaterialAmbColorBase( int MBHandle, int MaterialIndex, COLOR_F Color ) ;			// �w��̃}�e���A���̃A���r�G���g�J���[��ݒ肷��
extern	int				MV1SetMaterialSpcPowerBase( int MBHandle, int MaterialIndex, float Power ) ;			// �w��̃}�e���A���̃X�y�L�����̋�����ݒ肷��
extern	int				MV1SetMaterialDifGradTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���Ńg�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int				MV1GetMaterialDifGradTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ńg�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int				MV1SetMaterialSpcGradTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�y�L�����O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int				MV1GetMaterialSpcGradTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�y�L�����O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int				MV1SetMaterialSphereMapTextureBase( int MBHandle, int MaterialIndex, int TexIndex ) ;	// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�t�B�A�}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int				MV1GetMaterialSphereMapTextureBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�t�B�A�}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int				MV1SetMaterialDifGradBlendTypeBase( int MBHandle, int MaterialIndex, int BlendType ) ;	// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����f�B�t���[�Y�O���f�[�V�����}�b�v�ƃf�B�t���[�Y�J���[�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1GetMaterialDifGradBlendTypeBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����f�B�t���[�Y�O���f�[�V�����}�b�v�ƃf�B�t���[�Y�J���[�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1SetMaterialSpcGradBlendTypeBase( int MBHandle, int MaterialIndex, int BlendType ) ;	// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�y�L�����O���f�[�V�����}�b�v�ƃX�y�L�����J���[�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1GetMaterialSpcGradBlendTypeBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�y�L�����O���f�[�V�����}�b�v�ƃX�y�L�����J���[�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1SetMaterialSphereMapBlendTypeBase( int MBHandle, int MaterialIndex, int BlendType ) ;// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�t�B�A�}�b�v�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1GetMaterialSphereMapBlendTypeBase( int MBHandle, int MaterialIndex ) ;				// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�t�B�A�}�b�v�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int				MV1SetMaterialOutLineWidthBase( int MBHandle, int MaterialIndex, float Width ) ;		// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̑�����ݒ肷��
extern	float			MV1GetMaterialOutLineWidthBase( int MBHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̃h�b�g�P�ʂ̑������擾����
extern	int				MV1SetMaterialOutLineDotWidthBase( int MBHandle, int MaterialIndex, float Width ) ;		// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̃h�b�g�P�ʂ̑�����ݒ肷��
extern	float			MV1GetMaterialOutLineDotWidthBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̑������擾����( 0.0f �` 1.0f )
extern	int				MV1SetMaterialOutLineColorBase( int MBHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̐F��ݒ肷��
extern	COLOR_F			MV1GetMaterialOutLineColorBase( int MBHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̐F���擾����
extern	int				MV1SetMaterialDrawBlendModeBase( int MBHandle, int MaterialIndex, int BlendMode ) ;		// �w��̃}�e���A���̕`��u�����h���[�h��ݒ肷��( DX_BLENDMODE_ALPHA �� )
extern	int				MV1SetMaterialDrawBlendParamBase( int MBHandle, int MaterialIndex, int BlendParam ) ;	// �w��̃}�e���A���̕`��u�����h�p�����[�^��ݒ肷��
extern	int				MV1GetMaterialDrawBlendModeBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̕`��u�����h���[�h���擾����( DX_BLENDMODE_ALPHA �� )
extern	int				MV1GetMaterialDrawBlendParamBase( int MBHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̕`��u�����h�p�����[�^��ݒ肷��

// ��{�f�[�^���e�N�X�`���֌W
extern	int				MV1GetTextureNumBase( int MBHandle ) ;													// �e�N�X�`���̐����擾
extern	int				MV1AddTextureBase( 
							int MBHandle,
							const char *Name,
							const char *ColorFilePathA, const char *AlphaFilePathA,
							const wchar_t *ColorFilePathW, const wchar_t *AlphaFilePathW,
							void *ColorFileImage, void *AlphaFileImage,
							int AddressModeU, int AddressModeV, int FilterMode,
							int BumpImageFlag, float BumpImageNextPixelLength,
							bool ReverseFlag,
							bool Bmp32AllZeroAlphaToXRGB8Flag,
							int ASyncThread ) ;																	// �e�N�X�`���̒ǉ�
extern	int				MV1DeleteTextureBase( int MBHandle, int TexIndex ) ;									// �e�N�X�`���̍폜
extern	const char *	MV1GetTextureNameBase( int MBHandle, int TexIndex ) ;									// �e�N�X�`���̖��O���擾
extern	const wchar_t *	MV1GetTextureNameBaseW( int MBHandle, int TexIndex ) ;									// �e�N�X�`���̖��O���擾
extern	int				MV1SetTextureColorFilePathBase( int MBHandle, int TexIndex, const char *FilePath ) ;	// �J���[�e�N�X�`���̃t�@�C���p�X��ύX����
extern	int				MV1SetTextureColorFilePathBaseW( int MBHandle, int TexIndex, const wchar_t *FilePathW ) ;	// �J���[�e�N�X�`���̃t�@�C���p�X��ύX����
extern	const char *	MV1GetTextureColorFilePathBase( int MBHandle, int TexIndex ) ;							// �J���[�e�N�X�`���̃t�@�C���p�X���擾
extern	const wchar_t *	MV1GetTextureColorFilePathBaseW( int MBHandle, int TexIndex ) ;							// �J���[�e�N�X�`���̃t�@�C���p�X���擾
extern	int				MV1SetTextureAlphaFilePathBase( int MBHandle, int TexIndex, const char *FilePath ) ;	// �A���t�@�e�N�X�`���̃t�@�C���p�X��ύX����
extern	int				MV1SetTextureAlphaFilePathBaseW( int MBHandle, int TexIndex, const wchar_t *FilePathW ) ;	// �A���t�@�e�N�X�`���̃t�@�C���p�X��ύX����
extern	const char *	MV1GetTextureAlphaFilePathBase( int MBHandle, int TexIndex ) ;							// �A���t�@�e�N�X�`���̃t�@�C���p�X���擾
extern	const wchar_t *	MV1GetTextureAlphaFilePathBaseW( int MBHandle, int TexIndex ) ;							// �A���t�@�e�N�X�`���̃t�@�C���p�X���擾
extern	int				MV1SetTextureGraphHandleBase( int MBHandle, int TexIndex, int GrHandle, int SemiTransFlag ) ;	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����( GrHandle �� -1 �ɂ���Ɖ��� )
extern	int				MV1GetTextureGraphHandleBase( int MBHandle, int TexIndex ) ;							// �e�N�X�`���̃O���t�B�b�N�n���h�����擾����
extern	int				MV1SetTextureAddressModeBase( int MBHandle, int TexIndex, int AddrUMode, int AddrVMode ) ;	// �e�N�X�`���̃A�h���X���[�h��ݒ肷��( AddrUMode �� DX_TEXADDRESS_WRAP �� )
extern	int				MV1GetTextureAddressModeUBase( int MBHandle, int TexIndex ) ;							// �e�N�X�`���̂t�l�̃A�h���X���[�h���擾����( �߂�l:DX_TEXADDRESS_WRAP �� )
extern	int				MV1GetTextureAddressModeVBase( int MBHandle, int TexIndex ) ;							// �e�N�X�`���̂u�l�̃A�h���X���[�h���擾����( �߂�l:DX_TEXADDRESS_WRAP �� )
extern	int				MV1GetTextureWidthBase( int MBHandle, int TexIndex ) ;									// �e�N�X�`���̕����擾����
extern	int				MV1GetTextureHeightBase( int MBHandle, int TexIndex ) ;									// �e�N�X�`���̍������擾����
extern	int				MV1GetTextureSemiTransStateBase( int MBHandle, int TexIndex ) ;							// �e�N�X�`���ɔ������v�f�����邩�ǂ������擾����( �߂�l  TRUE:����  FALSE:�Ȃ� )
extern	int				MV1SetTextureBumpImageFlagBase( int MBHandle, int TexIndex, int Flag ) ;				// �e�N�X�`���Ŏg�p���Ă���摜���o���v�}�b�v���ǂ�����ݒ肷��
extern	int				MV1GetTextureBumpImageFlagBase( int MBHandle, int TexIndex ) ;							// �e�N�X�`�����o���v�}�b�v���ǂ������擾����( �߂�l  TRUE:�o���v�}�b�v  FALSE:�Ⴄ )
extern	int				MV1SetTextureBumpImageNextPixelLengthBase( int MBHandle, int TexIndex, float Length ) ;	// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋�����ݒ肷��
extern	float			MV1GetTextureBumpImageNextPixelLengthBase( int MBHandle, int TexIndex ) ;				// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋������擾����
extern	int				MV1SetTextureSampleFilterModeBase( int MBHandle, int TexIndex, int FilterMode ) ;		// �e�N�X�`���̃t�B���^�����O���[�h��ݒ肷��
extern	int				MV1GetTextureSampleFilterModeBase( int MBHandle, int TexIndex ) ;						// �e�N�X�`���̃t�B���^�����O���[�h���擾����( �߂�l  DX_DRAWMODE_BILINEAR�� )

// ���_�J���[�𗘗p���邩�ǂ����̐ݒ�
extern	int				MV1SetMeshUseVertDifColorBase( int MBHandle, int MeshIndex, int UseFlag ) ;				// �w��̃��b�V���̒��_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int				MV1SetMeshUseVertSpcColorBase( int MBHandle, int MeshIndex, int UseFlag ) ;				// �w��̃��b�V���̒��_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int				MV1GetMeshUseVertDifColorBase( int MBHandle, int MeshIndex ) ;							// �w��̃��b�V���̒��_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ����̐ݒ���擾����( �߂�l  TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int				MV1GetMeshUseVertSpcColorBase( int MBHandle, int MeshIndex ) ;							// �w��̃��b�V���̒��_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ����̐ݒ���擾����( �߂�l  TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )

// ���f���f�[�^�\�z�֌W
extern	int				MV1AddModel( void ) ;																	// ���f���f�[�^��ǉ�����( -1:�G���[  0�ȏ�:���f���f�[�^�n���h�� )
extern	int				MV1SubModel( int MV1ModelHandle ) ;														// ���f���f�[�^���폜����
extern	int				MV1MakeModel( int MV1ModelHandle, int MV1ModelBaseHandle, int ASyncThread = FALSE ) ;	// ���f����f�[�^���烂�f���f�[�^���\�z����( -1:�G���[ 0:���� )

extern	int				MV1GetMaxMinPosition( int MHandle, VECTOR *MaxPosition, VECTOR *MinPosition, int ASyncThread = FALSE ) ;	// ���f���̍ő咸�_���W�ƍŏ����_���W���擾����

extern	int				InitializeModelHandle( HANDLEINFO *HandleInfo ) ;										// ���f���f�[�^�n���h���̏�����
extern	int				TerminateModelHandle( HANDLEINFO *HandleInfo ) ;										// ���f���f�[�^�n���h���̌�n��

// ���f���f�[�^�֌W
extern	int				MV1GetModelBaseHandle( int MHandle ) ;													// ���f���n���h���Ŏg�p����Ă��郂�f����{�f�[�^�n���h�����擾����
extern	int				MV1GetModelDataSize( int MHandle, int DataType ) ;										// ���f���̃f�[�^�T�C�Y���擾����
extern	int				MV1GetAnimDataSize( int MHandle, const char *AnimName = NULL, int AnimIndex = -1 ) ;	// �A�j���[�V�����̃f�[�^�T�C�Y���擾����

// ���f���̓ǂݍ��݁E�ۑ��E�����֌W
extern	int				MV1LoadModelToPMX( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �o�l�w�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToPMD( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �o�l�c�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToVMD( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �u�l�c�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToX(   const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �w�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToFBX( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �e�a�w�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToMQO( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �l�p�n�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1LoadModelToMV1( const MV1_MODEL_LOAD_PARAM *LoadParam, int ASyncThread = FALSE ) ;	// �l�u�P�t�@�C����ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int				MV1SetupVertexBufferBase( int MV1ModelBaseHandle, int DuplicateNum = 1, int ASyncThread = FALSE ) ;	// ���f����f�[�^�̒��_�o�b�t�@�̃Z�b�g�A�b�v������( -1:�G���[ )
extern	int				MV1SetupVertexBuffer( int MHandle, int ASyncThread = FALSE ) ;							// ���f���f�[�^�̒��_�o�b�t�@�̃Z�b�g�A�b�v������( -1:�G���[ )
extern	int				MV1SetupVertexBufferAll( int ASyncThread = FALSE ) ;									// ���_�o�b�t�@�̃Z�b�g�A�b�v������( -1:�G���[ )
extern	int				MV1TerminateVertexBufferBase( int MV1ModelBaseHandle ) ;								// ���_�o�b�t�@�̌�n��������( -1:�G���[ )
extern	int				MV1TerminateVertexBuffer( int MV1ModelHandle ) ;										// ���_�o�b�t�@�̌�n��������( -1:�G���[ )
extern	int				MV1TerminateVertexBufferAll( void ) ;													// �S�Ă̒��_�o�b�t�@�̌�n��������( -1:�G���[ )
extern	const TCHAR *	MV1GetModelFileName( int MHandle ) ;													// ���[�h�������f���̃t�@�C�������擾����
extern	const TCHAR *	MV1GetModelDirectoryPath( int MHandle ) ;												// ���[�h�������f�������݂���f�B���N�g���p�X���擾����( ���[�� / �� \ ���t���Ă��܂� )
extern	int				MV1SetupShapeVertex( int MHandle ) ;													// �V�F�C�v�f�[�^�̃Z�b�g�A�b�v������

extern	void			InitMV1LoadModelGParam( MV1LOADMODEL_GPARAM *GParam ) ;									// MV1LOADMODEL_GPARAM �̃f�[�^���Z�b�g����

extern	int				MV1LoadModel_UseGParam( MV1LOADMODEL_GPARAM *GParam, const TCHAR *FileName, int ASyncLoadFlag = FALSE ) ;																																																									// MV1LoadModel �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int				MV1LoadModelFromMem_UseGParam( MV1LOADMODEL_GPARAM *GParam, void *FileImage, int FileSize, int (* FileReadFunc )( const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData ), int (* FileReleaseFunc )( void *MemoryAddr, void *FileReadFuncData ), void *FileReadFuncData = NULL, int ASyncLoadFlag = FALSE ) ;	// MV1LoadModelFromMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����


// ���C�g�֌W
extern	int				MV1GetLightNum( int MHandle ) ;															// ���C�g�̐����擾����
extern	int				MV1LightSetup( int MHandle ) ;															// �����Ă��郉�C�g�����C�u�����ɔ��f������

// �A�j���[�V�����֌W
extern	int				MV1GetAttachAnimTargetFrameNum( int MHandle, int AttachIndex ) ;						// �A�^�b�`���Ă���A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���̐����擾����
extern	int				MV1GetAttachAnimTargetFrame( int MHandle, int AttachIndex, int Index ) ;				// �A�^�b�`���Ă���A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���̃C���f�b�N�X����������
extern	int				MV1GetAttachAnimTargetFrameToAnimFrameIndex( int MHandle, int AttachIndex, int FrameIndex ) ;	// �w��̃t���[�����A�^�b�`���Ă���A�j���[�V�����̉��Ԗڂ̃^�[�Q�b�g�t���[�������擾����( AnimFrameIndex �Ƃ��Ďg�p���� )

// ���f����{����֌W
extern	VECTOR			MV1GetRotationZAxisZ( int MHandle ) ;													// ���f���̂y���̕����𓾂�
extern	VECTOR			MV1GetRotationZAxisUp( int MHandle ) ;													// ���f���̂y���̕������w�肵���ۂ̏�����x�N�g���𓾂�
extern	float			MV1GetRotationZAxisTwist( int MHandle ) ;												// ���f���̂y���̕������w�肵���ۂ̔P��p�x�𓾂�

// �g���C�A���O�����X�g�֌W
extern	int				MV1GetTriangleListUseBoneFrameNum( int MHandle, int TListIndex ) ;						// �w��̃g���C�A���O�����X�g���g�p���Ă���{�[���t���[���̐����擾����
extern	int				MV1GetTriangleListUseBoneFrame( int MHandle, int TListIndex, int Index ) ;				// �w��̃g���C�A���O�����X�g���g�p���Ă���{�[���t���[���̃t���[���C���f�b�N�X���擾����

// ���ʐ��`��Ԃ��s��
__inline static void _MV1SphereLinear( FLOAT4 *Q1, FLOAT4 *Q2, float t, FLOAT4 *Ret )
{
	float Sin1, Cos1, Sin2, Cos2, Sin3, Cos3 ;
	float s1, s2, qr, ss, ph ;

	qr = Q1->w * Q2->w + Q1->x * Q2->x + Q1->y * Q2->y + Q1->z * Q2->z ;
	ss = 1.0f - ( qr * qr ) ;
	if( ss <= 0.0f || qr >= 1.0f )
	{
		Ret->x = Q1->x ;
		Ret->y = Q1->y ;
		Ret->z = Q1->z ;
		Ret->w = Q1->w ;
	}
	else
	{
		ph = _ACOS( qr ) ;
		if( qr < 0.0f && ph > DX_PI_F / 2.0f )
		{
			qr = - Q1->w * Q2->w - Q1->x * Q2->x - Q1->y * Q2->y - Q1->z * Q2->z ;
			ph = _ACOS( qr ) ;
			_SINCOS( ph,                &Sin1, &Cos1 ) ;
			_SINCOS( ph * ( 1.0f - t ), &Sin2, &Cos2 ) ;
			_SINCOS( ph *          t  , &Sin3, &Cos3 ) ;
			s1 = Sin2 / Sin1 ;
			s2 = Sin3 / Sin1 ;
			Ret->x = Q1->x * s1 - Q2->x * s2 ;
			Ret->y = Q1->y * s1 - Q2->y * s2 ;
			Ret->z = Q1->z * s1 - Q2->z * s2 ;
			Ret->w = Q1->w * s1 - Q2->w * s2 ;
		}
		else
		{
			_SINCOS( ph,               &Sin1, &Cos1 ) ;
			_SINCOS( ph * (1.0f - t ), &Sin2, &Cos2 ) ;
			_SINCOS( ph *         t  , &Sin3, &Cos3 ) ;
			s1 = Sin2 / Sin1 ;
			s2 = Sin3 / Sin1 ;
			Ret->x = Q1->x * s1 + Q2->x * s2 ;
			Ret->y = Q1->y * s1 + Q2->y * s2 ;
			Ret->z = Q1->z * s1 + Q2->z * s2 ;
			Ret->w = Q1->w * s1 + Q2->w * s2 ;
		}
	}
}





#ifdef DX_THREAD_SAFE

// ���f���̓ǂݍ��݁E�ۑ��E�����֌W
extern	int			NS_MV1LoadModel( const TCHAR *FileName ) ;												// ���f���̓ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int			NS_MV1LoadModelFromMem( void *FileImage, int FileSize, int (* FileReadFunc )( const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData ), int (* FileReleaseFunc )( void *MemoryAddr, void *FileReadFuncData ), void *FileReadFuncData = NULL ) ;	// ��������̃��f���t�@�C���C���[�W�ƓƎ��̓ǂݍ��݃��[�`�����g�p���ă��f����ǂݍ���
extern	int			NS_MV1DeleteModel( int MHandle ) ;														// ���f�����폜����
extern	int			NS_MV1InitModel( void ) ;																		// ���ׂẴ��f�����폜����
extern	int			NS_MV1CreateCloneModel( int SrcMHandle ) ;														// �w��̃��f���ƑS�������������ʂ����كf�[�^�n���h�����쐬����( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int			NS_MV1DuplicateModel( int SrcMHandle ) ;												// �w��̃��f���Ɠ������f����{�f�[�^���g�p���ă��f�����쐬����( -1:�G���[  0�ȏ�:���f���n���h�� )
extern	int			NS_MV1SetLoadModelReMakeNormal( int Flag ) ;											// ���f����ǂݍ��ލۂɖ@���̍Čv�Z���s�����ǂ�����ݒ肷��( TRUE:�s��  FALSE:�s��Ȃ� )
extern	int			NS_MV1SetLoadModelReMakeNormalSmoothingAngle( float SmoothingAngle = 89.5f * DX_PI_F / 180.0f ) ;	// ���f����ǂݍ��ލۂɍs���@��̍Čv�Z�Ŏg�p����X���[�W���O�p�x��ݒ肷��( �P�ʂ̓��W�A�� )
extern	int			NS_MV1SetLoadModelPositionOptimize( int Flag ) ;										// ���f����ǂݍ��ލۂɍ��W�f�[�^�̍œK�����s�����ǂ�����ݒ肷��( TRUE:�s��  FALSE:�s��Ȃ� )
extern	int			NS_MV1SetLoadModelUsePhysicsMode( int PhysicsMode /* DX_LOADMODEL_PHYSICS_LOADCALC �� */ ) ;	// �ǂݍ��ރ��f���̕������Z���[�h��ݒ肷��
extern	int			NS_MV1SetLoadModelPhysicsWorldGravity( float Gravity ) ;										// �ǂݍ��ރ��f���̕������Z�ɓK�p����d�̓p�����[�^
extern	int			NS_MV1SetLoadCalcPhysicsWorldGravity( int GravityNo, VECTOR Gravity ) ;						// �ǂݍ��ރ��f���̕������Z���[�h�����O�v�Z( DX_LOADMODEL_PHYSICS_LOADCALC )�������ꍇ�ɓK�p�����d�͂̐ݒ������
extern	int			NS_MV1SetLoadModelAnimFilePath( const TCHAR *FileName ) ;										// �ǂݍ��ރ��f���ɓK�p����A�j���[�V�����t�@�C���̃p�X��ݒ肷��( ���݂� PMD,PMX �݂̂Ɍ��ʂ��� )

// ���f���`��֌W
extern	int			NS_MV1DrawModel( int MHandle ) ;														// ���f����`�悷��
extern	int			NS_MV1DrawFrame( int MHandle, int FrameIndex ) ;										// ���f���̎w��̃t���[����`�悷��
extern	int			NS_MV1DrawMesh( int MHandle, int MeshIndex ) ;											// ���f���̎w��̃��b�V����`�悷��
extern	int			NS_MV1DrawTriangleList( int MHandle, int TriangleListIndex ) ;									// ���f���̎w��̃g���C�A���O�����X�g��`�悷��
extern	int			NS_MV1DrawModelDebug( int MHandle, int Color, int IsNormalLine, float NormalLineLength, int IsPolyLine, int IsCollisionBox ) ;	// ���f���̃f�o�b�O�`��
//extern	int			NS_MV1DrawAlphaObject( void ) ;														// �A���t�@�I�u�W�F�N�g�̕`��

// �`��ݒ�֌W
extern	int			NS_MV1SetUseOrigShader( int UseFlag ) ;														// ���f���̕`��� SetUseVertexShader, SetUsePixelShader �Ŏw�肵���V�F�[�_�[���g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ�( �f�t�H���g ) )

// ���f����{����֌W
//extern	int			   MV1SetupMatrix( int MHandle ) ;														// �`��p�̍s����\�z����
extern	MATRIX		NS_MV1GetLocalWorldMatrix( int MHandle ) ;												// ���f���̃��[�J�����W���烏�[���h���W�ɕϊ�����s��𓾂�
extern	int			NS_MV1SetPosition( int MHandle, VECTOR Position ) ;										// ���f���̍��W���Z�b�g
extern	VECTOR		NS_MV1GetPosition( int MHandle ) ;														// ���f���̍��W���擾
extern	int			NS_MV1SetScale( int MHandle, VECTOR Scale ) ;											// ���f���̊g��l���Z�b�g
extern	VECTOR		NS_MV1GetScale( int MHandle ) ;															// ���f���̊g��l���擾
extern	int			NS_MV1SetRotationXYZ( int MHandle, VECTOR Rotate ) ;									// ���f���̉�]�l���Z�b�g( X����]��Y����]��Z����]���� )
extern	VECTOR		NS_MV1GetRotationXYZ( int MHandle ) ;													// ���f���̉�]�l���擾( X����]��Y����]��Z����]���� )
extern	int			NS_MV1SetRotationZYAxis( int MHandle, VECTOR ZAxisDirection, VECTOR YAxisDirection, float ZAxisTwistRotate ) ;	// ���f���̂y���Ƃx���̌������Z�b�g����
extern	int			NS_MV1SetRotationMatrix( int MHandle, MATRIX Matrix ) ;									// ���f���̉�]�p�s����Z�b�g����
extern	MATRIX		NS_MV1GetRotationMatrix( int MHandle ) ;												// ���f���̉�]�p�s����擾����
extern	int			NS_MV1SetMatrix( int MHandle, MATRIX Matrix ) ;											// ���f���̕ό`�p�s����Z�b�g����
extern	MATRIX		NS_MV1GetMatrix( int MHandle ) ;														// ���f���̕ό`�p�s����擾����
extern	int			NS_MV1SetVisible( int MHandle, int VisibleFlag ) ;										// ���f���̕\���A��\����Ԃ�ύX����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetVisible( int MHandle ) ;														// ���f���̕\���A��\����Ԃ��擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetMeshCategoryVisible( int MHandle, int MeshCategory, int VisibleFlag ) ;		// ���f���̃��b�V���̎��( DX_MV1_MESHCATEGORY_NORMAL �Ȃ� )���̕\���A��\����ݒ肷��( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetMeshCategoryVisible( int MHandle, int MeshCategory, int VisibleFlag ) ;		// ���f���̃��b�V���̎��( DX_MV1_MESHCATEGORY_NORMAL �Ȃ� )���̕\���A��\�����擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetDifColorScale( int MHandle, COLOR_F Scale ) ;									// ���f���̃f�B�t���[�Y�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetDifColorScale( int MHandle ) ;													// ���f���̃f�B�t���[�Y�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetSpcColorScale( int MHandle, COLOR_F Scale ) ;									// ���f���̃X�y�L�����J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetSpcColorScale( int MHandle ) ;													// ���f���̃X�y�L�����J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetEmiColorScale( int MHandle, COLOR_F Scale ) ;									// ���f���̃G�~�b�V�u�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetEmiColorScale( int MHandle ) ;													// ���f���̃G�~�b�V�u�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetAmbColorScale( int MHandle, COLOR_F Scale ) ;									// ���f���̃A���r�G���g�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetAmbColorScale( int MHandle ) ;													// ���f���̃A���r�G���g�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1GetSemiTransState( int MHandle ) ;												// ���f���ɔ������v�f�����邩�ǂ������擾����( �߂�l TRUE:����  FALSE:�Ȃ� )
extern	int			NS_MV1SetOpacityRate( int MHandle, float Rate ) ;										// ���f���̕s�����x��ݒ肷��( �s���� 1.0f �` ���� 0.0f )
extern	float		NS_MV1GetOpacityRate( int MHandle ) ;													// ���f���̕s�����x���擾����( �s���� 1.0f �` ���� 0.0f )
extern	int			NS_MV1SetUseZBuffer( int MHandle, int Flag ) ;											// ���f����`�悷��ۂɂy�o�b�t�@���g�p���邩�ǂ�����ݒ肷��
extern	int			NS_MV1SetWriteZBuffer( int MHandle, int Flag ) ;										// ���f����`�悷��ۂɂy�o�b�t�@�ɏ������݂��s�����ǂ�����ݒ肷��
extern	int			NS_MV1SetZBufferCmpType( int MHandle, int CmpType /* DX_CMP_NEVER �� */ ) ;				// ���f���̕`�掞�̂y�l�̔�r���[�h��ݒ肷��
extern	int			NS_MV1SetZBias( int MHandle, int Bias ) ;												// ���f���̕`�掞�̏������ނy�l�̃o�C�A�X��ݒ肷��
extern	int			NS_MV1SetUseVertDifColor( int MHandle, int UseFlag ) ;									// ���f���̊܂܂�郁�b�V���̒��_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int			NS_MV1SetUseVertSpcColor( int MHandle, int UseFlag ) ;									// ���f���Ɋ܂܂�郁�b�V���̒��_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int			NS_MV1SetSampleFilterMode( int MHandle, int FilterMode ) ;								// ���f���̃T���v���t�B���^�[���[�h��ύX����
extern	int			NS_MV1SetMaxAnisotropy( int MHandle, int MaxAnisotropy ) ;								// ���f���ٕ̈����t�B���^�����O�̍ő原����ݒ肷��
extern	int			NS_MV1SetWireFrameDrawFlag( int MHandle, int Flag ) ;									// ���f�������C���[�t���[���ŕ`�悷�邩�ǂ�����ݒ肷��
extern	int			NS_MV1RefreshVertColorFromMaterial( int MHandle ) ;										// ���f���̒��_�J���[�����ݐݒ肳��Ă���}�e���A���̃J���[�ɂ���
extern	int			NS_MV1PhysicsCalculation( int MHandle, float MillisecondTime ) ;						// ���f���̕������Z���w�莞�ԕ��o�߂����Ɖ��肵�Čv�Z����( MillisecondTime �Ŏw�肷�鎞�Ԃ̒P�ʂ̓~���b )
extern	int			NS_MV1PhysicsResetState( int MHandle ) ;												// ���f���̕������Z�̏�Ԃ����Z�b�g����( �ʒu�����[�v�����Ƃ��p )
extern	int			NS_MV1SetUseShapeFlag( int MHandle, int Flag ) ;										// ���f���̃V�F�C�v�@�\���g�p���邩�ǂ�����ݒ肷��


// �A�j���[�V�����֌W
extern	int			NS_MV1AttachAnim( int MHandle, int AnimIndex, int AnimSrcMHandle = -1, int NameCheck = TRUE ) ;		// �A�j���[�V�������A�^�b�`����( �߂�l  -1:�G���[  0�ȏ�:�A�^�b�`�C���f�b�N�X )
extern	int			NS_MV1DetachAnim( int MHandle, int AttachIndex ) ;										// �A�j���[�V�������f�^�b�`����
//extern	int			NS_MV1PlayAnim( int MHandle, int AttachIndex, int Loop ) ;							// �A�j���[�V�������Đ�����
//extern	int			NS_MV1AnimAddTime( int MHandle, int AttachIndex, float AddTime ) ;					// �A�j���[�V������i�߂�
extern	int			NS_MV1SetAttachAnimTime( int MHandle, int AttachIndex, float Time ) ;					// �A�^�b�`���Ă���A�j���[�V�����̍Đ����Ԃ�ݒ肷��
extern	float		NS_MV1GetAttachAnimTime( int MHandle, int AttachIndex ) ;								// �A�^�b�`���Ă���A�j���[�V�����̍Đ����Ԃ��擾����
extern	float		NS_MV1GetAttachAnimTotalTime( int MHandle, int AttachIndex ) ;							// �A�^�b�`���Ă���A�j���[�V�����̑����Ԃ𓾂�
extern	int			NS_MV1SetAttachAnimBlendRate( int MHandle, int AttachIndex, float Rate = 1.0f ) ;		// �A�^�b�`���Ă���A�j���[�V�����̃u�����h����ݒ肷��
extern	float		NS_MV1GetAttachAnimBlendRate( int MHandle, int AttachIndex ) ;							// �A�^�b�`���Ă���A�j���[�V�����̃u�����h�����擾����
extern	int			NS_MV1SetAttachAnimBlendRateToFrame( int MHandle, int AttachIndex, int FrameIndex, float Rate, int SetChild ) ;	// �A�^�b�`���Ă���A�j���[�V�����̃u�����h����ݒ肷��( �t���[���P�� )
extern	float		NS_MV1GetAttachAnimBlendRateToFrame( int MHandle, int AttachIndex, int FrameIndex ) ;			// �A�^�b�`���Ă���A�j���[�V�����̃u�����h����ݒ肷��( �t���[���P�� )
extern	int			NS_MV1GetAttachAnim( int MHandle, int AttachIndex ) ;									// �A�^�b�`���Ă���A�j���[�V�����̃A�j���[�V�����C���f�b�N�X���擾����
extern	int			NS_MV1SetAttachAnimUseShapeFlag( int MHandle, int AttachIndex, int UseFlag ) ;			// �A�^�b�`���Ă���A�j���[�V�����̃V�F�C�v���g�p���邩�ǂ�����ݒ肷��( UseFlag  TRUE:�g�p����( �f�t�H���g )  FALSE:�g�p���Ȃ� )
extern	int			NS_MV1GetAttachAnimUseShapeFlag( int MHandle, int AttachIndex ) ;						// �A�^�b�`���Ă���A�j���[�V�����̃V�F�C�v���g�p���邩�ǂ������擾����

//extern	int			NS_MV1StopAnim( int MHandle, int AttachIndex ) ;									// �A�j���[�V�������~�߂�
//extern	int			NS_MV1GetAnimState( int MHandle, int AttachIndex ) ;								// �A�j���[�V�������Đ������ǂ������擾����( TRUE:�Đ���  FALSE:��~�� )
extern	int			NS_MV1GetAnimNum( int MHandle ) ;														// �A�j���[�V�����̐����擾����
extern	const TCHAR *NS_MV1GetAnimName( int MHandle, int AnimIndex ) ;										// �w��ԍ��̃A�j���[�V���������擾����( NULL:�G���[ )
extern	int			NS_MV1SetAnimName( int MHandle, int AnimIndex, const TCHAR *AnimName ) ;										// �w��ԍ��̃A�j���[�V��������ύX����
extern	int			NS_MV1GetAnimIndex( int MHandle, const TCHAR *AnimName ) ;								// �w�薼�̃A�j���[�V�����ԍ����擾����( -1:�G���[ )
extern	float		NS_MV1GetAnimTotalTime( int MHandle, int AnimIndex ) ;									// �w��ԍ��̃A�j���[�V�����̑����Ԃ𓾂�
extern	int			NS_MV1GetAnimTargetFrameNum( int MHandle, int AnimIndex ) ;								// �w��̃A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���̐����擾����
extern	const TCHAR *NS_MV1GetAnimTargetFrameName( int MHandle, int AnimIndex, int AnimFrameIndex ) ;		// �w��̃A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���̖��O���擾����
extern	int			NS_MV1GetAnimTargetFrame( int MHandle, int AnimIndex, int AnimFrameIndex ) ;			// �w��̃A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���̔ԍ����擾����
extern	int			NS_MV1GetAnimTargetFrameKeySetNum( int MHandle, int AnimIndex, int AnimFrameIndex ) ;	// �w��̃A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���p�̃A�j���[�V�����L�[�Z�b�g�̐����擾����
extern	int			NS_MV1GetAnimTargetFrameKeySet( int MHandle, int AnimIndex, int AnimFrameIndex, int Index ) ;	// �w��̃A�j���[�V�������^�[�Q�b�g�Ƃ���t���[���p�̃A�j���[�V�����L�[�Z�b�g�L�[�Z�b�g�C���f�b�N�X���擾����

extern	int			NS_MV1GetAnimKeySetNum( int MHandle ) ;													// ���f���Ɋ܂܂��A�j���[�V�����L�[�Z�b�g�̑����𓾂�
extern	int			NS_MV1GetAnimKeySetType( int MHandle, int AnimKeySetIndex ) ;							// �w��̃A�j���[�V�����L�[�Z�b�g�̃^�C�v���擾����( MV1_ANIMKEY_TYPE_QUATERNION �� )
extern	int			NS_MV1GetAnimKeySetDataType( int MHandle, int AnimKeySetIndex ) ;						// �w��̃A�j���[�V�����L�[�Z�b�g�̃f�[�^�^�C�v���擾����( MV1_ANIMKEY_DATATYPE_ROTATE �� )
//extern	float		NS_MV1GetAnimKeySetTotalTime( int MHandle, int AnimKeySetIndex ) ;					// �w��̃A�j���[�V�����L�[�Z�b�g�̑����Ԃ��擾����
extern	int			NS_MV1GetAnimKeySetTimeType( int MHandle, int AnimKeySetIndex ) ;						// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[�̎��ԃf�[�^�^�C�v���擾����( MV1_ANIMKEY_TIME_TYPE_ONE �� )
extern	int			NS_MV1GetAnimKeySetDataNum( int MHandle, int AnimKeySetIndex ) ;						// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[�̐����擾����
extern	float		NS_MV1GetAnimKeyDataTime( int MHandle, int AnimKeySetIndex, int Index ) ;				// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[�̎��Ԃ��擾����
extern	FLOAT4		NS_MV1GetAnimKeyDataToQuaternion( int MHandle, int AnimKeySetIndex, int Index ) ;		// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_QUATERNION �ł͖��������ꍇ�͎��s����
extern	FLOAT4		NS_MV1GetAnimKeyDataToQuaternionFromTime( int MHandle, int AnimKeySetIndex, float Time ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_QUATERNION �ł͖��������ꍇ�͎��s����( ���Ԏw��� )
extern	VECTOR		NS_MV1GetAnimKeyDataToVector( int MHandle, int AnimKeySetIndex, int Index ) ;			// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_VECTOR �ł͖��������ꍇ�͎��s����
extern	VECTOR		NS_MV1GetAnimKeyDataToVectorFromTime( int MHandle, int AnimKeySetIndex, float Time ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_VECTOR �ł͖��������ꍇ�͎��s����( ���Ԏw��� )
extern	MATRIX		NS_MV1GetAnimKeyDataToMatrix( int MHandle, int AnimKeySetIndex, int Index ) ;			// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_MATRIX4X4C �� MV1_ANIMKEY_TYPE_MATRIX3X3 �ł͖��������ꍇ�͎��s����
extern	MATRIX		NS_MV1GetAnimKeyDataToMatrixFromTime( int MHandle, int AnimKeySetIndex, float Time ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_MATRIX4X4C �� MV1_ANIMKEY_TYPE_MATRIX3X3 �ł͖��������ꍇ�͎��s����( ���Ԏw��� )
extern	float		NS_MV1GetAnimKeyDataToFlat( int MHandle, int AnimKeySetIndex, int Index ) ;				// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_FLAT �ł͖��������ꍇ�͎��s����
extern	float		NS_MV1GetAnimKeyDataToFlatFromTime( int MHandle, int AnimKeySetIndex, float Time ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_FLAT �ł͖��������ꍇ�͎��s����( ���Ԏw��� )
extern	float		NS_MV1GetAnimKeyDataToLinear( int MHandle, int AnimKeySetIndex, int Index ) ;			// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_LINEAR �ł͖��������ꍇ�͎��s����
extern	float		NS_MV1GetAnimKeyDataToLinearFromTime( int MHandle, int AnimKeySetIndex, float Time ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_LINEAR �ł͖��������ꍇ�͎��s����( ���Ԏw��� )
//extern	int			NS_MV1GetAnimKeyDataToBlendKeyType( int MHandle, int AnimKeySetIndex, int Index ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[�̃L�[�^�C�v���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_BLEND �ł͖��������ꍇ�͎��s����
//extern	float		NS_MV1GetAnimKeyDataToBlendValue( int MHandle, int AnimKeySetIndex, int Index ) ;	// �w��̃A�j���[�V�����L�[�Z�b�g�̃L�[�̒l���擾����A�L�[�^�C�v�� MV1_ANIMKEY_TYPE_BLEND �ł͖��������ꍇ�͎��s����

// �}�e���A���֌W
extern	int			NS_MV1GetMaterialNum( int MHandle ) ;												// ���f���Ŏg�p���Ă���}�e���A���̐����擾����
extern	const TCHAR *NS_MV1GetMaterialName( int MHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̖��O���擾����
extern	int			NS_MV1SetMaterialType( int MHandle, int MaterialIndex, int Type ) ;					// �w��̃}�e���A���̃^�C�v��ύX����( Type : DX_MATERIAL_TYPE_NORMAL �Ȃ� )
extern	int			NS_MV1GetMaterialType( int MHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃^�C�v���擾����( �߂�l : DX_MATERIAL_TYPE_NORMAL �Ȃ� )
extern	int			NS_MV1SetMaterialDifColor( int MHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃f�B�t���[�Y�J���[��ݒ肷��
extern	COLOR_F		NS_MV1GetMaterialDifColor( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃f�B�t���[�Y�J���[���擾����
extern	int			NS_MV1SetMaterialSpcColor( int MHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃X�y�L�����J���[��ݒ肷��
extern	COLOR_F		NS_MV1GetMaterialSpcColor( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃X�y�L�����J���[���擾����
extern	int			NS_MV1SetMaterialEmiColor( int MHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃G�~�b�V�u�J���[��ݒ肷��
extern	COLOR_F		NS_MV1GetMaterialEmiColor( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃G�~�b�V�u�J���[���擾����
extern	int			NS_MV1SetMaterialAmbColor( int MHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃A���r�G���g�J���[��ݒ肷��
extern	COLOR_F		NS_MV1GetMaterialAmbColor( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃A���r�G���g�J���[���擾����
extern	int			NS_MV1SetMaterialSpcPower( int MHandle, int MaterialIndex, float Power ) ;			// �w��̃}�e���A���̃X�y�L�����̋�����ݒ肷��
extern	float		NS_MV1GetMaterialSpcPower( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃X�y�L�����̋������擾����
extern	int			NS_MV1SetMaterialDifMapTexture( int MHandle, int MaterialIndex, int TexIndex ) ;	// �w��̃}�e���A���Ńf�B�t���[�Y�}�b�v�Ƃ��Ďg�p����e�N�X�`�����w�肷��
extern	int			NS_MV1GetMaterialDifMapTexture( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ńf�B�t���[�Y�}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
extern	int			NS_MV1SetMaterialSpcMapTexture( int MHandle, int MaterialIndex, int TexIndex ) ;	// �w��̃}�e���A���ŃX�y�L�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����w�肷��
extern	int			NS_MV1GetMaterialSpcMapTexture( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���ŃX�y�L�����}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
extern	int			NS_MV1GetMaterialNormalMapTexture( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���Ŗ@���}�b�v�Ƃ��Ďg�p����Ă���e�N�X�`���̃C���f�b�N�X���擾����
//extern	const char *NS_MV1GetMaterialDifMapTexPath( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃f�B�t���[�Y�}�b�v�e�N�X�`���̃p�X���擾����
//extern	const char *NS_MV1GetMaterialSpcMapTexPath( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃X�y�L�����}�b�v�e�N�X�`���̃p�X���擾����
//extern	const char *NS_MV1GetMaterialNormalMapTexPath( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̖@���}�b�v�e�N�X�`���̃p�X���擾����
//extern	const char *NS_MV1GetMaterialBumpMapTexPath( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̓ʉ��}�b�v�e�N�X�`���̃p�X���擾����
//extern	float		NS_MV1GetMaterialBumpMapNextPixelLength( int MHandle, int MaterialIndex ) ;				// �w��̃}�e���A���̓ʉ��}�b�v�e�N�X�`���̂P�s�N�Z���ӂ�̋������擾����
//extern	int			NS_MV1SetMaterialDifMapTexPath( int MHandle, int MaterialIndex, const char *TexPath ) ;		// �w��̃}�e���A���̃f�B�t���[�Y�}�b�v�e�N�X�`���̃p�X��ݒ肷��
//extern	int			NS_MV1SetMaterialSpcMapTexPath( int MHandle, int MaterialIndex, const char *TexPath ) ;	// �w��̃}�e���A���̃X�y�L�����}�b�v�e�N�X�`���̃p�X��ݒ肷��
extern	int			NS_MV1SetMaterialDifGradTexture( int MHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���Ńg�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int			NS_MV1GetMaterialDifGradTexture( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���Ńg�D�[�������_�����O�̃f�B�t���[�Y�O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int			NS_MV1SetMaterialSpcGradTexture( int MHandle, int MaterialIndex, int TexIndex ) ;		// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�y�L�����O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int			NS_MV1GetMaterialSpcGradTexture( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�y�L�����O���f�[�V�����}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int			NS_MV1SetMaterialSphereMapTexture(		int MHandle, int MaterialIndex, int TexIndex ) ;			// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�t�B�A�}�b�v�Ƃ��Ďg�p����e�N�X�`����ݒ肷��
extern	int			NS_MV1GetMaterialSphereMapTexture(		int MHandle, int MaterialIndex ) ;							// �w��̃}�e���A���Ńg�D�[�������_�����O�̃X�t�B�A�}�b�v�Ƃ��Ďg�p����e�N�X�`�����擾����
extern	int			NS_MV1SetMaterialDifGradBlendType( int MHandle, int MaterialIndex, int BlendType ) ;	// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����f�B�t���[�Y�O���f�[�V�����}�b�v�ƃf�B�t���[�Y�J���[�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1GetMaterialDifGradBlendType( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����f�B�t���[�Y�O���f�[�V�����}�b�v�ƃf�B�t���[�Y�J���[�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1SetMaterialSpcGradBlendType( int MHandle, int MaterialIndex, int BlendType ) ;	// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�y�L�����O���f�[�V�����}�b�v�ƃX�y�L�����J���[�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1GetMaterialSpcGradBlendType( int MHandle, int MaterialIndex ) ;					// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�y�L�����O���f�[�V�����}�b�v�ƃX�y�L�����J���[�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1SetMaterialSphereMapBlendType(	int MHandle, int MaterialIndex, int BlendType ) ;			// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�t�B�A�}�b�v�̍������@��ݒ肷��( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1GetMaterialSphereMapBlendType(	int MHandle, int MaterialIndex ) ;							// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����X�t�B�A�}�b�v�̍������@���擾����( DX_MATERIAL_BLENDTYPE_ADDITIVE �Ȃ� )
extern	int			NS_MV1SetMaterialOutLineWidth( int MHandle, int MaterialIndex, float Width ) ;			// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̑�����ݒ肷��
extern	float		NS_MV1GetMaterialOutLineWidth( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̑������擾����
extern	int			NS_MV1SetMaterialOutLineDotWidth( int MHandle, int MaterialIndex, float Width ) ;			// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̃h�b�g�P�ʂ̑�����ݒ肷��
extern	float		NS_MV1GetMaterialOutLineDotWidth( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̃h�b�g�P�ʂ̑������擾����
extern	int			NS_MV1SetMaterialOutLineColor( int MHandle, int MaterialIndex, COLOR_F Color ) ;		// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̐F��ݒ肷��
extern	COLOR_F		NS_MV1GetMaterialOutLineColor( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̃g�D�[�������_�����O�Ŏg�p����֊s���̐F���擾����
extern	int			NS_MV1SetMaterialDrawBlendMode( int MHandle, int MaterialIndex, int BlendMode ) ;		// �w��̃}�e���A���̕`��u�����h���[�h��ݒ肷��( DX_BLENDMODE_ALPHA �� )
extern	int			NS_MV1SetMaterialDrawBlendParam( int MHandle, int MaterialIndex, int BlendParam ) ;		// �w��̃}�e���A���̕`��u�����h�p�����[�^��ݒ肷��
extern	int			NS_MV1GetMaterialDrawBlendMode( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̕`��u�����h���[�h���擾����( DX_BLENDMODE_ALPHA �� )
extern	int			NS_MV1GetMaterialDrawBlendParam( int MHandle, int MaterialIndex ) ;						// �w��̃}�e���A���̕`��u�����h�p�����[�^��ݒ肷��

// �e�N�X�`���֌W
extern	int			NS_MV1GetTextureNum( int MHandle ) ;													// �e�N�X�`���̐����擾
extern	const TCHAR *NS_MV1GetTextureName( int MHandle, int TexIndex ) ;										// �e�N�X�`���̖��O���擾
extern	int			NS_MV1SetTextureColorFilePath( int MHandle, int TexIndex, const TCHAR *FilePath ) ;		// �J���[�e�N�X�`���̃t�@�C���p�X��ύX����
extern	const TCHAR *NS_MV1GetTextureColorFilePath( int MHandle, int TexIndex ) ;							// �J���[�e�N�X�`���̃t�@�C���p�X���擾
extern	int			NS_MV1SetTextureAlphaFilePath( int MHandle, int TexIndex, const TCHAR *FilePath ) ;		// �A���t�@�e�N�X�`���̃t�@�C���p�X��ύX����
extern	const TCHAR *NS_MV1GetTextureAlphaFilePath( int MHandle, int TexIndex ) ;							// �A���t�@�e�N�X�`���̃t�@�C���p�X���擾
extern	int			NS_MV1SetTextureGraphHandle( int MHandle, int TexIndex, int GrHandle, int SemiTransFlag ) ;	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����( GrHandle �� -1 �ɂ���Ɖ��� )
extern	int			NS_MV1GetTextureGraphHandle( int MHandle, int TexIndex ) ;										// �e�N�X�`���̃O���t�B�b�N�n���h�����擾����
extern	int			NS_MV1SetTextureAddressMode( int MHandle, int TexIndex, int AddrUMode, int AddrVMode ) ;	// �e�N�X�`���̃A�h���X���[�h��ݒ肷��( AddrUMode �� DX_TEXADDRESS_WRAP �� )
extern	int			NS_MV1GetTextureAddressModeU( int MHandle, int TexIndex ) ;								// �e�N�X�`���̂t�l�̃A�h���X���[�h���擾����( �߂�l:DX_TEXADDRESS_WRAP �� )
extern	int			NS_MV1GetTextureAddressModeV( int MHandle, int TexIndex ) ;								// �e�N�X�`���̂u�l�̃A�h���X���[�h���擾����( �߂�l:DX_TEXADDRESS_WRAP �� )
extern	int			NS_MV1GetTextureWidth( int MHandle, int TexIndex ) ;									// �e�N�X�`���̕����擾����
extern	int			NS_MV1GetTextureHeight( int MHandle, int TexIndex ) ;									// �e�N�X�`���̍������擾����
extern	int			NS_MV1GetTextureSemiTransState( int MHandle, int TexIndex ) ;							// �e�N�X�`���ɔ������v�f�����邩�ǂ������擾����( �߂�l  TRUE:����  FALSE:�Ȃ� )
extern	int			NS_MV1SetTextureBumpImageFlag( int MHandle, int TexIndex, int Flag ) ;					// �e�N�X�`���Ŏg�p���Ă���摜���o���v�}�b�v���ǂ�����ݒ肷��
extern	int			NS_MV1GetTextureBumpImageFlag( int MHandle, int TexIndex ) ;							// �e�N�X�`�����o���v�}�b�v���ǂ������擾����( �߂�l  TRUE:�o���v�}�b�v  FALSE:�Ⴄ )
extern	int			NS_MV1SetTextureBumpImageNextPixelLength( int MHandle, int TexIndex, float Length ) ;	// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋�����ݒ肷��
extern	float		NS_MV1GetTextureBumpImageNextPixelLength( int MHandle, int TexIndex ) ;					// �o���v�}�b�v�摜�̏ꍇ�ׂ̗̃s�N�Z���Ƃ̋������擾����
extern	int			NS_MV1SetTextureSampleFilterMode( int MHandle, int TexIndex, int FilterMode ) ;			// �e�N�X�`���̃t�B���^�����O���[�h��ݒ肷��
extern	int			NS_MV1GetTextureSampleFilterMode( int MHandle, int TexIndex ) ;							// �e�N�X�`���̃t�B���^�����O���[�h���擾����( �߂�l  DX_DRAWMODE_BILINEAR�� )
extern	int			NS_MV1LoadTexture( const TCHAR *FilePath ) ;													// �R�c���f���ɓ\��t����̂Ɍ������摜�̓ǂݍ��ݕ����ŉ摜��ǂݍ���( �߂�l  -1:�G���[  0�ȏ�:�O���t�B�b�N�n���h�� )


// �t���[���֌W
extern	int			NS_MV1GetFrameNum( int MHandle ) ;														// �t���[���̐����擾����
extern	int			NS_MV1SearchFrame( int MHandle, const TCHAR *FrameName ) ;								// �t���[���̖��O���烂�f�����̃t���[���̃t���[���C���f�b�N�X���擾����( ���������ꍇ�͖߂�l��-1 )
extern	int			NS_MV1SearchFrameChild( int MHandle, int FrameIndex = -1, const TCHAR *ChildName = NULL ) ;	// �t���[���̖��O����w��̃t���[���̎q�t���[���̃t���[���C���f�b�N�X���擾����( ���O�w��� )( FrameIndex �� -1 �ɂ���Ɛe�������Ȃ��t���[���� ChildIndex �Ŏw�肷�� )( ���������ꍇ�͖߂�l��-1 )
extern	const TCHAR *NS_MV1GetFrameName( int MHandle, int FrameIndex ) ;										// �w��̃t���[���̖��O���擾����( �G���[�̏ꍇ�͖߂�l�� NULL )
extern	int			NS_MV1GetFrameParent( int MHandle, int FrameIndex ) ;									// �w��̃t���[���̐e�t���[���̃C���f�b�N�X�𓾂�( �e�����Ȃ��ꍇ�� -2 ���Ԃ� )
extern	int			NS_MV1GetFrameChildNum( int MHandle, int FrameIndex = -1 ) ;							// �w��̃t���[���̎q�t���[���̐����擾����( FrameIndex �� -1 �ɂ���Ɛe�������Ȃ��t���[���̐����Ԃ��Ă��� )
extern	int			NS_MV1GetFrameChild( int MHandle, int FrameIndex = -1, int ChildIndex = 0 ) ;			// �w��̃t���[���̎q�t���[���̃t���[���C���f�b�N�X���擾����( �ԍ��w��� )( FrameIndex �� -1 �ɂ���Ɛe�������Ȃ��t���[���� ChildIndex �Ŏw�肷�� )( �G���[�̏ꍇ�͖߂�l��-1 )
extern	VECTOR		NS_MV1GetFramePosition( int MHandle, int FrameIndex ) ;									// �w��̃t���[���̍��W���擾����
extern	MATRIX		NS_MV1GetFrameBaseLocalMatrix( int MHandle, int FrameIndex ) ;							// �w��̃t���[���̏�����Ԃł̍��W�ϊ��s����擾����
extern	MATRIX		NS_MV1GetFrameLocalMatrix( int MHandle, int FrameIndex ) ;								// �w��̃t���[���̍��W�ϊ��s����擾����
extern	MATRIX		NS_MV1GetFrameLocalWorldMatrix( int MHandle, int FrameIndex ) ;							// �w��̃t���[���̃��[�J�����W���烏�[���h���W�ɕϊ�����s��𓾂�
extern	int			NS_MV1SetFrameUserLocalMatrix( int MHandle, int FrameIndex, MATRIX Matrix ) ;			// �w��̃t���[���̍��W�ϊ��s���ݒ肷��
extern	int			NS_MV1ResetFrameUserLocalMatrix( int MHandle, int FrameIndex ) ;						// �w��̃t���[���̍��W�ϊ��s����f�t�H���g�ɖ߂�
extern	VECTOR		NS_MV1GetFrameMaxVertexLocalPosition( int MHandle, int FrameIndex ) ;					// �w��̃t���[���������b�V�����_�̃��[�J�����W�ł̍ő�l�𓾂�
extern	VECTOR		NS_MV1GetFrameMinVertexLocalPosition( int MHandle, int FrameIndex ) ;					// �w��̃t���[���������b�V�����_�̃��[�J�����W�ł̍ŏ��l�𓾂�
extern	VECTOR		NS_MV1GetFrameAvgVertexLocalPosition( int MHandle, int FrameIndex ) ;					// �w��̃t���[���������b�V�����_�̃��[�J�����W�ł̕��ϒl�𓾂�
extern	int			NS_MV1GetFrameTriangleNum( int MHandle, int FrameIndex ) ;								// �w��̃t���[���Ɋ܂܂��|���S���̐����擾����
extern	int			NS_MV1GetFrameMeshNum( int MHandle, int FrameIndex ) ;									// �w��̃t���[���������b�V���̐����擾����
extern	int			NS_MV1GetFrameMesh( int MHandle, int FrameIndex, int Index ) ;							// �w��̃t���[���������b�V���̃��b�V���C���f�b�N�X���擾����
extern	int			NS_MV1SetFrameVisible( int MHandle, int FrameIndex, int VisibleFlag ) ;					// �w��̃t���[���̕\���A��\����Ԃ�ύX����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetFrameVisible( int MHandle, int FrameIndex ) ;									// �w��̃t���[���̕\���A��\����Ԃ��擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetFrameDifColorScale( int MHandle, int FrameIndex, COLOR_F Scale ) ;			// �w��̃t���[���̃f�B�t���[�Y�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetFrameSpcColorScale( int MHandle, int FrameIndex, COLOR_F Scale ) ;		// �w��̃t���[���̃X�y�L�����J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetFrameEmiColorScale( int MHandle, int FrameIndex, COLOR_F Scale ) ;		// �w��̃t���[���̃G�~�b�V�u�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetFrameAmbColorScale( int MHandle, int FrameIndex, COLOR_F Scale ) ;			// �w��̃t���[���̃A���r�G���g�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetFrameDifColorScale( int MHandle, int FrameIndex ) ;						// �w��̃t���[���̃f�B�t���[�Y�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetFrameSpcColorScale( int MHandle, int FrameIndex ) ;						// �w��̃t���[���̃X�y�L�����J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetFrameEmiColorScale( int MHandle, int FrameIndex ) ;						// �w��̃t���[���̃G�~�b�V�u�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetFrameAmbColorScale( int MHandle, int FrameIndex ) ;						// �w��̃t���[���̃A���r�G���g�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1GetFrameSemiTransState( int MHandle, int FrameIndex ) ;							// �w��̃t���[���ɔ������v�f�����邩�ǂ������擾����( �߂�l TRUE:����  FALSE:�Ȃ� )
extern	int			NS_MV1SetFrameOpacityRate( int MHandle, int FrameIndex, float Rate ) ;					// �w��̃t���[���̕s�����x��ݒ肷��( �s���� 1.0f �` ���� 0.0f )
extern	float		NS_MV1GetFrameOpacityRate( int MHandle, int FrameIndex ) ;								// �w��̃t���[���̕s�����x���擾����( �s���� 1.0f �` ���� 0.0f )
extern	int			NS_MV1SetFrameBaseVisible( int MHandle, int FrameIndex, int VisibleFlag ) ;				// �w��̃t���[���̏����\����Ԃ�ݒ肷��( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetFrameBaseVisible( int MHandle, int FrameIndex ) ;								// �w��̃t���[���̏����\����Ԃ��擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetFrameTextureAddressTransform( int MHandle, int FrameIndex, float TransU, float TransV, float ScaleU, float ScaleV, float RotCenterU, float RotCenterV, float Rotate ) ;	// �w��̃t���[���̃e�N�X�`�����W�ϊ��p�����[�^��ݒ肷��
extern	int			NS_MV1SetFrameTextureAddressTransformMatrix( int MHandle, int FrameIndex, MATRIX Matrix ) ;			// �w��̃t���[���̃e�N�X�`�����W�ϊ��s����Z�b�g����
extern	int			NS_MV1ResetFrameTextureAddressTransform( int MHandle, int FrameIndex ) ;							// �w��̃t���[���̃e�N�X�`�����W�ϊ��p�����[�^�����Z�b�g����

// ���b�V���֌W
extern	int			NS_MV1GetMeshNum( int MHandle ) ;														// ���f���Ɋ܂܂�郁�b�V���̐����擾����
extern	int			NS_MV1GetMeshMaterial( int MHandle, int MeshIndex ) ;									// �w�胁�b�V�����g�p���Ă���}�e���A���̃C���f�b�N�X���擾����
extern	int			NS_MV1GetMeshTriangleNum( int MHandle, int MeshIndex ) ;								// �w�胁�b�V���Ɋ܂܂��O�p�`�|���S���̐����擾����
extern	int			NS_MV1SetMeshVisible( int MHandle, int MeshIndex, int VisibleFlag ) ;					// �w�胁�b�V���̕\���A��\����Ԃ�ύX����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetMeshVisible( int MHandle, int MeshIndex ) ;									// �w�胁�b�V���̕\���A��\����Ԃ��擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetMeshDifColorScale( int MHandle, int MeshIndex, COLOR_F Scale ) ;			// �w��̃��b�V���̃f�B�t���[�Y�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetMeshSpcColorScale( int MHandle, int MeshIndex, COLOR_F Scale ) ;			// �w��̃��b�V���̃X�y�L�����J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetMeshEmiColorScale( int MHandle, int MeshIndex, COLOR_F Scale ) ;			// �w��̃��b�V���̃G�~�b�V�u�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetMeshAmbColorScale( int MHandle, int MeshIndex, COLOR_F Scale ) ;			// �w��̃��b�V���̃A���r�G���g�J���[�̃X�P�[���l��ݒ肷��( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetMeshDifColorScale( int MHandle, int MeshIndex ) ;							// �w��̃��b�V���̃f�B�t���[�Y�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetMeshSpcColorScale( int MHandle, int MeshIndex ) ;							// �w��̃��b�V���̃X�y�L�����J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetMeshEmiColorScale( int MHandle, int MeshIndex ) ;							// �w��̃��b�V���̃G�~�b�V�u�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	COLOR_F		NS_MV1GetMeshAmbColorScale( int MHandle, int MeshIndex ) ;							// �w��̃��b�V���̃A���r�G���g�J���[�̃X�P�[���l���擾����( �f�t�H���g�l�� 1.0f )
extern	int			NS_MV1SetMeshOpacityRate( int MHandle, int MeshIndex, float Rate ) ;					// �w��̃��b�V���̕s�����x��ݒ肷��( �s���� 1.0f �` ���� 0.0f )
extern	float		NS_MV1GetMeshOpacityRate( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���̕s�����x���擾����( �s���� 1.0f �` ���� 0.0f )
extern	int			NS_MV1SetMeshDrawBlendMode( int MHandle, int MeshIndex, int BlendMode ) ;				// �w��̃��b�V���̕`��u�����h���[�h��ݒ肷��( DX_BLENDMODE_ALPHA �� )
extern	int			NS_MV1SetMeshDrawBlendParam( int MHandle, int MeshIndex, int BlendParam ) ;				// �w��̃��b�V���̕`��u�����h�p�����[�^��ݒ肷��
extern	int			NS_MV1GetMeshDrawBlendMode( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���̕`��u�����h���[�h���擾����( DX_BLENDMODE_ALPHA �� )
extern	int			NS_MV1GetMeshDrawBlendParam( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���̕`��u�����h�p�����[�^��ݒ肷��
extern	int			NS_MV1SetMeshBaseVisible( int MHandle, int MeshIndex, int VisibleFlag ) ;				// �w��̃��b�V���̏����\����Ԃ�ݒ肷��( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1GetMeshBaseVisible( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���̏����\����Ԃ��擾����( TRUE:�\��  FALSE:��\�� )
extern	int			NS_MV1SetMeshBackCulling( int MHandle, int MeshIndex, int CullingFlag ) ;				// �w��̃��b�V���̃o�b�N�J�����O���s�����ǂ�����ݒ肷��( DX_CULLING_LEFT �� )
extern	int			NS_MV1GetMeshBackCulling( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���̃o�b�N�J�����O���s�����ǂ������擾����( DX_CULLING_LEFT �� )
extern	VECTOR		NS_MV1GetMeshMaxPosition( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���Ɋ܂܂��|���S���̍ő働�[�J�����W���擾����
extern	VECTOR		NS_MV1GetMeshMinPosition( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���Ɋ܂܂��|���S���̍ŏ����[�J�����W���擾����
extern	int			NS_MV1GetMeshTListNum( int MHandle, int MeshIndex ) ;									// �w��̃��b�V���Ɋ܂܂��g���C�A���O�����X�g�̐����擾����
extern	int			NS_MV1GetMeshTList( int MHandle, int MeshIndex, int Index ) ;							// �w��̃��b�V���Ɋ܂܂��g���C�A���O�����X�g�̃C���f�b�N�X���擾����
extern	int			NS_MV1GetMeshSemiTransState( int MHandle, int MeshIndex ) ;								// �w��̃��b�V���ɔ������v�f�����邩�ǂ������擾����( �߂�l TRUE:����  FALSE:�Ȃ� )
extern	int			NS_MV1SetMeshUseVertDifColor( int MHandle, int MeshIndex, int UseFlag ) ;				// �w��̃��b�V���̒��_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int			NS_MV1SetMeshUseVertSpcColor( int MHandle, int MeshIndex, int UseFlag ) ;			// �w��̃��b�V���̒��_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ�����ݒ肷��( TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int			NS_MV1GetMeshUseVertDifColor( int MHandle, int MeshIndex ) ;						// �w��̃��b�V���̒��_�f�B�t���[�Y�J���[���}�e���A���̃f�B�t���[�Y�J���[�̑���Ɏg�p���邩�ǂ����̐ݒ���擾����( �߂�l  TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )
extern	int			NS_MV1GetMeshUseVertSpcColor( int MHandle, int MeshIndex ) ;						// �w��̃��b�V���̒��_�X�y�L�����J���[���}�e���A���̃X�y�L�����J���[�̑���Ɏg�p���邩�ǂ����̐ݒ���擾����( �߂�l  TRUE:�}�e���A���J���[�̑���Ɏg�p����  FALSE:�}�e���A���J���[���g�p���� )

// �g���C�A���O�����X�g�֌W
extern	int			NS_MV1GetTriangleListNum( int MHandle ) ;												// �g���C�A���O�����X�g�̐����擾����
extern	int			NS_MV1GetTriangleListVertexType( int MHandle, int TListIndex ) ;						// �w��̃g���C�A���O�����X�g�̒��_�f�[�^�^�C�v���擾����( MV1_VERTEX_TYPE_NORMAL �� )
extern	int			NS_MV1GetTriangleListPolygonNum( int MHandle, int TListIndex ) ;						// �w��̃g���C�A���O�����X�g�Ɋ܂܂��|���S���̐����擾����
extern	int			NS_MV1GetTriangleListVertexNum( int MHandle, int TListIndex ) ;							// �w��̃g���C�A���O�����X�g�Ɋ܂܂�钸�_�f�[�^�̐����擾����

// �R���W�����֌W
extern	int			NS_MV1SetupCollInfo( int MHandle, int FrameIndex = -1, int XDivNum = 32, int YDivNum = 8, int ZDivNum = 32 ) ;	// �R���W���������\�z����
extern	int			NS_MV1TerminateCollInfo( int MHandle, int FrameIndex = -1 ) ;							// �R���W�������̌�n��
extern	int			NS_MV1RefreshCollInfo( int MHandle, int FrameIndex = -1 ) ;								// �R���W���������X�V����
extern	MV1_COLL_RESULT_POLY NS_MV1CollCheck_Line( int MHandle, int FrameIndex, VECTOR PosStart, VECTOR PosEnd ) ;	// ���ƃ��f���̓����蔻��
extern	MV1_COLL_RESULT_POLY_DIM NS_MV1CollCheck_LineDim( int MHandle, int FrameIndex, VECTOR PosStart, VECTOR PosEnd ) ; // ���ƃ��f���̓����蔻��( �߂�l�� MV1_COLL_RESULT_POLY_DIM )
extern	MV1_COLL_RESULT_POLY_DIM NS_MV1CollCheck_Sphere( int MHandle, int FrameIndex, VECTOR CenterPos, float r ) ;	// ���ƃ��f���̓����蔻��
extern	MV1_COLL_RESULT_POLY_DIM NS_MV1CollCheck_Capsule( int MHandle, int FrameIndex, VECTOR Pos1, VECTOR Pos2, float r ) ;	// �J�v�Z���ƃ��f���̓����蔻��
extern	MV1_COLL_RESULT_POLY NS_MV1CollCheck_GetResultPoly( MV1_COLL_RESULT_POLY_DIM ResultPolyDim, int PolyNo ) ;	// �R���W�������ʃ|���S���z�񂩂�w��ԍ��̃|���S�������擾����
extern	int			NS_MV1CollResultPolyDimTerminate( MV1_COLL_RESULT_POLY_DIM ResultPolyDim ) ;			// �R���W�������ʃ|���S���z��̌�n��������

// �Q�Ɨp���b�V���֌W
extern	int			NS_MV1SetupReferenceMesh( int MHandle, int FrameIndex, int IsTransform ) ;				// �Q�Ɨp���b�V���̃Z�b�g�A�b�v
extern	int			NS_MV1TerminateReferenceMesh( int MHandle, int FrameIndex, int IsTransform ) ;			// �Q�Ɨp���b�V���̌�n��
extern	int			NS_MV1RefreshReferenceMesh( int MHandle, int FrameIndex, int IsTransform ) ;			// �Q�Ɨp���b�V���̍X�V
extern	MV1_REF_POLYGONLIST	NS_MV1GetReferenceMesh( int MHandle, int FrameIndex, int IsTransform ) ;		// �Q�Ɨp���b�V�����擾����

#else // DX_THREAD_SAFE

// ���f���̓ǂݍ��݁E�ۑ��E�����֌W
#define NS_MV1LoadModel									MV1LoadModel
#define NS_MV1LoadModelFromMem							MV1LoadModelFromMem
#define NS_MV1LoadModelUseReadFunc						MV1LoadModelUseReadFunc
#define NS_MV1DeleteModel								MV1DeleteModel
#define NS_MV1InitModel									MV1InitModel
#define NS_MV1CreateCloneModel							MV1CreateCloneModel
#define NS_MV1DuplicateModel							MV1DuplicateModel
#define NS_MV1SetLoadModelReMakeNormal					MV1SetLoadModelReMakeNormal
#define NS_MV1SetLoadModelReMakeNormalSmoothingAngle	MV1SetLoadModelReMakeNormalSmoothingAngle
#define NS_MV1SetLoadModelPositionOptimize				MV1SetLoadModelPositionOptimize
#define NS_MV1SetLoadModelUsePhysicsMode				MV1SetLoadModelUsePhysicsMode
#define NS_MV1SetLoadModelPhysicsWorldGravity			MV1SetLoadModelPhysicsWorldGravity
#define NS_MV1SetLoadCalcPhysicsWorldGravity			MV1SetLoadCalcPhysicsWorldGravity
#define NS_MV1SetLoadModelAnimFilePath					MV1SetLoadModelAnimFilePath

// ���f���`��֌W
#define NS_MV1DrawModel									MV1DrawModel
#define NS_MV1DrawFrame									MV1DrawFrame
#define NS_MV1DrawMesh									MV1DrawMesh
#define NS_MV1DrawTriangleList							MV1DrawTriangleList
#define NS_MV1DrawModelDebug							MV1DrawModelDebug

// �`��ݒ�֌W
#define NS_MV1SetUseOrigShader							MV1SetUseOrigShader

// ���f����{����֌W
#define NS_MV1GetLocalWorldMatrix						MV1GetLocalWorldMatrix
#define NS_MV1SetPosition								MV1SetPosition
#define NS_MV1GetPosition								MV1GetPosition
#define NS_MV1SetScale									MV1SetScale
#define NS_MV1GetScale									MV1GetScale
#define NS_MV1SetRotationXYZ							MV1SetRotationXYZ
#define NS_MV1GetRotationXYZ							MV1GetRotationXYZ
#define NS_MV1SetRotationZYAxis							MV1SetRotationZYAxis
#define NS_MV1SetRotationMatrix							MV1SetRotationMatrix
#define NS_MV1GetRotationMatrix							MV1GetRotationMatrix
#define NS_MV1SetMatrix									MV1SetMatrix
#define NS_MV1GetMatrix									MV1GetMatrix
#define NS_MV1SetVisible								MV1SetVisible
#define NS_MV1GetVisible								MV1GetVisible
#define NS_MV1SetMeshCategoryVisible					MV1SetMeshCategoryVisible
#define NS_MV1GetMeshCategoryVisible					MV1GetMeshCategoryVisible
#define NS_MV1SetDifColorScale							MV1SetDifColorScale
#define NS_MV1GetDifColorScale							MV1GetDifColorScale
#define NS_MV1SetSpcColorScale							MV1SetSpcColorScale
#define NS_MV1GetSpcColorScale							MV1GetSpcColorScale
#define NS_MV1SetEmiColorScale							MV1SetEmiColorScale
#define NS_MV1GetEmiColorScale							MV1GetEmiColorScale
#define NS_MV1SetAmbColorScale							MV1SetAmbColorScale
#define NS_MV1GetAmbColorScale							MV1GetAmbColorScale
#define NS_MV1GetSemiTransState							MV1GetSemiTransState
#define NS_MV1SetOpacityRate							MV1SetOpacityRate
#define NS_MV1GetOpacityRate							MV1GetOpacityRate
#define NS_MV1SetUseZBuffer								MV1SetUseZBuffer
#define NS_MV1SetWriteZBuffer							MV1SetWriteZBuffer
#define NS_MV1SetZBufferCmpType							MV1SetZBufferCmpType
#define NS_MV1SetZBias									MV1SetZBias
#define NS_MV1SetUseVertDifColor						MV1SetUseVertDifColor
#define NS_MV1SetUseVertSpcColor						MV1SetUseVertSpcColor
#define NS_MV1SetSampleFilterMode						MV1SetSampleFilterMode
#define NS_MV1SetMaxAnisotropy							MV1SetMaxAnisotropy
#define NS_MV1SetWireFrameDrawFlag						MV1SetWireFrameDrawFlag
#define NS_MV1RefreshVertColorFromMaterial				MV1RefreshVertColorFromMaterial
#define NS_MV1PhysicsCalculation						MV1PhysicsCalculation
#define NS_MV1PhysicsResetState							MV1PhysicsResetState
#define NS_MV1SetUseShapeFlag							MV1SetUseShapeFlag



// �A�j���[�V�����֌W
#define NS_MV1AttachAnim								MV1AttachAnim
#define NS_MV1DetachAnim								MV1DetachAnim
#define NS_MV1SetAttachAnimTime							MV1SetAttachAnimTime
#define NS_MV1GetAttachAnimTime							MV1GetAttachAnimTime
#define NS_MV1GetAttachAnimTotalTime					MV1GetAttachAnimTotalTime
#define NS_MV1SetAttachAnimBlendRate					MV1SetAttachAnimBlendRate
#define NS_MV1GetAttachAnimBlendRate					MV1GetAttachAnimBlendRate
#define NS_MV1SetAttachAnimBlendRateToFrame				MV1SetAttachAnimBlendRateToFrame
#define NS_MV1GetAttachAnimBlendRateToFrame				MV1GetAttachAnimBlendRateToFrame
#define NS_MV1GetAttachAnim								MV1GetAttachAnim
#define NS_MV1SetAttachAnimUseShapeFlag					MV1SetAttachAnimUseShapeFlag
#define NS_MV1GetAttachAnimUseShapeFlag					MV1GetAttachAnimUseShapeFlag

#define NS_MV1GetAnimNum								MV1GetAnimNum
#define NS_MV1GetAnimName								MV1GetAnimName
#define NS_MV1SetAnimName								MV1SetAnimName
#define NS_MV1GetAnimIndex								MV1GetAnimIndex
#define NS_MV1GetAnimTotalTime							MV1GetAnimTotalTime
#define NS_MV1GetAnimTargetFrameNum						MV1GetAnimTargetFrameNum
#define NS_MV1GetAnimTargetFrameName					MV1GetAnimTargetFrameName
#define NS_MV1GetAnimTargetFrame						MV1GetAnimTargetFrame
#define NS_MV1GetAnimTargetFrameKeySetNum				MV1GetAnimTargetFrameKeySetNum
#define NS_MV1GetAnimTargetFrameKeySet					MV1GetAnimTargetFrameKeySet

#define NS_MV1GetAnimKeySetNum							MV1GetAnimKeySetNum
#define NS_MV1GetAnimKeySetType							MV1GetAnimKeySetType
#define NS_MV1GetAnimKeySetDataType						MV1GetAnimKeySetDataType
#define NS_MV1GetAnimKeySetTimeType						MV1GetAnimKeySetTimeType
#define NS_MV1GetAnimKeySetDataNum						MV1GetAnimKeySetDataNum
#define NS_MV1GetAnimKeyDataTime						MV1GetAnimKeyDataTime
#define NS_MV1GetAnimKeyDataToQuaternion				MV1GetAnimKeyDataToQuaternion
#define NS_MV1GetAnimKeyDataToQuaternionFromTime		MV1GetAnimKeyDataToQuaternionFromTime
#define NS_MV1GetAnimKeyDataToVector					MV1GetAnimKeyDataToVector
#define NS_MV1GetAnimKeyDataToVectorFromTime			MV1GetAnimKeyDataToVectorFromTime
#define NS_MV1GetAnimKeyDataToMatrix					MV1GetAnimKeyDataToMatrix
#define NS_MV1GetAnimKeyDataToMatrixFromTime			MV1GetAnimKeyDataToMatrixFromTime
#define NS_MV1GetAnimKeyDataToFlat						MV1GetAnimKeyDataToFlat
#define NS_MV1GetAnimKeyDataToFlatFromTime				MV1GetAnimKeyDataToFlatFromTime
#define NS_MV1GetAnimKeyDataToLinear					MV1GetAnimKeyDataToLinear
#define NS_MV1GetAnimKeyDataToLinearFromTime			MV1GetAnimKeyDataToLinearFromTime

// �}�e���A���֌W
#define NS_MV1GetMaterialNum							MV1GetMaterialNum
#define NS_MV1GetMaterialName							MV1GetMaterialName
#define NS_MV1SetMaterialType							MV1SetMaterialType
#define NS_MV1GetMaterialType							MV1GetMaterialType
#define NS_MV1SetMaterialDifColor						MV1SetMaterialDifColor
#define NS_MV1GetMaterialDifColor						MV1GetMaterialDifColor
#define NS_MV1SetMaterialSpcColor						MV1SetMaterialSpcColor
#define NS_MV1GetMaterialSpcColor						MV1GetMaterialSpcColor
#define NS_MV1SetMaterialEmiColor						MV1SetMaterialEmiColor
#define NS_MV1GetMaterialEmiColor						MV1GetMaterialEmiColor
#define NS_MV1SetMaterialAmbColor						MV1SetMaterialAmbColor
#define NS_MV1GetMaterialAmbColor						MV1GetMaterialAmbColor
#define NS_MV1SetMaterialSpcPower						MV1SetMaterialSpcPower
#define NS_MV1GetMaterialSpcPower						MV1GetMaterialSpcPower
#define NS_MV1SetMaterialDifMapTexture					MV1SetMaterialDifMapTexture
#define NS_MV1GetMaterialDifMapTexture					MV1GetMaterialDifMapTexture
#define NS_MV1SetMaterialSpcMapTexture					MV1SetMaterialSpcMapTexture
#define NS_MV1GetMaterialSpcMapTexture					MV1GetMaterialSpcMapTexture
#define NS_MV1GetMaterialNormalMapTexture				MV1GetMaterialNormalMapTexture
#define NS_MV1SetMaterialDifGradTexture					MV1SetMaterialDifGradTexture
#define NS_MV1GetMaterialDifGradTexture					MV1GetMaterialDifGradTexture
#define NS_MV1SetMaterialSpcGradTexture					MV1SetMaterialSpcGradTexture
#define NS_MV1GetMaterialSpcGradTexture					MV1GetMaterialSpcGradTexture
#define NS_MV1SetMaterialSphereMapTexture				MV1SetMaterialSphereMapTexture
#define NS_MV1GetMaterialSphereMapTexture				MV1GetMaterialSphereMapTexture
#define NS_MV1SetMaterialDifGradBlendType				MV1SetMaterialDifGradBlendType
#define NS_MV1GetMaterialDifGradBlendType				MV1GetMaterialDifGradBlendType
#define NS_MV1SetMaterialSpcGradBlendType				MV1SetMaterialSpcGradBlendType
#define NS_MV1GetMaterialSpcGradBlendType				MV1GetMaterialSpcGradBlendType
#define NS_MV1SetMaterialSphereMapBlendType				MV1SetMaterialSphereMapBlendType
#define NS_MV1GetMaterialSphereMapBlendType				MV1GetMaterialSphereMapBlendType
#define NS_MV1SetMaterialOutLineWidth					MV1SetMaterialOutLineWidth
#define NS_MV1GetMaterialOutLineWidth					MV1GetMaterialOutLineWidth
#define NS_MV1SetMaterialOutLineDotWidth				MV1SetMaterialOutLineDotWidth
#define NS_MV1GetMaterialOutLineDotWidth				MV1GetMaterialOutLineDotWidth
#define NS_MV1SetMaterialOutLineColor					MV1SetMaterialOutLineColor
#define NS_MV1GetMaterialOutLineColor					MV1GetMaterialOutLineColor
#define NS_MV1SetMaterialDrawBlendMode					MV1SetMaterialDrawBlendMode
#define NS_MV1SetMaterialDrawBlendParam					MV1SetMaterialDrawBlendParam
#define NS_MV1GetMaterialDrawBlendMode					MV1GetMaterialDrawBlendMode
#define NS_MV1GetMaterialDrawBlendParam					MV1GetMaterialDrawBlendParam

// �e�N�X�`���֌W
#define NS_MV1GetTextureNum								MV1GetTextureNum
#define NS_MV1GetTextureName							MV1GetTextureName
#define NS_MV1SetTextureColorFilePath					MV1SetTextureColorFilePath
#define NS_MV1GetTextureColorFilePath					MV1GetTextureColorFilePath
#define NS_MV1SetTextureAlphaFilePath					MV1SetTextureAlphaFilePath
#define NS_MV1GetTextureAlphaFilePath					MV1GetTextureAlphaFilePath
#define NS_MV1SetTextureGraphHandle						MV1SetTextureGraphHandle
#define NS_MV1GetTextureGraphHandle						MV1GetTextureGraphHandle
#define NS_MV1SetTextureAddressMode						MV1SetTextureAddressMode
#define NS_MV1GetTextureAddressModeU					MV1GetTextureAddressModeU
#define NS_MV1GetTextureAddressModeV					MV1GetTextureAddressModeV
#define NS_MV1GetTextureWidth							MV1GetTextureWidth
#define NS_MV1GetTextureHeight							MV1GetTextureHeight
#define NS_MV1GetTextureSemiTransState					MV1GetTextureSemiTransState
#define NS_MV1SetTextureBumpImageFlag					MV1SetTextureBumpImageFlag
#define NS_MV1GetTextureBumpImageFlag					MV1GetTextureBumpImageFlag
#define NS_MV1SetTextureBumpImageNextPixelLength		MV1SetTextureBumpImageNextPixelLength
#define NS_MV1GetTextureBumpImageNextPixelLength		MV1GetTextureBumpImageNextPixelLength
#define NS_MV1SetTextureSampleFilterMode				MV1SetTextureSampleFilterMode
#define NS_MV1GetTextureSampleFilterMode				MV1GetTextureSampleFilterMode
#define NS_MV1LoadTexture								MV1LoadTexture


// �t���[���֌W
#define NS_MV1GetFrameNum								MV1GetFrameNum
#define NS_MV1SearchFrame								MV1SearchFrame
#define NS_MV1SearchFrameChild							MV1SearchFrameChild
#define NS_MV1GetFrameName								MV1GetFrameName
#define NS_MV1GetFrameParent							MV1GetFrameParent
#define NS_MV1GetFrameChildNum							MV1GetFrameChildNum
#define NS_MV1GetFrameChild								MV1GetFrameChild
#define NS_MV1GetFramePosition							MV1GetFramePosition
#define NS_MV1GetFrameBaseLocalMatrix					MV1GetFrameBaseLocalMatrix
#define NS_MV1GetFrameLocalMatrix						MV1GetFrameLocalMatrix
#define NS_MV1GetFrameLocalWorldMatrix					MV1GetFrameLocalWorldMatrix
#define NS_MV1SetFrameUserLocalMatrix					MV1SetFrameUserLocalMatrix
#define NS_MV1ResetFrameUserLocalMatrix					MV1ResetFrameUserLocalMatrix
#define NS_MV1GetFrameMaxVertexLocalPosition			MV1GetFrameMaxVertexLocalPosition
#define NS_MV1GetFrameMinVertexLocalPosition			MV1GetFrameMinVertexLocalPosition
#define NS_MV1GetFrameAvgVertexLocalPosition			MV1GetFrameAvgVertexLocalPosition
#define NS_MV1GetFrameTriangleNum						MV1GetFrameTriangleNum
#define NS_MV1GetFrameMeshNum							MV1GetFrameMeshNum
#define NS_MV1GetFrameMesh								MV1GetFrameMesh
#define NS_MV1SetFrameVisible							MV1SetFrameVisible
#define NS_MV1GetFrameVisible							MV1GetFrameVisible
#define NS_MV1SetFrameDifColorScale						MV1SetFrameDifColorScale
#define NS_MV1SetFrameSpcColorScale						MV1SetFrameSpcColorScale
#define NS_MV1SetFrameEmiColorScale						MV1SetFrameEmiColorScale
#define NS_MV1SetFrameAmbColorScale						MV1SetFrameAmbColorScale
#define NS_MV1GetFrameDifColorScale						MV1GetFrameDifColorScale
#define NS_MV1GetFrameSpcColorScale						MV1GetFrameSpcColorScale
#define NS_MV1GetFrameEmiColorScale						MV1GetFrameEmiColorScale
#define NS_MV1GetFrameAmbColorScale						MV1GetFrameAmbColorScale
#define NS_MV1GetFrameSemiTransState					MV1GetFrameSemiTransState
#define NS_MV1SetFrameOpacityRate						MV1SetFrameOpacityRate
#define NS_MV1GetFrameOpacityRate						MV1GetFrameOpacityRate
#define NS_MV1SetFrameBaseVisible						MV1SetFrameBaseVisible
#define NS_MV1GetFrameBaseVisible						MV1GetFrameBaseVisible
#define NS_MV1SetFrameTextureAddressTransform			MV1SetFrameTextureAddressTransform
#define NS_MV1SetFrameTextureAddressTransformMatrix		MV1SetFrameTextureAddressTransformMatrix
#define NS_MV1ResetFrameTextureAddressTransform			MV1ResetFrameTextureAddressTransform

// ���b�V���֌W
#define NS_MV1GetMeshNum								MV1GetMeshNum
#define NS_MV1GetMeshMaterial							MV1GetMeshMaterial
#define NS_MV1GetMeshTriangleNum						MV1GetMeshTriangleNum
#define NS_MV1SetMeshVisible							MV1SetMeshVisible
#define NS_MV1GetMeshVisible							MV1GetMeshVisible
#define NS_MV1SetMeshDifColorScale						MV1SetMeshDifColorScale
#define NS_MV1SetMeshSpcColorScale						MV1SetMeshSpcColorScale
#define NS_MV1SetMeshEmiColorScale						MV1SetMeshEmiColorScale
#define NS_MV1SetMeshAmbColorScale						MV1SetMeshAmbColorScale
#define NS_MV1GetMeshDifColorScale						MV1GetMeshDifColorScale
#define NS_MV1GetMeshSpcColorScale						MV1GetMeshSpcColorScale
#define NS_MV1GetMeshEmiColorScale						MV1GetMeshEmiColorScale
#define NS_MV1GetMeshAmbColorScale						MV1GetMeshAmbColorScale
#define NS_MV1SetMeshOpacityRate						MV1SetMeshOpacityRate
#define NS_MV1GetMeshOpacityRate						MV1GetMeshOpacityRate
#define NS_MV1SetMeshDrawBlendMode						MV1SetMeshDrawBlendMode
#define NS_MV1SetMeshDrawBlendParam						MV1SetMeshDrawBlendParam
#define NS_MV1GetMeshDrawBlendMode						MV1GetMeshDrawBlendMode
#define NS_MV1GetMeshDrawBlendParam						MV1GetMeshDrawBlendParam
#define NS_MV1SetMeshBaseVisible						MV1SetMeshBaseVisible
#define NS_MV1GetMeshBaseVisible						MV1GetMeshBaseVisible
#define NS_MV1SetMeshBackCulling						MV1SetMeshBackCulling
#define NS_MV1GetMeshBackCulling						MV1GetMeshBackCulling
#define NS_MV1GetMeshMaxPosition						MV1GetMeshMaxPosition
#define NS_MV1GetMeshMinPosition						MV1GetMeshMinPosition
#define NS_MV1GetMeshTListNum							MV1GetMeshTListNum
#define NS_MV1GetMeshTList								MV1GetMeshTList
#define NS_MV1GetMeshSemiTransState						MV1GetMeshSemiTransState
#define NS_MV1SetMeshUseVertDifColor					MV1SetMeshUseVertDifColor
#define NS_MV1SetMeshUseVertSpcColor					MV1SetMeshUseVertSpcColor
#define NS_MV1GetMeshUseVertDifColor					MV1GetMeshUseVertDifColor
#define NS_MV1GetMeshUseVertSpcColor					MV1GetMeshUseVertSpcColor

// �g���C�A���O�����X�g�֌W
#define NS_MV1GetTriangleListNum						MV1GetTriangleListNum
#define NS_MV1GetTriangleListVertexType					MV1GetTriangleListVertexType
#define NS_MV1GetTriangleListPolygonNum					MV1GetTriangleListPolygonNum
#define NS_MV1GetTriangleListVertexNum					MV1GetTriangleListVertexNum

// �R���W�����֌W
#define NS_MV1SetupCollInfo								MV1SetupCollInfo
#define NS_MV1TerminateCollInfo							MV1TerminateCollInfo
#define NS_MV1RefreshCollInfo							MV1RefreshCollInfo
#define NS_MV1CollCheck_Line							MV1CollCheck_Line
#define NS_MV1CollCheck_LineDim							MV1CollCheck_LineDim
#define NS_MV1CollCheck_Sphere							MV1CollCheck_Sphere
#define NS_MV1CollCheck_Capsule							MV1CollCheck_Capsule
#define NS_MV1CollCheck_GetResultPoly					MV1CollCheck_GetResultPoly
#define NS_MV1CollResultPolyDimTerminate				MV1CollResultPolyDimTerminate

// �Q�Ɨp���b�V���֌W
#define NS_MV1SetupReferenceMesh						MV1SetupReferenceMesh
#define NS_MV1TerminateReferenceMesh					MV1TerminateReferenceMesh
#define NS_MV1RefreshReferenceMesh						MV1RefreshReferenceMesh
#define NS_MV1GetReferenceMesh							MV1GetReferenceMesh

#endif  // DX_THREAD_SAFE

}

#endif	// DX_NON_MODEL

#endif
