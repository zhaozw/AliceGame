// main.cpp

// MyGameFormat
// �Q�[�������ۂ̃t�H�[�}�b�g���쐬���܂��B

// �ŏ��̃V�[�����w�肷��B
#define FIRST_SCENE (SCENE_TESTBATTLE)

// DX���C�u�����̃C���N���[�h
#include "DxLib.h"
#include "Common_Macro.h"

// �Q�[���Ɋւ���ݒ�̃C���N���[�h
#include "Static_Game.h"
#include "Static_CompileMode.h"


// �e���\�[�X�̃w�b�_�t�@�C��
#include "Image.h"
#include "Sound.h"
#ifdef MYGAME_USE_FONT
#include "DxFont.h"
#endif // MYGAME_USE_FONT
#include "WindowSkin.h"
#include "TempData.h"

// �Q�[���̐ݒ�֘A�̃w�b�_�t�@�C��
#include "Config.h"
#include "KeyConfig.h"

// �e�V�[���̃w�b�_�t�@�C��
#include "Scene_Base.h"
#include "Scene_Sample.h"
#include "Scene_Title.h"	// �^�C�g�����
#include "Scene_File.h"		// �t�@�C���̃Z�[�u�y�у��[�h���s��
#include "Scene_Camp.h"		// �L�����v
#include "Scene_DollCreate.h"		// �l�`�̍쐬
#include "Scene_DollBirth.h"		// �l�`�̒a��
#include "Scene_Battle.h"			// �퓬
#include "Scene_TestBattle.h"		// �e�X�g�o�g���̑I��



// �c�[���֘A�̃w�b�_�t�@�C��
#include "MyTaskList.h"
#include "Selectable.h"

// �Q�[���I�u�W�F�N�g�̂����A�O���[�o���ϐ��Ƃ��Ĉ�������
#include "Game_AliceInfo.h"
#include "Game_DollList.h"

// �f�[�^�I�u�W�F�N�g
#include "Data_DollParam.h"
#include "Data_EnemyParam.h"
#include "Data_EnemyGroup.h"
#include "Data_EnemyDraw.h"
#include "Data_BattleState.h"

// ��ŏ���
#include "GlobalData.h"

// �O���[�o���ϐ��̐錾
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

// ���Scene_Sample�ƈꏏ�ɏ���
GlobalData	g_dat;

// �V�[���Ԃ��f�[�^�ł��Ƃ肷��ۂ̕ϐ���ێ�
TempData	g_temp;

// �I�u�W�F�N�g�̂����A�O���[�o���ϐ��Ƃ��ĕ\����������
Game_AliceInfo	g_aliceInfo;
Game_DollList	g_dollList;

// �f�[�^�x�[�X�N���X
Data_DollParam		d_dollParam;
Data_EnemyParam		d_enemyParam;
Data_EnemyGroup		d_enemyGroup;
Data_EnemyDraw		d_enemyDraw;
Data_BattleState	d_battleState;

int			hDrawWindow;	// �`��p��ʂ̃n���h���B
							// �`����e�͂����ɕ`�悵�����̂�
							// ���ۂ̉�ʃT�C�Y�ɍ��킹�ĕ`�悷��B
#ifdef MYGAME_USE_LUA
lua_State*	L;
#endif // MYGAME_USE_LUA

// WinMain�̓��e���L�q�����֐��̐錾
bool WinMain_Initialize();
bool WinMain_LoadResource();
bool WinMain_ReleaseResource();
bool WinMain_PlayScene();
bool WinMain_Terminate(bool loopResult);

bool WinMain_Initialize(){
	//============================================
	// �Í���

#ifdef MYGAME_PERFORM_ENCODING
	// �Í��������s���ďI������
	if(!Perform_Encoding()){
		return -1;
	}
	return 0;
#endif // MYGAME_PERFORM_ENCODING

	// DX���C�u�����̃A�[�J�C�u���g�p����
#ifdef MYGAME_USE_ENCODED_DATA
	SetUseDXArchiveFlag(TRUE);
	SetDXArchiveExtension(ARCHIVE_EXTENSION));
