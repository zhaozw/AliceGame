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
// ���j�b�g���̍ő啶����
#define BATTLEUNIT_NAME					10
// TCHAR�̃o�C�g���Z�������̍ő�o�C�g��
// ���{���1����2�o�C�g�̂͂������A
// �����G���[���N���Ă��߂�ǂ������̂ő��߂ɃT�C�Y���m�ۂ��Ă���
// #define BATTLEUNIT_NAME_BYTES			(BATTLEUNIT_NAME*2)
#define BATTLEUNIT_NAME_BYTES			32

//======================================
// ���j�b�g�̃p�����[�^�֘A
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

// �X�e�[�g�Ɋւ���
#define BATTLEUNIT_STATE_MAX			16		// �����ɂ�����X�e�[�g�̍ő吔

//========================================
// �G�f�[�^�̃p�����[�^��
#define NUM_ENEMYPARAM_DATA			(BATTLEUNIT_PARAM_NUM-1)
#define ENEMYPARAM_HP				0
#define ENEMYPARAM_ATK				1
#define ENEMYPARAM_DEF				2
#define ENEMYPARAM_SPD				3
#define ENEMYPARAM_MGC				4
#define ENEMYPARAM_TEC				5



//=========================================
// �A���X�̃R�}���h�Q

#define ALICE_COMMAND_BATTLE		0	// �키
#define ALICE_COMMAND_UNITCHANGE	1	// ���j�b�g����
#define ALICE_COMMAND_SPECIAL		2	// ���Z
#define ALICE_COMMAND_ESCAPE		3	// ������

//==========================================
// �R�}���h�̎�ނɊւ���萔
#define COMMANDTYPE_ERROR		0	// �ǂݍ��݃G���[
#define COMMANDTYPE_NONE		1	// �������Ȃ�
#define COMMANDTYPE_ATTACK		2	// �ʏ�U��
#define COMMANDTYPE_GUARD		3	// �h��
#define COMMANDTYPE_SKILL		4	// ���Z


//=========================================
// commandPhaze�̔z��

#define COMMANDPHAZE_NOPHAZE		0	// �퓬�s���ȊO�Ŏg�p����B
										// actionPhaze���g�p���Ȃ��ꍇ�̒l
#define COMMANDPHAZE_BEFORE_SORT	1	// �R�}���h��f�������ɓ���ւ���O�B
										// ��{�I�ɁA�f������␳����ȊO��
										// �s�ׂ͍s��Ȃ��B
#define COMMANDPHAZE_AFTER_SORT		2	// �f�������ɓ���ւ�����ɍs���B
										// �����ւ̃X�e�[�g�t���ȂǁB
#define COMMANDPHAZE_NEXTCOMMAND	3	// ���̃R�}���h�Ɉړ����鎞�ɓ����l�B
										// ���ꎩ�g�͓��ɈӖ��͂Ȃ��B
#define COMMANDPHAZE_FIX_COMMAND	10	// ������ɁA�������s���ł��邩�𔻒肷��
#define COMMANDPHAZE_FIX_TARGET		11	// �s���̐錾���O�ɁA�^�[�Q�b�g�̊m����s��
#define COMMANDPHAZE_ASSERT			12	// �s���錾���ɍs������B
#define COMMANDPHAZE_PRE_ACTION		13	// �s���O�ɍs������B
#define COMMANDPHAZE_ACTION			14	// �s�����ɍs������B
#define COMMANDPHAZE_CHECK_DEATH	15	// �s����ɂ͂Ƃ肠�������S����B
#define COMMANDPHAZE_POST_ACTION	16	// �s����ɍs������B

#define COMMANDPHAZE_ERROR			-1	// �G���[
#define COMMANDPHAZE_FIRSTPHAZE		(COMMANDPHAZE_FIX_COMMAND)
#define COMMANDPHAZE_LASTPHAZE		(COMMANDPHAZE_POST_ACTION)

//=========================================
// �_���[�W�̍ő�l�B
#define DAMAGE_MAX			9999

