// Func_AliceFile.cpp
#include "Func_AliceFile.h"

// ���̃Q�[���̃Z�[�u�f�[�^�Ɋւ����舵�����L�q����t�@�C���B
#include <stdio.h>
#include <fstream>
#include <vector>

#include "MyFiles.h"
#include "Game_FileHeader.h"
#include "Game_AliceInfo.h"
#include "Game_DollList.h"
#include "TempData.h"
#include "Common_Macro.h"

// �Q�[���f�[�^��ۑ����邽�߂̃O���[�o���ϐ��Q
extern Game_AliceInfo		g_aliceInfo;
extern TempData				g_temp;
extern Game_DollList		g_dollList;

// �C���f�b�N�X���w�肷��ƃt�@�C������Ԃ��B
bool GetSaveGameFileName(LPTSTR str, int strLength, BYTE index){
	if(index<=0 || index>MAX_SAVEFILE) return false;
	if(strLength != SIZE_SAVEFILENAME) return false;
	TCHAR fileName[SIZE_SAVEFILENAME];
	wsprintf(fileName, "dat\\savefile%02d.dat", index);
	strcpy_s(str, SIZE_SAVEFILENAME-1, fileName);
	return true;
}

// �t�@�C�������݂��邩�ǂ������擾����
bool GetGameFileIsExist(BYTE index){
	TCHAR fileName[SIZE_SAVEFILENAME];
	std::basic_ifstream<TCHAR> fin;
	// �t�@�C�������擾
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	fin.open(fileName, std::ios::in|std::ios::binary); // ifstream��TCHAR�Ŏg�p����
	if(!fin){
		// �t�@�C�������݂��Ȃ�
		return false;
	}
	return true;
}

// Game_FileHeader�N���X�̃|�C���^��n���ƁA
// ���̓��e�Ɏw�肵���C���f�b�N�X�̃t�@�C���̃t�@�C���w�b�_��ǂݍ��ށB
bool GetGameFileHeader(Game_FileHeader* pHeader, BYTE index){
	TCHAR fileName[SIZE_SAVEFILENAME];
	// �t�@�C�������擾����
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// �t�@�C�������݂��邩�ǂ������肷��
	if(!GetGameFileIsExist(index)){
		return false;
	}
	// MyFiles�N���X
	MyFiles			file;
	// �t�@�C�����J��
	if(!file.LoadFilesFromDat(fileName)){
		return false;
	}
	// ������
	file.EncodeFileXOR(
		SAVEFILE_INDEX_FILEHEADER, 
		_T(SAVEFILE_CODE_FILEHEADER), (WORD)strlen(_T(SAVEFILE_CODE_FILEHEADER)));
	// �|�C���^�̎擾
	LPVOID pData = file.GetFilePointerByIndex(SAVEFILE_INDEX_FILEHEADER);
	// �t�@�C���T�C�Y�����������ǂ����̊m�F
	DWORD fileSize = file.GetFileSize(SAVEFILE_INDEX_FILEHEADER);
	// �f�[�^�̓ǂݍ���
	if(!pHeader->LoadFromBytes(pData, fileSize)){
		return false;
	}
	return true;
}

