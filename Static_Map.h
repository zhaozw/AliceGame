#ifndef STATIC_MAP_H
#define STATIC_MAP_H

//======================================
// �S�̃}�b�v�Ɋւ���萔�B
// CHOOSEMAP��WorldMap�̗��B

// �G���A���ƃp�X���̍ő�l�B
#define CHOOSEMAP_AREA_MAX			16		// �G���A��
#define CHOOSEMAP_POINT_MAX			24		// �|�C���g���i�K�������|�C���g�ƃG���A�͈�v���Ȃ��j
#define CHOOSEMAP_PATH_MAX			32		// �p�X��
#define CHOOSEMAP_SPOT_MAX			8		// ����Ȏ{�ݐ�
#define CHOOSEMAP_STAGE_MAX			8		// �e�G���A�̍ő�X�e�[�W���B

// �p�X�̏�ԂɊւ���萔
#define CHOOSEMAP_PATHSTATE_NONE	0		// �����������Ă��Ȃ�
#define CHOOSEMAP_PATHSTATE_OPENED	1		// ����������ꂽ
#define CHOOSEMAP_PATHSTATE_CLOSED	2		// ���炩�̗��R�ňꎞ�I�ɕ�����Ă���
#define CHOOSEMAP_PATHSTATE_HIDDEN	3		// ���炩�̗��R�ňꎞ�I�ɕ����ꂽ��A�����Ȃ�

// �}�b�v��ŗp��������̒萔�B
// �k���玞�v���B
#define MAP_NODIRECTION				0
#define MAP_NORTH					1
#define MAP_EAST					2
#define MAP_SOUTH					3
#define MAP_WEST					4

//======================================
// �}�b�v���O���b�h�ɂ���Ďw�肷��B

#define MAPGRID_INI_X			100
#define MAPGRID_DLT_X			120
#define MAPGRID_MAX_X			5		// ���ő吔
#define MAPGRID_INI_Y			80
#define MAPGRID_DLT_Y			100
#define MAPGRID_MAX_Y			4		// �c�ő吔


//======================================
// �e�|�C���g�̑����B

#define MAPPOINT_TYPE_NONE		0		// �����Ȃ��B�ʏ�g�p����Ȃ��B
#define MAPPOINT_TYPE_ENTRY		1		// �X�^�[�g�n�_�B
#define MAPPOINT_TYPE_BATTLE	2		// �퓬�|�C���g�B
#define MAPPOINT_TYPE_ITEM		3		// �A�C�e���擾�|�C���g�B
#define MAPPOINT_TYPE_BOSS		4		// �{�X�|�C���g�B���̃|�C���g�ł̐퓬�ɏ�������ƃN���A�B
#define MAPPOINT_TYPE_TERMINAL	5		// �{�X�ł͂Ȃ����}�b�v�̏o���ł���|�C���g�B
#define MAPPOINT_TYPE_PATH		6		// ���̗U���Ɏg�p����A�[���I�ȃ|�C���g�B

//======================================
// �e�|�C���g�̉����ԁB

#define MAPPOINT_STATE_NONE			0		// ��ԂȂ��B�X�^�[�g�n�_�Ɠ��|�C���g�Ɏg�p����B
#define MAPPOINT_STATE_HIDDEN		1		// �|�C���g���B�ꂽ��ԁB�����\�����Ȃ��B
#define MAPPOINT_STATE_UNKNOWN		2		// �|�C���g������Ă��邪�A������������Ȃ���ԁB
#define MAPPOINT_STATE_UNTRACKED	3		// �|�C���g�̑f���͕������Ă��邪�A�K��Ă��Ȃ��B
											// �N���A�ς݂̃}�b�v�͂��̏�ԂɂȂ�B
#define MAPPOINT_STATE_TRACKED		4		// �ʉߍς݂̃|�C���g�B


#endif // STATIC_MAP_H