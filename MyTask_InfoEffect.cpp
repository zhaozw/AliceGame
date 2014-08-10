// MyTask_InfoEffect.cpp 

#include "MyTask_InfoEffect.h"
#include <DxLib.h>


extern MyGroup* gMyTask_InfoEffect;


// コンストラクタ
void* MyTask_InfoEffect::operator new(size_t t){
	return operator_new(t, gMyTask_InfoEffect);
}
	
// デストラクタ
void MyTask_InfoEffect::operator delete(void* p){
	operator_delete(p, gMyTask_InfoEffect);
}

// コンストラクタ
MyTask_InfoEffect::MyTask_InfoEffect(float _x, float _y,
	WORD _typeID, int _param, int _param2)
:MyTask_ObjectEffect(gMyTask_InfoEffect, _x, _y, 0){
	typeID = _typeID;
	param = _param;
	// typeIDごとに派生する
	lifeTime = 60;
}

// 更新
bool MyTask_InfoEffect::Update(){
	// 末尾に親クラスのアップデートを実行
	return MyTask_BaseEffect::Update();
}

void MyTask_InfoEffect::SetLifeTime(){
	switch(typeID){
	case INFO_DAMAGENUM_ENEMY:
	case INFO_DAMAGENUM_ENEMY_STRONG:
	case INFO_DAMAGENUM_ENEMY_RESIST:
		lifeTime = INFO_DAMAGENUM_ENEMY_LIFETIME;
		break;
	case INFO_DAMAGENUM_DOLL:
	case INFO_DAMAGENUM_DOLL_STRONG:
	case INFO_DAMAGENUM_DOLL_RESIST:
		lifeTime = INFO_DAMAGENUM_DOLL_LIFETIME;
		break;
	default:
		lifeTime = 0;
		break;
	}
}


// 更新
void Update_MyTask_InfoEffect(){
	for( MyIterator i(gMyTask_InfoEffect); i.HasNext(); ){
		i.Next();
		MyTask_InfoEffect* s=(MyTask_InfoEffect*)i.Get();
		if(s->GetTaskIsActive()){
			if(!s->Update()){
				i.Remove();
			}
		}
	}
}

// 描画
void Draw_MyTask_InfoEffect(){
	for( MyIterator i(gMyTask_InfoEffect); i.HasNext(); ){
		i.Next();
		MyTask_InfoEffect* s=(MyTask_InfoEffect*)i.Get();
		if(s->GetTaskIsActive()){
			s->Draw();
		}
	}
}
