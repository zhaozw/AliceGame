#ifndef MYTASK_BASEEFFECT_H
#define MYTASK_BASEEFFECT_H

// GetEffectType�̖߂�l
#define EFFECTTYPE_BASE				0
#define EFFECTTYPE_OBJECT			1
#define EFFECTTYPE_INFO				2

//===========================================
// TBaseEffect�N���X

// �e��G�t�F�N�g�̊�{�N���X�B
// �ʒu�y�ьo�ߎ��Ԃ̏������B
// ��{�I�ɂ͑��̃N���X��I�u�W�F�N�g�Ƃ͑��ݍ�p�����A
// ���Ԍo�߂ɂ����ł���B

#include "MyTask.h"

class MyTask_BaseEffect : public MyTask{
protected:
	float x, y;		// �G�t�F�N�g�̈ʒu�B�Ӗ������̓N���X�ɂ��قȂ邪�A
					// ��{�I�ɂ̓G�t�F�N�g�̒��S�ʒu�ƍl���ėǂ��B
	int	existTime;	// �G�t�F�N�g�����݂��Ă��鎞�ԁB
	int lifeTime;	// �G�t�F�N�g�����ł��鎞�ԁB
public:
	//=================================
	// �N���X���ʊ֐�

	/*
	// �h����̃N���X�ɂ͈ȉ��̊֐����`����B
	// ���ۃN���X�ɂ͂���͕s�v�B�h������MyTask�N���X�ł�
	// NULL��n���悤�ɂȂ��Ă���B
	// �R���X�g���N�^
	void* operator new(size_t t, void* ptr){ return ptr; }; // placement_new
	void* operator new(size_t t);
	// �f�X�g���N�^
	void operator delete(void* ptr, void* ){}; // placement-new�̑΂ƂȂ�f�X�g���N�^
	void operator delete(void* p);
	*/

	// �R���X�g���N�^
	MyTask_BaseEffect(MyGroup *p, float _x, float _y, int _lifeTime);

	// �N���X���Ƃɔh������֐��B
	// �ǂ̔h���N���X���𔻒肷��̂ɗp����B
	// �^�C�v�͑S�Ă��̃t�@�C���̐擪�ɋL���B
	virtual BYTE	GetEffectType(){ return EFFECTTYPE_BASE; };

	// �A�N�Z�T
	int GetExistTime() const { return existTime; };
	int GetLifeTime() const { return lifeTime; };
	// �G�t�F�N�g�����݂��Ă���c�莞�Ԃ�Ԃ��B
	int GetRestTime() const { return lifeTime-existTime; }; 
	// �G�t�F�N�g�̌��݂̑��ݎ��Ԃ̎����ɑ΂��銄����Ԃ��B
	float GetExistRate() const { return (float)existTime/lifeTime; };

	// �X�V���\�b�h
	virtual bool Update(){ existTime++; return (existTime < lifeTime); };
};



#endif // MYTASK_BASEEFFECT_H
