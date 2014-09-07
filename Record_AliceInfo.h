#ifndef Record_AliceInfo_H
#define Record_AliceInfo_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Static_AliceDoll.h"

// アリス自身の情報を持つクラス。
// グローバル変数r_aliceInfoから参照される。

typedef struct Record_AliceInfo_Data{
	WORD chapter;		// このファイルでプレイ中の章
	int level;			// アリスのレベル。
	int exp;			// アリスの積算経験値。
	int mp;				// アリスの魔力
	int maxMP;			// 最大魔力
	int day;			// 経過日数
	int time;			// 現在の日数における時間(0時00分を0とした時、何分か)
	int timeToEat;		// 次に料理が作れるまでの時間
	int pieceNum[DOLL_GROUP_NUM][DOLL_ATTR_NUM-1];		// 欠片アイテムの数
	bool dollRecepe[DOLL_TYPE_MAX+1];		// 人形が作成可能かどうか
	DWORD playTime;		// プレイ時間(秒)
	DWORD savedYMD;		// セーブした年・月・日
	DWORD savedHMS;		// セーブした時間・分・秒
	
	Record_AliceInfo_Data(){
		chapter = 0;
		level = 0;
		mp = MAX_MP;
		maxMP = MAX_MP;
		day = 0;
		time = 0;
		timeToEat = 0;
		for(int j=0; j<DOLL_GROUP_NUM; j++){
			for(int i=0; i<(DOLL_ATTR_NUM-1); i++){
				pieceNum[j][i] = 10;
			}
		}
		dollRecepe[0] = false;
		for(int j=0; j<DOLL_GROUP_NUM; j++){
			for(int i=0; i<DOLL_TYPE_PER_GROUP; i++){
				// 各タイプ一番レベルの低い人形だけ作れる
				dollRecepe[i+j*DOLL_TYPE_PER_GROUP+1] = (i==0);
			}
		}
		playTime = 0;
		savedYMD = 0;
		savedHMS = 0;
	};
} RECORD_ALICEINFO_DATA;

class Record_AliceInfo{
private:
	RECORD_ALICEINFO_DATA	data; // データ保存用にデータ用構造体を作成
	// 保存しない
	DWORD					lastSavedWinTime;	// 最後にセーブした時のウィンドウズの時間
public:
	Record_AliceInfo();

	// バイト列からデータに内容をコピーする
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);
	// 現在の現実時間を代入する。
	void GetCntTime(bool load=false);

	// アクセサ
	WORD GetChapter(){ return data.chapter;};
	void SetChapter(WORD _chapter){ data.chapter = _chapter; };

	// 人形が作成可能かどうかを取得する
	bool GetHaveDollRecepe(int index){ return data.dollRecepe[index]; };

	// 人形作成のための石の数を取得する
	int GetPieceNum(int group, int attr){ return data.pieceNum[group][attr]; };
	// 石を増減させる。
	void AddPieceNum(int group, int attr, int num=1){ data.pieceNum[group][attr] += num; };
	bool ReducePieceNum(int group, int attr, int num=1){
		data.pieceNum[group][attr] -= num;
		if(data.pieceNum[group][attr] < 0){
			data.pieceNum[group][attr] = 0;
			return false;
		}
		return true;
	};

	// MPを設定する。
	void SetMP(int p){ data.mp = p; data.maxMP = max(data.maxMP, p); };
	// MPを増やす。上限などの判定を使用する。
	// 指定した値だけ増やせなかった場合：false
	bool AddMP(int p);
	// MPを減らす。加減などの判定を使用する。
	// 指定した値だけ減らせなかった場合：false
	bool SubMP(int p);
	// MPを取得する。
	int GetMP(){ return data.mp; };

	// 時間を取得する
	DWORD GetSavedYMD(){ return data.savedYMD; };
	DWORD GetSavedHMS(){ return data.savedHMS; };

	// プレイ時間を取得する
	DWORD GetPlayTime(){ return data.playTime; };

	// データの構造体全体を渡す。
	RECORD_ALICEINFO_DATA GetData(){ return data; };
};

#endif // Record_AliceInfo_H