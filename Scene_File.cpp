// Scene_File.cpp

#include "Scene_File.h"
#include "TempData.h"
#include "Func_AliceFile.h"
#include "DXFont.h"
#include "Window_Selectable.h"
#include "WindowSkin.h"

extern TempData g_temp;
extern DXFont	g_font;
extern WindowSkins g_wndSkins;

Scene_File::Scene_File() : s_file(MAX_SAVEFILE, 0, true, true, 0),
	w_yesno(){
	moving = 0x00;
	movingTime = 0;
	drawIndex = 0;
}

bool Scene_File::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// �ϐ��̏�����
	for(int n=0; n<MAX_SAVEFILE; n++){
		isFile[n] = false;
	}
	// ���݂̃��[�h��ǂݍ��ށB
	mode = g_temp.sceneParam;
	// �e�t�@�C������t�@�C���w�b�_��ǂݍ��ށB
	// �Z�[�u�f�[�^�����݂��Ȃ��t�@�C����isFile��false�ɂ���B
	for(int n=0; n<MAX_SAVEFILE; n++){
		// +1�́A�I������0����n�܂邽��
		if(GetGameFileHeader(&header[n], n+1)){
			isFile[n] = true;
		}
	}
	// �e�t�@�C����I���\�ɂ��邩�ۂ��̔���
	switch(mode){
	case TEMP_PARAM_FILE_NEWGAME:
		// �S�Ẵt�@�C����I���\
		break;
	case TEMP_PARAM_FILE_SAVEMODE:
		// �S�Ẵt�@�C����I���\
		break;
	case TEMP_PARAM_FILE_LOADMODE:
		// �f�[�^�̂Ȃ��t�@�C���͑I��s�\
		for(int n=0; n<MAX_SAVEFILE; n++){
			s_file.isActive[n] = isFile[n];
		}
		break;
	}

	// �E�B���h�E�̏�����
	InitWindow();

	// �V�[���X�e�[�g�̐ݒ�
	SetState(SCNSTATE_FILE_CHOOSEFILE);

	return true;
}

bool Scene_File::Terminate(){
	return true;
}

bool Scene_File::InitWindow(){
	// �͂��E�������E�B���h�E�̏�����
	w_yesno.Setup(
		&g_wndSkins.skin[WNDSKIN_SIMPLE],
		0, 0, g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4,
		true, ALIGN_CENTER);
	w_yesno.SetTitle(_T("�t�@�C�����㏑�����܂����H"));
	w_yesno.SetAllColor(
		GetColor(255, 255, 255),
		GetColor(192, 192, 192),
		GetColor(64, 64, 64));
	w_yesno.SetDefParam();
	w_yesno.SetPositionH(WND_WIDTH/2);		// ��ʒ����ɑ�����
	w_yesno.SetPositionV(WND_HEIGHT/2);
	return true;
}

int Scene_File::Update(){
	switch(GetState()){
	case SCNSTATE_FILE_CHOOSEFILE:
		if(!SceneIsReserved()){
			if(moving == 0){
				switch(s_file.Move()){
				case SELECT_CHOOSE:
					switch(mode){
					case TEMP_PARAM_FILE_NEWGAME:
						if(isFile[s_file.index]){
							// �㏑�����邩�ǂ����̊m�F
							SetState(SCNSTATE_FILE_ASKOVERWRITE);
							w_yesno.SetVisible(true);
							w_yesno.Open();
						}else{
							// �Q�[�������������Ďn�߂�
							g_temp.fileIndex = s_file.index+1;
							// �S�Ẵf�[�^��������
							NewGame();
							ReserveScene(SCENE_CAMP, 90);
						}
						/*
						// �t�@�C���ԍ����w�肵�A�ŏ��̃V�[���ֈړ�
						// +1�́A�I������0����n�܂�̂�␳���邽��
						g_temp.fileIndex = s_file.index+1;
						ReserveScene(SCENE_CAMP, 90);
						*/
						break;
					case TEMP_PARAM_FILE_LOADMODE:
						// �t�@�C���̃��[�h���s���B
						g_temp.fileIndex = s_file.index+1;
						LoadGame(s_file.index+1);
						ReserveScene(SCENE_CAMP, 60);
						break;
					}
					break;
				case SELECT_CANCEL:
					switch(mode){
					case TEMP_PARAM_FILE_NEWGAME:
					case TEMP_PARAM_FILE_LOADMODE:
						// �^�C�g���ɖ߂�
						ReserveScene(SCENE_TITLE, 20);
						break;
					}
					break;
				default:
					// ���ݑI�𒆂̂��̂���ʓ��ɕ\������Ă��邩�ǂ����𔻒肷��B
					if(abs(s_file.lastIndex-s_file.index) > 1){
						// ��ʂ̒[����[�ւ̈ړ�
						if(s_file.index == 0){
							// �t�@�C����������0�ւ̈ړ�
							drawIndex = 0;
							moving = 0x00;
						}else{
							// 0����t�@�C�������ւ̈ړ�
							drawIndex = MAX_SAVEFILE-FILESELECT_FILE_PER_PAGE;
							moving = 0x00;
						}
					}else{
						if(s_file.index >= drawIndex+FILESELECT_FILE_PER_PAGE){
							moving = 0x01;
							movingTime = 0;
						}
						if(s_file.index < drawIndex){
							moving = 0x02;
							drawIndex--;
							movingTime = 0;
						}
					}
					break;
				}
			}else{
				movingTime++;
				if(movingTime >= FILESELECT_SCROLL_TIME){
					if(moving == 0x01){
						drawIndex++;
					}
					moving = 0x00;
					movingTime = 0;
					s_file.lastIndex = s_file.index;
				}
			}
		}
		break;
	case SCNSTATE_FILE_ASKOVERWRITE:
		w_yesno.Update();
		if(w_yesno.GetState() == Window_Base::CLOSED){
			// ���肳�ꂽ�ꍇ
			switch(w_yesno.GetResult()){
			case WINDOW_YESNO_YES:
				// �Q�[�������������Ďn�߂�
				g_temp.fileIndex = s_file.index+1;
				// �S�Ẵf�[�^��������
				NewGame();
				ReserveScene(SCENE_CAMP, 90);
				break;
			case WINDOW_YESNO_NO:
				SetState(SCNSTATE_FILE_CHOOSEFILE);
				break;
			}
		}
		break;
	}
	return SCENE_NONE;
}

