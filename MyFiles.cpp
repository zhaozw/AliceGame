// MyFiles.cpp

#include "MyFiles.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Common_Macro.h"

MyFiles::MyFiles(){
	fileNum = 0;
}

MyFiles::~MyFiles(){
}

WORD MyFiles::GetEmptyIndex(){
	for(WORD i=0; i<MAX_FILES; i++){
		if(CheckIndexIsEmpty(i)){ // �g�p�������r�b�g��0�̎�
			if(fileInfo[i].pointer){
				_RPTF0(_CRT_WARN, "��̃t�@�C���Ƀ����������蓖�Ă��Ă��܂��B\n");
				return INDEX_ERROR;
			}
			return i;
		}
	}
	_RPTF0(_CRT_WARN, "���p�ł����̃t�@�C��������܂���B\n");
	return INDEX_ERROR;
}

bool MyFiles::CheckIndexIsEmpty(WORD index){
	if(!IndexEnabled(index)) return false;
	return (fileInfo[index].flags & MYFILE_FLAG_USED) == 0x00;
}

LPVOID MyFiles::GetFilePointerByIndex(WORD index){
	if(!IndexEnabled(index)) return NULL;
	if(CheckIndexIsEmpty(index)) return NULL;
	return fileInfo[index].pointer; 
};


WORD MyFiles::GetNamedIndex(LPTSTR fileName, WORD fileNameLength){
	WORD length = fileNameLength;
	if(length == 0) length = _tcslen(fileName);
	bool isOK = true;
	for(int i=0; i<MAX_FILEPATH; i++){
		isOK = true;
		for(int j=0; j<length&&isOK; j++){
			if(fileName[j] != fileInfo[i].name[j]){
				// ���O����v���Ȃ�
				isOK = false;
			}
		}
		if(isOK &&
			fileInfo[i].name[length] == _T('\0')){
				// ���O�����S�Ɉ�v����
				return i;
		}
	}
	return INDEX_ERROR;
}

void MyFiles::SetFileName(int index, LPTSTR fileName){
	for(int i=0; i<MAX_FILEPATH; i++){
		fileInfo[index].name[i] = _T('\0'); // �󕶎��ŏ���������
	}
	_tcscpy_s(fileInfo[index].name, MAX_FILEPATH-1, fileName);	// �t�@�C����

	// �󕶎��Ŗ��߂�I
	for(int i=_tcslen(fileInfo[index].name); i<MAX_FILEPATH; i++){
		fileInfo[index].name[i] = _T('\0'); // �󕶎��ŏ���������
	}
}

void MyFiles::SetFileFlags(int index, WORD flag){
	fileInfo[index].flags |= flag;
}

bool MyFiles::InitializePointer(int index, DWORD size){
	// �t�@�C���̓��e����������ɑS�ēǂݍ���
	fileInfo[index].pointer = VirtualAlloc(NULL,
					size,
					MEM_COMMIT,
					PAGE_READWRITE);
	if(!fileInfo[index].pointer){ // �G���[�̏ꍇ��NULL���������Ă���
		_RPTF0(_CRT_WARN, "VirtualAlloc�ŃG���[���������܂����B\n");
		return false;
	}
	return true;
}

