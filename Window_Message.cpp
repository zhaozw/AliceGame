// Window_Message.cpp

#include <Windows.h>
#include <tchar.h>
#include <DxLib.h>
#include "Window_Message.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "Func_Math.h"


extern WindowSkins		g_wndSkins;
extern DXFont			g_font;
extern DXInput			g_input;
extern KeyConfig		g_key;

//=====================================================
// Window_Message_Draw�n

Window_Message_DrawLine::Window_Message_DrawLine(){
	Clear();
}

void Window_Message_DrawLine::Clear(){
	for(int c=0; c<WND_MSG_DRAWLENGTH; c++){
		for(int n=0; n<3; n++){
			chars[c].character[n] = 0x00;
		}
		chars[c].used = false;
		chars[c].flags = 0x0000; // �����̃t���O
	}
	flags = 0x0000; // �s�̃t���O
}

int Window_Message_DrawLine::GetStrLength() const{
	for(int c=0; c<WND_MSG_DRAWLENGTH; c++){
		if(!chars[c].used){
			return c;
		}
	}
	return WND_MSG_DRAWLENGTH;
}

bool Window_Message_DrawLine::Import(LPTSTR buf, int strLen){
	// ������ɂ��Ĉꕶ����������s��
	TCHAR* p = buf;
	if(p == NULL) return false;
	
	// �܂���������N���A����
	Clear();
	int strCount = 0; // �\�����镶�������Z�ŉ������ڂ܂œ�������
	while((*p != '\0') && (strCount < strLen)){
		switch(_mbclen((BYTE*)p)){
		case 1:
			if(*p >= '0' && *p <= '9'){
				// �����B�ꌅ������ꕶ���ł��̂܂܃R�s�[����B
				chars[strCount].character[0] = *p;
				*p++;
				chars[strCount].character[1] = '\0';
				chars[strCount].character[2] = '\0';
				chars[strCount].used = true;
				chars[strCount].flags |= F_MSGCHAR_ONE_BYTE;
				strCount++;
			}else if(*p == _T('.')){
				// �s���I�h�͋�s��\��
				*p++;
				for(int n=0; n<3; n++){
					chars[strCount].character[n] = _T('\0');
				}
				chars[strCount].used = false;
				chars[strCount].flags |= F_MSGCHAR_ENDMSG;
				strCount++;
			}else{
				// ���ꕶ���B���p�����S�̂��R�s�[������ŕʓr������s���B
				strCount++; // ���݂͔��肵�Ȃ�
			}
			break;
		case 2:
			// �S�p�����B���̂܂܃R�s�[����B
			chars[strCount].character[0] = *p;
			*p++;
			chars[strCount].character[1] = *p;
			*p++;
			chars[strCount].character[2] = '\0';
			chars[strCount].used = true;
			strCount++;
			break;
		default:
			// �G���[
			return false;
			break;
		}
	}
	return true;
}

void Window_Message_DrawLine::DrawContent(
	int hFont, int hColor, int fontWidth,
	int x, int y, int count) const{
	// ��s���̓��e��`�悷��B
	int strLength = (count == -1 ? GetStrLength() : count);
	strLength = min(WND_MSG_DRAWLENGTH, strLength);
	int tmpDrawX = x;
	for(int n=0; n<strLength; n++){
		DrawStringToHandle(tmpDrawX, y, chars[n].character, 
			hColor, hFont);
		if(chars[n].flags & F_MSGCHAR_ONE_BYTE){
			tmpDrawX += fontWidth/2;
		}else{
			tmpDrawX += fontWidth;
		}
	}
}


Window_Message_DrawMsg::Window_Message_DrawMsg(){
	ClearAll();
}

void Window_Message_DrawMsg::ClearLine(int n){
	if(n<0 || n>= WND_MSG_DRAWLINE) return ;
	lines[n].Clear();
}

void Window_Message_DrawMsg::ClearAll(){
	for(int l=0; l<WND_MSG_DRAWLINE; l++){
		ClearLine(l);
	}
	// �f�[�^��z�u����ʒu��������
	// �ŏ��ɃC���N�������g���邽�ߍŏ��̃C���f�b�N�X��-1���Ă���
	index = WND_MSG_DRAWLINE-1;
}

void Window_Message_DrawMsg::DrawLine(
	int hFont, int hColor, int fontWidth, int x, int y,
	int count, int historyCount) const{
		int tmpIndex = SeamLess(index-historyCount, WND_MSG_DRAWLINE);
		if(tmpIndex < WND_MSG_DRAWLINE){
			lines[tmpIndex].DrawContent(hFont, hColor, fontWidth, x, y, count);
		}
}

