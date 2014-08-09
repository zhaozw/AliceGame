// Window_HintMessage.cpp

#include "Window_HintMessage.h"
#include <iostream>
#include <fstream>
#include <DxLib.h>
#include "WindowSkin.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"

extern WindowSkins		g_wndSkins;
extern DXFont			g_font;
extern DXInput			g_input;
extern KeyConfig		g_key;

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
		Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE],
			GetWindowArea(100, 200, WND_WIDTH-200, WND_HEIGHT-400),
			GetWindowArea(16, 16, WND_WIDTH-200-32, WND_HEIGHT-400-32),
			true);
		SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
		SetColor(GetColor(255,255,192));
		SetFontWidth(FONTSIZE_INFO);
		SetMessageSpeed(0.4);
		break;
	case WND_HINT_ALICE:
		Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE],
			GetWindowArea(100, 200, WND_WIDTH-200, WND_HEIGHT-400),
			GetWindowArea(16, 16, WND_WIDTH-200-32, WND_HEIGHT-400-32),
			true);
		SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
		SetColor(GetColor(255,255,192));
		SetFontWidth(FONTSIZE_INFO);
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
		F_READTYPE_QUICK | F_READTYPE_AUTOQUICK | F_READTYPE_PUSH;
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
		// �R�}���h�̔���
		switch(CheckCommand(tmpBuf)){
		case WND_HINT_CHKCMD_NEWPAGE:
			isEnd = true;
			break;
		case WND_HINT_CHKCMD_END:
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

	return isFileEnd ? WND_HINT_NEWPAGE_END : WND_HINT_NEWPAGE_OK;
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
				drawMsg.ClearAll();
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_OVERFLOW:
				isError = true;
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_END:
				drawMsg.ClearAll();
				isTerminated = true; // �������ܕ���̂ł͂Ȃ��A�Ō�̕��͂�\�����ĕ���
				state = UPDATING;
				break;
			case WND_HINT_NEWPAGE_ERROR:
				isError = true;
				Close();
				break;
			}
		}else{
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

void Window_HintMessage::DrawContent() const{
	if(!GetActive()) return;
	for(int n=0; n<WND_MSG_DRAWLINE; n++){
		if(n <= drawMsg.GetIndex() || true){
			DrawLineByIndex(10, 10+25*n, n);
		}
	}
}