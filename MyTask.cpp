// Task.cpp

#include <Windows.h>
#include <assert.h>
#include "MyTask.h"
#include "Common_Macro.h"

///////////////////////////////
// �O���[�v�̏�����
// task_size	:	���̃O���[�v���Ǘ�����^�X�N�̎�ނ̃T�C�Y�B
//					sizeof(Task)�Ŏ擾�������̂�������B
// task_num		:	���̃O���[�v�̃^�X�N���B
//					���̐������I�u�W�F�N�g�𓯎��ɏo����������B
//
///////////////////////////////

MyGroup::MyGroup(size_t task_size, int task_num)
:	taskSize(task_size),
							// �^�X�N�̃T�C�Y�B
							// ���̃O���[�v�ɓ��肤��^�X�N��
							// �ő�T�C�Y�̃^�X�N�̃T�C�Y���w�肷��B
							// �܂�A�h���N���X�Ȃǂ������ĕ������
							// �N���X�����肤��ꍇ�A�ő�T�C�Y�̂��̂�����B
							// �����Ő����ē���邩�A�h���������ɑS�Ẵ^�X�N�𓯂��T�C�Y�ɂ���B
							// �O�҂ł�new���ɑ����Ȃ�Ǝv����B
							// ��҂̓v���O�������̎�Ԃ��Ȃ���B
							// �h���ɂ�葽���̃����o��ǉ�����K�v������ꍇ�͑O�ҁA
							// ���܂�ς��Ȃ��ꍇ�͌�҂𐄏��B
	taskNum(task_num),		// �^�X�N�̐��B
	freeTaskNum(task_num),	// ���݂̃t���[�^�X�N�̐��i�ŏ��͑S�ăt���[�j
							// ���̂��́AGroup�̃����o�ϐ��B���̑���B
	activeTask(NULL), freeTask(NULL), buf(NULL)
{
	// �^�X�N�������p�̊֐��`���}�N�� -> �֐��`���}�N�����Q��
	// INDEX�Ԗڂ̃^�X�N�̈ʒu�i�|�C���^�j��Ԃ��}�N��
#define MYTASK(INDEX) ((MyTask*)(buf+task_size*(INDEX)))
	// buf��char�^�̃|�C���^�ŁA0�Ԗڂ̃^�X�N�̈ʒu�B
	// �|�C���^�̒l��task_size*INDEX�������炵�āAINDEX�Ԗڂ̈ʒu�ɂ���B

	// ���������m�ۂ��A0�Ԗڂ̃^�X�N�̈ʒu���擾�B
	// +2�́A�A�N�e�B�u�ƃt���[�̃_�~�[�^�X�N�B
	// new�ō쐬�����̂�size_t�Ȃ̂ŁAsize_t�^�̃|�C���^���󂯎��B
	buf = NEW size_t[task_size*(task_num+2)];

	// isActive��0�ɂȂ�悤�Ƀ�������S��0�ŏ�����
	ZeroMemory(buf, task_size*(task_num+2)*sizeof(size_t));

	// �A�N�e�B�u�^�X�N�̏�����
	// activeTask�i�����o�ϐ��j�̒l��0�Ԗڂ̃^�X�N�̃|�C���^����
	// ���ꂪ�_�~�[�^�X�N�ƂȂ�B
	// �����Group�̃����o�̒l�̕ύX�B
	activeTask = MYTASK(0);

	// �_�~�[�^�X�N�݂̂̎��ɂ́APrev��Next�͋��Ɏ��g���w��
	// ������Task�̃����o�̒l�̕ύX�B��Ƃ̈Ⴂ�ɒ��ӁB
	activeTask->prev = activeTask;
	activeTask->next = activeTask;

	// �t���[�^�X�N�̏�����
	freeTask = MYTASK(1); // freeTask�i�����o�ϐ��j�̒l��1�Ԗڂ̃^�X�N�̃|�C���^����
	for(int i=1; i<task_num+1; i++){
		MYTASK(i)->next = MYTASK(i+1);	// �e�X�̃^�X�N�ɁA���̎��̃^�X�N�̒l��ݒ�
									// �t���[�^�X�N��prev�̒l�͎Q�Ƃ���Ȃ��̂�
									// prev�ւ̑���̕K�v�͂Ȃ��B
									// �������ʒu���w���悤�ɂ��Ă���B
		MYTASK(i+1)->prev = MYTASK(i);
		/*
		�������z�u

		�A�N�e�B�u�E�_�~�[ �t���[�E�_�~�[
		TASK(0)            TASK(1)            TASK(2)
		*__________________*__________________*__________________ �c�c
		�^�X�N���͓��Ԋu�ŁA�^�X�N�̍ő�T�C�Y�ɓ������B

		*/
	}
	MYTASK(task_num+1)->next = freeTask;	// �Ō�̃^�X�N�̎��̃^�X�N��1�Ԗڂ̃^�X�N��
										// 1�`task_num�Ԗڂ̃^�X�N�Ń��[�v����
										// �A�N�e�B�u�^�X�N���P�ƂŃ��[�v���Ă���B
	MYTASK(1)->prev = MYTASK(task_num+1);	// �t���[�^�X�N�̑O�̃^�X�N�͎������g

	// activeTask��freeTask�Ɏ��g���w������
	// ����ȊO�̃^�X�N��new����group���w������
	activeTask->group = this;
	freeTask->group = this;
}

