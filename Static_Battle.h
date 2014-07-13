#ifndef STATIC_BATTLE
#define STATIC_BATTLE

//=========================================
// ���j�b�g���֘A

// �p�[�e�B�ɎQ������l�`�̍ő吔
#define MAX_BATTLEDOLL			8
// �O��ɏo��l�`�̍ő吔
#define NUM_BATTLEDOLL_FRONT	3
// �G�̍ő吔
#define MAX_BATTLEENEMY			8
// �U���p�^�[���̍ő吔
#define MAX_UNITCOMMAND			(MAX_BATTLEDOLL + MAX_BATTLEENEMY)


//=========================================
// �A���X�̃R�}���h�Q

#define ALICE_COMMAND_BATTLE		0	// �키
#define ALICE_COMMAND_UNITCHANGE	1	// ���j�b�g����
#define ALICE_COMMAND_SPECIAL		2	// ���Z
#define ALICE_COMMAND_ESCAPE		3	// ������

//=========================================
// commandPhaze�̔z��

#define COMMANDPHAZE_NOPHAZE		0	// �퓬�s���ȊO�Ŏg�p����B
										// actionPhaze���g�p���Ȃ��ꍇ�̒l
#define COMMANDPHAZE_FIX_COMMAND	1	// ������ɁA�������s���ł��邩�𔻒肷��
#define COMMANDPHAZE_FIX_TARGET		2	// �s���̐錾���O�ɁA�^�[�Q�b�g�̊m����s��
#define COMMANDPHAZE_ASSERT			3	// �s���錾���ɍs������B
#define COMMANDPHAZE_PRE_ACTION		4	// �s���O�ɍs������B
#define COMMANDPHAZE_ACTION			5	// �s�����ɍs������B
#define COMMANDPHAZE_CHECK_DEATH	6	// �s����ɂ͂Ƃ肠�������S����B
#define COMMANDPHAZE_POST_ACTION	7	// �s����ɍs������B
#define COMMANDPHAZE_START_TURN		8	// �^�[���̍ŏ��ɍs������B

#define COMMANDPHAZE_ERROR			-1	// �G���[
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_FIX_COMMAND)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)

//=========================================
// 
#define DAMAGE_MAX			9999

//=========================================
// �����U���̔{��

#define ATTRAFFINITY_EVEN	0	// �ӂ�
#define ATTRAFFINITY_STRONG	1	// ����
#define ATTRAFFINITY_WEAK	2	// �ア

#define ATTRRATE_STRONG		2.0
#define ATTRRATE_WEAK		0.5

//=========================================
// �_���[�W�v�Z�̃^�C�v

#define	CALCDAMAGE_ATTACK			0

//=========================================
// �퓬�̌���

#define BATTLERESULT_NONE			0	// �܂����s�������Ă��Ȃ�
#define BATTLERESULT_VICTORY		1	// ������
#define BATTLERESULT_LOSE			2	// �S�ł���


#endif // STATIC_BATTLE