void Window_Message_DrawMsg::DrawLineByIndex(
	int hFont, int hColor, int fontWidth, int x, int y,
	int index, int count) const{
		if(index < 0 || index >= WND_MSG_DRAWLINE) return;
		lines[index].DrawContent(hFont, hColor, fontWidth, x, y, count);
}


int Window_Message_DrawMsg::GetLineLength(int historyCount) const {
	int tmpIndex = SeamLess(index-historyCount, WND_MSG_DRAWLINE);
	return lines[tmpIndex].GetStrLength();
}

bool Window_Message_DrawMsg::ImportLine(LPTSTR buf){
	index = SeamLess(index+1, WND_MSG_DRAWLINE);
	return lines[index].Import(buf, strlen(buf));
}

void Window_Message_DrawMsg::BlankLine(){
	index = SeamLess(index+1, WND_MSG_DRAWLINE);
	TCHAR str[] = _T("."); // �s���I�h�ŋ�s��\�� 
	lines[index].Import(str, strlen(str));
}

//=====================================================
// Window_Message_Stock�n


Window_Message_StockLine::Window_Message_StockLine(){
}

void Window_Message_StockLine::Clear(){
	strcpy_s(chars, WND_MSG_STOCKLENGTH, _T(""));
}

bool Window_Message_StockLine::IsEmpty() const{
	return (strlen(chars) == 0);
}

Window_Message_StockMsg::Window_Message_StockMsg(){
	ClearAll();
	index = 0;
	emptyIndex = 0;
}

void Window_Message_StockMsg::ClearLine(int n){
	if(n<0 || n>= WND_MSG_STOCKLINE) return;
	lines[n].Clear();
}

void Window_Message_StockMsg::ClearAll(){
	for(int l=0; l<WND_MSG_STOCKLINE; l++){
		ClearLine(l);
	}
	// �f�[�^��z�u����ʒu��������
	index = 0;
	emptyIndex = 0;
}

bool Window_Message_StockMsg::AddMsg(LPTSTR str, int strlen){
	// ���������������Ȃ����̃`�F�b�N
	if(strlen >= WND_MSG_STOCKLENGTH) return false;
	if(emptyIndex >= WND_MSG_STOCKLINE){
		return false;
	}
	// �o�b�t�@�ɋ󂫂����邩�̃`�F�b�N
	if(!lines[emptyIndex].IsEmpty()) return false;
	// ��s�ɑ΂��ē��e���R�s�[����
	strcpy_s(lines[emptyIndex].chars, WND_MSG_STOCKLENGTH, str);
	// ��ł͂Ȃ��Ȃ����̂ŃC���f�b�N�X�����炷
	emptyIndex = SeamLess(emptyIndex+1, WND_MSG_STOCKLINE);
	return true;
}

bool Window_Message_StockMsg::ReadLine(LPTSTR buf, bool discard){
	// ��s�̏ꍇ��false��Ԃ�
	if(IsEmpty()) return false;
	// �ǂݍ��ނׂ��s�̓��e���R�s�[����
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, lines[index].chars);
	// �s����
	if(discard) DiscardLine();
	return true;
}

void Window_Message_StockMsg::DiscardLine(){
	// ���݂̍s����ɂ���
	strcpy_s(lines[index].chars, WND_MSG_STOCKLENGTH-1, _T(""));	
	// index��emptyIndex��ǂ��z���Ă͂����Ȃ�
	if(index != emptyIndex) index++;
	index = SeamLess(index, WND_MSG_STOCKLINE);
}

//=====================================================
// Window_Message

Window_Message::Window_Message() : Window_Text(){
	// �����o�̏�����
	ResetAll();
}

void Window_Message::Setup(
	WindowSkin* _pSkin, WINDOWAREA _frameArea, WINDOWAREA _contentArea,
	bool _visible){
	// ������
	Window_Text::Setup(_pSkin, _frameArea, _contentArea, _visible);
	// ���̒l
	SetColor(GetColor(255, 255, 255));
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	SetFontWidth(FONTSIZE_INFO);
	// �S�ă��Z�b�g����
	ResetAll();
}

