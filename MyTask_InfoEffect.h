#ifndef MYTASK_INFOEFFECT_H
#define MYTASK_INFOEEFECT_H

#include "MyTask_ObjectEffect.h"
#include "Static_InfoEffect.h"

//===============================================
// ���n�̃G�t�F�N�g�B
// �_���[�W���l�̕\���ȂǁB
// �O���[�o���ϐ�g_MyTaskInfoEffect�������O���[�v�Ƃ���B

class MyTask_InfoEffect : public MyTask_ObjectEffect{
protected:
	// ���̎�ށB
	WORD	typeID;

	// �p�����[�^�̎�ށB
	int		param;
	int		param2;
public:
	//=================================
	// �N���X���ʊ֐�
	// �R���X�g���N�^
	void* operator new(size_t t, void* ptr){ return ptr; }; // placement_new
	void* operator new(size_t t);
	// �f�X�g���N�^
	void operator delete(void* ptr, void* ){}; // placement-new�̑΂ƂȂ�f�X�g���N�^
	void operator delete(void* p);

	// �R���X�g���N�^
	MyTask_InfoEffect(float _x, float _y, WORD _typeID, int _param=0, int _param2=0);

	// �^�C�v�̎擾
	virtual BYTE	GetEffectType(){ return EFFECTTYPE_INFO; };

	// �Ǝ��̍X�V�y�ѕ`�惁�\�b�h
	virtual bool Update();
	virtual void Draw() const;

protected:
	// typeID�l�ɉ�����lifeTime��ݒ肷��B
	void SetLifeTime();
};

void Update_MyTask_InfoEffect();
void Draw_MyTask_InfoEffect();


#endif // MYTASK_INFOEFFECT_H