// main.cpp

// MyGameFormat
// ゲームを作る際のフォーマットを作成します。

// 最初のシーンを指定する。
#define FIRST_SCENE (SCENE_TESTBATTLE)

// DXライブラリのインクルード
#include "DxLib.h"
#include "Common_Macro.h"

// ゲームに関する設定のインクルード
#include "Static_Game.h"
#include "Static_CompileMode.h"


// 各リソースのヘッダファイル
#include "Image.h"
#include "Sound.h"
#ifdef MYGAME_USE_FONT
#include "DxFont.h"
#endif // MYGAME_USE_FONT
#include "WindowSkin.h"
#include "TempData.h"

// ゲームの設定関連のヘッダファイル
#include "Config.h"
#include "KeyConfig.h"

// 各シーンのヘッダファイル
#include "Scene_Base.h"
#include "Scene_Sample.h"
#include "Scene_Title.h"	// タイトル画面
#include "Scene_File.h"		// ファイルのセーブ及びロードを行う
#include "Scene_Camp.h"		// キャンプ
#include "Scene_DollCreate.h"		// 人形の作成
#include "Scene_DollBirth.h"		// 人形の誕生
#include "Scene_Battle.h"			// 戦闘
#include "Scene_TestBattle.h"		// テストバトルの選択



// ツール関連のヘッダファイル
#include "MyTaskList.h"
#include "Selectable.h"

// ゲームオブジェクトのうち、グローバル変数として扱うもの
#include "Game_AliceInfo.h"
#include "Game_DollList.h"

// データオブジェクト
#include "Data_DollParam.h"
#include "Data_EnemyParam.h"
#include "Data_EnemyGroup.h"
#include "Data_EnemyDraw.h"
#include "Data_BattleState.h"

// 後で消す
#include "GlobalData.h"

// グローバル変数の宣言
Image		g_image;
Sound		g_sound;
#ifdef MYGAME_USE_FONT
DXFont		g_font;
#endif // MYGAME_USE_FONT
DXInput		g_input;
#ifdef MYGAME_USE_2P
DXInput		g_input_2P;
#endif // MYGAME_USE_2P
Config		g_cfg;
KeyConfig	g_key;
WindowSkins g_wndSkins;

// 後でScene_Sampleと一緒に消す
GlobalData	g_dat;

// シーン間をデータでやりとりする際の変数を保持
TempData	g_temp;

// オブジェクトのうち、グローバル変数として表現されるもの
Game_AliceInfo	g_aliceInfo;
Game_DollList	g_dollList;

// データベースクラス
Data_DollParam		d_dollParam;
Data_EnemyParam		d_enemyParam;
Data_EnemyGroup		d_enemyGroup;
Data_EnemyDraw		d_enemyDraw;
Data_BattleState	d_battleState;

int			hDrawWindow;	// 描画用画面のハンドル。
							// 描画内容はここに描画したものを
							// 実際の画面サイズに合わせて描画する。
#ifdef MYGAME_USE_LUA
lua_State*	L;
#endif // MYGAME_USE_LUA

// WinMainの内容を記述した関数の宣言
bool WinMain_Initialize();
bool WinMain_LoadResource();
bool WinMain_ReleaseResource();
bool WinMain_PlayScene();
bool WinMain_Terminate(bool loopResult);

bool WinMain_Initialize(){
	//============================================
	// 暗号化

#ifdef MYGAME_PERFORM_ENCODING
	// 暗号化だけ行って終了する
	if(!Perform_Encoding()){
		return -1;
	}
	return 0;
#endif // MYGAME_PERFORM_ENCODING

	// DXライブラリのアーカイブを使用する
#ifdef MYGAME_USE_ENCODED_DATA
	SetUseDXArchiveFlag(TRUE);
	SetDXArchiveExtension(ARCHIVE_EXTENSION));
#endif // MYGAME_USE_ENCODED_DATA

#ifdef MYGAME_USE_CHECKMEMORY	
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // MYGAME_USE_CHECKMEMORY

	// ロケールの設定
	setlocale(LC_ALL, _T("JPN"));
	
	// 設定
