// MyTaskList.cpp

#include "MyTask.h"
#include "Common_Macro.h"

// �g�p���Ă���^�X�N�̃w�b�_�t�@�C�����
#include "MyTask_Sample.h"
#include "MyTask_InfoEffect.h"
#include "MyTask_ParticleEffect.h"

// ����ȃt�@�C���B
// �g�p����MyGroup�ւ̃|�C���^(�O���[�o���ϐ�)��錾����B
// �܂��AMyGroup�̏�����(�T�C�Y�̎w��)���s���֐�Create_MyTaskList
// �y��MyGroup�̉�����s���֐�Release_MyTaskList���L�q����B
// ���̊֐���main�֐�����Q�Ƃ����B

// MyTask_Sample�N���X
// �폜���č\��Ȃ��B
MyGroup* gMyTask_Sample;
// ���n�̃G�t�F�N�g��\������N���X�B
MyGroup* gMyTask_InfoEffect;
// �p�[�e�B�N���n�̃G�t�F�N�g��\������N���X�B
MyGroup* gMyTask_ParticleEffect;

bool Create_MyTaskList(){
	// MyTask_Sample�N���X
	// �폜���č\��Ȃ��B
	gMyTask_Sample = NEW MyGroup(sizeof(MyTask_Sample), 20);
	gMyTask_InfoEffect = NEW MyGroup(sizeof(MyTask_InfoEffect), 128);
	gMyTask_ParticleEffect = NEW MyGroup(sizeof(MyTask_ParticleEffect), 512);
	return true;
}

bool Release_MyTaskList(){
	bool isOK = true;
	// MyTask_Sample�N���X
	// �폜���č\��Ȃ�(��ƃZ�b�g�ō폜���邱�ƁI)
	if(!ReleaseMyTaskGroup(gMyTask_Sample)) isOK = false;
	
	if(!ReleaseMyTaskGroup(gMyTask_InfoEffect)) isOK = false;

	if(!ReleaseMyTaskGroup(gMyTask_ParticleEffect)) isOK = false;

	// 
	return isOK;
}