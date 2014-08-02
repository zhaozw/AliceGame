#ifndef DATA_SKILLTEXT_H
#define DATA_SKILLTEXT_H

#include <Windows.h>
#include <tchar.h>
#include "Game_BattleUnit.h"
#include "Static_Skill.h"

// ���b�Z�[�W�̕\���^�C�v
#define SKILLMESSAGE_TYPE_NONE	0		// �����\�����Ȃ�
#define SKILLMESSAGE_TYPE_CONST	1		// �X�e�[�g�ɂȂ郆�j�b�g�̖��O���g��Ȃ�
#define SKILLMESSAGE_TYPE_UNIT	2		// ���j�b�g�̖��O���g��

// �X�L���ɔ������b�Z�[�W�̃o�C�g���B
#define SKILLMESSAGE_BYTES		48

// �X�L���̐�����ʂŏo�镶�͂̃o�C�g���B
#define SKILLACC_BYTES			64			

// ��̃��b�Z�[�W�̃f�[�^�\��
// ���b�Z�[�W���̂��̂ƁA�\���^�C�v��ێ�����B
class Data_SkillMessage_Each{
private:
	BYTE		type;
	TCHAR		message[SKILLMESSAGE_BYTES];
public:
	// �R���X�g���N�^
	Data_SkillMessage_Each(){
		type = SKILLMESSAGE_TYPE_NONE;
		strcpy_s(message, SKILLMESSAGE_BYTES-1, _T(""));
	}
	// �l���Z�b�g����
	void SetSkillMessage(BYTE type, LPTSTR str, int strLen=-1);
	// �f�[�^��ǂݍ���
	bool GetSkillMessage(LPTSTR buf, Game_BattleUnit* pUnit);
};

// ��̃X�L���̃f�[�^�\��
// �X�L�����A�^�[�Q�b�g�A����MP�Ȃǂ�ێ�����\���́B
class Data_SkillInfo_Each{
protected:
	// �X�L�����B
	TCHAR		skillName[MAX_SKILL_BYTES];
	// �X�L���̐����B
	TCHAR		account[SKILLACC_BYTES];
	// �X�L���g�p���̃��b�Z�[�W�B
	Data_SkillMessage_Each		assertMessage;
	// �X�L���ŏ���閂�́B
	int			costMP;
	// �X�L���̑ΏہB
	BYTE		targetType;
public:
	// �R���X�g���N�^
	Data_SkillInfo_Each();

	// �f�[�^���Z�b�g����B
	void SetData(
		LPTSTR _skillName,
		LPTSTR _account,
		LPTSTR _assertMsg, BYTE _assertMsgType,
		int _costMP, BYTE _targetType);

	// �A�N�Z�T
	void	GetSkillName(LPTSTR buf);
	void	GetSkillAccount(LPTSTR buf);
	void	GetAssertMessage(LPTSTR buf, Game_BattleUnit* pUnit){
		assertMessage.GetSkillMessage(buf, pUnit); };
	int		GetCostMP(){ return costMP; };
	BYTE	GetTargetType(){ return targetType; };
};

//================================================
// �X�L���Ɋւ���f�[�^�x�[�X�B
// �X�L�����A�y�сA�X�L���̎g�p���Ȃǂɗ���郁�b�Z�[�W���L�^����B
// �����_�ł̓t�@�C������̓ǂݍ��݂ł͂Ȃ��x�^�ł��ł���B

class Data_SkillInfo{
protected:
	Data_SkillInfo_Each			data[MAX_SKILL];
	/*
	// �X�L�����B
	TCHAR						skillName[MAX_SKILL][MAX_SKILL_BYTES];
	// �X�L���̑ΏہB
	BYTE						targetType[MAX_SKILL];
	// �X�L���ŏ���閂�́B
	int							costMP[MAX_SKILL];

	// �X�L�����g�p����ۂɗ���郁�b�Z�[�W�B
	// �X�L���̐��������݂���B
	Data_SkillMessage_Each		assertMessages[MAX_SKILL];

	// �X�L���̐����B
	// �X�L���̐��������݂���B
	TCHAR						account[MAX_SKILL][SKILLACC_BYTES];
	*/

	// �g�p���ȊO�ɁA�X�L���Ɋ֘A���ė���郁�b�Z�[�W�B
	// �X�L���̐��������݂���킯�ł͂Ȃ��B
	Data_SkillMessage_Each		subMessages[MAX_SKILL_SUBMESSAGE];

public:

	// �R���X�g���N�^
	Data_SkillInfo();

	// ���e�����[�h����B
	// �i���ۂɂ̓x�^�ł��j
	bool Load();

	// �x�^�ł������B
	bool SetSkillData();

	// �X�L�������擾����B
	bool GetSkillName(LPTSTR buf, WORD skillID);

	// �X�L���̐������擾����B
	bool GetSkillAccount(LPTSTR buf, WORD skillID);

	// �^�[�Q�b�g�̃^�C�v���擾����B
	BYTE GetTargetType(WORD skillID);

	// ����MP���擾����B
	int GetCostMP(WORD skillID);

	// ���b�Z�[�W���擾����
	bool GetAssertMessage(LPTSTR buf, WORD skillID, Game_BattleUnit* pUnit);

	// �T�u���b�Z�[�W���擾����
	bool GetSubMessage(LPTSTR buf, WORD refID, Game_BattleUnit* pUnit);
};

#endif // DATA_SKILLMESSAGE_H