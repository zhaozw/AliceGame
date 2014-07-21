// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		���ʕ`��v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#ifndef __DXGRAPHICSBASE_H__
#define __DXGRAPHICSBASE_H__


// �C���N���[�h ------------------------------------------------------------------
#include "DxCompileConfig.h"
#include "DxLib.h"
#include "DxStatic.h"
#include "DxBaseImage.h"

namespace DxLib
{

// �}�N����` --------------------------------------------------------------------

#define GBASE						GraphicsBaseData
#define MASKD						MaskManageData

// �L�^���Ă����L���ɂȂ��Ă��郉�C�g�̃C���f�b�N�X�̐�
#define MAX_D3DENABLELIGHTINDEX_NUM			(256)

// �����ɕ`��ł��郌���_�����O�^�[�Q�b�g�̍ő吔
#define DX_RENDERTARGET_COUNT				(16)

// �g�p����e�N�X�`���X�e�[�W�̍ő吔
#define USE_TEXTURESTAGE_NUM				(8)

// �\���̒�` --------------------------------------------------------------------

// ���������_�^�� RECT �\����
struct RECTF
{
	float left, top ;
	float right, bottom ;
} ;

// �O���t�B�b�N�n���h���̃Z�b�g�A�b�v�ɕK�v�ȃO���[�o���f�[�^��Z�߂��\����
struct SETUP_GRAPHHANDLE_GPARAM
{
	DWORD					TransColor ;							// ���ߐF

	int						CreateImageColorBitDepth ;				// �쐬����摜�̐F�[�x
	int						CreateImageChannelBitDepth ;			// �쐬����摜�̂P�`�����l���ӂ�̃r�b�g�[�x( �����炪�ݒ肳��Ă���ꍇ�� CreateImageColorBitDepth ���D�悳��� )
	int						AlphaTestImageCreateFlag ;				// ���e�X�g�t���摜�쐬�w��t���O( AlphaGraphCreateFlag �̕����D��x������ )( �e�N�X�`���T�[�t�F�X�̂� )
	int						AlphaChannelImageCreateFlag ;			// ���`�����l���t���摜�쐬�w��t���O( DrawValidGraphCreateFlag �̕����D��x������ )
	int						BlendImageCreateFlag ;					// �u�����h�����p�摜�쐬�w��t���O
	int						UseManagedTextureFlag ;					// �}�l�[�W�h�e�N�X�`�����g�p���邩�A�t���O( 1:�g�p����  0:�g�p���Ȃ� )

	int						DrawValidImageCreateFlag ;				// �`��\�摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidAlphaImageCreateFlag ;			// �`��\�ȃ��`�����l���t���摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidFloatTypeGraphCreateFlag ;		// �`��\��Float�^�摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidGraphCreateZBufferFlag ;		// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@���쐬���邩�ǂ���
	int						CreateDrawValidGraphChannelNum ;		// �`��\�摜�̃`�����l����( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidMSSamples ;					// �`��\�ȉ摜�̃}���`�T���v�����O��
	int						DrawValidMSQuality ;					// �`��\�ȉ摜�̃}���`�T���v�����O�N�I���e�B

