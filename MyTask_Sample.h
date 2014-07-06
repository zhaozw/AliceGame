// MyTask_Sample.h

#ifndef MYTASK_SAMPLE_H
#define MYTASK_SAMPLE_H

#include "MyTask.h"

//==============================================
// MyTaskのサンプル。
// 
// (0, 0)から(320, 320)までのどこかに点を打つ。
// 点は60フレームにわたって移動し、
// 60フレーム経つと消える。

class MyTask_Sample : public MyTask{
private:
	float x, y;
	int existTime;
	int burstTime;
public:
	//=================================
	// クラス共通関数
	// コンストラクタ
	void* operator new(size_t t, void* ptr){ return ptr; }; // placement_new
	void* operator new(size_t t);
	// デストラクタ
	void operator delete(void* ptr, void* ){}; // placement-newの対となるデストラクタ
	void operator delete(void* p);

	// コンストラクタ
	MyTask_Sample();

	// 更新メソッド
	bool Update();

	// 自機との接触
	void CheckBurst(float x, float y);

	// 連鎖爆発
	void CheckChainBurst(MyTask_Sample* pTask);

	// 描画メソッド
	void Draw();

	// 位置の取得
	float GetX(){ return x; };
	float GetY(){ return y; };
	float GetBurstTime(){ return burstTime; };
};

void Update_MyTask_Sample();
void Check_MyTask_Sample_Burst(float x, float y);
void Check_MyTask_Sample_Chain_Burst();
void Draw_MyTask_Sample();

#endif