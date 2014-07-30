// Window_Info.cpp

#include "Window_Info.h"
#include "KeyConfig.h"
#include "DXFont.h"

extern DXInput		g_input;
extern KeyConfig	g_key;
extern DXFont		g_font;

Window_Info::Window_Info() : Window_Text(){
}

bool Window_Info::Setup(
	WindowSkin* _pSkin,
	WINDOWAREA _frameArea,
	WINDOWAREA _contentArea
	){
	changedTime = CONTENT_CHANGED_DELAY;
	opacity = 255;
	SetFont(g_font.hInfo, FONTSIZE_INFO, FONTSIZE_INFO+4);
	return Window_Text::Setup(_pSkin, _frameArea, _contentArea, true);
}

bool Window_Info::OpenIfCalled(){
	if (state != CLOSED) return false;
	if (g_input.pushedKey & g_key.input[BTN_SHOWINFO]){
		Open(false, false);
		return true;
	}
	return false;
}



bool Window_Info::CheckClose(){
	if (g_input.pushedKey & g_key.input[BTN_CHOOSE]) return true;
	if (g_input.pushedKey & g_key.input[BTN_CANCEL]) return true;
	if (g_input.pushedKey & g_key.input[BTN_SHOWINFO]) return true;
	return false;
}

void Window_Info::ContentChanged(){
	changedTime = 0;
	opacity = 0;
}

BYTE Window_Info::GetDigDir(){
	return g_input.getDigDir();
}

void Window_Info::Update(){
	Window_Base::Update();
	switch (state){
	case SUSPENDED:
		state = UPDATING;
		break;
	}

	if (changedTime <= CONTENT_CHANGED_DELAY){
		changedTime++;
		opacity = max(0, min(255, 255 * changedTime / CONTENT_CHANGED_DELAY));
	}
}