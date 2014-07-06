#ifndef TASK_H
#define TASK_H

#include "Static_Game.h"
#include <Windows.h>
#include <tchar.h>

// MyTask, MyGroup, MyIteratorクラス
// Taskクラスが特定のGroupに所属することを強制していたのに対し、
// より汎用的な場面で使えるTaskを目指す。

// 解放処理
// MyGroupに対して行う。
#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p)=0; }}

class MyTask;
class MyGroup;
class MyIterator;

/*////////////////////////////////////////////////
MyTask クラス
一般的なタスクを扱う。
自機や敵キャラなどのオブジェクトは全てここから派生する。
複数オブジェクトが存在する種類のオブジェクトを扱うのに便利。
*/////////////////////////////////////////////////
class MyTask{
	friend MyGroup;
	friend MyIterator;

	// そのTaskの所属するGroupへのポインタ
	MyGroup* group;

	// 前後のTaskへのポインタ
	MyTask *prev, *next;

	// 現在タスクがアクティブか否か
	// GroupのCall関数が実行されて
	bool isActive;

	void* operator new(size_t t){}
	void operator delete(void* p){}

protected:
	static void* operator_new(size_t t, MyGroup* group);
	static void operator_delete(void* p, MyGroup* group);

public:
	// コンストラクタ
	MyTask(MyGroup* group);
	// デストラクタ
	virtual ~MyTask();

	// 有効なタスクかどうかを取得
	bool GetTaskIsActive(){ return isActive; };
};

/*////////////////////////////////////////////////
MyGroup クラス
タスクの所属するグループを扱う。
全てのタスクはいずれかのグループに存在し、
MyTask クラスから直接派生した全てのオブジェクトは
いずれかのグループに所属する。
*/////////////////////////////////////////////////

class MyGroup{
	friend MyTask;
	friend MyIterator;

	// 現在指しているアクティブタスク、フリータスクへのポインタ
	// タスクの管理はポインタで行なう->Group::Group内を参照
	MyTask *activeTask, *freeTask;

	// バッファ
	size_t* buf;

	// タスクの最大サイズ
	size_t taskSize;

	// タスクの最大数
	int taskNum;

	// フリータスクの数
	int freeTaskNum;

public:

	// コンストラクタ
	// task_sizeとtask_numに合わせてメモリが確保される。
	// activeTaskには0番目のタスクのメモリが、
	// freeTaskには1番目のタスクのメモリが入る。
	// そして、これはダミータスクである。
	MyGroup(size_t task_size, int task_num);

	// アクティブタスクの数、フリータスクの数の取得
	int GetActiveNum(){ return freeTaskNum; }
	int GetFreeNum(){ return (taskNum - freeTaskNum); }

	// フリータスクのポインタを取得する。
	MyTask* Call();

	// グループで作成したタスクをリリースする
	void Release();

	// このグループに所属する全てのタスクを削除する
	// 実際には全てのタスクがフリータスクになるだけ。
	// メモリの開放は行なわれない。
	void DeleteAllTask();

};

/*////////////////////////////////////////////////
Iterator クラス
Groupに所属する全てのタスクについて処理を行うときに作成し、
Groupを（ポインタ的に）より上位から扱うクラス。
*/////////////////////////////////////////////////

class MyIterator{

protected:
	// この反復子の扱うグループ。
	MyGroup* group;
	// 反復子が現在指しているタスクのポインタ。
	MyTask* task;

public:
	// コンストラクタ
	// 反復子の属するグループを引数とする。
	// メンバ変数groupに引数のgを代入、
	// メンバ変数taskに引数のgの指すactiveTaskを代入。
	// gのactiveTaskには、最初のアクティブタスクのポインタが代入されている。
	// このactiveTaskの指すタスク（つまり、最初のアクティブタスク）から、
	// nextを辿って繰り返していく。
	// ちなみに、最初のアクティブタスクがダミータスクである。
	inline MyIterator(MyGroup* g) : group(g), task(g->activeTask){}

	// 次のタスクがActiveなものかどうかチェックする
	// Activeの最後のタスクまでいったらfalseを返す
	inline bool HasNext(){
		// activeTaskには、最初のアクティブタスクのポインタが代入されている。
		// それぞれのアクティブタスクのnextの値は次のアクティブタスクであるが、
		// 最後のアクティブタスクのnextは最初のアクティブタスクであり、
		// 結果として最後に来たときのみfalseを返すようになっている。
		// 三項演算子での記述
		return task->next==group->activeTask ? false : true;
	}

	// 次の要素へ移動
	inline void Next(){
		task=task->next;
	}

	// 現在の要素を取得
	inline MyTask* Get(LPTSTR str=_T("不明")){
		if(!task){ 
			_RPTF1(_CRT_WARN, "タスクの取得に問題が発生しました。\n呼び出し元:%s\n", str);
		}
		return task;
	}

	// 直前に返した要素（現在taskで指しているタスク）を削除する
	void Remove();
};

// MyGroupへのポインタを指定し、その解放を行う。
bool ReleaseMyTaskGroup(MyGroup* g);

#endif