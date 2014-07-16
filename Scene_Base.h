#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Static_Game.h"
#include "Config.h"
#include "DxLib.h"
#include "DXTimeCtrl.h"
#include "DXInput.h"

#define SCNANIME_NONE	0

//////////////////////////////////////////////////
// Scene_Baseクラス
// 全てのゲームシーンの元になるクラス。
// 基本的に初期化(Initialize), 実行(Play), 終了処理(Terminate)の3つの関数を持ち、
// 戻り値で次のシーンを判定する。
class Scene_Base{
protected:
	// 次のシーンの予約。
	// 一定の時間後にシーンの切り替えを行う場合などに用いる。
	int reservedScene;
	// 次のシーンの予約が行われてからのカウント。
	// フェードなどに使用する。
	int reservedCount;
	int reservedCount_max;
	// シーンでループするごとに増えるカウンタ。
	int sceneTime;
	// 時間制御を行なう
	DXTimeCtrl timectrl;
	// 次のフレームをスキップするフラグ
	bool fDrawSkip;
	// シーンの状態を保持しておく
	int state;
	int stateTime;
private:
	// アニメーションの状態を保持しておく
	int	anime;
	int animeCount;
	int animeTime;
public:
	// コンストラクタ
	Scene_Base();
	// デストラクタ
	virtual ~Scene_Base(){};
	// 初期化処理
	// fSkipFrame : 処理落ちではなくコマ落ちをするかどうか
	virtual bool Initialize(bool fSkipFrame);
	// 実行処理 (Input, Update, Drawからなり、各シーン共通)
	int Play();
	// 終了処理
	virtual bool Terminate();
	
	// 入力処理 (各シーン共通)
	bool Input();
	// 計算処理
	virtual int Update()=0;
	// 描画処理
	virtual void Draw() const =0;
	
	// 次シーンの予約
	void ReserveScene(int sceneID, int count=1){
		if(reservedCount_max == 0){
			reservedScene = sceneID;
			reservedCount = 0;
			reservedCount_max = count;
		}
	}

	// 次のシーンが予約されているか
	bool SceneIsReserved(){
		return reservedScene != SCENE_NONE;
	}

	// 予約解除
	void UnlockReservedScene(){
		reservedScene = SCENE_NONE;
		reservedCount = 0;
		reservedCount_max = 0;
	}
	
	// フェードなどに使用
	float GetFadeRate() const{
		return (float)reservedCount/reservedCount_max;
	}

	// ReserveSceneに併せてフェードアウトする
	void DrawReserveFade(int color=0) const;

	// 次のフレームをスキップするか否か
	void SetDrawSkip(bool f=true);

	// シーンの状態を変更する
	void SetState(int s){ state = s; stateTime = 0; };
	int GetState(){ return state; };

	// アニメの状態を変更する
	void SetAnime(int a, int time){ anime = a; animeTime = time; animeCount = 0; };
	void UpdateAnime(){
		if(animeTime < 0) animeTime = 0;
		if(anime != SCNANIME_NONE){
			animeCount++;
			if(animeCount>=animeTime){ 
				// アニメーションのブレを防ぐため
				// animeCount, animeTimeのリセットは行わない
				anime = SCNANIME_NONE;
			}
		}
	};
	// アクセサ
	int GetAnimeCount() const{ return animeCount; };
	int GetAnimeTime() const{ return animeTime; };
	int GetAnimeEnded(){ return anime == SCNANIME_NONE; };
};

#endif // SCENE_BASE_H