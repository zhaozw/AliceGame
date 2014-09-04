// Func_AliceFile.cpp
#include "Func_AliceFile.h"

// ���̃Q�[���̃Z�[�u�f�[�^�Ɋւ����舵�����L�q����t�@�C���B
#include <stdio.h>
#include <fstream>
#include <vector>

#include "MyFiles.h"
#include "Game_FileHeader.h"
#include "Record_AliceInfo.h"
#include "Game_DollList.h"
#include "TempData.h"
#include "Common_Macro.h"

// �Q�[���f�[�^��ۑ����邽�߂̃O���[�o���ϐ��Q
extern Record_AliceInfo		r_aliceInfo;
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
	r_aliceInfo.GetCntTime();

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
	fileHeader.data.alice_mp = r_aliceInfo.data.mp;
	fileHeader.data.savedYMD = r_aliceInfo.data.savedYMD;
	fileHeader.data.savedHMS = r_aliceInfo.data.savedHMS;
	fileHeader.data.playTime = r_aliceInfo.data.playTime;

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
	Record_AliceInfo_Data aliceData = r_aliceInfo.data;
	if(file.AddObjectToFiles(
		(LPVOID)&aliceData, sizeof(Record_AliceInfo_Data),
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
	r_aliceInfo.GetCntTime(true);
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
	if(!r_aliceInfo.LoadFromBytes(pData, fileSize)){
		return false;
	}

	// �l�`���X�g�̓ǂݍ���

	return true;
}

bool NewGame(){
	// �O���[�o���ϐ���S�ď���������K�v������
	r_aliceInfo = Record_AliceInfo();
	// ���݂̎��ԏ����X�V����
	r_aliceInfo.GetCntTime(true);
	// �O���炠�郊�X�g��������A�V�������X�g���쐬����
	g_dollList.Release();
	g_dollList = Game_DollList();
	g_temp.Reset();
	GenerateInitialDoll();
	// r_aliceInfo.data.mp = 0;
	return true;
}

void GenerateInitialDoll(){
	// g_dollList.list.In
}

// 2014�ăR�~�̑̌��łɊւ���N���X�B
AliceFile_140816::AliceFile_140816(){
	Reset();
}

void AliceFile_140816::Reset(){
	data.firstHint = false;
	for(int n=0; n<ALICEFILE_140816_TUTORIAL; n++){
		data.tutorialBattle[n] = 0;
	}
	data.tutorialHint = false;
	for(int n=0; n<10; n++){
		data.forFuture[n] = 0;
	}
}

// �̌��ł̃f�[�^��ۑ�����B
bool AliceFile_140816::Save(){
	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(ALICEFILE_140816_FILENAME,
		std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	// ���݂̃f�[�^�̃R�s�[�����A�Í���
	ALICEFILE_140816_DATA copiedData;
	copiedData = data;
	int dataSize = sizeof(ALICEFILE_140816_DATA)*sizeof(char);
	void* pData = static_cast<void*>(&copiedData);
	BYTE* byte_casted_data = static_cast<BYTE*>(pData);		// ��̍s�ƍ��킹�Ė������o�C�g��ɕϊ�

	// �f�[�^�ɑ΂��Ē��ڔr���I�_���a���s��
	int pos;
	TCHAR code[ALICEFILE_140816_XORCODE_LENGTH+1];
	strcpy_s(code, ALICEFILE_140816_XORCODE_LENGTH+1, ALICEFILE_140816_XORCODE);
	TCHAR code2[ALICEFILE_140816_XORCODE2_LENGTH+1];
	strcpy_s(code2, ALICEFILE_140816_XORCODE2_LENGTH+1, ALICEFILE_140816_XORCODE2);
	for(int i=0; i<dataSize; i++){
		pos = ((i+3)%strlen(ALICEFILE_140816_XORCODE)); // ������Ƃ��炵���ʒu�ňÍ���
		byte_casted_data[i] = byte_casted_data[i]^code[pos];
		pos = ((i+7)%strlen(ALICEFILE_140816_XORCODE2)); 
		byte_casted_data[i] = byte_casted_data[i]^code2[pos];
	}

	// ���ۂ̏����o��
	fout.write((char*)&copiedData, dataSize);

	// �����o���I��
	fout.close();
	return true;
}

// �̌��ł̃f�[�^�����[�h����B
bool AliceFile_140816::Load(){
	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(ALICEFILE_140816_FILENAME,
		std::ios::in|std::ios::binary);
	if(!fin){
		_RPTF0(_CRT_WARN, "�ǂݍ��ݗp�t�@�C�����J���܂���ł����B\n");
		return false;
	}

	// �t�@�C��������e��ǂݍ���
	ALICEFILE_140816_DATA loadedData;
	int dataSize = sizeof(ALICEFILE_140816_DATA)*sizeof(char);
	fin.read((char*)&loadedData, dataSize);
	if(!fin){
		_RPTF0(_CRT_WARN, "�t�@�C���̓��e���ǂݍ��߂܂���ł����B\n");
		return false;
	}

	// ����
	void* pData = static_cast<void*>(&loadedData);
	BYTE* byte_casted_data = static_cast<BYTE*>(pData);		// ��̍s�ƍ��킹�Ė������o�C�g��ɕϊ�
	// �f�[�^�ɑ΂��Ē��ڔr���I�_���a���s��
	int pos;
	TCHAR code[ALICEFILE_140816_XORCODE_LENGTH+1];
	strcpy_s(code, ALICEFILE_140816_XORCODE_LENGTH+1, ALICEFILE_140816_XORCODE);
	TCHAR code2[ALICEFILE_140816_XORCODE2_LENGTH+1];
	strcpy_s(code2, ALICEFILE_140816_XORCODE2_LENGTH+1, ALICEFILE_140816_XORCODE2);
	for(int i=0; i<dataSize; i++){
		pos = ((i+3)%strlen(ALICEFILE_140816_XORCODE)); // ������Ƃ��炵���ʒu�ňÍ���
		byte_casted_data[i] = byte_casted_data[i]^code[pos];
		pos = ((i+7)%strlen(ALICEFILE_140816_XORCODE2)); 
		byte_casted_data[i] = byte_casted_data[i]^code2[pos];
	}

	// ������̃f�[�^���R�s�[����
	data = loadedData;

	// �ǂݍ��ݏI��
	fin.close();
	return true;
}
