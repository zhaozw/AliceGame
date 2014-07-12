#ifndef SCENE_BATTLE_H
#define SCENE_BATTLE_H

#include "Scene_Base.h"
#include "Static_Battle.h"
#include "Game_BattleUnit.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Game_UnitCommand.h"
#include "Game_BattleAction.h"
#include "Window_BattleMessage.h"
#include "BWindow_AliceCommand.h"
#include "BWindow_DollCommand.h"
#include "BWIndow_SelectEnemy.h"
#include "BWindow_FocusedEnemy.h"
#include "Sprite_BattleDoll.h"
#include "Sprite_BattleEnemy.h"

class Scene_Battle : public Scene_Base{
public:
	// 戦闘のフェイズを記述する。
	// 基本的に、
	// ①フェイズ開始時に、SceneBattleのSetupPhaze関数により
	//   actionStackにそのフェイズのアクションがセットされる
	// ②actionStackを上から処理していく。
	//   各アクションを処理するごとに、ウィンドウの内容やスプライトに変化が生じるので
	//   それらの変化が終わるまで待機する。
	// ③全てのactionStackが消費されたところで次のフェイズに移行する。
	// という流れになる。
	//
	// BATTLE_DOフェイズにおいては、
	// actionStackベースではなくGame_UnitCommandクラスのcommandsベースで進行する。
	// すなわち、commandの内容を順番に処理していくが、
	// command一つごとにactionStackが追加・消費・リセットされる。
	// 全てのcommandsが実行されたところで次のフェイズに移行する。

	enum BATTLEPHAZE{
		BEFORE_BATTLE,		// 戦闘前（PRE_BATTLEの前に入るダミー）
		PRE_BATTLE,			// 戦闘前
		ALICE_COMMAND,		// アリスのコマンドを選択
		ALICE_COMMAND_DO,	// アリスのコマンドを実行
		DOLLS_COMMAND,		// 人形のコマンドを選択
		ENEMIES_COMMAND,	// 敵のコマンドを選択（即座に終了する）
		BEFORE_TURN,		// ターンの最初
		BATTLE_DO,			// 戦闘
		AFTER_TURN,			// ターン終了時
		POST_BATTLE,		// 戦闘終了
	};

	// 戦闘のサブフェイズを記録する。
	enum SUBPHAZE{
		ASSERT_ACTION,		// 行動の宣言
		BEFORE_ACTION,		// 行動を適用する前
		PERFORM_ACTION,		// 行動の適用
		AFTER_ACTION,		// 行動の適用後
		CHECK_ACTION,		// 行動の結果バトラーが変化する状態の確認
	};

private:
	// 現在戦闘している敵グループIDを指定する。
	WORD								enemyGroup;
	// 現在の状況を表す
	enum BATTLEPHAZE					phaze;
	enum SUBPHAZE						subPhaze;
	// 味方・敵ユニットは通常の配列で表現する
	// 味方ユニットの配列
	Game_BattleDoll						dolls[MAX_BATTLEDOLL];
	int									dollsNum;	// 味方ユニットの最大数（戦闘不能者含む）
	// 敵ユニットの配列
	Game_BattleEnemy					enemies[MAX_BATTLEENEMY];
	int									enemiesNum;	// 敵ユニットの最大数（戦闘不能者含む）
	// 攻撃コマンドの配列
	Game_UnitCommand					commands[MAX_UNITCOMMAND];
	// DOLL_COMMAND及びENEMY_COMMAND時
	// 現在何番目のコマンドまで入っているか。
	// DO_BATTLE時
	// 現在処理しているコマンドのインデックス。
	int									commandIndex;
	// 現在のインデックス（コマンド選択時など）
	int									currentIndex;
	// 現在のGame_UnitCommandを処理するフェイズ
	int									commandPhaze;
	// アクションのスタック
	Game_BattleActionStack				actionStack;
	// メッセージウィンドウ
	Window_BattleMessage				w_battleMsg;
	// アリスのコマンドウィンドウ
	BWindow_AliceCommand				w_aliceCommand;
	// 人形のコマンドウィンドウ
	BWindow_DollCommand					w_dollCommand;
	// 敵の選択ウィンドウ
	BWindow_SelectEnemy					w_selectEnemy;
	// 敵のフォーカスウィンドウ
	BWindow_FocusedEnemy				w_focusedEnemy;
	// 人形のスプライト
	Sprite_BattleDoll					s_dolls[NUM_BATTLEDOLL_FRONT];
	// 敵のスプライト
	Sprite_BattleEnemy					s_enemies[MAX_BATTLEENEMY];
public:
	// コンストラクタ
	Scene_Battle();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw();

