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
		_T("���͂ƋZ�I"), 
		_T("���͂ƋZ�I�E�����"), 
		_T("�A���X�̖���"), 
		_T("�A���X�̖��́E�����"), 
		_T("�G�̍U���p�^�[��"), 
		_T("�G�̍U���p�^�[���E�����"), 
		_T("�{�X��ɒ�����(������)"), 
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

