// MyTaskList.cpp

#include "MyTask.h"
#include "Common_Macro.h"

// �g�p���Ă���^�X�N�̃w�b�_�t�@�C�����
#include "MyTask_Sample.h"

// ����ȃt�@�C���B
// �g�p����MyGroup�ւ̃|�C���^(�O���[�o���ϐ�)��錾����B
// �܂��AMyGroup�̏�����(�T�C�Y�̎w��)���s���֐�Create_MyTaskList
// �y��MyGroup�̉�����s���֐�Release_MyTaskList���L�q����B
// ���̊֐���main�֐�����Q�Ƃ����B

// MyTask_Sample�N���X
// �폜���č\��Ȃ��B
MyGroup* gMyTask_Sample;

bool Create_MyTaskList(){
	// MyTask_Sample�N���X
	// �폜���č\��Ȃ��B
	gMyTask_Sample = NEW MyGroup(sizeof(MyTask_Sample), 20);

	return true;
}

bool Release_MyTaskList(){
	bool isOK = true;
	// MyTask_Sample�N���X
	// �폜���č\��Ȃ�(��ƃZ�b�g�ō폜���邱�ƁI)
	if(!ReleaseMyTaskGroup(gMyTask_Sample)) isOK = false;

	// 
	return isOK;
}