// �Q�[���f�[�^��ۑ�����
bool SaveGame(BYTE index){
	// ���݂̎��ԏ����X�V����
	g_aliceInfo.GetCntTime();

	// �t�@�C�����̎擾
	TCHAR fileName[SIZE_SAVEFILENAME];
	// �t�@�C�������擾����
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// MyFiles�N���X
	MyFiles			file;

	// �Q�[���ۑ��p�̃w�b�_���쐬����
	Game_FileHeader fileHeader;
	fileHeader.data.alice_mp = g_aliceInfo.data.mp;
	fileHeader.data.savedYMD = g_aliceInfo.data.savedYMD;
	fileHeader.data.savedHMS = g_aliceInfo.data.savedHMS;
	fileHeader.data.playTime = g_aliceInfo.data.playTime;

	// �t�@�C���w�b�_�̕ۑ�
	if(file.AddObjectToFiles(
		(LPVOID)&fileHeader.data, sizeof(Game_FileHeader_Data),
		_T("header"), SAVEFILE_INDEX_FILEHEADER) == INDEX_ERROR){
			file.ReleaseAll();
			return false;
	}
	file.EncodeFileXOR(
		SAVEFILE_INDEX_FILEHEADER, 
		_T(SAVEFILE_CODE_FILEHEADER), (WORD)strlen(_T(SAVEFILE_CODE_FILEHEADER)));

	// �A���X�̏��̕ۑ�
	Game_AliceInfo_Data aliceData = g_aliceInfo.data;
	if(file.AddObjectToFiles(
		(LPVOID)&aliceData, sizeof(Game_AliceInfo_Data),
		_T("aliceinfo"), SAVEFILE_INDEX_ALICEINFO) == INDEX_ERROR){
			file.ReleaseAll();
			return false;
	}
	file.EncodeFileXOR(
		SAVEFILE_INDEX_ALICEINFO, 
		_T(SAVEFILE_CODE_ALICEINFO), (WORD)strlen(_T(SAVEFILE_CODE_ALICEINFO)));

	// �l�`���X�g�̕ۑ�

	// �t�@�C���������o��
	DWORD bytesOfFile = 0;
	if(!file.SaveFilesToRawFile(fileName, true, &bytesOfFile)){
		return false;
	}
	if(bytesOfFile <= 0) return false;

	if(!file.ReleaseAll()){
		return false;
	}
	return true;
}

// �Q�[���f�[�^��ǂݍ���
bool LoadGame(BYTE index){
	// ���݂̎��ԏ����X�V����
	g_aliceInfo.GetCntTime(true);
	// �t�@�C�����̎擾
	TCHAR fileName[SIZE_SAVEFILENAME];
	// �t�@�C���̃|�C���^���󂯎��
	LPVOID pData = NULL;
	// �t�@�C���T�C�Y
	DWORD fileSize;
	// �t�@�C�������擾����
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// �t�@�C�������݂��邩�ǂ������肷��
	if(!GetGameFileIsExist(index)){
		return false;
	}

	// MyFiles�N���X
	MyFiles			file;

	// �t�@�C�����J��
	if(!file.LoadFilesFromDat(fileName)){
		return false;
	}

	// �w�b�_�t�@�C���͓ǂݍ��ޕK�v���Ȃ�

	// �A���X�̏��t�@�C����ǂݍ���
	// ������
	file.EncodeFileXOR(
		SAVEFILE_INDEX_ALICEINFO, 
		_T(SAVEFILE_CODE_ALICEINFO), (WORD)strlen(_T(SAVEFILE_CODE_ALICEINFO)));
	// �|�C���^�̎擾
	pData = file.GetFilePointerByIndex(SAVEFILE_INDEX_ALICEINFO);
	// �t�@�C���T�C�Y�����������ǂ����̊m�F
	fileSize = file.GetFileSize(SAVEFILE_INDEX_ALICEINFO);
	if(!g_aliceInfo.LoadFromBytes(pData, fileSize)){
		return false;
	}

	// �l�`���X�g�̓ǂݍ���

	return true;
}

bool NewGame(){
	// �O���[�o���ϐ���S�ď���������K�v������
	g_aliceInfo = Game_AliceInfo();
	// ���݂̎��ԏ����X�V����
	g_aliceInfo.GetCntTime(true);
	// �O���炠�郊�X�g��������A�V�������X�g���쐬����
	g_dollList.Release();
	g_dollList = Game_DollList();
	g_temp.Reset();
	GenerateInitialDoll();
	// g_aliceInfo.data.mp = 0;
	return true;
}

void GenerateInitialDoll(){
	// g_dollList.list.In
}