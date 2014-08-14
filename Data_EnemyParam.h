#ifndef DATA_ENEMYPARAM_H
#define DATA_ENEMYPARAM_H

#include <Windows.h>
#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

// �G�L�����̔\�͒l�̃f�[�^�x�[�X�������N���X�B
//�f�[�^�̓O���[�o���ϐ�d_enemyParam����Q�Ƃ����B

// �t�@�C����
#define CSVFILE_ENEMYPARAM		"dat_enemy\\enemy%03d.csv"
#define DATFILE_ENEMYPARAM		"dat\\enemy%03d.dat"

// �萔
#define MAX_CONDITION			2	// �����������w��\
#define MAX_CONDITIONPARAM		3	// ����������̃p�����[�^�̐�
#define MAX_ACTIONPATTERN		16	// �U���p�^�[���̐�
#define MAX_INITIALSTATE		8	// �ŏ����玝���Ă���X�e�[�g�̍ő吔

// �s���p�^�[���Ɋւ���p�����[�^���܂Ƃ߂Ďw�肷��p
#define ACTIONPATTERN_ACTIONTYPE			0
#define ACTIONPATTERN_SKILLID				1
#define ACTIONPATTERN_ECOMMANDTARGET		2
#define ACTIONPATTERN_PRIORITY				3
#define ACTIONPATTERN_PARAMNUM				4

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
		actionType		= COMMANDTYPE_NONE;
		skillID			= 0;
		targetType		= ECOMMANDTARGET_NONE;
		priority		= 0;
		for(int j=0; j<MAX_CONDITION; j++){
			conditionType[j] = CONDITIONTYPE_ALWAYS;
			for(int i=0; i<MAX_CONDITIONPARAM; i++){
				conditionParam[j][i] = 0;
			}
		}
	}
}ENEMYACTIONPATTERN;

typedef struct EnemyInitialState{
	WORD	refID;
	int		param;
	int		param2;
	EnemyInitialState(){
		refID = 0;
		param = 0;
		param2 = 0;
	}
} ENEMYINITIALSTATE;

typedef struct Data_EnemyParam_Each_Data{
	WORD		refID;							// �Q�Ƃ���鎞��ID
	TCHAR		name[BATTLEUNIT_NAME_BYTES];	// ���O
	int			param[NUM_ENEMYPARAM_DATA];		// �e�\�͒l(HP������)
	BYTE		attr;							// ����
	DWORD		exp;							// �o���l
	// �s���p�^�[���̔z��
	ENEMYACTIONPATTERN		actionPtn[MAX_ACTIONPATTERN];
	// ������ԂŎ����Ă���X�e�[�g�y�уp�����[�^�̔z��
	ENEMYINITIALSTATE		stateArray[MAX_INITIALSTATE];
	Data_EnemyParam_Each_Data(){
		refID = 0;
		attr = DOLL_ATTR_NONE;
		exp = 0;
		for(int n=0; n<BATTLEUNIT_PARAM_NUM-1; n++){
			param[n] = 0;
		}
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, "");
		// �e�U���p�^�[���̃��Z�b�g
		for(int n=0; n<MAX_ACTIONPATTERN; n++){
			actionPtn[n].actionType = COMMANDTYPE_ERROR;
			actionPtn[n].skillID = 0;
			actionPtn[n].targetType = ACTIONTARGET_NONE;
			actionPtn[n].priority = 0;
			// �U�������̃��Z�b�g
			for(int i=0; i<MAX_CONDITION; i++){
				actionPtn[n].conditionType[i] = CONDITIONTYPE_ALWAYS;
				for(int j=0; j<MAX_CONDITIONPARAM; j++){
					actionPtn[n].conditionParam[i][j] = 0;
				}
			}
		}
	}
} DATA_ENEMYPARAM_EACH_DATA;

