#ifndef MYTASK_OBJECTEFFECT_H
#define MYTASK_TOBJECTEEFECT_H

#include "MyTask_BaseEffect.h"

//===============================================
// MyTask_ObjectEffect�N���X
// 
// ���ۃN���X�B
// �G�t�F�N�g�̒��ł��A�I�u�W�F�N�g�̂悤�ɂӂ�܂��N���X�̔h�����B
// (��ʌ��ʂƂ��ł͂Ȃ��B�܂�A�قƂ�ǂ̃G�t�F�N�g�͂���)
// 

class MyTask_ObjectEffect : public MyTask_BaseEffect{
protected:
public:
	// �R���X�g���N�^
	MyTask_ObjectEffect(MyGroup* p, float _x, float _y, int _lifeTime);

	// ���X�V���\�b�hUpdate��MyTask_BaseEffect�Ő錾����Ă���
	// �`�惁�\�b�h
	virtual void Draw(){};
};


#endif // MYTASK_OBJECTEFFECT_H