bool MyFiles::LoadFilesFromTxt(LPTSTR fileName){
	if(fileNum > 0){
		ForceReleaseAll();
	}

	// �e�L�X�g�t�@�C���̓ǂݍ��݂ɂ�ifstream�N���X���g�p����
	// �t�@�C�������i�[����
	TCHAR fileNames[MAX_FILES][MAX_PATH]; 

	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName); // ifstream��TCHAR�Ŏg�p����
	if(!fin){
		// �t�@�C�������݂��Ȃ�
		_RPTF1(_CRT_WARN, "�t�@�C�� %s ���J���܂���B\n", fileName);
		return false;
	}

	int count = 0;

	// �t�@�C����ǂݍ���
	while(count < MAX_FILES && !fin.eof()){ // �t�@�C���̍Ō�܂œǂݍ���
		fin.getline(fileNames[count], MAX_FILEPATH-1); // 1�s�ځB�R�����g�B
		if(_tcslen(fileNames[count]) <= 0){ // ��s�͖�������
			continue;
		}
		_RPTF1(_CRT_WARN, "�t�@�C�� %s ��ǉ����X�g�ɉ����܂����B\n",
			fileNames[count]);
		count++;
	}
	fin.close();
	fin.clear();

	// �t�@�C���̓��e��ǂݍ���
	// �e�t�@�C���̓ǂݍ��݂ɂ�

	bool isOK = true;

	for(int i=0; i<count && isOK; i++){
		if(AddFileToFiles(fileNames[i], fileNames[i]) == -1){
			_RPTF1(_CRT_WARN, "�t�@�C�� %s ���ǉ��o���܂���ł����B\n",
				fileNames[i]);
			isOK = false;
		}else{ // ����ȓǂݍ��݂ɐ���
			_RPTF1(_CRT_WARN, "�t�@�C�� %s ��ǉ����܂����B\n",
				fileNames[i]);
		}
	}

	if(!isOK){ // ���炩�̃G���[���o���ꍇ�̓��������������false��Ԃ�
		ForceReleaseAll();
		return false;
	}

	return true;
}

bool MyFiles::LoadFilesFromDat(LPTSTR fileName){
	if(fileNum > 0){
		ForceReleaseAll();
	}

	// �t�@�C�����J��
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in|std::ios::binary); // ifstream��TCHAR�Ŏg�p����
	if(!fin){
		// �t�@�C�������݂��Ȃ�
		_RPTF1(_CRT_WARN, "�t�@�C�� %s ���J���܂���B\n", fileName);
		return false;
	}

	// �f�[�^�Ɋ܂܂��t�@�C������ǂݍ���
	WORD dataFileNum;
	fin.read((char*)&dataFileNum, sizeof(WORD));

	if(dataFileNum > MAX_FILES || dataFileNum == 0){
		_RPTF0(_CRT_WARN, "�t�@�C����������������܂���B\n");
		return false;
	}

	// �w�b�_�[��ǂݍ���
	for(int i=0; i<dataFileNum; i++){
		// �����珇�ɓ���Ă���
		// �����ł̓G���[���������ꍇ������false��Ԃ�

		// �t�@�C����
		fin.read((char*)fileInfo[i].name, sizeof(char)*MAX_FILEPATH);
		// �t�@�C���T�C�Y
		fin.read((char*)&fileInfo[i].size, sizeof(DWORD));

		// �����G���[���������ꍇ�͑����ɔ�����
		if(!fin.eof() && fin.fail()){
			ForceReleaseAll();
			return false;
		}
	}

	// �f�[�^�{�̂�ǂݍ���
	for(int i=0; i<dataFileNum; i++){
		if(!InitializePointer(i, fileInfo[i].size)){
			ForceReleaseAll();
			return false;
		}
		fin.read((char*)fileInfo[i].pointer, (sizeof(char))*fileInfo[i].size);
		// �����G���[���������ꍇ�͑����ɔ�����
		if(!fin.eof() && fin.fail()){
			ForceReleaseAll();
			return false;
		}

		// �t�@�C�����������ǂݍ��܂ꂽ���߃t���O��ǉ�����
		ResetFileFlags(i);
		SetFileFlags(i, MYFILE_FLAG_USED);

		_RPTF2(_CRT_WARN, "�t�@�C�� %s ���C���f�b�N�X %d �ɉ����܂����B\n",
			fileInfo[i].name, i);
		_RPTF1(_CRT_WARN, "�t�@�C���T�C�Y : %d Bytes\n",
			fileInfo[i].size);
	}

	fileNum = dataFileNum;
	_RPTF1(_CRT_WARN, "�t�@�C�� %s �𐳂����ǂݍ��݂܂����B\n", fileName);


	return true;
}

WORD MyFiles::AddObjectToFiles(void *pointer, DWORD size, LPTSTR objName, int i){
	// false�Ȃ̂͊J�����s��Ȃ�����
	return AddBytesToFiles(pointer, size, objName, false, i);
}

