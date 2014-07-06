// SortedList.h

#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <Windows.h>
#include <stdlib.h>

#include "Common_Macro.h"

// テンプレートを使用したクラス。
// 固定長のクラスであり、用途としては並べ替えが必要な
// オブジェクト群の管理を行う。
// たとえば描画順序を決めてある順に描画したい場合など。
// 
// class Aに求められる仕様
// 使用されているかどうかをメンバで判断することができ、
// GetUsed()メソッドで使用されているかどうかを返す。
// Initialize()メソッドで未使用状態にする。

template <class A> class SortedList{
private:
	bool enabled;		// リストを作成するとtrueになる。
						// 作成した時点でリストは固定長。
	DWORD num;			// 要素数

	A*	pList;			// 各要素のリスト。
	A** ppList;			// リストを指すポインタの配列。

	// 並べ替えに用いる関数のポインタ。
	int (*sortFunc)(const void* d1, const void*d2);


public:
	// コンストラクタ。
	// この時点では何も生成しない。
	SortedList();

	// デストラクタ
	// 配列が解放されていなかった場合は解放も行う。
	~SortedList();
	
	// 要素数を決めてリストを作成する。
	// 成功したらtrueを返す。
	// 作成した時点ではリストの各要素は空である。
	bool Generate(DWORD num);

	// リストの解放を行う。
	// 成功したらtrueを返す。
	bool Release();

	// 配列のn番目の要素へのポインタを返す。
	// 失敗した場合はNULLを返す。
	A* Get(DWORD index);

	// 配列の使用されていない部分に要素を挿入する。
	// 挿入された要素はその場で整列される。
	bool InsertItem(A* data);

	// ある要素の初期化を行う。
	void DeleteItem(DWORD index);

	// ソート用関数のポインタをセットする。
	void SetSortFunc(int (*sf)(const void* d1, const void*d2)){
		sortFunc = sf; };

	// 全要素のソートを行う。
	// ソート用の関数は引数として渡す。
	// ソートの形式はクイックソート。
	void Sort();

	// ソートのための比較に用いる関数を保持する。

	// アクセサ
	DWORD GetNum(){ return num; };
	DWORD GetUsedNum();

	// 要素の状態をチェックする
	bool GetUsed(DWORD index){ return ppList[index].GetUsed() ;};


};

template<class A> SortedList<A>::SortedList(){
	enabled		= false;
	num			= 0;
	sortFunc	= NULL;
	pList		= NULL;
	ppList		= NULL;
}

template<class A> SortedList<A>::~SortedList(){
	if(enabled) Release();
}

template<class A> bool SortedList<A>::Generate(DWORD n){
	// すでに配列が存在している場合はfalseを返す
	if(enabled) return false;
	do{ // 最後まで行けなかったらfalseを返す

		// 配列を作成する。
		pList = NEW A[n];
		if(pList == NULL) break;
		// ポインタの配列を作成する。
		ppList = NEW A*[n];
		if(ppList == NULL){
			// 作成した配列の解放
			SAFE_DELETE_ARRAY(pList);
			break;
		}
		// ポインタの配列に各要素を割り当てる。
		for(DWORD i=0; i<n; i++){
			ppList[i] = &pList[i];
		}
		num = n;
		enabled = true;
		return true;
	}while(0);
	return false;
}

template<class A> bool SortedList<A>::Release(){
	if(!enabled){ return false; };
	SAFE_DELETE_ARRAY(pList);
	SAFE_DELETE_ARRAY(ppList);
	num = 0;
	enabled = false;
	return true;
}

template<class A> bool SortedList<A>::InsertItem(A* data){
	A* pData = 0;
	A *tmp, *tmp_2;
	for(DWORD i=0; i<GetNum(); i++){
		pData = Get(i);
		if(!pData->GetUsed()){
			// 使用されていないデータが見つかった場合、それに代入する
			*ppList[i] = *data;
			// そのデータに対しての挿入ソートを行う
			while(i > 0){
				// 比較して大きいかどうかを確かめる
				tmp = ppList[i-1];
				tmp_2 = ppList[i];
				if(sortFunc(tmp, tmp_2) > 0){
					// 入れ替え
					tmp = ppList[i];
					ppList[i] = ppList[i-1];
					ppList[i-1] = tmp;
				}
				i--;
			}

			return true;
		}
	}

	return false;
}

template<class A>void SortedList<A>::DeleteItem(DWORD index){
	// データの削除を行う
	ppList[index]->Initialize();
	// データの順序を保持するように並べ替える
	DWORD i=index;
	A *tmp, *tmp_2;
	// 挿入した位置から後ろまでバブルソートで運ぶ
	while(i < num-1){
		// 比較して大きいかどうかを確かめる
		tmp = ppList[i];
		tmp_2 = ppList[i+1];
		if(sortFunc(tmp, tmp_2) > 0){
			tmp = ppList[i+1];
			// 使用されていない場合はループ脱出
			if(!tmp->GetUsed()) break;
			// 入れ替え
			ppList[i+1] = ppList[i];
			ppList[i] = tmp;
		}
		i++;
	}
};

template<class A> A* SortedList<A>::Get(DWORD index){
	if(index >= num) return 0;
	// ポインタのポインタの配列の要素はリストのある要素を指すポインタである。
	return ppList[index];
}

template<class A> void SortedList<A>::Sort(){
	if(!sortFunc) return;
	qsort(ppList, num, sizeof(*ppList), sortFunc);
}




#endif // SORTEDLIST_H