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
#include "BWindow_DollSkill.h"
#include "BWIndow_SelectEnemy.h"
#include "BWindow_FocusedUnit.h"
#include "Window_SimpleDollStatus.h"

#include "Sprite_BattleDoll.h"
#include "Sprite_BattleEnemy.h"

#define INFOWINDOW_NONE				0
#define INFOWINDOW_DOLLINFO			1
#define INFOWINDOW_ENEMY			2

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
		BEFORE_SORT,		// 素早さソートの前に各コマンドの判定を行う
		AFTER_SORT,			// ターンの最初（ソートの後）
		BATTLE_DO,			// 戦闘
		AFTER_TURN,			// ターン終了時
		POST_BATTLE,		// 戦闘終了
		END_BATTLE,			// シーン終了(即座にフェードアウトしてシーン移動)
	};

private:
	// 現在戦闘している敵グループIDを指定する。
	WORD								enemyGroup;
	// 現在の状況を表す
	enum BATTLEPHAZE					phaze;
	// 戦闘の結果を表す
	BYTE								battleResult;
	// 味方・敵ユニットは通常の配列で表現する
	// 味方ユニットの配列
	Game_BattleDoll						dolls[MAX_BATTLEDOLL];
	int									dollsNum;	// 味方ユニットの最大数（戦闘不能者含む）
	// 敵ユニットの配列
	Game_BattleEnemy					enemies[MAX_BATTLEENEMY];
	int									enemiesNum;	// 敵ユニットの最大数（戦闘不能者含む）
	// 攻撃コマンドの配列
	Game_UnitCommand					commands[MAX_UNITCOMMAND+1];
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
	// 人形の特技リストウィンドウ
	BWindow_DollSkill					w_dollSkill;
	// 敵の選択ウィンドウ
	BWindow_SelectEnemy					w_selectEnemy;
	// 敵のフォーカスウィンドウ
	BWindow_FocusedUnit					w_focusedEnemy;
	// 人形の情報を表示するウィンドウ
	Window_SimpleDollStatus				w_simpleDollStatus;
	// 情報表示用ウィンドウの状態。
	// 0なら開いていない、それ以外なら開いている。
	BYTE								infoWindowID;
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
	virtual void Draw() const;

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

	// シーンを終了する。
	// どのシーンに移動するかは様々な変数によって決める。
	int GetNextScene();

	// 次のフェイズに移行した際の処理。
	// 関数NextPhazeから実行される。
	// 各フェイズごとに実行するアクションをセットする。
	void SetupPreBattle();		// PRE_BATTLEになった時
	void SetupAliceCommand();	// アリスのコマンドウィンドウを開く
	void SetupAliceCommandDo(); // アリスのコマンドを実行する
	void SetupDollsCommand();	// 人形のコマンドウィンドウを開く 
	void SetupEnemiesCommand();	// 敵のコマンドを決定する。(即座に終わる)
	void SetupBeforeSort();		// ソート前のコマンド判定を行う。
	void SetupAfterSort();		// ソート後、ターン開始時。ステートの判定など。
	void SetupBattleDo();		// 戦闘。
	void SetupAfterTurn();		// ターン終了時。ステートの判定など。
	void SetupPostBattle();		// 戦闘終了時。battleResultの内容によって分岐。


	// 必要なオブジェクト群のアップデートを行う。
	void UpdateObjects();
	
	// 人形の配列が変わった際に、人形スプライトに人形を割り当て直す。
	bool AttachDollPtrToSprite();

	// 戦闘が終わっていないかを判断する。
	bool CheckBattleResult();

	// 情報ウィンドウを閉じる。
	// 現在のinfoWindowの値に応じ、開かれているものを閉じる。
	void CloseInfoWindow();

	//=========================================
	// アクセサ関連
	// ソースファイルに記述するものはScene_Battle.cppに記述する。
	int GetDollsNum(){ return dollsNum; } ;
	int GetEnemiesNum(){ return enemiesNum; };

	// 人形のポインタを取得する。
	Game_BattleDoll*	GetDollPtr(int index){
		if(index < 0 || index >= MAX_BATTLEDOLL) return NULL;
		if(dolls[index].GetIsUsed()){
			return &dolls[index];
		}else{
			return NULL;
		}
	}

	// 敵キャラのポインタを取得する。
	Game_BattleEnemy*	GetEnemyPtr(int index){
		if(index < 0 || index >= MAX_BATTLEENEMY) return NULL;
		if(enemies[index].GetIsUsed()){
			return &enemies[index];
		}else{
			return NULL;
		}
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

	// 人形へのポインタを渡すと、
	// その人形のスプライトのポインタを返す。
	Sprite_BattleDoll* GetDollSprite(Game_BattleDoll* dollPtr);

	// 敵へのポインタを渡すと、
	// その敵のスプライトのポインタを返す。
	Sprite_BattleEnemy* GetEnemySprite(Game_BattleEnemy* enemyPtr);




	// 各種ウィンドウを開く。
	// 他のウィンドウからの参照などの形。

	// 敵選択ウィンドウ
	BYTE	OpenSelectEnemyWindow();
	int		GetSelectEnemyIndex(){ return w_selectEnemy.GetSelectIndex(); };
	BWindow_SelectEnemy*	GetWndSelectEnemyPtr(){ return &w_selectEnemy; };
	BYTE	OpenFocusedEnemyWindow();
	int		GetFocusedEnemyIndex(){ return w_focusedEnemy.GetSelectIndex(); };
	BWindow_FocusedUnit*	GetWndFocusedUnitPtr(){ return &w_focusedEnemy; };
	BYTE	OpenDollSkillWindow();
	int		GetDollSkillIndex(){ return w_dollSkill.GetSelectIndex(); };
	BWindow_DollSkill*		GetWndDollSkillPtr(){ return &w_dollSkill; };

	// メッセージウィンドウへのメッセージの追加。
	bool AddStockMessage(LPTSTR str){
		return w_battleMsg.AddStockMsg(str, strlen(str));
	}

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

	bool Action_Damage(Game_BattleAction* pAction);
	bool Action_Heal(Game_BattleAction* pAction);
	bool Action_CallEnemyName();
	bool Action_CallVictory();
	bool Action_CallLose();
	bool Action_AssertAttack(Game_BattleAction* pAction);
	bool Action_AssertSkill(Game_BattleAction* pAction);
	bool Action_AssertGuard(Game_BattleAction* pAction);

	//=========================================
	// Game_UnitCommandの内容の処理。
	// Scene_Battle_Command.cppに記述する。

	// commandPhaze :
	// 例えば通常攻撃にせよ、
	// 実際の攻撃前に行われる判定（防御をしているキャラクターの防御力補正とか）や
	// 攻撃後に行われる判定（次の攻撃のみパワーアップのステートなど）がある。
	// 一つのUnitCommandの解釈を、いくつかのフェイズごとに管理するための
	// パラメータ。Static_Battle.h内のCOMMANDPHAZE_xxx定数群で定義される。
	// 
	char InterpretCommand(Game_UnitCommand* pCmd, int commandPhaze=COMMANDPHAZE_NOPHAZE);
	// commandPhazeによって分岐する
	// 戻り値 :
	// -1 : エラー
	// 0 : 何も処理を行わなかった/コマンド実行を待つ必要がない（即座に次のフェイズへ）
	// 1 : 処理を行った（コマンド実行を待つ）
	// 何か処理を行った場合はtrueを、
	// 何も処理を行わなかった場合はfalseを返す。
	char InterpretCommand_NoPhaze(Game_UnitCommand* pCmd);
	char InterpretCommand_Before_Sort(Game_UnitCommand* pCmd);
	char InterpretCommand_After_Sort(Game_UnitCommand* pCmd);
	char InterpretCommand_Fix_Command(Game_UnitCommand* pCmd);
	char InterpretCommand_Fix_Target(Game_UnitCommand* pCmd);
	char InterpretCommand_Assert(Game_UnitCommand* pCmd);
	char InterpretCommand_Pre_Action(Game_UnitCommand* pCmd);
	char InterpretCommand_Action(Game_UnitCommand* pCmd);
	char InterpretCommand_Check_Death(Game_UnitCommand* pCmd);
	char InterpretCommand_Post_Action(Game_UnitCommand* pCmd);

	//=========================================
	// 戦闘中の諸演算
	// Scene_Battle_Calc.cppに記述する。

	// コマンドを追加する。
	bool SetCommand(Game_UnitCommand cmd);
	
	// コマンドを一つ取り除く。
	bool RemoveOneCommand();

	// 敵のコマンドを自動で追加する。
	// 内部でSetEnemyCommandを使用する。
	bool SetEnemyCommands();

	// 現在アクティブなコマンドウィンドウをキャンセル出来るかを取得する。
	bool GetCommandWindowIsCancelable(int currentIndex);

	// ポインタを使用し、敵のコマンドを算出する。
	Game_UnitCommand GetEnemyCommand(Game_BattleEnemy* pEnemy);

	// 指定した敵のあるコマンドの優先順位を返す。
	// (インデックスに相当するコマンドが存在しない場合、
	//  また、行動条件を満たさない場合は0を返す。)
	int GetEnemyCommandPriority(Game_BattleEnemy* pEnemy, int index);

	// 全ての行動の中で最大の優先度を持つ行動の優先度の値を返す。
	int GetEnemyCommandMaxPriority(Game_BattleEnemy* pEnemy);

	// 指定した敵のあるコマンドから
	// 実行するコマンドを作成する。
	Game_UnitCommand MakeEnemyCommand(Game_BattleEnemy* pEnemy, int index);

	// 戦闘行動のソートを行う。
	bool SortUnitCommands();
	
	// commandsの内容を全てクリアする。
	void ClearCommands();

	// InterpretCommand_Action内でのみ使用される。
	// 使用者、ターゲット、パラメータを与えることで
	// ダメージを与える行動の成否を判断する。
	// 戻り値がその判断。
	BYTE CheckDamageAction(Game_BattleUnit* pActor, Game_BattleUnit* pTarget, int param);
	

	// ダメージ計算。
	// オプションを指定することで、通常攻撃以外のダメージ計算にも対応する。
	int CalcDamage(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent, int param);

	// 回復計算。
	// オプションを指定することで、スキル以外の回復量計算にも対応する。
	int CalcHeal(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent, int param);

	// ある属性に対してある属性が有利か不利かを返す。
	// 0 : 普通
	// 1 : 有利
	// 2 : 不利
	BYTE GetAttrAffinity(BYTE attackerAttr, BYTE opponentAttr);

	// 属性ダメージの倍率を計算する。
	float GetAttrRate(BYTE attackerAttr, BYTE opponentAttr);

	// ユニットにステートを割り当てる。
	// pUnit		: 割り当てるユニット
	// stateRefID	: ステートのID
	// showMessage	: メッセージを表示するか否か
	// level		: ステートレベル
	BYTE AddStateToUnit(Game_BattleUnit* pUnit, WORD stateRefID,
		bool showMessage=true, int level=1);

	// ステートのターン経過を処理する。
	// 一括してターン終了時に行う。
	void UpdateStateTurn();

	//=========================================
	// 描画
	// 下記の関数はScene_Battle_Draw.cppに記述する。

	// 背景を描画する。
	void DrawBG() const;

	// 人形のスプライトを描画する。
	void DrawDollsSprite() const;
	// 敵キャラのスプライトを描画する。
	void DrawEnemiesSprite() const;

	// 画面前景などを描画する。
	void DrawBattleInfo() const;

};

#endif // SCENE_BATTLE_H