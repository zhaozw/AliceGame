// MyTask_Sample.h

#ifndef MYTASK_SAMPLE_H
#define MYTASK_SAMPLE_H

#include "MyTask.h"

//==============================================
// MyTask�̃T���v���B
// 
// (0, 0)����(320, 320)�܂ł̂ǂ����ɓ_��łB
// �_��60�t���[���ɂ킽���Ĉړ����A
// 60�t���[���o�Ə�����B

class MyTask_Sample : public MyTask{
private:
	float x, y;
	int existTime;
	int burstTime;
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
	MyTask_Sample();

	// �X�V���\�b�h
	bool Update();

	// ���@�Ƃ̐ڐG
	void CheckBurst(float x, float y);

	// �A������
	void CheckChainBurst(MyTask_Sample* pTask);

	// �`�惁�\�b�h
	void Draw();

	// �ʒu�̎擾
	float GetX(){ return x; };
	float GetY(){ return y; };
	float GetBurstTime(){ return burstTime; };
};

void Update_MyTask_Sample();
void Check_MyTask_Sample_Burst(float x, float y);
void Check_MyTask_Sample_Chain_Burst();
void Draw_MyTask_Sample();

#endif