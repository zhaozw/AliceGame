#ifndef DATA_ENEMYPARAM_H
#define DATA_ENEMYPARAM_H

#include <Windows.h>
#include "Static_BattleUnit.h"
#include "VectorList.h"

// �G�L�����̔\�͒l�̃f�[�^�x�[�X�������N���X�B
//�f�[�^�̓O���[�o���ϐ�d_enemyParam����Q�Ƃ����B

// �萔
#define MAX_CONDITION			2	// �����������w��\
#define MAX_CONDITIONPARAM		3	// ����������̃p�����[�^�̐�
#define MAX_ACTIONPATTERN		16	// �U���p�^�[���̐�

/*
// ���̓��e��Static_BattleUnit�Ɉڍs�B
// �s���̎�ނɊւ���萔
#define ACTIONTYPE_NONE			0	// �������Ȃ�
#define ACTIONTYPE_ATTACK		1	// �ʏ�U��
#define ACTIONTYPE_GUARD		2	// �h��
#define ACTIONTYPE_SKILL		3	// ���Z
*/

// �s���̑ΏۂɊւ���萔
#define TARGETTYPE_NONE				0	// �ΏۂȂ��i�������͏�S�́j
#define TARGETTYPE_DOLL_RANDOM		1	// �l�`��̂������_����
#define TARGETTYPE_DOLL_ALL			2	// �l�`�S��
#define TARGETTYPE_ENEMY_RANDOM		3	// �G��̂������_����
#define TARGETTYPE_ENEMY_ALL		4	// �G�S��
#define TARGETTYPE_SELF				5	// ����
#define TARGETTYPE_DOLL_HP_MIN		6	// HP�̍ł����Ȃ��l�`���
#define TARGETTYPE_DOLL_HP_MIN2		7	// �ő�HP�ɑ΂���HP�̔䂪�ł����Ȃ��l�`���
#define TARGETTYPE_ENEMY_HP_MIN		8	// HP�̍ł����Ȃ��G���
#define TARGETTYPE_ENEMY_HP_MIN2	9	// �ő�HP�ɑ΂���HP�̔䂪�ł����Ȃ��G���

// �G�f�[�^�̃p�����[�^��
#define NUM_ENEMYPARAM_DATA			(BATTLEUNIT_PARAM_NUM-1)
#define ENEMYPARAM_HP				0
#define ENEMYPARAM_ATK				1
#define ENEMYPARAM_DEF				2
#define ENEMYPARAM_SPD				3
#define ENEMYPARAM_MGC				4
#define ENEMYPARAM_TEC				5

// �s���p�^�[������肤�邩���Ȃ����̏����B
// �����ɍ����s�����Apriority�ɏ]���đI������B

// �펞�s���B
// �R���h�����߁A�K�����̏��������s����1�ȏ㎝���Ă���ׂ��B
#define CONDITIONTYPE_ALWAYS		0 
// �s�����s��HP�̍ő�l���K�肷��B
// param[0] : HP��(x)%�ȏ�̎��͍s��Ȃ��B
#define CONDITIONTYPE_MAX_HP_RATE		1
// �s�����s��HP�̍ő�l���K�肷��B
// param[0] : HP��(x)%�ȉ��̎��͍s��Ȃ��B
#define CONDITIONTYPE_MIN_HP_RATE		2

// �^�[���ɂ��B
// [0][1] : �퓬���n�܂��Ă���̃^�[������[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC	1

// �^�[���ɂ�邻��2�B
// [0][1] : �G���ɈقȂ�^�[����selfTurn��[0]�Ŋ��������̒l��[1]�ł���΍s���B
#define CONDITIONTYPE_PERIODIC2	2

// HP�����͈͂̏ꍇ�B
// [0] : HP��[0]%�ȉ��ł���ꍇ�ł���A�����
// [1] : HP��[1]%�ȏ�ł���ꍇ�͍s������B
#define CONDITIONTYPE_HP		3

// �s���p�^�[���Ɋւ���p�����[�^���܂Ƃ߂Ďw�肷��p
#define ACTIONPATTERN_ACTIONTYPE	0
#define ACTIONPATTERN_SKILLID		1
#define ACTIONPATTERN_TARGETTYPE	2
#define ACTIONPATTERN_PRIORITY		3
#define ACTIONPATTERN_PARAMNUM		4

// �G�L�����̍s���p�^�[���̈�������\���́B
typedef struct EnemyActionPattern{
	WORD		actionType;			// �s���̎�ށB
	DWORD		skillID;			// �s�������Z�ł���ꍇ�A���ZID
	BYTE		targetType;			// �s���̑Ώۂ̎��
	WORD		priority;			// �s���̗D��x�B���ꂪ0�ł���Ƃ������Ƃ�
									// �s�����w�肳��Ă��Ȃ��Ƃ������Ƃ��Ӗ�����B
	// ���̍s����I����������̃^�C�v
	WORD		conditionType[MAX_CONDITION];
	// �����Ɋ֘A����p�����[�^
	int			conditionParam[MAX_CONDITION][MAX_CONDITIONPARAM];
	EnemyActionPattern(){
		actionType		= ACTIONTYPE_NONE;
		skillID			= 0;
		targetType		= TARGETTYPE_NONE;
		priority		= 0;
		for(int j=0; j<MAX_CONDITION; j++){
			conditionType[j] = CONDITIONTYPE_ALWAYS;
			for(int i=0; i<MAX_CONDITIONPARAM; i++){
				conditionParam[j][i] = 0;
			}
		}
	}
}ENEMYACTIONPATTERN;

