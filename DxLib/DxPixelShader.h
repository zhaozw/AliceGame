// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�s�N�Z���X�V�F�[�_�[�֘A��`
// 
// 				Ver 3.10c
// 
// -------------------------------------------------------------------------------

#define DX_PS_CONSTF_ZERO_HALF_ONE_TWO          0		// x=0.0f, y=0.5f, z=1.0f, w=2.0f
#define DX_PS_CONSTF_AMBIENT_EMISSIVE           1		// �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
#define DX_PS_CONSTF_MATERIAL_START             2		// �}�e���A�����̊i�[�J�n�A�h���X
#define DX_PS_CONSTF_MATERIAL_SIZE              3		// �}�e���A���p�̃��W�X�^�̐�
#define DX_PS_CONSTF_MAT_DIFFUSE                0		// �}�e���A���̃f�B�t���[�Y�J���[
#define DX_PS_CONSTF_MAT_SPECULAR               1		// �}�e���A���̃X�y�L�����J���[
#define DX_PS_CONSTF_MAT_POWER                  2		// �}�e���A���̃X�y�L�����n�C���C�g�̃p���[
#define DX_PS_CONSTF_FACTORCOLOR                5		// �����x��
#define DX_PS_CONSTF_TOON_OUTLINE_COLOR         6		// �g�D�[�������_�����O�̗֊s���̐F
#define DX_PS_CONSTF_TOON_OUTLINE_WIDTH         7		// �g�D�[�������_�����O�̗֊s���̑���
#define DX_PS_CONSTF_FOG_COLOR                  8		// �t�H�O�J���[
#define DX_PS_CONSTF_LIGHT_START                9		// ���C�g���̊i�[�J�n�A�h���X
#define DX_PS_CONSTF_LIGHT_UNITSIZE             3		// ���C�g�̏���ӂ�̎g�p���W�X�^�̐�
#define DX_PS_CONSTF_LGT_DIFFUSE                0		// ���C�g�̃f�B�t���[�Y�J���[
#define DX_PS_CONSTF_LGT_SPECULAR               1		// ���C�g�̃X�y�L�����J���[
#define DX_PS_CONSTF_LGT_AMBIENT                2		// ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
#define DX_PS_CONSTF_LIGHT2_START               32		// ���C�g�g�����̊i�[�J�n�A�h���X
#define DX_PS_CONSTF_LIGHT2_UNITSIZE            7		// ���C�g�g������ӂ�Ɏg�p���郌�W�X�^�̐�
#define DX_PS_CONSTF_LGT2_POSITION              0		// ���C�g�̈ʒu( �r���[��� )
#define DX_PS_CONSTF_LGT2_DIRECTION             1		// ���C�g�̕���( �r���[��� )
#define DX_PS_CONSTF_LGT2_DIFFUSE               2		// ���C�g�̃f�B�t�[�Y�F
#define DX_PS_CONSTF_LGT2_SPECULAR              3		// ���C�g�̃X�y�L�����F
#define DX_PS_CONSTF_LGT2_AMBIENT               4		// ���C�g�̃A���r�G���g�F�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
#define DX_PS_CONSTF_LGT2_RANGE_FALLOFF_AT0_AT1 5		// ���C�g�� x:�L�������̓�� y:�t�H�[���I�t z:���������p�����[�^�O w:���������p�����[�^�P
#define DX_PS_CONSTF_LGT2_AT2_SPOTP0_SPOTP1     6		// ���C�g�� x:���������p�����[�^�Q y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) ) z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )
