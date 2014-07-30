// FlexList.h

#ifndef FLEXLIST_H
#define FLEXLIST_H

#include "Common_Macro.h"
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>


//=============================================
// FlexList�N���X
// �z��𓮓I�ɐ���������A�����ۑ������肷��N���X�B
// 
// �N���X T�̗v��
// 
// static DWORD dataSize
// ���̃N���X�̎��f�[�^�̃T�C�Y��Ԃ��B
// �f�[�^��ۑ�����̂ɕK�v�ȗ̈�̑傫���B
// 
// DWORD GetDataSize();
// �f�[�^�̃T�C�Y��Ԃ��A�N�Z�T�B

template<class T>class FlexList{
private:
	T* list;	// �N���X�̔z��
	DWORD num; // �v�f��
	int index; // ���ݎw���Ă���v�f�̃C���f�b�N�X

public:
	// �R���X�g���N�^
	FlexList();
	FlexList(DWORD num);

	// �f�X�g���N�^
	~FlexList();

	// ���X�g���쐬����
	bool Generate(DWORD num);

	// ���X�g��j������
	void Release();

	// ���ݎw���Ă���v�f��Ԃ�
	// �G���[������ꍇ��null��Ԃ�
	T* Get();

	// ���ݎw���Ă���v�f�Ɋ֌W�Ȃ��A
	// �w�肵���C���f�b�N�X�̗v�f��Ԃ�
	T* GetByIndex(DWORD i);

	// ���X�g���L�����ǂ�����Ԃ�
	bool Enabled();

	// ���ݎw���Ă���v�f�ւ̑�����s��
	bool Set(const T& t);

	// ���̗v�f�ֈړ�����
	// �L���łȂ��l�Ɉړ������ꍇ��false��Ԃ�
	bool Next();

	// �C���f�b�N�X���L���ł���΁A�v�f����������
	bool Change(DWORD i1, DWORD i2);
	
	// �A�N�Z�T
	int GetNum(){ return num; };
	int GetIndex(){ return index; };

	// �C���f�b�N�X�̎w��
	// �L���łȂ��l���w�肵���ꍇ��false��Ԃ�
	bool SetIndex(DWORD i);

	// ���X�g�S�̂��܂ރo�C�i����������쐬����B
	// ���̕�����̃|�C���^�ƃT�C�Y��Ԃ��B
	LPVOID SaveToString(LPDWORD strSize);

	// ���X�g�S�̂��t�@�C������ǂݍ���
	bool LoadFromString(const LPVOID str, bool canOverWrite=false);

};

template<class T>FlexList<T>::FlexList():list(NULL){
	num = 0;
	index = -1;
}

template<class T>FlexList<T>::FlexList(DWORD n):list(NULL){
	Generate(n);
}

template<class T>FlexList<T>::~FlexList(){
	Release();
}

template<class T>bool FlexList<T>::Enabled(){
	if(list == NULL) return false;
	if(num == 0) return false;
	// �C���f�b�N�X���s���Ȓl�̏ꍇ
	if(index < 0 || index >= (int)num) return false;
	return true;
}

template<class T>bool FlexList<T>::Generate(DWORD n){
	SAFE_DELETE_ARRAY(list);
	list = NEW T[n];
	if(!list){
		Release();
		return false;
	}
	num = n;
	index = 0;
	_RPTF1(_CRT_WARN, _T("���X�g�̍쐬���s���܂����B���X�g�� : %d\n"), n);
	return true;
}

template<class T>void FlexList<T>::Release(){
	if(num > 0){
		// ���X�g�𐶐����Ă���ꍇ�A�J������
		// (if�����Ȃ��ƃG���[�ɂȂ�)
		SAFE_DELETE_ARRAY(list);
	}
	num = 0;
	index = -1;
	_RPTF0(_CRT_WARN, _T("���X�g�̊J�����s���܂����B\n"));
}

template<class T>T* FlexList<T>::Get(){
	if(index < 0 || index >= (int)num) return NULL;
	return &list[index];
}

template<class T>T* FlexList<T>::GetByIndex(DWORD i){
	if(i < 0 || i >= num) return NULL;
	return &list[i];
}


template<class T>bool FlexList<T>::Set(const T& t){
	if(index < 0 || index >= (int)num) return false;
	list[index] = t;
	return true;
}

template<class T>bool FlexList<T>::Next(){
	if(index == -1) return false;
	index++;
	if(!Enabled()){
		index = -1;
		return false;
	}else{
		return true;
	}
}

template<class T>bool FlexList<T>::Change(DWORD i1, DWORD i2){
	if(i1 < 0 || i1 >= num) return false;
	if(i2 < 0 || i2 >= num) return false;
	T tmp;
	tmp = list[i1];
	list[i1] = list[i2];
	list[i2] = tmp;
	return true;
}


template<class T>bool FlexList<T>::SetIndex(DWORD i){
	if(i < 0 || i >= num){
		index = -1;
		return false;
	}else{
		index = i;
	}
	return true;
}

