// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"
#include "Window_Text.h" // �萔���g�p
#include "Func_AliceFile.h"
#include "WindowSkin.h"

extern DXFont		g_font;
extern TempData		g_temp;		// �GID���w�肷��̂Ɏg�p
extern AliceFile_140816		g_trialAliceFile;
extern WindowSkins	g_wndSkins;

Scene_TestBattle::Scene_TestBattle():Scene_Base(), s_main(TESTBATTLE_SELECT_NUM){

}

bool Scene_TestBattle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// �V�[���J�n���Ƀf�[�^���Z�[�u����
	g_trialAliceFile.Save();

	// �ŏ��̏ꍇ�̓E�B���h�E���J��
	if(!g_trialAliceFile.data.firstHint){
		if(!OpenHintWindow()){
			return false;
		}
	}

	return true;
}

bool Scene_TestBattle::Terminate(){

	return true;
}

int Scene_TestBattle::Update(){
	if(w_hint.GetClosed()){
		switch(s_main.Move()){
		case SELECT_CHOOSE:
			if(s_main.index < MAX_TESTBATTLE){
				g_temp.battleType = TEMP_BTYPE_TUTORIAL;
				g_temp.battleID = s_main.index+1;
				// �`���[�g���A���퓬��ID���w��
				g_temp.enemyGroup = s_main.index+1;
				ReserveScene(SCENE_BATTLE, 60);
				break;
			}else{
				if(s_main.index == MAX_TESTBATTLE){
					OpenHintWindow();
				}
				if(s_main.index == TESTBATTLE_SELECT_NUM-1){
					ReserveScene(SCENE_END, 60);
				}
			}
			break;
		case SELECT_CANCEL:
			s_main.index = TESTBATTLE_SELECT_NUM-1;
			break;
		}
	}
	// �E�B���h�E�̍X�V
	w_hint.UpdateA();

	return SCENE_NONE;
}

void Scene_TestBattle::Draw() const{
	TCHAR	battleTitle[MAX_TESTBATTLE][128] = {
		_T("Battle1 �͂��߂̂�����"), 
		_T("Battle2 �l�`�ƓG�̑���"), 
		_T("Battle3 �X�e�[�^�X���m�F����"), 
		_T("Battle4 ���͂ƋZ�I"), 
		_T("Battle5 ���͂ƋZ�I�E�����"), 
		_T("Battle6 �A���X�̖���"), 
		_T("Battle7 �A���X�̖��́E�����"), 
		_T("Battle8 �G�̍U���p�^�[��"), 
		_T("Battle9 �G�̍U���p�^�[���E�����"), 
		_T("Battle10 �{�X��ɒ�����"), 
	};

	TCHAR	menuTitle[MAX_TESTBATTLE_MENU][128] = {
		_T("�����E�B���h�E�̍ĕ\��"), 
		// _T("�N���W�b�g"), 
		_T("�Q�[�����I������"), 
	};

	int color;
	for(int n=0; n<TESTBATTLE_SELECT_NUM; n++){
		if(s_main.index == n){
			if(g_trialAliceFile.data.tutorialBattle[n]){
				color = 0x00ffff40;
			}else{
				color = WINDOWFONT_DEFCOLOR;
			}
		}else if(s_main.isActive[n]){
			if(g_trialAliceFile.data.tutorialBattle[n]){
				color = 0x00d0d090;
			}else{
				color = WINDOWFONT_DEFICOLOR;
			}
		}else{
			color = WINDOWFONT_DEFNCOLOR;
		}
		if(n < MAX_TESTBATTLE){
			DrawStringToHandle(80, 50+30*n, battleTitle[n], color, 
				g_font.hInfo);
		}else{
			DrawStringToHandle(80, 50+30*n, menuTitle[n-MAX_TESTBATTLE], color, 
				g_font.hInfo);
		}
	}

	// �E�B���h�E�̕`��
	if(!w_hint.GetClosed()){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, WND_WIDTH, WND_HEIGHT, GetColor(0, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if(w_hint.GetState() == Window_Base::CLOSING){
		g_trialAliceFile.data.firstHint = true;
	}
	w_hint.Draw();

	// �V�[���؂�ւ��̃t�F�[�h�̕`��
	DrawReserveFade();
}

bool Scene_TestBattle::OpenHintWindow(){
	return w_hint.OpenAndPlay(_T("dat_text\\tutorial_first.txt"), WND_HINT_ALICE);
}


