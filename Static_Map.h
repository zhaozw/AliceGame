#ifndef STATIC_MAP_H
#define STATIC_MAP_H

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