	//=========================================
	// シーン全体の制御
	// Scene_Battle.cppに記述する。

	// ウィンドウの初期化を行う。
	bool SetupWindow();

	// スプライトの初期化を行う。
	bool SetupSprite();

	// 次のアクションに進むかどうかの判定を行う。
	// ウィンドウやスプライト群をチェックして、
	// 全て待機状態になっているかどうかを確認する。
	bool CheckNextAction();

	// 次のアクションを実行する。
	// 正しくアクションが実行された場合はtrueを、
	// 次に実行するべきアクションがない＝次のフェイズに移行する場合はfalseを返す。
	bool ExecuteAction();

	// 次のフェイズに移行する。
	void NextPhaze();

	// 次のフェイズに移行した際の処理。
	// 関数NextPhazeから実行される。
	// 各フェイズごとに実行するアクションをセットする。
	void SetupPreBattle();		// PRE_BATTLEになった時
	void SetupAliceCommand();	// アリスのコマンドウィンドウを開く
	void SetupAliceCommandDo(); // アリスのコマンドを実行する
	void SetupDollsCommand();	// 人形のコマンドウィンドウを開く 
	void SetupEnemiesCommand();	// 敵のコマンドを決定する。(即座に終わる)
	void SetupBeforeTurn();		// ターン開始時。ステートの判定など。
	void SetupBattleDo();		// 戦闘。
	void SetupAfterTurn();		// ターン終了時。ステートの判定など。


	// 必要なオブジェクト群のアップデートを行う。
	void UpdateObjects();
	
	// 人形の配列が変わった際に、人形スプライトに人形を割り当て直す。
	bool AttachDollPtrToSprite();

	//=========================================
	// アクセサ関連
	// ソースファイルに記述するものはScene_Battle.cppに記述する。
	int GetDollsNum(){ return dollsNum; } ;
	int GetEnemiesNum(){ return enemiesNum; };

	// 人形のポインタを取得する。
	Game_BattleDoll*	GetDollPtr(int index){
		if(index < 0 || index >= MAX_BATTLEDOLL) return NULL;
		return &dolls[index];
	}

	// 敵キャラのポインタを取得する。
	Game_BattleEnemy*	GetEnemyPtr(int index){
		if(index < 0 || index >= MAX_BATTLEENEMY) return NULL;
		return &enemies[index];
	}

	// 前列のi番目に居る人形が、Game_BattleDollの配列の中では何番目かを取得する。
	int	GetFrontIndex(WORD position);

	// 前列の指定した順番の人形のポインタを返す。
	// checkCanTargetをtrueにすると、人形が戦闘不能であった場合NULLを返す。
	Game_BattleDoll*	GetFrontDollPtr(WORD index, bool checkCanTarget=false);
	// 前列の人形一体をランダムで返す。
	Game_BattleDoll*	GetRandomDollPtr();
	// 敵キャラ一体のポインタをランダムで返す。
	Game_BattleEnemy*	GetRandomEnemyPtr();



	// 各種ウィンドウを開く。
	// 他のウィンドウからの参照などの形。

	// 敵選択ウィンドウ
	BYTE	OpenSelectEnemyWindow();
	int		GetSelectEnemyIndex(){ return w_selectEnemy.GetSelectIndex(); };
	BWindow_SelectEnemy*	GetWndSelectEnemyPtr(){ return &w_selectEnemy; };
	BYTE	OpenFocusedEnemyWindow();
	int		GetFocusedEnemyIndex(){ return w_focusedEnemy.GetSelectIndex(); };
	BWindow_FocusedEnemy*	GetWndFocusedEnemyPtr(){ return &w_focusedEnemy; };