void Window_Message::Setup_FixPadding(
	WindowSkin* _pSkin, WINDOWAREA _frameArea,
	int _px, int _py, bool _visible){
	// ������
	Window_Text::Setup_FixPadding(_pSkin, _frameArea, _px, _py, _visible);
	// ���̒l
	SetColor(GetColor(255, 255, 255));
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	SetFontWidth(FONTSIZE_INFO);
	// �S�ă��Z�b�g����
	ResetAll();
}


void Window_Message::ResetAll(){
	// ���e�̃N���A
	drawMsg.ClearAll();
	stockMsg.ClearAll();

	// �ϐ��̏�����
	linePos = 0;
	lineCount = 0;
	lineCountMin = 0;
	clickWaitCount = 0;
	clickWaitTime = -1;
	subState = WNDSUBSTATE_NOTEXT;
	fontWidth = 0;
	messageSpeed = WND_MSG_DEFSPD;
	readTypeFlag = F_READTYPE_QUICK;
	skipToEmpty = false;
}

bool Window_Message::AddStockMsg(LPTSTR str, int strlen){
	// �\���҂������Ƀ��b�Z�[�W��ǉ�
	if(!stockMsg.AddMsg(str, strlen)){
		return false;
	}
	// ���݂̃X�e�[�g�Ɋւ�炸�X�e�[�g���r�W�[��Ԃɂ���
	// (���IDLE��Ԃ���UPDATING��Ԃɕω�)
	state = UPDATING;
	return true;
}

void Window_Message::Update(){
	Update_Common();
	bool flag = false;
	switch(state){
	case UPDATING:
		// �\�����̍s���X�V���ł���΍X�V����B
		// �X�V���I�����Ă���ꍇ�͎��̍s��ǂݍ��ނ��A
		// �������̓X�g�b�N���Ȃ��ꍇ��IDLE��Ԃɂ���B
		switch(subState){
		case WNDSUBSTATE_NOTEXT:
			// �e�L�X�g���Ȃ����
			// �X�g�b�N��Ԃ̃e�L�X�g������Γǂݍ��ށB
			// �Ȃ��ꍇ��IDLE��ԂɂȂ�B
			if(stockMsg.IsEmpty()){
				state = IDLE;
			}else{
				NewLine(false);
			}
			break;
		case WNDSUBSTATE_READING:
			// �e�L�X�g��ǂ�ł�����
			UpdateLine();
			// ���s����
			CheckNewLine(
				((g_input.pushedKey & g_key.input[BTN_CHOOSE]) != 0),
				((g_input.key & g_key.input[BTN_CANCEL]) != 0));
			// IDLE��ԂɂȂ邩�ǂ����̊m�F
			// (�N���X�Ǝ��̓��e)
			if(CheckIsIdle()){
				subState = WNDSUBSTATE_NOTEXT;
				state = IDLE;
			}
			break;
			/*
		case WNDSUBSTATE_CLICKWAIT:
			// �N���b�N�҂��̏��
			// �N���b�N���ꂽ�ꍇ�A���邢�͑҂����Ԃ��߂����ꍇ��
			// �e�L�X�g���Ȃ���ԂɂȂ�B
			subState = WNDSUBSTATE_NOTEXT;
			break;
			*/
		case WNDSUBSTATE_UNDIFINED:
			// �悭������Ȃ���ԁB
			break;
		}
		break;
	case SUSPENDED:
		state = IDLE;
		break;
	case IDLE:
		break;
	}
	// �N���X�Ǝ��̍X�V
	ExUpdate();
}

void Window_Message::ExUpdate(){
}

bool Window_Message::CheckIsIdle(){
	return false;
}

void Window_Message::NewLine(bool force){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	// �V�����s���X�g�b�N����ǂݍ��ށB
	if(stockMsg.ReadLine(buf, true)){
		// �`��p�̍s�ɓǂݍ��񂾓��e���R�s�[���ĉ��߂�����
		drawMsg.ImportLine(buf);
	}else{
		// �ǂݍ��ލs���Ȃ��ꍇ�A��s����������
		drawMsg.BlankLine();
	}
	// ���b�Z�[�W�ǂݍ��ݒ���Ԃɂ���
	subState = WNDSUBSTATE_READING;
	// drawMsg.NextLine();
	linePos = 0;
	lineCount = 0;
	clickWaitCount = 0;
}