#endif // MYGAME_USE_ENCODED_DATA

#ifdef MYGAME_USE_CHECKMEMORY	
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // MYGAME_USE_CHECKMEMORY

	// ���P�[���̐ݒ�
	setlocale(LC_ALL, _T("JPN"));
	
	// �ݒ�
#ifdef MYGAME_USE_CONFIG
	// �����ݒ�̓ǂݍ���
	// �N���I�v�V�����̕\�����܂�
	if(!g_cfg.LoadConfig()){ // �t���X�N���[�����̊m�F�������ōs��
		MessageBox(NULL, TEXT("�ݒ�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
		return false;
	}
#else  // MYGAME_USE_CONFIG
	g_cfg.SetWindowSize();
#endif // MYGAME_USE_CONFIG

#ifdef MYGAME_USE_KEYCONFIG
	// �L�[�R���t�B�O�̃��[�h
	if(!g_key.LoadKeyConfig()){ // 
		MessageBox(NULL, TEXT("�L�[�ݒ�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
		return false;
	}
#else  // MYGAME_USE_KEYCONFIG	// �E�B���h�E�T�C�Y�̐ݒ�̂�
	g_key.ResetConfig();
#endif // MYGAME_USE_KEYCONFIG

	// �o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);
	// �^�C�g��
	SetMainWindowText(WND_TITLE);
	// Z�o�b�t�@�͎g�p���Ȃ�
	SetUseZBuffer3D(FALSE);
	// �X�N���[�����[�h�̐ݒ�
	if(!g_cfg.SetScreenMode()) return -1;
	// ��d�N���̋֎~
	SetDoubleStartValidFlag(FALSE);

	// DX���C�u�����̏�����
	if(DxLib_Init() == -1){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�Q�[���̏������Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
		return -1; // �G���[�I��
#endif // MYGAME_USE_WARN_ERROR
	}

	//=====================================
	// �`��p��ʂ̍쐬
	SetDrawValidGraphCreateFlag(TRUE);
	hDrawWindow = MakeScreen(WND_WIDTH, WND_HEIGHT);
	SetDrawValidGraphCreateFlag(FALSE);
	SetUseBackCulling(TRUE);

	// �V�t�g�Ȃǂ̃L�[���{�^���Ɋ��蓖��
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_11, KEY_INPUT_LSHIFT);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_12, KEY_INPUT_RSHIFT);

#ifdef MYGAME_USE_LUA
	// Lua��VM���쐬����
	L = lua_open();
	// Lua�̕W�����C�u�������J��
	luaL_openlibs(L);
#endif // MYGAME_USE_LUA
	return true;
}

bool WinMain_PlayScene(){
	// ���݂̃V�[��ID
	int sceneID = FIRST_SCENE;
	// �V�[�����w���|�C���^
	Scene_Base* scene = NULL;

	// �Q�[���̃��[�v�Ɏg�p����
	bool isOK = true;
	// �G���[�����������ꍇtrue�ɂȂ�
	bool isError = false;
	
	bool procMsg = false; // ProcessMessage��-1�̎���true��
	while(sceneID != SCENE_ERROR && isOK && !isError && !procMsg){
		if(ProcessMessage() != 0){
			procMsg = true;
		}else{
			////////////////////////////////
			// ���̃V�[���̌���
			////////////////////////////////
			// �V�[���̃N���A
			SAFE_DELETE(scene);
			// sceneID�ŕ���B
			// ���[�h��ʂƃZ�[�u��ʂȂǁA�����V�[���𕡐��p�^�[����
			// �g��������ꍇ�͂����ł����̃p�����[�^���w�肷��B
			// �R���X�g���N�^�𗘗p�B
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
			// �V�[���̎��s
			////////////////////////////////
			if(sceneID == SCENE_NONE) isError = true; // �V�[�������݂��Ȃ�
			do{
				if(isError || !isOK){
					break;
				}
				// ����������
				ErrorLogAdd(_T("�V�[���̏����������s���܂��B\n"));
				if(!scene->Initialize(g_cfg.skipFrame)){
					ErrorLogAdd(_T("�V�[���̏������ŃG���[���������܂����B\n"));
					isError = true;
					break;
				}
				// ���ۂ̎��s
				ErrorLogAdd(_T("�V�[���̓��e�����s���܂��B\n"));
				sceneID = scene->Play();
				if(sceneID == SCENE_ERROR || sceneID == SCENE_NONE){
					ErrorLogAdd(_T("�V�[���̓����ŃG���[���������܂����B\n"));
					isError = true;
					break;
				}
				// ����������
				ErrorLogAdd(_T("�V�[���̏I�����������s���܂��B\n"));
				if(!scene->Terminate()){
					ErrorLogAdd(_T("�V�[���̏I�������ŃG���[���������܂����B\n"));
					isError = true;
					break;
				}
				ErrorLogAdd(_T("�V�[�����������������܂����B\n"));
			}while(0);
		}
	}
	// �V�[���̊J���i�r���Ő؂����ꍇ�Ȃǁj
	SAFE_DELETE(scene);

	return !isError;
}

bool WinMain_Terminate(bool playResult){
	bool result = playResult;

	// �`��p��ʂ̊J��
	DeleteGraph(hDrawWindow);

	// DX���C�u�����̏I��
	DxLib_End();

	return result;
}

bool WinMain_LoadResource(){
	//////////////////////////
	// ���\�[�X�̃��[�h

	// �摜
	if(!g_image.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�摜�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		 return false;
	}
	
	// �E�B���h�E�X�L���ւ̉摜���蓖��
	if(!g_wndSkins.AttachImages()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�E�B���h�E�X�L���̊��蓖�ĂɎ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		 return false;
	}

	// BGM
	if(!g_sound.LoadMusic()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("BGM�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// ���ʉ�
	if(!g_sound.LoadSound()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("���ʉ��̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// �t�H���g
	if(!g_font.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�t�H���g�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}	

	// �f�[�^�x�[�X�Q
	if(!d_dollParam.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�l�`�f�[�^�x�[�X�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyParam.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�G�f�[�^�x�[�X�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyGroup.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�G�O���[�v�f�[�^�x�[�X�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_enemyDraw.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�G�O���t�B�b�N�f�[�^�x�[�X�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	if(!d_battleState.Load()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�X�e�[�g�f�[�^�x�[�X�̓ǂݍ��݂Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}

	// �^�X�N�Q
	if(!Create_MyTaskList()) return false;

	return true;
}

bool WinMain_ReleaseResource(){
	// Lua�̉��
#ifdef MYGAME_USE_LUA
	lua_close(L);
#endif // MYGAME_USE_LUA

	// �^�X�N�Q
	if(!Release_MyTaskList()) return false;

	// �t�H���g
	if(!g_font.Release()){
#ifdef MYGAME_USE_WARN_ERROR
		MessageBox(NULL, TEXT("�t�H���g�̉���Ɏ��s���܂����B"),
		TEXT("�G���["), MB_OK|MB_ICONWARNING);
#endif // MYGAME_USE_WARN_INIERROR		
		return false;
	}	
	return true;

}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// �Q�[���̏�����
	if(!WinMain_Initialize()) return -1;
	// ���\�[�X��ǂݍ���
	if(!WinMain_LoadResource()) return -1;
	// ���C�����[�v����яI������
	if(!WinMain_Terminate(WinMain_PlayScene())){
		WinMain_ReleaseResource();
		return -1;
	}
	WinMain_ReleaseResource();
#ifdef MYGAME_USE_CHECKMEMORY
	// ���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
	_CrtDumpMemoryLeaks();
#endif // MYGAME_USE_CHECKMEMORY	

	return 0;
}
