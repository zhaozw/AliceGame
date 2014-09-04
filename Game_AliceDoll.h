#ifndef GAME_ALICEDOLL_H
#define GAME_ALICEDOLL_H

// アリスの人形に関するクラスを記述するファイル。
// 戦闘中における人形に関しては別のファイルで扱う。

#include <Windows.h>
#include "Static_AliceDoll.h"
#include "Static_AliceInfo.h"

// パラメータを決める各レベルの構造体。
// 人形の各パラメータはこのレベルと通常のレベルを用いて計算されるグローバルレベルと
// 人形の種類によって決定される。
typedef struct ParamLevel{
	DWORD potential;		// 内部レベル。
						// 人形の作成時に決定され、
						// その後は変化しない。
	DWORD growth;			// 成長レベル。
						// レベルアップ時やアイテムによって
						// ボーナス時に増える。
} PARAMLEVEL;

// アリスの人形のデータのうち、
// セーブデータに含める必要のあるデータを保持する構造体。
// Game_AliceDoll_Essenseクラスに保持される。
typedef struct Game_AliceDoll_Essence_Data{
	DWORD		aliceID;			// この人形を作成したアリスのID。
	DWORD		id;					// 人形のID。ゲーム全体を通して通し番号で割り振られる。
									// aliceIDとidが同一の人形は区別されない。
	int			chapter;			// この人形が作成された章の番号。
	WORD		name[MAX_DOLLNAME];	// 人形の名前。
	BYTE		type;				// ここでは、上海人形など人形の種類。
									// 人形の種類（バランスタイプなどのタイプは"group"）
	WORD		level;				// 全体としてのレベル
	DWORD		exp;				// 積算の経験値。
	int			hp;					// 現在のHP。（最大HPとは別の管理）
	PARAMLEVEL	paramLevel[DOLL_PARAM_MAX];	// パラメータごとのレベル
	BYTE		attrStone[DOLL_ATTRSTONE_NUM]; // 属性スロット
	WORD		skillID[DOLL_SKILL_MAX];	// 覚えているスキルの配列

	Game_AliceDoll_Essence_Data(){
		aliceID = 0;
		id = 0;
		chapter = 0;
		type = DOLL_TYPE_UNDIFINED;
		level = 1;
		exp = 0;
		for(int n=0; n<DOLL_PARAM_MAX; n++){
			paramLevel[n].potential = 0;
			paramLevel[n].growth = 0;
		}
		for(int n=0; n<DOLL_ATTRSTONE_NUM; n++){
			attrStone[n] = 0;
		}
		for(int n=0; n<MAX_DOLLNAME; n++){
			name[n] = 0x00;
		}
		for(int n=0; n<DOLL_SKILL_MAX; n++){
			skillID[n] = 0;
		}
	}
} GAME_ALICEDOLL_ESSENCE_DATA;

// アリスの人形のデータのうち、
// セーブデータに含める必要のあるデータを扱うクラス。
// リストとして扱う関係上データをすべて構造体内に保持している。
class Game_AliceDoll_Essence{
private:
	GAME_ALICEDOLL_ESSENCE_DATA		data;	// データ。
public:
	static DWORD dataSize;					// データサイズ。
public:
	// コンストラクタ
	Game_AliceDoll_Essence();
	// デストラクタ
	~Game_AliceDoll_Essence();
	// コピーコンストラクタ
	Game_AliceDoll_Essence(const Game_AliceDoll_Essence& i);
	// 代入演算子
	Game_AliceDoll_Essence &operator=(const Game_AliceDoll_Essence &i);

	// アクセサ
	DWORD		GetAliceID(){ return data.aliceID; };
	void		SetAliceID(DWORD _aliceID){ data.aliceID = _aliceID; };
	DWORD		GetID(){ return data.id; };
	void		SetID(DWORD _id){ data.id = _id; };
	BYTE		GetType(){ return data.type; };
	void		SetType(BYTE type){ data.type = type; };
	WORD		GetLevel(){ return data.level; };
	void		SetLevel(WORD level){ data.level = level; };
	DWORD		GetExp(){ return data.exp; };
	void		SetExp(DWORD exp){ data.exp = exp; };
	int			GetHP(){ return data.hp; };
	void		SetHP(int hp){ data.hp = hp; };
	// aliceIDとidの値を用いて同一の人形かどうかを取得する。
	bool		CheckSerial(DWORD aliceID, DWORD id){
		return (data.aliceID==aliceID && data.id==id); };

	// 内部レベルを取得。
	DWORD		GetPotentialLevel(BYTE param){
		if(param >= DOLL_PARAM_MAX){
			return 0;
		}
		return data.paramLevel[param].potential;
	};

	// 成長レベルを取得。
	DWORD		GetGrowthLevel(BYTE param){
		if(param >= DOLL_PARAM_MAX){
			return 0;
		}
		return data.paramLevel[param].growth;
	};

	// 内部レベルをセット。
	void		SetPotentialLevel(BYTE param, DWORD level){
		if(param >= DOLL_PARAM_MAX){
			return;
		}
		data.paramLevel[param].potential = level;
	}
	// 成長レベルをセット。
	void		SetGrowthLevel(BYTE param, DWORD level){
		if(param >= DOLL_PARAM_MAX){
			return;
		}
		data.paramLevel[param].growth = level;
	}
	BYTE		GetAttrStone(int pos){
		if(pos >= DOLL_ATTRSTONE_NUM || pos<0){
			return DOLL_ATTR_NONE;
		}
		return data.attrStone[pos];
	}
	void		SetAttrStone(int pos, BYTE attr){
		if(pos >= DOLL_ATTRSTONE_NUM || pos<0){
			return;
		}
		data.attrStone[pos] = attr;
	}
	WORD		GetSkillID(int index){
		if(index < 0 || index >= DOLL_SKILL_MAX){
			return 0;
		}
		return data.skillID[index];
	}
	void		SetSkillID(int index, WORD _skillID){
		if(index < 0 || index >= DOLL_SKILL_MAX){
			return;
		}
		data.skillID[index] = _skillID;
	}


	// パラメータごとのグローバルレベルを取得する関数
	DWORD		GetGLevel(BYTE paramID) const;	// 各パラメータ
	DWORD		GetGeneralGLevel() const;		// 全パラメータの平均(経験値テーブルなどに使用)

	// 人形の属性を取得する関数。
	// 一番かけらの多い属性を返す。
	BYTE		GetAttr() const;

	// セーブデータとして保存するために内容をバイト列に変換する関数
	bool ConvertDataToBytes(LPBYTE p, DWORD size);

	// セーブデータから読み込むために内容をバイト列から読み込む関数
	bool ConvertBytesToData(LPBYTE p, DWORD size);
};

// アリスの人形のデータのうち、
// セーブデータに含める必要のないデータを保持するクラス。
// 実際はこれらのデータは計算によって算出が可能であるが、
// ステータス画面などで毎フレーム計算するのは無駄であるため、
// ステータス画面においてはこのクラスのリストとして人形を管理する。
class Game_AliceDoll : public Game_AliceDoll_Essence{
	DWORD		param[DOLL_PARAM_MAX];	// 各パラメータの実際の値
	DWORD		prevLevelExp;			// 前のレベルに必要な経験値
										// (Lv4であれば、Lv1→Lv4に上がるのに要した経験値。
										// Lv1の状態では0である。
	DWORD		nextLevelExp;			// 次のレベルに必要な経験値
										// (Lv4であれば、Lv1→Lv5に上がるのに必要な経験値。
										// 現在最大レベルである場合は固定値99999999となる。

};

#endif // GAME_ALICEDOLL_H
