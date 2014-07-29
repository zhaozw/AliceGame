// MyTaskList.cpp

#include "MyTask.h"
#include "Common_Macro.h"

// 使用しているタスクのヘッダファイルを列挙
#include "MyTask_Sample.h"
#include "MyTask_InfoEffect.h"
#include "MyTask_ParticleEffect.h"

// 特殊なファイル。
// 使用するMyGroupへのポインタ(グローバル変数)を宣言する。
// また、MyGroupの初期化(サイズの指定)を行う関数Create_MyTaskList
// 及びMyGroupの解放を行う関数Release_MyTaskListを記述する。
// この関数はmain関数から参照される。

// MyTask_Sampleクラス
// 削除して構わない。
MyGroup* gMyTask_Sample;
// 情報系のエフェクトを表示するクラス。
MyGroup* gMyTask_InfoEffect;
// パーティクル系のエフェクトを表示するクラス。
MyGroup* gMyTask_ParticleEffect;

bool Create_MyTaskList(){
	// MyTask_Sampleクラス
	// 削除して構わない。
	gMyTask_Sample = NEW MyGroup(sizeof(MyTask_Sample), 20);
	gMyTask_InfoEffect = NEW MyGroup(sizeof(MyTask_InfoEffect), 128);
	gMyTask_ParticleEffect = NEW MyGroup(sizeof(MyTask_ParticleEffect), 512);
	return true;
}

bool Release_MyTaskList(){
	bool isOK = true;
	// MyTask_Sampleクラス
	// 削除して構わない(上とセットで削除すること！)
	if(!ReleaseMyTaskGroup(gMyTask_Sample)) isOK = false;
	
	if(!ReleaseMyTaskGroup(gMyTask_InfoEffect)) isOK = false;

	if(!ReleaseMyTaskGroup(gMyTask_ParticleEffect)) isOK = false;

	// 
	return isOK;
}