	int						MipMapCount ;							// �����ō쐬����~�b�v�}�b�v�̐�( -1:�ő僌�x���܂ō쐬���� )
	int						UserMaxTextureSize ;					// ���[�U�[�w��̃e�N�X�`���ő�T�C�Y
	int						NotUseDivFlag ;							// �摜�������s��Ȃ����ǂ���( TRUE:�s��Ȃ�  FALSE:�s�� )
} ;

// �摜�f�[�^����O���t�B�b�N�n���h���̍쐬�E�摜�f�[�^�̓]���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM
{
	SETUP_GRAPHHANDLE_GPARAM InitHandleGParam ;						// �O���t�B�b�N�n���h���̃Z�b�g�A�b�v�ɕK�v�ȃO���[�o���f�[�^

	int						NotUseTransColor;						// ���ߐF���g�p���Ȃ����ǂ����t���O(TRUE:�g�p���Ȃ�  FALSE:�g�p����)
	int						UseTransColorGraphCreateFlag ;			// ���ߐF�Ƃ����łȂ������̋��E���������炩�ɂ��邩�A�t���O
	int						LeftUpColorIsTransColorFlag ;			// �摜����̃s�N�Z���F�𓧉ߐF�ɂ��邩�ǂ����̃t���O
} ;

#ifndef DX_NON_MOVIE

// ���[�r�[�t�@�C���̃I�[�v���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct OPENMOVIE_GPARAM
{
	int						RightAlphaFlag;							// ���摜�̉E�����A���t�@�Ƃ݂Ȃ�����n���h�����쐬���邩(TRUE:�쐬����)
} ;

#endif // DX_NON_MOVIE

// �摜�̌��f�[�^�̏��ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct SETGRAPHBASEINFO_GPARAM
{
	int						NotGraphBaseDataBackupFlag ;			// �O���t�B�b�N�n���h�����쐬�����ۂɎg�p�����摜�f�[�^���o�b�N�A�b�v���Ȃ����ǂ����̃t���O( TRUE:�o�b�N�A�b�v���Ȃ�  FALSE:�o�b�N�A�b�v���� )
} ;

// �t�@�C������O���t�B�b�N�n���h�����쐬���鏈���ɕK�v�ȃO���[�o���f�[�^��Z�߂�����
struct LOADGRAPH_GPARAM
{
	LOADBASEIMAGE_GPARAM	LoadBaseImageGParam ;					// �摜�f�[�^�̓ǂݍ��݂ɕK�v�ȃO���[�o���f�[�^
#ifndef DX_NON_MOVIE
	OPENMOVIE_GPARAM		OpenMovieGParam ;						// ���[�r�[�t�@�C���̃I�[�v���ɕK�v�ȃO���[�o���f�[�^
#endif
	CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM CreateGraphGParam ;	// �O���t�B�b�N�n���h���̍쐬�E�������ɕK�v�ȃO���[�o���f�[�^
	SETGRAPHBASEINFO_GPARAM	SetGraphBaseInfoGParam ;				// �摜�̌��f�[�^�̏��̕ۑ��ɕK�v�ȃO���[�o���f�[�^
} ;

// �O���t�B�b�N�f�[�^�ǂݍ��݈�����Z�߂�����
struct LOADGRAPH_PARAM
{
	LOADGRAPH_GPARAM		GParam ;
	int						ReCreateFlag ;
	int						GrHandle ;
	int						BaseHandle ;

	const TCHAR *			FileName ;
	void *					RgbMemImage ;
	int						RgbMemImageSize ;
	void *					AlphaMemImage ;
	int						AlphaMemImageSize ;
	BITMAPINFO *			RgbBmpInfo ;
	void *					RgbBmpImage ;
	BITMAPINFO *			AlphaBmpInfo ;
	void *					AlphaBmpImage ;
	BASEIMAGE *				RgbBaseImage ;
	BASEIMAGE *				AlphaBaseImage ;

	int						AllNum ;
	int						XNum ;
	int						YNum ;
	int						SizeX ;
	int						SizeY ;
	int *					HandleBuf ;
	int						TextureFlag ;
	int						ReverseFlag ;
	int						SurfaceMode ;
} ;

// ���C�g�n���h���\����
struct LIGHT_HANDLE
{
	unsigned int			ID ;							// �G���[�`�F�b�N�p�̂h�c
	int						Handle ;						// ���g�̃n���h���l

