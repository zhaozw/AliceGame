#ifndef STATIC_ALICEDOLL_H
#define STATIC_ALICEDOLL_H

// ��ފ֘A
#define DOLL_TYPE_UNDIFINED			0		// ����`�B���݂��Ȃ���ԁB
#define DOLL_TYPE_SHANGHAI			1		// ��C�l�`
#define DOLL_TYPE_MAIDEN			2		// �퉳���̐l�`
#define DOLL_TYPE_HOURAI			3		// �H���l�`
#define DOLL_TYPE_CAT				4		// �����L�̐l�`
#define DOLL_TYPE_GIANT				5		// �S���A�e�l�`
#define DOLL_TYPE_TENGU				6		// �G�V��̐l�`
#define DOLL_TYPE_FAIRY				7		// �d���̐l�`
#define DOLL_TYPE_MUSICIAN			8		// ���t�Ƃ̐l�`
#define DOLL_TYPE_HUUSUI			9		// �����t�̐l�`
#define DOLL_TYPE_MAID				10		// ���C�h�̐l�`
#define DOLL_TYPE_GREEN				11		// �Ί�̐l�`
#define DOLL_TYPE_RABBIT			12		// �ʓe�̐l�`

#define DOLL_TYPE_PER_GROUP			3		// 1�O���[�v������̐l�`�̐�
#define DOLL_GROUP_NUM				4		// �O���[�v��
#define DOLL_TYPE_MAX	(DOLL_TYPE_PER_GROUP*DOLL_GROUP_NUM) // �l�`�̎�ނ̑���

#define DOLL_GROUP_UNDIFINED		0		// 
#define DOLL_GROUP_BALANCE			1		// �o�����X�^
#define DOLL_GROUP_ATTACKER			2		// �O�q�^
#define DOLL_GROUP_MAGICIAN			3		// ���@�^
#define DOLL_GROUP_SUPPORTER		4		// �T�|�[�g�^

#define DOLL_GROUP_UNDIFINED_STR	"����`"
#define DOLL_GROUP_BALANCE_STR		"�o�����X�^"
#define DOLL_GROUP_ATTACKER_STR		"�O�q�^"
#define DOLL_GROUP_MAGICIAN_STR		"���@�^"
#define DOLL_GROUP_SUPPORTER_STR	"�T�|�[�g�^"

// �����֘A
#define DOLL_ATTR_NONE				0		// ������
#define DOLL_ATTR_SUN				1		// ���z �F�n���͐ԁB
#define DOLL_ATTR_MOON				2		// �� �F�n���͐B
#define DOLL_ATTR_STAR				3		// �� �F�n���͉��F�B
#define DOLL_ATTR_NUM				4		// �S�������B���������܂߂�B
#define DOLL_ATTR_RANDOM			4		// �G�O���[�v�̏��Ƃ��āA�����_���l�B

// �����̂�����֘A
#define DOLL_ATTRSTONE_NUM			6		// �l�`���������̂�����̐�
#define DOLL_ATTRSTONE_CREATE		3		// �l�`�쐬���̑����̂�����̐�

// �\��
#define DOLL_FACE_NORMAL			0		// �ʏ�
#define DOLL_FACE_ATTACK			1		// �U��
#define DOLL_FACE_DAMAGE			2		// �_���[�W
#define DOLL_FACE_FUN				3		// �Ί�
#define DOLL_FACE_HAPPY				4		// ����
#define DOLL_FACE_NUM				5		// �S�\��B


// ���x���֘A
#define DOLL_LEVEL_MAX				8		// ���x���̍ő�l
#define DOLL_POTENTIALLEVEL_MAX		1400	// �������x���̍ő�l
#define DOLL_GLOBALLEVEL_MAX		1600	// �O���[�o�����x���̍ő�l
#define DOLL_LEVEL_FACTOR			20		// ���x�����O���[�o�����x���ɉ��Z����鎞�̌W��
#define DOLL_EXP_MAX				99999999	// �ő�o���l

// �p�����[�^�֘A
#define DOLL_PARAM_MAX				5		// �S�X�e�[�^�X�̐�
#define DOLL_PARAM_HP				0		// �̗�
#define DOLL_PARAM_ATK				1		// �U��
#define DOLL_PARAM_SPD				2		// �q��
#define DOLL_PARAM_MGC				3		// ����
#define DOLL_PARAM_TEC				4		// �Z�I

// �X�L���֘A
#define DOLL_SKILL_MAX				8		// �o����Z�̐�


#endif // STATIC_ALICEDOLL_H