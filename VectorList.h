#ifndef VECTORLIST_H
#define VECTORLIST_H

#include <Windows.h>
#include <vector>


// vector�N���X�𗘗p�����ϒ����z����f�[�^�Ɏ��N���X�B
// list�ɂ̓N���X�̃|�C���^�ł͂Ȃ��A���̂�ێ�����B
// �z��ɃA�N�Z�X����ꍇ��GetPointerByIndex�Ń|�C���^���擾���A
// ��{�I�ɂ͂��̃|�C���^����l���R�s�[���Ďg���B
// �z��̓��e�������o���@�\�Ȃǂ����B


template<class T>class VectorList{
private:
	std::vector<T> list;
	int maxSize;			// ����\�ȍő�T�C�Y�B
public:

	// �R���X�g���N�^�H
	VectorList<T>();

	// i�Ԗڂ̗v�f�̃|�C���^��Ԃ��B
	T* GetPointerByIndex(int i);

	// ���݂̃��X�g�̃T�C�Y��Ԃ��B
	int GetSize(){ return list.size(); };

	// �����Ƀf�[�^��ǉ�����B
	bool AddData(T data);
	
	// ���X�g�S�̂��܂ރo�C�i����������쐬����B
	// ���̕�����̃|�C���^�ƃT�C�Y��Ԃ��B
	LPVOID SaveToString(LPDWORD strSize);

	// ���X�g�S�̂𕶎��񂩂�ǂݍ���
	bool LoadFromString(const LPVOID str, bool canOverWrite=false);

	// ���X�g���������B
	bool Release();
};

template<class T> VectorList<T>::VectorList(){
	// Release();
	maxSize = 0;
}

template<class T>T* VectorList<T>::GetPointerByIndex(int index){
	if(index >= GetSize()) return NULL;
	return &list[index];
}

template<class T>bool VectorList<T>::AddData(T data){
	list.push_back(data);
	return true;
}

template<class T>bool VectorList<T>::Release(){
	// �v�f��S�ĉ������
	list.clear();
	// ���������J������
	std::vector<T>().swap(list);
	// 
	return true;
}

template<class T>LPVOID VectorList<T>::SaveToString(LPDWORD size){

	// �Ƃ肠�����R�s�[�T�C�Y��0
	*size = 0;

	// �L�����ǂ���
	/*
	if(!Enabled()){
		_RPTF0(_CRT_WARN, _T("���X�g���������쐬����Ă��܂���B\n"));
		return NULL;
	}
	*/

	// �f�[�^�̗̈���m��
	DWORD dataSize = T::dataSize;
	DWORD allDataSize = dataSize*GetSize()+sizeof(DWORD)*2;

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
	sizeAndNum[1] = GetSize();
	if(memcpy_s((void*)byteData, allDataSize, (void*)&sizeAndNum, 2*sizeof(DWORD)) != 0){
		return NULL;
	}
	_RPTF2(_CRT_WARN, _T("�f�[�^�T�C�Y:%d, �f�[�^��:%d\n"),
		sizeAndNum[0], sizeAndNum[1]);

	// �e�f�[�^���T�[�`
	T* refClass = NULL;
	bool isOK=true;
	for(DWORD i=0; i<sizeAndNum[1]; i++){
		do{ // �G���[���o���甲����
			refClass = NULL;
			refClass = GetPointerByIndex(i);
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

template<class T>bool VectorList<T>::LoadFromString
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
	if(!Release()){
		_RPTF0(_CRT_WARN, _T("���X�g�̏������Ɏ��s���܂����B\n"));
		return false;
	}

	// ��������̃f�[�^��ǂݍ���
	// �e�f�[�^���T�[�`
	T data;
	for(DWORD i=0; i<sizeAndNum[1]; i++){
		// �f�[�^�̃R�s�[���s��
		if(!data.ConvertBytesToData(
			(BYTE*)str+sizeAndNum[0]*i+sizeof(DWORD)*2,
			sizeAndNum[0])){
				_RPTF0(_CRT_WARN, _T("�f�[�^�̃R�s�[�Ɏ��s���܂����B\n"));
				return false;
		}
		// �f�[�^���R�s�[���Ēǉ�����
		AddData(data);
	}
	return true;
}


#endif // VECTORLIST_H