	LIGHTPARAM				Param ;							// ���C�g�̃p�����[�^
	int						SetD3DIndex ;					// Direct3D ��̃Z�b�g����Ă���C���f�b�N�X( -1:�Z�b�g����Ă��Ȃ� )
	int						EnableFlag ;					// �L���t���O
	int						ChangeFlag ;					// Direct3D �ɔ��f���Ă��Ȃ��ݒ肪���邩�ǂ����̃t���O( TRUE:����  FALSE:�Ȃ� )
} ;

// ���C�g�֌W���̍\����
struct LIGHTBASEDATA
{
	int						ProcessDisable ;						// ���C�g�����𖳌��ɂ��邩�ǂ���
	int						ChangeMaterial ;						// ���C�g�v�Z�p�}�e���A�����ύX�������ǂ����̃t���O
	MATERIALPARAM			Material ;								// ���C�g�v�Z�p�}�e���A��
	int						MaterialNotUseVertexDiffuseColor ;		// ���C�g�v�Z�ɒ��_�̃f�B�t���[�Y�J���[���g�p���Ȃ����ǂ���
	int						MaterialNotUseVertexSpecularColor;		// ���C�g�v�Z�ɒ��_�̃X�y�L�����J���[���g�p���Ȃ����ǂ���
	LIGHT_HANDLE			*Data[ MAX_LIGHT_NUM ] ;				// ���C�g���ւ̃|�C���^
	int						Num ;									// ���C�g�W�̐�
	int						Area ;									// �L���ȃ��C�g������͈�
	int						HandleID ;								// ���C�g�Ɋ��蓖�Ă�h�c
	int						EnableNum ;								// �L���ɂȂ��Ă��郉�C�g�̐�
	int						MaxD3DEnableIndex ;						// Direct3DDevice �ɑ΂��ėL���ɂȂ��Ă��郉�C�g�ň�ԑ傫�Ȓl�̃C���f�b�N�X
	int						EnableD3DIndex[ MAX_D3DENABLELIGHTINDEX_NUM ] ;	// Direct3DDevice �ɑ΂��ėL���ɂ��Ă��郉�C�g�̃��X�g
	int						D3DChange ;								// Direct3DDevice ���ւ̔��f���K�v�ȕύX�����������ǂ����̃t���O
	int						D3DRefresh ;							// Direct3DDevice ���ւ̑S���ڂ̔��f���K�v���ǂ����̃t���O
	int						DefaultHandle ;							// �f�t�H���g���C�g�p�n���h��
} ;

// �O���t�B�b�N�`���{�f�[�^�^
struct GRAPHICSBASEDATA
{
	void					( *GraphRestoreShred )( void ) ;		// �O���t�B�b�N�����֐��̃|�C���^ 

	int						TargetScreen[ DX_RENDERTARGET_COUNT ] ;	// �`���O���t�B�b�N���ʒl
	int						TargetScreenVramFlag ;					// �`���O���t�B�b�N���u�q�`�l�ɑ��݂��邩�ۂ�
	int						TargetZBuffer ;							// �`���y�o�b�t�@���ʒl
	RECT					WindowDrawRect ;						// �f�X�N�g�b�v�̂���T�[�t�F�X�ɕ`�揈�����s��
																	// �ꍇ�E�C���h�E�̃N���C�A���g�̈�̋�`�f�[�^�������Ă���
	RECT					DrawArea ;								// �`��\��`
	RECTF					DrawAreaF ;								// �`��\��`���������_�^
	int						DrawSizeX, DrawSizeY ;					// �`��Ώۂ̃T�C�Y
	float					Draw3DScale ;							// �R�c�`�揈���̃X�P�[��

	int						ProjectionMatrixMode ;					// �ˉe�s�񃂁[�h( 0:���ߖ@  1:���ˉe  2:�s��w�� )
	float					ProjNear, ProjFar ;						// �y�N���b�s���O�� Near�ʂ� Far��
	float					ProjDotAspect ;							// �h�b�g�A�X�y�N�g��( �c / �� )
	float					ProjFov ;								// ���ߖ@���̎���p
	float					ProjSize ;								// ���ˉe���̃T�C�Y
	MATRIX					ProjMatrix ;							// �ˉe�s��

