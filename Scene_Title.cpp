// Scene_Title.cpp

#include "Scene_Title.h"
#include "DXFont.h"
#include "TempData.h"
#include "Func_AliceFile.h"

extern DXFont		g_font;
extern TempData		g_temp;

Scene_Title::Scene_Title():Scene_Base(), s_main(MAX_TITLE_MENU){
}

bool Scene_Title::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// �Z�[�u�t�@�C��������Α�������Ɉړ�����
	bool canContinue = false;
	for(int n=0; n<MAX_SAVEFILE; n++){
		if(GetGameFileIsExist(n+1)){
			canContinue = true;
		}
	}
	if(canContinue){
		s_main.index = TITLE_MENU_CONTINUE;
	}else{
		s_main.index = TITLE_MENU_NEWGAME;
		s_main.isActive[TITLE_MENU_CONTINUE] = false;
	}
	return true;
}

bool Scene_Title::Terminate(){

	return true;
}

int Scene_Title::Update(){
	if(!SceneIsReserved()){
		switch(s_main.Move()){
		case SELECT_CHOOSE:
			switch(s_main.index){
			case TITLE_MENU_NEWGAME:
				g_temp.sceneParam = TEMP_PARAM_FILE_NEWGAME;
				ReserveScene(SCENE_FILE, 20);
				break;
			case TITLE_MENU_CONTINUE:
				g_temp.sceneParam = TEMP_PARAM_FILE_LOADMODE;
				ReserveScene(SCENE_FILE, 20);
				break;
			case TITLE_MENU_EXIT:
				ReserveScene(SCENE_END, 90);
				break;
			}
			break;
		case SELECT_CANCEL:
			// �C���f�b�N�X��EXIT�ɍ����Ă��鎞�͏I������A
			// �����Ŗ����ꍇ��EXIT�ɍ��킹��
			if(s_main.index == TITLE_MENU_EXIT){
				ReserveScene(SCENE_END, 90);
			}else{
				s_main.index = TITLE_MENU_EXIT;
			}
			break;
		}
	}
	return SCENE_NONE;
}

void Scene_Title::Draw() const{
	TCHAR menuString[MAX_TITLE_MENU][64] = {
		_T("�͂��߂���"),
		_T("�Â�����"),
		_T("�Q�[�����I��")};
	
	// �e���j���[��`�悷��
	for(int n=0; n<MAX_TITLE_MENU; n++){
		DrawStringToHandle(0, 60*n, menuString[n],
			(n == s_main.index ? GetColor(255, 255, 255) : GetColor(96, 96, 96)),
			g_font.hInfo, 0, 0);
	}

	// �V�[���؂�ւ��̃t�F�[�h�̕`��
	DrawReserveFade();
}

