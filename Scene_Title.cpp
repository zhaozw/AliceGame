// Scene_Title.cpp

#include "Scene_Title.h"
#include "DXFont.h"
#include "TempData.h"
#include "Func_AliceFile.h"
#include "Record_AliceInfo.h"

extern DXFont				g_font;
extern TempData				g_temp;
extern Record_AliceInfo		r_aliceInfo;

Scene_Title::Scene_Title():Scene_Base(),
s_main(MAX_TITLE_MENU), s_chapter(MAX_CHAPTER-1, 0, false, true) {
	phaze = TITLE_PHAZE_MAIN;
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

	// �I�����̈ꕔ�𖳌���
	s_main.isActive[TITLE_MENU_STOCKDOLLS] = false;
	s_main.isActive[TITLE_MENU_RECORDS] = false;

	// �N���A���Ă��Ȃ��`���v�^�[�𖳌���


	return true;
}

bool Scene_Title::Terminate(){

	return true;
}

int Scene_Title::Update(){
	if(!SceneIsReserved())
		switch(phaze){
		case TITLE_PHAZE_MAIN:
			switch(s_main.Move()){
			case SELECT_CHOOSE:
				switch(s_main.index){
				case TITLE_MENU_NEWGAME:
					phaze = TITLE_PHAZE_CHAPTER;
					break;
				case TITLE_MENU_CONTINUE:
					g_temp.sceneParam = TEMP_PARAM_FILE_LOADMODE;
					ReserveScene(SCENE_FILE, 20);
					break;
				case TITLE_MENU_STOCKDOLLS:
					ReserveScene(SCENE_TESTBATTLE, 90);
					break;
				case TITLE_MENU_RECORDS:
					ReserveScene(SCENE_TESTBATTLE, 90);
					break;
				case TITLE_MENU_TESTBATTLE:
					ReserveScene(SCENE_TESTBATTLE, 10);
					break;
				case TITLE_MENU_OPTION:
					// ReserveScene(SCENE_TESTBATTLE, 10);
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
			break;
		case TITLE_PHAZE_CHAPTER:
			switch(s_chapter.Move()){
			case SELECT_CHOOSE:
				// ����L�[
				// �͂����肵�ăj���[�Q�[��
				g_temp.sceneParam = TEMP_PARAM_FILE_NEWGAME;
				ReserveScene(SCENE_FILE, 20);
				break;
			case SELECT_CANCEL:
				// �L�����Z���L�[
				phaze = TITLE_PHAZE_MAIN;
				s_main.index = 0;
				break;
			}
			break;
	}
	return SCENE_NONE;
}

void Scene_Title::Draw() const{
	TCHAR menuString[MAX_TITLE_MENU][64] = {
		_T("�͂��߂���"),
		_T("�Â�����"),
		_T("�L���̒��̐l�`"),
		_T("�g���t�B�["),
		_T("�퓬�`���[�g���A����"),
		_T("�I�v�V����"),
		_T("�Q�[�����I��")};

	TCHAR chapterString[MAX_CHAPTER][64] = {
		_T("�d���̖�(��)"),
		_T("�H��̖�(��)"),
		_T("���҂̖�(��)"),
		_T("�����̖�(��)"),
		_T("�A���X�̖�(��)"),
		_T("�e�X�g�v���C�p")
	};
	
	// �e���j���[��`�悷��
	for(int n=0; n<MAX_TITLE_MENU; n++){
		DrawStringToHandle(200, 300+34*n, menuString[n],
			(n == s_main.index ? GetColor(255, 255, 255) : GetColor(96, 96, 96)),
			g_font.hInfo, 0, 0);
	}

	// �V�[���؂�ւ��̃t�F�[�h�̕`��
	DrawReserveFade();
}