	int						EnableZBufferFlag2D ;					// �y�o�b�t�@�̗L���t���O
	int						WriteZBufferFlag2D ;					// �y�o�b�t�@�̍X�V���s�����A�t���O
	int						ZBufferCmpType2D ;						// �y�l�̔�r���[�h
	int						ZBias2D ;								// �y�o�C�A�X
	int						EnableZBufferFlag3D ;					// �y�o�b�t�@�̗L���t���O
	int						WriteZBufferFlag3D ;					// �y�o�b�t�@�̍X�V���s�����A�t���O
	int						ZBufferCmpType3D ;						// �y�l�̔�r���[�h
	int						ZBias3D ;								// �y�o�C�A�X
	int						FillMode ;								// �t�B�����[�h
	int						CullMode ;								// �J�����O���[�h
	int						TexAddressModeU[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�t
	int						TexAddressModeV[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�u
	int						TexAddressModeW[ USE_TEXTURESTAGE_NUM ] ;	// �e�N�X�`���A�h���X���[�h�v
	int						FogEnable ;								// �t�H�O���L�����ǂ���( TRUE:�L��  FALSE:���� )
	int						FogMode ;								// �t�H�O���[�h
	DWORD					FogColor ;								// �t�H�O�J���[
	float					FogStart, FogEnd ;						// �t�H�O�J�n�A�h���X�ƏI���A�h���X
	float					FogDensity ;							// �t�H�O���x
	float					DrawZ;									// �Q�c�`�掞�ɂy�o�b�t�@�ɏ������ނy�l
	int						DrawMode ;								// �`�惂�[�h
	int						MaxAnisotropy ;							// �ő�ٕ���
	int						BlendMode ;								// �u�����h���[�h
	int						BlendParam ;							// �u�����h�p�����[�^
	int						BlendGraph ;							// �u�����h�O���t�B�b�N�n���h��
	int						BlendGraphType ;						// �u�����h�O���t�B�b�N�^�C�v
	int						BlendGraphFadeRatio ;					// �u�����h�O���t�B�b�N�̃t�F�[�h�p�����[�^
	int						BlendGraphBorderParam ;					// �u�����h�O���t�B�b�N�n���h���̃u�����h���E�l(0�`255)
	int						BlendGraphBorderRange ;					// �u�����h�O���t�B�b�N�n���h���̋��E�����̕�(0�`255)
	int						BlendGraphX, BlendGraphY ;				// �u�����h�O���t�B�b�N�̋N�_���W
	int						AlphaTestMode ;							// �A���t�@�e�X�g���[�h
	int						AlphaTestParam ;						// �A���t�@�e�X�g�p�����[�^
	int						NotUseSpecular ;						// �X�y�L�������g�p���Ȃ����ǂ���

	union
	{
		RGBCOLOR			DrawBright ;							// �`��P�x
		DWORD				bDrawBright ;
	} ;
	int						IgnoreGraphColorFlag ;					// �`�悷��摜�̐F�����𖳎����邩�ǂ����̃t���O

	int						NotGraphBaseDataBackupFlag ;			// �O���t�B�b�N�n���h�����쐬�����ۂɎg�p�����摜�f�[�^���o�b�N�A�b�v���Ȃ����ǂ����̃t���O( TRUE:�o�b�N�A�b�v���Ȃ�  FALSE:�o�b�N�A�b�v���� )
	int						CreateImageColorBitDepth ;				// �쐬����摜�̐F�[�x
	int						CreateImageChannelBitDepth ;			// �쐬����摜�̂P�`�����l���ӂ�̃r�b�g�[�x( �����炪�ݒ肳��Ă���ꍇ�� CreateImageColorBitDepth ���D�悳��� )
	int						TextureImageCreateFlag ;				// �e�N�X�`���摜�쐬�t���O
	int						DrawValidImageCreateFlag ;				// �`��\�摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidAlphaImageCreateFlag ;			// �`��\�ȃ��`�����l���t���摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidFloatTypeGraphCreateFlag ;		// �`��\��Float�^�摜�쐬�w��t���O( �e�N�X�`���T�[�t�F�X�̂� )
	int						NotDrawValidGraphCreateZBufferFlag ;	// �`��\�摜���쐬����ۂɐ�p�̂y�o�b�t�@�͍쐬���Ȃ����ǂ���
	int						CreateDrawValidGraphChannelNum ;		// �`��\�摜�̃`�����l����( �e�N�X�`���T�[�t�F�X�̂� )
	int						DrawValidMSSamples ;					// �`��\�ȉ摜�̃}���`�T���v�����O��
	int						DrawValidMSQuality ;					// �`��\�ȉ摜�̃}���`�T���v�����O�N�I���e�B
	int						UseNoBlendModeParam ;					// DX_BLENDMODE_NOBLEND ���ł� Param �̒l���g�p���邩�ǂ����̃t���O( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
	int						AlphaChannelImageCreateFlag ;			// ���`�����l���t���摜�쐬�w��t���O( DrawValidGraphCreateFlag �̕����D��x������ )
	int						AlphaTestImageCreateFlag ;				// ���e�X�g�t���摜�쐬�w��t���O( AlphaGraphCreateFlag �̕����D��x������ )( �e�N�X�`���T�[�t�F�X�̂� )
	int						SystemMemImageCreateFlag ;				// �V�X�e�����������g�p����摜�쐬�w��t���O( �W���T�[�t�F�X�̂� )
	int						BlendImageCreateFlag ;					// �u�����h�����p�摜�쐬�w��t���O
	int						NotUseManagedTextureFlag ;				// �}�l�[�W�h�e�N�X�`�����g�p���Ȃ����A�t���O( 1:�g�p���Ȃ�  0:�g�p���� )
	int						LeftUpColorIsTransColorFlag ;			// �摜����̃s�N�Z���F�𓧉ߐF�ɂ��邩�ǂ����̃t���O
	int						NotUseBasicGraphDraw3DDeviceMethodFlag ;// �P���}�`�̕`��ɂR�c�f�o�C�X�̋@�\���g�p���Ȃ����ǂ����̃t���O
	int						NotWaitVSyncFlag ;						// �u�r�x�m�b�҂������Ȃ����ǂ����̃t���O�iTRUE�F���Ȃ� FALSE�F����j
	int						PreSetWaitVSyncFlag ;					// DxLib_Init ���Ă΂��O�� SetWaitVSyncFlag( TRUE ) ; �����s���ꂽ���ǂ����̃t���O( TRUE:���s���ꂽ  FALSE:���s����Ă��Ȃ� )
	int						Emulation320x240Flag ;					// 640x480 �̉�ʂ� 320x240 �̉�ʂ��o�͂��邩�ǂ����̃t���O

	DWORD					TransColor ;							// ���ߐF
	int						NotUseTransColor;						// ���ߐF���g�p���Ȃ����ǂ����t���O(TRUE:�g�p���Ȃ�  FALSE:�g�p����)
	int						UseTransColorGraphCreateFlag ;			// ���ߐF�Ƃ����łȂ������̋��E���������炩�ɂ��邩�A�t���O

	int						NotDrawFlag ;							// �`��s�\�t���O
	int						NotDrawFlagInSetDrawArea ;				// �`��s�\�t���O�iSetDrawArea�p�j

	int						ScreenFlipFlag ;						// ScreenFlip�֐����Ăт������t���O

	int						Screen3DWidth, Screen3DHeight ;			// �R�c�`����s���ۂ̑z�肷��X�N���[���̃T�C�Y
	int						Screen3DCenterX, Screen3DCenterY ;		// �R�c�`����s���ۂ̑z�肷��X�N���[���̒��S���W
	LONGLONG				FrameCounter ;							// �t���[���J�E���^�[

	int						MatchHardwareMatrix ;					// �R�c�f�o�C�X�ɐݒ肳��Ă���s��Ɩ{�\���̒��̍s�񂪈�v���Ă��邩�ǂ���( TRUE:��v���Ă���  FALSE:��v���Ă��Ȃ� )
	int						MatchHardwareWorldMatrix ;				// �R�c�f�o�C�X�ɐݒ肳��Ă��郏�[���h�ϊ��s��Ɩ{�\���̒��̃��[���h�ϊ��s�񂪈�v���Ă��邩�ǂ���( TRUE:��v���Ă���  FALSE:��v���Ă��Ȃ� )
	MATRIX					WorldMatrix ;							// ���[���h�ϊ��s��
	int						MatchHardwareViewMatrix ;				// �R�c�f�o�C�X�ɐݒ肳��Ă���r���[�ϊ��s��Ɩ{�\���̒��̃r���[�ϊ��s�񂪈�v���Ă��邩�ǂ���( TRUE:��v���Ă���  FALSE:��v���Ă��Ȃ� )
	MATRIX					ViewMatrix ;							// �r���[�ϊ��s��
	int						MatchHardwareProjectionMatrix ;			// �R�c�f�o�C�X�ɐݒ肳��Ă���ˉe�ϊ��s��Ɩ{�\���̒��̎ˉe�ϊ��s�񂪈�v���Ă��邩�ǂ���( TRUE:��v���Ă���  FALSE:��v���Ă��Ȃ� )
	MATRIX					ProjectionMatrix ;						// �ˉe�ϊ��s��
	MATRIX					ViewportMatrix ;						// �r���[�|�[�g�s��
	MATRIX					Direct3DViewportMatrix ;				// �c�����������R�c �I�ȃr���[�|�[�g�s��
	MATRIX					Direct3DViewportMatrixAnti ;			// �c�����������R�c �I�ȃr���[�|�[�g�s��𖳌��ɂ���s��
	int						TextureTransformUse ;					// �e�N�X�`�����W�ϊ��������s�����ǂ���( TRUE:�s��  FALSE:�s��Ȃ� )
	float					TextureTransX, TextureTransY ;			// �e�N�X�`�����s�ړ�
	float					TextureScaleX, TextureScaleY ;			// �e�N�X�`���g�嗦
	float					TextureRotateCenterX, TextureRotateCenterY ;	// �e�N�X�`����]�̒��S���W
	float					TextureRotate ;							// �e�N�X�`����]�l
	int						TextureMatrixValid ;					// TextureMatrix ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	MATRIX					TextureMatrix ;							// TextureTransX �� TextureScaleY �Ȃǂ��g�p���Ȃ��Őݒ肷��s��
	MATRIX					TextureTransformMatrix ;				// �e�N�X�`�����W�ϊ��s��
	int						TempVertexBufferSize ;					// �ꎞ�I�ɒ��_�f�[�^���i�[���邽�߂̃o�b�t�@�̃T�C�Y
	void					*TempVertexBuffer ;						// �ꎞ�I�ɒ��_�f�[�^���i�[���邽�߂̃o�b�t�@

	int						ValidBlendMatrix ;						// BlendMatrix, ViewProjectionMatrix, BillboardMatrix ���L�����ǂ���( TRUE:�L��  FALSE:���� )
	MATRIX					BlendMatrix ;							// ���[���h�ϊ��A�r���[�ϊ��A�ˉe�ϊ��A�r���[�|�[�g�ϊ��s����|�����킹������
	int						ValidInverseBlendMatrix ;				// BlendMatrix �̋t�s�񂪗L�����ǂ���( TRUE:�L��  FALSE:���� )
	MATRIX					InverseBlendMatrix ;					// BlendMatrix �̋t�s��
	MATRIX					ViewProjectionViewportMatrix ;			// �r���[�s��Ǝˉe�s��ƃr���[�|�[�g�s����|�����킹������
	MATRIX					BillboardMatrix ;						// �r���{�[�h�p�̍s��
	FLOAT4					ClippingPlane[ 6 ] ;					// �N���b�s���O����( 0:-x 1:+x 2:-y 3:+y 4:-z 5:+z )
	MATRIX					ConvScreenPosToWorldPosMatrix ;			// ��ʍ��W����X�N���[�����W�ɕϊ�����ۂɎg�p����s��
	int						ValidConvScreenPosToWorldPosMatrix ;	// ��ʍ��W����X�N���[�����W�ɕϊ�����ۂɎg�p����s�񂪗L�����ǂ���( TRUE:�L��  FALSE:���� )

	LIGHTBASEDATA			Light ;									// ���C�g�֌W�̏��

	VECTOR					CameraPosition ;						// �J�����̈ʒu
	VECTOR					CameraTarget ;							// �J�����̒����_
	VECTOR					CameraUp ;								// �J�����̃A�b�v�x�N�g��
	float					CameraHRotate ;							// �J�����̐����p�x
	float					CameraVRotate ;							// �J�����̐����p�x
	float					CameraTRotate ;							// �J�����̔P��p�x
	MATRIX					CameraMatrix ;							// �r���[�s��
	float					CameraScreenCenterX, CameraScreenCenterY ;	// �J�����̏����_
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �`�����̊�{�I�ȏ��
extern GRAPHICSBASEDATA GraphicsBaseData ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int		InitializeGraphicsBase( void ) ;											// �O���t�B�b�N�`���{�f�[�^�̏�����
extern	int		CheckCameraViewClip_Box_PosDim( VECTOR *CheckBoxPos ) ;						// �W���W�Ō`���{�b�N�X���J�����̎��E�ɓ����Ă��邩�ǂ����𔻒肷��( �߂�l TRUE:���E�ɓ����Ă��Ȃ�  FALSE:���E�ɓ����Ă��� )( CheckPos�� VECTOR 8���̔z��̐擪�A�h���X�A�z��̊e�v�f�ԍ��̓��e 0:+x +y +z   1:-x +y +z   2:-x -y +z   3:+x -y +z   4:+x -y -z   5:+x +y -z   6:-x +y -z   7:-x -y -z )


extern	int		MakeGraph_UseGParam( SETUP_GRAPHHANDLE_GPARAM *GParam, int SizeX, int SizeY, int NotUse3DFlag, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;																																				// ��̃O���t�B�b�N�n���h�����쐬����֐�
extern	int		CreateGraph_UseGParam(                  LOADGRAPH_PARAM *Param, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;																																															// �摜�f�[�^����O���t�B�b�N�n���h�����쐬����֐�
extern	int		CreateDivGraph_UseGParam(               LOADGRAPH_PARAM *Param, int ASyncLoadFlag = FALSE ) ;																																																						// �摜�f�[�^�𕪊����ăO���t�B�b�N�n���h�����쐬����֐�
extern	int		LoadBmpToGraph_UseGParam(               LOADGRAPH_GPARAM *GParam, int ReCreateFlag, int GrHandle, const TCHAR *GraphName, int TextureFlag, int ReverseFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL, int ASyncLoadFlag = FALSE ) ;																				// LoadBmpToGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		LoadDivBmpToGraph_UseGParam(            LOADGRAPH_GPARAM *GParam, int ReCreateFlag, const TCHAR *FileName, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag, int ReverseFlag, int ASyncLoadFlag = FALSE ) ;																// LoadDivBmpToGraph �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphFromMem_UseGParam(           LOADGRAPH_GPARAM *GParam, int ReCreateFlag, int GrHandle, void *MemImage, int MemImageSize, void *AlphaImage = NULL, int AlphaImageSize = 0, int TextureFlag = TRUE, int ReverseFlag = FALSE, int ASyncLoadFlag = FALSE ) ;											// CreateGraphFromMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateDivGraphFromMem_UseGParam(        LOADGRAPH_GPARAM *GParam, int ReCreateFlag, void *MemImage, int MemImageSize, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,int TextureFlag, int ReverseFlag, void *AlphaImage, int AlphaImageSize, int ASyncLoadFlag = FALSE ) ;			// CreateDivGraphFromMem �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphFromBmp_UseGParam(           LOADGRAPH_GPARAM *GParam, int ReCreateFlag, int GrHandle, BITMAPINFO *BmpInfo, void *GraphData, BITMAPINFO *AlphaInfo = NULL, void *AlphaData = NULL, int TextureFlag = TRUE, int ReverseFlag = FALSE, int ASyncLoadFlag = FALSE ) ;									// CreateGraphFromBmp �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateDivGraphFromBmp_UseGParam(        LOADGRAPH_GPARAM *GParam, int ReCreateFlag, BITMAPINFO *BmpInfo, void *GraphData, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf,int TextureFlag, int ReverseFlag, BITMAPINFO *AlphaInfo, void *AlphaData, int ASyncLoadFlag = FALSE ) ;		// CreateDivGraphFromBmp �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateGraphFromGraphImage_UseGParam(    LOADGRAPH_GPARAM *GParam, int ReCreateFlag, int GrHandle, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int TextureFlag = TRUE , int ReverseFlag = FALSE, int ASyncLoadFlag = FALSE, int ASyncThread = FALSE ) ;												// CreateGraphFromGraphImage �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateDivGraphFromGraphImage_UseGParam( LOADGRAPH_GPARAM *GParam, int ReCreateFlag, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE, int ASyncLoadFlag = FALSE ) ;					// CreateDivGraphFromGraphImage �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����

extern	int		CreateGraphFromGraphImageBase_UseGParam( CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM *GParam, int ReCreateFlag, int GrHandle, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int TextureFlag, int ASyncThread = FALSE ) ;																									// CreateGraphFromGraphImageBase �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����
extern	int		CreateDivGraphFromGraphImageBase_UseGParam( CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM *GParam, int ReCreateFlag, int BaseHandle, BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag, int ReverseFlag, int ASyncThread = FALSE ) ;		// CreateDivGraphFromGraphImageBase �̃O���[�o���ϐ��ɃA�N�Z�X���Ȃ��o�[�W����


extern	int		ResetFrameCounter( void ) ;													// �t���[���J�E���^�[������������
extern	int		IncFrameCounter( void ) ;													// �t���[���J�E���^�[���C���N�������g����
extern	LONGLONG GetFrameCounter( void ) ;													// �t���[���J�E���^�[�̒l���擾����
extern	int		RefreshLightState( void ) ;													// ���C�g�̕ύX�𔽉f����
extern	void	RefreshProjectionMatrix( void ) ;											// �ˉe�s��p�����[�^�Ɋ�Â��Ďˉe�s����\�z����
extern	void	RefreshBlendTransformMatrix( void ) ;										// ���_�ϊ��s����|�����킹���s����X�V����
extern	void	SetupDisplayModeData( int *Num, DISPLAYMODEDATA **Buffer ) ;				// �f�B�X�v���C���[�h�f�[�^�̏����Z�b�g�A�b�v����

extern	int		CreateGraphFromGraphImageBase( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int TextureFlag ) ;																														// CreateGraphFromGraphImage �̓����֐�
extern	int		CreateDivGraphFromGraphImageBase( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag, int ReverseFlag ) ;							// CreateDivGraphFromGraphImage �̓����֐�
extern	int		ReCreateGraphFromGraphImageBase( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int GrHandle, int TextureFlag ) ;																										// ReCreateGraphFromGraphImage �̓����֐�
extern	int		ReCreateDivGraphFromGraphImageBase( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag , int ReverseFlag ) ;						// ReCreateDivGraphFromGraphImage �̓����֐�

extern	void	InitCreateGraphHandleAndBltGraphImageGParam( CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM *GParam ) ;			// CREATE_GRAPHHANDLE_AND_BLTGRAPHIMAGE_GPARAM �̃f�[�^���Z�b�g����
extern	void	InitSetupGraphHandleGParam( SETUP_GRAPHHANDLE_GPARAM *GParam ) ;												// SETUP_GRAPHHANDLE_GPARAM �̃f�[�^���Z�b�g����

#ifndef DX_NON_DSHOW_MOVIE
#ifndef DX_NON_MOVIE
extern	void	InitOpenMovieGParam( OPENMOVIE_GPARAM *GParam ) ;																// OPENMOVIE_GPARAM �̃f�[�^���Z�b�g����
#endif
#endif
extern	void	InitSetGraphBaseInfoGParam( SETGRAPHBASEINFO_GPARAM *GParam ) ;													// SETGRAPHBASEINFO_GPARAM �̃f�[�^���Z�b�g����
extern	void	InitLoadGraphGParam( LOADGRAPH_GPARAM *GParam ) ;																// LOADGRAPH_GPARAM �̃f�[�^���Z�b�g����

}

#endif // __DXGRAPHICSBASE_H__
