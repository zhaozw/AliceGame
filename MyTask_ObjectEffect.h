#ifndef MYTASK_OBJECTEFFECT_H
#define MYTASK_TOBJECTEEFECT_H

#include "MyTask_BaseEffect.h"

//===============================================
// MyTask_ObjectEffectクラス
// 
// 抽象クラス。
// エフェクトの中でも、オブジェクトのようにふるまうクラスの派生元。
// (画面効果とかではなく。つまり、ほとんどのエフェクトはこれ)
// 

class MyTask_ObjectEffect : public MyTask_BaseEffect{
protected:
public:
	// コンストラクタ
	MyTask_ObjectEffect(MyGroup* p, float _x, float _y, int _lifeTime);

	// ※更新メソッドUpdateはMyTask_BaseEffectで宣言されている
	// 描画メソッド
	virtual void Draw(){};
};


#endif // MYTASK_OBJECTEFFECT_H