void Scene_File::Draw(){
	// �`��\�͈͂̐ݒ�
	SetDrawArea(
		0, DRAW_FILE_BASEY-5,
		400, 
		DRAW_FILE_BASEY+DRAW_FILE_WLH*FILESELECT_FILE_PER_PAGE-DRAW_FILE_MARGINY+5);
	// �e�t�@�C���̕`��
	int baseY = DRAW_FILE_BASEY;
	switch(moving){
	case 1:
		baseY -= DRAW_FILE_WLH*movingTime/FILESELECT_SCROLL_TIME;
		break;
	case 2:
		baseY -= DRAW_FILE_WLH*(FILESELECT_SCROLL_TIME-movingTime)
			/FILESELECT_SCROLL_TIME;
		break;
	}
	int cntN;

	for(int n=0; n<FILESELECT_FILE_PER_PAGE+1; n++){
		cntN = (n+drawIndex+MAX_SAVEFILE)%MAX_SAVEFILE;
		if(isFile[cntN]){
			DrawSaveFile(40, baseY+(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)*n,
				cntN, s_file.index==cntN, s_file.isActive[cntN]);
		}else{
			DrawEmptyFile(40, baseY+(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)*n,
				cntN, s_file.index==cntN, s_file.isActive[cntN]);
		}
	}

	SetDrawArea(0, 0, WND_WIDTH, WND_HEIGHT);
	// �I�𒆂̃t�@�C���̏ڍו\��
	DrawSelectedFile(420, 40, s_file.index);
	// �E�B���h�E�̕`��
	w_yesno.Draw();
	// �V�[���t�F�[�h�̕`��
	DrawReserveFade();
}

void Scene_File::DrawSaveFile(int x, int y, BYTE index,
	bool isActive, bool canSelect) const{
		int	pT, pH, pM, pS;	// �v���C���Ԍv�Z�p�̕ϐ�
		int sT, sY, sM, sD, sH, sMi;	// �Z�[�u���Ԍv�Z�p�̕ϐ�
		// �v���C���Ԃ̌v�Z
		pT = header[index].data.playTime;
		pH = (int)(pT / 3600);
		pT -= pH*3600;
		pM = (int)(pT / 60);
		pT -= pM*60;
		pS = pT;
		// �Z�[�u���Ԃ̌v�Z
		sT = header[index].data.savedYMD;
		sY = (int)(sT / 10000);
		sT -= sY*10000;
		sM = (int)(sT / 100);
		sT -= sM*100;
		sD = sT;
		// �Z�[�u���Ԃ̌v�Z
		sT = header[index].data.savedHMS;
		sH = (int)(sT / 10000);
		sT -= sH*10000;
		sMi = (int)(sT / 100);


		DrawBox(x, y, x+DRAW_FILE_WIDTH, y+DRAW_FILE_HEIGHT,
			(isActive?GetColor(255, 255, 255):GetColor(64, 64, 64)), 0);
		int n = 
			canSelect  
			? (isActive ? 255 : 160) : 64;
		TCHAR buf[64];
		wsprintf(buf, _T("�t�@�C��%02d"), index+1);
		DrawStringToHandle(x, y, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("%02d/%02d/%02d"), sY, sM, sD);
		DrawStringToHandle(x, y+30, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("%02d:%02d"), sH, sMi);
		DrawStringToHandle(x+200, y+30, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("�v���C���ԁ@%02d:%02d"), pH, pM);
		DrawStringToHandle(x, y+60, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		wsprintf(buf, _T("���́@%03d"), header[index].data.alice_mp);
		DrawStringToHandle(x+240, y+60, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
}

void Scene_File::DrawEmptyFile(int x, int y, BYTE index,
	bool isActive, bool canSelect) const{
		DrawBox(x, y, x+DRAW_FILE_WIDTH, y+DRAW_FILE_HEIGHT,
			(isActive?GetColor(255, 255, 255):GetColor(64, 64, 64)), 0);
		int n = 
			canSelect  
			? (isActive ? 255 : 160) : 64;
		TCHAR buf[64];
		wsprintf(buf, _T("�t�@�C��%02d"), index+1);
		DrawStringToHandle(x, y, buf, GetColor(n,n,n), g_font.hInfo, 0, 0);
		DrawStringToHandle(x, y+32, _T("�t�@�C�������݂��܂���B"), GetColor(255, 255, 255),
			g_font.hInfo, 0, 0);
}

void Scene_File::DrawSelectedFile(int x, int y, BYTE index){
	DrawBox(x, y, x+DRAW_SELECTED_WIDTH, y+DRAW_SELECTED_HEIGHT,
		GetColor(255, 255, 255), 0);
}