	//=========================================
	// 外部データの呼び出し・データ連係関連
	// Scene_Battle_Data.cppに記述する。
	// 人形を呼び出す（味方パーティをセットする）関数。

	// 味方の人形のセットアップを行う。
	bool SetupDolls();
	// 敵パーティのセットアップを行う。
	bool SetupEnemy();
	// デバッグ用。ソースコードで直接指定する。
	bool LoadDefaultDolls(int defaultID);	
	// データベースファイルからIDを指定して読み込む。
	// ファイルパスはdat_battle\\preset_dolls%02d.csv
	bool LoadPresetDolls(int presetID);
	// グループIDを指定してデータベースから読み込む。
	// SetupEnemyから使用される。
	bool LoadEnemyGroup();
	// Game_BattleEnemyの要素一つに指定した敵IDの情報を読み込む。
	// ついでに描画位置もセットする。
	// LoadEnemyGroupから使用される。
	bool LoadEnemyData(WORD index, WORD enemyID, int drawX, int drawY);

	//=========================================
	// ユニット関連
	// Scene_Battle_Unit.cppに記述する。
	// 能力値を指定する。
	// index : 配列の要素番号
	// hp, maxhp, atk, spd, mgc, tec : 各パラメータ
	// 人形のパラメータなどを指定するアクセサ。
	void SetDollParams(int index, int hp, int maxhp, int atk, int spd, int mgc, int tec);
	// 敵のパラメータなどを指定するアクセサ。
	void SetEnemyParams(
		int index, int hp, int maxhp, int atk, int def, int spd, int mgc, int tec);	

	//=========================================
	// Game_BattleActionの内容の処理。
	// Scene_Battle_Action.cppに記述する。
	bool InterpretAction(Game_BattleAction* pAction);
	bool Action_CallEnemyName();

	//=========================================
	// Game_BattleActionの内容の処理。
	// Scene_Battle_Action.cppに記述する。

	// commandPhaze :
	// 例えば通常攻撃にせよ、
	// 実際の攻撃前に行われる判定（防御をしているキャラクターの防御力補正とか）や
	// 攻撃後に行われる判定（次の攻撃のみパワーアップのステートなど）がある。
	// 一つのUnitCommandの解釈を、いくつかのフェイズごとに管理するための
	// パラメータ。Static_Battle.h内のCOMMANDPHAZE_xxx定数群で定義される。
	// 
	bool InterpretCommand(Game_UnitCommand* pCmd, int commandPhaze=COMMANDPHAZE_NOPHAZE);
	// commandPhazeによって分岐する
	bool InterpretCommand_NoPhaze(Game_UnitCommand* pCmd);
	bool InterpretCommand_Pre_Action(Game_UnitCommand* pCmd);
	bool InterpretCommand_Action(Game_UnitCommand* pCmd);
	bool InterpretCommand_Post_Action(Game_UnitCommand* pCmd);

	//=========================================
	// 戦闘中の諸演算
	// Scene_Battle_Calc.cppに記述する。

	// コマンドを追加する。
	bool SetCommand(Game_UnitCommand cmd);
	
	// 敵のコマンドを自動で追加する。
	// 内部でSetEnemyCommandを使用する。
	bool SetEnemyCommands();

	// ポインタを使用し、敵のコマンドを算出する。
	Game_UnitCommand GetEnemyCommand(Game_BattleEnemy* pEnemy);

	// 戦闘行動のソートを行う。
	bool SortUnitCommands();
	
	// commandsの内容を全てクリアする。
	void ClearCommands();

	//=========================================
	// 描画
	// 下記の関数はScene_Battle_Draw.cppに記述する。

	// 人形のスプライトを描画する。
	void DrawDollsSprite() const;
	// 敵キャラのスプライトを描画する。
	void DrawEnemiesSprite() const;

};

#endif // SCENE_BATTLE_H