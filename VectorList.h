#ifndef VECTORLIST_H
#define VECTORLIST_H

#include <Windows.h>
#include <vector>


// vectorクラスを利用した可変長さ配列をデータに持つクラス。
// listにはクラスのポインタではなく、実体を保持する。
// 配列にアクセスする場合はGetPointerByIndexでポインタを取得し、
// 基本的にはそのポインタから値をコピーして使う。
// 配列の内容を書き出す機能などを持つ。


template<class T>class VectorList{
private:
	std::vector<T> list;
	int maxSize;			// 代入可能な最大サイズ。
public:

	// コンストラクタ？
	VectorList<T>();

	// i番目の要素のポインタを返す。
	T* GetPointerByIndex(int i);

	// 現在のリストのサイズを返す。
	int GetSize(){ return list.size(); };

	// 末尾にデータを追加する。
	bool AddData(T data);
	
	// リスト全体を含むバイナリ文字列を作成する。
	// その文字列のポインタとサイズを返す。
	LPVOID SaveToString(LPDWORD strSize);

	// リスト全体を文字列から読み込む
	bool LoadFromString(const LPVOID str, bool canOverWrite=false);

	// リストを解放する。
	bool Release();
};

template<class T> VectorList<T>::VectorList(){
	// Release();
	maxSize = 0;
}

template<class T>T* VectorList<T>::GetPointerByIndex(int index){
	if(index >= GetSize()) return NULL;
	return &list[index];
}

template<class T>bool VectorList<T>::AddData(T data){
	list.push_back(data);
	return true;
}

template<class T>bool VectorList<T>::Release(){
	// 要素を全て解放する
	list.clear();
	// メモリも開放する
	std::vector<T>().swap(list);
	// 
	return true;
}

template<class T>LPVOID VectorList<T>::SaveToString(LPDWORD size){

	// とりあえずコピーサイズは0
	*size = 0;

	// 有効かどうか
	/*
	if(!Enabled()){
		_RPTF0(_CRT_WARN, _T("リストが正しく作成されていません。\n"));
		return NULL;
	}
	*/

	// データの領域を確保
	DWORD dataSize = T::dataSize;
	DWORD allDataSize = dataSize*GetSize()+sizeof(DWORD)*2;

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
	sizeAndNum[1] = GetSize();
	if(memcpy_s((void*)byteData, allDataSize, (void*)&sizeAndNum, 2*sizeof(DWORD)) != 0){
		return NULL;
	}
	_RPTF2(_CRT_WARN, _T("データサイズ:%d, データ数:%d\n"),
		sizeAndNum[0], sizeAndNum[1]);

	// 各データをサーチ
	T* refClass = NULL;
	bool isOK=true;
	for(DWORD i=0; i<sizeAndNum[1]; i++){
		do{ // エラーが出たら抜ける
			refClass = NULL;
			refClass = GetPointerByIndex(i);
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

template<class T>bool VectorList<T>::LoadFromString
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
	if(!Release()){
		_RPTF0(_CRT_WARN, _T("リストの初期化に失敗しました。\n"));
		return false;
	}

	// メモリ上のデータを読み込む
	// 各データをサーチ
	T data;
	for(DWORD i=0; i<sizeAndNum[1]; i++){
		// データのコピーを行う
		if(!data.ConvertBytesToData(
			(BYTE*)str+sizeAndNum[0]*i+sizeof(DWORD)*2,
			sizeAndNum[0])){
				_RPTF0(_CRT_WARN, _T("データのコピーに失敗しました。\n"));
				return false;
		}
		// データをコピーして追加する
		AddData(data);
	}
	return true;
}


#endif // VECTORLIST_H
