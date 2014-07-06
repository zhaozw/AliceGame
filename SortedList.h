// SortedList.h

#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <Windows.h>
#include <stdlib.h>

#include "Common_Macro.h"

// �e���v���[�g���g�p�����N���X�B
// �Œ蒷�̃N���X�ł���A�p�r�Ƃ��Ă͕��בւ����K�v��
// �I�u�W�F�N�g�Q�̊Ǘ����s���B
// ���Ƃ��Ε`�揇�������߂Ă��鏇�ɕ`�悵�����ꍇ�ȂǁB
// 
// class A�ɋ��߂���d�l
// �g�p����Ă��邩�ǂ����������o�Ŕ��f���邱�Ƃ��ł��A
// GetUsed()���\�b�h�Ŏg�p����Ă��邩�ǂ�����Ԃ��B
// Initialize()���\�b�h�Ŗ��g�p��Ԃɂ���B

template <class A> class SortedList{
private:
	bool enabled;		// ���X�g���쐬�����true�ɂȂ�B
						// �쐬�������_�Ń��X�g�͌Œ蒷�B
	DWORD num;			// �v�f��

	A*	pList;			// �e�v�f�̃��X�g�B
	A** ppList;			// ���X�g���w���|�C���^�̔z��B

	// ���בւ��ɗp����֐��̃|�C���^�B
	int (*sortFunc)(const void* d1, const void*d2);


public:
	// �R���X�g���N�^�B
	// ���̎��_�ł͉����������Ȃ��B
	SortedList();

	// �f�X�g���N�^
	// �z�񂪉������Ă��Ȃ������ꍇ�͉�����s���B
	~SortedList();
	
	// �v�f�������߂ă��X�g���쐬����B
	// ����������true��Ԃ��B
	// �쐬�������_�ł̓��X�g�̊e�v�f�͋�ł���B
	bool Generate(DWORD num);

	// ���X�g�̉�����s���B
	// ����������true��Ԃ��B
	bool Release();

	// �z���n�Ԗڂ̗v�f�ւ̃|�C���^��Ԃ��B
	// ���s�����ꍇ��NULL��Ԃ��B
	A* Get(DWORD index);

	// �z��̎g�p����Ă��Ȃ������ɗv�f��}������B
	// �}�����ꂽ�v�f�͂��̏�Ő��񂳂��B
	bool InsertItem(A* data);

	// ����v�f�̏��������s���B
	void DeleteItem(DWORD index);

	// �\�[�g�p�֐��̃|�C���^���Z�b�g����B
	void SetSortFunc(int (*sf)(const void* d1, const void*d2)){
		sortFunc = sf; };

	// �S�v�f�̃\�[�g���s���B
	// �\�[�g�p�̊֐��͈����Ƃ��ēn���B
	// �\�[�g�̌`���̓N�C�b�N�\�[�g�B
	void Sort();

	// �\�[�g�̂��߂̔�r�ɗp����֐���ێ�����B

	// �A�N�Z�T
	DWORD GetNum(){ return num; };
	DWORD GetUsedNum();

	// �v�f�̏�Ԃ��`�F�b�N����
	bool GetUsed(DWORD index){ return ppList[index].GetUsed() ;};


};

template<class A> SortedList<A>::SortedList(){
	enabled		= false;
	num			= 0;
	sortFunc	= NULL;
	pList		= NULL;
	ppList		= NULL;
}

template<class A> SortedList<A>::~SortedList(){
	if(enabled) Release();
}

template<class A> bool SortedList<A>::Generate(DWORD n){
	// ���łɔz�񂪑��݂��Ă���ꍇ��false��Ԃ�
	if(enabled) return false;
	do{ // �Ō�܂ōs���Ȃ�������false��Ԃ�

		// �z����쐬����B
		pList = NEW A[n];
		if(pList == NULL) break;
		// �|�C���^�̔z����쐬����B
		ppList = NEW A*[n];
		if(ppList == NULL){
			// �쐬�����z��̉��
			SAFE_DELETE_ARRAY(pList);
			break;
		}
		// �|�C���^�̔z��Ɋe�v�f�����蓖�Ă�B
		for(DWORD i=0; i<n; i++){
			ppList[i] = &pList[i];
		}
		num = n;
		enabled = true;
		return true;
	}while(0);
	return false;
}

template<class A> bool SortedList<A>::Release(){
	if(!enabled){ return false; };
	SAFE_DELETE_ARRAY(pList);
	SAFE_DELETE_ARRAY(ppList);
	num = 0;
	enabled = false;
	return true;
}

template<class A> bool SortedList<A>::InsertItem(A* data){
	A* pData = 0;
	A *tmp, *tmp_2;
	for(DWORD i=0; i<GetNum(); i++){
		pData = Get(i);
		if(!pData->GetUsed()){
			// �g�p����Ă��Ȃ��f�[�^�����������ꍇ�A����ɑ������
			*ppList[i] = *data;
			// ���̃f�[�^�ɑ΂��Ă̑}���\�[�g���s��
			while(i > 0){
				// ��r���đ傫�����ǂ������m���߂�
				tmp = ppList[i-1];
				tmp_2 = ppList[i];
				if(sortFunc(tmp, tmp_2) > 0){
					// ����ւ�
					tmp = ppList[i];
					ppList[i] = ppList[i-1];
					ppList[i-1] = tmp;
				}
				i--;
			}

			return true;
		}
	}

	return false;
}

template<class A>void SortedList<A>::DeleteItem(DWORD index){
	// �f�[�^�̍폜���s��
	ppList[index]->Initialize();
	// �f�[�^�̏�����ێ�����悤�ɕ��בւ���
	DWORD i=index;
	A *tmp, *tmp_2;
	// �}�������ʒu������܂Ńo�u���\�[�g�ŉ^��
	while(i < num-1){
		// ��r���đ傫�����ǂ������m���߂�
		tmp = ppList[i];
		tmp_2 = ppList[i+1];
		if(sortFunc(tmp, tmp_2) > 0){
			tmp = ppList[i+1];
			// �g�p����Ă��Ȃ��ꍇ�̓��[�v�E�o
			if(!tmp->GetUsed()) break;
			// ����ւ�
			ppList[i+1] = ppList[i];
			ppList[i] = tmp;
		}
		i++;
	}
};

template<class A> A* SortedList<A>::Get(DWORD index){
	if(index >= num) return 0;
	// �|�C���^�̃|�C���^�̔z��̗v�f�̓��X�g�̂���v�f���w���|�C���^�ł���B
	return ppList[index];
}

template<class A> void SortedList<A>::Sort(){
	if(!sortFunc) return;
	qsort(ppList, num, sizeof(*ppList), sortFunc);
}




#endif // SORTEDLIST_H