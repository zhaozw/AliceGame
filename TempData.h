#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Game_AliceDoll.h"

// sceneParam�ɓ������p�����[�^�Q
#define TEMP_PARAM_FILE_NEWGAME		0
#define TEMP_PARAM_FILE_SAVEMODE	1
#define TEMP_PARAM_FILE_LOADMODE	2

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
public:
	// �R���X�g���N�^
	TempData();
	// ���e�̃��Z�b�g
	void Reset();
};

#endif // TEMPDATA_H