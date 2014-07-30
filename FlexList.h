// FlexList.h

#ifndef FLEXLIST_H
#define FLEXLIST_H

#include "Common_Macro.h"
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>


//=============================================
// FlexListクラス
// 配列を動的に生成したり、それを保存したりするクラス。
// 
// クラス Tの要件
// 
// static DWORD dataSize
// そのクラスの持つデータのサイズを返す。
// データを保存するのに必要な領域の大きさ。
// 
// DWORD GetDataSize();
// データのサイズを返すアクセサ。

template<class T>class FlexList{
private:
	T* list;	// クラスの配列
	DWORD num; // 要素数
	int index; // 現在指している要素のインデックス

public:
	// コンストラクタ
	FlexList();
	FlexList(DWORD num);

	// デストラクタ
	~FlexList();

	// リストを作成する
	bool Generate(DWORD num);

	// リストを破棄する
	void Release();

	// 現在指している要素を返す
	// エラーがある場合はnullを返す
	T* Get();

	// 現在指している要素に関係なく、
	// 指定したインデックスの要素を返す
	T* GetByIndex(DWORD i);

	// リストが有効かどうかを返す
	bool Enabled();

	// 現在指している要素への代入を行う
	bool Set(const T& t);

	// 次の要素へ移動する
	// 有効でない値に移動した場合はfalseを返す
	bool Next();

	// インデックスが有効であれば、要素を交換する
	bool Change(DWORD i1, DWORD i2);
	
	// アクセサ
	int GetNum(){ return num; };
	int GetIndex(){ return index; };

	// インデックスの指定
	// 有効でない値を指定した場合はfalseを返す
	bool SetIndex(DWORD i);

	// リスト全体を含むバイナリ文字列を作成する。
	// その文字列のポインタとサイズを返す。
	LPVOID SaveToString(LPDWORD strSize);

	// リスト全体をファイルから読み込む
	bool LoadFromString(const LPVOID str, bool canOverWrite=false);

};

template<class T>FlexList<T>::FlexList():list(NULL){
	num = 0;
	index = -1;
}

template<class T>FlexList<T>::FlexList(DWORD n):list(NULL){
	Generate(n);
}

template<class T>FlexList<T>::~FlexList(){
	Release();
}

template<class T>bool FlexList<T>::Enabled(){
	if(list == NULL) return false;
	if(num == 0) return false;
	// インデックスが不正な値の場合
	if(index < 0 || index >= (int)num) return false;
	return true;
}

template<class T>bool FlexList<T>::Generate(DWORD n){
	SAFE_DELETE_ARRAY(list);
	list = NEW T[n];
	if(!list){
		Release();
		return false;
	}
	num = n;
	index = 0;
	_RPTF1(_CRT_WARN, _T("リストの作成を行いました。リスト数 : %d\n"), n);
	return true;
}

template<class T>void FlexList<T>::Release(){
	if(num > 0){
		// リストを生成している場合、開放する
		// (if文がないとエラーになる)
		SAFE_DELETE_ARRAY(list);
	}
	num = 0;
	index = -1;
	_RPTF0(_CRT_WARN, _T("リストの開放を行いました。\n"));
}

template<class T>T* FlexList<T>::Get(){
	if(index < 0 || index >= (int)num) return NULL;
	return &list[index];
}

template<class T>T* FlexList<T>::GetByIndex(DWORD i){
	if(i < 0 || i >= num) return NULL;
	return &list[i];
}


template<class T>bool FlexList<T>::Set(const T& t){
	if(index < 0 || index >= (int)num) return false;
	list[index] = t;
	return true;
}

template<class T>bool FlexList<T>::Next(){
	if(index == -1) return false;
	index++;
	if(!Enabled()){
		index = -1;
		return false;
	}else{
		return true;
	}
}

template<class T>bool FlexList<T>::Change(DWORD i1, DWORD i2){
	if(i1 < 0 || i1 >= num) return false;
	if(i2 < 0 || i2 >= num) return false;
	T tmp;
	tmp = list[i1];
	list[i1] = list[i2];
	list[i2] = tmp;
	return true;
}


template<class T>bool FlexList<T>::SetIndex(DWORD i){
	if(i < 0 || i >= num){
		index = -1;
		return false;
	}else{
		index = i;
	}
	return true;
}