WORD MyFiles::AddBytesToFiles(void* pointer, DWORD size, 
	LPTSTR objName, bool needToRelease, int i){
	// �ǉ�����ʒu
	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // ��ł���C���f�b�N�X���擾����
	}else{
		index = i;
		// �g�p����Ă��Ȃ����ǂ����̃`�F�b�N
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}
	if(index == INDEX_ERROR){
		return INDEX_ERROR;
	}

	// �|�C���^����łȂ���
	if(pointer == NULL) return INDEX_ERROR;

	// �|�C���^�����Ƀf�[�^�����蓖�Ă�
	fileInfo[index].pointer = pointer;
	fileInfo[index].size = size;
	SetFileName(index, objName);
	fileInfo[index].flags = 0;
	SetFileFlags(index, MYFILE_FLAG_USED);
	if(!needToRelease){
		SetFileFlags(index, MYFILE_FLAG_COPYED);
	}

	fileNum++;
	return index;
}

WORD MyFiles::AddFileToFiles(LPTSTR fileName, LPTSTR newName, WORD i, bool useNewName){
	std::basic_ifstream<TCHAR> fin;
	DWORD tmpFileSize = 0;

	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // ��ł���C���f�b�N�X���擾����
	}else{
		index = i;
		// �g�p����Ă��Ȃ����ǂ����̃`�F�b�N
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}

	if(index == INDEX_ERROR){
		_RPTF0(_CRT_WARN, "�C���f�b�N�X�̎擾�Ɏ��s���܂����B\n");
		return INDEX_ERROR;
	}else{
		_RPTF2(_CRT_WARN, "�C���f�b�N�X%d��%s��ǉ����܂��B\n", index, fileName);
	}

	// �t�@�C�����J��
	fin.open(fileName, std::ios::in|std::ios::binary);
	if(!fin){
		// �t�@�C�������݂��Ȃ�
		_RPTF1(_CRT_WARN, "�t�@�C�� %s ���J���܂���B\n", fileName);
		return INDEX_ERROR;
	}

	// �t�@�C���̃T�C�Y���擾����
	tmpFileSize = (DWORD)fin.seekg(0, std::ios::end).tellg();
	fin.seekg(0, std::ios::beg); // �|�C���^�ʒu���ŏ��ɖ߂�
	if(tmpFileSize == 0){
		_RPTF0(_CRT_WARN, "�t�@�C���T�C�Y��0�ł��B\n");
		return INDEX_ERROR;
	}

	// �������̊��蓖��
	if(!InitializePointer(index, tmpFileSize)){
		return INDEX_ERROR;
	}

	// �t�@�C���S�̂�ǂݍ���
	fin.read((char*)fileInfo[index].pointer, tmpFileSize);

	// �G���[�`�F�b�N
	if(fin.fail() || fin.bad()){
		_RPTF0(_CRT_WARN, "�t�@�C���̓ǂݍ��ݎ��ɃG���[���������܂����B\n");
		return INDEX_ERROR;
	}

	// �t�@�C���w�b�_�ɏ����i�[����
	SetFileName(index, (useNewName?newName:fileName));
	fileInfo[index].size = tmpFileSize;
	ResetFileFlags(index);
	SetFileFlags(index, MYFILE_FLAG_USED);
	fNeedToRelease = true;	// �S�̂Ƃ��Ă��f�[�^���ǂݍ��܂ꂽ
	fileNum++; // ����ɓǂݍ��܂ꂽ�t�@�C���̒ǉ�

	// �t�@�C���̃��t���b�V��
	fin.close();
	fin.clear();

	return index; // �i�[���ꂽ�t�@�C���ԍ�
}

