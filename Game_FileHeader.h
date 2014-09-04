#ifndef GAME_FILEHEADER_H
#define GAME_FILEHEADER_H

#include <Windows.h>
#include "Record_AliceInfo.h"

struct Game_FileHeader_Data{
	int		playTime;		// �v���C����(�b)
	WORD	alice_mp;		// �A���X�̖���
	DWORD	savedYMD;		// �Z�[�u�����N�E���E��
	DWORD	savedHMS;		// �Z�[�u�������ԁE���E�b

	Game_FileHeader_Data(){
		playTime = 0;
		alice_mp = MAX_MP;
		savedYMD = 0;
		savedHMS = 0;
	}
};

// �t�@�C���̃��[�h���ȂǂɎg�p����t�@�C���̃w�b�_�f�[�^�������N���X�B
// �Z�[�u�t�@�C���̐擪�ɕۑ�����AScene_File�ȂǂŌĂяo�����B
class Game_FileHeader{
public:
	Game_FileHeader_Data		data;
public:
	// �R���X�g���N�^
	Game_FileHeader();
	// �o�C�g�񂩂�f�[�^�ɓ��e���R�s�[����
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);
};

#endif // GAME_FILEHEADER_H