template<class T>LPVOID FlexList<T>::SaveToString(LPDWORD size){

	// とりあえずコピーサイズは0
	*size = 0;

	// 有効かどうか
	if(!Enabled()){
		_RPTF0(_CRT_WARN, _T("リストが正しく作成されていません。\n"));
		return NULL;
	}

	/*
	// 文字列を確保する
	if(data != NULL){
		if(canOverWrite){
			SAFE_DELETE_ARRAY(data);
		}else{
		_RPTF0(_CRT_WARN, _T("データが空ではなく、上書きができません。\n"));
			return NULL;	
		}
	}
	*/

	// データの領域を確保
	DWORD dataSize = T::dataSize;
	DWORD allDataSize = dataSize*num+sizeof(DWORD)*2;

	// void型では扱いにくいので実際にはBYTE型で配列を確保する
	// 最初のDWORD2つはデータの大きさと数
	BYTE* byteData;
	byteData = (BYTE*)malloc(allDataSize);
	if(!byteData){
		_RPTF0(_CRT_WARN, _T("各データ保存用の領域の確保に失敗しました。\n"));
		return NULL;
	}
	_RPTF0(_CRT_WARN, _T("各データ保存用の領域を確保しました。\n"));

	// データの大きさと数を代入する
	DWORD sizeAndNum[2];
	sizeAndNum[0] = dataSize;
	sizeAndNum[1] = num;
	if(memcpy_s((void*)byteData, allDataSize, (void*)&sizeAndNum, 2*sizeof(DWORD)) != 0){
		return NULL;
	}
	_RPTF2(_CRT_WARN, _T("データサイズ:%d, データ数:%d\n"),
		sizeAndNum[0], sizeAndNum[1]);

	// 各データをサーチ
	T* refClass = NULL;
	bool isOK=true;
	for(DWORD i=0; i<num; i++){
		do{ // エラーが出たら抜ける
			SetIndex(i);
			refClass = Get();
			if(!refClass){
				_RPTF0(_CRT_WARN, _T("リストからのデータの取得に失敗しました。\n"));
				isOK = false;
				break;
			}
			// メモリ領域にデータをコピーする
			// ポインタを配列のように利用してデータを並べる
			// 最初の2*sizeof(DWORD)には既にクラスの大きさと数が入っている
			if(!refClass->ConvertDataToBytes(byteData+dataSize*i+sizeof(DWORD)*2, dataSize)){
				_RPTF0(_CRT_WARN, _T("メモリへのデータのコピーに失敗しました。\n"));
				isOK = false;
				break;
			}
		}while(0);
		// isOKがfalseになったらすぐ抜ける
		if(!isOK) break;
	}

	void* data = 0;
	// ここまで正しくできていれば
	if(isOK){
		// 向こうで指定したメモリ領域に割り当て
		data = VirtualAlloc(NULL,
			allDataSize,
			MEM_COMMIT,
			PAGE_READWRITE);
		if(!data) return NULL; // エラーが発生
		_RPTF0(_CRT_WARN, _T("データ書き出し用の領域を確保しました。\n"));

		// メモリ領域にコピーを行う
		// ここでは関数内でconst値を用いて作成しているため
		// メモリオーバーフローの心配はない
		if(memcpy_s(data, allDataSize, byteData, allDataSize) != 0){
			_RPTF0(_CRT_WARN, _T("メモリのコピーでエラーが発生しました。\n"));
			isOK = false;
		}

		// エラーが出た場合は解放処理を行う
		if(!isOK){
			VirtualFree(NULL, allDataSize, MEM_DECOMMIT);
		}else{
			*size = allDataSize;
		}
	}
	// 各データ取り出し用に確保したメモリの開放
	// 途中でエラーが出ても開放は行う
	if(byteData){
		free(byteData);
		byteData = 0;
	}
	return (isOK?data:NULL);
}

template<class T>bool FlexList<T>::LoadFromString
	(const LPVOID str, bool canOverWrite){
	DWORD sizeAndNum[2];
	// データサイズのチェック
	if(memcpy_s((void*)&sizeAndNum, sizeof(DWORD)*2, str, sizeof(DWORD)*2) != 0){
		return false;
	}
	if(sizeAndNum[0] != T::dataSize){
		_RPTF0(_CRT_WARN, _T("読み込もうとしているデータのサイズがクラスと異なります。\n"));
		return false;
	}

	// リストの作成
	if(!Generate(sizeAndNum[1])){
		_RPTF0(_CRT_WARN, _T("リストの作成に失敗しました。\n"));
		return false;
	}
	int num = sizeAndNum[1];

	// メモリ上のデータを読み込む
	// 各データをサーチ
	T* refClass = NULL;
	for(DWORD i=0; i<num; i++){
		SetIndex(i);
		refClass = Get();
		// データのコピーを行う
		if(!refClass->ConvertBytesToData(
			(BYTE*)str+sizeAndNum[0]*i+sizeof(DWORD)*2,
			sizeAndNum[0])){
				_RPTF0(_CRT_WARN, _T("データのコピーに失敗しました。\n"));
				return false;
		}
	}
	return true;
}

#endif