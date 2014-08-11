// MyTask_ParticleEffect.cpp 

#include "MyTask_ParticleEffect.h"
#include <DxLib.h>


extern MyGroup* gMyTask_ParticleEffect;


// コンストラクタ
void* MyTask_ParticleEffect::operator new(size_t t){
	return operator_new(t, gMyTask_ParticleEffect);
}
	
// デストラクタ
void MyTask_ParticleEffect::operator delete(void* p){
	operator_delete(p, gMyTask_ParticleEffect);
}

// コンストラクタ
MyTask_ParticleEffect::MyTask_ParticleEffect(float _x, float _y,
	WORD _typeID, int _param, int _param2)
:MyTask_ObjectEffect(gMyTask_ParticleEffect, _x, _y, 0){
	typeID = _typeID;
	param = _param;
	// typeIDごとに派生する
	lifeTime = 60;
}

// 更新
bool MyTask_ParticleEffect::Update(){
	switch(typeID){
	case PARTICLE_SIGN_DAMAGE_RESIST:
	case PARTICLE_SIGN_DAMAGE_WEAK:
		y -= 5.0*max(0, (0.4-GetExistRate()));
		x += 3.5*max(0, (0.4-GetExistRate()));
		break;
	}
	// 末尾に親クラスのアップデートを実行
	return MyTask_BaseEffect::Update();
}

void MyTask_ParticleEffect::SetLifeTime(){
	switch(typeID){
	case PARTICLE_DUMMY:
		lifeTime = PARTICLE_DUMMY_LIFETIME;
		break;
	case PARTICLE_SIGN_DAMAGE_WEAK:
	case PARTICLE_SIGN_DAMAGE_RESIST:
		lifeTime = PARTICLE_SIGN_DAMAGE_LIFETIME;
		break;
	default:
		lifeTime = 0;
		break;
	}
}


// 更新
void Update_MyTask_ParticleEffect(){
	for( MyIterator i(gMyTask_ParticleEffect); i.HasNext(); ){
		i.Next();
		MyTask_ParticleEffect* s=(MyTask_ParticleEffect*)i.Get();
		if(s->GetTaskIsActive()){
			if(!s->Update()){
				i.Remove();
			}
		}
	}
}

// 描画
void Draw_MyTask_ParticleEffect(){
	for( MyIterator i(gMyTask_ParticleEffect); i.HasNext(); ){
		i.Next();
		MyTask_ParticleEffect* s=(MyTask_ParticleEffect*)i.Get();
		if(s->GetTaskIsActive()){
			s->Draw();
		}
	}
}
