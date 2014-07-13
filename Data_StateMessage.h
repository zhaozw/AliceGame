#ifndef DATA_STATEMESSAGE_H
#define DATA_STATEMESSAGE_H

#include <Windows.h>
#include <tchar.h>
#include "Data_BattleState.h"

// ���b�Z�[�W������X�e�[�g�̐�
#define STATEMESSAGE_STATENUM	8

// ���b�Z�[�W�̍ő啶����
#define STATEMESSAGE_BYTES		48

// ���b�Z�[�W�̕\���^�C�v
#define STATEMESSAGE_TYPE_NONE	0		// �����\�����Ȃ�
#define STATEMESSAGE_TYPE_CONST	1		// �X�e�[�g�ɂȂ郆�j�b�g�̖��O���g��Ȃ�
#define STATEMESSAGE_TYPE_UNIT	2		// ���j�b�g�̖��O���g��

// ���b�Z�[�W�̃C���f�b�N�X
#define STATEMESSAGE_INDEX_DOLL_ADDED	0	// �������X�e�[�g�ɂȂ�����
#define STATEMESSAGE_INDEX_ENEMY_ADDED	1	// �G���X�e�[�g�ɂȂ�����
#define STATEMESSAGE_INDEX_REMOVED		2	// �X�e�[�g����񕜂�����
#define STATEMESSAGE_INDEX_KEEP			3	// �X�e�[�g�p���i�^�[���I�����j

#define STATEMESSAGE_INDEX_NUM			4	// �C���f�b�N�X�̍ő吔

class Game_BattleUnit;

// ��̃��b�Z�[�W�̃f�[�^�\��
// ���b�Z�[�W���̂��̂ƁA�\���^�C�v��ێ�����B
typedef struct Data_StateMessage_DataUnit{
	BYTE		type;
	TCHAR		message[STATEMESSAGE_BYTES];
	Data_StateMessage_DataUnit(){
		type = STATEMESSAGE_TYPE_NONE;
		strcpy_s(message, STATEMESSAGE_BYTES-1, _T(""));
	}
}DATA_STATEMESSAGE_DATAUNIT;

// ��̃X�e�[�g�̃��b�Z�[�W�̏W��
class Data_StateMessage_Each{
protected:
	DATA_STATEMESSAGE_DATAUNIT		messages[STATEMESSAGE_INDEX_NUM];
public:
	// �R���X�g���N�^
	Data_StateMessage_Each();

	// �l���Z�b�g����
	void SetMessage(int index, BYTE type, LPTSTR str, int strLen=-1);

	// �l���擾����
	bool GetStateMessage(LPTSTR buf, int index, Game_BattleUnit* pUnit);
};

// �S���̃X�e�[�g���b�Z�[�W
// �O���[�o���ϐ�d_stateMessage����Q�Ƃ����
// �ʏ��VectorList�Ńf�[�^���Ǘ�����N���X�Ƃ͈Ⴂ�A
// ���̃N���X�ɂ����Ă̓f�[�^�̒����͌Œ�B
// ���Ȃ݂ɁA0�Ԗڂ̃C���f�b�N�X�͋�f�[�^�B
class Data_StateMessage{
protected:
	// �f�[�^
	Data_StateMessage_Each		stateMessages[STATEMESSAGE_STATENUM];
public:
	// �R���X�g���N�^
	Data_StateMessage();

	// ���[�h
	bool Load();

	// ���b�Z�[�W�̐ݒ�(�x�^�ł�)
	bool SetStateMessages();

	// ���b�Z�[�W���擾����
	// (�X�e�[�g�Ɋւ�郆�j�b�g��n���Ƃ��̖��O����ꂽ�������Ԃ�)
	// ���e�����݂��Ȃ��ꍇ��false��Ԃ�
	bool GetStateMessage(LPTSTR buf, WORD stateRefID, int index, Game_BattleUnit* pUnit);
};

#endif // DATA_STATEMESSAGE_H