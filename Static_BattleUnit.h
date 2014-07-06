#ifndef STATIC_BATTLEUNIT_H
#define STATIC_BATTLEUNIT_H

// ���O�̍ő啶����
#define BATTLEUNIT_NAME					10
// TCHAR�̃o�C�g���Z�������̍ő�o�C�g��
// ���{���1����2�o�C�g�̂͂������A
// �����G���[���N���Ă��߂�ǂ������̂ő��߂ɃT�C�Y���m�ۂ��Ă���
// #define BATTLEUNIT_NAME_BYTES			(BATTLEUNIT_NAME*2)
#define BATTLEUNIT_NAME_BYTES			32

// �p�����[�^�֘A
#define BATTLEUNIT_PARAM_NUM			7		// �p�����[�^�̍ő吔�B
												// �̗͂ƍő�̗͕͂ʃp�����[�^�����B
#define BATTLEUNIT_PARAM_HP				0		// �̗�
#define BATTLEUNIT_PARAM_MAXHP			1		// �ő�HP
#define BATTLEUNIT_PARAM_ATK			2		// �U��
#define BATTLEUNIT_PARAM_DEF			3		// �h���
#define BATTLEUNIT_PARAM_SPD			4		// �q��
#define BATTLEUNIT_PARAM_MGC			5		// ����
#define BATTLEUNIT_PARAM_TEC			6		// �Z�I

#define BATTLEUNIT_PARAM_ERROR			-9999	// �ςȒl�ɃA�N�Z�X�������̖߂�l

// �s���̎�ނɊւ���萔
#define ACTIONTYPE_ERROR		0	// �ǂݍ��݃G���[
#define ACTIONTYPE_NONE			1	// �������Ȃ�
#define ACTIONTYPE_ATTACK		2	// �ʏ�U��
#define ACTIONTYPE_GUARD		3	// �h��
#define ACTIONTYPE_SKILL		4	// ���Z

// �s���̃^�[�Q�b�g�Ɋւ���萔
#define ACTIONTARGET_NONE		0	// �^�[�Q�b�g�Ȃ�
#define ACTIONTARGET_DOLL_ONE	1	// �l�`���
#define ACTIONTARGET_DOLL_ALL	2	// �l�`�S��
#define ACTIONTARGET_ENEMY_ONE	3	// �G���
#define ACTIONTARGET_ENEMY_ALL	4	// �G�S��

#endif // STATIC_BATTLEUNIT_H