MyTask* MyGroup::Call(){
	// �ꎞ�ۊǗp
	MyTask* secondTask = freeTask->next->next;
	// �t���[�^�X�N��1���o��
	// �ŏ��̃t���[�^�X�N�i�_�~�[�j�̎��̃^�X�N�����o�����
	MyTask* task = freeTask->next;
	// �t���[�^�X�N���Ȃ��ꍇ��NULL��Ԃ�
	if(task == freeTask) return NULL;
	//  ���o���ꂽ�^�X�N�𔲂��ɂ������[�v����蒼���B
	secondTask->prev = freeTask;
	freeTask->next = secondTask;

	// �t���[�^�X�N��1����
	freeTaskNum--;

	// ���o�����t���[�^�X�N��n��
	// �����œn�����A�h���X���g����MyTask��placement new���Ȃ���΂Ȃ�Ȃ��B
	return task;

	// �A�N�e�B�u�^�X�N�Ƃ̘A����MyTask�N���X�̃R���X�g���N�^����s����B
}

void MyGroup::Release(){
	SAFE_DELETE_ARRAY(buf);
}

/////////////////////////////////
// �^�X�N�̏�����
// 
/////////////////////////////////

// new�̏���
// placement new�ɂ���Ă̂ݍ쐬�����B

void* MyTask::operator_new(size_t t, MyGroup* group){
	return NULL;
}

// �R���X�g���N�^
MyTask::MyTask(MyGroup* group) : group(group),
prev(NULL), next(NULL){
	// ���̃^�X�N���A�N�e�B�u�^�X�N�ɂ���B
	isActive = true;
	// �Ō�̃A�N�e�B�u�^�X�N�ɑ}������B
	// activeTask�̎w��prev�͍Ō�̃^�X�N�B
	prev = group->activeTask->prev;
	// next�͍ŏ��̃^�X�N�B
	next = group->activeTask;
	// prev:�Ōォ��2�Ԗڂ̃^�X�N�Bnext:�ŏ��̃^�X�N�B
	prev->next = next->prev = this;
}

/////////////////////////////////
// �^�X�N�̍폜
// 
/////////////////////////////////

// �^�X�N�̍폜��Group�N���X����s����B
// ���ۂɂ͎Q�ƈʒu���ς�邾���ł���A�������̉���Ȃǂ͍s���Ȃ��B
// 
void MyTask::operator_delete(void* p, MyGroup* group){
}

MyTask::~MyTask(){
}

/////////////////////////////////
// �S�^�X�N�̏���
// ���̃O���[�v�ɑ�����S�Ẵ^�X�N���t���[�^�X�N�ɂ���B
/////////////////////////////////

void MyGroup::DeleteAllTask(){
	for(MyIterator i(this); i.HasNext();){
		 i.Next();
		 i.Remove();
	}
}


void MyIterator::Remove(){
	// ���̊֐��͌��ݎw���Ă���^�X�N���폜���A
	// ��O�̃^�X�N�Ɉړ�����B

	// �^�X�N���A�N�e�B�u�ɂ���
	task->isActive = false;

	// ��O�̃^�X�N�ւ̈ړ��B
	MyTask* rsvTask = task->prev;

	// activeTask���̃��[�v���쐬����
	task->prev->next = task->next;
	task->next->prev = task->prev;

	// task���g�̃��[�v���쐬����
	task->next = group->freeTask->next;
	task->prev = group->freeTask;

	// freeTask���̃��[�v���쐬����
	group->freeTask->next->prev = task;
	group->freeTask->next = task;

	// Iterator�̎w���^�X�N���X�V����
	task = rsvTask;

	// �O���[�v�̃t���[�^�X�N��1���₷
	group->freeTaskNum++;
}

bool ReleaseMyTaskGroup(MyGroup* g){
	g->DeleteAllTask();
	g->Release();
	SAFE_DELETE(g);
	return true;
}