WORD MyFiles::AddFilePartToFiles(LPTSTR fileName, LPTSTR newName,
		DWORD offset, DWORD length, WORD i, bool useNewName){
	std::basic_ifstream<TCHAR> fin;
	DWORD tmpFileSize = 0;

	int index;

	if(i == INDEX_ANY || i >= MAX_FILES){
		index = GetEmptyIndex(); // ��ł���C���f�b�N�X���擾����
	}else{
		index = i;
		// �g�p����Ă��Ȃ����ǂ����̃`�F�b�N
		if((fileInfo[index].flags & MYFILE_FLAG_USED) != 0){
			index = INDEX_ERROR;
		}
	}

	if(index == INDEX_ERROR){
		_RPTF0(_CRT_WARN, "�C���f�b�N�X�̎擾�Ɏ��s���܂����B\n");
		return INDEX_ERROR;
	}else{
		_RPTF2(_CRT_WARN, "�C���f�b�N�X%d��%s��ǉ����܂��B\n", index, fileName);
	}

	// �t�@�C�����J��
	fin.open(fileName, std::ios::in|std::ios::binary);
	if(!fin){
		// �t�@�C�������݂��Ȃ�
		_RPTF1(_CRT_WARN, "�t�@�C�� %s ���J���܂���B\n", fileName);
		return INDEX_ERROR;
	}

	// �t�@�C���̃T�C�Y���擾����
	DWORD fileLast = (DWORD)fin.seekg(0, std::ios::end).tellg();
	if(fileLast < offset+length){
		_RPTF0(_CRT_WARN, "�K�v�ȃt�@�C���T�C�Y������܂���B\n");
		return INDEX_ERROR;
	}
	
	// �������̊��蓖��
	if(!InitializePointer(index, length)){
		return INDEX_ERROR;
	}

	// �|�C���^�̈ʒu���I�t�Z�b�g�ɍ��킹��
	fin.seekg(offset, std::ios::beg);
	// �t�@�C���̈ꕔ��ǂݍ���
	fin.read((char*)fileInfo[index].pointer, length);

	// �G���[�`�F�b�N
	if(fin.fail() || fin.bad()){
		_RPTF0(_CRT_WARN, "�t�@�C���̓ǂݍ��ݎ��ɃG���[���������܂����B\n");
		return INDEX_ERROR;
	}

	// �t�@�C���w�b�_�ɏ����i�[����
	SetFileName(index, (useNewName?newName:fileName));
	fileInfo[index].size = length;
	ResetFileFlags(index);
	SetFileFlags(index, MYFILE_FLAG_USED);
	fNeedToRelease = true;	// �S�̂Ƃ��Ă��f�[�^���ǂݍ��܂ꂽ
	fileNum++; // ����ɓǂݍ��܂ꂽ�t�@�C���̒ǉ�

	// �t�@�C���̃��t���b�V��
	fin.close();
	fin.clear();

	return index; // �i�[���ꂽ�t�@�C���ԍ�
}