#ifdef MYGAME_USE_CONFIG
	// 初期設定の読み込み
	// 起動オプションの表示も含む
	if(!g_cfg.LoadConfig()){ // フルスクリーンかの確認もここで行う
		MessageBox(NULL, TEXT("設定の読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
		return false;
	}
#else  // MYGAME_USE_CONFIG
	g_cfg.SetWindowSize();
#endif // MYGAME_USE_CONFIG

#ifdef MYGAME_USE_KEYCONFIG
	// キーコンフィグのロード
	if(!g_key.LoadKeyConfig()){ // 
		MessageBox(NULL, TEXT("キー設定の読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
		return false;
	}
#else  // MYGAME_USE_KEYCONFIG	// ウィンドウサイズの設定のみ
	g_key.ResetConfig();
#endif // MYGAME_USE_KEYCONFIG

	// バックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);
	// タイトル
	SetMainWindowText(WND_TITLE);
	// Zバッファは使用しない
	SetUseZBuffer3D(FALSE);
	// スクリーンモードの設定
	if(!g_cfg.SetScreenMode()) return -1;
	// 二重起動の禁止
	SetDoubleStartValidFlag(FALSE);

	// DXライブラリの初期化
	if(DxLib_Init() == -1){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("ゲームの初期化に失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
		return -1; // エラー終了
#endif // MYGAME_USE_WARN_ERROR
	}

	//=====================================
	// 描画用画面の作成
	SetDrawValidGraphCreateFlag(TRUE);
	hDrawWindow = MakeScreen(WND_WIDTH, WND_HEIGHT);
	SetDrawValidGraphCreateFlag(FALSE);
	SetUseBackCulling(TRUE);

	// シフトなどのキーをボタンに割り当て
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_11, KEY_INPUT_LSHIFT);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_12, KEY_INPUT_RSHIFT);

#ifdef MYGAME_USE_LUA
	// LuaのVMを作成する
	L = lua_open();
	// Luaの標準ライブラリを開く
	luaL_openlibs(L);
#endif // MYGAME_USE_LUA
	return true;
}

bool WinMain_PlayScene(){
	// 現在のシーンID
	int sceneID = FIRST_SCENE;
	// シーンを指すポインタ
	Scene_Base* scene = NULL;

	// ゲームのループに使用する
	bool isOK = true;
	// エラーが発生した場合trueになる
	bool isError = false;
	
	bool procMsg = false; // ProcessMessageが-1の時にtrueに
	while(sceneID != SCENE_ERROR && isOK && !isError && !procMsg){
		if(ProcessMessage() != 0){
			procMsg = true;
		}else{
			////////////////////////////////
			// 次のシーンの決定
			////////////////////////////////
			// シーンのクリア
			SAFE_DELETE(scene);
			// sceneIDで分岐。
			// ロード画面とセーブ画面など、同じシーンを複数パターンで
			// 使い分ける場合はここでそれらのパラメータを指定する。
			// コンストラクタを利用。
			switch(sceneID){
				case SCENE_SAMPLE:
					scene = NEW Scene_Sample();
					break;
				case SCENE_TITLE:
					scene = NEW Scene_Title();
					break;
				case SCENE_FILE:
					scene = NEW Scene_File();
					break;
				case SCENE_CAMP:
					scene = NEW Scene_Camp();
					break;
				case SCENE_DOLLCREATE:
					scene = NEW Scene_DollCreate();
					break;
				case SCENE_DOLLBIRTH:
					scene = NEW Scene_DollBirth();
					break;
				case SCENE_BATTLE:
					scene = NEW Scene_Battle();
					break;
				case SCENE_TESTBATTLE:
					scene = NEW Scene_TestBattle();
					break;
				case SCENE_END:
					isOK = false;
					break;
				default:
					sceneID = SCENE_ERROR;
					isOK = false;
					isError = true;
					break;
			}
			////////////////////////////////
			// シーンの実行
			////////////////////////////////
			if(sceneID == SCENE_NONE) isError = true; // シーンが存在しない
			do{
				if(isError || !isOK){
					break;
				}
				// 初期化処理
				ErrorLogAdd(_T("シーンの初期化を実行します。\n"));
				if(!scene->Initialize(g_cfg.skipFrame)){
					ErrorLogAdd(_T("シーンの初期化でエラーが発生しました。\n"));
					isError = true;
					break;
				}
				// 実際の実行
				ErrorLogAdd(_T("シーンの内容を実行します。\n"));
				sceneID = scene->Play();
				if(sceneID == SCENE_ERROR || sceneID == SCENE_NONE){
					ErrorLogAdd(_T("シーンの内部でエラーが発生しました。\n"));
					isError = true;
					break;
				}
				// 初期化処理
				ErrorLogAdd(_T("シーンの終了処理を実行します。\n"));
				if(!scene->Terminate()){
					ErrorLogAdd(_T("シーンの終了処理でエラーが発生しました。\n"));
					isError = true;
					break;
				}
				ErrorLogAdd(_T("シーンが正しく完了しました。\n"));
			}while(0);
		}
	}
	// シーンの開放（途中で切った場合など）
	SAFE_DELETE(scene);

	return !isError;
}

bool WinMain_Terminate(bool playResult){
	bool result = playResult;

	// 描画用画面の開放
	DeleteGraph(hDrawWindow);

	// DXライブラリの終了
	DxLib_End();

	return result;
}

bool WinMain_LoadResource(){
	//////////////////////////
	// リソースのロード

	// 画像
	if(!g_image.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("画像の読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		 return false;
	}
	
	// ウィンドウスキンへの画像割り当て
	if(!g_wndSkins.AttachImages()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("ウィンドウスキンの割り当てに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		 return false;
	}

	// BGM
	if(!g_sound.LoadMusic()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("BGMの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// 効果音
	if(!g_sound.LoadSound()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("効果音の読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// フォント
	if(!g_font.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("フォントの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}	

	// データベース群
	if(!d_dollParam.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("人形データベースの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyParam.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("敵データベースの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyGroup.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("敵グループデータベースの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyDraw.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("敵グラフィックデータベースの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_battleState.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("ステートデータベースの読み込みに失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// タスク群
	if(!Create_MyTaskList()) return false;

	return true;
}

bool WinMain_ReleaseResource(){
	// Luaの解放
#ifdef MYGAME_USE_LUA
	lua_close(L);
#endif // MYGAME_USE_LUA

	// タスク群
	if(!Release_MyTaskList()) return false;

	// フォント
	if(!g_font.Release()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("フォントの解放に失敗しました。"),
		TEXT("エラー"), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}	
	return true;

}

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// ゲームの初期化
	if(!WinMain_Initialize()) return -1;
	// リソースを読み込む
	if(!WinMain_LoadResource()) return -1;
	// メインループおよび終了処理
	if(!WinMain_Terminate(WinMain_PlayScene())){
		WinMain_ReleaseResource();
		return -1;
	}
	WinMain_ReleaseResource();
#ifdef MYGAME_USE_CHECKMEMORY
	// この時点で開放されていないメモリの情報の表示
	_CrtDumpMemoryLeaks();
#endif // MYGAME_USE_CHECKMEMORY	

	return 0;
}