template<class T>LPVOID FlexList<T>::SaveToString(LPDWORD size){

	// �Ƃ肠�����R�s�[�T�C�Y��0
	*size = 0;

	// �L�����ǂ���
	if(!Enabled()){
		_RPTF0(_CRT_WARN, _T("���X�g���������쐬����Ă��܂���B\n"));
		return NULL;
	}

	/*
	// ��������m�ۂ���
	if(data != NULL){
		if(canOverWrite){
			SAFE_DELETE_ARRAY(data);
		}else{
		_RPTF0(_CRT_WARN, _T("�f�[�^����ł͂Ȃ��A�㏑�����ł��܂���B\n"));
			return NULL;	
		}
	}
	*/

	// �f�[�^�̗̈���m��
	DWORD dataSize = T::dataSize;
	DWORD allDataSize = dataSize*num+sizeof(DWORD)*2;

	// void�^�ł͈����ɂ����̂Ŏ��ۂɂ�BYTE�^�Ŕz����m�ۂ���
	// �ŏ���DWORD2�̓f�[�^�̑傫���Ɛ�
	BYTE* byteData;
	byteData = (BYTE*)malloc(allDataSize);
	if(!byteData){
		_RPTF0(_CRT_WARN, _T("�e�f�[�^�ۑ��p�̗̈�̊m�ۂɎ��s���܂����B\n"));
		return NULL;
	}
	_RPTF0(_CRT_WARN, _T("�e�f�[�^�ۑ��p�̗̈���m�ۂ��܂����B\n"));

	// �f�[�^�̑傫���Ɛ���������
	DWORD sizeAndNum[2];
	sizeAndNum[0] = dataSize;
	sizeAndNum[1] = num;
	if(memcpy_s((void*)byteData, allDataSize, (void*)&sizeAndNum, 2*sizeof(DWORD)) != 0){
		return NULL;
	}
	_RPTF2(_CRT_WARN, _T("�f�[�^�T�C�Y:%d, �f�[�^��:%d\n"),
		sizeAndNum[0], sizeAndNum[1]);

	// �e�f�[�^���T�[�`
	T* refClass = NULL;
	bool isOK=true;
	for(DWORD i=0; i<num; i++){
		do{ // �G���[���o���甲����
			SetIndex(i);
			refClass = Get();
			if(!refClass){
				_RPTF0(_CRT_WARN, _T("���X�g����̃f�[�^�̎擾�Ɏ��s���܂����B\n"));
				isOK = false;
				break;
			}
			// �������̈�Ƀf�[�^���R�s�[����
			// �|�C���^��z��̂悤�ɗ��p���ăf�[�^����ׂ�
			// �ŏ���2*sizeof(DWORD)�ɂ͊��ɃN���X�̑傫���Ɛ��������Ă���
			if(!refClass->ConvertDataToBytes(byteData+dataSize*i+sizeof(DWORD)*2, dataSize)){
				_RPTF0(_CRT_WARN, _T("�������ւ̃f�[�^�̃R�s�[�Ɏ��s���܂����B\n"));
				isOK = false;
				break;
			}
		}while(0);
		// isOK��false�ɂȂ����炷��������
		if(!isOK) break;
	}

	void* data = 0;
	// �����܂Ő������ł��Ă����
	if(isOK){
		// �������Ŏw�肵���������̈�Ɋ��蓖��
		data = VirtualAlloc(NULL,
			allDataSize,
			MEM_COMMIT,
			PAGE_READWRITE);
		if(!data) return NULL; // �G���[������
		_RPTF0(_CRT_WARN, _T("�f�[�^�����o���p�̗̈���m�ۂ��܂����B\n"));

		// �������̈�ɃR�s�[���s��
		// �����ł͊֐�����const�l��p���č쐬���Ă��邽��
		// �������I�[�o�[�t���[�̐S�z�͂Ȃ�
		if(memcpy_s(data, allDataSize, byteData, allDataSize) != 0){
			_RPTF0(_CRT_WARN, _T("�������̃R�s�[�ŃG���[���������܂����B\n"));
			isOK = false;
		}

		// �G���[���o���ꍇ�͉���������s��
		if(!isOK){
			VirtualFree(NULL, allDataSize, MEM_DECOMMIT);
		}else{
			*size = allDataSize;
		}
	}
	// �e�f�[�^���o���p�Ɋm�ۂ����������̊J��
	// �r���ŃG���[���o�Ă��J���͍s��
	if(byteData){
		free(byteData);
		byteData = 0;
	}
	return (isOK?data:NULL);
}

template<class T>bool FlexList<T>::LoadFromString
	(const LPVOID str, bool canOverWrite){
	DWORD sizeAndNum[2];
	// �f�[�^�T�C�Y�̃`�F�b�N
	if(memcpy_s((void*)&sizeAndNum, sizeof(DWORD)*2, str, sizeof(DWORD)*2) != 0){
		return false;
	}
	if(sizeAndNum[0] != T::dataSize){
		_RPTF0(_CRT_WARN, _T("�ǂݍ������Ƃ��Ă���f�[�^�̃T�C�Y���N���X�ƈقȂ�܂��B\n"));
		return false;
	}

	// ���X�g�̍쐬
	if(!Generate(sizeAndNum[1])){
		_RPTF0(_CRT_WARN, _T("���X�g�̍쐬�Ɏ��s���܂����B\n"));
		return false;
	}
	int num = sizeAndNum[1];

	// ��������̃f�[�^��ǂݍ���
	// �e�f�[�^���T�[�`
	T* refClass = NULL;
	for(DWORD i=0; i<num; i++){
		SetIndex(i);
		refClass = Get();
		// �f�[�^�̃R�s�[���s��
		if(!refClass->ConvertBytesToData(
			(BYTE*)str+sizeAndNum[0]*i+sizeof(DWORD)*2,
			sizeAndNum[0])){
				_RPTF0(_CRT_WARN, _T("�f�[�^�̃R�s�[�Ɏ��s���܂����B\n"));
				return false;
		}
	}
	return true;
}

#endif