bool MyFiles::SaveFilesToRawFile(LPTSTR fileName, bool hideName, DWORD* sizeInBytes){
	*sizeInBytes = 0;

	// ���ݓǂݍ��܂�Ă���t�@�C�������L�^����
	if(fileNum <= 0){
		*sizeInBytes = 0;
		return true;
	}

	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(fileName, std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C�����J���܂���ł����B\n");
		*sizeInBytes = 0;
		return false;
	}

	// �t�@�C�������L�^����(WORD�^)
	fout.write((char*)&fileNum, sizeof(WORD));
	*sizeInBytes += sizeof(WORD);

	// �e�t�@�C���̃w�b�_���L�^����
	// (�t�@�C�����ƃt�@�C���T�C�Y)
	TCHAR tmpName[MAX_FILEPATH];
	int cntFileNum = 0;
	for(int i=0; i<MAX_FILES && cntFileNum<fileNum; i++){
		// �K�������C���f�b�N�X���ɕ���ł���킯�ł͂Ȃ��̂�
		if((fileInfo[i].flags & MYFILE_FLAG_USED) == 0x00) continue;
		if((fileInfo[i].flags & MYFILE_FLAG_PROTECTED) != 0x00){
			cntFileNum++; // �J�E���^�͑��������邪�����o���Ȃ�
			continue;
		}

		// �t�@�C�����g�p����Ă���ꍇ
		if(!hideName){
			_tcscpy_s(tmpName, sizeof(TCHAR)*(MAX_FILEPATH-1), fileInfo[i].name);
		}else{
			_tcscpy_s(tmpName, sizeof(TCHAR)*(MAX_FILEPATH-1), _T("dummy.dat"));
		}
		// ���ۂ̏����o��
		fout.write((char*)tmpName, sizeof(TCHAR)*MAX_FILEPATH);
		// �t�@�C���T�C�Y�̏����o��
		fout.write((char*)&fileInfo[i].size, sizeof(DWORD));
		*sizeInBytes += (sizeof(TCHAR)*MAX_FILEPATH + sizeof(DWORD));
		_RPTF2(_CRT_WARN, "�t�@�C����A�����܂� : %s, %d bytes\n", 
			tmpName, fileInfo[i].size);
		// �J�E���^�̑���
		cntFileNum++;
	}

	if(cntFileNum < fileNum){ // �����o�����t�@�C���̐����\�z�ƈقȂ�
		_RPTF0(_CRT_WARN, "���p�\�ȃt�@�C�������\�z�ƈقȂ�܂��B\n");
		fout.close();
		*sizeInBytes = 0;
		return false;
	}

	_RPTF0(_CRT_WARN, "�t�@�C���w�b�_�̏����o���𐳂����s���܂����B\n");
	_RPTF1(_CRT_WARN, "���v�T�C�Y : %d bytes\n", 
		*sizeInBytes);

	// ���ۂ̃f�[�^�̏����o��
	cntFileNum = 0;
	for(int i=0; i<MAX_FILES && cntFileNum<fileNum; i++){
		// �K�������C���f�b�N�X���ɕ���ł���킯�ł͂Ȃ��̂�
		if((fileInfo[i].flags & MYFILE_FLAG_USED) == 0x00) continue;
		if((fileInfo[i].flags & MYFILE_FLAG_PROTECTED) != 0x00){
			cntFileNum++; // �J�E���^�͑��������邪�����o���Ȃ�
			continue;
		}

		// �t�@�C�������݂���ꍇ�͏����o��
		fout.write((char*)fileInfo[i].pointer, fileInfo[i].size); 

		// �����o�����o�C�g���̑���
		*sizeInBytes += fileInfo[i].size;

		_RPTF2(_CRT_WARN, "�t�@�C����A�����܂��� : %s, %d bytes\n", 
			fileInfo[i].name, fileInfo[i].size);
		_RPTF1(_CRT_WARN, "���v�T�C�Y : %d bytes\n", 
			*sizeInBytes);

		// �J�E���^�̑���
		cntFileNum++;
	}

	if(cntFileNum < fileNum){ // �����o�����t�@�C���̐����\�z�ƈقȂ�
		_RPTF0(_CRT_WARN, "�\�z���ꂽ�t�@�C�����������o���Ȃ��܂܏I�����܂����B\n");
		fout.close();
		return false;
	}

	// �I���̍��m
	_RPTF1(_CRT_WARN, "�t�@�C�� %s �֏����o���𐳂����I�����܂����B\n", fileName);
	_RPTF1(_CRT_WARN, "���v�T�C�Y : %d bytes\n", *sizeInBytes);

	// �����o���I��
	fout.close();

	return true;
}

bool MyFiles::SaveFileToRawFileByIndex(int index, LPTSTR outName, bool useRawName){
	if(index >= MAX_FILES) return false; // �C���f�b�N�X���������Ȃ�

	// ���ۂɏ����o���t�@�C�����̎擾
	TCHAR realOutName[MAX_FILEPATH];
	if(useRawName){
		_tcscpy_s(realOutName, MAX_FILEPATH-1, fileInfo[index].name);
	}else{
		_tcscpy_s(realOutName, MAX_FILEPATH-1, outName);
	}

	// �C���f�b�N�X�̃f�[�^�������o��

	// �t�@�C�����J��
	std::basic_ofstream<TCHAR> fout;
	fout.open(realOutName, std::ios::out|std::ios::binary|std::ios::trunc);
	if(!fout){
		_RPTF0(_CRT_WARN, "�����o���p�t�@�C���̃I�[�v���Ɏ��s���܂����B\n");
		return false;
	}

	// �t�@�C�����g�p�\���̃`�F�b�N
	if((fileInfo[index].flags & MYFILE_FLAG_USED) == 0){
		_RPTF1(_CRT_WARN, "�C���f�b�N�X%d�̃t�@�C���͎g���Ă��܂���B\n", index);
		return false;
	}

	// �f�[�^�������o��
	fout.write((char*)fileInfo[index].pointer, fileInfo[index].size);
	_RPTF1(_CRT_WARN, "�t�@�C�� %s �𐳂��������o���܂����B\n", realOutName);
	_RPTF1(_CRT_WARN, "�����o�����o�C�g�� : %d Bytes\n", fileInfo[index].size);

	// �t�@�C�������
	fout.close();


	return true;
	
}

