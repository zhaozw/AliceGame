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
#define COMMANDPHAZE_PRE_ACTION		1	// �s���O�ɍs������B
#define COMMANDPHAZE_ACTION			2	// �s�����ɍs������B
#define COMMANDPHAZE_POST_ACTION	3	// �s����ɍs������B

#define COMMANDPHAZE_ERROR			-1	// �G���[
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_PRE_ACTION)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)


#endif // STATIC_BATTLE