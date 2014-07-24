// Scene_Camp.cpp

#include "Scene_Camp.h"
#include "DXFont.h"
#include "Func_Math.h"
#include "Func_AliceFile.h"
#include "TempData.h"
#include "WindowSkin.h"
#include <DxLib.h>

extern DXFont		g_font;
extern TempData		g_temp;
extern WindowSkins		g_wndSkins;

Scene_Camp::Scene_Camp():Scene_Base(),
	s_main(MAX_CAMP_MENU), infoIndex(CAMP_INFO_NONE), infoTime(0){
}

bool Scene_Camp::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	for(int n=0; n<MAX_CAMP_MENU; n++){
		menu_anime1[n] = 0;
		menu_anime2[n] = 0;
	}

	// �E�B���h�E�̏�����
	InitWindow();
	// �V�[���X�e�[�g�̐ݒ�
	SetState(SCNSTATE_CAMP_CHOOSEMENU);

	return true;
}

bool Scene_Camp::Terminate(){

	return true;
}

bool Scene_Camp::InitWindow(){
	WINDOWAREA	frameArea(0, 0, 300, 300);
	WINDOWAREA	contentArea(16, 16, 300-32, 300-32);
	WINDOWFONT	font(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4,
		WINDOWFONT_DEFCOLOR, WINDOWFONT_DEFICOLOR, WINDOWFONT_DEFNCOLOR);
		
	// �͂��E�������E�B���h�E�̏�����
	w_yesno.Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, contentArea, font,
		true);
	w_yesno.SetTitle(_T("�Q�[�����I�����܂����H"), g_font.hInfo);
	w_yesno.SetPositionH(WND_WIDTH/2);		// ��ʒ����ɑ�����
	w_yesno.SetPositionV(WND_HEIGHT/2);
	return true;
}

int Scene_Camp::Update(){
	if(!SceneIsReserved()){
		switch(state){
		case SCNSTATE_CAMP_CHOOSEMENU:
			switch(s_main.Move()){
			case SELECT_CHOOSE:
				switch(s_main.index){
				case CAMP_MENU_CREATE:
					ReserveScene(SCENE_DOLLCREATE, 20);
					break;
				case CAMP_MENU_SAVE:
					// �Z�[�u���s��
					if(SaveGame(g_temp.fileIndex)){
						SetInfo(CAMP_INFO_SAVE);
					}
					break;
				case CAMP_MENU_EXIT:
					// �㏑�����邩�ǂ����̊m�F
					SetState(SCNSTATE_CAMP_ASKQUITGAME);
					w_yesno.SetVisible(true);
					w_yesno.Open();
					break;
				}
				break;
			}
			break;
		case SCNSTATE_CAMP_ASKQUITGAME:
			w_yesno.Update();
			if(w_yesno.GetState() == Window_Base::CLOSED){
				// ���肳�ꂽ�ꍇ
				switch(w_yesno.GetResult()){
				case WINDOW_YESNO_YES:
					// LoadGame(s_file.index+1);
					ReserveScene(SCENE_TITLE, 120);
					break;
				case WINDOW_YESNO_NO:
					SetState(SCNSTATE_CAMP_CHOOSEMENU);
					break;
				}
			}
			break;
		}
	}

	// ���j���[�̃A�j���[�V����
	for(int n=0; n<MAX_CAMP_MENU; n++){
		// �A�j��1
		// �t�H�[�J�X�������Ă��鎞�̓v���X�A
		// �t�H�[�J�X���O���ƃ}�C�i�X�ɂȂ�
		if(s_main.index == n){
			menu_anime1[n] += (WORD)(0.1*(CAMP_ANIME1_TIME-menu_anime1[n]));
		}else{
			menu_anime1[n] = (WORD)(0.2*menu_anime1[n]);
		}
		// �A�j��2
		// �t�H�[�J�X�������������A�A�j���[�V�������J�n����B
		// �t�H�[�J�X�Ɋւ�炸�A�j���[�V�������s���B
		if(s_main.index == n && menu_anime2[n]==0){
			menu_anime2[n] = 1;
		}
		if(menu_anime2[n] > 0){
			menu_anime2[n]++;
			if(menu_anime2[n] >= CAMP_ANIME2_TIME){
				if(s_main.index == n){
					// �A�j���[�V�������I����Ă�
					// �܂��t�H�[�J�X���������Ă���ꍇ
					menu_anime2[n] = CAMP_ANIME2_TIME;
				}else{
					// �t�H�[�J�X���O��Ă���
					menu_anime2[n] = 0;
				}
			}
		}
	}
	// ��ʉ����̏��̍X�V
	if(infoTime > 0){
		infoTime++;
		if(infoTime > CAMP_INFO_TIME){
			infoTime = 0;
			infoIndex = 0;
		}
	}

	return SCENE_NONE;
}

void Scene_Camp::Draw() const{
	int w; // �`�悷�镶���̕�

	// ���j���[�̕���
	TCHAR menuString[MAX_CAMP_MENU][64] = {
		_T("�_���W�����ցi�������j"),
		_T("�`�[���Ґ��i�������j"),
		_T("�l�`�̍쐬�i�������j"),
		_T("�Z�[�u"),
		_T("�Q�[�����I���i�^�C�g���ɖ߂�j")};

	// ���̕���
		TCHAR infoString[MAX_CAMP_INFO][128] = {
			_T("�f�[�^���Z�[�u���܂����B"),
			_T("�x�����Ė��͂��񕜂��܂����B")
		};

	// �e���j���[��`�悷��
	for(int n=0; n<MAX_CAMP_MENU; n++){
		// menu_anime1�͍ő�1000
		// menu_anime2�͍ő�10
		DrawStringToHandle(
			100-0.04*menu_anime1[n],
			80+60*n,
			menuString[n],
			(n == s_main.index 
			? (menu_anime2[n] == 0 
				? GetColor(255, 255, 255) 
				: GetColor(255, 255, PARAM(30*menu_anime2[n])))
			: GetColor(96, 96, 96)),
			g_font.hInfo, 0, 0);

	}

	// �E�B���h�E�̕`��
	w_yesno.Draw();

	// ��ʉ��̏��̕`��
	if(infoIndex != CAMP_INFO_NONE && infoIndex <= MAX_CAMP_INFO){
		w = GetDrawFormatStringWidthToHandle(g_font.hInfo, infoString[infoIndex-1]);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,
			min(infoTime*60, 6*PARAM(CAMP_INFO_TIME-infoTime)));
		DrawStringToHandle((WND_WIDTH-w)/2, WND_HEIGHT-80, 
			infoString[infoIndex-1], GetColor(255, 255, 255),
			g_font.hInfo);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawReserveFade();
}

