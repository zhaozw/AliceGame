#ifndef TASK_H
#define TASK_H

#include "Static_Game.h"
#include <Windows.h>
#include <tchar.h>

// MyTask, MyGroup, MyIterator�N���X
// Task�N���X�������Group�ɏ������邱�Ƃ��������Ă����̂ɑ΂��A
// ���ėp�I�ȏ�ʂŎg����Task��ڎw���B

// �������
// MyGroup�ɑ΂��čs���B
#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p)=0; }}

class MyTask;
class MyGroup;
class MyIterator;

/*////////////////////////////////////////////////
MyTask �N���X
��ʓI�ȃ^�X�N�������B
���@��G�L�����Ȃǂ̃I�u�W�F�N�g�͑S�Ă�������h������B
�����I�u�W�F�N�g�����݂����ނ̃I�u�W�F�N�g�������̂ɕ֗��B
*/////////////////////////////////////////////////
class MyTask{
	friend MyGroup;
	friend MyIterator;

	// ����Task�̏�������Group�ւ̃|�C���^
	MyGroup* group;

	// �O���Task�ւ̃|�C���^
	MyTask *prev, *next;

	// ���݃^�X�N���A�N�e�B�u���ۂ�
	// Group��Call�֐������s�����
	bool isActive;

	void* operator new(size_t t){}
	void operator delete(void* p){}

protected:
	static void* operator_new(size_t t, MyGroup* group);
	static void operator_delete(void* p, MyGroup* group);

public:
	// �R���X�g���N�^
	MyTask(MyGroup* group);
	// �f�X�g���N�^
	virtual ~MyTask();

	// �L���ȃ^�X�N���ǂ������擾
	bool GetTaskIsActive(){ return isActive; };
};

/*////////////////////////////////////////////////
MyGroup �N���X
�^�X�N�̏�������O���[�v�������B
�S�Ẵ^�X�N�͂����ꂩ�̃O���[�v�ɑ��݂��A
MyTask �N���X���璼�ڔh�������S�ẴI�u�W�F�N�g��
�����ꂩ�̃O���[�v�ɏ�������B
*/////////////////////////////////////////////////

class MyGroup{
	friend MyTask;
	friend MyIterator;

	// ���ݎw���Ă���A�N�e�B�u�^�X�N�A�t���[�^�X�N�ւ̃|�C���^
	// �^�X�N�̊Ǘ��̓|�C���^�ōs�Ȃ�->Group::Group�����Q��
	MyTask *activeTask, *freeTask;

	// �o�b�t�@
	size_t* buf;

	// �^�X�N�̍ő�T�C�Y
	size_t taskSize;

	// �^�X�N�̍ő吔
	int taskNum;

	// �t���[�^�X�N�̐�
	int freeTaskNum;

public:

	// �R���X�g���N�^
	// task_size��task_num�ɍ��킹�ă��������m�ۂ����B
	// activeTask�ɂ�0�Ԗڂ̃^�X�N�̃��������A
	// freeTask�ɂ�1�Ԗڂ̃^�X�N�̃�����������B
	// �����āA����̓_�~�[�^�X�N�ł���B
	MyGroup(size_t task_size, int task_num);

	// �A�N�e�B�u�^�X�N�̐��A�t���[�^�X�N�̐��̎擾
	int GetActiveNum(){ return freeTaskNum; }
	int GetFreeNum(){ return (taskNum - freeTaskNum); }

	// �t���[�^�X�N�̃|�C���^���擾����B
	MyTask* Call();

	// �O���[�v�ō쐬�����^�X�N�������[�X����
	void Release();

	// ���̃O���[�v�ɏ�������S�Ẵ^�X�N���폜����
	// ���ۂɂ͑S�Ẵ^�X�N���t���[�^�X�N�ɂȂ邾���B
	// �������̊J���͍s�Ȃ��Ȃ��B
	void DeleteAllTask();

};

/*////////////////////////////////////////////////
Iterator �N���X
Group�ɏ�������S�Ẵ^�X�N�ɂ��ď������s���Ƃ��ɍ쐬���A
Group���i�|�C���^�I�Ɂj����ʂ��爵���N���X�B
*/////////////////////////////////////////////////

class MyIterator{

protected:
	// ���̔����q�̈����O���[�v�B
	MyGroup* group;
	// �����q�����ݎw���Ă���^�X�N�̃|�C���^�B
	MyTask* task;

public:
	// �R���X�g���N�^
	// �����q�̑�����O���[�v�������Ƃ���B
	// �����o�ϐ�group�Ɉ�����g�����A
	// �����o�ϐ�task�Ɉ�����g�̎w��activeTask�����B
	// g��activeTask�ɂ́A�ŏ��̃A�N�e�B�u�^�X�N�̃|�C���^���������Ă���B
	// ����activeTask�̎w���^�X�N�i�܂�A�ŏ��̃A�N�e�B�u�^�X�N�j����A
	// next��H���ČJ��Ԃ��Ă����B
	// ���Ȃ݂ɁA�ŏ��̃A�N�e�B�u�^�X�N���_�~�[�^�X�N�ł���B
	inline MyIterator(MyGroup* g) : group(g), task(g->activeTask){}

	// ���̃^�X�N��Active�Ȃ��̂��ǂ����`�F�b�N����
	// Active�̍Ō�̃^�X�N�܂ł�������false��Ԃ�
	inline bool HasNext(){
		// activeTask�ɂ́A�ŏ��̃A�N�e�B�u�^�X�N�̃|�C���^���������Ă���B
		// ���ꂼ��̃A�N�e�B�u�^�X�N��next�̒l�͎��̃A�N�e�B�u�^�X�N�ł��邪�A
		// �Ō�̃A�N�e�B�u�^�X�N��next�͍ŏ��̃A�N�e�B�u�^�X�N�ł���A
		// ���ʂƂ��čŌ�ɗ����Ƃ��̂�false��Ԃ��悤�ɂȂ��Ă���B
		// �O�����Z�q�ł̋L�q
		return task->next==group->activeTask ? false : true;
	}

	// ���̗v�f�ֈړ�
	inline void Next(){
		task=task->next;
	}

	// ���݂̗v�f���擾
	inline MyTask* Get(LPTSTR str=_T("�s��")){
		if(!task){ 
			_RPTF1(_CRT_WARN, "�^�X�N�̎擾�ɖ�肪�������܂����B\n�Ăяo����:%s\n", str);
		}
		return task;
	}

	// ���O�ɕԂ����v�f�i����task�Ŏw���Ă���^�X�N�j���폜����
	void Remove();
};

// MyGroup�ւ̃|�C���^���w�肵�A���̉�����s���B
bool ReleaseMyTaskGroup(MyGroup* g);

#endif