// Data_EnemyParam_Each�N���X�B
// �G��̂ɂ��Ă̏���ێ�����B
// ���ۂɂ́A���̃N���X�̔z�������FlexList���쐬�����B
class Data_EnemyParam_Each{
private:
	WORD		refID;							// �Q�Ƃ���鎞��ID
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// ���O
	int			param[NUM_ENEMYPARAM_DATA];	// �e�\�͒l(HP������)
	BYTE		attr;							// ����
	DWORD		exp;							// �o���l
	// �s���p�^�[���̔z��
	ENEMYACTIONPATTERN		actionPtn[MAX_ACTIONPATTERN];
public:
	// �R���X�g���N�^
	Data_EnemyParam_Each();
	void	Refresh();
	// �A�N�Z�T
	void	SetRefID(WORD _refID){ refID = _refID; };
	WORD	GetRefID(){ return refID; };
	LPTSTR	GetNamePtr(){ return name; }; // ���ڃ|�C���^���擾����B���Ɗ댯�B
	void	GetName(LPTSTR buf, int bufSize=-1){
		strcpy_s(buf, (bufSize!=-1?bufSize-1:BATTLEUNIT_NAME_BYTES-1), name); 
	}
	void	SetName(LPTSTR name){
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, name); 
	}
	void	SetAttr(BYTE _attr){ attr = _attr; };
	BYTE	GetAttr(){ return attr; };
	void	SetExp(DWORD _exp){ exp = _exp; };
	DWORD	GetExp(){ return exp; };
	// �p�����[�^
	void	SetParam(int index, int value){
		if(index >= 0 && index < NUM_ENEMYPARAM_DATA){
			param[index] = value; 
		}
	};
	int		GetParam(int index){
		if(index >= 0 && index < NUM_ENEMYPARAM_DATA){
			return param[index]; 
		}
		return BATTLEUNIT_PARAM_ERROR;
	};
	// �e�p�����[�^�̎Q��
	void	SetHP(int value){ param[ENEMYPARAM_HP] = value; };
	void	SetAtk(int value){ param[ENEMYPARAM_ATK] = value; };
	void	SetDef(int value){ param[ENEMYPARAM_DEF] = value; };
	void	SetSpd(int value){ param[ENEMYPARAM_SPD] = value; };
	void	SetMgc(int value){ param[ENEMYPARAM_MGC] = value; };
	void	SetTec(int value){ param[ENEMYPARAM_TEC] = value; };
	int		GetHP(){ return param[ENEMYPARAM_HP]; };
	int		GetAtk(){ return param[ENEMYPARAM_ATK]; };
	int		GetDef(){ return param[ENEMYPARAM_DEF]; };
	int		GetSpd(){ return param[ENEMYPARAM_SPD]; };
	int		GetMgc(){ return param[ENEMYPARAM_MGC]; };
	int		GetTec(){ return param[ENEMYPARAM_TEC]; };



	// �s���p�^�[�����C���f�b�N�X�Ŏw��
	void	SetActionPattern(int index, int paramIndex, int value);
	int		GetActionPattern(int index, int paramIndex);
	ENEMYACTIONPATTERN*	GetActionPatternPtr(int index);
	// �s���p�^�[���𒼐ڎw��
	void	SetActionType(int index, WORD type){ actionPtn[index].actionType = type; };
	void	SetActionSkillID(int index, DWORD skillID){
		actionPtn[index].skillID = skillID; 
	};
	void	SetActionTarget(int index, BYTE type){ actionPtn[index].targetType = type; };
	void	SetActionPriority(int index, WORD p){ actionPtn[index].priority = p; };
	WORD	GetActionType(int index){ return actionPtn[index].actionType; };
	DWORD	GetActionSkillID(int index){ return actionPtn[index].skillID; };
	BYTE	GetActionTarget(int index){ return actionPtn[index].targetType; };
	WORD	GetActionPriority(int index){ return actionPtn[index].priority; };
	// �s���p�^�[���̎Q�Ƃ�Ԃ�
	ENEMYACTIONPATTERN* GetActPatternPtr(){ return actionPtn; };
	// �s���p�^�[���̏���
	void	SetActConditionPattern(int index, int conditionIndex, int type);
	int		GetActConditionPattern(int index, int conditionIndex);
	void	SetActConditionParam(
		int index, int conditionIndex, int paramIndex, int value);
	int		GetActConditionParam(
		int index, int conditionIndex, int paramIndex);
};

// Data_EnemyParam�N���X�B
// �S�Ă̓G�̏���ێ�����B
// FlexList�Ƃ���Data_EnemyParam_Each�N���X�̔z������B
class Data_EnemyParam{
private:
	VectorList<Data_EnemyParam_Each>		enemyList;
public:
	// �R���X�g���N�^
	Data_EnemyParam();
	// ���e���t�@�C������ǂݍ���
	bool Load();
	bool LoadDataFromCsv();

	// �G�p�����[�^�ւ̃|�C���^���擾����B
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyParam_Each* GetEnemyParam(WORD _refID);
};


#endif // DATA_ENEMYPARAM