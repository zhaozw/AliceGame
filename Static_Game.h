#ifndef STATIC_GAME_H
#define STATIC_GAME_H

//===================================================
// �Q�[���S�̂Ɋւ���萔���`����B

// �Q�[���̃^�C�g��
#define WND_TITLE "�Q�[���t�H�[�}�b�g"

// �x�[�X�ƂȂ�E�B���h�E�̕�
// (�`�悷�鎞�̊�ł���A���ۂ̉�ʕ��Ƃ͈قȂ�ꍇ������)
#define WND_WIDTH	800
#define WND_HEIGHT	600

// ���݂���V�[���̗���B
#define SCENE_NONE			0		// �_�~�[�V�[���B
#define SCENE_ERROR			-1		// �����G���[�������������ɑ������l�B
#define SCENE_END			-2		// �Q�[�����I�����鎞�ɑ������l�B
#define SCENE_SAMPLE		1		// �T���v���V�[���B�폜���Ă��悢�B
#define SCENE_TITLE			2		// �^�C�g����ʁB
#define SCENE_FILE			3		// �t�@�C���̃Z�[�u�E���[�h��ʁB
#define SCENE_CAMP			4		// �L�����v��ʁB
#define SCENE_DOLLCREATE	5		// �L�����v��ʁB
#define SCENE_DOLLBIRTH		6		// �L�����v��ʁB
#define SCENE_BATTLE		7		// �퓬��ʁB
#define SCENE_TESTBATTLE	8		// �e�X�g�o�g���I���B

// �{�^���̖��̗̂���B
// ���Q�[���ɍ��킹�Ċo���₷���悤�ɕς���B
#define BTN_CHOOSE		0	// ����{�^��
#define BTN_CANCEL		1	// �L�����Z���{�^��
#define BTN_SHOWINFO	2	// ���E�B���h�E�̕\���E��\���؂�ւ��{�^��
#define BTN_SCREENSHOT	3	// �X�N���[���V���b�g���B��{�^��
#define BTN_D 3		// �L�����`�F���W�{�^���E�X�L�b�v�{�^��
#define BTN_E 4		// �ꎞ��~�{�^��

//===================================================
// �Q�[���Ŏg�p����@�\�ɂ��ċL�q����萔�B
// �g��Ȃ��ꍇ�̓R�����g�A�E�g����B

// �t�H���g���g�p���邩�ۂ��B
#define MYGAME_USE_FONT

// 3D���g�p���邩�ۂ��B
#define MYGAME_USE_3D

// FPS���߂��g�p���邩�ۂ��B
#define MYGAME_USE_TIMECTRL

// �R���t�B�O(�E�B���h�E�T�C�Y�ASE�ABGM�̒���)���g�p����(�t�@�C���ɏ����o��)��
#define MYGAME_USE_CONFIG		

// �L�[�R���t�B�O���g�p����(�t�@�C���ɏ����o��)��
#define MYGAME_USE_KEYCONFIG

// 2�l�v���C���g�p���邩�ۂ�
// #define MYGAME_USE_2P	

// �L�[�{�[�h���͂ƃQ�[���p�b�h���͂𓯎��ɏ������邩
#define MYGAME_USE_PAD_AND_KEY

// �������`�F�b�N���g�p���邩�ۂ�
#define MYGAME_USE_CHECKMEMORY

// ��{�I�ȃG���[���O���g�p���邩�ۂ��B
#define MYGAME_USE_CRT_LOG

// DX���C�u�����̃��O���g�p���邩�ۂ��B
#define MYGAME_USE_DXLIB_LOG

// �v���I�ȃo�O�ŏI�����鎞�Ƀ��b�Z�[�W�{�b�N�X���o�����ۂ��B
#define MYGAME_USE_WARN_ERROR

// Lua���g�p���邩�ۂ��B
// #define MYGAME_USE_LUA

//===================================================
// �Q�[���̐����ɍ��킹�ĕύX����萔�B

// �Q�[���ɂ���������(�p�x0�̕���)�����߂�B
// �ȉ��̂ǂꂩ��݂̂̃R�����g���O���ƁBFunc_Math�̓��e���ω�����B

// ���������p�x0�Ƃ��A���v��肪�������B�摜�͐i�s���������ɂ���B
// �c�X�N���[��STG�Ȃǂɕ֗��ȍ��W�n�B
// #define MYGAME_DEFDIR_Y_AXIS

// �E�������p�x0�Ƃ��A���v��肪������(��������y���������̂���)�B
// �摜�͐i�s�������E�ɂ���B
// ���X�N���[���A�N�V�����Ȃǂɕ֗��ȍ��W�n�B
#ifndef MYGAME_DEFDIR_Y_AXIS
#define MYGAME_DEFDIR_X_AXIS
#endif // MYGAME_DEFDIR_Y_AXIS

//===================================================
// �Q�Ƃ���O���t�@�C�����Ɋւ���萔���`����B

#define FILE_CONFIG "config.ini"


#define ARCHIVE_EXTENSION "dxa"

//===================================================
// �f�o�b�O�ȂǂɊւ���L�q�B��{�I�ɕύX���Ȃ��B

// double����float�ɕϊ�����ۂ̌x���𖳎�����
#ifndef DISABLE_WARNING
#define DISABLE_WARNING
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#endif // DISABLE_WARNING

// ��񂾂����������[�N�h�~�̃t�@�C����ǂݍ���
#ifndef _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#ifdef MYGAME_USE_LUA
#include <lua.hpp>
#endif // MYGAME_USE_LUA

// ���P�[���̐ݒ�
#include <locale.h>

//===================================================
// �ʏ�͕ύX���Ȃ��萔�Q�B

// �t���[�����[�g
// ��{�I��60�B
#define FPS			60

// �~����
// (MATH_PI�̗�)
#define M_PI 3.14159265

// ��������e�̐��񂳂����B
#define ALIGN_LEFT		0	// ����
#define ALIGN_CENTER	1	// ��������
#define ALIGN_RIGHT		2	// �E��


#endif