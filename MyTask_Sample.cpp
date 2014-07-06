// MyTask_Sample.cpp

#include "MyTask_Sample.h"

#include <DxLib.h>
#include "DXInput.h"
#include "KeyConfig.h"
#include "GlobalData.h"

#include "Func_Math.h"

extern DXInput g_input;
extern KeyConfig g_key;
extern GlobalData g_dat;

extern MyGroup* gMyTask_Sample;

// コンストラクタ
void* MyTask_Sample::operator new(size_t t){
	return operator_new(t, gMyTask_Sample);
}
	
// デストラクタ
void MyTask_Sample::operator delete(void* p){
	operator_delete(p, gMyTask_Sample);
}


MyTask_Sample::MyTask_Sample()
:MyTask(gMyTask_Sample){
	x = GetRand(WND_WIDTH);
	y = GetRand(WND_HEIGHT);
	existTime = 0;
	burstTime = 0;
}

bool MyTask_Sample::Update(){
	existTime++;
	if(burstTime > 0){
		burstTime++;
		if(burstTime > 60) return false;
	}
	return true;
}

void MyTask_Sample::CheckBurst(float _x, float _y){
	if(burstTime == 0){
		if(getLong(x, y, _x, _y) < 30){
			burstTime = 1;
			g_dat.score += 1;
		}
	}
}

void MyTask_Sample::CheckChainBurst(MyTask_Sample* pTask){
	if(burstTime == 0){
		if(getLong(x, y, pTask->GetX(), pTask->GetY()) < 30){
			if(pTask->GetBurstTime() > 20){
				burstTime = 1;
				g_dat.score += 1;
			}
		}
	}
}

void MyTask_Sample::Draw(){
	if(burstTime == 0){
		for(int j=0; j<3; j++){
			for(int i=0; i<3; i++){
				DrawPixel((int)x+i, (int)y+j, GetColor(255,255,255)); 
			}
		}
	}else{
		DrawCircle(x, y, 30, GetColor(255, 0, 0), 1);
	}
}

// スプライト群を更新する関数。
// 
void Update_MyTask_Sample(){
	for( MyIterator i(gMyTask_Sample); i.HasNext(); ){
		i.Next();
		MyTask_Sample* s=(MyTask_Sample*)i.Get();
		if(s->GetTaskIsActive()){
			if(!s->Update()){
				i.Remove();
			}
		}
	}
}

void Check_MyTask_Sample_Burst(float playX, float playY){
	for( MyIterator i(gMyTask_Sample); i.HasNext(); ){
		i.Next();
		MyTask_Sample* s=(MyTask_Sample*)i.Get();
		if(s->GetTaskIsActive()){
			s->CheckBurst(playX, playY);
		}
	}
}

void Check_MyTask_Sample_Chain_Burst(){
	for( MyIterator i(gMyTask_Sample); i.HasNext(); ){
		i.Next();
		MyTask_Sample* s=(MyTask_Sample*)i.Get();
		if(s->GetTaskIsActive()){
			for( MyIterator j(gMyTask_Sample); j.HasNext(); ){
				j.Next();
				MyTask_Sample* t=(MyTask_Sample*)j.Get();
				if(s != t){
					if(t->GetTaskIsActive()){
						s->CheckChainBurst(t);
					}
				}
			}
		}
	}
}


void Draw_MyTask_Sample(){
	for( MyIterator i(gMyTask_Sample); i.HasNext(); ){
		i.Next();
		MyTask_Sample* s=(MyTask_Sample*)i.Get();
		if(s->GetTaskIsActive()){
			s->Draw();
		}
	}
}
