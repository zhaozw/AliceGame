#ifndef DATA_BATTLESTATE_H
#define DATA_BATTLESTATE_H

#include <Windows.h>
#include "VectorList.h"

#define STATENAME_LENGTH	32

//==================================================
// �e�X�e�[�g�B

// �퓬�s�\�ɂȂ������ɕt�������X�e�[�g�B
#define STATE_DEATH				1

// �h���I���������ɕt�������X�e�[�g�B
// �󂯂�_���[�W��0.5�{�̕␳��������B
#define STATE_GUARD				2

// �f�����␳���s���ۂɕt�������X�e�[�g�B
// �f�������莞�Ƀp�����[�^�~1000�̑f�����𑝉�������B
#define STATE_SUBSPD_UP			3

// �f�����̃}�C�i�X�␳���s���ۂɕt�������X�e�[�g�B
// �f�������莞�Ƀp�����[�^�~1000�̑f����������������B
#define STATE_SUBSPD_DOWN		4

// �ꎞ�I�ɑ����𖳑����ɕς���X�e�[�g�B
// �p�����[�^�F�����܂ł̃^�[����
// �ȉ��A�����ύX�n�X�e�[�g�݂͌��ɗ����s�B
// �ʂ̂��̂�������ꂽ���_�Ō��̃X�e�[�g�͉��������B
#define STATE_TMPATTR_NONE		5

// �ꎞ�I�ɑ����𑾗z�����ɕς���X�e�[�g�B
// �p�����[�^�F�����܂ł̃^�[����
#define STATE_TMPATTR_SUN		6

// �ꎞ�I�ɑ������������ɕς���X�e�[�g�B
// �p�����[�^�F�����܂ł̃^�[����
#define STATE_TMPATTR_MOON		7

// �ꎞ�I�ɑ����𐯑����ɕς���X�e�[�g�B
// �p�����[�^�F�����܂ł̃^�[����
#define STATE_TMPATTR_STAR		8

//=============================================
// �t���O�֘A

// �^�[���̏I���ɉ�������
// ��̓I�ɂ́AGame_BattleUnit����UpdateStateTurn������������B
#define STATE_FLAG_REMOVE_AT_TURNEND		0x00000001
// �s���s�\�ɂȂ�
// ��̓I�ɂ́A�^�[���̍ŏ��ɃR�}���h���o�Ȃ�
#define STATE_FLAG_CANNOT_ACT				0x00000002
// �d�˂����\��
// ��̓I�ɂ́A���ɓ����X�e�[�g�ɂȂ��Ă���Ƃ��A
// ���̃t���O���ݒ肳��Ă��Ȃ��ƁA���łɃX�e�[�g�ɂȂ��Ă���
// �����ƃR�����g���o�邪�A
// �t���O��ݒ肵�Ă�����Game_BattleUnit�̃X�e�[�g�̃��x����1�オ��
#define STATE_FLAG_CAN_MULTIPLE				0x00000004
// ���̃X�e�[�g���t������Ă��郆�j�b�g��
// �U���ΏۂɂȂ�Ȃ�
// ��̓I�ɂ́A�l�`�̃R�}���h�I�����ɑI���o�����A
// �܂��A�G�̃^�[�Q�b�g�I���ɂ����đΏۂ���O���B
#define STATE_FLAG_CANNOT_TARGET			0x00000008

// �X�e�[�g���\���N���X�B
// Data_BattleState�N���X��VectorList�Ƃ��ĕێ������B
class Data_BattleState_Each{
private:
	// �X�e�[�gID�B
	WORD		refID;		
	// �X�e�[�g��
	// ���ۂɎg�����ǂ����͕s���B
	// csv�t�@�C���̉����̂��߂ł�����B
	TCHAR		stateName[STATENAME_LENGTH];
	// ��������(����ɍ��킹�ĕ��בւ����s��)
	// �ő�30�A�ŏ�1�B
	WORD		calcOrder;
	// �`��D��x(�D��x�̍������̂���A�C�R����\������B)
	// �`��D��x��0�̂��̂̓A�C�R����`�悵�Ȃ��B
	// �ő�10�A�ŏ�0�B
	WORD		drawOrder;
	// �A�C�R����`�悷��X�e�[�g�̏ꍇ�A
	// Image�N���X�̃A�C�R���̔z�񂩂�摜��\������B
	// ���̕\���摜�̃C���f�b�N�X�B
	WORD		iconIndex;
	// �t���O�B
	// ���e�͖���B
	DWORD		flags;
public:
	// �R���X�g���N�^
	Data_BattleState_Each();
	void Refresh();
	// �A�N�Z�T
	void		SetStateName(LPTSTR name, int size);
	void		GetStateName(LPTSTR buf, int bufSize);
	void		SetRefID(WORD id){ refID = id; };
	WORD		GetRefID(){ return refID; };
	void		SetCalcOrder(WORD _order){ calcOrder = _order; };
	WORD		GetCalcOrder(){ return calcOrder; };
	void		SetDrawOrder(WORD _order){ drawOrder = _order; };
	WORD		GetDrawOrder(){ return drawOrder; };
	void		SetIconIndex(WORD _icon){ iconIndex = _icon; };
	WORD		GetIconIndex(){ return iconIndex; };
	void		SetFlags(DWORD flag){ flags |= flag; };
	void		ResetFlags(DWORD flag){ flags &= !flag; };
	DWORD		GetFlags(){ return flags; };
};

// �G�O���[�v�̃f�[�^��ێ�����N���X�B
// �O���[�o���ϐ�d_enemyGroup����Q�Ƃ����B
class Data_BattleState{
private:
	// �G�O���[�v�̔z��
	VectorList<Data_BattleState_Each>		stateList;

public:
	// �R���X�g���N�^
	Data_BattleState();
	// ���[�h
	bool Load();
	bool LoadDataFromCsv();

	// �X�e�[�g�̔z��������[�X����B
	void ReleaseList(){ stateList.Release(); };


	// �X�e�[�g�ւ̃|�C���^���擾����B
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_BattleState_Each* GetBattleState(WORD _refID);

	// �w�肵��ID�̃X�e�[�g���w�肵���t���O�������Ă��邩�ǂ�����Ԃ��B
	bool CheckFlagOfState(WORD _refID, DWORD flag);

	// �傫����Ԃ��B
	int GetSize(){ return stateList.GetSize(); };
};

#endif // DATA_BATTLESTATE_H