//=========================================
// �����U���̔{��
#define ATTRAFFINITY_EVEN	0	// �ӂ�
#define ATTRAFFINITY_STRONG	1	// ����
#define ATTRAFFINITY_WEAK	2	// �ア

#define ATTRRATE_STRONG		2.0		// ��_���������ɗ^����_���[�W
#define ATTRRATE_WEAK		0.5		// ���肪�L���������Ƃ��ɗ^����_���[�W

//=============================================
// �s���̃^�[�Q�b�g�Ɋւ���萔
#define ACTIONTARGET_NONE			0	// �^�[�Q�b�g�Ȃ�
#define ACTIONTARGET_DOLL_ONE		1	// �l�`���
#define ACTIONTARGET_DOLL_ALL		2	// �l�`�S��
#define ACTIONTARGET_ENEMY_ONE		3	// �G���
#define ACTIONTARGET_ENEMY_ALL		4	// �G�S��
#define ACTIONTARGET_NO_MP			10	// ���͂�����Ȃ����Ƀt���O�Ƃ��Ďg�p�������Ȓl�B

//=============================================
// �X�L���̃^�[�Q�b�g�Ƃ��ė��p����萔�B
#define SKILLTARGET_NONE			0	// �ΏۂȂ�(�������͏�S��)
#define SKILLTARGET_TEAM_ONE		1	// �������(�l�`�Ȃ�l�`�A�G�Ȃ�G)
#define SKILLTARGET_TEAM_ALL		2	// �����S��
#define SKILLTARGET_OPPONENT_ONE	3	// ������
#define SKILLTARGET_OPPONENT_ALL	4	// ����S��
#define SKILLTARGET_SELF			5	// ����

//=======================================
// �G�̍s���̑ΏۂɊւ���萔
// Data_EnemyParam�ɂ����Ďg�p����B
// ���̒l�����ɍs���̑Ώۂ��v�Z���A
// ���ۂ̃R�}���h�̑ΏۂƂ��ē��Ă͂߂�B
#define ECOMMANDTARGET_NONE				0	// �ΏۂȂ��i�������͏�S�́j
#define ECOMMANDTARGET_DOLL_RANDOM		1	// �l�`��̂������_����
#define ECOMMANDTARGET_DOLL_ALL			2	// �l�`�S��
#define ECOMMANDTARGET_ENEMY_RANDOM		3	// �G��̂������_����
#define ECOMMANDTARGET_ENEMY_ALL		4	// �G�S��
#define ECOMMANDTARGET_SELF				5	// ����
#define ECOMMANDTARGET_DOLL_HP_MIN		6	// HP�̍ł����Ȃ��l�`���
#define ECOMMANDTARGET_DOLL_HP_MIN2		7	// �ő�HP�ɑ΂���HP�̔䂪�ł����Ȃ��l�`���
#define ECOMMANDTARGET_ENEMY_HP_MIN		8	// HP�̍ł����Ȃ��G���
#define ECOMMANDTARGET_ENEMY_HP_MIN2	9	// �ő�HP�ɑ΂���HP�̔䂪�ł����Ȃ��G���
#define ECOMMANDTARGET_ENEMY_OTHER		10	// �����ȊO�̖������

//==============================================
// �s���p�^�[������肤�邩���Ȃ����̏����B
// �����ɍ����s�����Apriority�ɏ]���đI������B

