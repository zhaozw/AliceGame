#ifndef DATA_DOLLPARAM_H
#define DATA_DOLLPARAM_H

#include <Windows.h>
#include "Static_AliceDoll.h"

// �l�`�̃��x���ƃp�����[�^�̊֌W�Ɋւ���f�[�^��ێ�����N���X�B
// �O���[�o���ϐ�g_dollParam����Q�Ƃ����B

#define DOLL_TYPENAME_BYTES		18
#define DATFILE_DOLLPARAM		"dat\\doll.dat"

// �������x�����p�����[�^�ɕϊ�����ۂ̐����̌W���̍\���́B
// ���x����x�Ƃ��āA�p�����[�^��ax^2+bx+c�ŕ\�����B
typedef struct LevelToParam{
	float a;
	float b;
	float c;
	LevelToParam(){
		a = 0;
		b = 0;
		c = 0;
	}
} LEVELTOPARAM;

// ���x���A�b�v�{�[�i�X��1���x��������̒l��ێ�����\���́B
typedef struct LevelUpBonus{
	int		growth[DOLL_PARAM_MAX];		// �������x���̏㏸�l�B
	WORD	skillID;					// �o����X�L���B0�ȊO�̒l���Ɗo����B
	LevelUpBonus(){
		for(int n=0; n<DOLL_PARAM_MAX; n++){
			growth[n] = 0;
		}
		skillID = 0;
	}
} LEVELUPBONUS;

// �e�l�`�̃p�����[�^�B
class Data_DollParam_Each{
protected:
	// �l�`�̃^�C�v���B
	TCHAR			typeName[DOLL_TYPENAME_BYTES];
	// �f�[�^�B
	// ���x�����p�����[�^�Ɋ��Z���鎮�B
	LEVELTOPARAM	LvToP[DOLL_PARAM_MAX];
	LEVELUPBONUS	LvBonus[DOLL_LEVEL_MAX];

public:
	// �R���X�g���N�^
	Data_DollParam_Each();
	// �f�[�^�x�[�X�t�@�C������f�[�^�̓ǂݍ��݂��s���B
	bool Load(LPTSTR fileName);
	// �������x���A�p�����[�^����w�肷���
	// �p�����[�^�̐��l��Ԃ��B
	int GetParamFromLv(BYTE paramType, int lv);

	// �\���̂ւ̃A�N�Z�T
	LEVELTOPARAM	GetLvToP(int paramType){ return LvToP[paramType]; }; 
	LEVELUPBONUS	GetLvBonus(int lv){ return LvBonus[lv]; }; 
	void			SetLvToP(int paramType, LEVELTOPARAM p){ LvToP[paramType] = p; };
	void			SetLvBonus(int lv, LEVELUPBONUS p){ LvBonus[lv] = p; };
	// ���O��Ԃ��B
	void GetName(LPTSTR buf, int bufSize);
	// ���O���Z�b�g����B
	void SetName(LPTSTR name);

};

class Data_DollParam{
protected:
	Data_DollParam_Each		dollList[DOLL_TYPE_MAX];		//
public:
	// �R���X�g���N�^
	Data_DollParam();

	// �l�`�̖��O��Ԃ��B
	void GetTypeName(BYTE index, LPTSTR buf, int bufSize){
		dollList[index-1].GetName(buf, bufSize); };
	
	// �l�`�^�C�vID�A�������x���A�p�����[�^����w�肷���
	// �p�����[�^�̐��l��Ԃ��B
	int GetParamFromLv(BYTE dollType, BYTE paramType, int lv);


	// ���[�h
	// �S�l�`�̃f�[�^�����[�h����B
	bool Load();

	// csv�t�@�C������ǂݍ��ޏꍇ
	bool LoadDataFromCsv();

	// dat�t�@�C������ǂݍ��ޏꍇ
	bool LoadDataFromDat();

	// Csv�f�[�^���Í������ăt�@�C���ɏ����o���B
	bool EncodeCsv();

};

#endif // DATA_DOLLPARAM_H