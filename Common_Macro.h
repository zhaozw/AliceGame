#ifndef COMMON_MACRO_H
#define COMMON_MACRO_H

#include "Static_Game.h"

// �������̉��
#define SAFE_DELETE(p)  { if(p) { delete (p); (p)=0; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] (p); (p)=0; } }

// ���������[�N�̌��o
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC) && !defined(NEW)
#define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif

// �G���[��������
#define ERROR_EXIT(){ int line = __LINE__; const char *file = __FILE__;\
	char msg[_MAX_FNAME + _MAX_EXT + 256];\
	char drive[_MAX_DRIVE];\
	char dir[_MAX_DIR];\
	char fname[_MAX_FNAME];\
	char ext[_MAX_EXT];\
	_splitpath(file, drive, dir, fname, ext);\
	sprintf(msg, "���炩�̃G���[�������������߃A�v���P�[�V�������I�����܂�\r\n"\
	"�t�@�C�� : %s%s\r\n"\
	"�s�ԍ� : %d", fname, ext, line);\
	MessageBox(NULL, msg, "Error", MB_OK|MB_ICONEXCLAMATION);\
	PostQuitMessage(1);\
}

#endif