void Window_Message::UpdateLine(){
	// ���݂̍s���Ō�܂ł������ꍇ�̓N���b�N�҂���ԂɂȂ�B
	lineCount++;
	if((readTypeFlag & F_READTYPE_NOWAIT)
		|| skipToEmpty){
			// �u�ԕ\��
			linePos = GetLineLength();
			if(stockMsg.IsEmpty() && skipToEmpty){
				// ���[�܂ŕ\�����ăX�L�b�v���I��
				lineCount = 9999;
				skipToEmpty = false;
			}
	}else{
		linePos = messageSpeed * lineCount;
	}
	// ���͂̕\�����I����Ă���ꍇ
	if(linePos >= GetLineLength()){
		clickWaitCount++;
	}
}

bool Window_Message::CheckNewLine(bool chooseKey, bool skipKey){
	// ���s���邩�ǂ���
	bool flag = false;

	if(linePos >= GetLineLength()){
		// ���͂��\���������Ă��鎞
		if((readTypeFlag & F_READTYPE_AUTOPLAY) == 0x0000){
			// �펞�����i�s�t���O�������Ă��Ȃ����
			// ���͂̕\�����I����Ă���ꍇ�A�����ꂩ�̃{�^���Ő��
			if(chooseKey){
				// ����L�[
				flag = true;
			}
			if(skipKey && (readTypeFlag & F_READTYPE_AUTOQUICK)){
				// �X�L�b�v�L�[���L���ȏꍇ
				flag = true;
			}
		}
		// ���Ԍo�߂ɂ��X�L�b�v
		if(clickWaitTime != -1){
			if(clickWaitCount >= clickWaitTime){
				flag = true;
			}
		}
		// ���ɕ��͂�����ꍇ�̃X�L�b�v
		if(readTypeFlag & F_READTYPE_PUSH){
			if(CheckStockMsg() && clickWaitCount > 4){ // �҂����Ԃɂ��Ă͗v����
				flag = true;
			}
		}
		// �펞�X�L�b�v
		if(readTypeFlag & F_READTYPE_FLOOD){
			flag = true;
		}
		// �펞�X�L�b�v
		if(skipToEmpty){
			flag = true;
		}
		// �X�g�b�N����s�ł����Ă��L�[�Ői�߂邩
		if(!(readTypeFlag & F_READTYPE_BLANKLINE)){
			if(StockIsEmpty()){
				flag = false;
			}
		}
	}else{
		// ���͂��\�����I����Ă��Ȃ��ꍇ
		if(lineCount > lineCountMin){
			// �u�ԕ\���\
			if((readTypeFlag & F_READTYPE_QUICK) != 0x0000){
				if(chooseKey){
					lineCount = 9999; // ��C�ɍs�̏I���܂ŕ\��
					if((readTypeFlag & F_READTYPE_DIRECTQUICK) != 0x0000){
						// �����ɉ��s
						flag = true;
					}
				}
			}
			// �y�[�W�I���܂Ői��
			if((readTypeFlag & F_READTYPE_SKIPTOEMPTY) != 0x0000){
				if(lineCount > 1 && chooseKey){
					skipToEmpty = true;
				}
			}
			if((readTypeFlag & F_READTYPE_AUTOQUICK) != 0x0000){
				if(skipKey){
					lineCount = 9999; // ��C�ɍs�̏I���܂ŕ\��
					if((readTypeFlag & F_READTYPE_DIRECTQUICK) != 0x0000){
						// �����ɉ��s
						flag = true;
					}
				}
			}
		}
	}

	// ���ۂ̉��s���s��
	if(flag) NewLine(false);
	return flag;
}

bool Window_Message::CheckStockMsg(){
	return !StockIsEmpty();
}

int Window_Message::GetLineLength() const{
	return drawMsg.GetLineLength();
}

void Window_Message::DrawContent() const{
	// �\�����@�͊e�N���X�ɔh������B
}

void Window_Message::DrawLine(int dx, int dy, int historyCount) const{
	// �w�肵����s��`�悷��
	drawMsg.DrawLine(windowFont.hFont, windowFont.color, fontWidth,
		frameArea.x+dx, frameArea.y+dy,
		(historyCount==0 ? linePos : -1), historyCount);
}

void Window_Message::DrawLineByIndex(int dx, int dy, int drawIndex) const{
	// �w�肵����s��`�悷��
	drawMsg.DrawLineByIndex(windowFont.hFont, windowFont.color, fontWidth,
		frameArea.x+contentArea.x+dx, frameArea.y+contentArea.y+dy,
		drawIndex, (drawIndex==drawMsg.GetIndex() ? linePos : -1));
}

