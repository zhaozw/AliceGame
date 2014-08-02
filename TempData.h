#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Game_AliceDoll.h"

// sceneParam�ɓ������p�����[�^�Q
#define TEMP_PARAM_FILE_NEWGAME		0
#define TEMP_PARAM_FILE_SAVEMODE	1
#define TEMP_PARAM_FILE_LOADMODE	2

// battleType�ɓ������p�����[�^�Q
#define TEMP_BTYPE_NORMAL			0	// �ʏ�퓬�B
#define TEMP_BTYPE_EVENT			1	// �C�x���g�퓬�B�ꍇ�ɂ���Ă�
										// �퓬�O��ɉ�b������B
#define TEMP_BTYPE_TUTORIAL			2	// �`���[�g���A���퓬�B
										// ���b�Z�[�W���퓬�O�ɓ���B
#define TEMP_BTYPE_EXTRA			3	// Extra���[�h�̐퓬�B



// �V�[���Ԃŏ������Ƃ肷�鎞�Ɉꎞ�I�ɏ����Ǘ�����̂ɗp����N���X�B
// �O���[�o���ϐ�g_temp�Ƃ��ĎQ�Ƃ����B
// �Z�[�u�f�[�^�ɂ͂��̓��e�͊܂߂Ȃ��B
class TempData{
public:
	// �����V�[���𕡐��̖ړI�Ŏg���񂷏ꍇ�̃t���O�ϐ��B
	int	sceneParam;
	// ���݂̃t�@�C���ԍ��B�I�[�g�Z�[�u�Ȃǂ̍ۂɗp����B���Z�b�g����Ȃ��B
	// �t�@�C���ԍ����̂܂܂��K������B
	BYTE	fileIndex;
	// ���O���̓E�B���h�E�̓��͌��ʂ��󂯎��B
	WORD	enteredName[MAX_ENTERNAME];
	// �l�`�쐬�E�������ɃV�[�����܂����ŏ���ێ�����B
	Game_AliceDoll_Essence	dollData;
	// �G�O���[�vID�B
	// ������w�肵����Ő퓬�V�[���ɑJ�ڂ���B
	WORD	enemyGroup;
	// �퓬�̎�ނ��w�肷��B
	// ���ۂɂǂ�ȓG�Ɛ키����enemyGroup�Ŏw�肷��B
	// �퓬��ID���w�肵�����ꍇ�AbattleID�ɂ��w�肷��B
	BYTE	battleType;
	// �퓬��ID���w�肷��B
	WORD	battleID;
public:
	// �R���X�g���N�^
	TempData();
	// ���e�̃��Z�b�g
	void Reset();
};

#endif // TEMPDATA_H