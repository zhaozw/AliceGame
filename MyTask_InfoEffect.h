#ifndef MYTASK_INFOEFFECT_H
#define MYTASK_INFOEEFECT_H

#include "MyTask_ObjectEffect.h"
#include "Static_InfoEffect.h"

//===============================================
// 情報系のエフェクト。
// ダメージ数値の表示など。
// グローバル変数g_MyTaskInfoEffectを所属グループとする。

class MyTask_InfoEffect : public MyTask_ObjectEffect{
protected:
	// 情報の種類。
	WORD	typeID;

	// パラメータの種類。
	int		param;
	int		param2;
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
	MyTask_InfoEffect(float _x, float _y, WORD _typeID, int _param=0, int _param2=0);

	// タイプの取得
	virtual BYTE	GetEffectType(){ return EFFECTTYPE_INFO; };

	// 独自の更新及び描画メソッド
	virtual bool Update();
	virtual void Draw() const;

protected:
	// typeID値に応じたlifeTimeを設定する。
	void SetLifeTime();
};

void Update_MyTask_InfoEffect();
void Draw_MyTask_InfoEffect();


#endif // MYTASK_INFOEFFECT_H