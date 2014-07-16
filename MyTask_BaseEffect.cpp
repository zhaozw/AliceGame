// MyTask_BaseEffect.cpp

#include "MyTask_BaseEffect.h"

MyTask_BaseEffect::MyTask_BaseEffect(MyGroup *p, float _x, float _y, int _lifeTime)
:MyTask(p){
	x = _x;
	y = _y;
	existTime = 0;
}