bool MyFiles::SaveFileToRawFileByName(LPTSTR searchName, LPTSTR outName, bool useRawName){
	int index = GetNamedIndex(searchName);
	if(index == INDEX_ERROR){
		return false;
	}

	return SaveFileToRawFileByIndex(index, outName, useRawName);
}

bool MyFiles::EncodeFileXOR(WORD index, LPTSTR code, WORD codeLength){
	WORD pos;
	// �t�@�C�����g�p�\���ǂ����̃`�F�b�N
	if(index >= MAX_FILES) return false; // �C���f�b�N�X���������Ȃ�
	if(CheckIndexIsEmpty(index)){
		_RPTF0(_CRT_WARN, "�w�肳�ꂽ�C���f�b�N�X�̃t�@�C���͎g�p����Ă��܂���B\n");
		return false;
	}

	// ������r���I�_���a���g����`�ɕύX����
	BYTE* b = static_cast<BYTE*>(fileInfo[index].pointer);

	// ���ۂ̔r���I�_���a���s��
	for(DWORD i=0; i<fileInfo[index].size; i++){
		pos = ((i+17)%codeLength); // ������Ƃ��炵���ʒu���Í���
		b[i] = b[i]^code[pos];
	}
	return true;
}

bool MyFiles::CompareFiles(WORD index, WORD index2){
	// �t�@�C���T�C�Y�̔�r
	if(index >= MAX_FILES) return false; // �C���f�b�N�X���������Ȃ�
	if(index2 >= MAX_FILES) return false; // �C���f�b�N�X���������Ȃ�
	if(fileInfo[index].size != fileInfo[index2].size) return false;

	// ������r���I�_���a���g����`�ɕύX����
	BYTE* b = static_cast<BYTE*>(fileInfo[index].pointer);
	BYTE* b2 = static_cast<BYTE*>(fileInfo[index2].pointer);

	// ���ۂ̔r���I�_���a���s��
	for(DWORD i=0; i<fileInfo[index].size; i++){
		if(b[i] != b2[i]) return false;
	}

	// �Ō�܂ň�v�����ꍇ��true��Ԃ�
	return true;
}

bool MyFiles::Release(int index){
	if(fNeedToRelease) return ForceRelease(index, true);
	return true;
}

bool MyFiles::ReleaseAll(){
	if(fNeedToRelease) return ForceReleaseAll(true);
	return true;
}

bool MyFiles::ForceRelease(int index, bool checkUsed){
	if(!checkUsed || ((fileInfo[index].flags & MYFILE_FLAG_USED) != 0x00)){
		if((fileInfo[index].flags & MYFILE_FLAG_COPYED) == 0x00){ 
			// �R�s�[���ꂽ���̂ł���ꍇ�͉�����Ȃ�
			VirtualFree(fileInfo[index].pointer, fileInfo[index].size, 
				MEM_DECOMMIT);
			fileInfo[index].flags = 0x00;
			fileInfo[index].pointer = NULL;
			SetFileName(index, _T(""));
			fileInfo[index].size = 0;
			// SAFE_DELETE(fileInfo[index].pointer);
		}
	}
	return true;
}

bool MyFiles::ForceReleaseAll(bool checkUsed){
	for(int i=0; i<MAX_FILES; i++){ // �S�t�@�C���̃f�[�^�����
		ForceRelease(i, checkUsed);
	}
	fileNum = 0;
	return true;
}