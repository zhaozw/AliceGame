// Task.cpp

#include <Windows.h>
#include <assert.h>
#include "MyTask.h"
#include "Common_Macro.h"

///////////////////////////////
// グループの初期化
// task_size	:	そのグループが管理するタスクの種類のサイズ。
//					sizeof(Task)で取得したものを代入する。
// task_num		:	そのグループのタスク数。
//					この数だけオブジェクトを同時に出現させられる。
//
///////////////////////////////

MyGroup::MyGroup(size_t task_size, int task_num)
:	taskSize(task_size),
							// タスクのサイズ。
							// そのグループに入りうるタスクの
							// 最大サイズのタスクのサイズを指定する。
							// つまり、派生クラスなどがあって複数種の
							// クラスが入りうる場合、最大サイズのものを入れる。
							// 自分で数えて入れるか、派生させずに全てのタスクを同じサイズにする。
							// 前者ではnew時に速くなると思われる。
							// 後者はプログラム時の手間が省ける。
							// 派生により多くのメンバを追加する必要がある場合は前者、
							// あまり変わらない場合は後者を推奨。
	taskNum(task_num),		// タスクの数。
	freeTaskNum(task_num),	// 現在のフリータスクの数（最初は全てフリー）
							// おのおの、Groupのメンバ変数。情報の代入。
	activeTask(NULL), freeTask(NULL), buf(NULL)
{
	// タスク初期化用の関数形式マクロ -> 関数形式マクロを参照
	// INDEX番目のタスクの位置（ポインタ）を返すマクロ
#define MYTASK(INDEX) ((MyTask*)(buf+task_size*(INDEX)))
	// bufはchar型のポインタで、0番目のタスクの位置。
	// ポインタの値をtask_size*INDEXだけずらして、INDEX番目の位置にする。

	// メモリを確保し、0番目のタスクの位置を取得。
	// +2は、アクティブとフリーのダミータスク。
	// newで作成したのがsize_tなので、size_t型のポインタを受け取る。
	buf = NEW size_t[task_size*(task_num+2)];

	// isActiveが0になるようにメモリを全て0で初期化
	ZeroMemory(buf, task_size*(task_num+2)*sizeof(size_t));

	// アクティブタスクの初期化
	// activeTask（メンバ変数）の値に0番目のタスクのポインタを代入
	// これがダミータスクとなる。
	// これはGroupのメンバの値の変更。
	activeTask = MYTASK(0);

	// ダミータスクのみの時には、PrevとNextは共に自身を指す
	// これらはTaskのメンバの値の変更。上との違いに注意。
	activeTask->prev = activeTask;
	activeTask->next = activeTask;

	// フリータスクの初期化
	freeTask = MYTASK(1); // freeTask（メンバ変数）の値に1番目のタスクのポインタを代入
	for(int i=1; i<task_num+1; i++){
		MYTASK(i)->next = MYTASK(i+1);	// 各々のタスクに、その次のタスクの値を設定
									// フリータスクのprevの値は参照されないので
									// prevへの代入の必要はない。
									// 正しく位置を指すようにしている。
		MYTASK(i+1)->prev = MYTASK(i);
		/*
		メモリ配置

		アクティブ・ダミー フリー・ダミー
		TASK(0)            TASK(1)            TASK(2)
		*__________________*__________________*__________________ ……
		タスク幅は等間隔で、タスクの最大サイズに等しい。

		*/
	}
	MYTASK(task_num+1)->next = freeTask;	// 最後のタスクの次のタスクが1番目のタスクに
										// 1～task_num番目のタスクでループする
										// アクティブタスクも単独でループしている。
	MYTASK(1)->prev = MYTASK(task_num+1);	// フリータスクの前のタスクは自分自身

	// activeTaskとfreeTaskに自身を指させる
	// それ以外のタスクはnew時にgroupを指させる
	activeTask->group = this;
	freeTask->group = this;
}

MyTask* MyGroup::Call(){
	// 一時保管用
	MyTask* secondTask = freeTask->next->next;
	// フリータスクを1つ取り出す
	// 最初のフリータスク（ダミー）の次のタスクが取り出される
	MyTask* task = freeTask->next;
	// フリータスクがない場合はNULLを返す
	if(task == freeTask) return NULL;
	//  取り出されたタスクを抜きにしたループを作り直す。
	secondTask->prev = freeTask;
	freeTask->next = secondTask;

	// フリータスクは1つ減る
	freeTaskNum--;

	// 取り出したフリータスクを渡す
	// ここで渡したアドレスを使ってMyTaskはplacement newしなければならない。
	return task;

	// アクティブタスクとの連結はMyTaskクラスのコンストラクタから行われる。
}

void MyGroup::Release(){
	SAFE_DELETE_ARRAY(buf);
}

/////////////////////////////////
// タスクの初期化
// 
/////////////////////////////////

// newの処理
// placement newによってのみ作成される。

void* MyTask::operator_new(size_t t, MyGroup* group){
	return NULL;
}

// コンストラクタ
MyTask::MyTask(MyGroup* group) : group(group),
prev(NULL), next(NULL){
	// このタスクをアクティブタスクにする。
	isActive = true;
	// 最後のアクティブタスクに挿入する。
	// activeTaskの指すprevは最後のタスク。
	prev = group->activeTask->prev;
	// nextは最初のタスク。
	next = group->activeTask;
	// prev:最後から2番目のタスク。next:最初のタスク。
	prev->next = next->prev = this;
}

/////////////////////////////////
// タスクの削除
// 
/////////////////////////////////

// タスクの削除はGroupクラスから行われる。
// 実際には参照位置が変わるだけであり、メモリの解放などは行われない。
// 
void MyTask::operator_delete(void* p, MyGroup* group){
}

MyTask::~MyTask(){
}

/////////////////////////////////
// 全タスクの消去
// そのグループに属する全てのタスクをフリータスクにする。
/////////////////////////////////

void MyGroup::DeleteAllTask(){
	for(MyIterator i(this); i.HasNext();){
		 i.Next();
		 i.Remove();
	}
}


void MyIterator::Remove(){
	// この関数は現在指しているタスクを削除し、
	// 一つ前のタスクに移動する。

	// タスクを非アクティブにする
	task->isActive = false;

	// 一つ前のタスクへの移動。
	MyTask* rsvTask = task->prev;

	// activeTask側のループを作成する
	task->prev->next = task->next;
	task->next->prev = task->prev;

	// task自身のループを作成する
	task->next = group->freeTask->next;
	task->prev = group->freeTask;

	// freeTask側のループを作成する
	group->freeTask->next->prev = task;
	group->freeTask->next = task;

	// Iteratorの指すタスクを更新する
	task = rsvTask;

	// グループのフリータスクを1つ増やす
	group->freeTaskNum++;
}

bool ReleaseMyTaskGroup(MyGroup* g){
	g->DeleteAllTask();
	g->Release();
	SAFE_DELETE(g);
	return true;
}