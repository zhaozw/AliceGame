// Window_Text.cpp

#include "Window_Text.h"

#include <string.h>
#include <DxLib.h>
#include "Static_Game.h"

Window_Text::Window_Text() : Window_Base(), windowFont(){
	windowFont.align = ALIGN_LEFT;
}

int Window_Text::GetDrawDeltaX(TCHAR* content, int strSize, int _hFont) const{
	int size = strSize > 0 ? strSize : strlen(content);
	int font = _hFont != 0 ? _hFont : windowFont.hFont;
	int drawWidth = GetDrawStringWidthToHandle(content, size, font);
	switch(windowFont.align){
	case ALIGN_LEFT:
		return 0;
		break;
	case ALIGN_CENTER:
		return (contentArea.w - drawWidth)/2;
		break;
	case ALIGN_RIGHT:
		return contentArea.w - drawWidth;
		break;
	}
	return 0;
}