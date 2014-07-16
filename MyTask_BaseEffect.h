#ifndef MYTASK_BASEEFFECT_H
#define MYTASK_BASEEFFECT_H

// GetEffectTypeの戻り値
#define EFFECTTYPE_BASE				0
#define EFFECTTYPE_OBJECT			1
#define EFFECTTYPE_INFO				2

//===========================================
// TBaseEffectクラス

// 各種エフェクトの基本クラス。
// 位置及び経過時間の情報を持つ。
// 基本的には他のクラスやオブジェクトとは相互作用せず、
// 時間経過により消滅する。

#include "MyTask.h"

class MyTask_BaseEffect : public MyTask{
protected:
	float x, y;		// エフェクトの位置。意味合いはクラスにより異なるが、
					// 基本的にはエフェクトの中心位置と考えて良い。
	int	existTime;	// エフェクトが存在している時間。
	int lifeTime;	// エフェクトが消滅する時間。
public:
	//=================================
	// クラス共通関数

	/*
	// 派生先のクラスには以下の関数を定義する。
	// 抽象クラスにはこれは不要。派生元のMyTaskクラスでは
	// NULLを渡すようになっている。
	// コンストラクタ
	void* operator new(size_t t, void* ptr){ return ptr; }; // placement_new
	void* operator new(size_t t);
	// デストラクタ
	void operator delete(void* ptr, void* ){}; // placement-newの対となるデストラクタ
	void operator delete(void* p);
	*/

	// コンストラクタ
	MyTask_BaseEffect(MyGroup *p, float _x, float _y, int _lifeTime);

	// クラスごとに派生する関数。
	// どの派生クラスかを判定するのに用いる。
	// タイプは全てこのファイルの先頭に記す。
	virtual BYTE	GetEffectType(){ return EFFECTTYPE_BASE; };

	// アクセサ
	int GetExistTime() const { return existTime; };
	int GetLifeTime() const { return lifeTime; };
	// エフェクトが存在している残り時間を返す。
	int GetRestTime() const { return lifeTime-existTime; }; 
	// エフェクトの現在の存在時間の寿命に対する割合を返す。
	float GetExistRate() const { return (float)existTime/lifeTime; };

	// 更新メソッド
	virtual bool Update(){ existTime++; return (existTime < lifeTime); };
};



#endif // MYTASK_BASEEFFECT_H
