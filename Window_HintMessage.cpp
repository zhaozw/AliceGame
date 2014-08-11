// Window_HintMessage.cpp

#include "Window_HintMessage.h"
#include <iostream>
#include <fstream>
#include <DxLib.h>
#include "WindowSkin.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "Image.h"
#include "Sound.h"

extern WindowSkins		g_wndSkins;
extern DXFont			g_font;
extern DXInput			g_input;
extern KeyConfig		g_key;
extern Image			g_image;
extern Sound			g_sound;

Window_HintMessage::Window_HintMessage() : Window_Message(){
	// �E�B���h�E�̏����N���A����B
	Clear();
}

void Window_HintMessage::Clear(){
	// �t�@�C�������Z�b�g
	_tcscpy_s(fileName, MAX_PATH, _T(""));
	// �t�@�C���ʒu���Z�b�g
	filePos = 0;
	lineCount = 0;
	isError = false;
	isTerminated = false;
	ClearBuffer();
	drawMsg.ClearAll();
	stockMsg.ClearAll();
}

void Window_HintMessage::ClearBuffer(){
	linePos = 0;
	for(int n=0; n<WND_MSG_DRAWLINE; n++){
		strcpy_s(buffer[n], WND_MSG_STOCKLENGTH-1, _T(""));
	}
}


bool Window_HintMessage::OpenAndPlay(LPTSTR fileName, WORD _typeID){
	// typeID���Z�b�g����
	if(!SetupByTypeID(_typeID, true)){
		return false;
	}
	// �t�@�C�������Z�b�g���A�J���邩�ǂ������m�F����
	Clear();
	if(!SetFileName(fileName)){
		return false;
	}
	// �E�B���h�E���J��
	if(Open(false, false) != WNDOPEN_SUCCEED){
		return false;
	}
	return true;
}

bool Window_HintMessage::SetupByTypeID(WORD _typeID, bool check){
	switch(_typeID){
	case WND_HINT_SHANGHAI:
		Setup(&g_wndSkins.skin[WNDSKIN_BALLOON],
			GetWindowArea(200, 150, 600, 300),
			GetWindowArea(90, 85, 440, 130),
			true);
		SetFont(g_font.hTalk, FONTSIZE_TALK, FONTSIZE_TALK+8);
		SetColor(GetColor(128, 48, 32));
		SetFontWidth(FONTSIZE_TALK);
		SetMessageSpeed(0.4);
		break;
	case WND_HINT_ALICE:
		Setup(&g_wndSkins.skin[WNDSKIN_BALLOON],
			GetWindowArea(200, 150, 600, 300),
			GetWindowArea(90, 85, 440, 130),
			true);
		SetFont(g_font.hTalk, FONTSIZE_TALK, FONTSIZE_TALK+8);
		SetColor(GetColor(128, 48, 32));
		SetFontWidth(FONTSIZE_TALK);
		SetMessageSpeed(0.4);
		break;
	default:
		if(check){
			// �L���Ȓl�ł͂Ȃ�(�`�F�b�N����ꍇ�̂�false��Ԃ�)
			return false;
		}
	}
	// ���ʂ̐ݒ�
	// �Ō�̍s�ȊO�̓N���b�N�҂������Ȃ�
	readTypeFlag = 
		F_READTYPE_SKIPTOEMPTY | F_READTYPE_AUTOQUICK | F_READTYPE_PUSH;
	typeID = _typeID;
	return true;
}


bool Window_HintMessage::SetFileName(LPTSTR name){
	_tcscpy_s(fileName, MAX_PATH-1, name);
	filePos = 0;
	lineCount = 0;

	// �t�@�C�����J��
	// (�J���邩�ǂ����̊m�F�������s��)
	std::basic_ifstream<TCHAR> fin;
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return false;
	}

	// �t�@�C�������
	fin.close();
	return true;
}

BYTE Window_HintMessage::NewPage(){
	bool isFirstPage = (lineCount == 0);
	// �錾
	std::basic_ifstream<TCHAR> fin;
	bool isError = false;
	bool isEnd = false;			// ��y�[�W���̓ǂݍ��݂��I��������
	bool isFileEnd = false;	// �t�@�C�����[�ɒB������
	TCHAR tmpBuf[WND_MSG_STOCKLENGTH];
	strcpy_s(tmpBuf, WND_MSG_STOCKLENGTH-1, _T(""));

	// �t�@�C�����J��
	fin.open(fileName, std::ios::in);
	if(!fin){
		fin.close();
		return WND_HINT_NEWPAGE_ERROR;
	}
	if(fin.eof()){
		isTerminated = true;
		return WND_HINT_NEWPAGE_END;
	}

	// �t�@�C���ʒu���Z�b�g
	fin.seekg(filePos, std::ios::beg);

	ClearBuffer();
	do{
		// �t�@�C����ǂݍ����buffer�ɃR�s�[����
		// 1�s�ǂݍ���
		fin.getline(tmpBuf, WND_MSG_STOCKLENGTH);
		lineCount++;
		// �R�}���h�̔���
		switch(CheckCommand(tmpBuf)){
		case WND_HINT_CHKCMD_NEWPAGE:
			drawMsg.ClearAll();
			isEnd = true;
			break;
		case WND_HINT_CHKCMD_END:
			drawMsg.ClearAll();
			isFileEnd = true;
			isEnd = true;
			break;
		case WND_HINT_CHKCMD_NONE:
			// �o�b�t�@�̓��e���R�s�[
			if(linePos < WND_MSG_DRAWLINE){
				strcpy_s(buffer[linePos], WND_MSG_STOCKLENGTH-1, tmpBuf);
				linePos++;
			}else{
				// �G���[�����ƌ��Ȃ�
				isError = true;
			}
		}
	}while(!isError && !isEnd);

	// �t�@�C���ʒu��ۑ�����
	filePos = fin.tellg();

	// �o�b�t�@��stockLine�Ɉړ�������
	if(!FlushBuffer()){
		return WND_HINT_NEWPAGE_ERROR;
	}

	if(isFileEnd){
		if(!isFirstPage){
			g_sound.PlaySE(MYSE_MESSAGE_NEWPAGE, 0.8f);
		}
		return WND_HINT_NEWPAGE_END;
	}else{
		// �����ŉ���炷
		if(!isFirstPage){
			g_sound.PlaySE(MYSE_MESSAGE_NEWPAGE, 0.8f);
		}
		return WND_HINT_NEWPAGE_OK;
	}
	// return isFileEnd ? WND_HINT_NEWPAGE_END : WND_HINT_NEWPAGE_OK;
}

