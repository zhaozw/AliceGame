// GRecord_Others.h

#pragma once

#include <Windows.h>
#include "Static_Game.h"

#define FIRST_DOLL_ID			100

//==========================================
// GRecord_Others�N���X
// 
// �Q�[���S�̂ŋ��L����f�[�^�̂����A
// �ǂ̃N���X�ɂ������Ȃ��f�[�^��ێ�����B

//==========================================
// Record_Global_Others_Data
// �ۑ�����f�[�^�̍\���́B

typedef struct GRecord_Others_Data{
	// �A���X��ID�B�����y�сA�R���s���[�^�̖��O�Ō��܂�B
	// ���̃v���C���[�Ɛl�`�������������̔F�؂Ȃǂɗp����B
	// (����������������킯�ł͂Ȃ�)
	// ���̒l�ƈقȂ�aliceID�l���f�[�^�Ƃ��Ď��l�`��
	// �悻�̃A���X�ƌ��������l�`�ƌ��Ȃ����B
	// ���_��͑��̃A���X��ID����邱�Ƃ��l�����邪�A
	// �����܂ł̓T�|�[�g���Ȃ��B
	DWORD		aliceID;

	// �l�`���V���A���i���o�[�ŊǗ����邽�߂�ID�B
	// �l�`����������邲�Ƃɂ��̒l�����蓖�Ă��A���̌�1������B
	DWORD		nextDollID;
	
	// �͂��N���A���Ă��邩�ۂ��B
	// ���ۂɂ͗v�f�̔ԍ���1�����B
	// ��Ƃ��āA1�͂��N���A�����ꍇ�͗v�f0�Ԃ̒l��true�ɂȂ�B
	bool isClearedChapter[MAX_CHAPTER+1];

	GRecord_Others_Data(){
		for(int n=0; n<MAX_CHAPTER+1; n++){
			isClearedChapter[n] = false;
		}
		aliceID = 0;
	}
} GRECORD_OTHERS_DATA;

class GRecord_Others{
private:
	// �f�[�^
	GRECORD_OTHERS_DATA		data;


public:
	// �R���X�g���N�^
	GRecord_Others();
	
	// �S�ď�����
	bool	Initialize();

	// �͂��N���A����(�v�f�ԍ���1�����)
	void	ClearChapter(int n){ data.isClearedChapter[n-1] = true; };
	
	// �͂��N���A���Ă��邩�̎擾(�v�f�ԍ���1�����)
	bool	GetChapterIsCleared(int n){ return data.isClearedChapter[n-1]; };

	// �A���X��ID�𐶐����A�������B
	void	GenerateAliceID();

	// �A���X��ID���擾����B
	DWORD	GetAliceID(){ return data.aliceID; };

	// �l�`��ID���擾���AID��1���₷�B
	DWORD	GetDollID();
};
