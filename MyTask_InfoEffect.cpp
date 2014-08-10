// MyTask_InfoEffect.cpp 

#include "MyTask_InfoEffect.h"
#include <DxLib.h>


extern MyGroup* gMyTask_InfoEffect;


// �R���X�g���N�^
void* MyTask_InfoEffect::operator new(size_t t){
	return operator_new(t, gMyTask_InfoEffect);
}
	
// �f�X�g���N�^
void MyTask_InfoEffect::operator delete(void* p){
	operator_delete(p, gMyTask_InfoEffect);
}

// �R���X�g���N�^
MyTask_InfoEffect::MyTask_InfoEffect(float _x, float _y,
	WORD _typeID, int _param, int _param2)
:MyTask_ObjectEffect(gMyTask_InfoEffect, _x, _y, 0){
	typeID = _typeID;
	param = _param;
	// typeID���Ƃɔh������
	lifeTime = 60;
}

// �X�V
bool MyTask_InfoEffect::Update(){
	// �����ɐe�N���X�̃A�b�v�f�[�g�����s
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


// �X�V
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

// �`��
void Draw_MyTask_InfoEffect(){
	for( MyIterator i(gMyTask_InfoEffect); i.HasNext(); ){
		i.Next();
		MyTask_InfoEffect* s=(MyTask_InfoEffect*)i.Get();
		if(s->GetTaskIsActive()){
			s->Draw();
		}
	}
}