bool Window_HintMessage::FlushBuffer(){
	// stockMsg�ɒl���R�s�[����
	for(int n=0; n<linePos; n++){
		stockMsg.AddMsg(buffer[n], strlen(buffer[n]));
	}
	ClearBuffer();
	return true;
}

WORD Window_HintMessage::CheckCommand(LPTSTR buf){
	if(buf == NULL) return WND_HINT_CHKCMD_ERROR;
	if(buf[0] != '#') return WND_HINT_CHKCMD_NONE;
	int bufLng = strlen(buf);
	bool isEnd = false;
	int num = 0;		// �X�y�[�X��؂�̒P��̐�
	int pos = 0;		// ���݂̒P���ǂވʒu

	// �錾
	TCHAR value[4][16];
	for(int n=0; n<4; n++){
		strcpy_s(value[n], 16-1, _T(""));
	}

	// �������ŏ�����ǂݍ���ł���
	for(int i=1; (i<=bufLng && !isEnd); i++){ // ���[��'\0'�܂Ŋ܂�(�擪��#�͏���)
		switch(buf[i]){
		case _T('\0'):
		case _T('\n'):		// �ǂݍ��݂̏I�[
			value[num][pos] = '\0';
			num++;
			isEnd = true;
			break;
		case _T(','):		// �J���} : ���̒l��
			value[num][pos] = '\0';
			num++;
			pos = 0;
			if(num >= 4){
				isEnd = true;
			}
			break;
		case _T(' '):		// �� : �l�̐擪�ł���Ζ�������
			if(pos > 0){ // �擪�ł��邩
				value[num][pos] = buf[i];
				pos++;
			}
			break;
		default:			// ���̑��̕��� : �l���p��
			value[num][pos] = buf[i];
			pos++;
			break;
		}
	}

	// �R�}���h�̔�����s��
	if(_tcscmp(value[0], _T("newpage")) == 0){
		return WND_HINT_CHKCMD_NEWPAGE;
	}
	if(_tcscmp(value[0], _T("exit")) == 0){
		return WND_HINT_CHKCMD_END;
	}
	
	// �ǂ̃R�}���h�ɂ����Ă͂܂�Ȃ��G���[
	return WND_HINT_CHKCMD_ERROR;
}

void Window_HintMessage::ExUpdate(){
	switch(state){
	case UPDATING:

		break;
	case IDLE:
		if(!isTerminated){
			// ���̃y�[�W��ǂݍ��ށB
			switch(NewPage()){
			case WND_HINT_NEWPAGE_OK:
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_OVERFLOW:
				isError = true;
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_END:
				isTerminated = true; // �������ܕ���̂ł͂Ȃ��A�Ō�̕��͂�\�����ĕ���
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_ERROR:
				isError = true;
				Close();
				break;
			}
		}else{
			// ���e���N���A���Ă������
			Clear();
			Close();
		}
		break;
	}
}

bool Window_HintMessage::CheckIsIdle(){
	// �Ō�̍s��\�����I����āA�N���b�N���ꂽ��IDLE�ɂȂ�B
	// (�����Ď��̍s���ǂݍ��܂��)
	if(state == UPDATING){
		if(linePos >= GetLineLength()){
			if(StockIsEmpty()){
				if((g_input.pushedKey & g_key.input[BTN_CHOOSE]) != 0){
					return true;
				}
			}
		}
	}
	return false;
}

void Window_HintMessage::DrawFrameBack() const{
	if(!GetActive()) return;
	int tmpY = 0;
	switch(typeID){
	case WND_HINT_ALICE:
	case WND_HINT_SHANGHAI:
		// �L�����N�^�[�̕`��
		tmpY = -15*sin(2.0*M_PI*activeCount/400);
		DrawRotaGraphF(
			frameArea.x-50, frameArea.y+frameArea.h/2+tmpY,
			0.8, 0, g_image.icon.doll[0][3][0], 1);
	}
}

void Window_HintMessage::DrawContent() const{
	if(!GetActive()) return;
	bool waitClick = false;
	if(state == UPDATING ){
		if(linePos >= GetLineLength()){
			if(StockIsEmpty()){
				waitClick = true;
			}
		}
	}
		

	switch(typeID){
	case WND_HINT_ALICE:
	case WND_HINT_SHANGHAI:
		// ���͂̕`��
		for(int n=0; n<WND_MSG_DRAWLINE; n++){
			if(n <= drawMsg.GetIndex() || true){
				DrawLineByIndex(0, windowFont.lineHeight*n, n);
			}
		}
		// �N���b�N�҂��L���̕`��
		if(waitClick){
			DrawGraph(
				frameArea.x + contentArea.x + contentArea.w - 16,
				frameArea.y + contentArea.y 
				+ contentArea.h + 8 + 6*sin(2*M_PI*activeCount/30),
				g_image.icon.cursor[0], 1);
			// DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), 1);
		}
	}
}