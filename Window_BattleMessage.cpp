// Window_BattleMessage.cpp

#include "Window_BattleMessage.h"
#include <DxLib.h>
#include "DXFont.h"
#include "WindowSkin.h"
#include "Func_Math.h"

extern DXFont		g_font;
extern WindowSkins	g_wndSkins;

Window_BattleMessage::Window_BattleMessage() : Window_Message(){
	Window_Message::Window_Message();
	pParent = NULL;
}

void Window_BattleMessage::Setup(Scene_Battle* _pParent){
	WINDOWAREA frameArea(
		WND_BATTLEMSG_X, WND_BATTLEMSG_Y,
		WND_BATTLEMSG_WIDTH, WND_BATTLEMSG_HEIGHT);
	// ��{�I�ȃZ�b�g�A�b�v
	Window_Message::Setup_FixPadding(
		&g_wndSkins.skin[WNDSKIN_SIMPLE], frameArea,
		WND_BATTLEMSG_PX, WND_BATTLEMSG_PY, true);
	Window_Message::ResetAll();
	// �t�H���g�ƐF�̎w��
	SetColor(GetColor(255, 255, 255));
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	SetFontWidth(FONTSIZE_INFO);
	// �ŏ�����J�������
	Open(true, true);
	// �e�ƂȂ�V�[���̎w��
	pParent = _pParent;
	// ���b�Z�[�W�̎����i�s�ݒ�
	SetReadType(
		F_READTYPE_QUICK | 
		F_READTYPE_DIRECTQUICK | 
		F_READTYPE_PUSH | 
		F_READTYPE_BLANKLINE);
}

void Window_BattleMessage::DrawContent() const{
	int a = 0;
	if(!GetActive()) return;
	DrawLine(16, 30, 0);
	if(lineCount < WND_BATTLEMSG_MOVETIME){ 
		a = PARAM(192*(1.0-(float)lineCount/WND_BATTLEMSG_MOVETIME));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawLine(16, 30-4*lineCount, 1);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Window_BattleMessage::ExUpdate(){
	// ���͕\�����I��������A
	// �\�����̕��͂�����A���X�g�b�N����ł����
	// ��s��}������B
	// ��Window_Message�̃f�t�H���g�@�\�ɂ�����

	// �X�g�b�N����ł���΋�s��}������
	/*
	if(!StockIsEmpty()){
	}
	*/
}

bool Window_BattleMessage::CheckIsIdle(){
	// ���͕\�����I��������A
	// ���݂̍s����ł���A���X�g�b�N����ł����
	// ���݂̏�Ԃ�IDLE�ƌ��Ȃ��B
	if(!DrawMsgIsEmpty(0)){
		return false;
	}
	if(GetClickWaitCount() < WND_BATTLEMSG_MOVETIME){
		return false;
	}
	if(!StockIsEmpty()){
		return false;
	}
	/*
	if(subState != WND_SUBSTATE_READING){
		return false;
	}
	*/
	return true;
}

bool Window_BattleMessage::IsReady(){
	if(state == Window_Base::IDLE){
		return true;
	}
	return false;
}