// Data_EnemyParam_Each�N���X�B
// �G��̂ɂ��Ă̏���ێ�����B
// ���ۂɂ́A���̃N���X�̔z�������FlexList���쐬�����B
class Data_EnemyParam_Each{
public:
	DATA_ENEMYPARAM_EACH_DATA	data;
public:
	// �R���X�g���N�^
	Data_EnemyParam_Each();
	void	GetName(LPTSTR buf, int bufSize=-1){
		strcpy_s(buf, (bufSize!=-1?bufSize-1:BATTLEUNIT_NAME_BYTES-1), data.name); 
	}
	void	SetName(LPTSTR name){
		strcpy_s(name, BATTLEUNIT_NAME_BYTES-1, data.name); 
	}
	// �e�p�����[�^�̎Q��
	void	SetHP(int value){	data.param[ENEMYPARAM_HP] = value; };
	void	SetAtk(int value){	data.param[ENEMYPARAM_ATK] = value; };
	void	SetDef(int value){	data.param[ENEMYPARAM_DEF] = value; };
	void	SetSpd(int value){	data.param[ENEMYPARAM_SPD] = value; };
	void	SetMgc(int value){	data.param[ENEMYPARAM_MGC] = value; };
	void	SetTec(int value){	data.param[ENEMYPARAM_TEC] = value; };
	int		GetHP(){	return data.param[ENEMYPARAM_HP]; };
	int		GetAtk(){	return data.param[ENEMYPARAM_ATK]; };
	int		GetDef(){	return data.param[ENEMYPARAM_DEF]; };
	int		GetSpd(){	return data.param[ENEMYPARAM_SPD]; };
	int		GetMgc(){	return data.param[ENEMYPARAM_MGC]; };
	int		GetTec(){	return data.param[ENEMYPARAM_TEC]; };

	void	SetInitialState(int index, WORD refID, int param, int param2){
		data.stateArray[index].refID = refID;
		data.stateArray[index].param = param;
		data.stateArray[index].param2 = param2;
	};
	WORD	GetInitialStateRefID(int index){ return data.stateArray[index].refID; };
	int		GetInitialStateParam(int index){ return data.stateArray[index].param; };
	int		GetInitialStateParam2(int index){ return data.stateArray[index].param2; };

	// �s���p�^�[�����C���f�b�N�X�Ŏw��
	void	SetActionPattern(int index, int paramIndex, int value);
	int		GetActionPattern(int index, int paramIndex);
	ENEMYACTIONPATTERN*	GetActionPatternPtr(int index);
	// �s���p�^�[���𒼐ڎw��
	void	SetActionType(int index, WORD type){ data.actionPtn[index].actionType = type; };
	void	SetActionSkillID(int index, DWORD skillID){
		data.actionPtn[index].skillID = skillID; 
	};
	void	SetActionTarget(int index, BYTE type){ data.actionPtn[index].targetType = type; };
	void	SetActionPriority(int index, WORD p){ data.actionPtn[index].priority = p; };
	WORD	GetActionType(int index){ return data.actionPtn[index].actionType; };
	DWORD	GetActionSkillID(int index){ return data.actionPtn[index].skillID; };
	BYTE	GetActionTarget(int index){ return data.actionPtn[index].targetType; };
	WORD	GetActionPriority(int index){ return data.actionPtn[index].priority; };
	// �s���p�^�[���̎Q�Ƃ�Ԃ�
	ENEMYACTIONPATTERN* GetActPatternPtr(){ return data.actionPtn; };
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
	bool LoadDataFromDat();

	// �Í���
	bool EncodeCsv();

	void ReleaseList(){ enemyList.Release(); };

	// ��������A�N�V�����^�C�v�ɕϊ�����B
	// A : �U��
	// S : ���Z
	// G : �h��
	// W, �G���[ : �������Ȃ�
	WORD GetActionTypeFromChar(TCHAR c);


	// �G�p�����[�^�ւ̃|�C���^���擾����B
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyParam_Each* GetEnemyParam(WORD _refID);


	// �傫����Ԃ��B
	int GetSize(){ return enemyList.GetSize(); };
};


#endif // DATA_ENEMYPARAM