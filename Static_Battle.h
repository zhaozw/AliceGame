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
#define MAX_UNITCOMMAND			(NUM_BATTLEDOLL_FRONT + MAX_BATTLEENEMY)


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
#define COMMANDPHAZE_ASSERT			1	// �s���錾���ɍs������B
#define COMMANDPHAZE_PRE_ACTION		2	// �s���O�ɍs������B
#define COMMANDPHAZE_ACTION			3	// �s�����ɍs������B
#define COMMANDPHAZE_CHECK_DEATH	4	// �s����ɂ͂Ƃ肠�������S����B
#define COMMANDPHAZE_POST_ACTION	5	// �s����ɍs������B

#define COMMANDPHAZE_ERROR			-1	// �G���[
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_ASSERT)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)

//=========================================
// 
#define DAMAGE_MAX			9999

//=========================================
// �����U���̔{��

#define ATTRRATE_STRONG		2.0
#define ATTRRATE_WEAK		0.5

//=========================================
// �_���[�W�v�Z�̃^�C�v

#define	CALCDAMAGE_ATTACK			0


#endif // STATIC_BATTLE