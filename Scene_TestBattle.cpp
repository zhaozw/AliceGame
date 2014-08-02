// Scene_TestBattle.cpp

#include "Scene_TestBattle.h"
#include "DxLib.h"
#include "DXFont.h"
#include "TempData.h"
#include "Window_Text.h" // �萔���g�p

extern DXFont		g_font;
extern TempData		g_temp;		// �GID���w�肷��̂Ɏg�p

Scene_TestBattle::Scene_TestBattle():Scene_Base(), s_main(TESTBATTLE_SELECT_NUM){

}

bool Scene_TestBattle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	for(int n=2; n<MAX_TESTBATTLE; n++){
		s_main.isActive[n] = false;
	}
	return true;
}

bool Scene_TestBattle::Terminate(){

	return true;
}

int Scene_TestBattle::Update(){
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
			if(s_main.index == TESTBATTLE_SELECT_NUM-1){
				ReserveScene(SCENE_END, 60);
			}
		}
		break;
	case SELECT_CANCEL:
		s_main.index = TESTBATTLE_SELECT_NUM-1;
		break;
	}
	return SCENE_NONE;
}

void Scene_TestBattle::Draw() const{
	TCHAR	battleTitle[MAX_TESTBATTLE][128] = {
		_T("�͂��߂̂�����"), 
		_T("�l�`�ƓG�̑���"), 
		_T("�X�e�[�^�X���m�F����"), 
		_T("�A���X�̖���"), 
		_T("���͂ƋZ�I"), 
		_T("�퓬�e�X�g6"), 
		_T("�퓬�e�X�g7"), 
		_T("�퓬�e�X�g8"), 
		_T("�퓬�e�X�g9"), 
		_T("�퓬�e�X�g10"), 
	};

	TCHAR	menuTitle[MAX_TESTBATTLE_MENU][128] = {
		// _T("�����X�^�[�}��"), 
		// _T("�N���W�b�g"), 
		_T("�Q�[�����I������"), 
	};

	int color;
	for(int n=0; n<TESTBATTLE_SELECT_NUM; n++){
		if(s_main.index == n){
			color = WINDOWFONT_DEFCOLOR;
		}else if(s_main.isActive[n]){
			color = WINDOWFONT_DEFICOLOR;
		}else{
			color = WINDOWFONT_DEFNCOLOR;
		}
		if(n < MAX_TESTBATTLE){
			DrawStringToHandle(50, 50+30*n, battleTitle[n], color, 
				g_font.hInfo);
		}else{
			DrawStringToHandle(50, 50+30*n, menuTitle[n-MAX_TESTBATTLE], color, 
				g_font.hInfo);
		}
	}
	// �V�[���؂�ւ��̃t�F�[�h�̕`��
	DrawReserveFade();
}