// �펞�s���B
// �R���h�����߁A�K�����̏��������s����1�ȏ㎝���Ă���ׂ��B
#define CONDITIONTYPE_ALWAYS			0 
// �s�����s��HP�̍ő�l���K�肷��B
// param[0] : HP��(x)%�ȏ�̎��͍s��Ȃ��B
#define CONDITIONTYPE_MAX_HP_RATE		1
// �s�����s��HP�̍ő�l���K�肷��B
// param[0] : HP��(x)%�ȉ��̎��͍s��Ȃ��B
#define CONDITIONTYPE_MIN_HP_RATE		2
// �^�[���ɂ��B
// [0][1] : �퓬���n�܂��Ă���̃^�[������[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC			3
// �^�[���ɂ�邻��2�B
// [0][1] : �G���ɈقȂ�^�[����selfTurn��[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC2			4
// HP�����͈͂̏ꍇ�B
// [0] : HP��[0]%�ȉ��ł���ꍇ�ł���A�����
// [1] : HP��[1]%�ȏ�ł���ꍇ�͍s������B
#define CONDITIONTYPE_HP_RATE_RANGE		5
// �����̒N����HP����芄���ȉ��ł��鎞�ɍs���B(P�̓p�[�e�B�̗�)
// param[0] : HP��(x)%�ȏ�̎��͍s��Ȃ��B
#define CONDITIONTYPE_MAX_HP_RATE_P		6
// ����������̑����ł��鎞�Ɏg���B
// �X�L���Ȃǂő������ω����Ă��鎞�ɁB
// param[0] : ���F0, ���z�F1, ���F2, ���F3�B
#define CONDITIONTYPE_ATTR				7
// actionCount�̐��l�ɂ��(���s���Ȃǂ̂���)�B
// [0][1] : actionCount�̒l��[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC3			8

// [0][1] : selfTurn��actionCount�̘a��[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC4			9

//==========================================
// ���j�b�g�ɑ΂��ēK�p����A�N�V�����Ɋւ���萔�B
// �����ł̃A�N�V�����͉��Z�̌��ʊ��Ɋm�肵�����̂ł���A
// ���΂��Ȃǂ̍s���͓K�p����Ȃ��B
#define ACTIONTYPE_DAMAGE		0	// �_���[�W�B
#define ACTIONTYPE_HEAL			1	// �񕜁B
#define ACTIONTYPE_STATE		10	// �X�e�[�g�t���B�p�����[�^�͎g�p���Ȃ��B
#define ACTIONTYPE_STATE_ATTR	11	// �����֌W�̃X�e�[�g�t���B
									// �p�����[�^��1000�̈ʂ��X�e�[�g�̃^�[�����B
									// 1000�̈ʈȉ����t������X�e�[�g��ID�B
#define ACTIONTYPE_ATTR			3	// �����̉i���I�ύX�B
									// �X�e�[�g�ɂ��ꎞ�I�ȕύX�Ƃ͈قȂ�B
									// ��{�I�ɂ͖����ɂ͓K�p����Ȃ��B
#define ACTIONTYPE_NO_MP		99	// MP������Ȃ��B


//=========================================
// �_���[�W�v�Z�̃^�C�v
#define	CALCDAMAGE_ATTACK			0
#define	CALCDAMAGE_TECH				1		// �Z�I - ����̖h��
#define	CALCDAMAGE_TECH_TECH		2		// �Z�I�~2 - ����̋Z�I - ����̖h��
#define	CALCDAMAGE_TECH_NOGUARD		3		// �Z�I(�h�䖳��)
#define	CALCDAMAGE_TECH_NOATTR		4		// �Z�I-�h��(��������)
#define	CALCDAMAGE_MAGIC_MAGIC		5		// ���́~2 - ����̖��� - ����̖h��
#define	CALCDAMAGE_ATTACK_DOUBLE	6		// �U���́~2 - �����(�Z�I�����͂̍����ق�) - ����̖h��

//=========================================
// �񕜗ʌv�Z�̃^�C�v
#define CALCHEAL_UNDIFINED			0
#define	CALCHEAL_HEAL1				1		// �񕜂̏p��1
#define	CALCHEAL_MAGIC				2		// ���͒l�Ɠ����l
#define	CALCHEAL_MAGIC_DOUBLE		3		// ���͂�2�{

//=========================================
// �퓬�̌���
#define BATTLERESULT_NONE			0	// �܂����s�������Ă��Ȃ�
#define BATTLERESULT_VICTORY		1	// ������
#define BATTLERESULT_LOSE			2	// �S�ł���
#define BATTLERESULT_ESCAPE			3	// ������




#endif // STATIC_BATTLE